#ifndef D3__POLYGON__HULL_HPP
#define D3__POLYGON__HULL_HPP

#include "d3_polygon/cross.hpp"

#include <vector>
#include <algorithm> // for std::sort()

namespace d3_polygon {

namespace detail {

template <typename PointT>
bool lexicographicOrder(const PointT& a, const PointT& b) {
    // NOTE: in c++ original js version not works: "a[0] - b[0] || a[1] - b[1]"
    // References: https://stackoverflow.com/a/46371357 & https://rosettacode.org/wiki/Convex_hull#Go
    return (a[0] == b[0]) ? (a[1] < b[1]) : (a[0] < b[0]);
}

// Computes the upper convex hull per the monotone chain algorithm.
// Assumes points.length >= 3, is sorted by x, unique in y.
// Returns an array of indices into points in left-to-right order.
template <typename PointT>
std::vector<std::size_t> computeUpperHullIndexes(const std::vector<PointT>& points) {
    const std::size_t n = points.size();
    std::vector<std::size_t> indexes = {0, 1};
    std::size_t size = 2;

    for (std::size_t i = 2; i < n; ++i) {
        while (size > 1 && cross(points[indexes[size - 2]], points[indexes[size - 1]], points[i]) <= 0) --size;

        // Next 5 lines of code - implementation of: `indexes[size++] = i;`
        if(size >= indexes.size()) {
            indexes.push_back(i);
        } else {
            indexes[size] = i;
        }
        size++;
    }

    indexes.resize(size); // the same as: `indexes.slice(0, size)`; // remove popped points
    return indexes;
}

template <typename T>
struct IndexedPoint {
    T x, y;
    T/*std::size_t*/ idx;

    IndexedPoint()
        : x(0), y(0), idx(0)
    {}

    IndexedPoint(const T x_, const T y_, const std::size_t idx_)
        : x(x_), y(y_), idx(idx_)
    {}

    T operator [](const std::size_t i) const {
        switch (i) {
        case 0: return x;
        case 1: return y;
        case 2: return idx;
        }
    }
};

} // namespace detail

template <typename PointT>
std::vector<PointT> hull(const std::vector<PointT>& points) {
    using IPoint = detail::IndexedPoint< double >; // TODO: instead of `double` must be type of .x or .y point fields, or something like decltype(PointT::operator<std::size_t>[]) :)

    const std::size_t n = points.size();
    if (n < 3) return {};

    std::size_t i;
    auto sortedPoints  = std::vector<IPoint>(n);
    auto flippedPoints = std::vector<PointT>(n);

    for (i = 0; i < n; ++i) sortedPoints[i] = {points[i][0], points[i][1], i};
    std::sort(sortedPoints.begin(), sortedPoints.end(), detail::lexicographicOrder<IPoint>);
    for (i = 0; i < n; ++i) flippedPoints[i] = {sortedPoints[i][0], -sortedPoints[i][1]};

    const auto upperIndexes = detail::computeUpperHullIndexes(sortedPoints),
               lowerIndexes = detail::computeUpperHullIndexes(flippedPoints);

    // Construct the hull polygon, removing possible duplicate endpoints.
    const bool skipLeft  = lowerIndexes[0] == upperIndexes[0],
               skipRight = lowerIndexes[lowerIndexes.size() - 1] == upperIndexes[upperIndexes.size() - 1];
    std::vector<PointT> hull;

    // Add upper hull in right-to-l order.
    // Then add lower hull in left-to-right order.
    for (i = (upperIndexes.size() ); i-- > 0; ) hull.push_back(points[sortedPoints[upperIndexes[i]][2]]); // NOTE: original loop code: `for(i = upperIndexes.size() - 1; i >= 0; --i)` NOT WORKS IN C++ (produces SEGFAULT) - due to `std::size_t i` comparison & overflow. References: https://stackoverflow.com/a/57935979 & https://stackoverflow.com/a/3626468
    for (i = skipLeft; i < (lowerIndexes.size() - skipRight); ++i) hull.push_back(points[sortedPoints[lowerIndexes[i]][2]]);

    return hull;
}

} // namespace d3_polygon

#endif // D3__POLYGON__HULL_HPP
