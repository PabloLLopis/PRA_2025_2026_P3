#ifndef NODE_H
#define NODE_H

#include <ostream>

template <typename T>
class Node {
public:
    T data;           // dato almacenado
    Node<T>* next;    // siguiente nodo (nullptr si es el último)

    // Constructor: next por defecto a nullptr
    Node(T data, Node<T>* next = nullptr) : data(data), next(next) {}

    // Impresión: solo el dato
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Node<U>& node) {
        out << node.data;
        return out;
    }
};

#endif // NODE_H


