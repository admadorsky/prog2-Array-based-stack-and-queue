#ifndef LAB3_ABQ_H
#define LAB3_ABQ_H

template <class T> class ABQ {
public:
    // constructors
    ABQ() ;
    ABQ(int capacity) ;

    // the big three
    ABQ(const ABQ &d) ;
    ABQ &operator=(const ABQ &d) ;
    ~ABQ() ;

    // void funcs
    void enqueue(T data) ;

    // template funcs
    T dequeue() ;
    T peek() ;

    // accessor funcs
    unsigned int getSize() ;
    unsigned int getMaxCapacity() ;
    T *getData() ;
private:
    unsigned int size ;
    unsigned int max_capacity ;
    float scale_factor = 2.0f ;
    T *queue ;
};

// default constructor
template <class T> ABQ<T>::ABQ() {
    size = 0 ;
    max_capacity = 1 ;
    queue = new T[max_capacity] ;
}

// overloaded constructor
template <class T> ABQ<T>::ABQ(int capacity) {
    size = 0 ;
    max_capacity = capacity ;
    queue = new T[max_capacity] ;
}

// copy constructor
template <class T> ABQ<T>::ABQ(const ABQ &d) {
    size = d.size ;
    max_capacity = d.max_capacity ;
    queue = new T[max_capacity] ;

    for (unsigned int i = 0; i < size; i++) {
        queue[i] = d.stack[i] ;
    }
}

// copy assignment operator
template<class T> ABQ<T>&ABQ<T>::operator=(const ABQ &d) {
    if (queue != d.queue) {
        queue = nullptr ;
        queue = new T[max_capacity] ;
        for (unsigned int i = 0; i < d.size; i++) {
            queue[i] = d.queue[i] ;
        }
    }
    // because C.A.O.
    return *this ;
}

// destructor
template<class T> ABQ<T>::~ABQ() {
    delete[] queue ;
}

// add to the "end of the line": enqueue
template<class T> void ABQ<T>::enqueue(T data) {
    // check if more space is needed
    if (size >= max_capacity) {
        // create a temporary array with double the space
        max_capacity *= scale_factor;
        T *tempstack = new T[max_capacity];
        // populate it with the data currently in queue, leaving a space at the end
        for (unsigned int i = 0; i < size; i++) {
            tempstack[i + 1] = queue[i];
        }
        // reassign the pointer, making the active queue the same as temp
        delete[] queue ;
        queue = tempstack ;
    }
    // add the enqueued data to the end of the line
    queue[0] = data ;
    size ++ ;
}

// remove one item from the "front of the line" and return its value: dequeue
template<class T> T ABQ<T>::dequeue() {
    T first_in_line = queue[size - 1] ;
    if ((size - 1) < (max_capacity / scale_factor)) {
        max_capacity /= (int)scale_factor ;
        T *tempstack = new T[max_capacity] ;
        for (int i = 0; i < size - 1; i++) {
            tempstack[i] = queue[i] ;
        }
    }

}

#endif //LAB3_ABQ_H
