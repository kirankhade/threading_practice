#include <iostream>    
#include <algorithm>   
#include <vector>   
#include <thread>
#include <string>
#include <mutex>
#include <queue>
#include <future>


using namespace std;
// Packaged task
//  Its pakage of task whic his packaged at one place and used later and executed there 
// Its templated task
// Packaged task returns void 
// to get val use task.get_future.getval
// to bind func with parm and create func object use std::bind


int fact(int n)
{
  //do som
  return n;
}

deque<std::packaged_task<int()>> task_q;

void thread_1()
{
  std::packaged_task<int()> t;
  t = std::move(task_q.front());
  t();
}

int main()
{
  std::packaged_task<int()> t(std::bind(fact,6)); //use t whrewver use val
  t();
  // other way
  auto tt = std::bind(fact,6);
  // do we need packaged task with above syntax?
  // it comes handy in threading env
  // Main advantage of pkged task is it can link callable object to future 

  //
  std::packaged_task<int()> t(std::bind(fact,6)); //use t whrewver use val
  std::thread t1(thread_1);
  task_q.push_back(t);
  // how will get return val
  // by using future
  //eg/
  std::future<int> fu = t.get_future();
  cout << fu.get();

//Summary 
// 3 ways to get a future
// - promise :: get_future
// - packaged_task::get_future()
// - async() returns a future



}
