#include <gtest/gtest.h>
#include <math.h>

#include <set>

#include "chrono"
#include "my_set.h"
#include "vector"

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
    for (int i = 10000; i > 0; i -= 3) {
        a.push_back(i);
    }
    auto t0 = Time::now();

    my_stl::Set<int> s(a.begin(), a.end());
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set:" << fs.count() << "s\n";
    EXPECT_EQ(s.size(), 3334);
    EXPECT_EQ(*s.begin(), 1);

    t0 = Time::now();

    std::set<int> s2(a.begin(), a.end());
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set:" << fs.count() << "s\n";
    auto i2 = s2.begin();
    for (auto i = s.begin(); i != s.end(); i++) {
        EXPECT_EQ(*i, *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestConstructorsSet, InList) {
    auto t0 = Time::now();
    std::initializer_list<int> l = {
        1,    2,     3,     11,    1,     134314,  12,     33,    44,   77,
        1111, 0,     -100,  -1000, 12312, 1312321, -13123, -2131, 411,  717319,
        213,  12311, 45245, -3141, -1,    -134,    -684,   -4256, -3241};
    my_stl::Set<int> s(l);
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set:" << fs.count() << "s\n";
    t0 = Time::now();

    std::set<int> s2(l);
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set:" << fs.count() << "s\n";
    auto i2 = s2.begin();
    for (auto i = s.begin(); i != s.end(); i++) {
        EXPECT_EQ(*i, *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestConstructorsSet, Other) {
    std::vector<int> a;
    for (int i = 20000; i > 0; i -= 4) {
        a.push_back(i);
    }
    my_stl::Set<int> s(a.begin(), a.end());
    auto t0 = Time::now();
    my_stl::Set<int> s2(s);
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set:" << fs.count() << "s\n";

    std::set<int> std_set(a.begin(), a.end());
    t0 = Time::now();
    std::set<int> std_set2(std_set);
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set:" << fs.count() << "s\n";
    auto i2 = s2.begin();
    for (auto i = s.begin(); i != s.end(); i++) {
        EXPECT_EQ(*i, *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestOperatorsSet, Assign) {
    std::vector<int> a;
    for (int i = 20000; i > 0; i -= 4) {
        a.push_back(i);
    }
    my_stl::Set<int> s(a.begin(), a.end());
    my_stl::Set<int> s2({1, 12, 121});
    auto t0 = Time::now();
    s2 = s;
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set:" << fs.count() << "s\n";

    std::set<int> std_set(a.begin(), a.end());
    std::set<int> std_set2({1, 2, 4});
    t0 = Time::now();
    std_set2 = std_set;
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set:" << fs.count() << "s\n";
    auto i2 = s2.begin();
    for (auto i = s.begin(); i != s.end(); i++) {
        EXPECT_EQ(*i, *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestIteratorsSet, Begin) {
    std::vector<int> a;

    my_stl::Set<int> s = {1, 124, 123, 311, 111, 11, -100, -90};
    EXPECT_EQ(*s.begin(), -100);
    my_stl::Set<int> s2 = {};
    EXPECT_EQ(s2.begin().getPtr(), nullptr);
}

TEST(TestIteratorsSet, End) {
    std::vector<int> a;

    my_stl::Set<int> s = {1, 124, 123, 111, 11, 2, -100, -90};
    EXPECT_EQ(*(--s.end()), 124);
}

TEST(TestOperatorsSet, BidiectIterator) {
    std::vector<int> a;
    for (int i = 20000; i > 0; i -= 4) {
        a.push_back(i);
    }
    my_stl::Set<int> s(a.begin(), a.end());
    auto t0 = Time::now();
    for (auto el : s) {
        auto var = el;
        var += 1;
        el = var;
    }
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set iterate:" << fs.count() << "s\n";

    std::set<int> std_set(a.begin(), a.end());
    t0 = Time::now();
    for (auto el : std_set) {
        auto var = el;
        var += 1;
        el = var;
    }
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set iterate:" << fs.count() << "s\n";
}
TEST(TestMethodsSet, Insert) {
    my_stl::Set<int> s;
    auto t0 = Time::now();
    for (int i = 20000; i > 0; i -= 4) {
        s.insert(i);
    }
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set insert time:" << fs.count() << "s\n";

    std::set<int> std_set;
    t0 = Time::now();
    for (int i = 20000; i > 0; i -= 4) {
        std_set.insert(i);
    }

    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set insert time:" << fs.count() << "s\n";
    auto i2 = std_set.begin();
    for (auto i = s.begin(); i != s.end(); i++) {
        EXPECT_EQ(*i, *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestMethodsSet, InsertIter) {
    std::vector<int> vec;

    for (int i = 20000; i > 0; i -= 4) {
        vec.push_back(i);
    }
    my_stl::Set<int> s;
    auto t0 = Time::now();

    s.insert(vec.begin(), vec.end());
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set insert time:" << fs.count() << "s\n";

    std::set<int> std_set;
    t0 = Time::now();
    std_set.insert(vec.begin(), vec.end());
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set insert time:" << fs.count() << "s\n";
    auto i2 = std_set.begin();
    for (auto i = s.begin(); i != s.end(); i++) {
        EXPECT_EQ(*i, *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestMethodsSet, EraseIter) {
    std::vector<int> vec;

    for (int i = 20000; i > 0; i -= 2) {
        vec.push_back(i);
    }
    my_stl::Set<int> s(vec.begin(), vec.end());
    auto t0 = Time::now();
    auto begin = s.begin();
    for (int i = 0; i < 1000; i++) {
        s.erase(begin++);
    }
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set erase time:" << fs.count() << "s\n";

    std::set<int> std_set(vec.begin(), vec.end());
    t0 = Time::now();
    auto begin2 = std_set.begin();
    for (int i = 0; i < 1000; i++) {
        std_set.erase(begin2++);
    }
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set erase time:" << fs.count() << "s\n";
    auto i2 = std_set.begin();
    for (auto i = s.begin(); i != s.end(); i++) {
        EXPECT_EQ(*i, *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestMethodsSet, EraseKey) {
    std::vector<int> vec;

    for (int i = 20000; i > 0; i -= 2) {
        vec.push_back(i);
    }
    my_stl::Set<int> s(vec.begin(), vec.end());
    auto t0 = Time::now();
    for (int i = 0; i < 1000; i += 4) {
        s.erase(i);
    }
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set erase time:" << fs.count() << "s\n";

    std::set<int> std_set(vec.begin(), vec.end());
    t0 = Time::now();
    for (int i = 0; i < 1000; i += 4) {
        std_set.erase(i);
    }
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std::set erase time:" << fs.count() << "s\n";
    auto i2 = std_set.begin();
    for (auto i = s.begin(); i != s.end(); i++) {
        EXPECT_EQ(*i, *i2);
        i2++;
    }
    std::cout << "sets are equal\n";
}

TEST(TestMethodsSet, Size) {
    std::vector<int> vec;
    for (int i = 20000; i > 0; i--) {
        vec.push_back(i);
    }
    my_stl::Set<int> s(vec.begin(), vec.end());
    EXPECT_EQ(s.size(), 20000);
    my_stl::Set<int> s2({1, 2, 3, 1});
    EXPECT_EQ(s2.size(), 3);
    my_stl::Set<int> s3;
    EXPECT_EQ(s3.size(), 0);
}

TEST(TestMethodsSet, Empty) {
    std::vector<int> vec;
    for (int i = 20; i > 0; i--) {
        vec.push_back(i);
    }
    my_stl::Set<int> s(vec.begin(), vec.end());
    EXPECT_EQ(s.empty(), false);
    my_stl::Set<int> s2({1, 2, 3, 1});
    EXPECT_EQ(s2.empty(), false);
    my_stl::Set<int> s3;
    EXPECT_EQ(s3.empty(), true);
}

TEST(TestMethodsSet, Find) {
    std::vector<int> vec;
    for (int i = 20000; i > 0; i -= 1) {
        vec.push_back(i);
    }
    my_stl::Set<int> s(vec.begin(), vec.end());
    std::set<int> std_set(vec.begin(), vec.end());
    for (int i = 1; i < 1000; i += 4) {
        EXPECT_EQ(*s.find(i), *std_set.find(i));
    }
}

TEST(TestMethodsSet, LowerBound) {
    std::vector<int> vec;
    for (int i = 20000; i > 0; i -= 2) {
        vec.push_back(i);
    }
    my_stl::Set<int> s(vec.begin(), vec.end());
    std::set<int> std_set(vec.begin(), vec.end());
    for (int i = 0; i < 10000; i += 4) {
        EXPECT_EQ(*s.lower_bound(i), *std_set.lower_bound(i));
    }
    auto t0 = Time::now();
    for (int i = 0; i < 10000; i += 4) {
        auto res = s.lower_bound(i);
        auto var = res.operator*();
        var++;
    }
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    std::cout << "my set lowerbound time:" << fs.count() << "s\n";

    t0 = Time::now();
    for (int i = 0; i < 10000; i += 4) {
        auto res = std_set.lower_bound(i);
        auto var = res.operator*();
        var++;
    }
    t1 = Time::now();
    fs = t1 - t0;
    std::cout << "std set lowerbound time:" << fs.count() << "s\n";
}
