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
#include "eleven/eleven.cpp"
#include "twelve/twelve.cpp"

namespace fs = std::filesystem;

int test() {
    std::string testString = 
R"(Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi
)";

    std::istringstream iss(testString);
    
    day_twelve::Map map = day_twelve::parse_input(iss);
    
    std::cout << day_twelve::count_steps_to_summit(map) << std::endl;

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
    if(argc < 2) {
        return test();
    } else {
        std::ifstream fileStream = get_filestream("input.txt");
        
        std::cout << day_nine::process_moves(fileStream) << std::endl;
    } 

    return 0;
}