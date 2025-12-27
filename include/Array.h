#pragma once

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <type_traits>

template<typename T>
concept HasDefaultConstructor = std::is_default_constructible_v<T>; //есть ли у т конструктор по ум

template<typename T>
requires HasDefaultConstructor<T>
class Array {
private:
    // Указатель на динамический массив символов
    std::shared_ptr<T[]> data_ptr = nullptr;

    // Размер массива
    std::size_t size = 0;
    std::size_t capacity = 0;
public:
    // Конструктор по умолчанию
    Array() { }

    // Конструктор с размером
    Array(std::size_t size) { //масс зад разм
        this->Resize(size);
    }

    // Конструктор с размером и значением по умолчанию
    Array(std::size_t size, T default_val) {
        this->Resize(size);

        for (std::size_t i = 0; i < this->size; ++i) {
            this->data_ptr[i] = default_val;
        }
    }

    // Конструктор из параметров инициализации
    Array(std::initializer_list<T> params) {
        if (params.size() > 0) {
            this->Resize(params.size());

            std::size_t i = 0;
            for (auto elem : params) {
                this->data_ptr[i] = std::move(elem);
                ++i;
            }
        }
    }

    // Конструктор копирования
    Array(const Array& other) {
        if (this != &other) {
            this->Resize(other.size);
            
            for (std::size_t i = 0; i < this->size; ++i) {
                this->data_ptr[i] = other.data_ptr[i];
            }
        }
    }

    // Конструктор перемещения
    Array(Array&& other) noexcept {
        if (this != &other) {
            this->data_ptr = other.data_ptr;
            this->size = other.size;
            this->capacity = other.capacity;

            other.data_ptr = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
    }

    // Деструктор
    ~Array() {
        this->size = this->capacity = 0;
    }

    // Операторы индексирования (изменения элемента)
    T& operator[](std::size_t idx) {
        if (idx >= this->size) {  
            throw std::out_of_range("Array index out of range");
        }

        return this->data_ptr[idx];
    }

    // Операторы индексирования (получение элемента)
    const T& operator[](std::size_t idx) const {
        if (idx >= this->size) {  
            throw std::out_of_range("Array index out of range");
        }

        return this->data_ptr[idx];
    }

    // Метод резервирования памяти
    void Reserve(std::size_t new_capacity) {
        if (new_capacity <= this->capacity) {
            return;
        }

        this->capacity = new_capacity;
        std::shared_ptr<T[]> new_mem(new T[this->capacity]);

        for (std::size_t i = 0; i < this->size; ++i) {
            new_mem[i] = std::move(this->data_ptr[i]); //перемещаем в нов
        }

        this->data_ptr = new_mem;    
    }

    // Метод изменения размера
    void Resize(std::size_t new_size) {
        if (new_size < this->size) {
            for (std::size_t i = new_size; i < this->size; ++i) {
                this->data_ptr[i] = T{}; //деструктор через присв
            }
        }

        if (new_size > this->capacity) { //разверт
            this->Reserve(std::max(new_size, this->capacity * 2));
        }

        if (new_size > this->size) {
            for (std::size_t i = this->size; i < new_size; ++i) {
                this->data_ptr[i] = T{}; //констр
            }
        }

        this->size = new_size;
    }

    // Оператор копирования
    Array<T>& operator=(const Array<T>& other) {
        if (this != &other) {
            this->Resize(other.size);
            
            for (std::size_t i = 0; i < this->size; ++i) {
                this->data_ptr[i] = other.data_ptr[i];
            }
        }

        return *this;
    }

    // Оператор перемещения
    Array<T>& operator=(Array<T>&& other) noexcept {
        if (this != &other) {
            this->data_ptr = other.data_ptr;
            this->size = other.size;
            this->capacity = other.capacity;

            other.data_ptr = nullptr;
            other.size = 0;
            other.capacity = 0;
        }

        return *this;
    }

    // Метод получения размера
    std::size_t GetSize() const {
        return this->size;
    }

    // Методы добавления в конец
    void PushBack(T val) {
        this->Resize(this->size + 1);
        this->data_ptr[this->size - 1] = val;
    }

    // Метод удаления из конца
    T PopBack() {
        if (this->size == 0) {
            throw std::out_of_range("Array is empty");
        }

        --this->size;
        return this->data_ptr[this->size];
    }

    // Метод вставки по индексу
    void Insert(std::size_t pos, T val) {
        if (pos > this->size) {
            throw std::out_of_range("Position is out of range");
        }

        this->Resize(this->size + 1);

        for (std::size_t i = this->size - 1; i > pos; --i) {
            this->data_ptr[i] = std::move(this->data_ptr[i - 1]);
        } //сдв пр

        this->data_ptr[pos] = val;
    }

    // Метод удаления по индексу
    void Remove(std::size_t pos) {
        if (pos >= this->size) {  // 
            throw std::out_of_range("Position is out of range");
        }

        for (std::size_t i = pos; i < this->size - 1; ++i) {
            this->data_ptr[i] = std::move(this->data_ptr[i + 1]);
        } //сдвиг эл вправо

        this->Resize(this->size - 1);
    }

    // Метод очистки массива
    void Clear() {
        for (std::size_t i = 0; i < this->size; ++i) {
            this->data_ptr[i] = T{};
        }

        this->size = 0;
    }
};