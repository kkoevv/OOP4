#pragma once

#include "./Figure.h"

template<typename T>
class Octagon : public Figure<T> {
public:
    Octagon() : Figure<T>() {}
    ~Octagon() = default;

    Octagon(
        Point<T> v1, Point<T> v2, Point<T> v3, Point<T> v4,
        Point<T> v5, Point<T> v6, Point<T> v7, Point<T> v8
    ) : Figure<T>()
    {
        this->_points = std::make_unique<Point<T>[]>(this->GetPointCount());         
        this->_points[0] = v1;
        this->_points[1] = v2;
        this->_points[2] = v3;
        this->_points[3] = v4;
        this->_points[4] = v5;
        this->_points[5] = v6;
        this->_points[6] = v7;
        this->_points[7] = v8;
    }

    double Area() const override {
        return 2.0 * (1.0 + std::sqrt(2)) * std::pow(this->Length(), 2);
    }


    size_t GetPointCount() const override { return 8; }

    std::string GetTypeName() const override {
        return "Octagon";
    }
};