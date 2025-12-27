#pragma once
#include "concept.h"
#include <memory>
#include <iostream>
#include <cmath>

template<Scalar T>
class Point {
private:
    std::unique_ptr<T> x_;
    std::unique_ptr<T> y_;
    
public:
    Point(T x = 0, T y = 0) 
        : x_(std::make_unique<T>(x)), y_(std::make_unique<T>(y)) {}
    
    Point(const Point& other)
        : x_(std::make_unique<T>(*other.x_)), y_(std::make_unique<T>(*other.y_)) {}
    
    Point& operator=(const Point& other) {
        if (this != &other) {
            *x_ = *other.x_;
            *y_ = *other.y_;
        }
        return *this;
    }
    
    // Move конструкторы
    Point(Point&& other) noexcept = default;
    Point& operator=(Point&& other) noexcept = default;
    
    T x() const { return *x_; }
    T y() const { return *y_; }
    
    void set_x(T x) { *x_ = x; }
    void set_y(T y) { *y_ = y; }
    
    bool operator==(const Point& other) const {
        const double eps = 1e-6;
        return std::abs(*x_ - *other.x_) < eps && 
               std::abs(*y_ - *other.y_) < eps;
    }
    
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << *p.x_ << ", " << *p.y_ << ")";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Point& p) {
        T x, y;
        if (is >> x >> y) {
            *p.x_ = x;
            *p.y_ = y;
        }
        return is;
    }
};