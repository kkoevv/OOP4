#pragma once
#include "point.h"
#include "concept.h"
#include <memory>
#include <string>
#include <iostream>

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    
    // Обязательные методы
    virtual Point<T> geometric_center() const = 0;
    virtual double area() const = 0;
    virtual void print_vertices() const = 0;
    virtual std::shared_ptr<Figure<T>> clone() const = 0;
    virtual std::string name() const = 0;
    
    // Проверки из задания
    virtual bool is_rotation_figure() const = 0;
    virtual bool is_inscribed_in_circle() const = 0;
    
    // Операторы
    explicit operator double() const {
        return area();
    }
    
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual bool operator!=(const Figure<T>& other) const {
        return !(*this == other);
    }
    
    // Ввод/вывод
    virtual std::istream& read(std::istream& is) = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        os << fig.name() << ":\n";
        fig.print_vertices();
        os << "Center: " << fig.geometric_center() << "\n";
        os << "Area: " << fig.area();
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        return fig.read(is);
    }
};