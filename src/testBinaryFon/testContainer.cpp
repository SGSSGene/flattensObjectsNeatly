#include <catch/catch.hpp>
#include <fon/binary.h>
#include <fon/std/all.h>

TEST_CASE("test binary serialization of std::string", "[yaml][std][string][serialize]") {
    auto data = std::string{"hallo welt"};
    auto buffer = fon::binary::serialize(data);

    auto expected = std::vector<std::byte>{
        std::byte{0x0a}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00}, // string size
        std::byte{0x00}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00},
        std::byte{'h'},  std::byte{'a'},  std::byte{'l'},  std::byte{'l'}, // actual string
        std::byte{'o'},  std::byte{' '},  std::byte{'w'},  std::byte{'e'},
        std::byte{'l'},  std::byte{'t'},
    };

    REQUIRE(buffer.size() == expected.size());
    CHECK(buffer == expected);
}

TEST_CASE("test binary deserialization of std::string", "[yaml][std][string][deserialize]") {
    auto input = std::vector<std::byte>{
        std::byte{0x0a}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00}, // string size
        std::byte{0x00}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00},
        std::byte{'h'},  std::byte{'a'},  std::byte{'l'},  std::byte{'l'}, // actual string
        std::byte{'o'},  std::byte{' '},  std::byte{'w'},  std::byte{'e'},
        std::byte{'l'},  std::byte{'t'},
    };

    auto data = fon::binary::deserialize<std::string>(input);
    REQUIRE(data == std::string{"hallo welt"});
}

/*TEST_CASE("test binary serialization of std::vector", "[yaml][std][vector][serialize]") {
    auto data = std::vector<int32_t>{10, 20, 30};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsSequence());
    REQUIRE(node.size() == 3);
    REQUIRE(node[0].as<int32_t>() == 10);
    REQUIRE(node[1].as<int32_t>() == 20);
    REQUIRE(node[2].as<int32_t>() == 30);
}

TEST_CASE("test binary deserialization of std::vector", "[yaml][std][vector][deserialize]") {
    binary::Node node;
    node[0] = 10;
    node[1] = 20;
    node[2] = 30;
    auto data = fon::binary::deserialize<std::vector<int32_t>>(node);
    REQUIRE(data == (std::vector<int32_t>{10, 20, 30}));
}
TEST_CASE("test binary serialization of std::vector with strings", "[yaml][std][vector][string][serialize]") {
    auto data = std::vector<std::string>{"hallo", "welt", "!"};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsSequence());
    REQUIRE(node.size() == 3);
    REQUIRE(node[0].as<std::string>() == "hallo");
    REQUIRE(node[1].as<std::string>() == "welt");
    REQUIRE(node[2].as<std::string>() == "!");
}

TEST_CASE("test binary deserialization of std::vector with strings", "[yaml][std][vector][deserialize]") {
    binary::Node node;
    node[0] = "hallo";
    node[1] = "welt";
    node[2] = "!";
    auto data = fon::binary::deserialize<std::vector<std::string>>(node);
    REQUIRE(data == (std::vector<std::string>{"hallo", "welt", "!"}));
}


TEST_CASE("test binary serialization of std::array", "[yaml][std][array][serialize]") {
    auto data = std::array<int32_t, 3>{10, 20, 30};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsSequence());
    REQUIRE(node.size() == 3);
    REQUIRE(node[0].as<int32_t>() == 10);
    REQUIRE(node[1].as<int32_t>() == 20);
    REQUIRE(node[2].as<int32_t>() == 30);
}

TEST_CASE("test binary deserialization of std::array", "[yaml][std][array][deserialize]") {
    binary::Node node;
    node[0] = 10;
    node[1] = 20;
    node[2] = 30;
    auto data = fon::binary::deserialize<std::array<int32_t, 3>>(node);
    REQUIRE(data == (std::array<int32_t, 3>{10, 20, 30}));
}

TEST_CASE("test binary serialization of std::list", "[yaml][std][list][serialize]") {
    auto data = std::list<int32_t>{10, 20, 30};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsSequence());
    REQUIRE(node.size() == 3);
    REQUIRE(node[0].as<int32_t>() == 10);
    REQUIRE(node[1].as<int32_t>() == 20);
    REQUIRE(node[2].as<int32_t>() == 30);
}
TEST_CASE("test binary deserialization of std::list", "[yaml][std][list][deserialize]") {
    binary::Node node;
    node[0] = 10;
    node[1] = 20;
    node[2] = 30;
    auto data = fon::binary::deserialize<std::list<int32_t>>(node);
    REQUIRE(data == (std::list<int32_t>{10, 20, 30}));
}
TEST_CASE("test binary serialization of std::forward_list", "[yaml][std][forward_list][serialize]") {
    auto data = std::forward_list<int32_t>{10, 20, 30};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsSequence());
    REQUIRE(node.size() == 3);
    REQUIRE(node[0].as<int32_t>() == 10);
    REQUIRE(node[1].as<int32_t>() == 20);
    REQUIRE(node[2].as<int32_t>() == 30);
}
TEST_CASE("test binary deserialization of std::forward_list", "[yaml][std][forward_list][deserialize]") {
    binary::Node node;
    node[0] = 10;
    node[1] = 20;
    node[2] = 30;
    auto data = fon::binary::deserialize<std::forward_list<int32_t>>(node);
    REQUIRE(data == (std::forward_list<int32_t>{10, 20, 30}));
}
TEST_CASE("test binary serialization of std::deque", "[yaml][std][deque][serialize]") {
    auto data = std::deque<int32_t>{10, 20, 30};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsSequence());
    REQUIRE(node.size() == 3);
    REQUIRE(node[0].as<int32_t>() == 10);
    REQUIRE(node[1].as<int32_t>() == 20);
    REQUIRE(node[2].as<int32_t>() == 30);
}
TEST_CASE("test binary deserialization of std::deque", "[yaml][std][deque][deserialize]") {
    binary::Node node;
    node[0] = 10;
    node[1] = 20;
    node[2] = 30;
    auto data = fon::binary::deserialize<std::deque<int32_t>>(node);
    REQUIRE(data == (std::deque<int32_t>{10, 20, 30}));
}

TEST_CASE("test binary serialization of std::set", "[yaml][std][set][serialize]") {
    auto data = std::set<int32_t>{10, 20, 30};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsSequence());
    REQUIRE(node.size() == 3);
    REQUIRE(node[0].as<int32_t>() == 10);
    REQUIRE(node[1].as<int32_t>() == 20);
    REQUIRE(node[2].as<int32_t>() == 30);
}
TEST_CASE("test binary deserialization of std::set", "[yaml][std][set][deserialize]") {
    binary::Node node;
    node[0] = 10;
    node[1] = 20;
    node[2] = 30;
    auto data = fon::binary::deserialize<std::set<int32_t>>(node);
    REQUIRE(data == (std::set<int32_t>{10, 20, 30}));
}
TEST_CASE("test binary serialization of std::unordered_set", "[yaml][std][unordered_set][serialize]") {
    auto data = std::unordered_set<int32_t>{10, 20, 30};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsSequence());
    REQUIRE(node.size() == 3);
    REQUIRE((std::set<int32_t>{node[0].as<int32_t>(), node[1].as<int32_t>(), node[2].as<int32_t>()}) == (std::set<int32_t>{10, 20, 30}));
}
TEST_CASE("test binary deserialization of std::unordered_set", "[yaml][std][unordered_set][deserialize]") {
    binary::Node node;
    node[0] = 10;
    node[1] = 20;
    node[2] = 30;
    auto data = fon::binary::deserialize<std::unordered_set<int32_t>>(node);
    REQUIRE(data.size() == 3);
    REQUIRE(data.count(10) == 1);
    REQUIRE(data.count(20) == 1);
    REQUIRE(data.count(30) == 1);
}

TEST_CASE("test binary serialization of std::map", "[yaml][std][map][serialize]") {
    auto data = std::map<std::string, int32_t>{{"k1", 10}, {"k2", 20}, {"k3", 30}};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsMap());
    REQUIRE(node.size() == 3);
    REQUIRE(node["k1"].as<int32_t>() == 10);
    REQUIRE(node["k2"].as<int32_t>() == 20);
    REQUIRE(node["k3"].as<int32_t>() == 30);
}
TEST_CASE("test binary deserialization of std::map", "[yaml][std][map][deserialize]") {
    binary::Node node;
    node["k1"] = 10;
    node["k2"] = 20;
    node["k3"] = 30;
    auto data = fon::binary::deserialize<std::map<std::string, int32_t>>(node);
    REQUIRE(data == (std::map<std::string, int32_t>{{"k1", 10}, {"k2", 20}, {"k3", 30}}));
}

TEST_CASE("test binary serialization of std::unordered_map", "[yaml][std][unordered_map][serialize]") {
    auto data = std::unordered_map<std::string, int32_t>{{"k1", 10}, {"k2", 20}, {"k3", 30}};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsMap());
    REQUIRE(node.size() == 3);
    REQUIRE(node["k1"].as<int32_t>() == 10);
    REQUIRE(node["k2"].as<int32_t>() == 20);
    REQUIRE(node["k3"].as<int32_t>() == 30);
}
TEST_CASE("test binary deserialization of std::unordered_map", "[yaml][std][unordered_map][deserialize]") {
    binary::Node node;
    node["k1"] = 10;
    node["k2"] = 20;
    node["k3"] = 30;
    auto data = fon::binary::deserialize<std::unordered_map<std::string, int32_t>>(node);
    REQUIRE(data == (std::unordered_map<std::string, int32_t>{{"k1", 10}, {"k2", 20}, {"k3", 30}}));
}
TEST_CASE("test binary serialization of std::pair", "[yaml][std][pair][serialize]") {
    auto data = std::pair<std::string, int32_t>{"hallo welt", 42};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsMap());
    REQUIRE(node.size() == 2);
    REQUIRE(node[0].as<std::string>() == "hallo welt");
    REQUIRE(node[1].as<int32_t>() == 42);
}
TEST_CASE("test binary deserialization of std::pair", "[yaml][std][pair][deserialize]") {
    binary::Node node;
    node[0] = "hallo welt";
    node[1] = 42;
    auto data = fon::binary::deserialize<std::pair<std::string, int32_t>>(node);
    REQUIRE(data.first == "hallo welt");
    REQUIRE(data.second == 42);
}
TEST_CASE("test binary serialization of std::tuple<>", "[yaml][std][tuple][serialize]") {
    auto data = std::tuple<>{};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.size() == 0);
}
TEST_CASE("test binary deserialization of std::tuple<>", "[yaml][std][tuple][deserialize]") {
    binary::Node node;
    auto data = fon::binary::deserialize<std::tuple<>>(node);
    (void)data;
}

TEST_CASE("test binary serialization of std::tuple<X>", "[yaml][std][tuple][serialize]") {
    auto data = std::tuple<std::string> {"hallo welt"};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsMap());
    REQUIRE(node.size() == 1);
    REQUIRE(node[0].as<std::string>() == "hallo welt");
}
TEST_CASE("test binary deserialization of std::tuple<X>", "[yaml][std][tuple][deserialize]") {
    binary::Node node;
    node[0] = "hallo welt";
    auto data = fon::binary::deserialize<std::tuple<std::string>>(node);
    REQUIRE(std::get<0>(data) == "hallo welt");
}


TEST_CASE("test binary serialization of std::tuple<X, Y>", "[yaml][std][tuple][serialize]") {
    auto data = std::tuple<std::string, int32_t>{"hallo welt", 42};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsMap());
    REQUIRE(node.size() == 2);
    REQUIRE(node[0].as<std::string>() == "hallo welt");
    REQUIRE(node[1].as<int32_t>() == 42);
}
TEST_CASE("test binary deserialization of std::tuple<X, Y>", "[yaml][std][tuple][deserialize]") {
    binary::Node node;
    node[0] = "hallo welt";
    node[1] = 42;
    auto data = fon::binary::deserialize<std::tuple<std::string, int32_t>>(node);
    REQUIRE(std::get<0>(data) == "hallo welt");
    REQUIRE(std::get<1>(data) == 42);
}
TEST_CASE("test binary serialization of std::optional", "[yaml][std][optional][serialize]") {
    auto data = std::optional<std::string>{"hallo welt"};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.IsSequence());
    REQUIRE(node.size() == 1);
    REQUIRE(node[0].IsScalar());
    REQUIRE(node[0].as<std::string>() == "hallo welt");
}

TEST_CASE("test binary deserialization of std::optional", "[yaml][std][optional][deserialize]") {
    binary::Node node;
    node[0] = "hallo welt";
    auto data = fon::binary::deserialize<std::optional<std::string>>(node);
    REQUIRE(data.has_value());
    REQUIRE(data.value() == "hallo welt");
}

TEST_CASE("test binary serialization of empty std::optional", "[yaml][std][optional][serialize]") {
    auto data = std::optional<std::string>{};
    auto node = fon::binary::serialize(data);
    REQUIRE(node.size() == 0);
}
TEST_CASE("test binary deserialization of empty std::optional", "[yaml][std][optional][deserialize]") {
    binary::Node node;
    auto data = fon::binary::deserialize<std::optional<std::string>>(node);
    REQUIRE(not data.has_value());
}

TEST_CASE("test binary serialization of std::variant (index 0)", "[yaml][std][variant][serialize]") {
    auto data = std::variant<std::string, int32_t, bool>{std::string{"hallo welt"}};
    auto node = fon::binary::serialize(data);

    REQUIRE(node.IsMap());
    REQUIRE(node.size() == 2);

    REQUIRE(node["index"].IsScalar());
    REQUIRE(node["index"].as<size_t>() == 0);
    REQUIRE(node["value"].as<std::string>() == "hallo welt");
}
TEST_CASE("test binary deserialization of std::variant (index 0)", "[yaml][std][variant][deserialize]") {
    binary::Node node {YAML::NodeType::Map};
    node["index"] = 0;
    node["value"] = "hallo welt";
    auto data = fon::binary::deserialize<std::variant<std::string, int32_t, bool>>(node);
    REQUIRE(data.index() == 0);
    REQUIRE(std::get<0>(data) == "hallo welt");
}

TEST_CASE("test binary serialization of std::variant (index 1)", "[yaml][std][variant][serialize]") {
    auto data = std::variant<std::string, int32_t, bool>{int32_t{42}};
    auto node = fon::binary::serialize(data);

    REQUIRE(node.IsMap());
    REQUIRE(node.size() == 2);

    REQUIRE(node["index"].as<size_t>() == 1);
    REQUIRE(node["value"].as<int32_t>() == 42);
}
TEST_CASE("test binary deserialization of std::variant (index 1)", "[yaml][std][variant][deserialize]") {
    binary::Node node {YAML::NodeType::Map};
    node["index"] = 1;
    node["value"] = 42;
    auto data = fon::binary::deserialize<std::variant<std::string, int32_t, bool>>(node);
    REQUIRE(data.index() == 1);
    REQUIRE(std::get<1>(data) == 42);
}

TEST_CASE("test binary serialization of std::variant (index 2)", "[yaml][std][variant][serialize]") {
    auto data = std::variant<std::string, int32_t, bool>{true};
    auto node = fon::binary::serialize(data);

    REQUIRE(node.IsMap());
    REQUIRE(node.size() == 2);

    REQUIRE(node["index"].as<size_t>() == 2);
    REQUIRE(node["value"].as<bool>() == true);
}
TEST_CASE("test binary deserialization of std::variant (index 2)", "[yaml][std][variant][deserialize]") {
    binary::Node node {YAML::NodeType::Map};
    node["index"] = 2;
    node["value"] = true;
    auto data = fon::binary::deserialize<std::variant<std::string, int32_t, bool>>(node);
    REQUIRE(data.index() == 2);
    REQUIRE(std::get<2>(data) == true);
}

TEST_CASE("test binary serialization of std::filesystem::path", "[yaml][std][filesystem][path][serialize]") {
    auto data = std::filesystem::path{"./myfile.txt"};
    auto node = fon::binary::serialize(data);

    REQUIRE(node.IsScalar());
    REQUIRE(node.as<std::string>() == "./myfile.txt");
}

TEST_CASE("test binary deserialization of std::filesystem::path", "[yaml][std][filesystem][path][deserialize]") {
    binary::Node node;
    node = "./some_file";
    auto data = fon::binary::deserialize<std::filesystem::path>(node);

    REQUIRE(data == "./some_file");
}

TEST_CASE("test binary serialization of std::set<std::filesystem::path>", "[yaml][std][filesystem][set][path][serialize]") {
    auto data = std::set<std::filesystem::path>{{"./myfile.txt"}};

    auto node = fon::binary::serialize(data);

    REQUIRE(node.IsSequence());
    REQUIRE(node[0].IsScalar());
    REQUIRE(node[0].as<std::string>() == "./myfile.txt");
}

TEST_CASE("test binary deserialization of std::set<std::filesystem::path>", "[yaml][std][filesystem][set][path][deserialize]") {
    binary::Node node;
    node[0] = "./some_file";
    auto data = fon::binary::deserialize<std::set<std::filesystem::path>>(node);

    REQUIRE(data.size() == 1);
    REQUIRE(*data.begin() == "./some_file");
}

TEST_CASE("test binary serialization of std::chrono::time_point<ms>", "[yaml][std][chrono][time_point][serialize]") {
    auto data = std::chrono::time_point<std::chrono::milliseconds>(std::chrono::milliseconds{42});
    auto node = fon::binary::serialize(data);

    REQUIRE(node.IsScalar());
    REQUIRE(node.as<int>() == 42);
}

TEST_CASE("test binary deserialization of std::chrono::time_point<ms>", "[yaml][std][chrono][time_point][deserialize]") {
    binary::Node node;
    node = 42;
    auto data = fon::binary::deserialize<std::chrono::time_point<std::chrono::milliseconds>>(node);
    REQUIRE(data == std::chrono::time_point<std::chrono::milliseconds>(std::chrono::milliseconds{42}));
}

TEST_CASE("test binary serialization of std::chrono::time_point<ns>", "[yaml][std][chrono][time_point][serialize]") {
    auto data = std::chrono::time_point<std::chrono::nanoseconds>(std::chrono::nanoseconds{42});
    auto node = fon::binary::serialize(data);

    REQUIRE(node.IsScalar());
    REQUIRE(node.as<int>() == 42);
}

TEST_CASE("test binary deserialization of std::chrono::time_point<ns>", "[yaml][std][chrono][time_point][deserialize]") {
    binary::Node node;
    node = 42;
    auto data = fon::binary::deserialize<std::chrono::time_point<std::chrono::nanoseconds>>(node);
    REQUIRE(data == std::chrono::time_point<std::chrono::nanoseconds>(std::chrono::nanoseconds{42}));
}

TEST_CASE("test binary serialization of std::filesystem::file_time_type", "[yaml][std][chrono][time_point][serialize]") {
    auto data = std::filesystem::file_time_type(std::chrono::nanoseconds{42});
    auto node = fon::binary::serialize(data);

    REQUIRE(node.IsScalar());
    REQUIRE(node.as<int>() == 42);
}

TEST_CASE("test binary deserialization of std::filesystem::file_time_type", "[yaml][std][chrono][time_point][deserialize]") {
    binary::Node node;
    node = 42;
    auto data = fon::binary::deserialize<std::filesystem::file_time_type>(node);
    REQUIRE(data == std::filesystem::file_time_type(std::chrono::nanoseconds{42}));
}

TEST_CASE("test binary serialization of std::chrono::duration", "[yaml][std][chrono][duration][serialize]") {
    using namespace std::chrono_literals;
    auto data = 42ms - 20ms;
    auto node = fon::binary::serialize(data);

    REQUIRE(node.IsScalar());
    REQUIRE(node.as<int>() == 22);
}

TEST_CASE("test binary deserialization of std::chrono::duration", "[yaml][std][chrono][duration][deserialize]") {
    using namespace std::chrono_literals;

    binary::Node node;
    node = 22;
    using duration = decltype(42ms - 20ms);
    auto data = fon::binary::deserialize<duration>(node);
    REQUIRE(data == (42ms - 20ms));
}*/
