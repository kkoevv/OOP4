
#include <gtest/gtest.h>
#include "../include/Array.h"

// Тесты конструкторов
TEST(ArrayConstructor, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.GetSize(), 0);
}

TEST(ArrayConstructor, SizeConstructor) {
    Array<int> arr(5);
    EXPECT_EQ(arr.GetSize(), 5);
    for(size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], 0);
    }
}

TEST(ArrayConstructor, SizeValueConstructor) {
    Array<int> arr(3, 42);
    EXPECT_EQ(arr.GetSize(), 3);
    for(size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(arr[i], 42);
    }
}

TEST(ArrayConstructor, InitializerListConstructor) {
    Array<int> arr{1, 2, 3, 4, 5};
    EXPECT_EQ(arr.GetSize(), 5);
    for(size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], i + 1);
    }
}

// Тесты копирования и перемещения
TEST(ArrayCopyMove, CopyConstructor) {
    Array<int> arr1{1, 2, 3};
    Array<int> arr2(arr1);
    EXPECT_EQ(arr2.GetSize(), 3);
    for(size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(arr2[i], arr1[i]);
    }
}

TEST(ArrayCopyMove, MoveConstructor) {
    Array<int> arr1{1, 2, 3};
    Array<int> arr2(std::move(arr1));
    EXPECT_EQ(arr2.GetSize(), 3);
    EXPECT_EQ(arr1.GetSize(), 0);
}

// Тесты методов изменения размера
TEST(ArrayResize, ResizeGrow) {
    Array<int> arr{1, 2, 3};
    arr.Resize(5);
    EXPECT_EQ(arr.GetSize(), 5);
    for(size_t i = 3; i < 5; ++i) {
        EXPECT_EQ(arr[i], 0);
    }
}

TEST(ArrayResize, ResizeShrink) {
    Array<int> arr{1, 2, 3, 4, 5};
    arr.Resize(3);
    EXPECT_EQ(arr.GetSize(), 3);
}

// Тесты операций добавления/удаления
TEST(ArrayOperations, PushBackAndPopBack) {
    Array<int> arr;
    arr.PushBack(1);
    EXPECT_EQ(arr.GetSize(), 1);
    EXPECT_EQ(arr[0], 1);
    
    int val = arr.PopBack();
    EXPECT_EQ(val, 1);
    EXPECT_EQ(arr.GetSize(), 0);
}

TEST(ArrayOperations, InsertAndRemove) {
    Array<int> arr{1, 2, 4, 5};
    arr.Insert(2, 3);
    EXPECT_EQ(arr.GetSize(), 5);
    for(size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], i + 1);
    }
    
    arr.Remove(2);
    EXPECT_EQ(arr.GetSize(), 4);
    EXPECT_EQ(arr[2], 4);
}

// Тесты исключений
TEST(ArrayExceptions, OutOfRange) {
    Array<int> arr{1, 2, 3};
    EXPECT_THROW(arr[5], std::out_of_range);
    EXPECT_THROW(arr.Remove(5), std::out_of_range);
    EXPECT_THROW(arr.Insert(5, 0), std::out_of_range);
}

TEST(ArrayExceptions, EmptyArray) {
    Array<int> arr;
    EXPECT_THROW(arr.PopBack(), std::out_of_range);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
