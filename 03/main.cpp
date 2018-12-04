#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <set>
#include <map>

int main(int argc, char *argv[]) {
    using claimedPoint = std::pair<unsigned int, unsigned int>;

    std::ifstream file("input.txt");
    std::map<claimedPoint, std::unique_ptr<std::vector<unsigned int>>> claimedPoints;
    std::set<unsigned int> ids;

    std::string line;
    while (std::getline(file, line)) {
        unsigned int claimId = 0;
        unsigned int claimX = 0;
        unsigned int claimY = 0;
        unsigned int claimWidth = 0;
        unsigned int claimHeight = 0;

        sscanf(line.c_str(), "#%u @ %u,%u: %ux%u", &claimId, &claimX, &claimY, &claimWidth, &claimHeight);

        ids.insert(claimId);

        for (unsigned int y = claimY; y < claimY + claimHeight; ++y) {
            for (unsigned int x = claimX; x < claimX + claimWidth; ++x) {
                const auto t = std::pair(x, y);
                claimedPoints.try_emplace(t, std::make_unique<std::vector<unsigned int>>());
                claimedPoints.at(t)->push_back(claimId);
            }
        }
    }

    unsigned long overlapping = 0;

    for (const auto& p : claimedPoints) {
        const auto pointIds = *p.second;
        const auto claimedBy = pointIds.size();

        if (claimedBy >= 2) {
            ++overlapping;

            for (const auto& id : pointIds) {
                ids.erase(id);
            }
        }
    }

    std::cout << "Overlapping:              " << overlapping << "\nNon overlapping claim id: " << *ids.begin() << std::endl;

    return 0;
}
