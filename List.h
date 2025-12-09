
    #ifndef LIST_H
#define LIST_H

// Interfaz genérica y abstracta de una EDL Lista
// Métodos virtuales puros según especificación

template <typename T>
class List {
public:
    virtual ~List() = default;

    virtual void insert(int pos, T e) = 0;
    virtual void append(T e) = 0;
    virtual void prepend(T e) = 0;
    virtual T remove(int pos) = 0;
virtual T get(int pos) const = 0;
    virtual int search(T e) const = 0;
    virtual bool empty() const = 0;
    virtual int  size()  const = 0;
    virtual void duplicate_list(int pos,T e) = 0;
};

#endif // LIST_H
