#g++ -std=c++20 src/example/main.cpp -O0 -ggdb -lyaml-cpp -lfmt src/demangle/demangle.cpp -isystem src -o example

g++ -std=c++20 src/testYAMLFon/*.cpp -O0 -ggdb -lyaml-cpp -lfmt src/demangle/demangle.cpp src/catch/catch.cpp -isystem src -o testYAMLFon
g++ -std=c++20 src/testBinaryFon/*.cpp -O0 -ggdb -lyaml-cpp -lfmt src/demangle/demangle.cpp src/catch/catch.cpp -isystem src -o testBinaryFon
