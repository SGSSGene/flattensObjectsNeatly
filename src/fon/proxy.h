#pragma once

#include "traits.h"

#include <type_traits>
#include <vector>
#include <map>
#include <iostream>

namespace fon {

// converter functions
template <typename T>
    requires (std::is_enum_v<T>)
struct proxy<T> {
    static constexpr void reflect(auto& visitor, auto& self) {
        using UT = std::underlying_type_t<T>;
        auto val = static_cast<UT>(self);
        visitor % val;
        self = T {val};
    }
    static constexpr void reflect(auto& visitor, auto const& self) {
        using UT = std::underlying_type_t<T>;
        auto val = static_cast<UT>(self);
        return visitor % val;
    }
};

template <typename T, typename ...Args>
struct proxy<std::vector<T, Args...>> {
    static constexpr void reflect(auto& visitor, auto& self) {
        visitor % fon::List{[&](size_t len) { // init write
            self.clear();
            self.resize(len, getEmpty<T>());
        }, [&](auto& cb) { // write each element
            for (size_t i{0}; i < self.size(); ++i) {
                cb(i, self[i]);
            }
        }};
    }

    static constexpr void reflect(auto& visitor, auto const& self) {
        visitor % fon::List{[&]() { // init read
            return self.size();
        }, [&](auto& cb) { // read each element
            for (size_t i{0}; i < self.size(); ++i) {
                cb(i, self[i]);
            }
        }};
    }
};

template <typename Key, typename Value, typename ...Args>
struct proxy<std::map<Key, Value, Args...>> {
    static constexpr void reflect(auto& visitor, auto& self) {
        size_t totalCount {};
        visitor % fon::Map{[&](size_t len) { // init write
            totalCount = len;
            self.clear();
        }, [&](auto& cb) { // write each element
            for (size_t i{0}; i < totalCount; ++i) {
                Key key;
                Value value;
                cb(key, value);
                self.try_emplace(key, value);
            }
        }};
    }

    static constexpr void reflect(auto& visitor, auto const& self) {
        visitor % fon::Map{[&]() { // init read
            return self.size();
        }, [&](auto& cb) { // read each element
            for (auto const& [key, value] : self) {
                cb(key, value);
            }
        }};
    }
};



}
