#include <iostream>    
#include <algorithm>   
#include <vector>   
#include <thread>
#include <string>
#include <mutex>


using namespace std;
//As both main threads are racing for cout 
// will result in messy output
// to avoid we need to sync those
// ways to sync
// Create mutex
// IN shared print we created mutext which whill sync cout 
// there will be pb if cout inside shred_print throws exception mutex will be remain locked
// to avoid that use lock_guard which is wrapper with raii
// Its not recommended to use lock and unlock this way insted use lockgurad
// Still there is pb as cout is gobal any code acess it without going through lock to avoid that
// muxtex must be binded with resource which is protected
// to achive same we have written log file class 


mutex mu;
void shared_print(string msg, int id)
{
  lock_guard<mutex> guard(mu);
  //mu.lock();
  cout << msg << id << endl;
  //mu.unlock();

}

class LogFile {
  mutex _mutex;
  ofstream _f;

  public:
  LogFile(){
    _f.open("log.txt");
  } // close in destructor

  void shared_print(string msg, int id)
  {
    lock_guard<mutex> locker(_mutex);
    _f << msg << id <<endl;
  }
  //Never written f to outside world
  // As it will expose f without mutex
  // never pass f as argument to user provided function

};

void function_1(LogFile& log)
{
  
  for(int i=0;i>-100;i--)
  {
    //cout<<"From t1:"<<i<<endl;
    // shared_print("From t1:", i);
    log.shared_print("From t1:", i);
  }

}


int main()
{

  LogFile log;
  // std::thread t1(function_1);
  thread t1(function_1, std::ref(log));
  for(int i =0 ; i<100;i++)
  {
    // cout << "From main:"<<i<<endl;
    // shared_print("From main:", i);
    log.shared_print("From main:", i);
  }

  t1.join();
  return 0;
}


class stack {
int * _data;
mutex _mu;
public : 
  int & pop();// pops off the item on top of stack
  int & top(); // returns the top item of stack
};

// In above class both fuctions are accesing the data through mutex only 
// So is it thread safe?
// No 
// As lets say we pass stack object to differnt thereads they do pop and top operations in order
// Based on their scheduling two threads might get difernt result ... that is undefined behaviour
// To avoid whats wrong with class
// There is pb with interface itself top and pop operations need to be synced 
// one sol would be pop itself return the top element and pops it so insted use pop in your code
// but pop is not exception safe 
// thats the reason stl stack doesnt return data on pop 

// To avoid data race 
// 1. Use mutex to sync data access.
// 2. Never leak a handle of data to outside
// 3. Design interface approriately

