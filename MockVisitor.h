#pragma once

namespace fon {

struct MockVisitor {
    template <typename Key>
    auto operator[](Key key) const -> MockVisitor {
        return *this;
    }
    template <typename V>
    auto operator%(V&& v) const {
    }
    template <typename V>
    auto operator()(V&) const {
    }
};

}
