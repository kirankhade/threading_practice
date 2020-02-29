#include <iostream>    
#include <algorithm>   
#include <vector>   
#include <thread>
#include <string>
#include <mutex>


using namespace std;
//Deadlock
// HOw introduce and to avoid ??
// Avoiding deadlock
// 1. Prefer locking single mutex
// 2. Avoid locking mutex and then calling user provided function
// 3. Use std::lock() to lock more than one mutex
// 4. Lock the mutex in same order
// 

// Locking Granualarity:
// -Fine-grained lock : protects small amount of data
// - Corse-gained lock : protects big amout of data

class Logfile {
mutex _m1;
mutex _m2;
public:
void shared_print1(string msg, int id)
{
  lock_guard<mutex> locker1(_m1);
  lock_guard<mutex> locker2(_m2);
  ////--------something here 
}
void shared_print2(string msg, int id)
{
  lock_guard<mutex> locker2(_m2);
  lock_guard<mutex> locker1(_m1);
  ////--------something here 
}
// If shared 1 and shared 2 called by main and child threads it will result in deadlock as both will be waiting for other lock 
// To avoid such either awuire lock in same order in each funct
// Use std::lock function which uses deadlock avoidance algo to lock mutex in order 
// to use lock aquired by std::lock use function adopt_lock inside your lock gurad so locks will get freed


};