using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void tokenize(std::string const &str, char delim, std::vector<std::string> &out);
void tokenize(std::string const &str, const string& delim, std::vector<std::string> &out);

// Taken from https://cplusplus.com/forum/beginner/282741/
template<typename C> C get_intersection( C &a, C &b ) {
  sort( a.begin(), a.end() );
  sort( b.begin(), b.end() );
  C result;
  set_intersection( a.begin(), a.end(), b.begin(), b.end(), back_inserter( result ) );
  return result;
}

bool uniqueCharacters(string str);

template <typename T>
const bool contains( std::vector<T>& Vec, const T& Element )
{
  if (std::find(Vec.begin(), Vec.end(), Element) != Vec.end())
    return true;

  return false;
}