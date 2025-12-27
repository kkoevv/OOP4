#pragma once
#include "figure.h"
#include <cmath>
#include <numbers>

template<Scalar T>
class Square : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center_;
    T side_;
    
public:
    Square(T x = 0, T y = 0, T side = 1) 
        : center_(std::make_unique<Point<T>>(x, y)), side_(side) {}
    
    Square(const Point<T>& center, T side) 
        : center_(std::make_unique<Point<T>>(center)), side_(side) {}
    
    Square(const Square& other)
        : center_(std::make_unique<Point<T>>(*other.center_)), side_(other.side_) {}
    
    Square& operator=(const Square& other) {
        if (this != &other) {
            center_ = std::make_unique<Point<T>>(*other.center_);
            side_ = other.side_;
        }
        return *this;
    }
    
    // Move семантика
    Square(Square&& other) noexcept = default;
    Square& operator=(Square&& other) noexcept = default;
    
    Point<T> geometric_center() const override {
        return *center_;
    }
    
    double area() const override {
        return side_ * side_;
    }
    
    void print_vertices() const override {
        std::cout << "Vertices: ";
        T half = side_ / 2.0;
        // Вращаем квадрат на 45 градусов для красоты
        double angle45 = std::numbers::pi / 4.0;
        double r = half * std::sqrt(2.0);
        
        for (int i = 0; i < 4; ++i) {
            double angle = 2.0 * std::numbers::pi * i / 4.0 + angle45;
            T x = center_->x() + r * std::cos(angle);
            T y = center_->y() + r * std::sin(angle);
            std::cout << "(" << x << ", " << y << ") ";
        }
        std::cout << "\n";
    }
    
    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Square<T>>(*this);
    }
    
    std::string name() const override { return "Square"; }
    
    bool is_rotation_figure() const override {
        return true;  // Квадрат - фигура вращения
    }
    
    bool is_inscribed_in_circle() const override {
        return true;  // Квадрат можно вписать в окружность
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Square* other_sq = dynamic_cast<const Square*>(&other);
        if (!other_sq) return false;
        return *center_ == *other_sq->center_ && side_ == other_sq->side_;
    }
    
    std::istream& read(std::istream& is) override {
        T x, y, side;
        if (is >> x >> y >> side && side > 0) {
            *center_ = Point<T>(x, y);
            side_ = side;
        } else {
            is.setstate(std::ios::failbit);
        }
        return is;
    }
    
    T side() const { return side_; }
    Point<T> center() const { return *center_; }
};