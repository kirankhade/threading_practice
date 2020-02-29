#include <iostream>    
#include <algorithm>   
#include <vector>   
#include <thread>
#include <string>
#include <mutex>
#include <queue>
#include <future>


using namespace std;
// Time constraints 
// 

int fact(int n) 
{
   return n;
}

int main()
{
  // thread
  std::thread t1(fact,6);

  //mutex
  mutex mu;
  lock_guard<mutex> locker(mu);
  unique_lock<mutex> ulocker(mu);


  // Cond var
  std::condition_variable cond;

  // future and promise
  promise<int> p;
  future<int> f = p.get_future();

  // async
  future<int> fu = async(fact,6);


  // packaged task
  // class template can use to parameterise to funct sign on task we want to create later on
  packaged_task<int(int)> t(fact);
  future<int> fu2 = t.get_future();
  t(6);

  // timing
  chrono::steady_clock ::time_point = chrono::steady_clock::now()+ chrono::microseconds(4);
  std::this_thread::sleep_until(tp);
  ulocker.try_lock_until(tp);
  //cond.wait_for
  //cond.wait_unitl
}