
#include "./include/Octagon.h"
#include "./include/Square.h"
#include "./include/Triangle.h"
#include "./include/Array.h"
#include "include/Figure.h"

#include <cstddef>
#include <iostream>
#include <memory>
#include <type_traits>


template<typename T, typename F>  
concept DerivedFromFigure = std::derived_from<F, Figure<T>>;

template<typename T, typename F>
requires DerivedFromFigure<T, F>
void printPoints(std::shared_ptr<F> figure) {
    std::cout << *figure << "\n\n";
}

template<typename T, typename F>
requires DerivedFromFigure<T, F>
void doOperations(Array<std::shared_ptr<F>> figures) {
    double total_area = 0.0;

    for (size_t i = 0; i < figures.GetSize(); ++i) {   //полим
        std::cout << "Сравниваем объекты типов " << figures[i]->GetTypeName()
                  << " и " << figures[(i + 1) % figures.GetSize()]->GetTypeName() << ": они ";
        std::cout << ((*figures[i] == *figures[(i + 1) % figures.GetSize()]) ? "Равны" : "НЕ равны") << "\n";

        Point p = figures[i]->GeometricCenter();
        std::cout << "Площадь фигуры " << figures[i]->GetTypeName() << " равна " 
                  << figures[i]->Area() << ", координаты её геометрического центра - X: " << p.x << " Y: " << p.y << "\n\n";

        total_area += figures[i]->Area();
    }

    // Выводим общую площадь всех трёх фигур.
    std::cout << "Общая площадь фигур в массиве: " << total_area << "\n";

    // Проверим функции удаления и добавления в массив по индексу.

    std::cout << "\nСейчас набор фигур в массиве такой:\n";
    for (size_t i = 0; i < figures.GetSize(); ++i) {
        std::cout << i + 1 << ") " << figures[i]->GetTypeName() << " ";
    }
    std::cout << "\n";

    // Удаляем вторую фигуру
    std::cout << "\nУдаляем фигуру номер 2 (индекс 1)\n";
    std::shared_ptr<F> tmp = figures[1];
    figures.Remove(1);

    std::cout << "\nТеперь набор фигур в массиве выглядит так:\n";
    for (size_t i = 0; i < figures.GetSize(); ++i) {
        std::cout << i + 1 << ") " << figures[i]->GetTypeName()  << " ";
    }

    // Добавляем удаленную фигуру в начало массива
    std::cout << "\n\nДобавляем удаленную фигуру в самое начало массива (индекс 0)\n";
    figures.Insert(0, tmp);

    std::cout << "Теперь набор фигур в массиве такой:\n";
    for (size_t i = 0; i < figures.GetSize(); ++i) {
        std::cout << i + 1 << ") " << figures[i]->GetTypeName() << "\n ";
    }
    
}

int main() {
    // Инициализурем массив фигур с координатами вершин типа int
    Array<std::shared_ptr<Figure<int>>> figures_ints {
        std::make_shared<Triangle<int>>(Triangle<int>{ 
            Point<int>{0, 0}, Point<int>{4, 0}, Point<int>{0, 3} 
        }),
        std::make_shared<Square<int>>(Square<int>{
            Point<int>{0, 0}, Point<int>{0, 2}, Point<int>{2, 2}, Point<int>{2, 0}
        }),
        std::make_shared<Octagon<int>>(Octagon<int>{
            Point<int>{1, 0}, Point<int>{2, 0}, Point<int>{3, 1}, Point<int>{3, 2},
            Point<int>{2, 3}, Point<int>{1, 3}, Point<int>{0, 2}, Point<int>{0, 1}
        })
    };

    // Инициализируем массив фигур с координатами вершин типа double
    Array<std::shared_ptr<Figure<double>>> figures_doubles {
        std::make_shared<Triangle<double>>(Triangle<double>{ 
            Point<double>{ 0.0, 0.0}, Point<double>{4.5, 0.0}, Point<double>{0.0, 3.5} 
        }),
        std::make_shared<Square<double>>(Square<double>{
            Point<double>{0.0, 0.0}, Point<double>{0.0, 2.5}, Point<double>{2.5, 2.5}, Point<double>{2.5, 0.0}
        }),
        std::make_shared<Octagon<double>>(Octagon<double>{
            Point<double>{1.0, 0.0}, Point<double>{2.5, 0.0}, Point<double>{3.5, 1.0}, Point<double>{3.5, 2.5},
            Point<double>{2.5, 3.5}, Point<double>{1.0, 3.5}, Point<double>{0.0, 2.5}, Point<double>{0.0, 1.0}
        })
    };

    Array<std::shared_ptr<Square<double>>> squares_doubles {
        std::make_shared<Square<double>>(Square<double>{
            Point<double>{0.0, 0.0}, Point<double>{0.0, 3.0}, Point<double>{3.0, 3.0}, Point<double>{3.0, 0.0}
        }),
        std::make_shared<Square<double>>(Square<double>{
            Point<double>{1.0, 1.0}, Point<double>{1.0, 4.0}, Point<double>{4.0, 4.0}, Point<double>{4.0, 1.0}
        }),
        std::make_shared<Square<double>>(Square<double>{
            Point<double>{2.0, 2.0}, Point<double>{2.0, 5.0}, Point<double>{5.0, 5.0}, Point<double>{5.0, 2.0}
        })
    };

    std::cout << "Продемонстрируем работу основных функций для фигур с координатами типа int:\n\n";
    doOperations<int, Figure<int>>(figures_ints);

    std::cout << "Продемонстрируем работу основных функций для фигур с координатами типа double:\n\n";
    doOperations<double, Figure<double>>(figures_doubles);

    std::cout << "Продемонстрируем работу основных функций для квадратов с координатами типа double:\n\n";
    doOperations<double, Square<double>>(squares_doubles);

    return 0;
}
