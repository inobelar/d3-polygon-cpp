#ifndef D3__POLYGON__TEST__HULL_TEST_HPP
#define D3__POLYGON__TEST__HULL_TEST_HPP

#include "catch/catch.hpp"

#include "d3_polygon/index.hpp"

using point_t = std::array<double, 2>;
using points_t = std::vector<point_t>;

// NOTE: in original (javascript) code, here is checks for null. Replaced by check 'is empty'.
TEST_CASE("polygonHull(points) returns null if points has fewer than three elements") {
    REQUIRE( d3_polygon::polygonHull(points_t{}).empty() );
    REQUIRE( d3_polygon::polygonHull(points_t{{0, 1}}).empty() );
    REQUIRE( d3_polygon::polygonHull(points_t{{0, 1}, {1, 0}}).empty() );
}

TEST_CASE("polygonHull(points) returns the convex hull of the specified points") {
    REQUIRE( d3_polygon::polygonHull(points_t{{200, 200}, {760, 300}, {500, 500}}) == points_t{{760, 300}, {200, 200}, {500, 500}} );
    REQUIRE( d3_polygon::polygonHull(points_t{{200, 200}, {760, 300}, {500, 500}, {400, 400}}) == points_t{{760, 300}, {200, 200}, {500, 500}} );
}

TEST_CASE("polygonHull(points) handles points with duplicate ordinates") {
    REQUIRE( d3_polygon::polygonHull(points_t{{-10, -10}, {10, 10}, {10, -10}, {-10, 10}}) == points_t{{10, 10}, {10, -10}, {-10, -10}, {-10, 10}} );
}

TEST_CASE("polygonHull(points) handles overlapping upper and lower hulls") {
    REQUIRE( d3_polygon::polygonHull(points_t{{0, -10}, {0, 10}, {0, 0}, {10, 0}, {-10, 0}}) == points_t{{10, 0}, {0, -10}, {-10, 0}, {0, 10}} );
}

// Cases below taken from http://uva.onlinejudge.org/external/6/681.html
TEST_CASE("polygonHull(points) handles various non-trivial hulls") {
    REQUIRE( d3_polygon::polygonHull(points_t{{60, 20}, {250, 140}, {180, 170}, {79, 140}, {50, 60}, {60, 20}}) == points_t{{250, 140}, {60, 20}, {50, 60}, {79, 140}, {180, 170}} );
    REQUIRE( d3_polygon::polygonHull(points_t{{50, 60}, {60, 20}, {70, 45}, {100, 70}, {125, 90}, {200, 113}, {250, 140}, {180, 170}, {105, 140}, {79, 140}, {60, 85}, {50, 60}}) == points_t{{250, 140}, {60, 20}, {50, 60}, {79, 140}, {180, 170}} );
    REQUIRE( d3_polygon::polygonHull(points_t{{30, 30}, {50, 60}, {60, 20}, {70, 45}, {86, 39}, {112, 60}, {200, 113}, {250, 50}, {300, 200}, {130, 240}, {76, 150}, {47, 76}, {36, 40}, {33, 35}, {30, 30}}) == points_t{{300, 200}, {250, 50}, {60, 20}, {30, 30}, {47, 76}, {76, 150}, {130, 240}} );
}

#endif // D3__POLYGON__TEST__HULL_TEST_HPP
