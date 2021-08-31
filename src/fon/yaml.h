#pragma once

#include "Visitor.h"
#include "proxy.h"
#include "traits.h"

#include <cassert>
#include <fmt/format.h>
#include <tuple>
#include <yaml-cpp/yaml.h>
#include "demangle/demangle.h"

namespace fon::yaml {

namespace details {

template <typename T>
auto serialize(T const& _input, YAML::Node start = {}) -> YAML::Node {
    auto& input = _input;

    YAML::Node top;
    fon::visit([&]<typename Visitor, typename ValueT>(Visitor& visitor, ValueT const& obj) {

        auto stackVisit = [&](auto& obj) {
            YAML::Node a = top;
            top.reset();
            visitor % obj;
            YAML::Node b = top;
            top.reset(a);
            return b;
        };

        // Interpret int8_t and uint8_t as ints not chars
        if constexpr (std::is_same_v<ValueT, int8_t>
                    or std::is_same_v<ValueT, uint8_t>) {
            top = static_cast<int16_t>(obj);
        } else if constexpr (std::is_arithmetic_v<ValueT>
                      or std::is_same_v<std::string, ValueT>
                      or std::is_same_v<YAML::Node, ValueT>) {
            top = obj;
        } else if constexpr (std::is_same_v<ValueT, std::string_view>
                            or std::is_same_v<ValueT, char const*>) {
            top = std::string{obj};
        } else if constexpr (fon::has_list_adapter_v<ValueT>) {
            auto adapter = fon::list_adapter{obj};
            adapter.visit([&](auto& key, auto& value) {
                auto right = stackVisit(value);
                top.push_back(right);
            });
        } else if constexpr (fon::has_map_adapter_v<ValueT>) {
            auto adapter = fon::map_adapter{obj};
            adapter.visit([&](auto& key, auto& value) {
                auto left  = stackVisit(key);
                auto right = stackVisit(value);
                top[left] = right;
            });
        } else if constexpr (fon::has_struct_adapter_v<ValueT>) {
            auto adapter = fon::struct_adapter{obj};
            adapter.visit([&](auto& key, auto& value) {
                auto left  = stackVisit(key);
                auto right = stackVisit(value);
                top[left] = right;
            });
        } else if constexpr (fon::has_proxy_v<ValueT>) {
            proxy<ValueT>::reflect(visitor, obj);
        } else {
            fmt::print("unknown visit(serialization): {}  -  {}\n", demangle<ValueT>(), demangle(obj));
        }
    }, input);

    return top;
//    return root;
}


struct yaml_error : std::runtime_error {
    yaml_error(std::string s, YAML::Node const& node)
        : runtime_error(s + " in line " + std::to_string(node.Mark().line) + ":" + std::to_string(node.Mark().column) + " (" + std::to_string(node.Mark().pos) + ")")
    {}
};

struct StackGuard final {
    std::vector<YAML::Node>& stack;

    StackGuard(std::vector<YAML::Node>& stack, YAML::Node n)
        : stack{stack}
    {
        stack.push_back(n);
    }
    void reset(YAML::Node n) {
        stack.pop_back();
        stack.push_back(n);
    }
    ~StackGuard() {
        stack.pop_back();
    }
};

template <typename T>
auto deserialize(YAML::Node root) -> T {

    auto res = getEmpty<T>();
    std::vector<YAML::Node> nodeStack{root};
    visit([&]<typename Visitor, typename ValueT>(Visitor& visitor, ValueT& obj) {
        auto top = nodeStack.back();

        if (not top.IsDefined()) {
            return;
        }

        try {
            if constexpr (std::is_same_v<YAML::Node, ValueT>) {
                obj = top;
            } else if constexpr (std::is_arithmetic_v<ValueT>
                      or std::is_same_v<std::string, ValueT>) {
                if constexpr (std::is_same_v<ValueT, int8_t>
                              or std::is_same_v<ValueT, uint8_t>
                              or std::is_same_v<ValueT, int16_t>
                              or std::is_same_v<ValueT, uint16_t>
                              or std::is_same_v<ValueT, int32_t>
                              or std::is_same_v<ValueT, uint32_t>) {
                    auto v = top.template as<int64_t>();
                    if (v < std::numeric_limits<ValueT>::min() or v > std::numeric_limits<ValueT>::max()) {
                        throw std::runtime_error("value out of range");
                    }
                    obj = v;
                } else {
                    // !TODO no check, we just hope it works
                    obj = top.template as<ValueT>();
                }
            } else if constexpr (fon::has_list_adapter_v<ValueT>) {
                auto adapter = fon::list_adapter<ValueT>{obj, top.size()};
                adapter.visit([&](size_t idx, auto& value) {
                    auto g = StackGuard{nodeStack, top[idx]};
                    visitor % value;
                });
            } else if constexpr (fon::has_map_adapter_v<ValueT>) {
                auto adapter = fon::map_adapter<ValueT>{obj, top.size()};
                auto iter = top.begin();
                adapter.visit([&](auto& key, auto& value) {
                    auto g = StackGuard{nodeStack, iter->first};
                    visitor % key;
                    g.reset(iter->second);
                    visitor % value;
                    ++iter;
                });
            } else if constexpr (fon::has_struct_adapter_v<ValueT>) {
                auto adapter = fon::struct_adapter{obj};
                adapter.visit([&](auto& key, auto& value) {
                    //!WORKAROUND for bug: https://github.com/jbeder/yaml-cpp/issues/979
                    auto fakeKey = [&]() {
                        YAML::Emitter emit;
                        emit << serialize(key);
                        return std::string{emit.c_str()};
                    }();
                    auto g = StackGuard{nodeStack, top[fakeKey]};
                    visitor % value;
                });
            } else if constexpr (fon::has_proxy_v<ValueT>) {
                proxy<ValueT>::reflect(visitor, obj);
            } else {
                fmt::print("unknown visit (deserialization): {}  -  {}\n", demangle<ValueT>(), demangle(obj));
            }
        } catch(yaml_error const&) {
            throw;
        } catch(...) {
            std::throw_with_nested(yaml_error("error reading yaml file ", top));
        }
    }, res);

    return res;
}

}

using details::serialize;
using details::deserialize;

}

/*namespace fon {

// convertible
template <typename Node>
struct convert<Node, ::YAML::Node> {
    static constexpr Type type = Type::Convertible;
    template <typename Node2>
    static void access(Node2& node, YAML::Node& obj) {
        std::stringstream ss;
        ss << obj;
        auto val = ss.str();
        node % val;
        obj = val;
    }

    template <typename Node2>
    static void access(Node2& node, YAML::Node const& obj) {
        std::stringstream ss;
        ss << obj;
        auto val = ss.str();
        return node % val;
    }
};

}*/