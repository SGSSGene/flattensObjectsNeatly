#pragma once

#include "MockVisitor.h"
#include "proxy.h"
#include "traits.h"

namespace fon {

template <typename CB>
struct Visitor {
    CB cb;

    Visitor(CB cb) : cb{cb} {}

    template <typename V>
    void operator%(V const& v) const {
        cb(*this, v);
    }
    template <typename V>
    void operator%(V& v) const {
        cb(*this, v);
    }
    template <typename V>
    void operator%(V&& v) const {
        cb(*this, v);
    }
};

template <typename CB, typename T>
auto visit(CB cb, T& t) {
    fon::Visitor visitor{cb};
    return visitor % t;
}

}
