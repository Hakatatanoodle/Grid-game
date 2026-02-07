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
  int playerX=-1,playerY=-1;
  bool found=false;//flag to check if player is found or not
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
  
  
  for(int i = 0; i < grid.size() && !found;i++)
  {
    for(int j = 0; j < grid[i].size(); j++)//here i is the row  and i am trying to stop at the end of the string which is controlled by i 
    {
      if(grid[i][j] == 'P')
      {
        playerX  = j;
        playerY = i;
        found = true;
        break;
      }
    }
  }
  if(playerX == -1 || playerY  == -1)
  {
    std::cout << "Player coordinates error!" << std::endl;
    return 0;
  }
  else
  {
    grid[playerY][playerX]='.';//substitute the player with empty space(.)
    std::cout << "Player Position: " << playerX << "," << playerY << std::endl;
  }

  //print the grid after extracting the player
  drawGrid(grid);
  //print a blanck line before reinserting the player
  std::cout << std::endl;
  //reinserting the player (modify the vector and reprint the gird)
  grid[playerY][playerX] = 'P';
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