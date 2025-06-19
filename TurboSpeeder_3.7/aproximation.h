#pragma once
// This will be the aproximation
#include <vector>
#include <string>
#include <cmath>

struct Point3D {
public:
    float x, y, z;
    size_t index; // originaler Index zum Wiederaufbau
};

float perpendicularDistance(const Point3D& pt, const Point3D& lineStart, const Point3D& lineEnd);
void douglasPeuckerRecursive(const std::vector<Point3D>& points, float epsilon, std::vector<Point3D>& result);