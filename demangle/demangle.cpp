#include "demangle.h"

#include <cxxabi.h>
#include <stdexcept>

auto demangle(std::type_info const& ti) -> std::string {
    int status;
    char* name_ = abi::__cxa_demangle(ti.name(), 0, 0, &status);
    if (status) {
        return ti.name();
    }
    auto demangledName = std::string{name_};
    free(name_); // need to use free here :/
    return demangledName;
}
