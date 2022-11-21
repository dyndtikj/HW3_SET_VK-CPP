#include <gtest/gtest.h>
#include <math.h>
#include "vector"
#include "my_set.h"
#include "chrono"
#include <set>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

TEST(TestConstructorsSet, Default) {
    my_stl::Set<int> s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.begin().getPtr(), nullptr);
    EXPECT_EQ(s.end().getPtr(), nullptr);
}

TEST(TestConstructorsSet, TwoIterators) {
    std::vector<int> a;
    for (int i = 10000 ; i > 0; i -= 3) {
        a.push_back(i);
    }
    auto t0 = Time::now();

    my_stl::Set<int> s(a.begin(), a.end());
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set:"<< fs.count() << "s\n";
    EXPECT_EQ(s.size(), 3334);
    EXPECT_EQ(*s.begin(),1);

    t0 = Time::now();

    std::set<int> s2(a.begin(), a.end());
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set:"<< fs.count() << "s\n";
    auto i2 = s2.begin();
    for (auto i = s.begin(); i != s.end(); i++){
        EXPECT_EQ(*i , *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestConstructorsSet, InList) {
    auto t0 = Time::now();
    std::initializer_list<int> l = {1, 2,3, 11, 1,134314, 12, 33, 44 ,77, 1111, 0,
                                    -100, -1000, 12312, 1312321, -13123, -2131, 411, 717319,
                                    213, 12311, 45245, -3141, -1, -134, -684, -4256, -3241};
    my_stl::Set<int> s(l);
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set:"<< fs.count() << "s\n";
    t0 = Time::now();

    std::set<int> s2(l);
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set:"<< fs.count() << "s\n";
    auto i2 = s2.begin();
    for (auto i = s.begin(); i != s.end(); i++){
        EXPECT_EQ(*i , *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestConstructorsSet, Other) {
    std::vector<int> a;
    for (int i = 20000 ; i > 0; i -= 4) {
        a.push_back(i);
    }
    my_stl::Set<int> s(a.begin(), a.end());
    auto t0 = Time::now();
    my_stl::Set<int> s2(s);
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set:"<< fs.count() << "s\n";


    std::set<int> std_set(a.begin(), a.end());
    t0 = Time::now();
    std::set<int> std_set2(std_set);
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set:"<< fs.count() << "s\n";
    auto i2 = s2.begin();
    for (auto i = s.begin(); i != s.end(); i++){
        EXPECT_EQ(*i , *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestOperatorsSet, Assign) {
    std::vector<int> a;
    for (int i = 20000 ; i > 0; i -= 4) {
        a.push_back(i);
    }
    my_stl::Set<int> s(a.begin(), a.end());
    my_stl::Set<int> s2({1, 12, 121});
    auto t0 = Time::now();
    s2 = s;
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set:"<< fs.count() << "s\n";


    std::set<int> std_set(a.begin(), a.end());
    std::set<int> std_set2({1, 2, 4});
    t0 = Time::now();
    std_set2 = std_set;
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set:"<< fs.count() << "s\n";
    auto i2 = s2.begin();
    for (auto i = s.begin(); i != s.end(); i++){
        EXPECT_EQ(*i , *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestIteratorsSet, Begin) {
    std::vector<int> a;

    my_stl::Set<int> s = {1, 124 ,123, 311, 111, 11 , -100, -90 };
    EXPECT_EQ(*s.begin(), -100);
    my_stl::Set<int> s2 = {};
    EXPECT_EQ(s2.begin().getPtr(), nullptr);
}

TEST(TestIteratorsSet, End) {
    std::vector<int> a;

    my_stl::Set<int> s = {1, 124 ,123, 111, 11 , -100, -90 };
    std::cout << s;
    EXPECT_EQ(*(--s.end()), 124);
    my_stl::Set<int> s2 = {123};
    EXPECT_EQ(s2.end().getPtr(), nullptr);

}

//const_iterator begin() const;
//const_iterator end() const;
//
//// 3
//std::pair<const_iterator, bool> insert(const key_type&);
//template <class Iterator>
//void insert(Iterator, Iterator);
//
//void erase(iterator);
//size_t erase(const key_type&);
//void erase(iterator, iterator);
//
//// 4
//size_t size() const;
//bool empty() const;
//
//const_iterator find(const key_type&) const;
//const_iterator lower_bound(const key_type&) const;