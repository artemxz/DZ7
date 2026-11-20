#include <gtest/gtest.h>
#include "OneWayList.h"

struct TrackableList {
    static int destroy_count;
    int id;
    TrackableList() : id(0) {}
    TrackableList(int i) : id(i) {}
    ~TrackableList() { destroy_count++; }

    friend std::ostream& operator<<(std::ostream& os, const TrackableList& t) {
        return os << "TrackableList(" << t.id << ")";
    }
};

int TrackableList::destroy_count = 0;

TEST(list, create) {
    OneWayList<int> lst;
    EXPECT_EQ(lst.size(), 0);
}

TEST(list, push_back) {
    OneWayList<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst[1], 20);
}

TEST(list, insert_begin) {
    OneWayList<int> lst;
    lst.push_back(20);
    lst.insert(0, 10);
    EXPECT_EQ(lst[0], 10);
}

TEST(list, insert_middle) {
    OneWayList<int> lst;
    lst.push_back(10); lst.push_back(30);
    lst.insert(1, 20);
    EXPECT_EQ(lst[1], 20);
}

TEST(list, erase_end) {
    OneWayList<int> lst;
    lst.push_back(10); lst.push_back(20);
    lst.erase(1);
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst[0], 10);
}

TEST(list, erase_begin) {
    OneWayList<int> lst;
    lst.push_back(10); lst.push_back(20);
    lst.erase(0);
    EXPECT_EQ(lst[0], 20);
}

TEST(list, erase_middle) {
    OneWayList<int> lst;
    lst.push_back(10); lst.push_back(20); lst.push_back(30);
    lst.erase(1);
    EXPECT_EQ(lst[1], 30);
}

TEST(list, get_and_size) {
    OneWayList<int> lst;
    lst.push_back(42);
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst[0], 42);
}


TEST(list, destruct) {
    TrackableList::destroy_count = 0;
    {
        OneWayList<TrackableList> lst;
        lst.push_back(TrackableList(1));
        lst.push_back(TrackableList(2));
    }
    EXPECT_GE(TrackableList::destroy_count, 2);  
}

TEST(list, move) {
    OneWayList<int> lst1;
    lst1.push_back(10);
    lst1.push_back(20);

    OneWayList<int> lst2 = std::move(lst1);

    EXPECT_EQ(lst2.size(), 2);
    EXPECT_EQ(lst2[0], 10);
    EXPECT_EQ(lst1.size(), 0);
}

TEST(list, copy) {
    OneWayList<int> lst1;
    lst1.push_back(10);
    lst1.push_back(20);

    OneWayList<int> lst2 = lst1; 

    EXPECT_EQ(lst2.size(), 2);
    EXPECT_EQ(lst2[0], 10);
    EXPECT_EQ(lst2[1], 20);
}