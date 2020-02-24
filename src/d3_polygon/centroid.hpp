#ifndef D3__POLYGON__CENTROID_HPP
#define D3__POLYGON__CENTROID_HPP

#include <vector>

namespace d3_polygon {

template <typename PointT>
inline PointT centroid(const std::vector<PointT>& polygon) {
    int i = -1;
    const int n = polygon.size();
    double x = 0;
    double y = 0;
    PointT a;
    PointT b = polygon[n - 1];
    double c;
    double k = 0;

    while (++i < n) {
        a = b;
        b = polygon[i];
        k += c = a[0] * b[1] - b[0] * a[1];
        x += (a[0] + b[0]) * c;
        y += (a[1] + b[1]) * c;
    }

    k *= 3;
    return {x / k, y / k};
}

} // namespace d3_polygon

#endif // D3__POLYGON__CENTROID_HPP
