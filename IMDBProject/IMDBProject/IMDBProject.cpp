/*
* Solution to course project # 6
* Introduction to programming course
* Faculty of Matematics and Informatics of Sofia University
* Winter semester 2023/2024
* 
* @author Petya Savova Hrusanova
* @idnumber 7MI0600437
* @compiler vss
* 
* <file with functions and main>
*/

#include <iostream>
#include <fstream>
using namespace std;

/// <summary>
/// Structure that defines movies.
/// </summary>
struct Movie
{
    char title[120] = { '\0' };
    int year = 0;
    char genre[50] = { '\0' };
    char director[50] = { '\0' };
    char cast[270] = { '\0' };
    double rating = 0.0;
    int ratingsCount = 0;
};

/// <summary>
/// Function that lexicographically compares 2 char arrays.
/// </summary>
/// <param name="str1">The first char array.</param>
/// <param name="str2">The second char array.</param>
/// <returns>
/// If any of the arrays is a nullpointer, returns -2;
/// If the first array is lexicographically bigger, returns 1.
/// If the second array is lexicographically bigger, returns -1.
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
/// Checks if str2 is a substring of str1.
/// </summary>
/// <param name="str1"></param>
/// <param name="str2"></param>
/// <returns>True if it is a substring, false otherwise.</returns>
bool isSubstring(const char* str1, const char* str2)
{
    if (!str1 || !str2) {
        return false;
    }
    if (*str2 == '\0') {
        return true;
    }
    for (const char* p = str1; *p != '\0'; ++p) {
        const char* temp1 = p;
        const char* temp2 = str2;
        while (*temp1 != '\0' && *temp2 != '\0' && *temp1 == *temp2) {
            ++temp1;
            ++temp2;
        }
        if (*temp2 == '\0') {
            return true;
        }
    }
    return false;
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
         << "3.Sort movies" << endl
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

/// <summary>
/// Counts the elements in the array.
/// </summary>
/// <param name="movies">An array of movies.</param>
/// <returns>The number of movies in the array.</returns>
int movieCount(Movie* movies)
{
    if (!movies)
    {
        cerr << "No data!" << endl;
        return 0;
    }
    int count = 0;
    while (movies[count++].title[0] != '\0');
    return --count;
}

/// <summary>
/// Checks if every character in the array is a digit.
/// </summary>
/// <param name="text"></param>
/// <returns>True if all the characters are digits, false otherwise.</returns>
bool checkDigits(char text[])
{
    int i = 0;
    while (text[i] != '\0')
    {
        if (text[i] < '0' || text[i]>'9') return false;
        i++;
    }
    return true;
}

/// <summary>
/// Validates whether the input string has correct values to be a rating.
/// </summary>
/// <param name="input">Input string of rating.</param>
/// <returns>True if the value is correct, false otherwise.</returns>
bool isValidRating(const char* input)
{
    if (input[0] == '\0') return false;
    if (input[1] != '\0' && input[1] != '.') return false;
    int i = 0;
    bool decimalFound = false;
    int digitCountAfterDecimal = 0;
    if (input[i] < '0' || input[i] > '9') {
        return false;
    }
    while (input[i] != '\0')
    {
        if (input[i] == '.')
        {
            if (decimalFound)
            {
                return false;
            }
            decimalFound = true;
        }
        else if (input[i] >= '0' && input[i] <= '9')
        {
            if (decimalFound)
            {
                digitCountAfterDecimal++;
                if (digitCountAfterDecimal > 1) {
                    return false;
                }
            }
        }
        else 
        {
            return false;
        }
        i++;
    }
    return true;
}

/// <summary>
/// Transforms a line from the file into a movie variable.
/// </summary>
/// <param name="line">The line read from the file.</param>
/// <returns>Returns the movie with the coresponding data.</returns>
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
    lineIndex++;
    movie.ratingsCount = 0;
    char a = line[lineIndex];
    while (line[lineIndex] >= '0' && line[lineIndex] <= '9')
    {
        movie.ratingsCount = movie.ratingsCount * 10 + (line[lineIndex] - '0');
        lineIndex++;
    }
    return movie;
}

/// <summary>
/// Reads the file with the movies and creates a coresponding Movie array with them.
/// </summary>
/// <returns>A movie array with the movies from the file.</returns>
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

/// <summary>
/// Converts the data in variable 
/// </summary>
/// <param name="movie"></param>
/// <returns></returns>
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
    int integerPart = (int)rating;
    int fractionalPart = (int)((rating - integerPart) * 10);
    line[++lineIndex] = (char)(integerPart + '0');
    line[++lineIndex] = '.';
    line[++lineIndex] = (char)(fractionalPart + '0');
    line[++lineIndex] = ';';

    //Parse count rating
    lineIndex++;
    int countRating = movie.ratingsCount;
    int temp = countRating;
    int digitCount = 0;
    do 
    {
        digitCount++;
        temp /= 10;
    } while (temp > 0);
    int startIndex = lineIndex + digitCount; 
    lineIndex += digitCount - 1;             
    for (int i = 0; i < digitCount; i++) {
        line[lineIndex--] = (char)((countRating % 10) + '0');
        countRating /= 10;                                   
    }
    lineIndex = startIndex;
    line[lineIndex] = '\0'; 

    return line;
}

/// <summary>
/// Saves the array into a file.
/// </summary>
/// <param name="movies">The array with movies.</param>
void saveInFile(Movie* movies)
{
    if (!movies)
    {
        cerr << "No data!"<<endl;
        return;
    }
    string file_name = "movies.txt";
    ofstream output_stream(file_name);
    if (!output_stream) {
        cerr << "Can't open output file!" << endl;
    }
    char* line;
    int index = 0;
    int moviesCount = movieCount(movies);
    while (index < moviesCount)
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

/// <summary>
/// Prints the information for a movie.
/// </summary>
/// <param name="movie"></param>
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

/// <summary>
/// Prints the information for all of the movies in the file onto the console.
/// </summary>
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

/// <summary>
/// Allows users and admins to add rating for a movie and saves it.
/// </summary>
void addRating()
{
    Movie* movies = openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    //Finding the movie
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
    int mCount = movieCount(movies);
    for ( i = 0; i <mCount; i++)
    {                       
        if (strCompare(movies[i].title, inputTitle) == 0)
        {
            break;
        }
    } 
    if (i == mCount)
    {
        cerr << "There was no movie found with this title." << endl;
        return;
    }
    //Adding a rating and validating input
    cout << "How would you rate the movie " << movies[i].title << "?" << endl;
    char inputRating[10];
    cin.clear();
    cin.getline(inputRating, 10);
    while (!isValidRating(inputRating))
    {
        cout << "Add a valid rating!" << endl;
        cin.clear();
        cin.getline(inputRating, 10);
    }

    double newRating = 0.0;
    int index = 0;
    bool decimalFound = false;
    double decimalPlace = 0.1;
    while (inputRating[index] != '\0')
    {
        if (inputRating[index] == '.')
        {
            decimalFound = true;
        }
        else 
        {
            if (decimalFound) 
            {
                newRating += (inputRating[index] - '0') * decimalPlace;
                decimalPlace /= 10;
            }
            else 
            {
                newRating = newRating * 10 + (inputRating[index] - '0');
            }
        }
        index++;
    }

    //Changing the rating for the movie
    movies[i].ratingsCount++;
    double totalRating = movies[i].rating * (movies[i].ratingsCount - 1) + newRating;
    movies[i].rating = round((totalRating / movies[i].ratingsCount) * 10.0) / 10.0;
    saveInFile(movies);
    delete[] movies;
}

/// <summary>
/// Prints out movies with certain rating
/// </summary>
void filterByRating()
{
    Movie* movies = openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    cout << "Enter your minimal rating." << endl;

    char inputRating [10];
    cin >> inputRating;
    while (!isValidRating(inputRating))
    {
        cout << "Wrong input! Try againg." << endl;
        cin >> inputRating;
        continue;
    }
    cout << "These are the movies with rating " << inputRating << " and above:"<<endl;

    int i = 0;
    double actualRating =0.0;
    int index = 0;
    bool decimalFound = false;
    double decimalPlace = 0.1;
    while (inputRating[index] != '\0')
    {
        if (inputRating[index] == '.')
        {
            decimalFound = true;
        }
        else
        {
            if (decimalFound)
            {
                actualRating += (inputRating[index] - '0') * decimalPlace;
                decimalPlace /= 10;
            }
            else
            {
                actualRating = actualRating * 10 + (inputRating[index] - '0');
            }
        }
        index++;
    }
    while (movies[i].title[0] != '\0')
    {
        if (movies[i].rating >= actualRating) printMovie(movies[i]);
        i++;
    }
    delete[] movies;
}

/// <summary>
/// Sorts movies by rating and saves it.
/// </summary>
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
    seeAllMovies();
    delete[] movies;

    cout << "Would you like to filter these movies by a rating?" << endl
        << "1. Yes" << endl
        << "2. No" << endl;
    bool isValidChoice = false;
    char choice; 
    cin >> choice;
    do
    {       
        if (choice != '1' && choice != '2')
        {
            cout << "Wrong input! Try againg." << endl;
            cin >> choice;
            continue;
        }
        isValidChoice = true;
    } while (!isValidChoice);
    switch (choice)
    {
    case '1': filterByRating(); break;
    case '2':break;
    }
}

/// <summary>
/// Sorts movies by title and saves it in the file.
/// </summary>
void sortMoviesByTitle()
{
    Movie* movies = openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    int mCount = movieCount(movies);
    for (int i = 0; i < mCount; i++)
    {
        for (int j = i + 1; j < mCount; j++)
        {
            if (strCompare(movies[i].title, movies[j].title)==1) {
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }
        }
    }
    saveInFile(movies);
    delete[] movies;
    seeAllMovies();
}

/// <summary>
/// Manages the sorting choice.
/// </summary>
void manageSortChoice()
{
    cout << "\033[2J\033[H";
    cout << "How would you like to sort the movies?" << endl
        << "1. By title" << endl
        << "2. By rating" << endl;
    bool isValidChoice = false;
    char choice;
    cin >> choice;
    if (choice != '1' && choice != '2')
    {
        while (!isValidChoice)
        {
            cout << "Wrong input! Try againg!" << endl;
            cin >> choice;
            if (choice == '1' || choice == '2') isValidChoice = true;
        }
    }
    switch (choice)
    {
    case '1': sortMoviesByTitle(); break;
    case '2': sortMoviesByRating(); break;
    }
}

/// <summary>
/// Prints the movie with a matching title.
/// </summary>
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
            cerr << "There was no other movie found with this title." << endl;
            return;
        }
        if (isSubstring(movies[i].title,inputTitle))
        {
            printMovie(movies[i]);
        }
    }
    delete[] movies;
}

/// <summary>
/// Prints out the movies with matching genre.
/// </summary>
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
    delete[] movies;
}

/// <summary>
/// Allows admins to add new movies.
/// </summary>
void addMovie()
{
    Movie* movies = openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";

    cout << "Enter a title name." << endl;
    char inputTitle[100];
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.getline(inputTitle, 100);
    while (inputTitle[0] == '\0')
    {
        cout << "The title cannot be an empty string." << endl;
        cin.getline(inputTitle, 100);
    }

    cout << "Enter year of release." << endl;
    char inputY[20];
    int inputYear;    
    std::cin.clear();
    cin >> inputY;
    inputYear = (inputY[0] - '0') * 1000 + (inputY[1] - '0') * 100 + (inputY[2] - '0') * 10 + (inputY[3] - '0');
    while (inputY[4] != '\0' || !checkDigits(inputY) || (inputYear<=1888 || inputYear>=2025))
    {
        cout << "Invalid year, try again." << endl; 
        std::cin.clear();
        cin >> inputY;
        inputYear = (inputY[0] - '0') * 1000 + (inputY[1] - '0') * 100 + (inputY[2] - '0') * 10 + (inputY[3] - '0');
    }

    cout << "Enter the genre." << endl;
    char inputGenre[50];
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.getline(inputGenre, 50);
    while (inputGenre[0] == '\0')
    {
        cout << "The genre cannot be an empty string." << endl;
        cin.getline(inputGenre, 50);
    }

    cout << "Enter the director's name." << endl;
    char inputDirector[50];
    cin.clear();
    cin.getline(inputDirector, 50);
    while (inputDirector[0] == '\0')
    {
        cout << "The director's name cannot be an empty string." << endl;
        cin.getline(inputDirector, 50);
    }

    cout << "Enter the names of the cast, divided by commas." << endl;
    char inputCast[270];
    cin.clear();
    cin.getline(inputCast, 270);
    while (inputCast[0] == '\0')
    {
        cout << "The cast cannot be an empty string." << endl;
        cin.getline(inputCast, 100);
    }

    cout << "Enter a rating." << endl;
    char inputRating[10];
    cin.clear();
    cin.getline(inputRating, 10);
    while (!isValidRating(inputRating))
    {
        cout << "Enter a valid rating!" << endl;
        cin.clear();
        cin.getline(inputRating, 10);
    }

    cout << "How many people have rated the movie? Enter 1 if you have no information." << endl;
    int inputCountR;
    cin >> inputCountR;
    while (inputCountR < 1)
    {
        cin >> inputCountR;
    }

    Movie newMovie;
    int i;
    for (i = 0; inputTitle[i] != '\0'; ++i) {
        newMovie.title[i] = inputTitle[i];
    }
    newMovie.title[i] = '\0';
    
    newMovie.year = inputYear;

    for (i = 0; inputGenre[i] != '\0'; ++i) {
        newMovie.genre[i] = inputGenre[i];
    }
    newMovie.genre[i] = '\0';

    for (i = 0; inputDirector[i] != '\0'; ++i) {
        newMovie.director[i] = inputDirector[i];
    }
    newMovie.director[i] = '\0';

    for (i = 0; inputCast[i] != '\0'; ++i) {
        newMovie.cast[i] = inputCast[i];
    }
    newMovie.cast[i] = '\0';

    newMovie.rating = 0.0;
    int index = 0;
    bool decimalFound = false;
    double decimalPlace = 0.1;
    while (inputRating[index] != '\0') {
        if (inputRating[index] == '.') {
            decimalFound = true;
        }
        else {
            if (decimalFound) {
                newMovie.rating += (inputRating[index] - '0') * decimalPlace;
                decimalPlace /= 10;
            }
            else {
                newMovie.rating = newMovie.rating * 10 + (inputRating[index] - '0');
            }
        }
        index++;
    }

    newMovie.ratingsCount = inputCountR;

    int mCount = movieCount(movies);
    if (mCount == 29)
    {
        cerr << "You cannot add movies at the moment. Delete or edit existing ones." << endl;
        return;
    }
    movies[mCount] = newMovie;
    saveInFile(movies);
    delete[] movies;
}

/// <summary>
/// Allows admins to edit existing movies.
/// </summary>
void editMovie()
{
    Movie* movies = openFile();
    cout << "\033[2J\033[H";
    cout << "Which movie are you going to edit?" << endl;
    char inputTitle[50];
    cin.clear();
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
            printMovie(movies[i]);
            char choice;
            while (true)
            { 

                cout << "What would you like to edit:" << endl
                << "1. Title" << endl
                << "2. Year of release" << endl
                << "3. Genre" << endl
                << "4. Director" << endl
                << "5. Cast" << endl
                << "6. Rating" << endl
                << "0. Back to menu" << endl;

                cin >> choice;
                switch(choice)
                { 
                case '0':
                {
                    saveInFile(movies);
                    delete[] movies;
                    return;
                    break;
                }
                case '1': 
                {
                    cout << "Enter a new title"<<endl;
                    char inputTitle[100];
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.clear();
                    cin.getline(inputTitle, 100);
                    while (inputTitle[0] == '\0')
                    {
                        cout << "The title cannot be an empty string." << endl;
                        //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.clear();
                        cin.getline(inputTitle, 100);
                    }
                    int j = 0;
                    for (j = 0; inputTitle[j] != '\0'; ++j) {
                        movies[i].title[j] = inputTitle[j];
                    }
                    movies[i].title[j] = '\0';
                    cout << "\033[2J\033[H";
                    printMovie(movies[i]);
                    break;
                }
                    
                case '2': 
                {
                    cout << "Enter a new release year." << endl;
                    char inputY[20];
                    int inputYear;
                    std::cin.clear();
                    cin >> inputY;
                    inputYear = (inputY[0] - '0') * 1000 + (inputY[1] - '0') * 100 + (inputY[2] - '0') * 10 + (inputY[3] - '0');
                    while (inputY[4] != '\0' || !checkDigits(inputY) || (inputYear <= 1888 || inputYear >= 2025))
                    {
                        cout << "Invalid year, try again." << endl;
                        std::cin.clear();
                        cin >> inputY;
                        inputYear = (inputY[0] - '0') * 1000 + (inputY[1] - '0') * 100 + (inputY[2] - '0') * 10 + (inputY[3] - '0');
                    }
                    movies[i].year = inputYear;
                    cout << "\033[2J\033[H";
                    printMovie(movies[i]);
                    break;

                }
                case '3': {
                    cout << "Enter a new genre" << endl;
                    char inputGenre[50];
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.getline(inputGenre, 50);
                    while (inputGenre[0] == '\0')
                    {
                        cout << "The genre cannot be an empty string." << endl;
                        std::cin.clear();
                        cin.getline(inputGenre, 50);
                    }
                    int j = 0;
                    for (j = 0; inputGenre[j] != '\0'; ++j) {
                        movies[i].genre[j] = inputGenre[j];
                    }
                    movies[i].genre[j] = '\0';
                    cout << "\033[2J\033[H";
                    printMovie(movies[i]);
                    break;
                }
                case '4': {
                    cout << "Enter a new director" << endl;
                    char inputDirector[50];
                    cin.clear();
                    cin.getline(inputDirector, 50);
                    while (inputDirector[0] == '\0')
                    {
                        cout << "The director's name cannot be an empty string." << endl;
                        std::cin.clear();
                        cin.getline(inputDirector, 50);
                    }
                    int j = 0;
                    for (j = 0; inputDirector[j] != '\0'; ++j) {
                        movies[i].director[j] = inputDirector[j];
                    }
                    movies[i].director[j] = '\0';
                    cout << "\033[2J\033[H";
                    printMovie(movies[i]);
                    break;
                }
                case '5': {
                    cout << "Enter a new cast" << endl;
                    char inputCast[270];
                    cin.clear();
                    cin.getline(inputCast, 270);
                    while (inputCast[0] == '\0')
                    {
                        cout << "The cast cannot be an empty string." << endl;
                        std::cin.clear();
                        cin.getline(inputCast, 100);
                    }
                    int j = 0;
                    for (j = 0; inputCast[j] != '\0'; ++j) {
                        movies[i].cast[j] = inputCast[j];
                    }
                    movies[i].cast[j] = '\0';
                    cout << "\033[2J\033[H";
                    printMovie(movies[i]);
                    break;
                    cout << "\033[2J\033[H";
                    printMovie(movies[i]);
                    break;
                }
                case '6': {
                    cout << "Enter a new rating" << endl;
                    char inputRating[10];
                    cin.clear();
                    cin>>inputRating;
                    while (!isValidRating(inputRating))
                    {
                        cout << "Enter a valid rating." << endl;
                        cin.clear();
                        cin>>inputRating;
                    }

                    double newRating = 0.0;
                    int index = 0;
                    bool decimalFound = false;
                    double decimalPlace = 0.1;
                    while (inputRating[index] != '\0')
                    {
                        if (inputRating[index] == '.')
                        {
                            decimalFound = true;
                        }
                        else
                        {
                            if (decimalFound)
                            {
                                newRating += (inputRating[index] - '0') * decimalPlace;
                                decimalPlace /= 10;
                            }
                            else
                            {
                                newRating = newRating * 10 + (inputRating[index] - '0');
                            }
                        }
                        index++;
                    }
                    movies[i].rating = newRating;
                    cout << "\033[2J\033[H";
                    printMovie(movies[i]);
                    break;
                }
                default: cout << "Wrong input try again." << endl; break;
                }
                
            }
            
        }
        
    }
    
}

/// <summary>
/// Allows admins to delete a movie
/// </summary>
void deleteMovie()
{
    Movie* movies = openFile();
    //ANSI code to clear the console.
    cout << "\033[2J\033[H";
    cout << "Which movie would you like to delete?" << endl;
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
            int cMovies = movieCount(movies);
            if (i == cMovies - 1)
            {
                movies[i].title[0] = '\0';
                break;
            }
            for (i = 0; i < cMovies-1; i++)
            {
                movies[i] = movies[i + 1];
            }
            movies[i].title[0] = '\0';
            break;
        }
    }
    saveInFile(movies);
    delete[] movies;
}

/// <summary>
/// Manages the choice for menu.
/// </summary>
/// <param name="isAdmin">True if your role is Admin, otherwise false.</param>
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
            case '3': manageSortChoice(); break;
            case '4': searchMoviesByTitle(); break;
            case '5': searchMoviesByGenre(); break;
            case '6': addMovie(); break;
            case '7': editMovie(); break;
            case '8': deleteMovie(); break;
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
