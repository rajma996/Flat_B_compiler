#include <iostream>
using namespace std;

class A
{
    public:
        virtual void f(){cout << "A::f()" << endl;}
};

class B : public A
{
    public:
        void f(){cout << "B::f()" << endl;}
};

int main()
{
    A a;
    B b;
    a.f();        // A::f()
    b.f();        // B::f()

    A *pA = &a;   
    B *pB = &b;   
    pA->f();      // A::f()
    pB->f();      // B::f()

    pA = &b;
    // pB = &a;      // not allowed
      pB = dynamic_cast<B*>(pA); // allowed but it returns NULL
    
          return 0;
          }
