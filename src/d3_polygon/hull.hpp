#ifndef D3__POLYGON__HULL_HPP
#define D3__POLYGON__HULL_HPP

#include "d3_polygon/cross.hpp"

#include <vector>
#include <algorithm> // for std::sort()

namespace d3_polygon {

namespace detail {

template <typename PointT>
bool lexicographicOrder(const PointT& a, const PointT& b) {
    return a[0] - b[0] || a[1] - b[1];
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
        indexes[size++] = i; // FIX
    }

    indexes.resize(size); // indexes.slice(0, size); // remove popped points
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
    const std::size_t n = points.size();
    if (n < 3) return {};

    std::size_t i;
    auto sortedPoints  = std::vector<detail::IndexedPoint<double>>(n);
    auto flippedPoints = std::vector<PointT>(n);

    for (i = 0; i < n; ++i) sortedPoints[i] = {points[i][0], points[i][1], i};
    std::sort(sortedPoints.begin(), sortedPoints.end(), detail::lexicographicOrder<detail::IndexedPoint<double>>);
    for (i = 0; i < n; ++i) flippedPoints[i] = {sortedPoints[i][0], -sortedPoints[i][1]};

    const auto upperIndexes = detail::computeUpperHullIndexes(sortedPoints),
               lowerIndexes = detail::computeUpperHullIndexes(flippedPoints);

    // Construct the hull polygon, removing possible duplicate endpoints.
    const bool skipLeft = lowerIndexes[0] == upperIndexes[0],
               skipRight = lowerIndexes[lowerIndexes.size() - 1] == upperIndexes[upperIndexes.size() - 1];
    std::vector<PointT> hull;

    // Add upper hull in right-to-l order.
    // Then add lower hull in left-to-right order.
    for (int i = (upperIndexes.size() - 1); i >= 0; --i) hull.push_back(points[sortedPoints[upperIndexes[i]][2]]);
    for (int i = (int)skipLeft; i < ((int)lowerIndexes.size() - (int)skipRight); ++i) hull.push_back(points[sortedPoints[lowerIndexes[i]][2]]);

    return hull;
}

} // namespace d3_polygon

#endif // D3__POLYGON__HULL_HPP
