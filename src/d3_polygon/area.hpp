#ifndef D3__POLYGON__AREA_HPP
#define D3__POLYGON__AREA_HPP

#include <vector>

namespace d3_polygon {

template <typename PointT>
inline double area(const std::vector<PointT>& polygon) {
    int i = -1;
    const int n = polygon.size();
    PointT a;
    PointT b = polygon[n - 1];
    double area = 0;

    while (++i < n) {
        a = b;
        b = polygon[i];
        area += a[1] * b[0] - a[0] * b[1];
    }

    return area / 2;
}

} // namespace d3_polygon

#endif // D3__POLYGON__AREA_HPP
