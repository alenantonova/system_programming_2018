#include <iostream>
#include <vector>
#include <assert.h>
#include <cstdio>
#include <string>

#define ASSERT_OK if(!ok()) {dump(error_msg); assert(!'failed');}
#define POISON 0xDEADBEEF
#define VAR_NAME(var) #var

template <class T>
class My_Stack {
private:
    unsigned int canary1 = POISON;
    std::string error_msg;
    long long sum;
    std::string name;
    size_t capacity;
    std::size_t size_;
    unsigned int canary2 = POISON;
    std::hash<T> hash_f;
    bool ok();
    void dump(std::string reason) const;
public:
    T * data_;
    My_Stack(size_t init_size, std::string var_name);
    void push(T elem);
    void pop();
    T top();
    size_t size();
    bool empty();
};

template <class T>
My_Stack<T>::My_Stack(size_t init_size, std::string var_name): error_msg("ok"){
    name = var_name;
    data_ = new T[init_size];
    for(int i = 0; i < init_size; i++) {
        data_[i] = POISON;
    }
    size_ = 0;
    capacity = init_size;
    sum = 0;
}

template <class T>
bool My_Stack<T>::ok() {
    if (size_ < 0) {
        error_msg = "Negative stack size";
        return false;
    }
    long long cur_sum = 0;
    int i = 0;
    while (data_[i] != POISON && i < capacity) {
        cur_sum += hash_f(data_[i]);
        i++;
    }
    if (cur_sum != sum) {
        error_msg = "Untracked item change";
        return false;
    }
    if (canary1 != POISON || canary2 != POISON) {
        error_msg = "Untracked memory change";
        return false;
    }
    return true;
}

template <class T>
void My_Stack<T>::dump(std::string msg) const {
    std::printf("%s %s [%p] (%s)\n", "STACK", name.c_str(), this, msg.c_str());
    std::printf("%s %d\n", "SIZE", size_);
    std::printf("%s %X %s %X\n", "CANARY1", canary1, "CANARY2", canary2);
    std::printf("DATA[%d] [%p]: {\n", capacity, data_);
    int i = 0;
    while (i < capacity) {
        if (data_[i] != POISON) {
            std::printf("[%d]: %d\n", i, data_[i]);
        } else {
            std::printf("[%d]: %X\n", i, data_[i]);
        }
        i++;
    }
    std::printf("}\n");
}

template <class T>
size_t My_Stack<T>::size() {
    ASSERT_OK;
    return size_;
}

template <class T>
void My_Stack<T>::push(T elem) {
    ASSERT_OK;
    if (size_ == capacity) {
        dump("Stack is full: can't push element " + std::to_string(elem));
        return;
    }
    data_[size_] = elem;
    size_ += 1;
    sum += hash_f(elem);
    ASSERT_OK;
}

template <class T>
void My_Stack<T>::pop() {
    ASSERT_OK;
    if(empty()) {
        dump("Stack is empty: can't pop element");
        return;
    }
    T elem = data_[size_-1];
    data_[size_-1] = POISON;
    size_ -= 1;
    sum -= hash_f(elem);
    ASSERT_OK
}

template <class T>
T My_Stack<T>::top() {
    ASSERT_OK;
    if(empty()) {
        dump("Stack is empty: can't get element");
        return POISON;
    }
    return data_[size_ - 1];
}

template <class T>
bool My_Stack<T>::empty() {
    ASSERT_OK;
    return size_ == 0;
}





