/*
Turn based Grid game
*/ 
#include<iostream>
#include<vector>
#include<string>
#include<limits>
#include<cmath>
enum MovementResult
{
  MOVED,
  BLOCKEDBYWALL,
  BLOCKEDBYBOUNDS,
  HITENEMY
};

enum ActionType
{
  ATTACK,
  MOVE
};
//structs
struct Entity
{
  int x,y;
  int health;
};

//function prototypes
void drawGrid(const std::vector<std::string>& grid,const Entity&,const Entity&);
void moveEnemy(const std::vector<std::string>&,Entity&,const Entity&);
bool canAttack(const Entity& attacker, const Entity& target);//function to check if the target can be attacked or not

enum MovementResult movementResolver(const std::vector<std::string>&,const std::string&,Entity&);

int main()
{ 
  MovementResult mvr ;
  Entity player, enemy;
  player.x = -1 , player.y=-1, enemy.x=-1,enemy.y=-1;
  player.health = 3,enemy.health = 3;//setting initial health of player and enemy
  bool playerFound=false,enemyFound = false;//flag to check if player is found or not
  bool gameEnd = false;
  std::string action;//player input
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
  if(enemy.x ==-1 || enemy.y == -1)
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
      drawGrid(grid,player,enemy);

      //player turn 
      std::cout << "Do you want to attack or move?"<<std::endl;
      std::cout << "Move : m: "<< std::endl << "Attack: a: ";
      std::cin >> action;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if(action =="m")
      {
        std::string direction;
        std::cout << "Choose direction to move: (w a s d ):" ;
        std::cin >> direction;

        mvr = movementResolver(grid,direction,player);
        if(mvr==BLOCKEDBYWALL)
        {
          std::cout << "Blocked By wall!"<<std::endl;
        }
        else if(mvr==BLOCKEDBYBOUNDS)
        {
          std::cout << "Bloced by bounds"<<std::endl;
        }
      }
      else if(action == "a")
      {
        if(canAttack(player,enemy))
        {
          std::cout << "Hit enemy!"<<std::endl;
          enemy.health--;
          if(enemy.health<=0)
          {
            std::cout << "Enemy is cooked ! You won !"<<std::endl;
            gameEnd = true;
          }
          
        }
        else
        {
          std::cout << "Enemy not in range!"<<std::endl;
        }
      }

      //enemyturn 
      if(!gameEnd)
      {
        if(canAttack(enemy,player))
        {
          std::cout << "Player got hit!"<<std::endl;
          player.health--;
          if(player.health<=0)
          {
            std::cout << "Bruh you got cooked by an stupid AI !"<<std::endl;
            gameEnd = true;
          }
        }
        else
        {
          moveEnemy(grid,enemy,player);
        }
      }

    }while(action != "exit" && !gameEnd);
  return 0;
}


void drawGrid(const std::vector<std::string>& grid,const Entity& player, const Entity& enemy)
{
  for(int i =0 ; i < grid.size();i++)
  {
    for(int j = 0; j < grid[i].size();j++)
    {
      if(j == player.x && i ==player.y )
      {
        std::cout << "P" ;
      }
      else if (j==enemy.x && i == enemy.y )
      {
        std::cout << "E";
      }
      else std::cout<< grid[i][j];
    }
    std::cout << std::endl;
  }
}

//function to resolve movement
enum MovementResult movementResolver(const std::vector<std::string>& grid,const std::string& input,Entity& player)
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
  else
  {
    //commit move
    player.x = targetX;
    player.y = targetY;
    return MOVED;
  }
}

void moveEnemy(const std::vector<std::string>& grid,Entity& enemy,const Entity& player)
{
  //use mahattan distance to calculate ai movement
  //first set initial position of the enemy  
  int targetX = enemy.x;
  int targetY = enemy.y;

  int dx = player.x - enemy.x;
  int dy = player.y - enemy.y;

  if(abs(dx)>abs(dy))
  {
    targetX+= (dx>0)? 1:-1;
  }
  else if(dy!=0)
  {
    targetY+= (dy>0)? 1:-1;
  }

  if (targetY < 0 || targetY >= grid.size())
    return;

  if (targetX < 0 || targetX >= grid[targetY].size())
    return;

  //check if grid is walkable
  if(grid[targetY][targetX] == '#') return ;
  enemy.x = targetX;
  enemy.y = targetY;
}
//check if the target can be attacked or not
bool canAttack(const Entity& attacker, const Entity& target)
{

  int dx=std::abs(attacker.x - target.x);
  int dy = std::abs(attacker.y-target.y);
  //same column 
  if(attacker.x==target.x && dy<=3)
  {
      return true;
  }
  //same row 
  else if(attacker.y==target.y && dx<=3)
  {
    return true;
  }
  return false;
}