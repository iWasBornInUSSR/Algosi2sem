#include <iostream>
#include <vector>
#include "source/newHash.hpp"

using namespace std;

// TODO: shared ptr<> vs common ptr?
//  --A.concat(B).printSequence() error????
//  --указатель на лист или на элемент?
//  -- excl полностью или отдельные элементы
int main() {
    HashMap A;
    HashMap B;
    A.add({3, 4, 1});
    B.add({8, 1, 5, 2, 61, 2, 1, 1});
    A.mul(3);
    A.printSequence();
}