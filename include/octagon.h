#pragma once
#include "figure.h"
#include <cmath>
#include <numbers>

template<Scalar T>
class Octagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center_;
    T radius_;  // радиус описанной окружности
    
public:
    Octagon(T x = 0, T y = 0, T radius = 1) 
        : center_(std::make_unique<Point<T>>(x, y)), radius_(radius) {}
    
    Octagon(const Point<T>& center, T radius) 
        : center_(std::make_unique<Point<T>>(center)), radius_(radius) {}
    
    Octagon(const Octagon& other)
        : center_(std::make_unique<Point<T>>(*other.center_)), radius_(other.radius_) {}
    
    Octagon& operator=(const Octagon& other) {
        if (this != &other) {
            center_ = std::make_unique<Point<T>>(*other.center_);
            radius_ = other.radius_;
        }
        return *this;
    }
    
    // Move семантика
    Octagon(Octagon&& other) noexcept = default;
    Octagon& operator=(Octagon&& other) noexcept = default;
    
    Point<T> geometric_center() const override {
        return *center_;
    }
    
    double area() const override {
        return 2.0 * radius_ * radius_ * std::sin(std::numbers::pi / 4.0);
    }
    
    void print_vertices() const override {
        std::cout << "Vertices: ";
        for (int i = 0; i < 8; ++i) {
            double angle = 2.0 * std::numbers::pi * i / 8.0;
            T x = center_->x() + radius_ * std::cos(angle);
            T y = center_->y() + radius_ * std::sin(angle);
            std::cout << "(" << x << ", " << y << ") ";
        }
        std::cout << "\n";
    }
    
    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Octagon<T>>(*this);
    }
    
    std::string name() const override { return "Octagon"; }
    
    bool is_rotation_figure() const override {
        return true;  // Правильный 8-угольник - фигура вращения
    }
    
    bool is_inscribed_in_circle() const override {
        return true;  // Все вершины на одной окружности
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Octagon* other_oct = dynamic_cast<const Octagon*>(&other);
        if (!other_oct) return false;
        return *center_ == *other_oct->center_ && radius_ == other_oct->radius_;
    }
    
    std::istream& read(std::istream& is) override {
        T x, y, radius;
        if (is >> x >> y >> radius && radius > 0) {
            *center_ = Point<T>(x, y);
            radius_ = radius;
        } else {
            is.setstate(std::ios::failbit);
        }
        return is;
    }
    
    T radius() const { return radius_; }
    Point<T> center() const { return *center_; }
};