#include <complex.h>
#include <iostream>
#include <cstring>

/**************
 *  F*CK YE   *
 * IT IS WORK *
 **************/

template <typename T>

class Vctr{
public:
    Vctr(T* arr, unsigned int size){
        m_capacity = size;
        m_data = new T[m_capacity];
        memcpy(m_data, arr, size*sizeof(T));
        m_arr_size = size;
    }
    ~Vctr(){
        delete[] m_data;
    }
    //in theory it is fast operation
    void add_elem(T e){
        if(m_arr_size == m_capacity){
            resize();
        }
        m_data[m_arr_size] = e;
        ++m_arr_size;
    }
    T* get(){
        return m_data;
    }
    int get_size(){
        return m_arr_size;
    }
private:
    T* m_data = nullptr;
    unsigned int m_arr_size = 0;
    size_t m_capacity = 1;
    void resize(){
        m_capacity *= 2;
        T* new_data = new T [m_capacity];
        memcpy(new_data, m_data, m_capacity*sizeof(T));
        delete[] m_data;
        m_data = new_data;
    }
};

class Unit_tests{
public:
    void frst_test(){
        v.add_elem(9);
        v.add_elem(8);
        if(v.get()[5] == 9 && v.get()[6] == 8){
            std::cout << "first pass\n";
        }
        else{
            std::cout << "first failed\n";
        }
    }

private:
    int x[5] = {1,2,3,4,5};
    Vctr<int> v = {x, 5};
};

int main(){
    Unit_tests test;
    test.frst_test();
}