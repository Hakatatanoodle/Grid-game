#include<iostream>

int main()
{
    srand(time(NULL));
    int num = rand()%10;
    std::cout << num<<std::endl;
    return 0;

}