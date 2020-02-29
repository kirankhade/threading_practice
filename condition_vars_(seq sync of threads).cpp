#include <iostream>    
#include <algorithm>   
#include <vector>   
#include <thread>
#include <string>
#include <mutex>
#include <queue>


using namespace std;

// Condition variable 
// Mutex alone will not solve pb in some cases
// but with only mutex sync consumer will suffer from busy waiting 
// to some improvement we can make consumer sleep if it finds q empty for some time still not efficient
// also what should be duration for sleep of consumer its difficult to find efficient time
// in such scenario cond var come into picture
// 
//cond vars are used to sync execution sequence of threads.

std::deque<int> q; //access to q is sync with mutex mu
mutex mu;
condition_variable cond;

void producer()
 {
       int count = 10;
       while (count > 0)
       {
         unique_lock<mutex> locker(mu);
         q.push_front(count);
         locker.unlock();
         cond.notify_one(); //wake up call to consumer
         //cond.notify_all(); //wake call to all
         this_thread::sleep_for(chrono::seconds(1));
         count --;
       }
       
}

void consumer()
{
  int data =0;
  while (data != 1)
  {
    unique_lock<mutex> locker(mu);
    //cond.wait(locker); //it will wake up on itesef as well which is spurious wake to avoid continueing on spurious wake we can add cond check to wait call
    cond.wait(locker, [&]() {return !q.empty();}); //when q is not empty below code will be executed  // ie predicate need to fullfill
    data = q.back();
    q.pop_back();
    locker.unlock();
    cout << "consumer got val :"<< data <<endl;
    // if(!q.empty())
    // {
    //   data = q.back();
    //   q.pop_back();
    //   locker.unlock();
    //   cout << "consumer got val from producer :" << data <<endl;
    // } else {
    //   locker.unlock();
    // }

  }
  
}

int main()
{
  thread t1(producer);
  thread t2(consumer);
  t1.join();
  t2.join();
}


