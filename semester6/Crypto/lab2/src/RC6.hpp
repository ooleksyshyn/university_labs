#ifndef RC6_HPP__
#define RC6_HPP__

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>

class RC6 {
    unsigned int w, r, b, log_w;
    int64_t modulo;

    unsigned int *S;
    unsigned int *L;

    // Gets RC6 "magic constraints"
    void rc_constraints(const unsigned int &, unsigned int &, unsigned int &);
    void key_schedule(const std::string& key);
    std::string encrypt(const std::string &);
    std::string decrypt(const std::string &);
    int left_rot(unsigned int, unsigned int, unsigned int);
    int right_rot(unsigned int, unsigned int, unsigned int);
    std::string little_endian(std::string);

    std::string hex_to_string(unsigned int A, unsigned int B, unsigned int C, unsigned int D);

public:
    enum Mode {
        Encrypt, Decrypt
    };

    explicit RC6(unsigned int W = 32, unsigned int R = 20, unsigned int B = 16);

    std::string run(Mode, const std::string & text, const std::string & key);

    ~RC6();
};

#endif