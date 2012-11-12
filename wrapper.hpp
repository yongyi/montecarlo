/*
 * wrapper template for handling pointers of type T
 *
 * handles memory management automatically - mimic the smart pointer in a simpler way
 *
 */

#ifndef WRAPPER_HPP
#define WRAPPER_HPP

template<class T>
class Wrapper{

    private:
        T* ptr;

    public:
        Wrapper();
        Wrapper(const Wrapper<T> &input);
        Wrapper(const T& input);
        ~Wrapper();

        Wrapper& operator =(const Wrapper &input);

        T& operator *();
        const T& operator *() const;

        T* operator ->();
        const T* operator ->() const;


};


#ifndef WRAPPER_CPP
#include"wrapper.cpp"
#endif

#endif
