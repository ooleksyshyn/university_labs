#include "definitions.h"

int main() {
    std::string mode = " ";
    while (mode != "EXIT") {
        std::cout << "Choose mode(DEMONSTRATION, BENCHMARK or EXIT):";
        std::cin >> mode;
        if (mode == "DEMONSTRATION") {
            demonstration();
        }
        if (mode == "BENCHMARK"){
            benchmark();

        }
    }

    return 0;
}

void selection_sort(std::vector<int>& vec){
    for (int i = 0; i < vec.size() - 1; ++i){
        int index_of_min = i;

        for (int j = i; j < vec.size(); ++j){
            if (vec[j] < vec[index_of_min]){
                index_of_min = j;
            }
        }

        int buf = vec[i];
        vec[i] = vec[index_of_min];
        vec[index_of_min] = buf;
    }
}

void selection_sort_with_printing(std::vector<int>& vec){
    for (int i = 0; i < vec.size() - 1; ++i){
        int index_of_min = i;

        for (int j = i; j < vec.size(); ++j){
            if (vec[j] < vec[index_of_min]){
                index_of_min = j;
            }
        }

        int buf = vec[i];
        vec[i] = vec[index_of_min];
        vec[index_of_min] = buf;
        for (auto element : vec){
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

void merge_sort(std::vector<int>& vec, int left_position, int right_position){
    if (right_position == left_position) return;

    int middle = (right_position + left_position)/2;

    merge_sort(vec, left_position, middle);
    merge_sort(vec, middle + 1, right_position);

    std::vector<int> left_part, right_part;
    for (int i = left_position; i <= middle; ++i){
        left_part.push_back(vec[i]);
    }
    for (int i = middle + 1; i <= right_position; ++i){
        right_part.push_back(vec[i]);
    }

    int right_vector_index = 0, left_vector_index = 0;
    for (int i = left_position; i <= right_position; ++i){
        if (right_vector_index == right_part.size()){
            vec[i] = left_part[left_vector_index];
            ++left_vector_index;
        } else if (left_vector_index == left_part.size()){
            vec[i] = right_part[right_vector_index];
            ++right_vector_index;
        } else if (right_part[right_vector_index] > left_part[left_vector_index]){
            vec[i] = left_part[left_vector_index];
            ++left_vector_index;
        } else{
            vec[i] = right_part[right_vector_index];
            ++right_vector_index;
        }
    }
}

void merge_sort_with_printing(std::vector<int>& vec, int left_position, int right_position){
    if (right_position == left_position) return;

    int middle = (right_position + left_position)/2;

    merge_sort_with_printing(vec, left_position, middle);
    merge_sort_with_printing(vec, middle + 1, right_position);

    std::vector<int> left_part, right_part;
    for (int i = left_position; i <= middle; ++i){
        left_part.push_back(vec[i]);
    }
    for (int i = middle + 1; i <= right_position; ++i){
        right_part.push_back(vec[i]);
    }

    int right_vector_index = 0, left_vector_index = 0;
    for (int i = left_position; i <= right_position; ++i){
        if (right_vector_index == right_part.size()){
            vec[i] = left_part[left_vector_index];
            ++left_vector_index;
        } else if (left_vector_index == left_part.size()){
            vec[i] = right_part[right_vector_index];
            ++right_vector_index;
        } else if (right_part[right_vector_index] > left_part[left_vector_index]){
            vec[i] = left_part[left_vector_index];
            ++left_vector_index;
        } else{
            vec[i] = right_part[right_vector_index];
            ++right_vector_index;
        }
    }

    for (auto i : vec){
        std::cout << i << " ";
    }
    std::cout << "Sorted part: " << left_position << "-" << right_position;
    std::cout << std::endl;
}

void quick_sort(std::vector<int>& vec, int low, int high){
    if (high <= low) return;

    int pivot = vec[high];
    int first_great_element_index = low - 1;
    for (int j = low; j < high; ++j){

        if (vec[j] <= pivot){
            ++first_great_element_index;
            int buf = vec[first_great_element_index];
            vec[first_great_element_index] = vec[j];
            vec[j] = buf;
        }
    }
    int buf = vec[high];
    vec[high] = vec[first_great_element_index + 1];
    vec[first_great_element_index + 1] = buf;

    quick_sort(vec, low, first_great_element_index);
    quick_sort(vec, first_great_element_index + 1, high);
}

void quick_sort_with_printing(std::vector<int>& vec, int low, int high){

    if (high <= low) return;

    int pivot = vec[high];
    int first_great_element_index = low - 1;
    for (int j = low; j < high; ++j){
        if (vec[j] <= pivot){
            ++first_great_element_index;
            int buf = vec[first_great_element_index];
            vec[first_great_element_index] = vec[j];
            vec[j] = buf;

        }
        for (auto i : vec){
            std::cout << i << " ";
        }
        std::cout << "low = " << low << " high = " << high;

        std::cout << std::endl;
    }
    int buf = vec[high];
    vec[high] = vec[first_great_element_index + 1];
    vec[first_great_element_index + 1] = buf;

    for (auto i : vec){
        std::cout << i << " ";
    }
    std::cout << "Sorted with pivot = " << buf;

    std::cout << std::endl;

    quick_sort_with_printing(vec, low, first_great_element_index);
    quick_sort_with_printing(vec, first_great_element_index + 1, high);
}

void benchmark(){
    {
        for (int amount = 2; amount < 100'000; amount*=2) {

            std::vector<int> Vec(amount);
            for (int i = 0; i < amount; ++i) {
                Vec[i] = RandomInt(0, amount * 2);
            }

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            selection_sort(Vec);

            end = std::chrono::system_clock::now();

            double elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds>
                    (end - start).count()) / 1000.;


            double time = elapsed_seconds;
            std::cout << "Sort: selection, elements: " << amount << " time: " << time << std::endl;
        }
    }
    std::cout << std::endl << std::endl;
    {
        for (int amount = 2; amount < 10'000'000; amount *= 2) {

            std::vector<int> Vec(amount);
            for (int i = 0; i < amount; ++i) {
                Vec[i] = RandomInt(0, amount * 2);
            }

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            merge_sort(Vec, 0, Vec.size() - 1);

            end = std::chrono::system_clock::now();

            double elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds>
                    (end - start).count()) / 1000.;


            double time = elapsed_seconds;
            std::cout << "Sort: merge, elements: " << amount << " time: " << time << std::endl;
        }
    }
    std::cout << std::endl << std::endl;
    {
        for(int amount = 1; amount < 40'000'000; amount *= 2){
            std::vector<int> vec(amount);

            for (auto &i : vec){
                i = RandomInt(0, amount * 2);
            }

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            quick_sort(vec, 0, vec.size() - 1);

            end = std::chrono::system_clock::now();

            double elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds>
                    (end - start).count()) / 1000.;


            double time = elapsed_seconds;
            std::cout << "Sort: quicksort , elements: " << amount << " time: " << time << std::endl;

        }

    }
    std::cout << std::endl << std::endl;
    {
        for (int amount = 2; amount < 40'000'000; amount*=2) {

            std::vector<int> Vec(amount);
            for (int i = 0; i < amount; ++i) {
                Vec[i] = RandomInt(0, amount * 2);
            }

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            sort(Vec.begin(), Vec.end());

            end = std::chrono::system_clock::now();

            double elapsed_seconds = (std::chrono::duration_cast<std::chrono::milliseconds>
                    (end - start).count()) / 1000.;


            double time = elapsed_seconds;
            std::cout << "Sort: algorithm::sort , elements: " << amount << " time: " << time << std::endl;
        }
    }
}

int RandomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

void demonstration(){
    std::cout << "Amount of elements to sort: ";
    int n;
    std::cin >> n;
    std::vector<int> vector_to_sort(n);
    for (auto &i : vector_to_sort){
        i = RandomInt(0, n*n);
        std::cout << i << " ";
    }

    std::vector<int> copy = vector_to_sort;

    std::cout << std::endl << "Selection sort:" << std::endl;
    selection_sort_with_printing(vector_to_sort);

    vector_to_sort = copy;

    std::cout << std::endl << "Merge sort:" << std::endl;
    merge_sort_with_printing(vector_to_sort, 0, vector_to_sort.size() - 1);

    vector_to_sort = copy;

    std::cout << std::endl << "Quick sort:" << std::endl;
    quick_sort_with_printing(vector_to_sort, 0, vector_to_sort.size() - 1);

}