#include <catch2/catch_test_macros.hpp>

import vektor;
import std;

using namespace vektor;

TEST_CASE("Vector initializer list construction", "[vector][construction]") {
    Vector<i64, 3> vec{10, 20, 30};

    REQUIRE(vec[0] == 10);
    REQUIRE(vec[1] == 20);
    REQUIRE(vec[2] == 30);
}

TEST_CASE("Vector partial construction value initializes unprovided elements", "[vector][construction]") {
    Vector<i64, 5> vec{1};
    REQUIRE(vec[0] == 1);
    
    for (size i = 1; i < 5; ++i) {
        REQUIRE(vec[i] == 0);
    }
}

TEST_CASE(".at() throws std::out_of_range when out of bounds", "[vector][access]") {
    Vector<i64, 3> vec{1, 2, 3};
    REQUIRE_THROWS_AS(vec.at(3), std::out_of_range);
}

TEST_CASE(".at() returns correct element", "[vector][access]") {
    Vector<i64, 3> vec{1, 2, 3};
    REQUIRE(vec.at(0) == 1);
    REQUIRE(vec.at(1) == 2);
    REQUIRE(vec.at(2) == 3);
}

TEST_CASE("Vector compound addition", "[vector][arithmetic]") {
    Vector<i64, 3> vec1{6, 5, 4};
    Vector<i64, 3> vec2{4, 5, 6};
    
    vec1 += vec2;

    REQUIRE(vec1.at(0) == 10);
    REQUIRE(vec1.at(1) == 10);
    REQUIRE(vec1.at(2) == 10);
}

TEST_CASE("Vector compound subtraction", "[vector][arithmetic]") {
    Vector<i64, 3> vec1{12, 5, 9};
    Vector<i64, 3> vec2{15, 6, 9};
    
    vec1 -= vec2;

    REQUIRE(vec1.at(0) == -3);
    REQUIRE(vec1.at(1) == -1);
    REQUIRE(vec1.at(2) == 0);
}