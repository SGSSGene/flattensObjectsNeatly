#pragma once

#include <filesystem>
#include <string>

#include "proxy.h"

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
