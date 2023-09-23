#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
#include <stdlib.h>

//base task
void Get_User_Name(std::string &user_name);
int Get_Some_Number(const int &max_number);
void Get_User_Value(int &user_value, const int& max_number);
void Compare(int &counter_user_attempt, const int& max_number);
void Save(std::string &user_name, int &counter_user_attempt);
void View_List_Results();


//extra tasks
void Treat_Arguments(int& argc, char** argv);
void Treat_Arguments(int i, std::string parametr, char** argv);
void View_and_Save_Min_Result();
bool Play_Again();

