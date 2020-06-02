#define CATCH_CONFIG_MAIN

#include <iostream>
#include <iomanip>

#include "./Catch2-master/single_include/catch2/catch.hpp"

#include "object.h"
#include "graph.h"
#include "others.hpp"
#include "exceptions.h"

TEST_CASE("test Plain class", "[Plain]") {

    Plain p2([](double x, double y){ return x + y;});
    Plain p1([](double x, double y) { return x * y + y + 3; });

        //test characteristic function : Plain
        std::cout << "p2 :\n" << p2;

        SECTION("applying characteristic function of Plain objects") {
            REQUIRE(p2.apply({1, 1}) == 2);
            REQUIRE(p2.apply({2, 6}) == 8);
            REQUIRE(p2.apply({13, 2.5}) == 15.5);

            REQUIRE(p1.apply({1, 1}) == 5);
            REQUIRE(p1.apply({0.5, 2}) == 6);
            REQUIRE(p1.apply({100, 0}) == 3);
        }


        SECTION("check volume calculation") {
            REQUIRE(std::abs(p2.volume() - 1) < 0.01);
            REQUIRE(std::abs(p1.volume() - 3.75) < 0.01);
        }
    }


TEST_CASE("test Rotating class", "[Rotating]"){
    Rotating r1([](double x) { return x * x; });
    Rotating r2([](double x) { return 2 * x + 1; }, 1, 2);


    //test characteristic function : Rotating

    std::cout << "\nr1 :\n" << r1;

    SECTION("applying characteristic function of Rotating objects") {
        REQUIRE(r1.apply({1}) == 1);
        REQUIRE(r1.apply({0.5}) == 0.25);
        REQUIRE(r1.apply({12.5}) == 156.25);


        std::cout << "\nr2 :\n" << r2;

        REQUIRE(r2.apply({1}) == 3);
        REQUIRE(r2.apply({1.5}) == 4);
        REQUIRE(r2.apply({6.1}) == 13.2);
    }

    //test volume calculation : Rotating
    SECTION("check volume calculation") {
        REQUIRE(std::abs(r1.volume() - 0.62) < 0.01);
        REQUIRE(std::abs(r2.volume() - 51.31) < 0.01);
    }
}


TEST_CASE("testing graph with Plain and Rotating objects", "[graph-objects]"){

    SECTION("test adding nodes and edges to graph") {
        //test creating a graph
        Plain p2([](double x, double y){ return x + y;});
        Plain p1([](double x, double y) { return x * y + y + 3; });
        Rotating r1([](double x) { return x * x; });
        Rotating r2([](double x) { return 2 * x + 1; }, 1, 2);
        Graph<Shape *> g;

        g.add_vertex(&p1);
        g.add_vertex(&p2);
        g.add_vertex(&r1);
        g.add_vertex(&r1);
        g.add_vertex(&p1);

        REQUIRE(g.size() == 5);


        //test adding an edge
        g.add_edge(1, 2, 5);
        g.add_edge(0, 2, 3);
        g.add_edge(1, 3, 2);
        g.add_edge(0, 3, 10);


        REQUIRE(g.matrix()[0][1] == 0);
        REQUIRE(g.matrix()[0][2] == 3);
        REQUIRE(g.matrix()[1][3] == 2);
    }

    SECTION("test connectivity check function") {

        Plain p2([](double x, double y){ return x + y;});
        Plain p1([](double x, double y) { return x * y + y + 3; });
        Rotating r1([](double x) { return x * x; });
        Rotating r2([](double x) { return 2 * x + 1; }, 1, 2);
        Graph<Shape *> g;

        g.add_vertex(&p1);
        g.add_vertex(&p2);
        g.add_vertex(&r1);
        g.add_vertex(&r1);
        g.add_vertex(&p1);

        g.add_edge(1, 2, 5);
        g.add_edge(0, 2, 3);
        g.add_edge(1, 3, 2);
        g.add_edge(0, 3, 10);

        //test connected function
        try {
            Graph<Shape *> g1 = g.build_min_tree(); //throws ConnectedError if g1 is not connected
            REQUIRE(0);
        } catch (ConnectedError &err) {}

        g.add_edge(4, 2, 6);
        g.add_edge(1, 4);

        std::cout << "\nGraph g:\n";
        print_data(g);
        std::cout
                << "\n\n/------------------------------------------------------------------------------------------/\n\n";

        /* Matrix:
         * | 0 0 3 0 0 |
         * | 0 0 5 2 1 |
         * | 3 5 0 0 6 |
         * | 0 2 0 0 0 |
         * | 0 1 6 0 0 |
         * */


        REQUIRE(g.connected());
    }


    SECTION("test building spanning tree function") {

        Plain p2([](double x, double y){ return x + y;});
        Plain p1([](double x, double y) { return x * y + y + 3; });
        Rotating r1([](double x) { return x * x; });
        Rotating r2([](double x) { return 2 * x + 1; }, 1, 2);
        Graph<Shape *> g;

        g.add_vertex(&p1);
        g.add_vertex(&p2);
        g.add_vertex(&r1);
        g.add_vertex(&r1);
        g.add_vertex(&p1);

        g.add_edge(1, 2, 5);
        g.add_edge(0, 2, 3);
        g.add_edge(1, 3, 2);
        g.add_edge(0, 3, 10);
        g.add_edge(4, 2, 6);
        g.add_edge(1, 4);


        Graph<Shape *> g1 = g.build_min_tree();

        std::cout << "\nGraph g1 (min tree of g):\n";
        print_data(g1);
        std::cout
                << "\n\n/------------------------------------------------------------------------------------------/\n\n";

        REQUIRE(g1.matrix()[0][3] == 0);
        REQUIRE(g1.matrix()[2][4] == 0);
        REQUIRE(g1.matrix()[1][2] == 5);
    }


    //test delete functions
    SECTION("test delete functions") {


        Plain p2([](double x, double y){ return x + y;});
        Plain p1([](double x, double y) { return x * y + y + 3; });
        Rotating r1([](double x) { return x * x; });
        Rotating r2([](double x) { return 2 * x + 1; }, 1, 2);
        Graph<Shape *> g;

        g.add_vertex(&p1);
        g.add_vertex(&p2);
        g.add_vertex(&r1);
        g.add_vertex(&r1);
        g.add_vertex(&p1);

        g.add_edge(1, 2, 5);
        g.add_edge(0, 2, 3);
        g.add_edge(1, 3, 2);
        g.add_edge(0, 3, 10);
        g.add_edge(4, 2, 6);
        g.add_edge(1, 4);

        Graph<Shape *> g1 = g.build_min_tree();

        REQUIRE(g1.matrix()[1][2] == 5);
        g1.remove_edge(1, 2);
        REQUIRE(g1.matrix()[1][2] == 0);

        REQUIRE(g.matrix()[0][3] == 10);
        g.remove_edge(3, 0);
        REQUIRE(g.matrix()[0][3] == 0);

        std::cout << "\nGraph g1 after removal of edges (1,2) and (0,3) :\n";
        print_data(g1);
        std::cout
                << "\n\n/------------------------------------------------------------------------------------------/\n\n";

        g.remove_vertex(2);
        REQUIRE(g.matrix().size() == 4);
        REQUIRE(g.matrix()[0].size() == 4);
        REQUIRE(g.data().size() == 4);


        /* Matrix:
         * | 0 0 0 0 |
         * | 0 0 2 1 |
         * | 0 2 0 0 |
         * | 0 1 0 0 |
         * */

        std::cout << "\nGraph g after removal of vertex 2 :\n";
        print_data(g);
        std::cout
                << "\n\n/------------------------------------------------------------------------------------------/\n\n";

        //check the edges, that remained after removal
        REQUIRE(g.matrix()[1][2] == 2);
        REQUIRE(g.matrix()[3][1] == 1);
    }
}


TEST_CASE("testing graph with vectors and ints objects", "[graph]") {
    //Check graph with vectors and integers
    std::vector<int> v1 = random_vector(5, 0, 25);
    std::vector<int> v2 = random_vector(10, 4, 80);
    std::vector<int> v3 = random_vector(2, 0, 2);

    Graph<std::vector<int>> vec_graph;
    vec_graph.add_vertex(v1);
    vec_graph.add_vertex(v2, {std::make_pair(0, 4)});
    vec_graph.add_vertex(v3, {std::make_pair(0, 2), std::make_pair(1, 8)});

    std::cout << "\nGraph of vectors :\n" << vec_graph;

    SECTION("checking adding functions") {
        REQUIRE(vec_graph[0] == v1);
        REQUIRE(vec_graph[1] == v2);
        REQUIRE(vec_graph[2] == v3);
        REQUIRE(vec_graph.matrix()[0][2] == 2);
        REQUIRE(vec_graph.matrix()[0][1] == 4);
        REQUIRE(vec_graph.matrix()[1][2] == 8);
    }


    Graph<int> int_graph;
    for (int i = 0; i < 10; ++i) {
        int_graph.add_vertex(i * 5);
    }

    std::cout << "\nGraph of integers :\n" << int_graph;

    SECTION("checking content") {
        REQUIRE(int_graph.data() == std::vector({0, 5, 10, 15, 20, 25, 30, 35, 40, 45}));
    }
}