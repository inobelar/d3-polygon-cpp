#ifndef D3__POLYGON__TEST__AREA_TEST_HPP
#define D3__POLYGON__TEST__AREA_TEST_HPP

#include "catch/catch.hpp"

#include "d3_polygon/index.hpp"

using point_t = std::array<double, 2>;
using points_t = std::vector<point_t>;

TEST_CASE("polygonArea(polygon) returns the expected value for closed counterclockwise polygons") {
    REQUIRE( d3_polygon::polygonArea(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}}) == Approx(1) );
}

TEST_CASE("polygonArea(polygon) returns the expected value for closed clockwise polygons") {
    REQUIRE( d3_polygon::polygonArea(points_t{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}) == Approx(-1) );
    REQUIRE( d3_polygon::polygonArea(points_t{{1, 1}, {3, 2}, {2, 3}, {1, 1}}) == Approx(-1.5) );
}

TEST_CASE("polygonArea(polygon) returns the expected value for open counterclockwise polygons") {
    REQUIRE( d3_polygon::polygonArea(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}}) == Approx(1) );
}

TEST_CASE("polygonArea(polygon) returns the expected value for open clockwise polygons") {
    REQUIRE( d3_polygon::polygonArea(points_t{{0, 0}, {1, 0}, {1, 1}, {0, 1}}) == Approx(-1) );
    REQUIRE( d3_polygon::polygonArea(points_t{{1, 1}, {3, 2}, {2, 3}}) == Approx(-1.5) );
}

TEST_CASE("polygonArea(polygon) returns the expected value for a very large polygon") {
    constexpr double stop = 1e8;
    constexpr double step = 1e4;
    points_t points = {};
    double value;
    for (value = 0; value < stop; value += step) points.push_back({0, value});
    for (value = 0; value < stop; value += step) points.push_back({value, stop});
    for (value = stop - step; value >= 0; value -= step) points.push_back({stop, value});
    for (value = stop - step; value >= 0; value -= step) points.push_back({value, 0});
    REQUIRE( d3_polygon::polygonArea(points) == Approx(1e16 - 5e7) );
}

#endif // D3__POLYGON__TEST__AREA_TEST_HPP
