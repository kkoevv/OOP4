#pragma once

#include "./Figure.h"

template<typename T>
class Square : public Figure<T> {
public:
    Square() : Figure<T>() {}
    ~Square() = default;

    Square(Point<T> v1, Point<T> v2, Point<T> v3, Point<T> v4) : Figure<T>() {
        this->_points = std::make_unique<Point<T>[]>(this->GetPointCount()); 
        this->_points[0] = v1;
        this->_points[1] = v2;
        this->_points[2] = v3;
        this->_points[3] = v4;
    }

    double Area() const override  {
        return std::pow(this->Length(), 2);
    }

    size_t GetPointCount() const override { return 4; }

    std::string GetTypeName() const override  {
        return "Square";
    }
};