#ifndef SINGLETON
#define SINGLETON
#include <assert.h>
#include <cstddef>
#include <iostream>

template <class T>
class Singleton{
public:
    static T* Instance()
    {
        if(!m_Instance) m_Instance=new T;
        assert(m_Instance!= NULL);
        return m_Instance;
    }
    static void ResetInstance()
    {
        delete m_Instance;
        m_Instance= NULL;
    }

protected:
    Singleton();
    ~Singleton()
      {
	std::cout << "Singleton destructor called" << std::endl;
	Singleton::ResetInstance();
      }
private:
    Singleton(Singleton const&);
    Singleton& operator=(Singleton const&);
    static T* m_Instance;
};

template <class T> T* Singleton<T>::m_Instance= NULL;
#endif // SINGLETON
