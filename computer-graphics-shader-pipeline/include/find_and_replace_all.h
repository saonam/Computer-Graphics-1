#ifndef FIND_AND_REPLACE_ALL_H
#define FIND_AND_REPLACE_ALL_H
#include <string>

// Find and replace all (exact) occurances of a string with something else.
//
// Inputs:
//   toSearch  string to find
//   replaceStr  string to replace
//   data   string to look in and change in place
// Outputs:
//   data   (see input)
// Returns number of replacements made
inline int find_and_replace_all(
  const std::string & toSearch,
  const std::string & replaceStr, 
  std::string & data);

// Implementation

inline int find_and_replace_all(
  const std::string & toSearch,
  const std::string & replaceStr, 
  std::string & data)
{
  // https://thispointer.com/find-and-replace-all-occurrences-of-a-sub-string-in-c/
  int count = 0;
  // Get the first occurrence
  size_t pos = data.find(toSearch);
  // Repeat till end is reached
  while( pos != std::string::npos)
  {
    count++;
    // Replace this occurrence of Sub String
    data.replace(pos, toSearch.size(), replaceStr);
    // Get the next occurrence from the current position
    pos =data.find(toSearch, pos + replaceStr.size());
  }
  return count;
}

#endif
