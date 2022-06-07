/////////////////////////
///// SnakeGame.cpp /////
/////////////////////////

#include "SnakeGame.hpp"

#include "Snake.cpp"

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

    Snake snake = Snake();
    keypad((stdscr), TRUE);
    int ch;
    while(ch = getch()){
      clear;
      if (ch == KEY_F(1)) break;

      pair<int, int> temp = snake.getHead();
      pair<int, int> nextHead;

      if (ch == KEY_LEFT){
        nextHead = {temp.first, temp.second - 1};
      }
      else if (ch == KEY_RIGHT){
        nextHead = {temp.first, temp.second + 1};
      }
      else if (ch == KEY_UP){
        nextHead = {temp.first - 1, temp.second};
      }
      else if (ch == KEY_DOWN){
        nextHead = {temp.first + 1, temp.second};
      }
      snake.move(nextHead);
    }
    mvaddch(3,3,'%');
    mvaddch(3,67,'%');
    mvaddch(32,3,'%');
    mvaddch(32,67,'%');


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
