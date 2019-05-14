#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <unordered_set>
#include <list>
#include "source/UltimateClass.hpp"

using namespace std;

int main() {
    coolIterSet As = {1, 2, 3, 8, 3, 9, 1, 2};
    As.showSeq();
    coolIterSet Bs = {1, 2};
    Bs.showSeq();
    As.excl(Bs).showSeq();

    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~
    return 0;
}