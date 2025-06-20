#pragma once
// This will be the aproximation
#include <vector>
#include <string>
#include <cmath>

struct Point3D {
public:
    double x, y, z;
    size_t index; // originaler Index zum Wiederaufbau
};

double perpendicularDistance(const Point3D& pt, const Point3D& lineStart, const Point3D& lineEnd);
void douglasPeuckerRecursive(const std::vector<Point3D>& points, float DouglasPeuckerTolerance, std::vector<Point3D>& result);