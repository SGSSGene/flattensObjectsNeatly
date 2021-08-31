#pragma once

#include <variant>

#include "proxy.h"

namespace fon {

template <typename ...Args>
struct proxy<std::variant<Args...>> {
    static constexpr void reflect(auto& visitor, auto& self) {
        size_t index;
        visitor["index"] % index;
        reflect_impl(visitor, self, index);
    }

    template <size_t N=0>
    static constexpr void reflect_impl(auto& visitor, auto& self, size_t index) {
        if constexpr (N < sizeof...(Args)) {
            if ( N == index ) {
                using T = std::variant_alternative_t<N, std::variant<Args...>>;
                auto v = getEmpty<T>();
                visitor["value"] % v;
                self = v;
            } else {
                reflect_impl<N+1>(visitor, self, index);
            }
        }
    }

    static constexpr void reflect(auto& visitor, auto const& self) {
        size_t index = self.index();
        visitor["index"] % index;
        std::visit([&](auto& obj) {
            visitor["value"] % obj;
        }, self);
    }
};

}
