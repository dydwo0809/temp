#include "Stable.hpp"
#include "Unstable.hpp"
#include<deque>

using namespace std;

class Snake{
private:
public:
  deque<pair<int, int>> locations;

  Snake(){
    pair<int, int> head = {10, 10};
    pair<int, int> tale = {10, 11};
    pair<int, int> tale2 = {10, 12};
    locations.push_back(head);
    locations.push_back(tale);
    locations.push_back(tale2);
    for (const auto& location : locations)
      mvaddch(location.first, location.second, '#');
  }
  void move(pair<int, int> nextHead){
    //방향 입력받음
    //pair<int, int> nextHead = {a, b}; // 입력받은 방향으로 가야함
    locations.push_front(nextHead); //새로운 머리 추가
    mvaddch(nextHead.first, nextHead.second, '#');
    pair<int, int> remove_tale = locations.back(); // 맨 끝 꼬리 제거
    locations.pop_back();
    mvaddch(remove_tale.first, remove_tale.second, ' ');
  }
  pair<int, int> getHead(){
    return locations.front();
  }

};
