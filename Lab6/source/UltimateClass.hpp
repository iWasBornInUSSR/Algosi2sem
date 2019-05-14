//
// Created by Admin on 08.05.2019.
//
#ifndef LAB6_ULTIMATECLASS_HPP
#define LAB6_ULTIMATECLASS_HPP
using namespace std;

bool pred(const set<int>::iterator &a, const set<int>::iterator &b) {
    return *a == *b;
}

class coolIterSet {
public:
    explicit coolIterSet(unsigned n) : name(code_name++) {
        for (int i = 0; i < n; ++i) {
            if (rand() % 2) {
                seq.push_back(variety.insert(rand() % 100));
            }
        }
    };

    coolIterSet(multiset<int> copySet, list<multiset<int>::iterator> copyList) : variety(move(copySet)),
                                                                                 seq(move(copyList)),
                                                                                 name(code_name++) {};

    void push_back(int val) {
        seq.push_back(variety.insert(val));
    }

    void add_values(initializer_list<int> list) {
        for (auto &a : list)
            push_back(a);
    }

    coolIterSet(initializer_list<int> list) : name('0') {
        for (auto &a : list)
            push_back(a);
    }

    void showSeq() {
        for (auto &i : seq) {
            cout << *i << " ";
        }
        cout << endl;
    }

    coolIterSet &mul(unsigned n);

    coolIterSet &contact(coolIterSet &another);

    coolIterSet &excl(coolIterSet &another);

    coolIterSet operator&(coolIterSet &another);

    coolIterSet operator|(coolIterSet &another);

    coolIterSet operator^(coolIterSet &another);

    coolIterSet operator~();
private:
    int name;
    static int code_name;
    static const int MAX_INT = 100;
    multiset<int> variety;
    list<multiset<int>::iterator> seq;
};


coolIterSet &coolIterSet::contact(coolIterSet &another) {
    for (auto &i : another.seq) {
        push_back(*i);
    }
    return *this;
}

coolIterSet &coolIterSet::mul(unsigned n) {
    auto tmp = seq;
    for (int i = 0; i < n; ++i) {
        for (auto &it : tmp)
            push_back(*it);
    }
    return *this;
}

coolIterSet &coolIterSet::excl(coolIterSet &another) {
    unsigned size = another.seq.size();
    while (true) {
        auto it = search(seq.begin(), seq.end(), another.seq.begin(), another.seq.end(), pred);
        if (it != seq.end()) {
            for (int i = 0; i < size; ++i) {
                variety.erase(*it);
                it = seq.erase(it);
            }
        } else break;
    }
    return *this;
}

coolIterSet coolIterSet::operator^(coolIterSet &another) {

    multiset<int> newObj;
    list<multiset<int>::iterator> newIts;
    set_symmetric_difference(variety.begin(), variety.end(), another.variety.begin(), another.variety.end(),
                             back_inserter(newObj));
    for (auto it = newObj.begin(); it != newObj.end(); it++) {
        newIts.push_back(it);
    }
    return coolIterSet(newObj, newIts);
}

coolIterSet coolIterSet::operator&(coolIterSet &another) {
    multiset<int> newObj;
    list<multiset<int>::iterator> newIts;
    set_intersection(variety.begin(), variety.end(), another.variety.begin(), another.variety.end(),
                     back_inserter(newObj));
    for (auto it = newObj.begin(); it != newObj.end(); it++) {
        newIts.push_back(it);
    }
    return coolIterSet(newObj, newIts);
}

coolIterSet coolIterSet::operator~() {
    multiset<int> full;
    for (int i = 0; i < MAX_INT + 1; ++i) {
        full.insert(i);
    }
    multiset<int> newObj;
    list<multiset<int>::iterator> newIts;
    set_difference(full.begin(), full.end(), variety.begin(), variety.end(), back_inserter(newObj));
    for (auto it = newObj.begin(); it != newObj.end(); it++) {
        newIts.push_back(it);
    }
    return coolIterSet(newObj, newIts);
}

coolIterSet coolIterSet::operator|(coolIterSet &another) {
    multiset<int> newObj;
    list<multiset<int>::iterator> newIts;
    set_union(variety.begin(), variety.end(), another.variety.begin(), another.variety.end(), back_inserter(newObj));
    for (auto it = newObj.begin(); it != newObj.end(); it++) {
        newIts.push_back(it);
    }
    return coolIterSet(newObj, newIts);
}
#endif //LAB6_ULTIMATECLASS_HPP
