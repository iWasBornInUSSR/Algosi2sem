//
// Created by Admin on 08.05.2019.
//
#ifndef LAB6_ULTIMATECLASS_HPP
#define LAB6_ULTIMATECLASS_HPP
using namespace std;

#include <set>

class newSet {
private:
    char name;
    set<int> variety;

public:
    newSet(char A, unsigned n) : name('A') {
        for (int i = 0; i < n; ++i) {
            if (rand() % 2) {
                variety.insert(rand() % 100);
            }
        }
    }

    newSet &mul(unsigned n);

    void push_back(int val) {
        variety.insert(variety.cend(), val);
    }

    void add_values(initializer_list<int> list) {
        for (auto &a : list)
            push_back(a);
    }

    newSet(initializer_list<int> list) : name('0') {
        for (auto &a : list)
            push_back(a);
    }


    void showMap();

    newSet &contact(newSet &another);

    newSet &excl(newSet &another);

};

void newSet::showMap() {
    for (auto &i : variety) {
        cout << i << " ";
    }
    cout << endl;
}

newSet &newSet::contact(newSet &another) {
    variety.insert(another.variety.cbegin(), another.variety.cend());
    return *this;
}

newSet &newSet::mul(unsigned n) {
    auto tmp = variety;
    for (int i = 0; i < n; ++i) {
        variety.insert(tmp.begin(), tmp.end());
    }
    return *this;
}

newSet &newSet::excl(newSet &another) { //стоит ли игра свеч??
    /* vector<int> tmp1(variety.begin(),variety.cend());
     vector<int> tmp2(another.variety.begin(),another.variety.cend());
     unsigned size = another.variety.size();
     for (auto it = tmp1.begin(); it != tmp1.end() - size;) {
         if(equal(it,it + size,tmp2.cbegin(),tmp2.cend())){
             it = tmp1.erase(it,it + size);
         } else it++;
     }
     variety.clear();
     variety.insert(tmp1.begin(),tmp1.end());*/
    //vector<int> tmp1(variety.begin(),variety.cend());
    //vector<int> tmp2(another.variety.begin(),another.variety.cend());
    unsigned size = another.variety.size();
    while (true) {
        auto it = search(variety.begin(), variety.end(), another.variety.begin(), another.variety.end());
        if (it != variety.end()) {
            for (int i = 0; i < size; ++i) {
                variety.erase(it++);
            }
            //   tmp1.erase(it,it + size);
        } else break;
    }
    //variety.clear();
    //variety.insert(tmp1.begin(),tmp1.end());
    return *this;
}
//
//STLseq STLseq::symDiff(STLseq &another) {
//    STLseq C(1);
//    set_symmetric_difference(variety.cbegin(),variety.cend(),another.variety.cbegin(),variety.cend(),C.variety.begin());
//    C.showMap();
//    return C;
//}

#endif //LAB6_ULTIMATECLASS_HPP
