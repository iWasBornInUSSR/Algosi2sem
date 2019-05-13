#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include "source/UltimateClass.hpp"

using namespace std;

int main() {
    newList A = {1, 2,10, 7, 5,6};
    newList B = {6,5,7, 3,5,1};
    (A ^ B).showMap();
    (A | B).showMap();
    (A & B).showMap();
    (~A).showMap();

}