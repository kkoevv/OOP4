#include <iostream>
#include <limits>
#include <memory>
#include "point.h"
#include "figure.h"
#include "octagon.h"
#include "triangle.h"
#include "square.h"
#include "array.h"

// Функции для создания фигур
template<Scalar T>
std::shared_ptr<Figure<T>> create_octagon() {
    T x, y, radius;
    std::cout << "Введите центр 8-угольника (x y): ";
    std::cin >> x >> y;
    std::cout << "Введите радиус описанной окружности: ";
    std::cin >> radius;
    
    auto fig = std::make_shared<Octagon<T>>(x, y, radius);
    if (!fig->is_rotation_figure()) {
        std::cout << "Ошибка: это не правильный 8-угольник!\n";
        return nullptr;
    }
    return fig;
}

template<Scalar T>
std::shared_ptr<Figure<T>> create_triangle() {
    T x, y, radius;
    std::cout << "Введите центр треугольника (x y): ";
    std::cin >> x >> y;
    std::cout << "Введите радиус описанной окружности: ";
    std::cin >> radius;
    
    auto fig = std::make_shared<Triangle<T>>(x, y, radius);
    if (!fig->is_rotation_figure()) {
        std::cout << "Ошибка: это не равносторонний треугольник!\n";
        return nullptr;
    }
    return fig;
}

template<Scalar T>
std::shared_ptr<Figure<T>> create_square() {
    T x, y, side;
    std::cout << "Введите центр квадрата (x y): ";
    std::cin >> x >> y;
    std::cout << "Введите длину стороны: ";
    std::cin >> side;
    
    auto fig = std::make_shared<Square<T>>(x, y, side);
    if (!fig->is_inscribed_in_circle()) {
        std::cout << "Ошибка: квадрат не вписан в окружность!\n";
        return nullptr;
    }
    return fig;
}

// Демонстрация работы с Array<T> для базового типа
void demonstrate_array_figure() {
    std::cout << "\nдемонстрация: Array<Figure<int>>\n";
    
    Array<std::shared_ptr<Figure<int>>> figures;
    
    figures.add(std::make_shared<Octagon<int>>(0, 0, 5));
    figures.add(std::make_shared<Triangle<int>>(1, 1, 3));
    figures.add(std::make_shared<Square<int>>(2, 2, 4));
    
    std::cout << "Размер массива: " << figures.size() << "\n";
    std::cout << "Емкость массива: " << figures.capacity() << "\n";
    
    print_figures_info(figures);
    std::cout << "Общая площадь: " << total_area(figures) << "\n";
}

// Демонстрация работы с Array<T> для наследника
void demonstrate_array_square() {
    std::cout << "\nдемонстрация: Array<Square<double>>\n";
    
    Array<std::shared_ptr<Square<double>>> squares;
    
    squares.add(std::make_shared<Square<double>>(0.5, 0.5, 2.5));
    squares.add(std::make_shared<Square<double>>(1.5, 1.5, 3.5));
    squares.add(std::make_shared<Square<double>>(2.5, 2.5, 4.5));
    
    std::cout << "Количество квадратов: " << squares.size() << "\n";
    
    double total_square_area = 0;
    for (size_t i = 0; i < squares.size(); ++i) {
        std::cout << "Квадрат " << i + 1 << ": площадь = " 
                  << squares[i]->area() << ", сторона = " 
                  << squares[i]->side() << "\n";
        total_square_area += squares[i]->area();
    }
    std::cout << "Суммарная площадь квадратов: " << total_square_area << "\n";
}

void demonstrate_move_semantics() {
    std::cout << "\nдемонстрация Moveсемантики\n";
    
    Array<std::shared_ptr<Figure<int>>> small_array;
    small_array.add(std::make_shared<Square<int>>(0, 0, 2));
    small_array.add(std::make_shared<Triangle<int>>(1, 1, 3));
    
    std::cout << "До перемещения:\n";
    std::cout << "  small_array размер: " << small_array.size() 
              << ", емкость: " << small_array.capacity() << "\n";
    
    // Перемещение
    Array<std::shared_ptr<Figure<int>>> large_array = std::move(small_array);
    
    std::cout << "После перемещения:\n";
    std::cout << "  small_array размер: " << small_array.size() 
              << ", емкость: " << small_array.capacity() << "\n";
    std::cout << "  large_array размер: " << large_array.size() 
              << ", емкость: " << large_array.capacity() << "\n";
    
    // Добавляем больше элементов для демонстрации resize с move
    std::cout << "\nДобавляем элементы в large_array (будет увеличение емкости с move):\n";
    for (int i = 0; i < 10; ++i) {
        large_array.add(std::make_shared<Octagon<int>>(i, i, i+1));
    }
    std::cout << "  Итоговый размер: " << large_array.size() 
              << ", емкость: " << large_array.capacity() << "\n";
}

// Основное меню
template<Scalar T>
void interactive_menu() {
    Array<std::shared_ptr<Figure<T>>> figures;
    int choice;
    
    do {
        std::cout << "\nменю\n";
        std::cout << "1. Добавить 8-угольник\n";
        std::cout << "2. Добавить треугольник\n";
        std::cout << "3. Добавить квадрат\n";
        std::cout << "4. Показать все фигуры\n";
        std::cout << "5. Вычислить общую площадь\n";
        std::cout << "6. Удалить фигуру по индексу\n";
        std::cout << "7. Демонстрация Array<Figure<int>>\n";
        std::cout << "8. Демонстрация Array<Square<double>>\n";
        std::cout << "9. Демонстрация Move-семантики\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                auto fig = create_octagon<T>();
                if (fig) figures.add(fig);
                break;
            }
            case 2: {
                auto fig = create_triangle<T>();
                if (fig) figures.add(fig);
                break;
            }
            case 3: {
                auto fig = create_square<T>();
                if (fig) figures.add(fig);
                break;
            }
            case 4:
                print_figures_info(figures);
                break;
            case 5:
                std::cout << "Общая площадь: " << total_area(figures) << "\n";
                break;
            case 6: {
                size_t index;
                std::cout << "Введите индекс для удаления (0-" 
                          << (figures.size() > 0 ? figures.size()-1 : 0) << "): ";
                std::cin >> index;
                if (index < figures.size()) {
                    figures.remove(index);
                    std::cout << "Фигура удалена. Осталось: " << figures.size() << "\n";
                } else {
                    std::cout << "Неверный индекс!\n";
                }
                break;
            }
            case 7:
                demonstrate_array_figure();
                break;
            case 8:
                demonstrate_array_square();
                break;
            case 9:
                demonstrate_move_semantics();
                break;
            case 0:
                std::cout << "Выход...\n";
                break;
            default:
                std::cout << "Неверный выбор!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);
}

int main() {
    
    // Запускаем с типом double
    interactive_menu<double>();
    
    return 0;
}