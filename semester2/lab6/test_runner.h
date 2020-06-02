#pragma once


#include <cmath>

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <functional>


template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}


template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}


template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}


//-----------------------------------  class TestRunner -----------------------------------//


template <class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint) {
    if (!(t == u)) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw std::runtime_error(os.str());
    }
}


template <class T, class U>
void PtrEqual(const T& t, const U& u, const std::string& hint){
    AssertEqual(*t, *u, hint);
}


template <class T>
void Assert(T object, const std::string& hint) {
    if (object != T()) {
        std::ostringstream os;
        os << "Assertion failed: " << object << " != " << T();
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw std::runtime_error(os.str());
    }
}


class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        } catch (std::exception& e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        } catch (...) {
            ++fail_count;
            std::cerr << "Unknown exception caught" << std::endl;
        }
    }


    ~TestRunner() {
        if (fail_count > 0) {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }


    static TestRunner SetTester(){
        static TestRunner instance;
        return instance;
    }



private:
    int fail_count = 0;


    TestRunner(){}


    TestRunner(const TestRunner&){}


    TestRunner& operator=(TestRunner&){}
};


//-----------------------------------  TestRunner macros -----------------------------------//


#define ASSERT_EQUAL(x, y) {            \
  std::ostringstream os;                \
  os << #x << " != " << #y << ", "      \
    << __FILE__ << ":" << __LINE__;     \
  AssertEqual(x, y, os.str());          \
}


#define ASSERT(x) {                     \
  std::ostringstream os;                \
  os << #x << " is false, "             \
    << __FILE__ << ":" << __LINE__;     \
  Assert(x, os.str());                  \
}


#define PTR_EQUAL(x, y){                \
    std::ostringstream os;              \
    os << #x << " != " << #y << ", "    \
        << __FILE__ << __LINE__;        \
    PtrEqual(x, y, os.str());              \
}


#define RUN_TEST(tr, func) \
  tr.RunTest(func, #func);


//-----------------------------------  class TimeKeeper -----------------------------------//



class TimeKeeper{
public:
    explicit TimeKeeper(std::ostream& ostream) : os(ostream){}


    ~TimeKeeper(){
        if (!benchmarks.empty()) {
            for (auto &test:benchmarks) {
                os << "Benchmark:" << " function " << test.first << std::endl;

                os << std::string(23, '-') << "\n|  Amount  |" << "   Time   |\n";

                os << std::string(10, '-') << "\n";
                for (auto time_test : test.second) {
                    if (time_test.second != 0) {
                        os << "|" << std::setw(10) << time_test.first
                           << "|" << std::setw(10) << time_test.second << "|";
                        os << std::endl;

                        os << std::string(23, '-');
                        os << std::endl;
                    }
                }
                os << "\n\n";
            }
            os << "\n";
        }

        if (!compared_functions.empty()) {

            std::string lower_line = std::string(12, '-');
            for (auto &i : compared_functions) {
                for (int j = 0; j < i.size() + 3; ++j) {
                    lower_line += "-";
                }
            }

            os << "Comparison table" << std::endl;

            os << lower_line << "\n";
            os << "|  Amount  |";

            for (auto& i : compared_functions) {
                os << std::setw(i.size() + 2) << i << "|";
            }
            os << std::endl << lower_line << std::endl;
            for (int i = 0; i < comparison_data.size(); ++i) {
                os << "|" << std::setw(10) << comparison_data[i].first << "|";
                for (int j = 0; j < comparison_data[i].second.size(); ++j) {
                    os << std::setw(compared_functions[j].size() + 2) << comparison_data[i].second[j];
                    os << "|";
                }
                os << std::endl << lower_line << std::endl;
            }
        }
    }


    template <typename Function, typename Generation_function, typename T>
    void set_benchmark(Function F, Generation_function G, T& object, std::string name, double max_time){
        benchmarks.emplace_back(std::make_pair(name, std::vector<std::pair<long long, double >>()));
        long long index = benchmarks.size() - 1;
        long long n = 1;
        double elapsed_time = 0;
        while (elapsed_time < max_time){

            G(object, n);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            F(object);

            end = std::chrono::system_clock::now();


            elapsed_time = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            benchmarks[index].second.emplace_back(std::make_pair(n, elapsed_time));
            long long degree = log10(n);
            n += pow(10, degree);
        }
    }


    template<typename Function>
    void set_benchmark(Function F, std::string function_name, double max_time){
        benchmarks.emplace_back(std::make_pair(function_name, std::vector<std::pair<long long, double >>()));
        long long index = benchmarks.size() - 1;
        long long n = 1;
        double elapsed_time = 0;
        while(elapsed_time < max_time){
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            F(n);

            end = std::chrono::system_clock::now();


            elapsed_time = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;
            benchmarks[index].second.emplace_back(std::make_pair(n, elapsed_time));
            long long degree = log10(n);
            n += pow(10, degree);
        }
    }


    template <typename Function, typename Generation_gunction, class T>
    void set_comparison_benchmark(Function F, Generation_gunction G,
                                              T& object, std::string name, double max_time){

        bool first_addition = comparison_data.empty();


        compared_functions.push_back(name);
        int index = 0;
        long long n = 1;
        double elapsed_time = 0;
        while (elapsed_time < max_time){
            if (!first_addition && index == comparison_data.size()) return;


            G(object, n);
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            for (int i = 0; i < n; ++i) {
                F(object);
            }

            end = std::chrono::system_clock::now();


            elapsed_time = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;

            if (first_addition){

                comparison_data.emplace_back(std::make_pair(n, std::vector<double>{elapsed_time}));
            } else {

                comparison_data[index].second.push_back(elapsed_time);
            }

            long long degree = log10(n);
            n += pow(10, degree);

            ++index;
        }
    }


    template<typename Function>
    void set_comparison_benchmark(Function F, std::string name, double max_time) {
        bool first_addition = comparison_data.empty();


        compared_functions.push_back(name);
        int index = 0;
        long long n = 1;
        double elapsed_time = 0;
        while (elapsed_time < max_time){
            if (!first_addition && index == comparison_data.size()) return;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            F(n);

            end = std::chrono::system_clock::now();


            elapsed_time = (std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count()) / 1000.;

            if (first_addition){
                comparison_data.emplace_back(std::make_pair(n, std::vector<double>{elapsed_time}));
            } else {
                comparison_data[index].second.push_back(elapsed_time);
            }

            long long degree = log10(n);
            n += pow(10, degree);

            ++index;
        }
    }


private:
    std::vector<std::pair<std::string,std::vector<std::pair<long long, double >>>> benchmarks;
    std::vector<std::pair<long long ,std::vector<double>>> comparison_data;
    std::vector<std::string> compared_functions;
    std::ostream& os;
};


//-----------------------------------  TimeKeeper macros -----------------------------------//


#define TEST(tester, func, max_time){             \
    tester.set_benchmark(func, #func, max_time);  \
}


#define TEST_GENERATED(tester, func, generation_function, object, max_time){                \
    tester.set_benchmark(func, generation_function, object, #func, max_time);               \
}


#define TEST_COMPARISON(tester, func, max_time){                                            \
    tester.set_comparison_benchmark(func, #func, max_time);                                 \
}


#define TEST_COMPARISON_GENERATED(tester, func, generation_function, object, max_time){     \
    tester.set_comparison_benchmark(func, generation_function, object, #func, max_time);    \
}