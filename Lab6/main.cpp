#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include "source/UltimateClass.hpp"

using namespace std;

int main() {
/*    multimap <int,int> myFirstMap = {{ 2, 37 },
                                   { 4, 40 },
                                   { 3, 15 },
                                   { 5, 15 }};
    myFirstMap.insert(pair<int,int>(5,100));
    for (const auto & i : myFirstMap) {
        cout << i.first << ":" << i.second << " ";

    }
    cout << endl;
    multimap <int,int> mySecondMap = {{ 2, 37 },
                                { 4, 40 },
                                { 3, 15 },
                                };
    for (const auto & i : mySecondMap) {
        cout << i.first << ":" << i.second << " ";

    }
    cout << endl;
    multimap <int,int> finalMap = myFirstMap;
    finalMap.insert(mySecondMap.cbegin(),mySecondMap.cend());

    for (const auto & i : finalMap) {
        cout << i.first << ":" << i.second << " ";

    }
    vector<int> vec1 = {1,2,3,4,5,6,2,4,1,6,2,13,5,2,14};
    vector<int> vec2 = {6,2};
    __gnu_cxx::__normal_iterator<const int *, vector<int, allocator<int>>> it1;
    while(true) {
        it1 = search(vec1.cbegin(), vec1.cend(), vec2.cbegin(), vec2.cend());
        if(it1 != vec1.cend())
        vec1.erase(it1, it1 + vec2.size());
        else break;
    }
    for(auto t : vec1)
        cout << t << " ";
    cout << endl;*/
    STLseq A = {1, 2, 3, 4, 5, 10, 15};
    STLseq B = {5, 3, 1, 6, 100};
    A.contact(B).showSeq();
    A.showMap();
    return 0;
}