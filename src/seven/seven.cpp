#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <istream>
#include <ranges>

namespace day_seven {

struct Directory {

    //parent
    Directory* parent = nullptr;

    std::unordered_map<std::string, Directory*> subdirs;
    std::unordered_map<std::string, int> files;
};

class Tree {
public:
    Tree() {
        root = std::make_unique<Directory>();
    }

    std::unique_ptr<Directory> root;

    std::vector<std::unique_ptr<Directory>> dirs;
private:
};

Tree create_tree(std::istream& stream) {
    Tree tree;
    std::string currentDir;
    Directory* temp = tree.root.get();
    for(std::string line; std::getline(stream, line); ) {
        std::cout << line << std::endl;
        if(line.length() < 1)
            continue;    

        if(line.substr(2,2) == "cd") {
            //cd
            currentDir = line.substr(5);

            if(currentDir == "..") {
                if(temp->parent == nullptr)
                    temp = tree.root.get();
                else
                    temp = temp->parent;

                continue;
            }

            if(currentDir == "/") {
                continue;
            }

            if(temp->subdirs[currentDir] == nullptr) {
                std::abort();
            }

            temp = temp->subdirs[currentDir];

            continue;
        }

        if(line == "ls") {
            continue;
        }

        if(line.substr(0, 3) == "dir") {
            std::string dirName = line.substr(4);
            auto newDir = std::make_unique<Directory>();
            newDir->parent = temp;
            temp->subdirs[dirName] = newDir.get();
            tree.dirs.push_back(std::move(newDir));
            continue;
        }

        //then it is a file at this point
        if(line[0] != '$') {
            int size;
            std::string fileName;
            std::istringstream iss(line);

            if(!(iss >> size >> fileName)) std::abort();

            temp->files[fileName] = size;
        }

    }
    return tree;
} 

int recurse_total(const Directory& dir) {
    int total = 0;
    for(const auto& file : dir.files) {
        total += file.second;
    }

    for(const auto& subdir : dir.subdirs) {
        total += recurse_total(*subdir.second);
    }

    return total;
}

int calculate_dir_total(const Tree& tree) {
    int total = 0;

    for(const auto& dir : tree.dirs) {
        int temp = recurse_total(*dir);
        if(temp <= 100000) {
            total += temp;
        }
    }

    return total;
}

size_t find_smallest_but_sufficient(Directory* current, size_t goal) {

    auto values = std::views::transform([](auto& p) { return p.second; });
    auto dsz = current->subdirs | values | std::views::transform([goal](Directory* current) {
        return find_smallest_but_sufficient(current, goal);
    }) | std::views::filter([goal](size_t value) {
        return value >= goal;
    });

    if(dsz.empty()) return recurse_total(*current);

    return std::ranges::min(dsz);
}

int solveProblemTwo(const Tree& tree) {
    int spaceOfRoot = recurse_total(*tree.root);
    int currentLeftOver = 70000000 - spaceOfRoot;
    int spaceNeeded = 30000000 - currentLeftOver;



    return find_smallest_but_sufficient(tree.root.get(), spaceNeeded);
}

}