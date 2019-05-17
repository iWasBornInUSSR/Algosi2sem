#include <iostream>
#include <vector>
#include "source/newHash.hpp"

using namespace std;

// TODO: shared_ptr<> vs common ptr?
//  -- сохраняются ли итераторы при копировании?
unsigned HashMap::numb = 0;
int main() {
    HashMap A({1, 2, 3, 5, 2, 3, 12, 5, 2, 3, 4, 2, 6, 2, 3}), C({2, 3});
    HashMap B({5, 8, 9, 1, 6, 2, 6, 50});
    (A & C).printTable();
    (A | B).printTable();
    (A ^ C).printTable();
    (~A).printTable();
    A.excl(C).printSequence();
    C.mul(4).printSequence();
    A.concat(B).printSequence();
}