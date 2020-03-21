#include <cassert>
#include <cstring>
#include <iostream>

struct A
{
    char* data = nullptr;

    explicit A(const char* msg = 0) : data(new char[msg ? strlen(msg) + 1 : 0 + 1])
    {
        if (msg) {
            memcpy(data, msg, strlen(msg));
        }
    }

    virtual void say()
    {
        assert(data);
        std::cout << "A::say " << data << std::endl;
    }

    virtual ~A() { delete[] data; }

    A& operator=(A const& a)
    {
        if (this == &a)
            return *this;

        std::cout << "here" << std::endl;
        char* tmp_data = new char[strlen(a.data) + 1]{0};
        delete[] data;
        data[strlen(tmp_data) + 1] = '\0';
        memcpy(tmp_data, a.data, strlen(a.data));
        data = tmp_data;
        return *this;
    }
};

struct B : public A
{
    int* data = nullptr;

    void say() override { std::cout << "B::say " << *data << std::endl; }

    B() : A(), data(new int(0)) {}

    ~B() { delete data; }
};

int main(int, char**)
try {
    A* a = new A("hello");
    A* b = new B();

    a->say();
    *b = *a;
    b->say();

    delete a;
    delete b;
} catch (std::exception const& ex) {
    std::cout << ex.what() << std::endl;
}

/*struct A
{
    char* data;
    
    A(const char* msg = 0)
        : data(new char[msg ? strlen(msg) : 0 + 1 ])
    {
        if(msg)
        { memcpy(data, msg, strlen(msg)); }
    }
    
    virtual void say()
    { std::cout << "A::say " << data << std::endl; }
    
    ~A()
    { delete data; }
};

struct B: public A
{
    int *data;
    
    virtual void say()
    { std::cout << "B::say " << *data << std::endl; }
    
    B() : A() , data(new int(0))
    { }
    
    ~B() { delete data; }
};


int main(int, char**) try
{
    A* a = new A("hello");
    A* b = new B();
    
    a->say();
    
    *b = *a;
    
    b->say();
    
    delete a;
    delete b;
}
catch( std::exception const& ex)
{ std::cout << ex.what() << std::endl; }

---------------------------------------------
#include <iostream>
#include <vector>

class VectorBoolAPI
{
protected:
    void set_bit(size_t index, bool value); // already 
  bool get_bit(size_t index);             // implemented
};

// Implement VectorBool::operator[] using provided get/set_bit API

class VectorBool : public VectorBoolAPI
{
    class Proxy
    {
    public:
        Proxy(VectorBool & v, size_t index) :m_vector(v), m_index(index)
        {
        }
        
        bool operator=(bool value)
        {
            m_vector.set_bit(m_index, value);
            return value;
        }
        
        operator bool() const
        {
            return m_vector.get_bit(m_index);
        }
        
    private:
        VectorBool & m_vector;
        size_t m_index;
    };
    
public:
    Proxy operator[](size_t index)
    {
        return Proxy(*this, index);
    }
};


int main()
{
    VectorBool v; // = {true, false, true, false, ...}
    
    if(v[1]) 
  {  
    v[2] = v[4] = v[6] = false;
    }
    
    
    return 0;
}

// Mock implementation ----------------------------------------
void VectorBoolAPI::set_bit(size_t index, bool value)
{
    std::cout << std::boolalpha << '[' << index << "] = " << value << std::endl;
}

bool VectorBoolAPI::get_bit(size_t index)
{
    std::cout << "get_bit [" << index << "]" << std::endl;
    return index % 2;
}
//-------------------------------------------------------------
*/
