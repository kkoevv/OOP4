#include <gtest/gtest.h>
#include "../include/Triangle.h"
#include "../include/Square.h"
#include "../include/Octagon.h"
#include <cmath>
#include <memory>

// Вспомогательная функция для сравнения double с допуском
bool IsEqual(double a, double b, double epsilon = 1e-6) {
    return std::fabs(a - b) < epsilon;
}

// тесты triangle
// Тесты конструкторов Triangle
TEST(TriangleConstructor, DefaultConstructorInt) {
    Triangle<int> triangle;
    EXPECT_EQ(triangle.GetPointCount(), 3);
}

TEST(TriangleConstructor, DefaultConstructorFloat) {
    Triangle<float> triangle;
    EXPECT_EQ(triangle.GetPointCount(), 3);
}

TEST(TriangleConstructor, DefaultConstructorDouble) {
    Triangle<double> triangle;
    EXPECT_EQ(triangle.GetPointCount(), 3);
}

TEST(TriangleConstructor, ParameterizedConstructorInt) {
    Triangle<int> triangle(
        Point<int>{0, 0},
        Point<int>{4, 0},
        Point<int>{0, 3}
    );
    EXPECT_EQ(triangle.GetPointCount(), 3);
}

TEST(TriangleConstructor, ParameterizedConstructorDouble) {
    Triangle<double> triangle(
        Point<double>{0.0, 0.0},
        Point<double>{4.0, 0.0},
        Point<double>{0.0, 3.0}
    );
    EXPECT_EQ(triangle.GetPointCount(), 3);
}

TEST(TriangleConstructor, ParameterizedConstructorFloat) {
    Triangle<float> triangle(
        Point<float>{0.0f, 0.0f},
        Point<float>{4.0f, 0.0f},
        Point<float>{0.0f, 3.0f}
    );
    EXPECT_EQ(triangle.GetPointCount(), 3);
}

// Тесты копирования Triangle
TEST(TriangleCopyMove, CopyConstructorInt) {
    Triangle<int> triangle1(
        Point<int>{0, 0},
        Point<int>{4, 0},
        Point<int>{0, 3}
    );
    Triangle<int> triangle2(triangle1);
    EXPECT_EQ(triangle2.GetPointCount(), 3);
    EXPECT_TRUE(triangle1 == triangle2);
}

TEST(TriangleCopyMove, CopyConstructorDouble) {
    Triangle<double> triangle1(
        Point<double>{0.0, 0.0},
        Point<double>{4.5, 0.0},
        Point<double>{0.0, 3.5}
    );
    Triangle<double> triangle2(triangle1);
    EXPECT_EQ(triangle2.GetPointCount(), 3);
    EXPECT_TRUE(triangle1 == triangle2);
}

// Тесты перемещения Triangle
TEST(TriangleCopyMove, MoveConstructorInt) {
    Triangle<int> triangle1(
        Point<int>{0, 0},
        Point<int>{4, 0},
        Point<int>{0, 3}
    );
    Triangle<int> triangle2(std::move(triangle1));
    EXPECT_EQ(triangle2.GetPointCount(), 3);
}

// Тесты площади Triangle
TEST(TriangleArea, AreaCalculationInt) {
    Triangle<int> triangle(
        Point<int>{0, 0},
        Point<int>{2, 0},
        Point<int>{1, 2}
    );
    double length = 2.0;
    double expected_area = std::sqrt(3) * std::pow(length, 2) / 4.0;
    EXPECT_TRUE(IsEqual(triangle.Area(), expected_area));
}

TEST(TriangleArea, AreaCalculationDouble) {
    Triangle<double> triangle(
        Point<double>{0.0, 0.0},
        Point<double>{2.0, 0.0},
        Point<double>{1.0, std::sqrt(3)}
    );
    double length = 2.0;
    double expected_area = std::sqrt(3) * std::pow(length, 2) / 4.0;
    EXPECT_TRUE(IsEqual(triangle.Area(), expected_area));
}

TEST(TriangleArea, AreaCalculationFloat) {
    Triangle<float> triangle(
        Point<float>{0.0f, 0.0f},
        Point<float>{4.0f, 0.0f},
        Point<float>{2.0f, (float)(2.0f * std::sqrt(3.0f))}
    );
    double length = 4.0;
    double expected_area = std::sqrt(3) * std::pow(length, 2) / 4.0;
    EXPECT_TRUE(IsEqual(triangle.Area(), expected_area, 1e-3));
}

// Тесты геометрического центра Triangle
TEST(TriangleGeometricCenter, CenterInt) {
    Triangle<int> triangle(
        Point<int>{0, 0},
        Point<int>{3, 0},
        Point<int>{0, 3}
    );
    Point<int> center = triangle.GeometricCenter();
    EXPECT_EQ(center.x, 1);
    EXPECT_EQ(center.y, 1);
}

TEST(TriangleGeometricCenter, CenterDouble) {
    Triangle<double> triangle(
        Point<double>{0.0, 0.0},
        Point<double>{3.0, 0.0},
        Point<double>{0.0, 3.0}
    );
    Point<double> center = triangle.GeometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

// Тесты оператора сравнения Triangle
TEST(TriangleComparison, EqualTrianglesInt) {
    Triangle<int> triangle1(
        Point<int>{0, 0},
        Point<int>{4, 0},
        Point<int>{0, 3}
    );
    Triangle<int> triangle2(
        Point<int>{0, 0},
        Point<int>{4, 0},
        Point<int>{0, 3}
    );
    EXPECT_TRUE(triangle1 == triangle2);
}

TEST(TriangleComparison, NotEqualTrianglesInt) {
    Triangle<int> triangle1(
        Point<int>{0, 0},
        Point<int>{4, 0},
        Point<int>{0, 3}
    );
    Triangle<int> triangle2(
        Point<int>{0, 0},
        Point<int>{3, 0},
        Point<int>{0, 2}
    );
    EXPECT_FALSE(triangle1 == triangle2);
}

// Тесты типа Triangle
TEST(TriangleTypeName, GetTypeNameInt) {
    Triangle<int> triangle;
    EXPECT_EQ(triangle.GetTypeName(), "Triangle");
}

TEST(TriangleTypeName, GetTypeNameDouble) {
    Triangle<double> triangle;
    EXPECT_EQ(triangle.GetTypeName(), "Triangle");
}

// тесты square
// Тесты конструкторов Square
TEST(SquareConstructor, DefaultConstructorInt) {
    Square<int> square;
    EXPECT_EQ(square.GetPointCount(), 4);
}

TEST(SquareConstructor, DefaultConstructorFloat) {
    Square<float> square;
    EXPECT_EQ(square.GetPointCount(), 4);
}

TEST(SquareConstructor, DefaultConstructorDouble) {
    Square<double> square;
    EXPECT_EQ(square.GetPointCount(), 4);
}

TEST(SquareConstructor, ParameterizedConstructorInt) {
    Square<int> square(
        Point<int>{0, 0},
        Point<int>{0, 2},
        Point<int>{2, 2},
        Point<int>{2, 0}
    );
    EXPECT_EQ(square.GetPointCount(), 4);
}

TEST(SquareConstructor, ParameterizedConstructorDouble) {
    Square<double> square(
        Point<double>{0.0, 0.0},
        Point<double>{0.0, 2.5},
        Point<double>{2.5, 2.5},
        Point<double>{2.5, 0.0}
    );
    EXPECT_EQ(square.GetPointCount(), 4);
}

TEST(SquareConstructor, ParameterizedConstructorFloat) {
    Square<float> square(
        Point<float>{0.0f, 0.0f},
        Point<float>{0.0f, 3.0f},
        Point<float>{3.0f, 3.0f},
        Point<float>{3.0f, 0.0f}
    );
    EXPECT_EQ(square.GetPointCount(), 4);
}

// Тесты копирования Square
TEST(SquareCopyMove, CopyConstructorInt) {
    Square<int> square1(
        Point<int>{0, 0},
        Point<int>{0, 2},
        Point<int>{2, 2},
        Point<int>{2, 0}
    );
    Square<int> square2(square1);
    EXPECT_EQ(square2.GetPointCount(), 4);
    EXPECT_TRUE(square1 == square2);
}

TEST(SquareCopyMove, CopyConstructorDouble) {
    Square<double> square1(
        Point<double>{0.0, 0.0},
        Point<double>{0.0, 2.5},
        Point<double>{2.5, 2.5},
        Point<double>{2.5, 0.0}
    );
    Square<double> square2(square1);
    EXPECT_EQ(square2.GetPointCount(), 4);
    EXPECT_TRUE(square1 == square2);
}

// Тесты перемещения Square
TEST(SquareCopyMove, MoveConstructorInt) {
    Square<int> square1(
        Point<int>{0, 0},
        Point<int>{0, 2},
        Point<int>{2, 2},
        Point<int>{2, 0}
    );
    Square<int> square2(std::move(square1));
    EXPECT_EQ(square2.GetPointCount(), 4);
}

// Тесты площади Square
TEST(SquareArea, AreaCalculationInt) {
    Square<int> square(
        Point<int>{0, 0},
        Point<int>{0, 2},
        Point<int>{2, 2},
        Point<int>{2, 0}
    );
    double expected_area = std::pow(2.0, 2); // length = 2
    EXPECT_TRUE(IsEqual(square.Area(), expected_area));
}

TEST(SquareArea, AreaCalculationDouble) {
    Square<double> square(
        Point<double>{0.0, 0.0},
        Point<double>{0.0, 3.0},
        Point<double>{3.0, 3.0},
        Point<double>{3.0, 0.0}
    );
    double expected_area = std::pow(3.0, 2);
    EXPECT_TRUE(IsEqual(square.Area(), expected_area));
}

TEST(SquareArea, AreaCalculationFloat) {
    Square<float> square(
        Point<float>{0.0f, 0.0f},
        Point<float>{0.0f, 2.5f},
        Point<float>{2.5f, 2.5f},
        Point<float>{2.5f, 0.0f}
    );
    double expected_area = std::pow(2.5, 2);
    EXPECT_TRUE(IsEqual(square.Area(), expected_area, 1e-4));
}

// Тесты геометрического центра Square
TEST(SquareGeometricCenter, CenterInt) {
    Square<int> square(
        Point<int>{0, 0},
        Point<int>{0, 4},
        Point<int>{4, 4},
        Point<int>{4, 0}
    );
    Point<int> center = square.GeometricCenter();
    EXPECT_EQ(center.x, 2);
    EXPECT_EQ(center.y, 2);
}

TEST(SquareGeometricCenter, CenterDouble) {
    Square<double> square(
        Point<double>{0.0, 0.0},
        Point<double>{0.0, 2.0},
        Point<double>{2.0, 2.0},
        Point<double>{2.0, 0.0}
    );
    Point<double> center = square.GeometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

// Тесты оператора сравнения Square
TEST(SquareComparison, EqualSquaresInt) {
    Square<int> square1(
        Point<int>{0, 0},
        Point<int>{0, 2},
        Point<int>{2, 2},
        Point<int>{2, 0}
    );
    Square<int> square2(
        Point<int>{0, 0},
        Point<int>{0, 2},
        Point<int>{2, 2},
        Point<int>{2, 0}
    );
    EXPECT_TRUE(square1 == square2);
}

TEST(SquareComparison, NotEqualSquaresInt) {
    Square<int> square1(
        Point<int>{0, 0},
        Point<int>{0, 2},
        Point<int>{2, 2},
        Point<int>{2, 0}
    );
    Square<int> square2(
        Point<int>{0, 0},
        Point<int>{0, 3},
        Point<int>{3, 3},
        Point<int>{3, 0}
    );
    EXPECT_FALSE(square1 == square2);
}

// Тесты типа Square
TEST(SquareTypeName, GetTypeNameInt) {
    Square<int> square;
    EXPECT_EQ(square.GetTypeName(), "Square");
}

TEST(SquareTypeName, GetTypeNameDouble) {
    Square<double> square;
    EXPECT_EQ(square.GetTypeName(), "Square");
}

// ============================================================================
// ТЕСТЫ Octagon
// ============================================================================

// Тесты конструкторов Octagon
TEST(OctagonConstructor, DefaultConstructorInt) {
    Octagon<int> octagon;
    EXPECT_EQ(octagon.GetPointCount(), 8);
}

TEST(OctagonConstructor, DefaultConstructorFloat) {
    Octagon<float> octagon;
    EXPECT_EQ(octagon.GetPointCount(), 8);
}

TEST(OctagonConstructor, DefaultConstructorDouble) {
    Octagon<double> octagon;
    EXPECT_EQ(octagon.GetPointCount(), 8);
}

TEST(OctagonConstructor, ParameterizedConstructorInt) {
    Octagon<int> octagon(
        Point<int>{1, 0}, Point<int>{2, 0}, Point<int>{3, 1}, Point<int>{3, 2},
        Point<int>{2, 3}, Point<int>{1, 3}, Point<int>{0, 2}, Point<int>{0, 1}
    );
    EXPECT_EQ(octagon.GetPointCount(), 8);
}

TEST(OctagonConstructor, ParameterizedConstructorDouble) {
    Octagon<double> octagon(
        Point<double>{1.0, 0.0}, Point<double>{2.5, 0.0}, Point<double>{3.5, 1.0}, Point<double>{3.5, 2.5},
        Point<double>{2.5, 3.5}, Point<double>{1.0, 3.5}, Point<double>{0.0, 2.5}, Point<double>{0.0, 1.0}
    );
    EXPECT_EQ(octagon.GetPointCount(), 8);
}

TEST(OctagonConstructor, ParameterizedConstructorFloat) {
    Octagon<float> octagon(
        Point<float>{1.0f, 0.0f}, Point<float>{2.0f, 0.0f}, Point<float>{3.0f, 1.0f}, Point<float>{3.0f, 2.0f},
        Point<float>{2.0f, 3.0f}, Point<float>{1.0f, 3.0f}, Point<float>{0.0f, 2.0f}, Point<float>{0.0f, 1.0f}
    );
    EXPECT_EQ(octagon.GetPointCount(), 8);
}

// Тесты копирования Octagon
TEST(OctagonCopyMove, CopyConstructorInt) {
    Octagon<int> octagon1(
        Point<int>{1, 0}, Point<int>{2, 0}, Point<int>{3, 1}, Point<int>{3, 2},
        Point<int>{2, 3}, Point<int>{1, 3}, Point<int>{0, 2}, Point<int>{0, 1}
    );
    Octagon<int> octagon2(octagon1);
    EXPECT_EQ(octagon2.GetPointCount(), 8);
    EXPECT_TRUE(octagon1 == octagon2);
}

TEST(OctagonCopyMove, CopyConstructorDouble) {
    Octagon<double> octagon1(
        Point<double>{1.0, 0.0}, Point<double>{2.5, 0.0}, Point<double>{3.5, 1.0}, Point<double>{3.5, 2.5},
        Point<double>{2.5, 3.5}, Point<double>{1.0, 3.5}, Point<double>{0.0, 2.5}, Point<double>{0.0, 1.0}
    );
    Octagon<double> octagon2(octagon1);
    EXPECT_EQ(octagon2.GetPointCount(), 8);
    EXPECT_TRUE(octagon1 == octagon2);
}

// Тесты перемещения Octagon
TEST(OctagonCopyMove, MoveConstructorInt) {
    Octagon<int> octagon1(
        Point<int>{1, 0}, Point<int>{2, 0}, Point<int>{3, 1}, Point<int>{3, 2},
        Point<int>{2, 3}, Point<int>{1, 3}, Point<int>{0, 2}, Point<int>{0, 1}
    );
    Octagon<int> octagon2(std::move(octagon1));
    EXPECT_EQ(octagon2.GetPointCount(), 8);
}

// Тесты площади Octagon
TEST(OctagonArea, AreaCalculationInt) {
    Octagon<int> octagon(
        Point<int>{1, 0}, Point<int>{2, 0}, Point<int>{3, 1}, Point<int>{3, 2},
        Point<int>{2, 3}, Point<int>{1, 3}, Point<int>{0, 2}, Point<int>{0, 1}
    );
    double length = 1.0; // Distance between (1,0) and (2,0)
    double expected_area = 2.0 * (1.0 + std::sqrt(2)) * std::pow(length, 2);
    EXPECT_TRUE(IsEqual(octagon.Area(), expected_area));
}

TEST(OctagonArea, AreaCalculationDouble) {
    Octagon<double> octagon(
        Point<double>{0.0, 0.0}, Point<double>{1.0, 0.0}, Point<double>{2.0, 1.0}, Point<double>{2.0, 2.0},
        Point<double>{1.0, 3.0}, Point<double>{0.0, 3.0}, Point<double>{-1.0, 2.0}, Point<double>{-1.0, 1.0}
    );
    double length = 1.0; // Distance between (0,0) and (1,0)
    double expected_area = 2.0 * (1.0 + std::sqrt(2)) * std::pow(length, 2);
    EXPECT_TRUE(IsEqual(octagon.Area(), expected_area));
}

TEST(OctagonArea, AreaCalculationFloat) {
    Octagon<float> octagon(
        Point<float>{0.0f, 0.0f}, Point<float>{2.0f, 0.0f}, Point<float>{4.0f, 2.0f}, Point<float>{4.0f, 4.0f},
        Point<float>{2.0f, 6.0f}, Point<float>{0.0f, 6.0f}, Point<float>{-2.0f, 4.0f}, Point<float>{-2.0f, 2.0f}
    );
    double length = 2.0; // Distance between (0,0) and (2,0)
    double expected_area = 2.0 * (1.0 + std::sqrt(2)) * std::pow(length, 2);
    EXPECT_TRUE(IsEqual(octagon.Area(), expected_area, 1e-4));
}

// Тесты геометрического центра Octagon
TEST(OctagonGeometricCenter, CenterInt) {
    Octagon<int> octagon(
        Point<int>{1, 0}, Point<int>{2, 0}, Point<int>{3, 1}, Point<int>{3, 2},
        Point<int>{2, 3}, Point<int>{1, 3}, Point<int>{0, 2}, Point<int>{0, 1}
    );
    Point<int> center = octagon.GeometricCenter();
    EXPECT_EQ(center.x, 1);
    EXPECT_EQ(center.y, 1);
}

TEST(OctagonGeometricCenter, CenterDouble) {
    Octagon<double> octagon(
        Point<double>{1.0, 0.0}, Point<double>{2.0, 0.0}, Point<double>{3.0, 1.0}, Point<double>{3.0, 2.0},
        Point<double>{2.0, 3.0}, Point<double>{1.0, 3.0}, Point<double>{0.0, 2.0}, Point<double>{0.0, 1.0}
    );
    Point<double> center = octagon.GeometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 1.5);
    EXPECT_DOUBLE_EQ(center.y, 1.5);
}

// Тесты оператора сравнения Octagon
TEST(OctagonComparison, EqualOctagonsInt) {
    Octagon<int> octagon1(
        Point<int>{1, 0}, Point<int>{2, 0}, Point<int>{3, 1}, Point<int>{3, 2},
        Point<int>{2, 3}, Point<int>{1, 3}, Point<int>{0, 2}, Point<int>{0, 1}
    );
    Octagon<int> octagon2(
        Point<int>{1, 0}, Point<int>{2, 0}, Point<int>{3, 1}, Point<int>{3, 2},
        Point<int>{2, 3}, Point<int>{1, 3}, Point<int>{0, 2}, Point<int>{0, 1}
    );
    EXPECT_TRUE(octagon1 == octagon2);
}

TEST(OctagonComparison, NotEqualOctagonsInt) {
    Octagon<int> octagon1(
        Point<int>{1, 0}, Point<int>{2, 0}, Point<int>{3, 1}, Point<int>{3, 2},
        Point<int>{2, 3}, Point<int>{1, 3}, Point<int>{0, 2}, Point<int>{0, 1}
    );
    Octagon<int> octagon2(
        Point<int>{2, 0}, Point<int>{3, 0}, Point<int>{4, 1}, Point<int>{4, 2},
        Point<int>{3, 3}, Point<int>{2, 3}, Point<int>{1, 2}, Point<int>{1, 1}
    );
    EXPECT_FALSE(octagon1 == octagon2);
}

// Тесты типа Octagon
TEST(OctagonTypeName, GetTypeNameInt) {
    Octagon<int> octagon;
    EXPECT_EQ(octagon.GetTypeName(), "Octagon");
}

TEST(OctagonTypeName, GetTypeNameDouble) {
    Octagon<double> octagon;
    EXPECT_EQ(octagon.GetTypeName(), "Octagon");
}

//тесты операторов преобразования
TEST(ConversionOperators, TriangleDoubleConversionInt) {
    Triangle<int> triangle(
        Point<int>{0, 0},
        Point<int>{4, 0},
        Point<int>{0, 3}
    );
    double area = (double)triangle;
    EXPECT_TRUE(IsEqual(area, triangle.Area()));
}

TEST(ConversionOperators, SquareDoubleConversionDouble) {
    Square<double> square(
        Point<double>{0.0, 0.0},
        Point<double>{0.0, 2.0},
        Point<double>{2.0, 2.0},
        Point<double>{2.0, 0.0}
    );
    double area = (double)square;
    EXPECT_TRUE(IsEqual(area, 4.0));
}

TEST(ConversionOperators, OctagonDoubleConversionFloat) {
    Octagon<float> octagon(
        Point<float>{0.0f, 0.0f}, Point<float>{1.0f, 0.0f}, Point<float>{2.0f, 1.0f}, Point<float>{2.0f, 2.0f},
        Point<float>{1.0f, 3.0f}, Point<float>{0.0f, 3.0f}, Point<float>{-1.0f, 2.0f}, Point<float>{-1.0f, 1.0f}
    );
    double area = (double)octagon;
    EXPECT_TRUE(IsEqual(area, octagon.Area(), 1e-4));
}

//тесты операторов клонирования 

TEST(AssignmentOperators, TriangleCopyAssignmentInt) {
    Triangle<int> triangle1(
        Point<int>{0, 0},
        Point<int>{4, 0},
        Point<int>{0, 3}
    );
    Triangle<int> triangle2(
        Point<int>{1, 1},
        Point<int>{5, 1},
        Point<int>{1, 4}
    );
    triangle2 = triangle1;
    EXPECT_TRUE(triangle1 == triangle2);
}

TEST(AssignmentOperators, SquareMoveAssignmentDouble) {
    Square<double> square1(
        Point<double>{0.0, 0.0},
        Point<double>{0.0, 2.0},
        Point<double>{2.0, 2.0},
        Point<double>{2.0, 0.0}
    );
    Square<double> square2;
    square2 = std::move(square1);
    EXPECT_EQ(square2.GetPointCount(), 4);
}


// ИНТЕГРАЦИОННЫЕ ТЕСТЫ


TEST(Integration, MultipleShapesWithDifferentTypes) {
    // Проверяем, что различные типы фигур работают корректно
    Triangle<int> tri_int(Point<int>{0, 0}, Point<int>{4, 0}, Point<int>{0, 3});
    Square<double> sq_double(
        Point<double>{0.0, 0.0},
        Point<double>{0.0, 2.0},
        Point<double>{2.0, 2.0},
        Point<double>{2.0, 0.0}
    );
    Octagon<float> oct_float(
        Point<float>{0.0f, 0.0f}, Point<float>{1.0f, 0.0f}, Point<float>{2.0f, 1.0f}, Point<float>{2.0f, 2.0f},
        Point<float>{1.0f, 3.0f}, Point<float>{0.0f, 3.0f}, Point<float>{-1.0f, 2.0f}, Point<float>{-1.0f, 1.0f}
    );

    EXPECT_EQ(tri_int.GetPointCount(), 3);
    EXPECT_EQ(sq_double.GetPointCount(), 4);
    EXPECT_EQ(oct_float.GetPointCount(), 8);

    EXPECT_EQ(tri_int.GetTypeName(), "Triangle");
    EXPECT_EQ(sq_double.GetTypeName(), "Square");
    EXPECT_EQ(oct_float.GetTypeName(), "Octagon");
}

TEST(Integration, SharedPointerWithPolymorphism) {
    std::shared_ptr<Figure<double>> tri =
        std::make_shared<Triangle<double>>(
            Point<double>{0.0, 0.0},
            Point<double>{4.0, 0.0},
            Point<double>{0.0, 3.0}
        );
    std::shared_ptr<Figure<double>> sq =
        std::make_shared<Square<double>>(
            Point<double>{0.0, 0.0},
            Point<double>{0.0, 3.0},
            Point<double>{3.0, 3.0},
            Point<double>{3.0, 0.0}
        );
    std::shared_ptr<Figure<double>> oct =
        std::make_shared<Octagon<double>>(
            Point<double>{0.0, 0.0}, Point<double>{1.0, 0.0}, Point<double>{2.0, 1.0}, Point<double>{2.0, 2.0},
            Point<double>{1.0, 3.0}, Point<double>{0.0, 3.0}, Point<double>{-1.0, 2.0}, Point<double>{-1.0, 1.0}
        );

    double total_area = tri->Area() + sq->Area() + oct->Area();
    EXPECT_GT(total_area, 0.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}