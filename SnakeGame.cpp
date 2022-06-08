/////////////////////////
///// SnakeGame.cpp /////
/////////////////////////

#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "SnakeGame.hpp"
#include "Snake.cpp"
#include "Item.cpp"


#define DEBUG_CHECK(__CONDITION__, __MESSAGE__)\
{\
    if (__CONDITION__ == ERR)\
    {\
        mvwprintw(this->debugWindow, 2, 0, "\"%s:%d\"\n\n%s", __FILE__, __LINE__, __MESSAGE__);\
        wrefresh(this->debugWindow);\
        this->~SnakeGame();\
        exit(EXIT_FAILURE);\
    }\
}

SnakeGame::SnakeGame()
{
    this->InitMainScreen();
    this->MainOperation();
}

static inline bool
kbhit(void){
    int ch;
    bool ret;

    nodelay(stdscr, TRUE);

    ch = getch();
    if ( ch == ERR ) {
        ret = false;
    } else {
        ret = true;
        ungetch(ch); // 마지막에 받은 문자를 버퍼에 다시 넣어서 다음 getch()가 받을 수 있도록 합니다.
    }

    nodelay(stdscr, FALSE);
    return ret;
}

void SnakeGame::InitMainScreen()
{
    initscr();
    start_color();
    resize_term(40, 100);
    noecho();

    init_pair(defaultColorPair, COLOR_WHITE, COLOR_BLACK);
    init_pair(defaultWindowColorPair, COLOR_RED, COLOR_BLACK);
    init_pair(gameWindowColorPair, COLOR_GREEN, COLOR_BLACK);
    init_pair(statusWindowColorPair, COLOR_YELLOW, COLOR_BLACK);
    init_pair(debugWindowColorPair, COLOR_BLACK, COLOR_WHITE);

    border('|', '|', '-', '-', '+', '+', '+', '+');

    wattron(stdscr, COLOR_PAIR(defaultWindowColorPair));
    mvwprintw(stdscr, 1, 1, "Welcome to the Snake Game");
    wattron(stdscr, COLOR_PAIR(defaultWindowColorPair));
    wrefresh(stdscr);

    gameWindow = newwin(30, 65, 3, 3);

    wborder(gameWindow, '|', '|', '-', '-', '+', '+', '+', '+');
    wattron(gameWindow, COLOR_PAIR(gameWindowColorPair));
    mvwprintw(gameWindow, 1, 1, "This is Game Window");
    wattroff(gameWindow, COLOR_PAIR(gameWindowColorPair));
    wrefresh(gameWindow);


    scoreWindow = newwin(4, 15, 3, 75);

    wborder(scoreWindow, '|', '|', '-', '-', '+', '+', '+', '+');
    wattron(scoreWindow, COLOR_PAIR(statusWindowColorPair));
    mvwprintw(scoreWindow, 1, 1, "Score:");
    mvwprintw(scoreWindow, 2, 1, "%d", this->score);
    wattroff(scoreWindow, COLOR_PAIR(statusWindowColorPair));
    wrefresh(scoreWindow);

    nameWindow = newwin(4, 15, 8, 75);

    wborder(nameWindow, '|', '|', '-', '-', '+', '+', '+', '+');
    wattron(nameWindow, COLOR_PAIR(statusWindowColorPair));
    mvwprintw(nameWindow, 1, 1, "Name:");
    mvwprintw(nameWindow, 2, 1, "Player");
    wattroff(nameWindow, COLOR_PAIR(statusWindowColorPair));
    wrefresh(nameWindow);

    debugBorder = newwin(20, 27, 13, 70);

    wborder(debugBorder, '|', '|', '-', '-', '+', '+', '+', '+');
    wbkgd(debugBorder, COLOR_PAIR(debugWindowColorPair));
    wrefresh(debugBorder);

    debugWindow = newwin(9, 25, 17, 71);

    wbkgd(debugWindow, COLOR_PAIR(debugWindowColorPair));
    wattron(debugWindow, COLOR_PAIR(debugWindowColorPair));
    mvwprintw(debugWindow, 0, 0, "Debug Console:");
    wattroff(debugWindow, COLOR_PAIR(debugWindowColorPair));
    wrefresh(debugWindow);

    mvaddch(3,3,'a');
    mvaddch(3,67,'b');
    mvaddch(32,3,'c');
    mvaddch(32,67,'d');

    Snake snake = Snake();
    keypad((stdscr), TRUE);
    int ch;
    int dx = 0;
    int dy = 1;

    vector<Item> Items;
    pair<int, int> temp;
    srand(time(NULL));
    do{
      temp = {rand() % 29 + 4, rand() % 63 + 4};
    }while(FALSE); // 스네이크랑 겹치지 않는지 확인
    Item item1 = Item('G', temp);

    do{
      temp = {rand() % 29 + 4, rand() % 63 + 4};
    }while(FALSE); // 스네이크랑 겹치지 않는지 확인
    Item item2 = Item('G', temp);

    do{
      temp = {rand() % 29 + 4, rand() % 63 + 4};
    }while(FALSE); // 스네이크랑 겹치지 않는지 확인
    Item item3 = Item('P', temp);

    Items.push_back(item1);
    Items.push_back(item2);
    Items.push_back(item3);

    for (int i = 0; i < 3; i++){
      Items[i].print();
    }

    while(TRUE){
      usleep(500000);
      for (int i = 0; i < 3; i++){
        Items[i].time++;
      }


      if (kbhit()){
        ch = getch();
        if (ch == KEY_F(1)) break;

        if (ch == KEY_LEFT){
          if (dx == 0 && dy == -1) break;
          dx = 0;
          dy = -1;
        }
        else if (ch == KEY_RIGHT){
          if (dx == 0 && dy == 1) break;
          dx = 0;
          dy = 1;
        }
        else if (ch == KEY_UP){
          if (dx == -1 && dy == 0) break;
          dx = -1;
          dy = 0;
        }
        else if (ch == KEY_DOWN){
          if (dx == 1 && dy == 0) break;
          dx = 1;
          dy = 0;
        }
      }

      pair<int, int> temp = snake.getHead();
      pair<int, int> nextHead;

      nextHead = {temp.first + dx, temp.second + dy};

      // nextHead가 갈 수 있는 곳인지, 아이템 있는지 확인 확인하는 코드 넣을곳
      for (int i = 0; i < 3; i++){
        if (nextHead == Items[i].Point){
            if (Items[i].ItemType == 'P'){
              snake.remove_tale();
            }
            else{
              snake.add_head(nextHead);
            }
            if (kbhit()){
              ch = getch();
              if (ch == KEY_F(1)) break;

              if (ch == KEY_LEFT){
                if (dx == 0 && dy == -1) break;
                dx = 0;
                dy = -1;
              }
              else if (ch == KEY_RIGHT){
                if (dx == 0 && dy == 1) break;
                dx = 0;
                dy = 1;
              }
              else if (ch == KEY_UP){
                if (dx == -1 && dy == 0) break;
                dx = -1;
                dy = 0;
              }
              else if (ch == KEY_DOWN){
                if (dx == 1 && dy == 0) break;
                dx = 1;
                dy = 0;
              }
            }

            pair<int, int> temp = snake.getHead();
            pair<int, int> nextHead;
        }
      }

      snake.move(nextHead);
    }
}

void SnakeGame::MainOperation()
{
    DEBUG_CHECK(ERR, "Testing...");
}

SnakeGame::~SnakeGame()
{
    getch();
    delwin(gameWindow);
    delwin(scoreWindow);
    delwin(nameWindow);
    delwin(debugBorder);
    delwin(debugWindow);
    endwin();
}
