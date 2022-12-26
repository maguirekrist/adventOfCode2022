#include <set>

namespace day_six {

int count_markers(std::string& input) {
    //create a sliding window of 4 characters
    int count = 0;
    for(int i = 0; i < input.length(); i++) {
        std::set<char> window{};
        for(int j = 0; j < 4; j++) {
            if(i+j < input.length()) {
                window.insert(input[i+j]);
            }
        }

        if(window.size() == 4) {
            return (count + 4);
        } else {
            count++;
        }
    }

    return count;
}

int count_message_marker(std::string& input) {
    int count = 0;

    for(int i = 0; i < input.length(); i++) {
        std::set<char> window{};
        for(int j = 0; j < 14; j++) {
            if(i+j < input.length()) {
                window.insert(input[i+j]);
            }
        }

        if(window.size() == 14) {
            return (count + 14);
        } else {
            count++;
        }
    }

    return count;
}

}