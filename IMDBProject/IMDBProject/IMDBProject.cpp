#include <iostream>
#include <fstream>
using namespace std;

struct Movie
{
    char title[120];
    int year;
    char genre[50];
    char director[50];
    char cast[270];
    double rating;
};

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

/// <summary>
/// Prints out the menu and validates the menu choice.
/// </summary>
/// <param name="isAdmin"></param>
/// <returns>A char value which represents the chosen command from the menu.</returns>
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

Movie lineToData(char line[])
{
    Movie movie;
    int lineIndex = 0;
    int movieFieldIndex = 0;

    // Parse Title
    while (line[lineIndex] != ';') {
        movie.title[movieFieldIndex++] = line[lineIndex++];
    }
    movie.title[movieFieldIndex] = '\0'; 
    lineIndex++;

    //Parse Year
    movie.year = 0;
    movie.year += (line[lineIndex] - '0') * 1000;
    movie.year += (line[++lineIndex] - '0') * 100;    
    movie.year += (line[++lineIndex] - '0') * 10;    
    movie.year += (line[++lineIndex] - '0');          
    lineIndex = lineIndex+2; 

    // Parse Genre
    movieFieldIndex = 0;
    while (line[lineIndex] != ';') {
        movie.genre[movieFieldIndex++] = line[lineIndex++];
    }
    movie.genre[movieFieldIndex] = '\0';
    lineIndex++;

    // Parse Director
    movieFieldIndex = 0;
    while (line[lineIndex] != ';') {
        movie.director[movieFieldIndex++] = line[lineIndex++];
    }
    movie.director[movieFieldIndex] = '\0';
    lineIndex++;

    // Parse Cast
    movieFieldIndex = 0;
    while (line[lineIndex] != ';') {
        movie.cast[movieFieldIndex++] = line[lineIndex++];
    }
    movie.cast[movieFieldIndex] = '\0';
    lineIndex++; 

    // Parse Rating
    movie.rating = 0.0;
    bool decimalFound = false;
    double decimalPlace = 0.1;
    while (line[lineIndex] != '\0') {
        if (line[lineIndex] == '.') {
            decimalFound = true;
        }
        else {
            if (decimalFound) {
                movie.rating += (line[lineIndex] - '0') * decimalPlace;
                decimalPlace /= 10;
            }
            else {
                movie.rating = movie.rating * 10 + (line[lineIndex] - '0');
            }
        }
        lineIndex++;
    }
    return movie;
}

Movie* openFile()
{ 
    Movie* movies = new Movie[30];
    string file_name = "movies.txt";
    ifstream input_stream(file_name);
    if (!input_stream) {
        cerr << "Can't open input file!" << endl;
    }
    const int MAX_LINE_LENGTH = 500;  
    char line[MAX_LINE_LENGTH];
    int index = 0;
    while (input_stream.getline(line, MAX_LINE_LENGTH))
    {
        movies[index] = lineToData(line);
        index++;
    }
    input_stream.close();
    return movies;
}

void seeAllMovies()
{
    Movie* movies=openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    if (movies == nullptr) cerr << "No data!" << endl;
    else
    {
        for (int i=0;i<2;i++)
        {
            if (movies[i].year==0) break;
            else
            {
                cout << "Title: " << movies[i].title << endl
                     <<"Year: "<<movies[i].year<<endl
                     <<"Genre: "<<movies[i].genre<<endl
                     <<"Director: "<<movies[i].director<<endl
                     <<"Actors: "<<movies[i].cast<<endl
                     <<"Rating: "<<movies[i].rating<<endl;
            }
            cout << endl;
        }
    }
    delete[]movies;
}
void addRating()
{

}
void sortMoviesByRating()
{

}
void searchMoviesByTitle()
{

}
void searchMoviesByGenre()
{

}
void addMovie()
{

}
void editMovie()
{

}
void deleteMovie()
{

}

void manageMenuChoice(bool isAdmin)
{
    char choice;
    while (true) {
        choice = menu(isAdmin);

        switch (choice)
        {
            case '0': return; break;
            case '1':seeAllMovies(); break;
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
}
int main()
{
    bool isAdmin;
    isAdmin = signIn();
    manageMenuChoice(isAdmin);
}
