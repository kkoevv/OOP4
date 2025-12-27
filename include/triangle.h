#pragma once
#include "figure.h"
#include <cmath>
#include <numbers>

template<Scalar T>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center_;
    T radius_;  // радиус описанной окружности
    
public:
    Triangle(T x = 0, T y = 0, T radius = 1) 
        : center_(std::make_unique<Point<T>>(x, y)), radius_(radius) {}
    
    Triangle(const Point<T>& center, T radius) 
        : center_(std::make_unique<Point<T>>(center)), radius_(radius) {}
    
    Triangle(const Triangle& other)
        : center_(std::make_unique<Point<T>>(*other.center_)), radius_(other.radius_) {}
    
    Triangle& operator=(const Triangle& other) {
        if (this != &other) {
            center_ = std::make_unique<Point<T>>(*other.center_);
            radius_ = other.radius_;
        }
        return *this;
    }
    
    // Move семантика
    Triangle(Triangle&& other) noexcept = default;
    Triangle& operator=(Triangle&& other) noexcept = default;
    
    Point<T> geometric_center() const override {
        return *center_;
    }
    
    double area() const override {
        return (3.0 * std::sqrt(3.0) / 4.0) * radius_ * radius_;
    }
    
    void print_vertices() const override {
        std::cout << "Vertices: ";
        for (int i = 0; i < 3; ++i) {
            double angle = 2.0 * std::numbers::pi * i / 3.0;
            T x = center_->x() + radius_ * std::cos(angle);
            T y = center_->y() + radius_ * std::sin(angle);
            std::cout << "(" << x << ", " << y << ") ";
        }
        std::cout << "\n";
    }
    
    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Triangle<T>>(*this);
    }
    
    std::string name() const override { return "Triangle"; }
    
    bool is_rotation_figure() const override {
        return true;  // Равносторонний треугольник - фигура вращения
    }
    
    bool is_inscribed_in_circle() const override {
        return true;  // Равносторонний треугольник вписан в окружность
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Triangle* other_tri = dynamic_cast<const Triangle*>(&other);
        if (!other_tri) return false;
        return *center_ == *other_tri->center_ && radius_ == other_tri->radius_;
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