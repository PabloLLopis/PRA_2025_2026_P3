#ifndef BSTREE_H
#define BSTREE_H

#include <stdexcept>
#include <ostream>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    BSNode<T>* root;
    int nelems;

    // Inserción recursiva
    BSNode<T>* insert_rec(BSNode<T>* node, T elem) {
        if (node == nullptr) return new BSNode<T>(elem);

        if (elem < node->elem) node->left = insert_rec(node->left, elem);
        else if (elem > node->elem) node->right = insert_rec(node->right, elem);
        else throw std::runtime_error("Duplicated element!");

        return node;
    }

    // Búsqueda recursiva
    T search_rec(BSNode<T>* node, T elem) const {
        if (node == nullptr)
            throw std::runtime_error("Element not found!");

        if (elem == node->elem) return node->elem;
        if (elem < node->elem) return search_rec(node->left, elem);
        else return search_rec(node->right, elem);
    }

    // Eliminar mínimo desde nodo
    BSNode<T>* remove_min(BSNode<T>* node, T &minElem) {
        if (node->left == nullptr) {
            minElem = node->elem;
            return node->right;
        }
        node->left = remove_min(node->left, minElem);
        return node;
    }

    // Eliminación recursiva
    BSNode<T>* remove_rec(BSNode<T>* node, T elem, T &removed) {
        if (node == nullptr)
            throw std::runtime_error("Element not found!");

        if (elem < node->elem)
            node->left = remove_rec(node->left, elem, removed);
        else if (elem > node->elem)
            node->right = remove_rec(node->right, elem, removed);
        else {
            removed = node->elem;

            if (node->left == nullptr) return node->right;
            if (node->right == nullptr) return node->left;

            T minElem;
            node->right = remove_min(node->right, minElem);
            node->elem = minElem;
        }
        return node;
    }

    // Impresión inorder
    void print_inorder(std::ostream &out, BSNode<T>* node) const {
        if (node == nullptr) return;
        print_inorder(out, node->left);
        out << node->elem << " ";
        print_inorder(out, node->right);
    }

    // Liberar memoria
    void clear(BSNode<T>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BSTree() : root(nullptr), nelems(0) {}

    ~BSTree() {
        clear(root);
    }

    int size() const {
        return nelems;
    }

    void insert(T elem) {
        root = insert_rec(root, elem);
        nelems++;
    }

    T search(T elem) const {
        return search_rec(root, elem);
    }

    T remove(T elem) {
        T removed;
        root = remove_rec(root, elem, removed);
        nelems--;
        return removed;
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &tree) {
        tree.print_inorder(out, tree.root);
        return out;
    }
};

#endif


