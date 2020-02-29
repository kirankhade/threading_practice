#include <iostream>    
#include <algorithm>   
#include <vector>   
#include <thread>
#include <string>
#include <mutex>


using namespace std;

// Unique lock and lazy initialization
// Uniq lock provide more fine grained lock
// Actually lock gurad scope till end of block 
// with uniq lock you can lock and unlock arbitary no of times 
// Uniq lock can be moved
// That is transfer of ownership from one to other

// Depend on use case you can use lock_guard or unique_lock



class LogFile {
mutex _mu;
mutex _mu_open;
ofstream _f;
std::once_flag _flag;
public:
LogFile()
{
  _f.open("log.txt"); //Irrespective of share_pruinut call file always opoen
}

void shared_print(string msg, int id)
{
  std::unique_lock<mutex> locker2(_mu_open); // this solves pb to enter into critical section simml but
  // it introduces another pb unnecessarily we are lock and unlock mu_open lock i,e in case of files is already open 
  // we are wasting cycles here 
  // to avoid that std::once_flag can be used 
  //eg.
std::call_once(_flag, [&]() {_f.open("log.txt");}); //file will be opend only once by one thread only

  if(!_f.is_open())
  {
    //std::unique_lock<mutex> locker2(_mu_open); // still not thread safe as both thrread can enter into critcal section simmult.
    // to make it thread safe is_open call alson need to sync 
    _f.open("log.txt"); // Lazy initialization
  }
  std::unique_lock<mutex> locker(_mu,std::defer_lock);
  // Some code here
  locker.lock();
  // Do work under lock
  locker.unlock();
  //....

  locker.lock();

  std::unique_lock<mutex> locker2(std::move(locker)); // uniq lock can be moved
}


};

