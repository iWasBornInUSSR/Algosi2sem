//
// Created by Admin on 05.05.2019.
//

#ifndef LAB5_NEWHASH_HPP
#define LAB5_NEWHASH_HPP

#include <list>
#include <vector>
#include <cstdio>
#include <iostream>
#include <random>
#include <memory>
#include <algorithm>

using namespace std;

class HashMap {

public:
    typedef unsigned short hashtype;

    // typedef std::vector<list < hashtype> *> ptr_list_type;
    HashMap() {
        table.resize(m);
        mark = numb++;
    }

    explicit HashMap(char i) : mark(numb++) {
        table.resize(m);
        for (hashtype j = 0; j < m; ++j) {
            if (rand() % 2) add(j);
        }
    }

    HashMap(initializer_list<hashtype> vals) : mark(numb++) {
        table.resize(m);
        for (auto &i : vals) {
            add(i);
        }
    }
    HashMap(HashMap const &A) {
        mark = numb++;
        table.resize(m);
        for (auto i : A.ptr_table) {
            add(*i);
        }
    }

    void add(hashtype val) {
        list<hashtype> &cpy = table.at(hash_function(val));
        ptr_table.push_back(cpy.insert(cpy.end(), val));
    }

    void add(initializer_list<hashtype> vals) {
        for (auto &i : vals) {
            add(i);
        }
    }

    void printTable();

    void printSequence();

    HashMap operator~() const;

    HashMap operator|(const HashMap &B) const;

    HashMap operator&(const HashMap &) const;

    HashMap operator^(const HashMap &B) const { return (~(*this & B) & (*this | B)); };

    HashMap &operator=(const HashMap &copy) {
        table.clear();
        ptr_table.clear();
        for (auto i :copy.ptr_table) {
            add(*i);
        }
        return (*this);
    };

    HashMap &concat(HashMap &B);

    HashMap &mul(unsigned int n);

    HashMap &excl(HashMap &);

    friend void whatHave(HashMap &e);

private:
    static unsigned numb;
    static const hashtype a = 97;
    static const hashtype b = 11;
    static const hashtype capacity = 26;
    static const hashtype m = capacity * 3;
    static const hashtype MAXINT = 100;
    vector<list<hashtype> > table;
    list<list<hashtype>::iterator> ptr_table;

    static bool pred(const list<hashtype>::iterator &c, const list<hashtype>::iterator &d) {
        return *c == *d;
    }
    static hashtype hash_function(hashtype x) {
        return (a * x + b) % m;
    }

    unsigned mark;
};

void HashMap::printTable() {

    printf("HashMap %d:\n", mark);
    hashtype p = 0;
    for (auto &i : table) {
        p++;
        if (!i.empty()) {
            printf("key - %2d = {", p);
            for (auto j : i) {
                printf("%4d", j);
            }
            printf("  }\n");
        }
    }
}

HashMap HashMap::operator~() const {
    HashMap C;
    for (hashtype i = 0; i < MAXINT; ++i) {
        if (table.at(hash_function(i)).empty())
            C.add(i);
        else {
            bool flag = true;
            for (auto t = table.at(hash_function(i)).begin(); t != table.at(hash_function(i)).end() && flag; t++)
                if (*t == i) flag = false;
            if (flag) C.add(i);
        }
    }


    return C;
}

HashMap HashMap::operator|(const HashMap &B) const {
    // if this == B return C(*this)
    HashMap C(*this);
    bool flag;
    for (hashtype i = 0; i < m; ++i) {
        if (!table.at(i).empty()) {
            for (auto c : B.table.at(i)) {
                flag = true;
                for (auto d : this->table.at(i)) {
                    if (c == d) {
                        flag = false;
                        break;
                    }
                }
                if (flag) C.add(c);
            }
        } else C.table.at(i) = B.table.at(i);
    }
    return C;
}

HashMap HashMap::operator&(const HashMap &B) const {
    HashMap C;
    bool flag;
    for (hashtype i = 0; i < m; ++i) {
        if (!table.at(i).empty() && !B.table.at(i).empty()) {
            for (auto c : B.table.at(i)) {
                flag = false;
                for (auto d : table.at(i)) {
                    if (c == d) {
                        flag = true;
                        break;
                    }
                }
                if (flag) C.add(c);
            }
        }
    }
    return C;
}

void whatHave(HashMap &e) {
    for (HashMap::hashtype i = 0; i < HashMap::m; ++i) {
        for (unsigned short &a : e.table.at(i)) {
            cout << a << " ";
        }
    }
    cout << endl;
}

void HashMap::printSequence() {
    for (auto i : ptr_table) {
        cout << *i << " ";
    }
    cout << endl;
}

HashMap &HashMap::concat(HashMap &B) {
    for (auto i : B.ptr_table) {
        add(*i);
    }
    return *this;
}

HashMap &HashMap::mul(unsigned int n) {
    auto cpy = ptr_table;
    for (int j = 0; j < n; ++j) {
        for (auto i : cpy) {
            add(*i);
        }
    }
    return *this;
}

HashMap &HashMap::excl(HashMap &B) {
    // экономия времени на обращение???
    // запихать значения в вектор?
//    const vector<list < hashtype> *> ptr_vector_cpy(ptr_table);
//    int deletionTimes = 0;
//    unsigned long size = ptr_vector_cpy.size() - B.ptr_table.size();
//    for (unsigned long i = 0; i < size + 1; ++i) {
//        bool flag = true;
//        for (unsigned long j = 0; j < B.ptr_table.size(); ++j) {
//            if (ptr_vector_cpy.at(i + j)->front() != B.ptr_table.at(j)->front()) {
//                flag = false;
//                break;
//            }
//        }
//        if (flag) {
//            // deleting from Map
//            for (auto c : B.ptr_table) {
//                table.at(hash_function(c->front())).erase(table.at(hash_function(c->front())).begin());
//            }
//            ptr_table.erase(ptr_table.cbegin() + i - B.ptr_table.size() * deletionTimes, ptr_table.cbegin()
//                                                                                         + i + B.ptr_table.size() -
//                                                                                         B.ptr_table.size() *
//                                                                                         deletionTimes); // subtract B.ptr_table.size() * deletionTimes
//            // because ptr_table size less than its copy
//            deletionTimes++;
//            i = i + B.ptr_table.size() - 1;
//        }
//    }
    unsigned size = B.ptr_table.size();
    while (true) {
        auto it = search(ptr_table.begin(), ptr_table.end(), B.ptr_table.begin(), B.ptr_table.end(), pred);
        if (it != ptr_table.end()) {
            for (int i = 0; i < size; ++i) {
                table.at(hash_function(**it)).erase(*it);
                it = ptr_table.erase(it);
            }
        } else break;
    }
    return *this;
}

#endif //LAB5_NEWHASH_HPP
