#include <complex.h>
#include <cstddef>
#include <iostream>
#include <cstring>

template <typename T>

class Vctr{
public:
    Vctr(T* arr, unsigned int size){
        m_capacity = size;
        m_data = new T[m_capacity];
        memcpy(m_data, arr, size*sizeof(T));
        m_arr_size = size;
        #ifdef DEBUG_VCTR
        std::cout << "constructor\n";
        #endif
    }
    Vctr(){
        m_data = new T [m_capacity];
    }
    ~Vctr(){
        if(m_data != nullptr){
            delete[] m_data;
            m_data = nullptr;  
        }
        #ifdef DEBUG_VCTR
        std::cout << "destructor\n";
        #endif
        
    }
    //in theory it is fast operation
    void add_elem(T e){
        if(m_arr_size == m_capacity){
            resize();
        }
        m_data[m_arr_size] = e;
        ++m_arr_size; 
    }
    //rvalue adding element
    void add_rvalue_elem(T&& e){
        if(m_arr_size == m_capacity){
            resize();
        }
        m_data[m_arr_size] = std::move(e);
        ++m_arr_size; 
    }

    void clear(){
        m_capacity = 1;
        m_arr_size = 0;
        delete[] m_data;
        m_data = nullptr;
        m_data = new T [m_capacity];
    }

    T operator[](int index){
        return m_data[index];
    }

    /* not working
    void operator=(Vctr v){
        if (this != &v){
            delete[] m_data;
            m_data = nullptr;
            m_arr_size = v.m_arr_size;
            m_capacity = v.m_capacity;
            m_data = new T[m_capacity];
            memcpy(m_data, v.m_data, m_capacity*sizeof(T));
        }
    }*/

    int get_size(){
        return m_arr_size;
    }

    void print_vctr(){
        for(int i = 0; i < m_arr_size; ++i){
            std::cout << m_data[i] << " ";
        }
        std::cout << "\n";
    }
private:
    T* m_data = nullptr;
    unsigned int m_arr_size = 0;
    size_t m_capacity = 1;

    void resize(){
        m_capacity *= 2;
        #ifdef DEBUG_VCTR
        std::cout << "resizing, capacity = " << m_capacity << "\n";
        #endif
        T* new_data = new T [m_capacity];
        memcpy(new_data, m_data, m_capacity*sizeof(T));
        delete[] m_data;
        m_data = nullptr;
        m_data = new_data;
    }
};

class Unit_tests{
public:
    void frst_test(){
        v.add_elem(9);
        v.add_elem(8);
        if(v[5] == 9 && v[6] == 8){
            std::cout << "first pass\n";
        }
        else{
            std::cout << "first failed\n";
        }
    }
    void scnd_test(){
        v.clear();
        v.add_rvalue_elem(5);
        v.add_rvalue_elem(8);
        if(v[0] == 5 && v[1] == 8){
            std::cout << "second pass\n";
        }
        else{
            std::cout << "second failed\n";
        }
    }

private:
    int x[5] = {1,2,3,4,5};
    Vctr<int> v = {x, 5};
};

int main(){
    Unit_tests tests;
    tests.frst_test();
    tests.scnd_test();
}