#pragma once

namespace fon {

namespace detail {
struct FakeLambda {
    template <typename ...Args>
    void operator()(Args&&...) {}
};
}

template <typename CB>
struct Visitor {
    CB cb;

    Visitor(CB cb) : cb{cb} {}

    template <typename V>
    void operator%(V const& v) {
        cb(*this, v);
    }
    template <typename V>
    void operator%(V& v) {
        cb(*this, v);
    }
    template <typename V>
    void operator%(V&& v) {
        cb(*this, v);
    }
};

template <typename CB>
Visitor(CB cb) -> Visitor<CB>;

using MockVisitor = Visitor<detail::FakeLambda>;



template <typename CB, typename T>
auto visit(CB cb, T& t) {
    fon::Visitor visitor{cb};
    return visitor % t;
}

}
