// SPDX-FileCopyrightText: 2024 Simon Gene Gottlieb
// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

#include "../proxy.h"

#include <filesystem>
#include <string>

namespace fon {

template <>
struct proxy<std::filesystem::path> {
    static void reflect(auto& visitor, auto& self) {
        std::string str;
        visitor % str;
        self = str;
    }

    static void reflect(auto& visitor, auto const& self) {
        std::string str = self;
        visitor % str;
    }
};

}
