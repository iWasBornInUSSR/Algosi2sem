#include <utility>

//
// Created by Admin on 08.05.2019.
//
#ifndef LAB6_ULTIMATECLASS_HPP
#define LAB6_ULTIMATECLASS_HPP
using namespace std;

#include <set>
#include <list>
#include <numeric>

class newList {
private:
    char name;
    list<int> variety;
    const unsigned MAX_INT = 100;

    list<int> makeSet() {
        list<int> copy(variety);
        copy.sort();
        auto it1 = unique(copy.begin(), copy.end());
        copy.erase(it1, copy.end());
        return copy;
    }
    //
public:
    //newList()
    newList(char A, unsigned n) : name('A') {
        for (int i = 0; i < n; ++i) {
            if (rand() % 2) {
                variety.push_back(rand() % MAX_INT);
            }
        }
    }

    newList &mul(unsigned n);

    void push_back(int val) {
        variety.insert(variety.cend(), val);
    }

    void add_values(initializer_list<int> list) {
        for (auto &a : list)
            push_back(a);
    }

    newList(initializer_list<int> list) : name('0') {
        for (auto &a : list)
            push_back(a);
    }

    newList(list<int> copylist) : name('0'), variety(std::move(copylist)) {};

    void showMap();

    newList &contact(newList &another);

    newList &excl(newList &another);

    newList operator^(newList &another);

    newList operator&(newList &another);

    newList operator~();

    newList operator|(newList &another);


};

void newList::showMap() {
    for (auto &i : variety) {
        cout << i << " ";
    }
    cout << endl;
}


newList &newList::contact(newList &another) {
    variety.insert(variety.cend(), another.variety.cbegin(), another.variety.cend());
    return *this;
}

newList &newList::mul(unsigned n) {
    auto tmp = variety;
    for (int i = 0; i < n; ++i) {
        variety.insert(variety.cend(), tmp.begin(), tmp.end());
    }
    return *this;
}

newList &newList::excl(newList &another) { //стоит ли игра свеч??
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
newList newList::operator^(newList &another) {

    list<int> copy(makeSet());
    list<int> copyA(another.makeSet());
    list<int> newObj;
    set_symmetric_difference(copy.begin(), copy.end(), copyA.begin(), copyA.end(), back_inserter(newObj));
    return newList(newObj);
}

newList newList::operator&(newList &another) {
    list<int> copy(makeSet());
    list<int> copyA(another.makeSet());
    list<int> newObj;
    set_intersection(copy.begin(), copy.end(), copyA.begin(), copyA.end(), back_inserter(newObj));
    return newList(newObj);
}

newList newList::operator~() {
    list<int> copy(makeSet());
    list<int> full;
    full.resize(MAX_INT + 1);
    iota(full.begin(), full.end(), 0);
    list<int> newObj;
    set_difference(full.begin(), full.end(), copy.begin(), copy.end(), back_inserter(newObj));
    return newList(newObj);
}

newList newList::operator|(newList &another) {
    list<int> copy(makeSet());
    list<int> copyA(another.makeSet());
    list<int> newObj;
    set_union(copy.begin(), copy.end(), copyA.begin(), copyA.end(), back_inserter(newObj));
    return newList(newObj);
}


#endif //LAB6_ULTIMATECLASS_HPP
