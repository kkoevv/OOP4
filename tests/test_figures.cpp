#include <gtest/gtest.h>
#include "octagon.h"
#include "triangle.h"
#include "square.h"

TEST(OctagonTest, Construction) {
    Octagon<int> oct(0, 0, 5);
    EXPECT_EQ(oct.geometric_center(), Point<int>(0, 0));
    EXPECT_EQ(oct.radius(), 5);
}

TEST(OctagonTest, Area) {
    Octagon<double> oct(0, 0, 1.0);
    double expected_area = 2.0 * 1.0 * 1.0 * std::sin(M_PI / 4.0); // формула площади
    EXPECT_NEAR(oct.area(), expected_area, 1e-9);
}

TEST(OctagonTest, Copy) {
    Octagon<int> oct1(1, 2, 3);
    Octagon<int> oct2 = oct1;
    EXPECT_TRUE(oct1 == oct2);
}

TEST(TriangleTest, Construction) {
    Triangle<int> tri(0, 0, 5);
    EXPECT_EQ(tri.geometric_center(), Point<int>(0, 0));
    EXPECT_EQ(tri.radius(), 5);
}

TEST(TriangleTest, Area) {
    Triangle<double> tri(0, 0, 1.0);
    double expected_area = (3.0 * std::sqrt(3.0) / 4.0) * 1.0 * 1.0;
    EXPECT_NEAR(tri.area(), expected_area, 1e-9);
}

TEST(SquareTest, Construction) {
    Square<int> sq(0, 0, 5);
    EXPECT_EQ(sq.geometric_center(), Point<int>(0, 0));
    EXPECT_EQ(sq.side(), 5);  // Исправлено: side() вместо radius()
}

TEST(SquareTest, Area) {
    Square<double> sq(0, 0, 2.0);
    double expected_area = 4.0; // 2.0 * 2.0
    EXPECT_NEAR(sq.area(), expected_area, 1e-9);
}

TEST(FigureTest, DoubleConversion) {
    Square<double> sq(0, 0, 2.0);
    double area = static_cast<double>(sq);
    EXPECT_NEAR(area, 4.0, 1e-9);
}

TEST(FigureTest, Clone) {
    Square<int> original(0, 0, 5);
    auto cloned = original.clone();
    EXPECT_NE(&original, cloned.get());
    EXPECT_TRUE(original == *cloned);
}

TEST(FigureTest, IsRotationFigure) {
    Octagon<int> oct(0, 0, 5);
    EXPECT_TRUE(oct.is_rotation_figure());
    
    Triangle<int> tri(0, 0, 3);
    EXPECT_TRUE(tri.is_rotation_figure());
    
    Square<int> sq(0, 0, 4);
    EXPECT_TRUE(sq.is_rotation_figure());
}

TEST(FigureTest, IsInscribedInCircle) {
    Octagon<int> oct(0, 0, 5);
    EXPECT_TRUE(oct.is_inscribed_in_circle());
    
    Square<int> sq(0, 0, 4);
    EXPECT_TRUE(sq.is_inscribed_in_circle());
}