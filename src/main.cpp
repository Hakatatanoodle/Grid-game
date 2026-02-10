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
  BLOCKEDBYBOUNDS,
  HITENEMY
};
//structs
struct Entity
{
  int x,y;
};

//function prototypes
void drawGrid(const std::vector<std::string>& grid);

enum MovementResult movementResolver(const std::vector<std::string>&,const std::string&,Entity&,Entity&);

int main()
{ 
  MovementResult mvr ;
  Entity player, enemy;
  player.x = -1 , player.y=-1, enemy.x=-1,enemy.y=-1;
  bool playerFound=false,enemyFound = false;//flag to check if player is found or not
  bool gameEnd = false;
  std::string input;//player input
  //create the grid
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
  
  //find initial player position
  for(int i = 0; i < grid.size() && !playerFound;i++)
  {
    for(int j = 0; j < grid[i].size(); j++)//here i is the row  and i am trying to stop at the end of the string which is controlled by i 
    {
      if(grid[i][j] == 'P')
      {
        player.x  = j;
        player.y = i;
        playerFound = true;
        break;
      }
    }
  }
  if(player.x == -1 || player.y == -1)
  {
    std::cout << "Player coordinates error!" << std::endl;
    return 0; 
  }
  else
  {
    grid[player.y][player.x]='.';//substitute the player with empty space(.)
  }
  //find initial enemy position 
  for(int i=0;i<grid.size() && !enemyFound;i++)
  {
    for(int j=0;j<grid[i].size();j++)
    {
      if(grid[i][j]=='E')
      {
        enemy.x=j;
        enemy.y=i;
        enemyFound=true;
      }
    }
  }
  if(enemy.x==-1 || enemy.y == -1)
  {
    std::cout << "Invalid player coordingates"<<std::endl;
    return 0;
  }
  else
  {
    grid[enemy.y][enemy.x] = '.';//substitute enemy with empty space . 
  }


  //GAME LOOP 
    do
    {
      //print a blanck line before reinserting the player
      std::cout << std::endl;
      //reinserting the player 
      grid[player.y][player.x] = 'P';
      grid[enemy.y][enemy.x] = 'E'; //reinsert enemy
      drawGrid(grid);
      grid[player.y][player.x] = '.';//replacing P with .
      grid[enemy.y][enemy.x] = '.';

      std::cout << "W A S D (or exit): " ;
      std::cin >> input;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


      mvr = movementResolver(grid,input,player,enemy);
      if(mvr==BLOCKEDBYWALL)
      {
        std::cout << "Blocked By wall!"<<std::endl;
      }
      else if(mvr==BLOCKEDBYBOUNDS)
      {
        std::cout << "Bloced by bounds"<<std::endl;
      }
      else if(mvr==HITENEMY)
      {
        std::cout << "Hit enemy!"<<std::endl;
        gameEnd = true;
      }

    }while(input != "exit" && !gameEnd);
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
enum MovementResult movementResolver(const std::vector<std::string>& grid,const std::string& input,Entity& player,const Entity& enemy)
{
  int targetX=player.x,targetY=player.y;

  if (input == "w")
  {
    targetY--;
  }
  else if (input == "s")
  {
    targetY++;
  }
  else if (input == "a")
  {
    targetX--;
  }
  else if (input == "d")
  {
    targetX++;
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
  else if(targetX==enemy.x && targetY==enemy.y)
  {
    return HITENEMY;
  }
  else
  {
    //commit move
    player.x = targetX;
    player.y = targetY;
    return MOVED;
  }

}