#ifndef D3__POLYGON__TEST__CENTROID_TEST_HPP
#define D3__POLYGON__TEST__CENTROID_TEST_HPP

#include "catch/catch.hpp"

#include "d3_polygon/index.hpp"

using point_t = std::array<double, 2>;
using points_t = std::vector<point_t>;

TEST_CASE("polygonCentroid(points) returns the expected value for closed counterclockwise polygons") {
    REQUIRE( d3_polygon::polygonCentroid(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}}) == point_t{.5, .5} );
}

TEST_CASE("polygonCentroid(points) returns the expected value for closed clockwise polygons") {
    REQUIRE( d3_polygon::polygonCentroid(points_t{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}) == point_t{.5, .5} );
    REQUIRE( d3_polygon::polygonCentroid(points_t{{1, 1}, {3, 2}, {2, 3}, {1, 1}}) == point_t{2, 2} );
}

TEST_CASE("polygonCentroid(points) returns the expected value for open counterclockwise polygons") {
    REQUIRE( d3_polygon::polygonCentroid(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}}) == point_t{.5, .5} );
}

TEST_CASE("polygonCentroid(points) returns the expected values for closed counterclockwise polygons") { // Added value[s] into test name, because first test named the same
    REQUIRE( d3_polygon::polygonCentroid(points_t{{0, 0}, {1, 0}, {1, 1}, {0, 1}}) == point_t{.5, .5} );
    REQUIRE( d3_polygon::polygonCentroid(points_t{{1, 1}, {3, 2}, {2, 3}}) == point_t{2, 2} );
}

TEST_CASE("polygonCentroid(polygon) returns the expected value for a very large polygon") {
    constexpr double stop = 1e8;
    constexpr double step = 1e4;
    points_t points = {};
    double value;
    for (value = 0; value < stop; value += step) points.push_back({0, value});
    for (value = 0; value < stop; value += step) points.push_back({value, stop});
    for (value = stop - step; value >= 0; value -= step) points.push_back({stop, value});
    for (value = stop - step; value >= 0; value -= step) points.push_back({value, 0});
    REQUIRE( d3_polygon::polygonCentroid(points) == point_t{49999999.75000187, 49999999.75001216} );
}

#endif // D3__POLYGON__TEST__CENTROID_TEST_HPP
