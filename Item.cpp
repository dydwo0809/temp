#include "Stable.hpp"
#include "Unstable.hpp"
#include<deque>

using namespace std;

class Item{
private:
public:
  char ItemType;
  pair<int, int> Point;
  int time;

  Item(char type, pair<int, int> point){
    this->ItemType = type;
    this->Point = point;
    this->time = 0;
  }
  Item(){
    this->ItemType = 'G';
    this->Point = {1, 1};
    this->time = 0;
  }
  void print(){
    mvaddch(Point.first, Point.second, ItemType);
  }
};
