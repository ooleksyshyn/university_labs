#include <iostream>
#include <utility>
#include <random>
#include <chrono>

#include "include/lint.hpp"


namespace utils {

    apa::lint mod(const apa::lint& number, const apa::lint& modulo) {
        return number - (number / modulo) * modulo;
    }

    apa::lint randomLongInt(const apa::lint& max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 9);

        if (max == 0)
            return 0;

        apa::lint result{dis(gen)};

        for (int i = 0; i < max.get_length(); ++i) {
            result *= 10;
            result += dis(gen);
        }

        return mod(result, max);
    }


    apa::lint exponent(apa::lint number, apa::lint power, const apa::lint& modulo) {
        apa::lint res(1);

        while (power > 0) {
            if (power[power.get_length() - 1] % 2 != 0) {
                res = mod(res * number, modulo);
            }
            number = mod(number * number, modulo);
            power /= 2;
        }

        return res;
    }

    class FermatPrimeChecker{
        using LongInt = apa::lint;

        const LongInt& m_candidate;
        bool m_isPrime = true;
    public:
        explicit FermatPrimeChecker(const LongInt& number, const LongInt& n_checks) noexcept : m_candidate{number} {
            check(n_checks);
        }

        void check(const LongInt& n_checks) {
            for (LongInt i = 0; i < n_checks; ++i) {
                const LongInt a = randomLongInt(m_candidate);

                if (a != 0 && exponent(a, m_candidate - 1, m_candidate) != 1) {
                    m_isPrime = false;
                    return;
                }
            }
        }

        [[nodiscard]] bool isPrime() const noexcept { return m_isPrime; }
    };

}


bool fermatCheck(const apa::lint& number) {
    utils::FermatPrimeChecker checker{number, apa::lint{"5000"}};
    return checker.isPrime();
}


int main() {
    std::cout << fermatCheck(apa::lint{"7919"}) << std::endl;
    return 0;
}
