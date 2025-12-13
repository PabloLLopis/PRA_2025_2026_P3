#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    ~BSTreeDict() {
        delete tree;
    }

    int entries() override {
        return tree->size();
    }

    void insert(std::string key, V value) override {
        TableEntry<V> e(key, value);
        tree->insert(e);
    }

    V search(std::string key) override {
        TableEntry<V> e(key);
        return tree->search(e).value;
    }

    V remove(std::string key) override {
        TableEntry<V> e(key);
        V val = tree->search(e).value;
        tree->remove(e);
        return val;
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        out << *(bs.tree);
        return out;
    }
};

#endif

