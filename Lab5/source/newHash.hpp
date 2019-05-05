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
#include <bits/unique_ptr.h>
#include <memory>

using namespace std;

class HashMap {

public:
    typedef unsigned short hashtype;

    HashMap() {
        table.resize(m);
        A = '0';
    }

    explicit HashMap(char i) : A(i) {
        table.resize(m);
        for (hashtype j = 0; j < m; ++j) {
            if (rand() % 2) add(j);
        }
    }

    void add(hashtype val) {
        table.at(hash_function(val)).push_back(val);
        ptr_table.push_back(&table.at(hash_function(val)));
    }

    void add(initializer_list<hashtype> vals) {
        for (auto &i : vals) {
            add(i);
        }
    }

    list<hashtype> get(hashtype key) {
        return table.at(key);
    }

    void printTable();

    void printSequence();

    HashMap operator~() const;

    HashMap operator|(const HashMap &B) const;

    HashMap operator&(const HashMap &) const;

    HashMap operator^(const HashMap &B) const { return (~(*this & B) & (*this | B)); };

    HashMap &operator=(const HashMap &copy) {
        table = copy.table;
        return (*this);
    };

    HashMap &concat(HashMap &B);

    HashMap &mul(unsigned int n);

    HashMap &excl();

    friend void whatHave(HashMap &e);

private:
    static const hashtype a = 97;
    static const hashtype b = 11;
    static const hashtype capacity = 26;
    static const hashtype m = capacity * 3;
    static const hashtype MAXINT = 100;
    vector<list<hashtype> > table;
    list<list<hashtype> *> ptr_table;

    static hashtype hash_function(hashtype x) {
        return (a * x + b) % m;
    }

    char A;
};

void HashMap::printTable() {

    printf("HashMap %c:\n", A);
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
            for (auto a = table.at(hash_function(i)).begin(); a != table.at(hash_function(i)).end() && flag; a++)
                if (*a == i) flag = false;
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
    for (HashMap::hashtype i = 0; i < HashMap::m; ++i)
        for (unsigned short &a : e.table.at(i))
            cout << a << " ";
    cout << endl;
}

void HashMap::printSequence() {
    for (auto i = ptr_table.cbegin(); i != ptr_table.cend(); ++i) {
        cout << i.operator*()->front() << " ";
    }
    cout << endl;
}

HashMap &HashMap::concat(HashMap &B) {
    for (auto i : B.ptr_table) {
        add(i->front());
    }
}

HashMap &HashMap::mul(unsigned int n) {
    vector<hashtype> temp;
    for (auto i = ptr_table.cbegin(); i != ptr_table.cend(); ++i) {
        temp.push_back(i.operator*()->front());
    }
    for (int j = 0; j < n; ++j) {
        for (auto k : temp) {
            add(k);
        }
    }
}

HashMap &HashMap::excl() {

}

#endif //LAB5_NEWHASH_HPP
