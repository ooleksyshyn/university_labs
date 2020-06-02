#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include "catch.hpp"
#include "multiplication.hpp"


void simple_test(MatrixMultiplier& multiplier){
    matrix x = {{1, 2}, {1, 2}};
    matrix e = {{1, 0}, {0, 1}};
    matrix o = {{0, 0}, {0, 0}};

    matrix result{{3, 6}, {3, 6}};

    REQUIRE(multiplier.multiply(x, x) == result);

    REQUIRE(multiplier.multiply(x, e) == x);
    REQUIRE(multiplier.multiply(e, x) == x);

    REQUIRE(multiplier.multiply(x, o) == o);
    REQUIRE(multiplier.multiply(o, x) == o);
}


void bigger_test(MatrixMultiplier& multiplier){
    matrix x = {
            {1, 2, 3, 4, 5},
            {1, 2, 7, 1, 5},
            {3, 4, 6, 1, 8}
    };
    matrix y = {
            {5, 7, 82},
            {4, 5, 12},
            {12, 35, 43},
            {75, 23, 84},
            {420, 45, 12}
    };

    matrix xy_result{
            {2449, 439,631},
            {2272, 510,551},
            {3538, 634, 732}
    };

    matrix yx_result{
            {258, 352, 556, 109, 716},
            {45, 66, 119, 33, 141},
            {176, 266, 539, 126, 579},
            {350, 532, 890, 407, 1162},
            {501, 978, 1647, 1737, 2421}
    };

    REQUIRE(multiplier.multiply(y, x) == yx_result);
    REQUIRE(multiplier.multiply(x, y) == xy_result);

}



TEST_CASE("test simple multiplication"){
    SimpleMatrixMultiplier simple;

    SECTION("simple matrix"){
        simple_test(simple);
    }


    SECTION("bigger matrix"){
        bigger_test(simple);
    }
}


TEST_CASE("test multi thread multiplication"){
    MultiThreadMatrixMultiplier multiThread;


    SECTION("simple matrix"){
        simple_test(multiThread);
    }


    SECTION("bigger matrix"){
        bigger_test(multiThread);
    }
}



TEST_CASE("random big matrix"){
    SimpleMatrixMultiplier simple;
    MultiThreadMatrixMultiplier multiThread;

    SECTION("medium"){
        matrix x = generate_random(20, 36);
        matrix y = generate_random(36, 31);

        REQUIRE(simple.multiply(x, y) == multiThread.multiply(x, y));
    }

    SECTION("big"){
        matrix x = generate_random(70, 93);
        matrix y = generate_random(93, 105);

        REQUIRE(simple.multiply(x, y) == multiThread.multiply(x, y));
    }


    SECTION("very big"){
        matrix x = generate_random(200, 250);
        matrix y = generate_random(250, 300);

        REQUIRE(simple.multiply(x, y) == multiThread.multiply(x, y));
    }
}


TEST_CASE("benchmark"){
    SimpleMatrixMultiplier simple;
    MultiThreadMatrixMultiplier multiThread;

    matrix x = generate_random(300, 300);
    matrix y = generate_random(300, 300);

    BENCHMARK("test multi thread"){
        return multiThread.multiply(x, y);
    };


    BENCHMARK("test simple"){
        return simple.multiply(x, y);
    };
}