#ifndef LAB3_ABS_H
#define LAB3_ABS_H
using namespace std ;

template<class T> class ABS {
public:
    // (DONE) constructors
    ABS() ;
    ABS(int capacity) ;

    // (DONE) the big three
    ABS(const ABS &d) ;
    ABS &operator=(const ABS &d) ;
    ~ABS() ;

    // (DONE) void funcs
    void push(T data) ;

    // (DONE) template funcs
    T pop() ;
    T peek() ;

    // (DONE) accessor funcs
    unsigned int getSize() ;
    unsigned int getMaxCapacity() ;
    // :(
    T *getData() ;

private:
    unsigned int size ;
    unsigned int max_capacity ;
    T *stack ;
    float scale_factor = 2.0f ;
};

// default constructor
template<class T> ABS<T>::ABS() {
    size = 0 ;
    max_capacity = 1 ;
    stack = new T[max_capacity] ;
}

// constructor with specified starting capacity
template<class T> ABS<T>::ABS(int capacity) {
    size = 0 ;
    max_capacity = capacity ;
    stack = new T[max_capacity] ;
}

template<class T> ABS<T>::ABS(const ABS &d) {
    size = d.size ;
    max_capacity = d.max_capacity ;
    stack = new T[max_capacity] ;

    for (unsigned int i = 0; i < size; i++) {
        stack[i] = d.stack[i] ;
    }
}

template<class T>
ABS<T>&ABS<T>::operator=(const ABS &d) {
    if (stack != d.stack) {
        stack = nullptr ;
        stack = new T[max_capacity] ;
        for (unsigned int i = 0; i < d.size; i++) {
            stack[i] = d.stack[i] ;
        }
    }
    // because C.A.O.
    return *this ;
}

template<class T> ABS<T>::~ABS() {
    delete[] stack ;
}

template<class T> void ABS<T>::push(T data) {
    if (size >= max_capacity) {
        max_capacity *= scale_factor ;
        T *tempstack = new T[max_capacity] ;

        for (unsigned int i = 0; i < size; i++) {
            tempstack[i] = stack[i] ;
        }

        delete[] stack ;
        stack = tempstack ;
    }
    stack[size] = data ;
    size ++ ;
}

template<class T> T ABS<T>::pop() {
    if (size == 0) { throw std::runtime_error("Cannot pop empty stack") ; }

    T popped = stack[size - 1] ;
    size -= 1 ;

    if (size < max_capacity / scale_factor) {
        max_capacity /= (int)scale_factor ;
        T *tempstack = new T[max_capacity] ;
        for (unsigned int i = 0; i < size ; i++) {
            tempstack[i] = stack[i] ;
        }
        delete[] stack ;
        stack = tempstack ;
    }
    return popped ;
}

template<class T> T ABS<T>::peek() {
    if (size == 0) { throw std::runtime_error("Cannot peek empty stack"); }
    return stack[size - 1];
}

template<class T> unsigned int ABS<T>::getSize() {
    return size ;
}

template<class T> unsigned int ABS<T>::getMaxCapacity() {
    return max_capacity ;
}

template<class T> T *ABS<T>::getData() {
    return stack ;
}

#endif //LAB3_ABS_H