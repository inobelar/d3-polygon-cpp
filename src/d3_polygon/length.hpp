#ifndef D3__POLYGON__LENGTH_HPP
#define D3__POLYGON__LENGTH_HPP

#include <vector>

#include <cmath> // for std::sqrt()

namespace d3_polygon {

template <typename PointT>
inline double length(const std::vector<PointT>& polygon) {
    int i = -1;
    const int n = polygon.size();
    PointT b = polygon[n - 1];
    double xa;
    double ya;
    double xb = b[0];
    double yb = b[1];
    double perimeter = 0;

    while (++i < n) {
        xa = xb;
        ya = yb;
        b = polygon[i];
        xb = b[0];
        yb = b[1];
        xa -= xb;
        ya -= yb;
        perimeter += std::sqrt(xa * xa + ya * ya);
    }

    return perimeter;
}

} // namespace d3_polygon

#endif // D3__POLYGON__LENGTH_HPP
