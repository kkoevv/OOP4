#pragma once
#include <memory>
#include <iostream>
#include <utility>
#include <stdexcept>
#include "concept.h"  
#include "figure.h"

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
    
    void resize(size_t new_capacity) {
        std::shared_ptr<T[]> new_data(new T[new_capacity]);
        
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        
        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }
    
public:
    Array() : size_(0), capacity_(0) {}
    
    explicit Array(size_t initial_capacity) : size_(0), capacity_(initial_capacity) {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
    }
    
    // Конструктор копирования
    Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];  // Копирование
        }
    }
    
    // Конструктор перемещения
    Array(Array&& other) noexcept 
        : data_(std::move(other.data_)), 
          size_(other.size_), 
          capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    // Оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other);
            *this = std::move(temp);  // Используем move
        }
        return *this;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    void add(const T& item) {
        if (size_ >= capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = item;
    }
    
    void add(T&& item) {
        if (size_ >= capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = std::move(item);
    }
    
    void remove(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }
    
    T& operator[](size_t index) { 
        if (index >= size_) throw std::out_of_range("Array index out of range");
        return data_[index]; 
    }
    
    const T& operator[](size_t index) const { 
        if (index >= size_) throw std::out_of_range("Array index out of range");
        return data_[index]; 
    }
    
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    
    void clear() {
        size_ = 0;
    }
    
    // Итераторы
    T* begin() { return data_.get(); }
    T* end() { return data_.get() + size_; }
    const T* begin() const { return data_.get(); }
    const T* end() const { return data_.get() + size_; }
};

// Вспомогательные функции для фигур
template<Scalar T>
void print_figures_info(const Array<std::shared_ptr<Figure<T>>>& figures) {
    std::cout << "\nВсе фигуры (" << figures.size() << ") \n";
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "\n[" << i << "] " << *figures[i] << "\n";
    }
}

template<Scalar T>
double total_area(const Array<std::shared_ptr<Figure<T>>>& figures) {
    double total = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += figures[i]->area();
    }
    return total;
}