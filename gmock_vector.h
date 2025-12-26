#include<iostream>
#include<vector>
using namespace std;

class my_vector
{
    public:
    virtual void push(int n)=0;
    virtual void pop()=0;
    virtual int top()=0;
   virtual ~my_vector()=default;   
};