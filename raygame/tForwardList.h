#pragma once

template<typename T>
class tForwardList
{
    struct Node
    {
        T data;
        Node * next;
    };

    Node * head;

public:
    tForwardList() {}
    ~tForwardList() {}

    void push_front(const T& val);
    void pop_front();

    T& front();
    const T& front() const;

    void remove(const T& val);
};

// todo: copy, empty, resize, clear