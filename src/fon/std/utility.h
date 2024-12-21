// SPDX-FileCopyrightText: 2024 Simon Gene Gottlieb
// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

#include "../proxy.h"

#include <utility>

namespace fon {

template <typename T1, typename T2>
struct proxy<std::pair<T1, T2>> {
    static constexpr void reflect(auto& visitor, auto& self) {
        visitor[0] % self.first;
        visitor[1] % self.second;
    }
};

}
