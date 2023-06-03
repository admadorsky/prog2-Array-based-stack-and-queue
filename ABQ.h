#ifndef LAB3_ABQ_H
#define LAB3_ABQ_H
using namespace std ;

template <class T> class ABQ {
public:
    // (DONE) constructors
    ABQ() ;
    ABQ(int capacity) ;

    // (DONE) the big three
    ABQ(const ABQ &d) ;
    ABQ &operator=(const ABQ &d) ;
    ~ABQ() ;

    // (DONE) void funcs
    void enqueue(T data) ;

    // (DONE) template funcs
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
    }
    T *tempqueue = new T[max_capacity];
    // populate it with the data currently in queue, leaving a space at the end
    for (unsigned int i = 0; i < size; i++) {
        tempqueue[i + 1] = queue[i];
    }
    // reassign the pointer, making the active queue the same as temp
    delete[] queue ;
    queue = tempqueue ;
    // add the enqueued data to the end of the line
    queue[0] = data ;
    size ++ ;
}

// remove one item from the "front of the line" and return its value: dequeue
template<class T> T ABQ<T>::dequeue() {
    if (size == 0) { throw runtime_error("Cannot dequeue empty queue") ; }

    T first_in_line = queue[size - 1] ;
    // effectively removes the first item in the list
    size -= 1 ;

    // check if array needs resizing
    if ((size) < (max_capacity / scale_factor)) {
        max_capacity /= (int)scale_factor ;
        T *tempqueue = new T[max_capacity] ;
        /* copy everything into resized temp array except for the head
        (remember size decreased by 1 already) */
        for (unsigned int i = 0; i < size; i++) {
            tempqueue[i] = queue[i] ;
        }
        // reassign the active array pointer to the temp array
        delete[] queue ;
        queue = tempqueue ;
    }
    return first_in_line ;
}

template<class T> T ABQ<T>::peek() {
    if (size == 0) { throw runtime_error("Cannot peek into an empty queue") ; }
    // returns value at the "front of the line"
    return queue[size - 1] ;
}

template<class T> unsigned int ABQ<T>::getSize() {
    return size ;
}

template<class T> unsigned int ABQ<T>::getMaxCapacity() {
    return max_capacity ;
}

template<class T> T *ABQ<T>::getData() {
    return queue ;
}

#endif //LAB3_ABQ_H
