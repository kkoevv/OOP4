#pragma once

#include "./Figure.h"

template<typename T>
class Triangle : public Figure<T> {
public:
    Triangle() : Figure<T>() {}
    ~Triangle() = default;

    Triangle(Point<T> v1, Point<T> v2, Point<T> v3) : Figure<T>() {
        this->_points = std::make_unique<Point<T>[]>(this->GetPointCount());
        this->_points[0] = v1;
        this->_points[1] = v2;
        this->_points[2] = v3;
    }

    double Area() const override  {
        return std::sqrt(3) * std::pow(this->Length(), 2) / 4.0;
    }

    size_t GetPointCount() const override  { return 3; }

    std::string GetTypeName() const override  {
        return "Triangle";
    }
};