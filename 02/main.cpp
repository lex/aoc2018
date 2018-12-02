#include <iostream>
#include <fstream>
#include <array>
#include <vector>

int main(int argc, char *argv[]) {
    size_t two = 0;
    size_t three = 0;
    bool foundCommon = false;
    std::string common;
    std::vector<std::string> ids;

    std::ifstream file("input.txt");
    std::copy(std::istream_iterator<std::string>(file),
          std::istream_iterator<std::string>(),
          std::back_inserter(ids));

    for (auto& currentId : ids) {
        std::array<char, 26> counts = {0};

        for (auto& c : currentId) {
            counts.at(c - 'a') += 1;
        }

        bool gotTwo = false;
        bool gotThree = false;

        for (auto& c : counts) {
            if (c == 2)
                gotTwo = true;
            if (c == 3)
                gotThree = true;
        }

        two += gotTwo ? 1 : 0;
        three += gotThree ? 1 : 0;

        if (foundCommon) continue;

        for (auto& id : ids) {
            bool oneDifferent = false;
            size_t differentIndex = 0;

            for (size_t i = 0; i < id.length(); ++i) {
                char c1 = currentId.at(i);
                char c2 = id.at(i);

                if (c1 != c2) {
                    if (!oneDifferent) {
                        oneDifferent = true;
                        differentIndex = i;
                    } else {
                        oneDifferent = false;
                        break;
                    }
                }
            }

            if (oneDifferent) {
                foundCommon = true;

                for (size_t i = 0; i < id.length(); ++i) {
                    if (i != differentIndex) common.push_back(id.at(i));
                }
            }
        }
    }
    
    std::cout << "Checksum: " << two * three << '\n' << "Common:   " << common << std::endl;

    return 0;
}
