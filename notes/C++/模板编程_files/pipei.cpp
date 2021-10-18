#include <iostream> 
// General case
template<typename T0, typename T1, typename T2>
struct S 
{  
    void id() 
    { std::cout<<"General"<<std::endl;}
}; 

// Special case 1
template<typename T0, typename T1>
struct S<T0, T1, char> 
{  
    void id() 
    { std::cout<<"Special case #1"<<std::endl;}
}; 

// Special case 2
template<typename T0>struct S<T0, char, char> 
{  
    void id() 
    {std::cout<<"Special case#2"<<std::endl;}
}; 

// Special case 3
template<typename T>
struct S<int, T, T> 
{  
    void id() {std::cout<<"Special case #3"<<std::endl;}
}; 

int main(int argc, char**argv) 
{   
    S<float, float, float>().id();  
    S<int, int, int>().id();  
    S<int, int, char>().id();  
    S<char, char, char>().id();  
    // S<int, char, char>().id(); /* compile error, can not decide which one is more special */   
    return EXIT_SUCCESS;
}
