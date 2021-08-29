#pragma once

#include "MockVisitor.h"

#include <type_traits>
#include <string_view>

namespace fon {

enum class ctor : uint8_t {};

template <typename T>
struct proxy;

template <typename Data> struct list_adapter;
template <typename Data> list_adapter(Data&, size_t) -> list_adapter<Data>;
template <typename Data> list_adapter(Data const&) -> list_adapter<Data const>;

template <typename Data> struct map_adapter;
template <typename Data> map_adapter(Data&, size_t) -> map_adapter<Data>;
template <typename Data> map_adapter(Data const&) -> map_adapter<Data const>;

template <typename Data> struct struct_adapter;
template <typename Data> struct_adapter(Data&) -> struct_adapter<Data>;
template <typename Data> struct_adapter(Data const&) -> struct_adapter<Data const>;

template <typename Visitor, typename T>
concept has_reflect_v = requires(Visitor visitor, T t) {
    { T::reflect(visitor, t) };
};

template <typename Visitor, typename T>
concept has_proxy_v = requires(Visitor visitor, T t) {
    { proxy<T>::reflect(visitor, t) };
};

template <typename T>
concept has_list_adapter_v = requires(T t, size_t l) {
    { list_adapter<T>{t, l} };
    { list_adapter<T const>{t} };
};

template <typename T>
concept has_map_adapter_v = requires(T t, size_t l) {
    { map_adapter<T>{t, l} };
    { map_adapter<T const>{t} };
};

template <typename T>
concept has_struct_adapter_v = requires(T t) {
    { struct_adapter<T>{t} };
    { struct_adapter<T const>{t} };
};


/*
// use as is_same_base<std::vector, T>::type
template <template <typename...> typename T1, typename T2>
struct is_same_base : std::false_type {};

template <template <typename...> typename T, typename ...Args>
struct is_same_base<T, T<Args...>> : std::true_type{};

template <template <typename...> typename T1, typename T2>
constexpr static bool is_same_base_v = is_same_base<T1, std::decay_t<T2>>::value;

template <typename T, typename ...Args>
constexpr static bool is_any_of_v = (std::is_same_v<T, Args> or...);*/

template <typename T>
auto getEmpty() -> T {
    static_assert(std::is_constructible_v<T, ctor> or std::is_constructible_v<T>,
        "object is not constructible");

    if constexpr (std::is_constructible_v<T, ctor> and not std::is_arithmetic_v<T>) {
        return T{ctor{}};
    } else if constexpr (std::is_constructible_v<T>) {
        return T{};
    } else {
        return T{};
    }
}

}
