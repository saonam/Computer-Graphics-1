// g++ -o file_watcher file_watcher.cpp -I include -std=c++11
//
// Appears to work correctly on mac and linux. Haven't tested on windows.

#include "last_modification_time.h"
#include "get_seconds.h"
#include <iostream>
#include <thread>
 
int main(int argc, char * argv []) 
{
  double time_since_last_load = 0;
  while(true)
  {
    if(last_modification_time(argv[1]) > time_since_last_load)
    {
      std::cout<<argv[1]<<" changed. Reloading..."<<std::endl;
      time_since_last_load = get_seconds();
    }
    std::this_thread::sleep_for(std::chrono::microseconds((int)(10000.0)));
  }
  return 0;
}
