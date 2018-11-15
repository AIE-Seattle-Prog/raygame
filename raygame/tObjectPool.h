#pragma once

template<typename T>
class tObjectPool
{
    ObjectPool();                       // default initializes the object pool
    ObjectPool(size_t initialCapacity); // initializes the pool to have a set number of objects
    ~ObjectPool();                      // destroys all objects

    T* pool;
    bool* free;

    T* retrieve();                      // returns a pointer to an object that will be used (returns null if none available)
    void recycle(T* obj);               // accepts a pointer that can be used in the future

    size_t capacity();                  // returns the total number of objects that this pool can provide
};