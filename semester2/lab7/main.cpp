#include "test_runner.h"
#include <iostream>


void test_vector_(){
    std::vector<int> vec;

    ASSERT_EQUAL(vec, std::vector<int>())
    vec.push_back(0);
    ASSERT_EQUAL(vec, std::vector<int>({1}))

    ASSERT(std::vector<int>())

}

void function_vector(long long n){
    std::vector<long long> data;
    for (int i = 0; i < n; ++i){
        data.push_back(i);
    }
    data.insert(data.begin(), -1);
}

void function_set(long long n){
    std::set<long long> data;
    for (int i = 0; i < n; ++i){
        data.insert(i);
    }
    data.insert(-1);
}

void generate_vector(std::vector<long long>& vector, long long n){
    for (int i = 0; i < n; ++i){
        vector.push_back(i);
    }
}

void generate_set(std::set<int>& set, int n){
    for (int i = 0; i < n; ++i){
        set.insert(i);
    }
}

void test_vector(std::vector<long long>& vector){
    vector.insert(vector.begin(), -1);
}

void test_set(std::set<int>& set){
    set.insert(-1);
}

int main() {
    TestRunner tr = TestRunner::SetTester();
    TimeKeeper t(std::cout);
    //TEST(t, function_vector, 0.1);
    //TEST(t, function_set, 0.1);
    std::vector<long long> vector;
    std::set<int> set;
    RUN_TEST(tr, test_vector_);

    //TEST_COMPARISON_GENERATED(t, test_vector, generate_vector, vector, 0.01)
    //TEST_COMPARISON_GENERATED(t, test_set, generate_set, set, 0.01)
    return 0;
}