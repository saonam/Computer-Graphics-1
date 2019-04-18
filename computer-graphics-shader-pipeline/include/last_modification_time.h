#ifndef LAST_MODIFICATION_TIME_H
#define LAST_MODIFICATION_TIME_H
#include <string>
// Inputs:
//   path  path to file in question
// Returns the last time this file has been modified in seconds.
double last_modification_time(const std::string & path);

// Implementation

#if WIN32

// Shot in the dark... I don't even know if this compiles
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <cassert>

double last_modification_time(const std::string & path)
{
  // https://www.rosettacode.org/wiki/File_modification_time#Windows
  FILETIME modtime;
  //SYSTEMTIME st;
  HANDLE fh;
  std::wstring w_path = std::wstring(path.begin(), path.end());
  fh = CreateFileW(w_path.c_str(), GENERIC_READ | FILE_WRITE_ATTRIBUTES,
      0, NULL, OPEN_EXISTING, 0, NULL);
  if(fh == INVALID_HANDLE_VALUE)
  {
    return -1;
  }
  if(GetFileTime(fh, NULL, NULL, &modtime) == 0)
  {
    return -1;
  }
  CloseHandle(fh);
  // https://stackoverflow.com/a/19709740/148668
  __int64* val = (__int64*) &modtime;
  return static_cast<double>(*val) / 10000000.0 - 11644473600.0;
}
#else

#include <sys/stat.h>
#include <sys/time.h>
#include <ctime>
#include <fcntl.h>

double last_modification_time(const std::string & path)
{
  struct stat s;
  struct timespec t = {0,0};
  if (stat(path.c_str(), &s) < 0) { return -1; }
#ifdef __APPLE__
  t = s.st_mtimespec;
#else // Linux?
  t = s.st_mtim;
#endif
  return double(t.tv_sec) + double(t.tv_nsec)*1e-9;
}

#endif

#endif
