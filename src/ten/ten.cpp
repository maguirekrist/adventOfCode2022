#include <string>
#include <vector>
#include <ranges>
#include <iostream>
#include <unordered_set>
#include <numeric>

namespace day_ten {
    
    struct Operation {
        int amount;
        int cycles;

        friend std::istream& operator>>(std::istream& s, Operation& o) {
            std::string word;
            
            s >> word;
            if(word == "addx") {
                s >> o.amount;
                o.cycles = 2;
            } else {
                o.amount = 0;
                o.cycles = 1;
            }

            return s;
        }
    };

    int execute_program(std::istream& input) {
        int reg = 1;
        int cycles = 0;
        
        std::vector<Operation> ops;
        std::unordered_set<int> marks = { 20, 60, 100, 140, 180, 220 };
        std::vector<int> signals;
        
        std::ranges::copy(std::istream_iterator<Operation>(input), std::istream_iterator<Operation>(), std::back_inserter(ops));

        for(auto& op : ops) {
            for(int i = 0; i < op.cycles; i++) {
                cycles++;
                if(marks.contains(cycles)) {
                    signals.push_back(cycles * reg);
                }
            }
            reg += op.amount;
        }

        //compute total signal strenght
        return std::accumulate(signals.begin(), signals.end(), 0);

    }

    void draw_crt(std::istream& input) {
        int reg = 1;
        int cycles = 1;
        
        std::vector<Operation> ops;
        std::unordered_set<int> marks = { 40, 80, 120, 160, 200, 240 };
        std::vector<int> signals;
        
        std::ranges::copy(std::istream_iterator<Operation>(input), std::istream_iterator<Operation>(), std::back_inserter(ops));

        std::ostream& out = std::cout;

        for(auto& op : ops) {
            for(int i = 0; i < op.cycles; i++) { 
                if(marks.contains(cycles-1)) {
                    cycles = 1;
                    out << '\n';
                }

                if(std::abs(reg-(cycles-1)) < 2) {
                    out << '#';
                } else {
                    out << '.';
                }
                cycles++;
                out.flush();
            }
            reg += op.amount;
        }
    }

}