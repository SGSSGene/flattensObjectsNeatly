#pragma once

#include "traits.h"

#include "proxy.h"

#include <vector>
#include <map>
#include <iostream>

namespace fon {

template <typename InitCB, typename EachCB>
struct List {
    InitCB initCb;
    EachCB eachCb;
};

template <typename CB1, typename CB2>
List(CB1, CB2) -> List<CB1, CB2>;


template <typename ...Args>
struct list_adapter<List<Args...>> {
    using Data = List<Args...>;
    Data& data;

    list_adapter(Data& data, size_t len)
        : data{data}
    {
        data.initCb(len);
    }

    void visit(auto cb) {
        data.eachCb(cb);
    }
};
template <typename ...Args>
struct list_adapter<List<Args...> const> {
    using Data = List<Args...>;
    Data const& data;
    size_t len;

    list_adapter(Data const& data)
        : data{data}
        , len{data.initCb()}
    {}
    auto size() const {
        return len;
    }

    void visit(auto cb) {
        data.eachCb(cb);
    }

};



template <typename InitCB, typename EachCB>
struct Map {
    InitCB initCb;
    EachCB eachCb;
};

template <typename CB1, typename CB2>
Map(CB1, CB2) -> Map<CB1, CB2>;

template <typename ...Args>
struct map_adapter<Map<Args...>> {
    using Data = Map<Args...>;
    Data& data;

    map_adapter(Data& data, size_t len)
        : data{data}
    {
        data.initCb(len);
    }

    void visit(auto cb) {
        data.eachCb(cb);
    }
};
template <typename ...Args>
struct map_adapter<Map<Args...> const> {
    using Data = Map<Args...>;
    Data const& data;
    size_t len;

    map_adapter(Data const& data)
        : data{data}
        , len{data.initCb()}
    {}
    auto size() const {
        return len;
    }

    void visit(auto cb) {
        data.eachCb(cb);
    }
};


template <typename Data>
    requires (has_reflect_v<MockVisitor, Data>)
struct struct_adapter<Data> {
    Data& data;

    struct_adapter(Data& data)
        : data{data}
    {}

    template <typename Cb, typename Key>
    struct SubVisitor {
        Cb const& cb;
        Key key;
        SubVisitor(Cb const& _cb, Key _key)
            : cb{_cb}
            , key{_key}
        {}

        template <typename T>
        void operator%(T& obj) {
            cb(key, obj);
        }
    };
    template <typename Cb1, typename Cb2>
    struct Visitor {
        Cb1 cb1;
        Cb2 cb2;

        Visitor(Cb1 const& _cb1, Cb2 const& _cb2)
            : cb1{_cb1}
            , cb2{_cb2}
        {};

        template <typename Key>
        auto operator[](Key key) {
            return SubVisitor{cb1, key};
        }
        auto operator[](std::string_view key) {
            return SubVisitor{cb1, key};
        }

        template <typename T>
        void operator%(T& obj) {
            cb2(obj);
        }
    };

    void visit(auto cb) {
        Visitor visitor{[&](auto& key, auto& value) {
            cb(key, value);
        }, [&](auto& value) {
            cb(value);
        }};
        Data::reflect(visitor, data);
    }

};

template <typename Data>
    requires (has_reflect_v<MockVisitor, Data>)
struct struct_adapter<Data const> {
    Data const& data;

    struct_adapter(Data const& data)
        : data{data}
    {}

    auto size() const {
        return 0;
    }

    template <typename Cb, typename Key>
    struct SubVisitor {
        Cb const& cb;
        Key key;
        SubVisitor(Cb const& _cb, Key _key)
            : cb{_cb}
            , key{_key}
        {}

        template <typename T>
        void operator%(T& obj) {
            cb(key, obj);
        }
    };
    template <typename Cb1, typename Cb2>
    struct Visitor {
        Cb1 cb1;
        Cb2 cb2;

        Visitor(Cb1 const& _cb1, Cb2 const& _cb2)
            : cb1{_cb1}
            , cb2{_cb2}
        {};

        template <typename Key>
        auto operator[](Key key) {
            return SubVisitor{cb1, key};
        }
        auto operator[](std::string_view key) {
            return SubVisitor{cb1, key};
        }

        template <typename T>
        void operator%(T& obj) {
            cb2(obj);
        }
    };

    void visit(auto cb) {
        Visitor visitor{[&](auto& key, auto& value) {
            cb(key, value);
        }, [&](auto& value) {
            cb(value);
        }};
        Data::reflect(visitor, data);
    }
};


}
