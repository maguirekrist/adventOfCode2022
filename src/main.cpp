#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <deque>
#include "six/six.cpp"
#include "seven/seven.cpp"
#include "eight/eight.cpp"
#include "nine/nine.cpp"
#include "ten/ten.cpp"

namespace fs = std::filesystem;

int test() {
    std::string testString = 
R"(noop
addx 3
addx -5
)";

    std::istringstream iss(testString);
    
    day_ten::execute_program(iss);

    return 0;
}

std::ifstream get_filestream(std::string path) {
    fs::path fullPath{fs::current_path().append(path)};

    std::ifstream inputStream(fullPath);
    if(!inputStream)
        throw std::runtime_error("failed to open file");

    return inputStream;
}

std::string get_file_as_string(std::string path) {
    auto istream = get_filestream(path);

    return std::string(std::istream_iterator<char>(istream), std::istream_iterator<char>());
}

int main(int argc, char const *argv[])
{
    // if(argc < 2) {
    //     return test();
    // } else {
    //     std::ifstream fileStream = get_filestream("input.txt");

    //     std::cout << day_nine::process_moves(fileStream) << std::endl;
    // } 

    std::ifstream fileStream = get_filestream("input.txt");

    day_ten::draw_crt(fileStream);

    return 0;
}