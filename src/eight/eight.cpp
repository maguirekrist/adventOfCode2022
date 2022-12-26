#include <string>
#include <vector>
#include <ranges>
#include <numeric>
#include <algorithm>

namespace day_eight {

int count_visible(std::vector<std::string>& map) {
    int count = 0;
    char max = '0'-1;
    auto map_copy = map;

    auto calc_count = [&](int ridx, int cidx) -> void { 
        
        if(map[ridx][cidx] <= max)
            return;
        
        if(map_copy[ridx][cidx] != 'X')
            count++;
        
        max = map[ridx][cidx];

        //We've seen it before
        map_copy[ridx][cidx] = 'X';
    };

    //Focus on rows, left to right & righ to left
    for(auto ridx : std::views::iota(0u, map.size())) {
        max = '0'-1;
        for(auto cidx : std::views::iota(0u, map[ridx].length())) {
            calc_count(ridx, cidx);
        }

        max = '0'-1;
        for(auto cidx : std::views::iota(0u, map[ridx].length()) | std::views::reverse) {
            calc_count(ridx, cidx);
        }   
    }

    //Focus on columsn, top to bottom and then bottom to top
    for(auto cidx : std::views::iota(0u, map[0].length())) {
        max = '0'-1;
        for(auto ridx : std::views::iota(0u, map.size())) {
            calc_count(ridx, cidx);
        }

        max = '0'-1;
        for(auto ridx : std::views::iota(0u, map.size()) | std::views::reverse) {
            calc_count(ridx, cidx);
        }   
    }

    return count;
}

int calculate_scenic_score(std::vector<std::string>& map) {
    std::vector<int> scenic_scores;

    auto calc_count = [&](int ridx, int cidx, int target) -> bool {
        if(map[ridx][cidx] < target)
            return true;
        
        return false;
    };

    //calculates scenic score
    auto calc = [&](int t_ridx, int t_cidx) -> int {
        int counterW = 0;
        int counterE = 0;
        int counterS = 0;
        int counterN = 0;
        char target = map[t_ridx][t_cidx];

        //we need to do four loops

        //Look right
        for(auto cidx : std::views::iota(t_cidx+1u, map[t_ridx].length())) {
            counterE++;
            if(map[t_ridx][cidx] >= target) {
                break;
            }
        }

        //Look left
        for(auto cidx : std::views::iota(0u, t_cidx-0u) | std::views::reverse) {
            counterW++;
            if(map[t_ridx][cidx] >= target) {
                break;
            }
        }

        //Look south
        for(auto ridx : std::views::iota(t_ridx+1u, map.size())) {
            counterS++;
            if(map[ridx][t_cidx] >= target) {
                break;
            }
        }

        //Look north
        for(auto ridx : std::views::iota(0u, t_ridx-0u) | std::views::reverse) {
            counterN++;
            if(map[ridx][t_cidx] >= target) {
                break;
            }
        }

        return counterN * counterS * counterE * counterW;
    };

    //loop through whole map and calculate the 
    for(auto ridx : std::views::iota(0u, map.size())) {
        for(auto cidx : std::views::iota(0u, map[ridx].size())) {
            scenic_scores.push_back(calc(ridx, cidx));
        }
    }

    return std::ranges::max(scenic_scores);
}

//We need to construct a list of 

std::vector<std::string> parse_input(std::istream& input) {
    std::vector<std::string> output;

    for(std::string line; std::getline(input, line); ) {
        output.push_back(line);
    }

    return output;
}

}