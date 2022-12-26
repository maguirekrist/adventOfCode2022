#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <deque>

namespace fs = std::filesystem;

namespace day_five {

struct Order {
    uint32_t count;
    uint32_t from;
    uint32_t to;

    friend std::istream& operator>>(std::istream& s, Order& o) {
        std::string word;
        s >> word >> o.count >> word>> o.from >> word >> o.to;
        --o.from;
        --o.to;

        return s;
    }
};

std::pair<std::vector<std::deque<char>>, std::vector<Order>> get_data(std::istream& stream) {
    std::vector<std::deque<char>> crates;
    std::vector<Order> orders;
    bool done = false;
    
    std::string line;
    while(!done && std::getline(stream, line)) {        
        for(size_t i = 0; i< line.length(); i++) {
            if(std::isdigit(line[i])) { 
                done = true;
                break;
            }   

            if(!std::isupper(line[i])) continue;

            size_t stack = (i-1)/4;
            if(crates.size() <= stack) crates.resize(stack+1);

            crates[stack].push_back(line[i]);
        }
    }
    //read a blank line
    std::getline(stream, line);

    //read input from orders
    //std::ranges::copy(std::views::istream<Order>(stream), std::back_inserter(orders));

    std::ranges::copy(std::istream_iterator<Order>(stream), std::istream_iterator<Order>(), std::back_inserter(orders));

    return std::make_pair(crates, orders); 
}



std::string print_crates(std::vector<std::deque<char>>& crates) {
    std::string output;

    for(auto& stack : crates) {
        for(auto& crate : stack) {
            std::cout << crate << std::endl;
        }

        std::cout << std::endl;
    }

    return output;
}

std::string print_top(std::vector<std::deque<char>>& crates) {
    std::string output;

    for(auto& stack : crates) {
        output += stack.front();    
    }

    return output;
}

std::string solveProblemOne(std::vector<std::deque<char>>& crates, const std::vector<Order>& orders) {
    for(auto& order : orders)  {
        //for orders in orders
        //we want to move x amount from 0-n stack to some 0-n stack
        //crates represent a vector of stacks, represented by characters


        //grab the first crates
        auto cratesToTake{ crates[order.from] | std::views::take(order.count) };

        std::ranges::reverse(crates[order.to]);
        std::ranges::copy(cratesToTake, std::back_inserter(crates[order.to]));
        std::ranges::reverse(crates[order.to]);

    
        
        std::ranges::reverse(crates[order.from]);

        crates[order.from].resize(crates[order.from].size() - order.count);

        std::ranges::reverse(crates[order.from]);
    }
    
    return print_top(crates);
}

std::string solveProblemTwo(std::vector<std::deque<char>>& crates, const std::vector<Order>& orders) {
    for(auto& order : orders) {
        auto cratesToTake { crates[order.from] | std::views::take(order.count) | std::views::reverse };
        //CratesToTake is already in the order that we want it to be in
        std::ranges::copy(cratesToTake, std::front_inserter(crates[order.to]));


        crates[order.from].erase(crates[order.from].begin(), crates[order.from].begin()+order.count);
    }

    return print_top(crates);
}
}