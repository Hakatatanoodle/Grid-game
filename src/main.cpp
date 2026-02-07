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
  int playerX,playerY;
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
  
  for(int i = 0; i < grid.size();i++)
  {
    for(int j = 0; j < grid[i].size(); j++)//here i is the row  and i am trying to stop at the end of the string which is controlled by i 
    {
      if(grid[i][j] == 'P')
      {
        playerX  = j;
        playerY = i;
      }
    }
  }
  grid[playerX][playerY]='.';
  std::cout << "Player Position: " << playerX << "," << playerY << std::endl;
  return 0;
}


void drawGrid(const std::vector<std::string>& grid)
{
  for (const std::string& row : grid)
  {
    std::cout << row<< std::endl;  
  }
}