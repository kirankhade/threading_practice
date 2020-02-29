#include <iostream>    
#include <algorithm>   
#include <vector>   
#include <thread>
#include <string>
#include <mutex>
#include <queue>
#include <future>


using namespace std;
// Using callable objects

class A {
  public:
  void f(int x, char c) {};
  int operator()(int n) {return 0;};
};



int main()
{
  //Different syntax to call threads and details
  A a;
  std::thread t1(a,6); //copy of a in diff thread
  std::thread t(std::ref(a),6); // a in diff thread
  std::thread t(std::move(a),6); // a is no longer avlbl in main thread
  std::thread t(A(), 6); //temp a
  std::thread t([](int x){return x*x;}, 6); //lambada in 
  std::thread t(foo, 7);
  std::thread t(&A::f, a,8, 'w'); //copy of a .f(8,w) in different thread
  std::thread t(&A::f,&a,8,'w'); // a.f(8,'w') in different thread
  
  // callable obj can be used in 
  // std::bind std::async std::call_once
return 0;
}