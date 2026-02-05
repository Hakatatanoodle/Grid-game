/*
Turn based Grid game
*/ 
#include<iostream>
#include<vector>
#include<string>

//constants

constexpr int gridWidth = 10;
constexpr int gridHeight = 10;


//function prototypes
void drawGrid(const std::vector<std::string>& grid);
int main()
{
  std::vector<std::string> grid = 
  {
    "############",
    "#....P.....#",
    "#..........#",
    "#..........#",
    "#..........#",
    "#..........#",
    "#..........#",
    "#..........#",
    "#....E.....#",
    "############"
  };
  drawGrid(grid);
  return 0;
}

void drawGrid(const std::vector<std::string>& grid)
{
  for (const std::string& row : grid)
  {
    std::cout << row<< std::endl;  
  }
}