#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;  // puntero al primer nodo
    int n;           // número de elementos

    // Devuelve puntero al nodo en la posición pos (0..n-1)
    Node<T>* node_at(int pos) const {
        if (pos < 0 || pos >= n) throw std::out_of_range("node_at: posicion invalida");
        Node<T>* cur = first;
        for (int i = 0; i < pos; ++i) cur = cur->next;
        return cur;
    }

public:
    // Constructor
    ListLinked() : first(nullptr), n(0) {}

    // Destructor: libera todos los nodos (estrategia pedida)
    ~ListLinked() override {
        while (first != nullptr) {
            Node<T>* aux = first->next; // 1) aux = first->next
            delete first;               // 2) liberar first
            first = aux;                // 3) avanzar first = aux
        }                                // 4) repetir hasta nullptr
        n = 0;
    }

    // Estado
    int  size()  const override { return n; }
    bool empty() const override { return n == 0; }

    // Acceso por valor
    T get(int pos) const override {
        return node_at(pos)->data;
    }

    // Operador [] por valor (según enunciado)
    T operator[](int pos) const {
        return node_at(pos)->data;
    }

    // Inserción general
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) throw std::out_of_range("insert: posicion invalida");
        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* prev = node_at(pos - 1);
            prev->next = new Node<T>(e, prev->next);
        }
        ++n;
    }
    void duplicate_list(int pos,T e) override {
        Node<T>*  aux = first;
    while (aux !=  nullptr) {
        Node<T>*  copia = new Node<T>(aux->data, aux->next);
        aux->next =   copia;                                
        aux = copia->next;                               
        n++;      
    }
    }
    void append (T e) override { insert(n, e); }
    void prepend(T e) override { insert(0, e); }

    // Eliminación y devolución del valor eliminado
    T remove(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("remove: posicion invalida");

        T val;
        if (pos == 0) {
            Node<T>* del = first;
            val = del->data;
            first = del->next;
            delete del;
        } else {
            Node<T>* prev = node_at(pos - 1);
            Node<T>* del  = prev->next;
            val = del->data;
            prev->next = del->next;
    delete del;
        }
        --n;
        return val;
    }

    // Búsqueda lineal
    int search(T e) const override {
        Node<T>* cur = first;
        int idx = 0;
        while (cur) {
            if (cur->data == e) return idx;
            cur = cur->next;
            ++idx;
        }
        return -1;
    }

    // Impresión
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const ListLinked<U>& list);
}; // fin clase

// Operador << externo
template <typename U>
std::ostream& operator<<(std::ostream& out, const ListLinked<U>& list) {
    out << "List => [\n";
    Node<U>* cur = list.first;
    while (cur) {
        out << "  " << cur->data << "\n";
        cur = cur->next;
    }
    out << "]\n";
    return out;
}

#endif // LIST_LINKED_H

