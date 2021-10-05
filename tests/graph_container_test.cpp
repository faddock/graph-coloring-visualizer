#include <catch2/catch.hpp>
#include <graph_container.h>
#include <iostream>

using graph_color::GraphContainer;
using graph_color::Node;

TEST_CASE("Preliminary Tests") {
    GraphContainer graph = GraphContainer(vec2(100, 100), vec2(500, 500));
    std::cout << "Chromatic number:" << graph.ColorGraph();
    //graph_color.Display();
    REQUIRE(1 == 1);

}
TEST_CASE("Preliminary Tests 2") {
    GraphContainer graph = GraphContainer(vec2(100, 100), vec2(500, 500));
    graph.LoadAdjMatrix();
    std::ofstream file(R"(D:\Cinder\my-projects\final-project-faddock\data\graph_data_output.txt)");
    file << graph;
}

TEST_CASE("Load data test") {
    GraphContainer graph = GraphContainer(vec2(100, 100), vec2(500, 500));
    std::ifstream load_file("D:\\Cinder\\my-projects\\final-project-faddock\\data\\graph_data_input.txt");
    load_file >> graph;
}

