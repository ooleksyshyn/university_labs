#include <iostream>
#include <vector>
#include <map>

class SearchEngine{
public:
    explicit SearchEngine(const std::vector<std::vector<char>>& table) : table(table) {
        int i = 0;
        for (const auto& row : table){
            for (const auto ch : row){
                if (values[ch] == 0) {
                    ++i;
                    values[ch] = i;
                }
            }
        }
    }

    std::vector<std::pair<unsigned long, unsigned long>> search_sample(const std::vector<std::vector<char>>& smp){
        if (smp.empty() || smp.size() > table.size()) return {};

        unsigned long k = smp.size();
        unsigned long n = table.size();
        unsigned long p = values.size() + 1;


        std::vector<std::pair<unsigned long, unsigned long>> result;

        std::vector<std::vector<unsigned long>> hashes(
                n - k + 1,std::vector<unsigned long>(n - k + 1, 0));


        std::vector<unsigned long> p_degrees(k * k);


        p_degrees[0] = 1;

        for (unsigned long i = 1; i < p_degrees.size(); ++i){
            p_degrees[i] = p_degrees[i - 1] * p;
        }

        unsigned long sample_hash = 0;

        for (unsigned long i = 0; i < smp.size(); ++i){
            for (unsigned long j = 0; j < smp.size(); ++j){
                for (unsigned long t = 0; t < n - k + 1; ++t){
                    hashes[t][0] += values[table[t + i][j]] * p_degrees[k * i + j];
                }
                sample_hash += values[smp[i][j]] * p_degrees[k * i + j];
            }
        }


        for (unsigned long x = 0; x < n - k + 1; ++x){
            for (unsigned long y = 0; y < n - k + 1; ++y){
                if (y != 0){
                    unsigned long sum1 = 0; // added part
                    unsigned long sum2 = 0; // removed part
                    for (unsigned long i = x; i < x + k; ++i){
                        sum1 += values[table[i][y + k - 1]] * p_degrees[k * (i - x)];
                        sum2 += values[table[i][y - 1]] * p_degrees[k * (i - x)];
                    }
                    sum1 *= p_degrees[k - 1];
                    hashes[x][y] = hashes[x][y - 1] + sum1 - sum2 - (p - 1) * ((hashes[x][y - 1] - sum2)/p);
                }

                std::cout << x << " " << y << " : " << hashes[x][y] << std::endl;
                if (hashes[x][y] == sample_hash) result.emplace_back(x, y);
            }
        }

        return result;
    }

private:

    const std::vector<std::vector<char>>& table;
    std::map<char, unsigned long> values;
};


int main(){
    std::vector<std::vector<char>> x = {{'a', 'b', 'a', 'b'}, {'a', 'b', 'a', 'b'}, {'a', 'b', 'c', 'a'},
                                        {'a', 'b', 'c', 'a'}};

    std::vector<std::vector<char>> sample = {{'a', 'b'}, {'a', 'b'}};
    SearchEngine y(x);

    for (auto i : y.search_sample(sample)){
        std::cout << i.first << " " << i.second << " - hurray" << std::endl;
    }

    return 0;
}