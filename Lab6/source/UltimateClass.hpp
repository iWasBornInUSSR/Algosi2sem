//
// Created by Admin on 08.05.2019.
//
#ifndef LAB6_ULTIMATECLASS_HPP
#define LAB6_ULTIMATECLASS_HPP
using namespace std;

class STLseq {
public:
    STLseq(char A, unsigned n) : name('A') {
        for (int i = 0; i < n; ++i) {
            if (rand() % 2) {
                variety.insert(pair<unsigned, int>(i, rand() % 100));
                seq.push_back(i);
                bigKey = i;
            }
        }
    };

    STLseq &mul(unsigned n) {
        auto tmp = variety;
        for (int i = 0; i < n; ++i) {
            variety.insert(tmp.cbegin(), tmp.cend());
            seq.insert(seq.cend(), seq.cbegin(), seq.cend());
        }
        return *this;
    }

    void push_back(int val) {
        bigKey++;
        variety.insert(pair<unsigned, int>(bigKey, val));
        seq.push_back(bigKey);
    }

    void add_values(initializer_list<int> list) {
        for (auto &a : list)
            push_back(a);
    }

    STLseq(initializer_list<int> list) : name('0'), bigKey(-1) {
        for (auto &a : list)
            push_back(a);
    }

    void showSeq() {
        for (auto &i : seq) {
            cout << variety.find(i)->second << " ";
        }
        cout << endl;
    }

    void showMap();

    STLseq &contact(STLseq &another);

private:
    char name;
    unsigned bigKey;
    multimap<unsigned, int> variety;
    vector<unsigned> seq;
};

void STLseq::showMap() {
    for (auto &i : variety) {
        cout << i.first << ":" << i.second << " ";
    }
    cout << endl;
}

STLseq &STLseq::contact(STLseq &another) {
    bigKey = max(bigKey, another.bigKey);
    for (auto &i : another.variety) {
        push_back(i.second);

    }// add no insetrt
    return *this;
}

#endif //LAB6_ULTIMATECLASS_HPP
