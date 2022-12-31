#include <vector>
#include <functional>
#include <istream>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace day_eleven { 

    struct Monkey {
        std::vector<int64_t> items;
        std::function<int64_t(int64_t)> operation;
        std::function<int64_t(int64_t)> test;
        int64_t inspectCount = 19*3*13*17*2*11*5*7;
    };

    std::vector<Monkey> get_monkeys(std::istream& input) {
        std::vector<Monkey> monkeys;

        Monkey monkey;
        for(std::string line; std::getline(input, line); ) {
            if(line.find("Monkey") != std::string::npos) {
                continue;
            }

            if(line.find("Starting") != std::string::npos) {
                size_t start = line.find(":") + 1;
                std::istringstream iss(line.substr(start));
                
                std::vector<int64_t> items;
                int i;
                while(iss >> i) {
                    items.push_back(i);
                    if(iss.peek() == ',') {
                        iss.ignore();
                    }
                }

                monkey.items = items;
            }

            if(line.find("Operation") != std::string::npos) {
                size_t start = line.find(":") + 1;
                std::istringstream iss(line.substr(start));

                std::string newWord;
                std::string equals;
                std::string oldWord;
                char operation;
                iss >> newWord >> equals >> oldWord >> operation;
                int amt;

            }

            if(line.find("Test") != std::string::npos) {
                size_t start = line.find(":");

            }

            if(line.find("true") != std::string::npos) {
                size_t start = line.find(":") + 1;
                std::istringstream iss(line.substr(start));
            }

            if(line.find("false") != std::string::npos) {
                size_t start = line.find(":") + 1;
                std::istringstream iss(line.substr(start));

            }


            if(line.empty()) {
                monkeys.push_back(monkey);
                monkey = Monkey{}; //reset building monkey
            }
        }

        return monkeys;
    }

    void process_round(std::vector<Monkey>& monkies) {
        for(auto& monkey : monkies) {
            int quantity = monkey.items.size();
            for(size_t i = 0; i < monkey.items.size(); i++) {
                monkey.inspectCount++;
                monkey.items[i] = monkey.operation(monkey.items[i]);
                // monkey.items[i] = monkey.items[i]/3;

                int targetMonkey = monkey.test(monkey.items[i]);
                monkies[targetMonkey].items.push_back(monkey.items[i]);
                monkey.items.erase(monkey.items.begin() + i);
                i--;
            }
        }
    }

    int64_t solve_one() {
        // std::vector<Monkey> monkies{
        //     Monkey{
        //         {83,97,95,67},
        //         [](int64_t v) -> int64_t { return v * 19; },
        //         [](int64_t v) -> int64_t { if(v % 17 == 0) return 2; return 7; }
        //     },
        //     Monkey{
        //         { 71, 70, 79, 88, 56, 70 },
        //         [](int64_t v) -> int64_t { return v + 2; },
        //         [](int64_t v) -> int64_t { if(v % 19 == 0) return 7; return 0; }
        //     },
        //     Monkey{
        //         { 98, 51, 51, 63, 80, 85, 84, 95 },
        //         [](int64_t v) -> int64_t { return v + 7; },
        //         [](int64_t v) -> int64_t { if(v % 7 == 0) return 4; return 3; }
        //     },
        //     Monkey{
        //         {77, 90, 82, 80, 79},
        //         [](int64_t v) -> int64_t { return v + 1; },
        //         [](int64_t v) -> int64_t { if(v % 11 == 0) return 6; return 4; }
        //     },
        //     Monkey{
        //         { 68 },
        //         [](int64_t v) -> int64_t { return v * 5; },
        //         [](int64_t v) -> int64_t { if(v % 13 == 0) return 6; return 5; }
        //     },
        //     Monkey{
        //         { 60, 94 },
        //         [](int64_t v) -> int64_t { return v + 5; },
        //         [](int64_t v) -> int64_t { if(v % 3 == 0) return 1; return 0; }
        //     },
        //     Monkey{
        //         { 81, 51, 85 },
        //         [](int64_t v) -> int64_t { return v * v; },
        //         [](int64_t v) -> int64_t { if(v % 5 == 0) return 5; return 1; }
        //     },
        //     Monkey{
        //         { 98, 81, 63, 65, 84, 71, 84 },
        //         [](int64_t v) -> int64_t { return v + 3; },
        //         [](int64_t v) -> int64_t { if(v % 2 == 0) return 2; return 3; }
        //     }
        // };

        std::vector<Monkey> monkies{
            Monkey{
                { 79,98 },
                [](int64_t v) -> int64_t { return v * 19; },
                [](int64_t v) -> int64_t { if(v % 23 == 0) return 2; return 3; }
            },
            Monkey{
                { 54, 65, 75, 74 },
                [](int64_t v) -> int64_t { return v + 6; },
                [](int64_t v) -> int64_t { if(v % 19 == 0) return 2; return 0; }
            },
            Monkey{
                { 79, 60, 97 },
                [](int64_t v) -> int64_t { return v * v; },
                [](int64_t v) -> int64_t { if(v % 13 == 0) return 1; return 3; }
            },
            Monkey{
                { 74 },
                [](int64_t v) -> int64_t { return v + 3; },
                [](int64_t v) -> int64_t { if(v % 17 == 0) return 0; return 1; }
            }
        };

        for(int i = 0; i < 10000; i++) {
            process_round(monkies);
        }

        std::ranges::sort(monkies, [](auto& a, auto& b) {
            return a.inspectCount < b.inspectCount;
        });
        return monkies[monkies.size()-1].inspectCount*monkies[monkies.size()-2].inspectCount;
    

    }


}