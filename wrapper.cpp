/*
 * implementation of the wrapper template
 */

#ifndef WRAPPER_CPP
#define WRAPPER_CPP

#include"wrapper.hpp"

template<typename T>
Wrapper<T>::Wrapper(): ptr(0){}

template<typename T>
Wrapper<T>::Wrapper(const Wrapper<T>& input){
    if(input.ptr == 0){ ptr = 0;}
    else{ ptr = input.ptr->clone();}
}

template<typename T>
Wrapper<T>::Wrapper(const T& input):ptr(input.clone()){}

template<typename T>
Wrapper<T>::~Wrapper(){
    if(ptr != 0) delete ptr;
}

template<typename T>
Wrapper<T>& Wrapper<T>::operator =(const Wrapper<T>& input){
    //both self-assignment safe and exception safe
    T* temp_ptr = ptr;
    ptr = (input.ptr == 0) ? 0 : (input.ptr->clone());

    //delete original pointer
    if(temp_ptr != 0){delete temp_ptr;}

    return *this;
}

template<typename T>
T& Wrapper<T>::operator *(){
    return *ptr;
}

template<typename T>
const T& Wrapper<T>::operator *() const{
    return *ptr;
}

template<typename T>
T* Wrapper<T>::operator ->(){
    return ptr;
}

template<typename T>
const T* Wrapper<T>::operator ->() const{
    return ptr;
}

#endif
