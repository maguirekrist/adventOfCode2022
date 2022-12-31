#include <vector>
#include <sstream>
#include <iostream>
#include <istream>
#include <string>
#include <tuple>
#include <queue>
#include <unordered_set>

namespace day_twelve { 
    struct Coordinate { 
        int32_t x;
        int32_t y;
        int32_t z;

        int32_t cost{0};

        bool operator==(const Coordinate& b) const {
            return x == b.x && y == b.y;
        }
    };

    struct CoordinateHash {
        size_t operator()(const Coordinate& c) const {
            return (c.x+1) ^ (c.y+1);
        }
    };

    struct Map {
        uint32_t width;
        uint32_t height;

        std::vector<Coordinate> map;

        Coordinate sPos;
        Coordinate ePos;
    };

    std::vector<Coordinate> get_valid_neighbors(const Map& map, const Coordinate& coordinate) {
        std::vector<Coordinate> neighbors;

        auto& x = coordinate.x;
        auto& y = coordinate.y;
        auto& z = coordinate.z;
        auto& coordMap = map.map;

        //Check top neighbor
        if((y + 1) < map.height && coordMap[((y+1) * map.width) + x].z <= z + 1) {
            neighbors.push_back(coordMap[((y+1) * map.width) + x]);
        }

        //check bottom neighbor
        if((y - 1) >= 0 && coordMap[((y-1) * map.width) + x].z <= z + 1) {
            neighbors.push_back(coordMap[((y-1) * map.width) + x]);
        }
        //check left neighbor
        if((x - 1) >= 0 && coordMap[((y) * map.width) + x-1].z <= z + 1) { 
            neighbors.push_back(coordMap[(y * map.width) + x-1]);
        }
        //check right neighbor
        if((x + 1) < map.width && coordMap[(y * map.width) + x+1].z <= z + 1) {
            neighbors.push_back(coordMap[(y * map.width) + x+1]);
        }

        return neighbors;
    }


    uint32_t count_steps_to_summit(const Map& map) {  
        std::queue<std::tuple<Coordinate, uint32_t>> queue;
        std::unordered_set<Coordinate, CoordinateHash> visited;
        std::unordered_set<Coordinate, CoordinateHash> pushed;

        queue.push(std::make_tuple(map.sPos, 0));

        while(queue.size() > 0) {
            auto[current, distance] = queue.front();
            queue.pop();
            visited.insert(current);
            
            std::vector<Coordinate> neighbors = get_valid_neighbors(map, current);
            
            for(auto& ele : neighbors) { 
                if(visited.find(ele) == visited.end() && pushed.find(ele) == pushed.end()) {
                    queue.push(std::make_tuple(ele, distance + 1));
                    ele.cost = current.cost + 1;
                    pushed.insert(ele);
                }
            }
        }
        


        return map.ePos.cost;
    }


    Map parse_input(std::istream& stream) {
        std::vector<Coordinate> map; 
        uint32_t height = 0;
        uint32_t width = 0;

        Coordinate sPos;
        Coordinate ePos;

        for(std::string line; std::getline(stream, line); ) {
            std::istringstream iss(line);
            char temp;
            width = 0;
            while(iss >> temp) {
                if(temp == 'S') {
                    sPos = Coordinate{ width, height, 0 };
                    map.push_back(sPos);
                }
                else if(temp == 'E') {
                    ePos = Coordinate{ width, height, 100 };
                    map.push_back(ePos);
                } else {
                    map.push_back(Coordinate{ width, height, temp-'a'});
                }
                width++;
            }
            height++;
        }

        return Map{ width, height, map, sPos, ePos };
    }

}