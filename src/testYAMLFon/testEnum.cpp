// SPDX-FileCopyrightText: 2024 Simon Gene Gottlieb
// SPDX-License-Identifier: CC0-1.0
#include <catch2/catch_all.hpp>
#include <fon/yaml.h>
#include <fon/std/all.h>

namespace {
enum class MyEnum : int32_t {
    E1,
    E2,
    E3
};

auto asString(YAML::Node node) -> std::string {
    YAML::Emitter emit;
    emit << node;
    return emit.c_str();
}
}


TEST_CASE("test yaml serialization of enum", "[yaml][enum][serialize]") {
    SECTION("E1") {
        auto data = MyEnum::E1;
        auto node = fon::yaml::serialize(data);
        INFO(asString(node));
        REQUIRE(node.IsScalar());
        REQUIRE(node.as<int32_t>() == int32_t(MyEnum::E1));
    }
    SECTION("E2") {
        auto data = MyEnum::E2;
        auto node = fon::yaml::serialize(data);
        REQUIRE(node.IsScalar());
        REQUIRE(node.as<int32_t>() == int32_t(MyEnum::E2));
    }
    SECTION("E3") {
        auto data = MyEnum::E3;
        auto node = fon::yaml::serialize(data);
        REQUIRE(node.IsScalar());
        REQUIRE(node.as<int32_t>() == int32_t(MyEnum::E3));
    }
}
TEST_CASE("test yaml deserialization of enum", "[yaml][enum][deserialize]") {
    SECTION("E1") {
        YAML::Node node;
        node = int(MyEnum::E1);
        auto data = fon::yaml::deserialize<MyEnum>(node);
        REQUIRE(data == MyEnum::E1);
    }
    SECTION("E2") {
        YAML::Node node;
        node = int(MyEnum::E2);
        auto data = fon::yaml::deserialize<MyEnum>(node);
        REQUIRE(data == MyEnum::E2);
    }
    SECTION("E3") {
        YAML::Node node;
        node = int(MyEnum::E3);
        auto data = fon::yaml::deserialize<MyEnum>(node);
        REQUIRE(data == MyEnum::E3);
    }
}
