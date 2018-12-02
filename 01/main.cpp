#include <iostream>
#include <map>

int main(int argc, char *argv[]) {
    std::map<int, bool> m;
    int f = 0;

    while (std::cin) {
        int input = 0;
        std::cin >> input;
        f += input;

        auto s = m.find(f);

        if (s != m.end()) {
            break;
        }

        m.insert({f, true});
    }

    std::cout << f << std::endl;
    return 0;
}
