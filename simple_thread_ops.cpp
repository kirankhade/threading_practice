#include <iostream>    
#include <algorithm>   
#include <vector>   
#include <thread>


using namespace std;

void func1()
{
  cout<<"Some code goes here"<<endl;
}

int main()
{
  thread t1(func1); //t1 starts runnig
  // t1.join(); //main thread waits for t1 to finish
  //t1.detach(); // t1 will freely on its own -- daemon process 

  if(t1.joinable())
  {
    t1.join(); // will crash without checking joinable if thread is already detached 
  }
  return 0;
}

/*
Summary :- thread -crates a thread with param to execute
thread.detach : - detach thread from main thread like daemon  cant rejoin it
thread.join :_ main thread wait till end of created thread
thread.joinable :- to check we can join on thread 
