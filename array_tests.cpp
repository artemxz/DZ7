#include <gtest/gtest.h>
#include "ArrayContainer.h"

struct Trackable {
    static int destroy_count;
    int id;
    Trackable() : id(0) {}
    Trackable(int i) : id(i) {}
    ~Trackable() { destroy_count++; }

    // 🛠️ ДОБАВЛЕНО: Учим компилятор выводить Trackable на экран
    friend std::ostream& operator<<(std::ostream& os, const Trackable& t) {
        return os << "Trackable(" << t.id << ")";
    }
};
int Trackable::destroy_count = 0;

TEST(array, create) {
    ArrayContainer<int> arr;
    EXPECT_EQ(arr.size(), 0);
}


TEST(array, push_back) {
    ArrayContainer<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 20);
}


TEST(array, insert_begin) {
    ArrayContainer<int> arr;
    arr.push_back(20);
    arr.insert(0, 10);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr.size(), 2);
}


TEST(array, insert_middle) {
    ArrayContainer<int> arr;
    arr.push_back(10); arr.push_back(30);
    arr.insert(1, 20);
    EXPECT_EQ(arr[1], 20);
}

TEST(array, erase_end) {
    ArrayContainer<int> arr;
    arr.push_back(10); arr.push_back(20);
    arr.erase(1);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 10);
}


TEST(array, erase_begin) {
    ArrayContainer<int> arr;
    arr.push_back(10); arr.push_back(20);
    arr.erase(0);
    EXPECT_EQ(arr[0], 20);
}


TEST(array, erase_middle) {
    ArrayContainer<int> arr;
    arr.push_back(10); arr.push_back(20); arr.push_back(30);
    arr.erase(1);
    EXPECT_EQ(arr[1], 30);
}


TEST(array, get_and_size) {
    ArrayContainer<int> arr;
    arr.push_back(42);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}


TEST(array, destruct) {
    Trackable::destroy_count = 0;
    {
        ArrayContainer<Trackable> arr;
        arr.push_back(Trackable(1));
        arr.push_back(Trackable(2));
    }
    EXPECT_GE(Trackable::destroy_count, 2);  
}

TEST(array, move) {
    ArrayContainer<int> arr1;
    arr1.push_back(10);
    arr1.push_back(20);

    ArrayContainer<int> arr2 = std::move(arr1);

    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 10);
    EXPECT_EQ(arr1.size(), 0);
}

TEST(array, copy) {
    ArrayContainer<int> arr1;
    arr1.push_back(10);
    arr1.push_back(20);

    ArrayContainer<int> arr2 = arr1; 

    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 10);
    EXPECT_EQ(arr2[1], 20);
}