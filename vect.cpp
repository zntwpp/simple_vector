#include <complex.h>
#include <cstddef>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <utility>

//#define DEBUG_VCTR

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
        #ifdef DEBUG_VCTR
        std::cout << "constructor\n";
        #endif
    }
    ~Vctr(){
        delete[] m_data;
        m_data = nullptr;  
            
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

    void delete_elem_by_index(int index){
        bool passed_element = 0;
        T* new_data = new T[--m_arr_size];
        for(int i = 0; i < m_arr_size+1; ++i){
            if(i != index){
                //passed element becomes 1 if m_data[i] equal to e and all element will shift
                new_data[i-passed_element] = m_data[i];
            }
            else{
                passed_element=1;
            }
        }
        delete[] m_data;
        m_data = new_data;
    }

    void delete_elem(T e){
        int passed_element = 0;
        T* new_data = new T[m_arr_size];
        for(int i = 0; i < m_arr_size; ++i){
            if(m_data[i] != e){
                //passed element becomes 1 if m_data[i] equal to e and all element will shift
                new_data[i-passed_element] = m_data[i];
            }
            else{
                ++passed_element;
            }
        }
        m_arr_size -= passed_element;
        delete[] m_data;
        m_data = new_data;
    }

    void sort(){
        for (int i = 0; i < m_arr_size; ++i){
            for(int j = 0; j < m_arr_size; ++j){
                if(m_data[j] > m_data[j+1]){
                    //add_elem(add_rvalue_elem too) is adding element to the end of the array
                    add_rvalue_elem(std::move(m_data[j]));
                    delete_elem_by_index(j);
                }
            }
        }
    }

    void clear(){
        m_capacity = 1;
        m_arr_size = 0;
        delete[] m_data;
        m_data = nullptr;
        m_data = new T [m_capacity];
    }

    T& operator[](int index){
        return m_data[index];
    }
    
    void operator=(const Vctr& v){
        if (this != &v){
            delete[] m_data;
            m_data = nullptr;
            m_arr_size = v.m_arr_size;
            m_capacity = v.m_capacity;
            m_data = new T[m_capacity];
            memcpy(m_data, v.m_data, m_capacity*sizeof(T));
        }
    }

    const T get() const{
        return *m_data;
    }

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
        std::move(m_data, m_data+m_capacity, new_data); 
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
            std::cout << "first passed\n";
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
            std::cout << "second passed\n";
        }
        else{
            std::cout << "second failed\n";
        }
    }
    void thrd_test(){
        Vctr<int> v2;
        v2 = v;
        if(v.get() == v2.get()){
            std::cout << "third passed\n";
        }
        else{
            std::cout << "third failed\n";
        }
    }
    void four_test()
    {
        v.add_elem(111);
        v.delete_elem_by_index(0);
        if(v[0] == 8 && v[1] == 111){
            std::cout << "four passed\n";
        }
        else{
            std::cout << "four failed\n";
        }
    }
    void five_test(){
        Vctr<int> nums;
        nums.add_elem(2);
        nums.add_elem(73);
        nums.add_elem(4);
        nums.add_elem(1);
        nums.add_elem(-48);
        nums.sort();
        if(nums[0] == -48 && nums[5] == 73){
            std::cout << "five passed\n";
        }
        else{
            std::cout << "five failed\n";
        }
    }
    void six_test(){
        Vctr<bool> b;
        b.add_elem(1);
        b.add_elem(1);
        b.add_elem(0);
        b.delete_elem(1);
        if(b.get_size() == 1){
            std::cout << "six passed\n";
        }
        else{
            std::cout << "six failed\n";
        }
    }

private:
    int x[5] = {1,2,3,4,5};
    Vctr<int> v = {x, 5};
};

int main(){
    clock_t start, end;

    Unit_tests tests;
    start = clock();
    tests.frst_test();
    tests.scnd_test();
    tests.thrd_test();
    tests.four_test();
    tests.five_test();
    tests.six_test();
    end = clock();
    double executable_time = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "time taken: " << std::fixed << executable_time << std::setprecision(5) << std::endl;
}