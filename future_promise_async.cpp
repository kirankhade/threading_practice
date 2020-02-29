#include <iostream>    
#include <algorithm>   
#include <vector>   
#include <thread>
#include <string>
#include <mutex>
#include <queue>
#include <future>


using namespace std;

// Future and Promises
// 

mutex mu;
condition_variable cond;


void fact(int n, int & x)
{
  int res =1;
  for (int i=n;i>1;i--)
  {
   res *= i; 
  }
  cout << "res is : "<< res<< endl;
  x =res;
}

int fact1(int n)
{
  int res =1;
  for (int i=n;i>1;i--)
  {
   res *= i; 
  }
  cout << "res is : "<< res<< endl;
  return res;
}

int fact2(std::future<int>& f)
{
  int n = f.get();
  // do something with n 
  cout<<"Value by child is:"<<n<<endl;
  return n;
}

int main()
{
  int x;
  thread t1(fact, 4, std::ref(x)); //what I want launch thread and get result out of it 
  // as x is shared var between child and parent so to do we need mutex
  // also we can use x only after x is set by child so need cond var to notify parent
  // which becomes complicated
  // so std lib provides nicer way to achieve this
  // which is std::async and future
  // you can use async to call get res
  //eg
  std::future<int> fut = std::async(fact1,4);
  x = fut.get();
  // get func will wait until child thread finish 
  // future cast object which is something avl in future  only call once get func
  // async func may or may not create thread
  // we can defer function call until its call
  // std::launch::defered will defer func call till its usage i.e future usage
  // eg
 std::future<int> fu = std::async(std::launch::deferred, fact1,4); // this call will defer func call till its future val is used 
  // which is not creating thread to create thread you need to pass async to launch
  //we can pass val from parent thread to chiold thread i.e in future we can set val
  // eg/
  std::promise<int> p;
  std::future<int> f = p.get_future();
  std::future<int> fu = std::async(std::launch::async, fact2, std::ref(f));
  // In short future and promise is way of communicating bet producer and consumer
  std::this_thread::sleep_for(std::chrono::microseconds(10));
  p.set_value(10);
// if we forget to set / promise val in that case exception well be std::future+errc::broken_promise
// we can set exception as well
p.set_exception(std::make_exception_ptr(std::runtime_error("human error")));

// what if we want to launch many threads for each call func
// we cant pass same future to different threads ..i.e each future can call only one get call
// one idea is to create 10 future and promise ...which is messy
// std::lib provides way to do this by std::shared_future
// it can be copied
// so shared future is kind of broadcast to other threads



  t1.join();

  return 0;

}