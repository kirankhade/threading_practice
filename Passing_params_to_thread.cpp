#include <iostream>    
#include <algorithm>   
#include <vector>   
#include <thread>
#include <string>

using namespace std;


class Fctor {
public:
  void operator()(string& msg){
    {
      cout << "t1 says :" << msg <<endl;
      msg = "Look I have modified this";
    }
  }
};

// We have created main and child thread acess the same memory
// We can use move to pass param to thread as well
// Thread cant be copied they can be moved
// Each thread has id with it we can use this_thread::get_id();
// How many threads I should create ??
// Should not do oversuscription which cause too many context switching i.e thrashing
// std::thread ::hardware_concurrency() // can be used to get indication about no of thread can be created
int main()
{
  string msg("hi fisdfsadfkladf ldkfsdfj");
  thread t1((Fctor()), std::ref(msg));
  //std::ref is wrapper for reference 

//Other app to same is use RAII
// Wrapper w(t1) which will join thread in its destructor
// Thread object can be created with any callable obj such as functor or lambda
//Parameters to thread will always will be pass by value


// try {
//   for(int i =0;i<100;i++)
//     cout<<"From main:"<<i<<endl; // if this block throws any excpn then thread will not be joined  to avoid we used try catch

// } catch(...) {
//   t1.join();
//   throw; //rethrow 
// }

t1.join(); 
cout << "from main :"<< msg; //will not get modifed until wrap inside ref as threads take param by val
  return 0;
}
