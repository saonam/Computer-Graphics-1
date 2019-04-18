#ifndef GET_SECONDS_H
#define GET_SECONDS_H
// Return current epoch time in seconds
double get_seconds();

// Implementation
#include <chrono>
double get_seconds()
{
  return 
    std::chrono::duration<double>(
      std::chrono::system_clock::now().time_since_epoch()).count();
}
#endif
