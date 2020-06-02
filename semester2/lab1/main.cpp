#include "vectormode.h"
#include "filemode.h"
#include "binfilemode.h"
#include "benchmark.h"

int main(){
    std::ofstream ofs;
    ofs.open("file", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    std::string mode;
    std::cout << "Choose storing mode (VECTOR, FILE, BINARY_FILE): ";
    std::cin >> mode;
    std::cout << std::endl;
    if (mode == "BENCHMARKFILE") benchmark_file();
    if (mode == "BENCHMARKVECTOR") benchmark_vector();
    if (mode == "BENCHMARKBINFILE") benchmark_bin_file();
    if (mode == "VECTOR") Use_Vector();
    if (mode == "FILE") Use_File();
    if (mode == "BINARY_FILE") Use_Bin_File();

    return 0;
};