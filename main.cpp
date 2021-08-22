
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "output_container1.h"

using namespace std;

struct A
{
  int a;
  int b;
  friend ostream& operator<< (ostream &os,const A &sta)
  {
    os << sta.a << sta.b <<endl;
    return os;
  }
  //how to print point content
  friend ostream& operator<< (ostream &os,const A* sta)
  {
    os << sta->a << sta->b <<endl;
    return os;
  }
};




int main()
{
  A a1{11, 22};
  A a2{33, 44};
  A a3{55, 66};
  map<int, A> map1{{111,a1},{222,a2},{333,a3}};
  cout<<map1<<endl;

  A* pa1 = &a1;
  A* pa2 = &a2;
  A* pa3 = &a3;
  map<int, A*> map2{{111,pa1},{222,pa2},{333,pa3}};
  cout<<map2<<endl;

  map<int, char> mp{
    {1, '1'}, {2, '4'}, {3, '9'}};
  cout << mp << endl;

  vector<vector<int>> vv{
    {1, 1}, {2, 4}, {3, 9}};
  cout << vv << endl;

  std::set<int> set1 = { 3, 1, 4, 1, 5, 9, 2, 6, 5 };
  cout<<set1<<endl;

  const std::multiset<std::string> words = {
        "some", "not", "sorted", "words",
        "will", "come", "out", "sorted",
  };
  cout <<words<<endl;

  std::multimap<std::size_t, std::string> mmap;
  mmap.insert({ sizeof(int), "int" });
  mmap.insert({ sizeof(short), "short" });
  cout << mmap << endl;

  std::unordered_set<int> nums {1, 3, 5, 7};
  cout << nums << endl;

  std::unordered_multimap<int,char> multiNums {{1, 'a'}, {3, 'b'}, {5, 'c'}, {7, 'd'}};
  cout << multiNums << endl;


  return 0;
}
