#ifndef D3__POLYGON__TEST__LENGTH_TEST_HPP
#define D3__POLYGON__TEST__LENGTH_TEST_HPP

#include "catch/catch.hpp"

#include "d3_polygon/index.hpp"

using point_t = std::array<double, 2>;
using points_t = std::vector<point_t>;

TEST_CASE("polygonLength(polygon) returns the expected value for closed counterclockwise polygons") {
    REQUIRE( d3_polygon::polygonLength(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}}) == Approx(4) );
}

TEST_CASE("polygonLength(polygon) returns the expected value for closed clockwise polygons") {
    REQUIRE( d3_polygon::polygonLength(points_t{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}) == Approx(4) );
    REQUIRE( d3_polygon::polygonLength(points_t{{1, 1}, {3, 2}, {2, 3}, {1, 1}}) == Approx(std::sqrt(20) + std::sqrt(2)) );
}

TEST_CASE("polygonLength(polygon) returns the expected value for open counterclockwise polygons") {
    REQUIRE( d3_polygon::polygonLength(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}}) == Approx(4) );
}

TEST_CASE("polygonLength(polygon) returns the expected value for open clockwise polygons") {
    REQUIRE( d3_polygon::polygonLength(points_t{{0, 0}, {1, 0}, {1, 1}, {0, 1}}) == Approx(4) );
    REQUIRE( d3_polygon::polygonLength(points_t{{1, 1}, {3, 2}, {2, 3}}) == Approx( std::sqrt(20) + std::sqrt(2)) );
}

#endif // D3__POLYGON__TEST__LENGTH_TEST_HPP
