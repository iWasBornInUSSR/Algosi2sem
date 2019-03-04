#include <iostream>
#include "source/Hash.h"
int main() {
    HashMap p;
    for (HashMap::hashtype i = 0; i < 50; ++i) {
        p.add(i);
    }
    whatHave(p);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}