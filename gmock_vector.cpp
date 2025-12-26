#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include"gmock_vector.h"
using namespace testing;

using ::testing::Return;

class my_array:public my_vector
{
    protected:
    std::vector<int> v = {11,22,33,44,55,66,77,88,99};
    public:
    
    void push(int n)override{
        v.push_back(n);
    }

    void pop()override{
        v.erase(v.begin());
    }

    int top()override{
        return v.back();
    }
    
};

class vector_fake
{
    my_vector *p;
    public:

    vector_fake(my_vector *obj):p(obj){}

    void dlt(){

        p->pop();
    }
    void add(int n)
    {
        p->push(n);
    }
    int read(){
        return p->top();
    }
};

class MOCKmy_vector :public my_vector
{
    public:

    MOCK_METHOD(void,push,(int n),(override));
    MOCK_METHOD(void,pop,(),(override));
 MOCK_METHOD(int, top, (), (override));
};

TEST(my_vector,pushtest)
{
    MOCKmy_vector mock;
    
    vector_fake v(&mock);
    
    EXPECT_CALL(mock,push(_)).Times(3);
    EXPECT_CALL(mock,pop()).Times(1);
    EXPECT_CALL(mock,top()).Times(1)
    .WillOnce(::testing::Return(3));

   v.add(55);
   v.add(555);
   v.add(5555);
    v.dlt();
    int result = v.read();
    EXPECT_EQ(result,3);
}
TEST(my_vector,nocalltest)
{
    MOCKmy_vector vec;
    EXPECT_CALL(vec,push(50)).Times(0);
}

TEST(my_vector,GTLTtest)
{
    MOCKmy_vector vec;
    vector_fake v(&vec);

EXPECT_CALL(vec,push(Gt(50))).Times(3);

EXPECT_CALL(vec,top()).Times(3)
.WillOnce(Return (50))
.WillOnce(Return (55))
.WillOnce(Return (85));

v.add(70);
v.add(55);
v.add(77);

int one=v.read();
int two=v.read();
int three=v.read();

EXPECT_GE(one,50);
EXPECT_GE(two,50);
EXPECT_GE(three,50);
}

int main(int argc,char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
