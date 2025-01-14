#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct Movie
{
    char title[120] = {'\0'};
    int year;
    char genre[50];
    char director[50];
    char cast[270];
    double rating;
    int ratingsCount;
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

int movieCount(Movie* movies)
{
    int count = 0;
    while (movies[count++].title[0] != '\0');
    return --count;
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
    while (line[lineIndex] != ';') {
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
    //Parse the number of people who rated the movie
    lineIndex--;
    movie.ratingsCount = 0;
    char a = line[lineIndex];
    while (line[lineIndex] >= '0' && line[lineIndex] <= '9')
    {
        movie.ratingsCount = movie.ratingsCount * 10 + (line[lineIndex] - '0');
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

char* dataToLine(Movie movie)
{
    char* line= new char[500];
    int lineIndex = 0;
    int movieFieldIndex = 0;

    //Parse title
    while (movie.title[movieFieldIndex] != '\0')
    {
        line[lineIndex] = movie.title[movieFieldIndex];
        lineIndex++;
        movieFieldIndex++;
    }
    line[lineIndex] = ';';
    
    //Parse year
    line[++lineIndex] = (char)((movie.year / 1000) + '0');
    line[++lineIndex] = (char)(((movie.year / 100) %10) + '0');
    line[++lineIndex] = (char)(((movie.year / 10) %10) + '0');
    line[++lineIndex] = (char)(movie.year%10 + '0');
    line[++lineIndex] = ';';

    //Parse genre
    movieFieldIndex = 0;
    lineIndex++;
    while (movie.genre[movieFieldIndex] != '\0')
    {
        line[lineIndex] = movie.genre[movieFieldIndex];
        lineIndex++;
        movieFieldIndex++;
    }
    line[lineIndex] = ';';

    //Parse director
    movieFieldIndex = 0;
    lineIndex++;
    while (movie.director[movieFieldIndex] != '\0')
    {
        line[lineIndex] = movie.director[movieFieldIndex];
        lineIndex++;
        movieFieldIndex++;
    }
    line[lineIndex] = ';';

    //Parse actors
    movieFieldIndex = 0;
    lineIndex++;
    while (movie.cast[movieFieldIndex] != '\0')
    {
        line[lineIndex] = movie.cast[movieFieldIndex];
        lineIndex++;
        movieFieldIndex++;
    }
    line[lineIndex] = ';';

    //Parse rating
    double rating = movie.rating;
    double remainder = rating - floor(movie.rating)*10;
    line[++lineIndex] = (char)(rating + '0');
    line[++lineIndex] = '.';
    line[++lineIndex] = (char)((int)remainder + '0');
    line[++lineIndex] = ';';

    //Parse count rating
    int countRating = movie.ratingsCount;
    int temp = countRating;
    int digitCount = 0;
    do 
    {
        digitCount++;
        temp /= 10;
    } while (temp > 0);
    lineIndex = lineIndex + digitCount;
    for (int i = 0; i < digitCount; i++)
    {
        line[lineIndex] == (char)((countRating % 10) + '0');
        countRating = countRating / 10;
        lineIndex--;
    }
    line[++lineIndex] = '\0';
    return line;
}

void saveInFile(Movie* movies)
{
    string file_name = "moviesRes.txt";
    ofstream output_stream(file_name);
    if (!output_stream) {
        cerr << "Can't open output file!" << endl;
    }
    char* line;
    int index = 0;
    int moviesCount = movieCount(movies);
    while (index<moviesCount)
    { 
        line = dataToLine(movies[index]);
        if (line[0] == ';') {
            break;
        }
        output_stream << line << std::endl;
        delete[] line;
        line = nullptr;
        index++;
    }
    output_stream.close();
}

void printMovie(Movie movie)
{
    cout << "Title: " << movie.title << endl
        << "Year: " << movie.year << endl
        << "Genre: " << movie.genre << endl
        << "Director: " << movie.director << endl
        << "Actors: " << movie.cast << endl
        << "Rating: " << (round(movie.rating * 10.0) / 10.0) << endl;

    cout << endl;
}
void seeAllMovies()
{
    Movie* movies=openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    int mCount = movieCount(movies);
    if (movies == nullptr) cerr << "No data!" << endl;
    else
    {
        for (int i=0;i<mCount;i++)
        {
            if (movies[i].title[0] == '\0') break;
            printMovie(movies[i]);
        }
    }
    delete[]movies;
}

void addRating()
{
    Movie* movies = openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    cout << "Please type the title of the movie you want to rate: ";
    char inputTitle[50];
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.getline(inputTitle, 100);
    cout << endl;
    if (movies == nullptr)
    {
        cerr << "No data!" << endl;
        return;
    }
    int i = 0;
    for ( i = 0; i <30; i++)
    {
       
        if (movies[i].title[0] == '\0')
        {
            cerr << "There was no movie found with this title." << endl;
            return;
        }
        if (strCompare(movies[i].title, inputTitle) == 0)
        {
            break;
        }
    } 
    cout << "How would you rate the movie " << movies[i].title << "?" << endl;
    int rating;
    cin >> rating;
    while (rating < 0 || rating>10)
    {
        cout << "Enter a valid rating. A whole number in the interval [0,10]." << endl;
        cin >> rating;
    }
    double newRating = movies[i].rating * (double)movies[i].ratingsCount + rating;
    movies[i].ratingsCount++;
    newRating = newRating / (double)movies[i].ratingsCount;
    movies[i].rating = round(newRating * 10.0) / 10.0;
    saveInFile(movies);
}

void sortMoviesByRating()
{
    Movie* movies = openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    int mCount = movieCount(movies);
    for (int i = 0; i < mCount; i++)
    {
        for (int j = i+1; j < mCount; j++)
        {
            if (movies[i].rating < movies[j].rating) {
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }
        }
    }
    saveInFile(movies);
}

void searchMoviesByTitle()
{
    Movie* movies = openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    cout << "What movie are you looking for?"<<endl;
    char inputTitle[50];
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.getline(inputTitle, 100);
    cout << endl;
    if (movies == nullptr)
    {
        cerr << "No data!" << endl;
        return;
    }
    int i = 0;
    for (i = 0; i < 30; i++)
    {

        if (movies[i].title[0] == '\0')
        {
            cerr << "There was no movie found with this title." << endl;
            return;
        }
        if (strCompare(movies[i].title, inputTitle) == 0)
        {
            break;
        }
    }
    printMovie(movies[i]);
}

void searchMoviesByGenre()
{
    Movie* movies = openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    cout << "What genre of movies are you looking for?" << endl;
    char inputGenre[50];
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.getline(inputGenre, 50);
    cout << endl;
    if (movies == nullptr)
    {
        cerr << "No data!" << endl;
        return;
    }
    int i = 0;
    for (i = 0; i < 30; i++)
    {

        if (movies[i].title[0] == '\0')
        {
            cerr << "There is nothing else in "<<inputGenre<<"." << endl;
            return;
        }
        if (strCompare(movies[i].genre, inputGenre) == 0)
        {
            printMovie(movies[i]);
        }
    }
    
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
            case '1': seeAllMovies(); break;
            case '2': addRating(); break;
            case '3': sortMoviesByRating(); break;
            case '4': searchMoviesByTitle(); break;
            case '5': searchMoviesByGenre(); break;
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
