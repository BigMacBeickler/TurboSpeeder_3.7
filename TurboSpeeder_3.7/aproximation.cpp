// This will be the aproximation
#include "aproximation.h"

double perpendicularDistance(const Point3D& pt, const Point3D& lineStart, const Point3D& lineEnd) {
    Point3D u = { lineEnd.x - lineStart.x, lineEnd.y - lineStart.y, lineEnd.z - lineStart.z };
    Point3D v = { pt.x - lineStart.x, pt.y - lineStart.y, pt.z - lineStart.z };

    double dot = u.x * v.x + u.y * v.y + u.z * v.z;
    double lenSq = u.x * u.x + u.y * u.y + u.z * u.z;
    double param = dot / lenSq;

    Point3D proj = {
        lineStart.x + param * u.x,
        lineStart.y + param * u.y,
        lineStart.z + param * u.z
    };

    double dx = pt.x - proj.x;
    double dy = pt.y - proj.y;
    double dz = pt.z - proj.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

void douglasPeuckerRecursive(const std::vector<Point3D>& points, float DouglasPeuckerTolerance, std::vector<Point3D>& result) {
    if (points.size() < 2) return;

    double maxDist = 0;
    size_t index = 0;

    for (size_t i = 1; i < points.size() - 1; ++i) {
        double dist = perpendicularDistance(points[i], points[0], points.back());
        if (dist > maxDist) {
            index = i;
            maxDist = dist;
        }
    }

    if (maxDist > DouglasPeuckerTolerance) {
        std::vector<Point3D> left(points.begin(), points.begin() + index + 1);
        std::vector<Point3D> right(points.begin() + index, points.end());

        std::vector<Point3D> resLeft, resRight;
        douglasPeuckerRecursive(left, DouglasPeuckerTolerance, resLeft);
        douglasPeuckerRecursive(right, DouglasPeuckerTolerance, resRight);

        result.insert(result.end(), resLeft.begin(), resLeft.end() - 1);
        result.insert(result.end(), resRight.begin(), resRight.end());
    }
    else {
        result.push_back(points.front());
        result.push_back(points.back());
    }
}