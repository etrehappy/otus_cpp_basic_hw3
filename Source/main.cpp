#include "main.h"

//Base tasks
int max_number = 100;
const int min_number = 0;
constexpr int max_int_size = std::numeric_limits<int>::max();
constexpr char max_char_size = std::numeric_limits<char>::max();

const std::string file_path("file_result.txt");


void Get_User_Name(std::string &user_name)
{
    std::cout << "Please, enter your name: ";
    std::cin >> user_name;
}

int Get_Some_Number(const int &max_number)
{
    int some_number = std::rand() % max_number;
    
    return some_number;
}

void Get_User_Value(int &user_value, const int &max_number)
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

void Compare(int &counter_user_attempt, const int &max_number)
{
    int random_number = Get_Some_Number(max_number);
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

        Get_User_Value(user_value, max_number);
    }
}

void Save(std::string &user_name, int &counter_user_attempt)
{
    std::ofstream file(file_path, std::ios::app);

    if (file.is_open() == false)
    {
        std::cout << "Error. The file is not open. Your result not saved.";
        return;
    }

    file << user_name << "\t" << counter_user_attempt << std::endl;
    file.close();
}
 
void View_List_Results() // This function uses only with argument "-table" beacause there is a extra-task function "View_and_Save_Min_Result()"
{
    std::string input;

    std::ifstream file(file_path);
    file.seekg(0);

    std::cout << "\nHigh scores table\n" << "\nName\t" << "Scores" << std::endl;  
    std::getline(file, input, '$');
    std::cout << input;

    file.close();
}
//-----------------------------------------------------------------------------------------------------


//Extra tasks: 
// 1, 2, 5
void Treat_Arguments(int i, std::string parametr, char** argv)
{
    if (parametr == "-max")
    {
        try
        {
            if (argv[i + 1] == NULL)
                throw std::exception("The argument '-max' requires some integer > 0. Example: -max 50");

            max_number = std::stoi(argv[i + 1]); //convertation from char to integer
        }
        catch (const std::exception& ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
            return;
        }

        return;
    }

    if (parametr == "-level")
    {
        int level = 0;

        try
        {
            if (argv[i + 1] == NULL)
                throw std::exception("The argument '-level' requires 1, 2 or 3. Example: -level 2");

            level = std::stoi(argv[i + 1]); //convertation from char to integer
        }
        catch (const std::exception& ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
            return;
        }

        switch (level)
        {

        case 1:
            max_number = 9;
            break;
        case 2:
            max_number = 49;
            break;
        case 3:
            max_number = 99;
            break;
        default:
            break;
        }

        return;
    }

    if (parametr == "-table")
    {
        View_List_Results();
        std::cout << std::endl;
        exit(0);
    }
}

void Treat_Arguments(int& argc, char** argv)
{
    //task 5 !!!
    for (int i = 1; i < argc; i++)
    {
        std::string parametr = argv[i];

        if (parametr == "-max" || parametr == "-level")
        {
            for (int j = 2; j < argc; j++)
            {
                std::string double_parametr = argv[j];

                if (double_parametr == "-max" || double_parametr == "-level")
                {
                    std::cout << "Error. Set only one parametr: '-max' OR '-level' " << std::endl;
                    exit(0);
                }
            }
        }

        Treat_Arguments(i, parametr, argv);
    }
}

// 3, 4
void View_and_Save_Min_Result()
{
    // GET vector of name  and vector of results from file

    std::vector<std::string> user_names;
    std::vector<int> user_results;

    std::fstream file;

    file.open(file_path, std::ios::in);

    if (!file.is_open())
    {
        std::cout << "Error. The save-file is not open. You can't view result table.";
        return;
    }

    file.seekg(0);

    int i = 0;
    int max_count_name = 0;
    bool is_first_iteration = true;
    std::string i_string_name, i_string_result;
    int i_result;

    while (!file.eof())
    {
        std::getline(file, i_string_name, '\t');

        std::getline(file, i_string_result, '\n');
        i_result = std::stoi(i_string_result);

        if (is_first_iteration)
        {
            user_names.push_back(i_string_name);
            user_results.push_back(i_result);
            is_first_iteration = false;
            ++i;
            continue;
        }

        max_count_name = (int)user_names.size() - 1;
        for (int j = 0; j <= max_count_name; j++)
        {
            if (i_string_name == user_names[j])
            {
                if (i_result < user_results[j])
                    user_results[j] = i_result;

                break;
            }

            if (j == max_count_name)
            {
                user_names.push_back(i_string_name);
                user_results.push_back(i_result);
                ++i;
                break;
            }
        }
    }

    //clear last excess string (this string contains '\n' because of the use of Save() )
    user_names.pop_back();
    user_results.pop_back();

    file.close();



    // VIEW table and SAVE result

    file.open(file_path, std::ios::out | std::ios::trunc);

    std::cout << "----\t" << "------"
        << "\nName\t" << "Scores\n"
        << "----\t" << "------" << std::endl;

    for (int l = 0; l < user_names.size(); l++)
    {
        std::cout << user_names[l] << '\t' << user_results[l] << std::endl;
        file << user_names[l] << '\t' << user_results[l] << std::endl;
    }

    file.flush();
    file.close();
}

//My
bool Play_Again()
{
    char user_chois;

    std::cout << "Do you want to play again? (y/n):  ";
    std::cin >> user_chois;

    while (std::cin.fail() || ((int)user_chois != 121 && (int)user_chois != 89 && (int)user_chois != 110 && (int)user_chois != 78))
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

    return false;
}
//-----------------------------------------------------------------------------------------------------



int main(int argc, char *argv[])
{   
    Treat_Arguments(argc, argv);
   
    std::srand((unsigned int)std::time(nullptr));

    std::string user_name;
    int counter_user_attempt = 0;


    Get_User_Name(user_name);

    std::cout << "\n***** START GAME *****" << std::endl;

    do
    {
        std::cout << "\nThe computer thinking of a number from 0 to " << max_number << ". Guess and enter this number: ";

        Compare(counter_user_attempt, max_number);
        Save(user_name, counter_user_attempt);
        std::cout << "You Win! Your attempt = " << counter_user_attempt << std::endl;

    } while (Play_Again() );

    View_and_Save_Min_Result();
       
    std::cout << "\n***** END GAME *****\n" << std::endl;

    return 0;
}
