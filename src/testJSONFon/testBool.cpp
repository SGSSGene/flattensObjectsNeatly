// SPDX-FileCopyrightText: 2024 Simon Gene Gottlieb
// SPDX-License-Identifier: CC0-1.0
#include <catch2/catch_all.hpp>
#include <fon/json.h>

TEST_CASE("test json serialization of bool", "[json][bool][serialize]") {
    SECTION ("testing 'true'") {
        bool data {true};
        auto node = fon::json::serialize(data);
        REQUIRE(node.isBool());
        REQUIRE(node.asBool() == true);
    }

    SECTION ("testing 'false'") {
        bool data {false};
        auto node = fon::json::serialize(data);
        REQUIRE(node.isBool());
        REQUIRE(node.asBool() == false);
    }
}

TEST_CASE("test json deserialization of bool", "[json][bool][deserialize]") {
    SECTION ("testing 'true'") {
        Json::Value node;
        node = true;
        auto data = fon::json::deserialize<bool>(node);
        REQUIRE(data == true);
    }

    SECTION ("testing 'false'") {
        Json::Value node;
        node = false;
        auto data = fon::json::deserialize<bool>(node);
        REQUIRE(data == false);
    }
}
