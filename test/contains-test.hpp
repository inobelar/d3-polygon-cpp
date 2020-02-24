#ifndef D3__POLYGON__TEST__CONTAINS_TEST_HPP
#define D3__POLYGON__TEST__CONTAINS_TEST_HPP

#include "catch/catch.hpp"

#include "d3_polygon/index.hpp"

using point_t = std::array<double, 2>;
using points_t = std::vector<point_t>;

TEST_CASE("polygonContains(polygon, point) returns the expected value for closed counterclockwise polygons") {
    REQUIRE( d3_polygon::polygonContains(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}}, {0.5, 0.5}) == true );
    REQUIRE( d3_polygon::polygonContains(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}}, {1.5, 0.5}) == false );
    REQUIRE( d3_polygon::polygonContains(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}}, {-0.5, 0.5}) == false );
    REQUIRE( d3_polygon::polygonContains(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}}, {0.5, 1.5}) == false );
    REQUIRE( d3_polygon::polygonContains(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}}, {0.5, -0.5}) == false );
}

TEST_CASE("polygonContains(polygon, point) returns the expected value for closed clockwise polygons") {
    REQUIRE( d3_polygon::polygonContains(points_t{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}, {0.5, 0.5}) == true );
    REQUIRE( d3_polygon::polygonContains(points_t{{1, 1}, {3, 2}, {2, 3}, {1, 1}}, {1.5, 1.5}) == true );
}

TEST_CASE("polygonContains(polygon, point) returns the expected value for open counterclockwise polygons") {
    REQUIRE( d3_polygon::polygonContains(points_t{{0, 0}, {0, 1}, {1, 1}, {1, 0}}, {0.5, 0.5}) == true );
}

TEST_CASE("polygonContains(polygon, point) returns the expected value for open clockwise polygons") {
    REQUIRE( d3_polygon::polygonContains(points_t{{0, 0}, {1, 0}, {1, 1}, {0, 1}}, {0.5, 0.5}) == true );
    REQUIRE( d3_polygon::polygonContains(points_t{{1, 1}, {3, 2}, {2, 3}}, {1.5, 1.5}) == true );
}

#endif // D3__POLYGON__TEST__CONTAINS_TEST_HPP
