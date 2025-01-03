// SPDX-FileCopyrightText: 2024 Simon Gene Gottlieb
// SPDX-License-Identifier: CC0-1.0
#include <catch2/catch_all.hpp>

#include <fon/yaml.h>
#include <fon/std/all.h>

namespace {

struct B {
    YAML::Node node;

    constexpr static void reflect(auto& visitor, auto& self) {
        visitor["node"] % self.node;
    }
};

TEST_CASE("test yaml serialization of YAML::Node", "[yaml][serialize][yaml-cpp]") {
    auto data = B{};
    data.node["foo"] = "bar";

    auto node = fon::yaml::serialize(data);

    REQUIRE(node.IsMap());
    REQUIRE(node["node"].IsMap());
    CHECK(node["node"]["foo"].as<std::string>() == "bar");
}

TEST_CASE("test yaml deserialization of YAML::Node", "[yaml][deserialize][yaml-cpp]") {
    YAML::Node node;
    node["node"]["foo"] = "bar";

    auto data = fon::yaml::deserialize<B>(node);
    REQUIRE(data.node.IsMap());
    CHECK(data.node["foo"].as<std::string>() == "bar");
}

TEST_CASE("test yaml deserialization of YAML::Node inside tuples", "[yaml][deserialize][yaml-cpp][tuple]") {
    YAML::Node node;
    node.push_back("bar");
    node.push_back("blub");

    auto data = fon::yaml::deserialize<std::tuple<YAML::Node>>(node);
    REQUIRE(std::get<0>(data).IsScalar());
    CHECK(std::get<0>(data).as<std::string>() == "bar");
}


}
