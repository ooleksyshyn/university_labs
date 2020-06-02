#include <iostream>
#include <string>
#include <vector>
#include <map>


class CircularComparator {
public:
    explicit CircularComparator(const std::string& line) : line(line),
    values(std::map<char, unsigned long>()), p_degrees(std::vector<unsigned long>(line.size() - 1)),
    circular_lines_hashes(std::vector<unsigned long>(line.size()))
    {

        p = line.size() + 1;
        p_degrees[0] = 1;
        p_degrees_sum = 1;
        for (unsigned long i = 1; i < line.size(); ++i){
            p_degrees[i] = p_degrees[i - 1] * p;
            if (i != line.size() - 1) p_degrees_sum += p_degrees[i];
        }

        set_values();

        compute_hashes();
    }


    bool is_circular_shift(const std::string& other){

        if (other.size() != line.size()) return false;

        unsigned long other_hash = compute_polinomial_hash(other);

        for (auto hash : circular_lines_hashes){
            if (hash == other_hash) return true;
        }

        return false;
    }


private:
    void set_values() {
        unsigned long i = 1;
        for (auto ch : line){
            values[ch] = i;
            ++i;
        }
    }


    unsigned long compute_polinomial_hash(const std::string& s){
        unsigned long result = 0;
        unsigned long i = 0;

        for (const auto &ch : s) {
            result += values[ch] * p_degrees[i];
            ++i;
        }

        return result;
    }


    void compute_hashes(){


        circular_lines_hashes[0] = compute_polinomial_hash(line);

        for (unsigned long i = 1; i < line.size(); ++i){
            circular_lines_hashes[i] = circular_lines_hashes[i - 1] + (p - 1)*(p_degrees_sum * values[line[i - 1]]
                    - (circular_lines_hashes[i - 1] - values[line[i - 1]])/p);
        }
    }


    std::string line;
    unsigned long p;
    std::vector<unsigned long> p_degrees;
    unsigned long p_degrees_sum;
    std::map<char, unsigned long> values;
    std::vector<unsigned long> circular_lines_hashes;
};


int main() {
    CircularComparator comparator("oleksii");

    std::cout << comparator.is_circular_shift("ioleksi");


    return 0;
}