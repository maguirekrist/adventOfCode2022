#include <iostream>
#include <vector>
#include <ranges>
#include <unordered_set>
#include <utility>

namespace day_nine {

    struct pair_hash
    {
        template <class T1, class T2>
        std::size_t operator () (std::pair<T1, T2> const &pair) const
        {
            std::size_t h1 = std::hash<T1>()(pair.first);
            std::size_t h2 = std::hash<T2>()(pair.second);
            return h1 * 97 * h2;
        }
    };

    struct Move { 
        char dir;
        int steps;

        friend std::istream& operator>>(std::istream& s, Move& m) {
            s >> m.dir >> m.steps;

            return s;
        }
    };

    struct Knot { 
        int x;
        int y;

        Knot() : x(0), y(0) {}
    };

    void process_move(Knot& a, Knot& b) {
        if(std::abs(a.x - b.x) == 2 && a.y - b.y == 1)
        {
            b.y++;
        }

        if(std::abs(a.x - b.x) == 2 && a.y - b.y == -1)
        {
            b.y--;
        }

        if(std::abs(a.y - b.y) == 2 && a.x - b.x == 1)
        {
            b.x++;
        }
        
        if(std::abs(a.y - b.y) == 2 && a.x - b.x == -1)
        {
            b.x--;
        }

        //calculate tail
        if(a.x - b.x == 2) {
            b.x++;
        }

        if(a.x - b.x== -2) {
            b.x--;
        }

        if(a.y - b.y == 2) {
            b.y++;
        }

        if(a.y - b.y == -2) {
            b.y--;
        }
    }

    int process_moves(std::istream& input) {   
        int count = 0;
        std::vector<Move> moves;
        std::unordered_set<std::pair<int, int>, pair_hash> trackMap;
        std::ranges::copy(std::istream_iterator<Move>(input), std::istream_iterator<Move>(), std::back_inserter(moves));
        
        std::vector<Knot> knots(9);
        Knot head;        

        for(auto& move : moves) {
            for(int j = 0; j < move.steps; j++) {
                //move the head
                switch(move.dir) {
                    case 'R':
                        head.x++;
                        break;
                    case 'L':
                        head.x--;
                        break;
                    case 'U':
                        head.y++;
                        break;
                    case 'D':
                        head.y--;
                        break;
                }

                //update all knots bassed head change
                for(int k = 0; k < knots.size(); k++) {
                    if(k == 0) {
                        process_move(head, knots[k]);
                    } else {
                        process_move(knots[k-1], knots[k]);
                    }
                }

                auto result = trackMap.insert(std::make_pair(knots[8].x, knots[8].y));

                if(result.second) {
                    count++;
                }
            }
        }

        return count;
    }

}