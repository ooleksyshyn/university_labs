#define CATCH_CONFIG_MAIN


#include "structures.h"
#include "point.hpp"


#include "./Catch2-master/single_include/catch2/catch.hpp"


#include <iostream>
#include <sstream>


TEST_CASE("test class Point", "[point]"){
    Point p;

    SECTION("test default constructor"){
        REQUIRE(p.X == 0);
        REQUIRE(p.Y == 0);
        REQUIRE(p.Z == 0);
    }

    Point m(1, 2.6);


    SECTION("test constructor"){
        REQUIRE(m.X == 1);
        REQUIRE(m.Y == 2.6);
        REQUIRE(m.Z == 0);
    }

    Point n(2.5, -1, -5.8);

    std::ostringstream os;

    SECTION("test operator <<"){
        os << m << " " << p << " " << n;

        REQUIRE(os.str() == "(1,2.6,0) (0,0,0) (2.5,-1,-5.8)");
    }

    std::istringstream is("-1 2.0 3.5");

    SECTION("test operator >>"){
        Point x;
        is >> x;

        REQUIRE(x.X ==  -1);
        REQUIRE(x.Y ==  2.0);
        REQUIRE(x.Z ==  3.5);
    }
}


TEST_CASE("test class ListQueue", "[list]") {

    ListQueue<Point> l;


    SECTION("test empty list") {
        REQUIRE(l.size() == 0);
    }


    SECTION("push back and operator []"){
        Point p(-1, 2.5, 31);

        l.push_back(Point(1, 2, 3));
        l.push_back(p);


        REQUIRE(l.size() == 2);


        REQUIRE(l[0].X == 1);
        REQUIRE(l[0].Y == 2);
        REQUIRE(l[0].Z == 3);

        REQUIRE(l[1].X == p.X);
        REQUIRE(l[1].Y == p.Y);
        REQUIRE(l[1].Z == p.Z);

        l.push_back(Point(-1, -2, -3));
        l.push_back(Point(-11, -12, -13));
        l.push_back(Point(-21, -22, -23));

        REQUIRE(l.size() == 5);
    }


    SECTION("erase and operator []"){

        l.push_back(Point(1, 2, 3));
        l.push_back(Point(10.5, 11.5, 12.25));
        l.push_back(Point(-1, -2, -3));
        l.push_back(Point(-11, -12, -13));
        l.push_back(Point(-21, -22, -23));

        REQUIRE(l.size() == 5);


        l.pop_front();

        REQUIRE(l.size() == 4);

        l.pop_front();

        REQUIRE(l.size() == 3);

        REQUIRE(l[0].X == -1);
        REQUIRE(l[0].Y == -2);
        REQUIRE(l[0].Z == -3);


        l.pop_front();

        REQUIRE(l.size() == 2);


        REQUIRE(l[0].X == -11);
        REQUIRE(l[0].Y == -12);
        REQUIRE(l[0].Z == -13);

    }
}


TEST_CASE("test class ArrayQueue", "[array]") {

    ArrayQueue<Point> l;


    SECTION("test empty array") {
        REQUIRE(l.size() == 0);
    }


    SECTION("push back and operator []"){
        Point p(-1, 2.5, 31);

        l.push_back(Point(1, 2, 3));
        l.push_back(p);


        REQUIRE(l.size() == 2);


        REQUIRE(l[0].X == 1);
        REQUIRE(l[0].Y == 2);
        REQUIRE(l[0].Z == 3);

        REQUIRE(l[1].X == p.X);
        REQUIRE(l[1].Y == p.Y);
        REQUIRE(l[1].Z == p.Z);

        l.push_back(Point(-1, -2, -3));
        l.push_back(Point(-11, -12, -13));
        l.push_back(Point(-21, -22, -23));

        REQUIRE(l.size() == 5);
    }


    SECTION("erase and operator []"){

        l.push_back(Point(1, 2, 3));
        l.push_back(Point(10.5, 11.5, 12.25));
        l.push_back(Point(-1, -2, -3));
        l.push_back(Point(-11, -12, -13));
        l.push_back(Point(-21, -22, -23));

        REQUIRE(l.size() == 5);


        l.pop_front();

        REQUIRE(l.size() == 4);

        l.pop_front();

        REQUIRE(l.size() == 3);

        REQUIRE(l[0].X == -1);
        REQUIRE(l[0].Y == -2);
        REQUIRE(l[0].Z == -3);


        l.pop_front();

        REQUIRE(l.size() == 2);


        REQUIRE(l[0].X == -11);
        REQUIRE(l[0].Y == -12);
        REQUIRE(l[0].Z == -13);

    }
}


TEST_CASE("test class VectorQueue", "[vector]") {

    VectorQueue<Point> l;


    SECTION("test empty array") {
        REQUIRE(l.size() == 0);
    }


    SECTION("push back and operator []"){
        Point p(-1, 2.5, 31);

        l.push_back(Point(1, 2, 3));
        l.push_back(p);


        REQUIRE(l.size() == 2);


        REQUIRE(l[0].X == 1);
        REQUIRE(l[0].Y == 2);
        REQUIRE(l[0].Z == 3);

        REQUIRE(l[1].X == p.X);
        REQUIRE(l[1].Y == p.Y);
        REQUIRE(l[1].Z == p.Z);

        l.push_back(Point(-1, -2, -3));
        l.push_back(Point(-11, -12, -13));
        l.push_back(Point(-21, -22, -23));

        REQUIRE(l.size() == 5);
    }


    SECTION("erase and operator []"){

        l.push_back(Point(1, 2, 3));
        l.push_back(Point(10.5, 11.5, 12.25));
        l.push_back(Point(-1, -2, -3));
        l.push_back(Point(-11, -12, -13));
        l.push_back(Point(-21, -22, -23));

        REQUIRE(l.size() == 5);


        l.pop_front();

        REQUIRE(l.size() == 4);

        l.pop_front();

        REQUIRE(l.size() == 3);

        REQUIRE(l[0].X == -1);
        REQUIRE(l[0].Y == -2);
        REQUIRE(l[0].Z == -3);


        l.pop_front();

        REQUIRE(l.size() == 2);


        REQUIRE(l[0].X == -11);
        REQUIRE(l[0].Y == -12);
        REQUIRE(l[0].Z == -13);

    }
}
