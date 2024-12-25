#include <iostream>
#include <fstream>
using namespace std;
/// <summary>
/// Function that lexicographically compares 2 char arrays.
/// </summary>
/// <param name="str1">The first char array.</param>
/// <param name="str2">The second char array.</param>
/// <returns>
/// If any of the arrays is a nullpointer, returns -2;
/// If the first array is lexicographically bigger, returns 1.
/// If the first array is lexicographically bigger, returns -1.
/// If the arrays are lexicographically equal, returns 0;
/// </returns>
int strCompare(const char* str1, const char* str2) 
{
    if (str1 == nullptr || str2 == nullptr)
    {
        return -2;
    }
    int i1 = 0;
    int i2 = 0;
    while (str1[i1] && str2[i2])
    {
        if (str1[i1] == str2[i2])
        {
            i1++;
            i2++;
            continue;
        }
        if (str1[i1] > str2[i2])
        {
            return 1;
        }
        else if (str1[i1] < str2[i2]) 
        {
            return -1;
        }
    }
    if ((str1[i1] - str2[i2]) > 0)
    {
        return 1;
    }
    else if ((str1[i1] - str2[i2]) < 0) 
    {
        return -1;
    }
    return 0;
}

/// <summary>
/// A function where you can be signed in as a regular user or an admin.
/// </summary>
/// <returns>
/// True, if you signed in as an admin.
/// False, if you signed in as a user.
/// </returns>
bool signIn()
{   
    cout << "Welcome to IMDB!" << endl;
    cout << "Sign in as: " << endl 
         << "1.User" << endl 
         << "2.Admin" << endl;
    char choice;
    cin >> choice;
    while (choice != '1' && choice != '2')
    {
        cout << "Invalid input! Try again!" << endl;
        cin >> choice;
    }
    if (choice == '2')
    {
        //ANSI code to clear the console.
        cout << "\033[2J\033[H";
        cout << "You were signed in as an admin." << endl;
        return true;
    }
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    cout << "You were signed in as a user." << endl;
    return false;
}

char menu(bool isAdmin)
{
    cout << endl;
    cout << "-----------MENU----------" << endl;
    cout << "1.See all movies" << endl
         << "2.Add a rating" << endl
         << "3.Sort movies by rating" << endl
         << "4.Search movie titles" << endl
         << "5.Search movie genres" << endl;
    if (isAdmin)
    {
        cout << "6.Add a movie" << endl
             << "7.Edit a movie" << endl
             << "8.Delete a movie" << endl;
    }
    cout << "0.Exit" << endl;
    char choice;
    bool isChoiceValid = false;
    while (!isChoiceValid)
    {   
        cin >> choice;
        if (choice < '0' || choice>'8')
        {
            cout << "Invalid command! Try again!" << endl;
            isChoiceValid = false;
        }
        else if (!isAdmin && (choice == '6' || choice == '7' || choice == '8'))
        {
            cout << "Invalid command! Try again!" << endl;
            isChoiceValid = false;
        }
        else
        {
            isChoiceValid = true;
        }           
    }
    return choice;
}

void manageMenuChoice(char choice)
{
    switch (choice)
    {
    case '0': return; break;
    case '1': break;
    case '2': break;
    case '3': break;
    case '4': break;
    case '5': break;
    case '6': break;
    case '7': break;
    case '8': break;
    default: break;
    }
}
int main()
{
    bool isAdmin;
    isAdmin = signIn();
    menu(isAdmin);
    manageMenuChoice(menu(isAdmin));
 

}
