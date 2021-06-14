#include "RC6.hpp"

#include <sstream>

namespace {
    std::string to_hex(const std::string& text) {
        std::stringstream stream;
        for (const auto& ch : text) {
            stream << std::hex << int(ch);
        }
        return stream.str();
    }

    std::string from_hex(const std::string& hex) {
        std::string output;

        size_t cnt = hex.length() / 2;

        for (size_t i = 0; cnt > i; ++i) {
            uint32_t s = 0;
            std::stringstream ss;
            ss << std::hex << hex.substr(i * 2, 2);
            ss >> s;

            output.push_back(static_cast<unsigned char>(s));
        }

        return output;
    }
}

RC6::RC6(unsigned int W, unsigned int R, unsigned int B){
    w = W;
    r = R;
    b = B;
    log_w = (unsigned int)log2(w);
    modulo = std::pow(2, w);
    S = new unsigned int[2 * r + 4];
}

void RC6::rc_constraints(const unsigned int &w, unsigned int &p, unsigned int &q){
    p = (unsigned int)std::ceil(((M_E - 2) * std::pow(2, w)));
    q = (unsigned int)((1.618033988749895 - 1) * std::pow(2, w));    // Golden Ratio
}


int RC6::left_rot(unsigned int a, unsigned int b, unsigned int w){
    b <<= w - log_w;
    b >>= w - log_w;
    return (a << b) | (a >> (w - b));
}


int RC6::right_rot(unsigned int a, unsigned int b, unsigned int w){
    b <<= w - log_w;
    b >>= w - log_w;
    return (a >> b) | (a << (w - b));
}


std::string RC6::little_endian(std::string str){
    std::string endian;

    if(str.length() % 2 == 0){
        for(std::string::reverse_iterator r_it = str.rbegin();
            r_it != str.rend();r_it = r_it + 2){
            endian.push_back(*(r_it+1));
            endian.push_back(*r_it);
        }
    }else{
        str = "0" + str;
        for(std::string::reverse_iterator r_it = str.rbegin();
            r_it != str.rend();r_it = r_it + 2){
            endian.push_back(*(r_it+1));
            endian.push_back(*r_it);
        }
    }

    return endian;
}

std::string RC6::hex_to_string(unsigned int A, unsigned int B, unsigned int C, unsigned int D){

    std::string strA, strB, strC, strD, result;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) <<std::hex << A;
    strA = little_endian(ss.str());
    ss.str("");
    ss.clear();

    ss << std::setfill('0') << std::setw(4) <<std::hex << B;
    strB = little_endian(ss.str());
    ss.str("");
    ss.clear();

    ss << std::setfill('0') << std::setw(4) <<std::hex << C;
    strC = little_endian(ss.str());
    ss.str("");
    ss.clear();

    ss << std::setfill('0') << std::setw(4) <<std::hex << D;
    strD = little_endian(ss.str());
    ss.str("");
    ss.clear();

    result = strA + strB + strC + strD;

    return result;

}


void RC6::key_schedule(const std::string& key){
    const unsigned int w_bytes = std::ceil((float)w / 8);
    const unsigned int c = std::ceil((float)b / w_bytes);

    unsigned int p, q;
    rc_constraints(w, p, q);

    L = new unsigned int[c];
    for(int i = 0; i < c; i++){
        L[i] = strtoul(little_endian(key.substr(w_bytes * 2 * i, w_bytes * 2)).c_str(), NULL, 16);
    }

    S[0] = p;
    for(int i = 1; i <= (2 * r + 3); i++){
        S[i] = (S[i - 1] + q) % modulo;
    }

    unsigned int A = 0, B = 0, i = 0, j = 0;
    int v = 3 * std::max(c, (2 * r + 4));
    for(int s = 1; s <= v; s++){
        A = S[i] = left_rot((S[i] + A + B) % modulo, 3, w);
        B = L[j] = left_rot((L[j] + A + B) % modulo, (A + B), w);
        i = (i + 1) % (2 * r + 4);
        j = (j + 1) % c;
    }
}


std::string RC6::encrypt(const std::string &text){
    std::string result;

    unsigned int A, B, C, D;
    A = strtoul(little_endian(text.substr(0, 8)).c_str(), NULL, 16);
    B = strtoul(little_endian(text.substr(8, 8)).c_str(), NULL, 16);
    C = strtoul(little_endian(text.substr(16, 8)).c_str(), NULL, 16);
    D = strtoul(little_endian(text.substr(24, 8)).c_str(), NULL, 16);

    int32_t t, u, temp;

    B += S[0];
    D += S[1];
    for(int i = 1; i <= r; ++i){
        t = left_rot((B * (2 * B + 1)) % modulo, log_w, w);
        u = left_rot((D * (2 * D + 1)) % modulo, log_w, w);
        A = left_rot((A ^ t), u , w) + S[2 * i];
        C = left_rot((C ^ u), t, w) + S[2 * i + 1];
        temp = A;
        A = B;
        B = C;
        C = D;
        D = temp;
    }

    A += S[2 * r + 2];
    C += S[2 * r + 3];

    result = hex_to_string(A, B, C, D);

    return result;
}


std::string RC6::decrypt(const std::string& text){
    std::string result;

    unsigned int A, B, C, D;
    A = strtoul(little_endian(text.substr(0, 8)).c_str(), NULL, 16);
    B = strtoul(little_endian(text.substr(8, 8)).c_str(), NULL, 16);
    C = strtoul(little_endian(text.substr(16, 8)).c_str(), NULL, 16);
    D = strtoul(little_endian(text.substr(24, 8)).c_str(), NULL, 16);

    unsigned int t, u, temp;

    C -= S[2 * r + 3];
    A -= S[2 * r + 2];
    for(int i = r; i >= 1; --i){
        temp = D;
        D = C;
        C = B;
        B = A;
        A = temp;
        u = left_rot((D * (2 * D + 1)) % modulo, log_w, w);
        t = left_rot((B * (2 * B + 1)) % modulo, log_w, w);
        C = right_rot((C - S[2 * i + 1]) % modulo, t, w) ^ u;
        A = right_rot((A - S[2 * i]) % modulo, u, w) ^ t;
    }
    D -= S[1];
    B -= S[0];

    result = hex_to_string(A, B, C, D);

    return result;
}


std::string RC6::run(Mode mode, const std::string &text, const std::string &key){
    key_schedule(key);
    std::string hex = to_hex(text);
    switch (mode) {
        case Encrypt:
            return encrypt(hex);
        case Decrypt:
            return from_hex(decrypt(text));
    }
}

RC6::~RC6(){
    delete S;
}