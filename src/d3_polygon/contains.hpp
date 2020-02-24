#ifndef D3__POLYGON__CONTAINS_HPP
#define D3__POLYGON__CONTAINS_HPP

#include <vector>

namespace d3_polygon {

template <typename PointT>
inline bool contains(const std::vector<PointT>& polygon, const PointT& point) {
    const std::size_t n = polygon.size();
    PointT p = polygon[n - 1];
    auto x = point[0], y = point[1];
    auto x0 = p[0], y0 = p[1];
    double x1, y1;
    bool inside = false;

    for (std::size_t i = 0; i < n; ++i) {
        p = polygon[i], x1 = p[0], y1 = p[1];
        if (((y1 > y) != (y0 > y)) && (x < (x0 - x1) * (y - y1) / (y0 - y1) + x1)) inside = !inside;
        x0 = x1, y0 = y1;
    }

    return inside;
}

} // namespace d3_polygon

#endif // D3__POLYGON__CONTAINS_HPP
