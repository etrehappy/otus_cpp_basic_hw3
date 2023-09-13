#include <iostream>
#include <ctime>
#include <string>
#include <limits>
#include <fstream>
#include "main.h"

const int max_number = 100;
const int min_number = 0;
constexpr int max_int_size = std::numeric_limits<int>::max();
constexpr char max_char_size = std::numeric_limits<char>::max();

const std::string file_path("file_result.txt");


bool Play_Again()
{
    char user_chois;

    std::cout << "Do you want to play again? (y/n):  ";
    std::cin >> user_chois;

    while (std::cin.fail() || ( (int)user_chois != 121 && (int)user_chois != 89 && (int)user_chois != 110 && (int)user_chois != 78) )
    {
        std::cin.clear();
        std::cin.ignore(max_char_size, '\n');
        std::cout << "Error. Please, enter \"y\" or \"n\": ";
        std::cin >> user_chois;
    }

    if ((int)user_chois == 121 || (int)user_chois == 89) // 121 = y, 89 = Y
        return true;
    if ((int)user_chois == 110 || (int)user_chois == 78) // 110 = n, 78 = N
        return false;
}

void Get_User_Name(std::string &user_name)
{
    std::cout << "Please, enter your name and press Enter: ";
    std::cin >> user_name;
}

int Get_Some_Number()
{
    int some_number = std::rand() % 100;
    
    std::cout << some_number << std::endl; //!!!

    return some_number;
}

void Get_User_Value(int &user_value) 
{
    std::cin >> user_value;

    while (std::cin.fail() || (user_value > max_number) || (user_value < min_number) )
    {
        std::cin.clear();
        std::cin.ignore(max_int_size, '\n');
        std::cout << "Error. Enter integer from 0 untill " << max_number << ": ";
        std::cin >> user_value;
    }
}

void Compare(int &counter_user_attempt)
{
    int random_number = Get_Some_Number();
    int user_value = -1;
  
    for (counter_user_attempt = 0; user_value != random_number; counter_user_attempt++)
    {
        if (counter_user_attempt > 0)
        {
            if (user_value > random_number)           
                std::cout << user_value  << " is greater. Try to guess again: ";

            if (user_value < random_number)
                std::cout << user_value << " is less. Try to guess again: ";
        }

        Get_User_Value(user_value);        
    }
}

void Save(std::string &output, int &counter_user_attempt)
{
    std::fstream file;

    file.open(file_path, std::ios::out | std::ios::app);
    if (file.is_open() == false)
    {
        std::cout << "Error. The file is not open. Your result not saved.";
        return;
    }

    file << /*"\v" <<*/ output << "\t" << counter_user_attempt << std::endl;
    file.close();
}


int main() 
{   
    int counter_user_attempt = 0;
    std::string user_name;

    std::srand((unsigned int)std::time(nullptr));

    Get_User_Name(user_name);

    std::cout << std::endl;
    std::cout << "***** START GAME *****" << std::endl;

    do
    {
        std::cout << std::endl;
        std::cout << "The computer thinking of a number from 0 to " << max_number << ". Guess and enter this number: ";

        Compare(counter_user_attempt);
        Save(user_name, counter_user_attempt);
        std::cout << "You Win! Your attempt = " << counter_user_attempt << std::endl;

    } while (Play_Again() );

    std::cout << std::endl;
    std::cout << "***** END GAME *****" << std::endl;
    std::cout << std::endl;

    return 0;
}