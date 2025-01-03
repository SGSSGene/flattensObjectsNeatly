// SPDX-FileCopyrightText: 2024 Simon Gene Gottlieb
// SPDX-License-Identifier: CC0-1.0
#include <catch2/catch_all.hpp>
#include <fon/yaml.h>

TEST_CASE("test yaml serialization of bool", "[yaml][bool][serialize]") {
    SECTION ("testing 'true'") {
        bool data {true};
        auto node = fon::yaml::serialize(data);
        REQUIRE(node.IsScalar());
        REQUIRE(node.as<bool>() == true);
    }

    SECTION ("testing 'false'") {
        bool data {false};
        auto node = fon::yaml::serialize(data);
        REQUIRE(node.IsScalar());
        REQUIRE(node.as<bool>() == false);
    }
}

TEST_CASE("test yaml deserialization of bool", "[yaml][bool][deserialize]") {
    SECTION ("testing 'true'") {
        YAML::Node node;
        node = true;
        auto data = fon::yaml::deserialize<bool>(node);
        REQUIRE(data == true);
    }

    SECTION ("testing 'false'") {
        YAML::Node node;
        node = false;
        auto data = fon::yaml::deserialize<bool>(node);
        REQUIRE(data == false);
    }
}
