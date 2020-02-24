#ifndef D3__POLYGON__INDEX_HPP
#define D3__POLYGON__INDEX_HPP

#include "d3_polygon/area.hpp"
#include "d3_polygon/centroid.hpp"
#include "d3_polygon/hull.hpp"
#include "d3_polygon/contains.hpp"
#include "d3_polygon/length.hpp"

// Simple function aliases

namespace d3_polygon {

template <typename PointT>
inline double polygonArea(const std::vector<PointT>& polygon) {
    return d3_polygon::area(polygon);
}

template <typename PointT>
inline PointT polygonCentroid(const std::vector<PointT>& polygon) {
    return d3_polygon::centroid(polygon);
}

template <typename PointT>
inline std::vector<PointT> polygonHull(const std::vector<PointT>& polygon) {
    return d3_polygon::hull(polygon);
}

template <typename PointT>
inline bool polygonContains(const std::vector<PointT>& polygon, const PointT& point) {
    return d3_polygon::contains(polygon, point);
}

template <typename PointT>
inline double polygonLength(const std::vector<PointT>& polygon) {
    return d3_polygon::length(polygon);
}

} // namespace d3_polygon

#endif // D3__POLYGON__INDEX_HPP
