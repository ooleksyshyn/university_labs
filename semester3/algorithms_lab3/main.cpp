#include <iostream>
#include <vector>


template<typename T>
class d_heap{
public:
    explicit d_heap(size_t d) : data(std::vector<T>()), d(d){}

    d_heap(const std::vector<T>& Data, size_t d) : data(Data), d(d){
        d_heap::d_heapify(data, d, 0);
    }

    static void d_heapify(std::vector<T>& vec, int d, int index){
        if (index >= vec.size()) return;
        for (int i = 1; i <= d; ++i){
            d_heapify(vec, d, index * d + i);
        }
        T max = vec[index];
        int max_index = index;
        for (int i = 1; i <= d; ++i){
            if (index * d + i < vec.size()) {
                if (vec[index * d + i] > max) {
                    max_index = index * d + i;
                    max = vec[max_index];
                }
            }
        }
        std::swap(*(vec.begin() + index), *(vec.begin() + max_index));
        if (index != max_index) d_heap::d_heapify(vec, d, max_index);
    }

    //---------------------------------------required algorithms------------------------------------------------------//

    // complexity -- \log(n)

    T extract_max(){
        if (data.empty()) throw std::range_error("cannot extract max from empty d_heap");
        T max = data[0];
        std::swap(*data.begin(), *(data.end() - 1));

        data.pop_back();

        d_heap::d_heapify(data, d, 0);

        return max;
    }

    // complexity -- log(n)
    void insert(const T& element){
        data.push_back(element);
        pull_up(data.size() - 1);
    }


    //complexity -- log(n)
    void increase_key(int index, T key){
        if (index >= data.size()) throw std::range_error("invalid index for d_heap::increase key");
        if (data[index] >= key) throw std::range_error("invalid key for d_heap::increase key");
        data[index] = key;
        pull_up(index);
    }

    //----------------------------------------------------------------------------------------------------------------//

    [[nodiscard]] auto begin() const{
        return data.begin();
    }

    [[nodiscard]] auto end() const {
        return data.end();
    }

private:

    void pull_up(int index){
        while (index > 0 && data[index] > data[(index - 1)/d]){
            std::swap(*(data.begin() + index), *(data.begin() + (index - 1)/d));
            index = (index - 1)/ d;
        }
    }

    std::vector<T> data;
    size_t d;
};


template<typename T>
std::ostream& operator<<(std::ostream& os, const d_heap<T>& dHeap){
    for (const auto& i : dHeap){
        os << i << " ";
    }
    return os;
}

int main() {
    std::vector<int> y{1, 4, 6, 2, 10};
    d_heap<int> x(y, 3);
    x.insert(100);
    x.insert(0);
    std::cout << x << std::endl;
    x.extract_max();
    std::cout << x << std::endl;
    return 0;
}