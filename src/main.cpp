/*
Turn based Grid game
*/ 
#include<iostream>
#include<vector>
#include<string>
#include<limits>

//enum to define the result of movement 
enum MovementResult
{
  MOVED,
  BLOCKEDBYWALL,
  BLOCKEDBYBOUNDS
};
//constants

//function prototypes
void drawGrid(const std::vector<std::string>& grid);

enum MovementResult movementResolver(const std::vector<std::string>&,const std::string&,int& playerX,int& playerY);

int main()
{ 
  MovementResult mvr ;
  int playerX=-1,playerY=-1;
  bool found=false;//flag to check if player is found or not
  bool gameEnd = false;
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

  std::string input;
  std::cout << "W A S D " ;
  std::cin >> input;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  //GAME LOOP 
    while(input!= "exit" && !gameEnd)
    {
      mvr = movementResolver(grid,input,playerX,playerY);
      if(mvr == MOVED)
      {
        continue;
      }
      else if(mvr==BLOCKEDBYWALL)
      {
        printf("Blocked By wall!");
      }
      else if(mvr==BLOCKEDBYBOUNDS)
      {
        printf("Bloced by bounds");
      }

    }
  return 0;
}


void drawGrid(const std::vector<std::string>& grid)
{
  for (const std::string& row : grid)
  {
    std::cout << row<< std::endl;  
  }
}

//function to resolve movement
enum MovementResult movementResolver(const std::vector<std::string>& grid,const std::string& input,int& playerX,int& playerY)
{
  int targetX=playerX,targetY=playerY;

  if(input == "w")
  {
    targetY-=1;
  }
  if(input =="s")
  {
    targetY+=1;
  }
  if(input == "a")
  {
    targetX-=1;
  }
  if( input =="d")
  {
    targetX+=1;
  }

  if(targetY <0 ||  targetY >=grid.size())
  {
    return BLOCKEDBYBOUNDS;
  }
  else if( targetX<0 || targetX >=grid[targetY].size()  )
  {
    return BLOCKEDBYBOUNDS;
  }
  else if(grid[targetY][targetX]=='#')
  {
    return BLOCKEDBYWALL;
  }
  else
  {
    //commit move
    playerX = targetX;
    playerY = targetY;
    return MOVED;
  }

}