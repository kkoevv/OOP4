#pragma once

#include "./Array.h"

#include <cstddef>
#include <istream>
#include <cmath>
#include <memory>
#include <type_traits>

template<typename T>
struct Point {
    T x, y;
};

template<typename T>
requires std::is_arithmetic_v<T> //числовые типв
class Figure {
protected:
    // Список координат фигуры
    std::unique_ptr<Point<T>[]> _points;

public:
    // Конструктор по умолчанию
    Figure() {
        this->_points = std::make_unique<Point<T>[]>(this->GetPointCount()); 
    }

    // Конструктор копирования
    Figure(const Figure& obj) {
        if (this != &obj) {
            this->_points = std::make_unique<Point<T>[]>(obj.GetPointCount());
            for (size_t i = 0; i < obj.GetPointCount(); ++i) {
                this->_points[i] = obj._points[i];
            }
        }
    }

    // Конструктор перемещения
    Figure(Figure&& obj) noexcept {
        if (this != obj) {
            this->_points = std::move(obj._points);
        }
    }

    // Оператор копирования
    Figure& operator=(const Figure& obj) {
        if (this != &obj) {
            this->_points = std::make_unique<Point<T>[]>(this->GetPointCount());
            for (size_t i = 0; i < this->GetPointCount(); ++i) {
                this->_points[i] = obj._points[i];
            }
        }

        return *this;
    }

    // Оператор перемещения
    Figure& operator=(Figure&& obj) noexcept {
        if (this != &obj) {
            this->_points = std::move(obj._points);
        }

        return *this;
    }

    // Оператор сравнения двух фигур
    bool operator==(const Figure& obj) const {
        if (this == &obj) {
            return true;
        }

        if (typeid(*this) != typeid(obj)) {
            return false;
        }

        if (this->GetPointCount() != obj.GetPointCount()) {
            return false;
        }

        for (std::size_t i = 0; i < this->GetPointCount(); ++i) {
            if (this->_points[i].x != obj._points[i].x || this->_points[i].y != obj._points[i].y) {
                return false;
            }
        }

        return true;
    }

    // Метод вычисления площади фигуры
    virtual double Area() const = 0;

    // Метод вычисление геометрического центра фигуры
    Point<T> GeometricCenter() const {
        T sum_x = 0, sum_y = 0;

        for (std::size_t i = 0; i < this->GetPointCount(); ++i) {
            sum_x += this->_points[i].x;
            sum_y += this->_points[i].y;
        }

        return Point<T>{ sum_x / (T)this->GetPointCount(), sum_y / (T)this->GetPointCount() };
    }

    // Оператор явного преобразования к типу double (вычисление площади)
    operator double() const {
        return this->Area();
    }

    // Метод вычисления длины стороны фигуры
    double Length() const {
        Point p1 = this->_points[0], p2 = this->_points[1];

        return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
    }

    // Метод для получения количества вершин фигуры
    virtual std::size_t GetPointCount() const { return 0; }

    virtual std::string GetTypeName() const = 0;


    template<typename F> friend std::istream& operator>>(std::istream&, Figure<F>&);
    template<typename F> friend std::ostream& operator<<(std::ostream&, const Figure<F>&);
};


// Оператор чтения фигуры из потока
template<typename T>
std::istream& operator>>(std::istream& input, Figure<T>& obj) {
    obj._points.Clear();

    for (std::size_t i = 0; i < obj.GetPointCount(); ++i) {
        double coord_x, coord_y;
        input >> coord_x >> coord_y;

        obj._points.PushBack(Point<T>{ coord_x, coord_y });
    }

    return input;
}

// Оператор вывода фигуры в поток
template<typename T>
std::ostream& operator<<(std::ostream& output, const Figure<T>& obj) {
    for (std::size_t i = 0; i < obj.GetPointCount(); ++i) {
        output << obj._points[i].x << " " << obj._points[i].y << " ";
    }

    return output;
}