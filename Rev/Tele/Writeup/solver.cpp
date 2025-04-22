#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <cmath>
using namespace std;

#define BOLDRED "\e[1;91m"
#define BOLDGREEN "\e[1;32m"
#define RED "\e[0;31m"
#define RESET "\e[0m"

bool horizontalSearch(char **, char **, char *, int, int, double &, int *, int *);
bool verticalSearch(char **, char **, char *, int, int, double &, int *, int *);
bool reverseHorizontalSearch(char **, char **, char *, int, int, double &, int *, int *);
bool reverseVerticalSearch(char **, char **, char *, int, int, double &, int *, int *);
bool topToBottomRIGHTDiognalSearch(char **, char **, char *, int, int, double &, int *, int *);
bool bottomToTopRIGHTDiognalSearch(char **, char **, char *, int, int, double &, int *, int *);
bool topToBottomLEFTDiognalSearch(char **, char **, char *, int, int, double &, int *, int *);
bool bottomToTopLEFTDiognalSearch(char **, char **, char *, int, int, double &, int *, int *);

void welcome();

int main(int argc, char **argv)
{

    if (argc == 2)
    {

        int counter = strlen(argv[1]);
        int a = 1;

        bool txtFound = false;

        while (true)
        {
            if (argv[1][counter - a] == 't')
            {
                a++;

                if (argv[1][counter - a] == 'x')
                {
                    a++;

                    if (argv[1][counter - a] == 't')
                    {
                        a++;

                        if (argv[1][counter - a] == '.')
                        {
                            txtFound = true;
                            break;
                        }
                    }
                    else
                        break;
                }
                else
                    break;
            }
            else
                break;
        }

        char *filename = new char[counter + 5];

        strcpy(filename, argv[1]);

        fstream readLetters;

        if (!txtFound)
        {
            strcat(filename, ".txt");
        }

        readLetters.open(filename, ios::in);

        if (!readLetters)
        {
            cout << "Error opening file";
            return 0;
        }
        else
        {
            int countLetters = 0;

            char che;
            while (readLetters.get(che))
            {
                if (che != ',' && che != '\n')
                {
                    countLetters++;
                }
                else if (che == '\n')
                {
                    break;
                }
            }

            int GridSize = sqrt(countLetters);

            char **letters = new char *[GridSize];
            char **usedLetters = new char *[GridSize];
            char **notUsedLetters = new char *[GridSize];
            int *heavyRow = new int[GridSize];
            int *heavyCol = new int[GridSize];

            char ch;

            readLetters.seekg(0, ios::beg);
            readLetters.clear();

            for (int i = 0; i < GridSize; i++)
            {
                heavyCol[i] = 0;
                heavyRow[i] = 0;
                letters[i] = new char[GridSize];
                usedLetters[i] = new char[GridSize];
                notUsedLetters[i] = new char[GridSize];

                for (int j = 0; j < GridSize; j++)
                {
                    readLetters.get(ch);

                    if (ch == ',' || ch == ' ')
                    {
                        readLetters.get(ch);
                    }
                    // if encountered newline then exit
                    else if (ch == '\n')
                    {
                        break;
                    }
                    letters[i][j] = ch;
                    notUsedLetters[i][j] = ch;
                }
            }

            readLetters.close();

            for (int i = 0; i < GridSize; i++)
            {
                for (int j = 0; j < GridSize; j++)
                {
                    usedLetters[i][j] = ' ';
                }
            }

            fstream readWords;

            readWords.open(filename, ios::in);

            int totWords = 0;
            char characters[32];

            int linesize = countLetters * 2 + 1;

            readWords.ignore(linesize);

            while (readWords.getline(characters, 32, ','))
            {
                totWords++;
            }

            readWords.close();

            readWords.open(filename, ios::in);

            readWords.ignore(linesize);

            char **words = new char *[totWords];

            for (int i = 0; i < totWords; i++)
            {
                words[i] = new char[32];
            }

            char chh;
            int wordIndex = 0;
            int wordCounter = 0;

            while (readWords.get(chh))
            {
                if (isalpha(chh))
                {
                    words[wordCounter][wordIndex] = chh;
                    wordIndex++; 
                }
                else
                { 
                    if (wordIndex > 0)
                    {
                        words[wordCounter][wordIndex] = '\0';
                        wordCounter++; 
                        wordIndex = 0; 
                    }
                    if (chh == '\n' || wordCounter == totWords)
                    {
                        break;
                    }
                }
            }

            readWords.close();

           

     

            // some useful variables for the search algorithms

            int i = 0;

            int wordSum = 0;
            double wordAverage;

            double timeSum = 0;

            bool found;

            int horizontalCounter = 0;
            int reverseHorizontalCounter = 0;
            int verticalCounter = 0;
            int reverseVerticalCounter = 0;
            int diagonal_1_Counter = 0;
            int diagonal_2_Counter = 0;
            int diagonal_3_Counter = 0;
            int diagonal_4_Counter = 0;

            do
            {
                // calculating wordlength of the words in the file
                int wordLength = strlen(words[i]);

                // running sum for wordlength average
                wordSum = wordSum + wordLength;
                                    // displaying the current word
               

                // function calls
                found = horizontalSearch(letters, usedLetters, words[i], GridSize, wordLength, timeSum, heavyRow, heavyCol);

                // incrementing the counters when a word is found
                if (found)
                    horizontalCounter++;

                if (!found)
                {
                    found = verticalSearch(letters, usedLetters, words[i], GridSize, wordLength, timeSum, heavyRow, heavyCol);

                    if (found)
                        verticalCounter++;

                    if (!found)
                    {
                        found = reverseHorizontalSearch(letters, usedLetters, words[i], GridSize, wordLength, timeSum, heavyRow, heavyCol);

                        if (found)
                            reverseHorizontalCounter++;

                        if (!found)
                        {
                            found = reverseVerticalSearch(letters, usedLetters, words[i], GridSize, wordLength, timeSum, heavyRow, heavyCol);

                            if (found)
                                reverseVerticalCounter++;

                            if (!found)
                            {
                                found = topToBottomRIGHTDiognalSearch(letters, usedLetters, words[i], GridSize, wordLength, timeSum, heavyRow, heavyCol);

                                if (found)
                                    diagonal_1_Counter++;

                                if (!found)
                                {
                                    found = bottomToTopRIGHTDiognalSearch(letters, usedLetters, words[i], GridSize, wordLength, timeSum, heavyRow, heavyCol);

                                    if (found)
                                        diagonal_2_Counter++;

                                    if (!found)
                                    {
                                        found = topToBottomLEFTDiognalSearch(letters, usedLetters, words[i], GridSize, wordLength, timeSum, heavyRow, heavyCol);

                                        if (found)
                                            diagonal_3_Counter++;

                                        if (!found)
                                        {

                                            found = bottomToTopLEFTDiognalSearch(letters, usedLetters, words[i], GridSize, wordLength, timeSum, heavyRow, heavyCol);

                                            if (found)
                                                diagonal_4_Counter++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                i++;

            } while (i < totWords);



            for (int i = 0; i < GridSize; i++)
            {

                for (int j = 0; j < GridSize; j++)
                {
                    if (usedLetters[i][j] == ' ')
                    {
                        notUsedLetters[i][j] = letters[i][j]; 
                    }
                    else
                    {
                        notUsedLetters[i][j] = ' ';         
                    }
                }


            }


            string teleword;
            int k=0;
            for (int i = 0; i < GridSize; i++)
            {

                for (int j = 0; j < GridSize; j++)
                {
                    if (usedLetters[i][j] == ' ')
                    {
                        teleword[k] = notUsedLetters[i][j];;
                        cout<<notUsedLetters[i][j];
                        k++;
                    }
                }
            }

            for (int i = 0; i < GridSize; i++)
            {
                delete[] letters[i];
                delete[] usedLetters[i];
                delete[] notUsedLetters[i];
            }
            for (int i = 0; i < totWords; i++)
            {
                delete[] words[i];
            }

            delete[] letters;
            delete[] notUsedLetters;
            delete[] usedLetters;
            delete[] words;
            delete[] filename;

            letters = NULL;
            notUsedLetters = NULL;
            usedLetters = NULL;
            words = NULL;
            filename = NULL;

            return 0;
        }
    }
    else
    {
        cout << BOLDRED << "INVALID NUMBER OF ARGUMENTS" << argc <<RESET <<endl;
    }
}



bool horizontalSearch(char **letters, char **usedLetters, char *word, int GridSize, int wordLength, double &timeSum, int *heavyRow, int *heavyCol)
{

    int counter = 0;

    int positionRow;
    int positionCol;

    auto startWord = chrono::high_resolution_clock::now(); // clock start time

    for (int i = 0; i < GridSize; i++)
    {
        for (int j = 0; j < GridSize; j++)
        {
            if (letters[i][j] == word[0]) // if letter is matched with the first letter of the word
            {
                int col = j + 1; // go to next column

                counter = 1;

                for (int k = 1; k < wordLength; k++) // and search for the rest of the letters
                {
                    // col must not be greater than GridSize
                    if (col < GridSize && letters[i][col] == word[k]) // if letters then
                    {
                        col++;     // go to next column
                        counter++; // and increment the counter

                        if (counter == wordLength) // if counter is equal to the word length
                        {
                            positionRow = i; // recording the positions
                            positionCol = j;

                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (counter == wordLength) // if counter is equal to the word length
            {
                auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                for (int i = 0; i < GridSize; i++)
                {
                    for (int j = 0; j < GridSize; j++)
                    {


                        if (i == positionRow && j == positionCol) // if position is found
                        {

                            for (int k = 0; k < wordLength; k++) // printing word from that position
                            {
                                usedLetters[positionRow][positionCol + k] = letters[positionRow][positionCol + k]; // assigning letters to usedLetters array on same index
                                heavyRow[positionRow]++;                                                           // incrementing the heavyRow array on same index
                                heavyCol[positionCol + k]++;                                                       // going to next columns and incrementing the heavyCol array on same index
                            }
                        }
                    }
                }




                return true;
            }
            else
            {
                counter = 0; // if counter is not equal to the word length then resetting the counter
            }
        }
    }

    return false;
}

bool verticalSearch(char **letters, char **usedLetters, char *word, int GridSize, int wordLength, double &timeSum, int *heavyRow, int *heavyCol)
{

    int counter = 0;
    int row;
    int positionRow;
    int positionCol;

    auto startWord = chrono::high_resolution_clock::now();

    for (int i = 0; i < GridSize; i++)
    {
        for (int j = 0; j < GridSize; j++)
        {

            if (letters[j][i] == word[0]) // if letter is matched with the first letter of the word
            {
                counter = 1;

                row = j + 1; // going to next row

                for (int k = 1; k < wordLength; k++)
                {
                    // also checking that row does not exceed the GridSize
                    if (row < GridSize && letters[row][i] == word[k]) // checking if next word matches or not
                    {
                        counter++; // if letter is matched then incrementing the counter
                        row++;     // also going to next row

                        if (counter == wordLength) // if counter is equal to the word length
                        {
                            positionRow = j; // recording the positions
                            positionCol = i;
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }

            // if counter is equal to the word length
            if (counter == wordLength)
            {
                auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                int k = 0;

                for (int i = 0; i < GridSize; i++)
                {
                    for (int j = 0; j < GridSize; j++)
                    {

                        // if position is found
                        if (i == positionRow + k && j == positionCol && k < wordLength)
                        {
                            usedLetters[positionRow + k][positionCol] = letters[positionRow + k][positionCol]; // assigning letters to usedLetters array on same index
                            heavyCol[positionCol]++;                                                           // incrementing the heavyCol array on same index
                            heavyRow[positionRow + k]++;                                                       // incrementing the heavyRow array and also going to next rows
                            k++;
                        }
                    }
                }

     

                return true;
            }
            else
            {
                counter = 0; // if counter is not equal to the word length then resetting the counter
            }
        }
    }

    return false;
}

bool reverseHorizontalSearch(char **letters, char **usedLetters, char *word, int GridSize, int wordLength, double &timeSum, int *heavyRow, int *heavyCol)
{
    int counter = 0;
    int positionRow;
    int positionCol;
    int col;

    auto startWord = chrono::high_resolution_clock::now();

    for (int i = 0; i < GridSize; i++)
    {
        for (int j = GridSize - 1; j >= 0; j--)
        {

            if (letters[i][j] == word[0]) // if letter is matched with the first letter of the word
            {
                counter = 1;

                col = j - 1; // going to previous column

                for (int k = 1; k < wordLength; k++)
                {
                    if (col >= 0 && letters[i][col] == word[k]) // checking if next letter matches or not/
                    {
                        counter++; // if letter is matched then incrementing the counter
                        col--;     // also going to previous column

                        if (counter == wordLength) // if counter is equal to the word length
                        {
                            positionRow = i;       // recording the positions
                            positionCol = col + 1; // recording the word ending position

                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (counter == wordLength)
            {
                auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                int k = 0;

                for (int i = 0; i < GridSize; i++)
                {
                    for (int j = 0; j < GridSize; j++)
                    {
                        // if position is found

                        if (i == positionRow && j == positionCol + k && k < wordLength)
                        {

                            usedLetters[positionRow][positionCol + k] = letters[positionRow][positionCol + k]; // assigning letters to usedLetters array on same index
                            heavyCol[positionCol + k]++;                                                       // incrementing the heavyCol array and also going to next columns
                            heavyRow[positionRow]++;                                                           // incrementing the heavyRow array on same index

                            k++;
                        }
                    }
                }


                return true;
            }
            else
            {
                counter = 0; // if counter is not equal to the word length then resetting the counter
            }
        }
    }

    return false;
}

bool reverseVerticalSearch(char **letters, char **usedLetters, char *word, int GridSize, int wordLength, double &timeSum, int *heavyRow, int *heavyCol)
{
    int counter = 0;
    int positionRow;
    int positionCol;
    int row;
    auto startWord = chrono::high_resolution_clock::now();

    for (int i = 0; i < GridSize; i++)
    {
        for (int j = GridSize - 1; j >= 0; j--)
        {

            if (letters[j][i] == word[0]) // if letter is matched with the first letter of the word
            {
                counter = 1;
                row = j - 1; // going to previous row

                for (int k = 1; k < wordLength; k++)
                {
                    if (row >= 0 && letters[row][i] == word[k]) // checking if next letter matches or not
                    {
                        counter++; // if letter is matched then incrementing the counter
                        row--;     // also going to previous row

                        if (counter == wordLength) // if counter is equal to the word length
                        {
                            positionRow = row + 1; // recording the end position of the word
                            positionCol = i;       // recording the start position of the word
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (counter == wordLength)
            {
                auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                int k = 0;

                for (int i = 0; i < GridSize; i++)
                {
                    for (int j = 0; j < GridSize; j++)
                    {

                        if (i == positionRow + k && j == positionCol && k < wordLength)
                        {
                            usedLetters[positionRow + k][positionCol] = letters[positionRow + k][positionCol]; // assigning letters to usedLetters array on same index
                            heavyCol[positionCol]++;                                                           // incrementing the heavyCol array on same index
                            heavyRow[positionRow + k]++;                                                       // incrementing the heavyRow array and also going to next rows
                            k++;
                        }
                    }
                }
           

                return true;
            }
            else
            {
                counter = 0;
            }
        }
    }

    return false;
}

bool topToBottomRIGHTDiognalSearch(char **letters, char **usedLetters, char *word, int GridSize, int wordLength, double &timeSum, int *heavyRow, int *heavyCol)
{
    int counter = 0;
    int row;
    int column;

    int positionRow;
    int positionCol;

    auto startWord = chrono::high_resolution_clock::now();

    for (int i = 0; i < GridSize; i++)
    {
        for (int j = 0; j < GridSize; j++)
        {
            if (letters[i][j] == word[0]) // if letter is matched with the first letter of the word
            {
                counter = 1;

                row = i + 1;    // going to next row
                column = j + 1; // going to next column

                for (int k = 1; k < wordLength; k++)
                {
                    // also checking row and column does not exceed the grid size
                    if (row < GridSize && column < GridSize && letters[row][column] == word[k]) // checking if next letter matches or not
                    {
                        counter++; // if letter is matched then incrementing the counter
                        row++;     // also going to next row
                        column++;  // also going to next column

                        if (counter == wordLength) // if counter is equal to the word length
                        {
                            positionRow = i; // recording start positions of the word
                            positionCol = j;

                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (counter == wordLength)
            {
                auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                int k = 0;

                for (int i = 0; i < GridSize; i++)
                {
                    for (int j = 0; j < GridSize; j++)
                    {

                        // if position is found
                        if (i == positionRow + k && j == positionCol + k && k < wordLength)
                        {
                            usedLetters[positionRow + k][positionCol + k] = letters[positionRow + k][positionCol + k]; // assigning letters to usedLetters array on same index
                            heavyCol[positionCol + k]++;                                                               // incrementing the heavyCol and also going to next columns
                            heavyRow[positionRow + k]++;                                                               // incrementing the heavyRow and also going to next rows

                            k++;
                        }
                    }

                }


                return true;
            }
            else
            {
                counter = 0; // if counter is not equal to the word length then resetting the counter
            }
        }
    }
    return false;
}

bool bottomToTopRIGHTDiognalSearch(char **letters, char **usedLetters, char *word, int GridSize, int wordLength, double &timeSum, int *heavyRow, int *heavyCol)
{
    auto startWord = chrono::high_resolution_clock::now();

    int counter = 0;
    int positionRow;
    int positionCol;

    int row;
    int column;

    for (int i = GridSize - 1; i >= 0; i--)
    {
        for (int j = 0; j < GridSize; j++)
        {
            if (letters[i][j] == word[0]) // if letter is matched with the first letter of the word
            {
                counter = 1;

                row = i - 1;    // going to previous row
                column = j + 1; // going to next column

                for (int k = 1; k < wordLength; k++)
                {

                    if (row >= 0 && column < GridSize && letters[row][column] == word[k]) // checking if next letter matches or not
                    {
                        counter++; // if letter is matched then incrementing the counter
                        row--;     // also going to previous row
                        column++;  // also going to next column

                        if (counter == wordLength) // if counter is equal to the word length
                        {
                            positionCol = column - 1; // recording the start positions of the word
                            positionRow = row + 1;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (counter == wordLength) // if counter is equal to the word length
            {
                auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                int k = 0;
                int l = 0;

                for (int i = 0; i < GridSize; i++)
                {
                    for (int j = 0; j < GridSize; j++)
                    {
                        // if position is found
                        if (i == positionRow + k && j == positionCol - l && k < wordLength)
                        {
                            usedLetters[positionRow + k][positionCol - l] = letters[positionRow + k][positionCol - l]; // assigning letters to usedLetters array on same index
                            heavyRow[positionRow + k]++;                                                               // incrementing the heavyRow array and also going to next rows
                            heavyCol[positionCol - l]++;                                                               // incrementing the heavyCol array and also going to prevoius columns
                            k++;
                            l++;
                        }
                    }
                }
 

                return true;
            }
            else
            {
                counter = 0;
            }
        }
    }

    return false;
}

bool topToBottomLEFTDiognalSearch(char **letters, char **usedLetters, char *word, int GridSize, int wordLength, double &timeSum, int *heavyRow, int *heavyCol)
{

    int counter = 0;
    int positionRow;
    int positionCol;

    int row;
    int column;

    auto startWord = chrono::high_resolution_clock::now();

    for (int i = 0; i < GridSize; i++)
    {
        for (int j = GridSize - 1; j >= 0; j--)
        {
            if (letters[i][j] == word[0]) // if letter is matched with the first letter of the word
            {
                counter = 1;

                row = i + 1;    // going to next row
                column = j - 1; // going to previous column

                for (int k = 1; k < wordLength; k++)
                {
                    // checking if next letter matches or not and also checking row doesnot exceeds gridsize and column must be greaater or equal to 0
                    if (row < GridSize && column >= 0 && letters[row][column] == word[k])
                    {
                        counter++; // if letter is matched then incrementing the counter
                        row++;     // also going to next row
                        column--;  // also going to previous column

                        if (counter == wordLength) // if counter is equal to the word length
                        {
                            positionRow = i; // recording the start positions of the word
                            positionCol = j;
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (counter == wordLength)
            {
                auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                int k = 0;
                int l = 0;

                for (int i = 0; i < GridSize; i++)
                {
                    for (int j = 0; j < GridSize; j++)
                    {
                        // if position is found
                        if (i == positionRow + k && j == positionCol - l && k < wordLength)
                        {
                            usedLetters[positionRow + k][positionCol - l] = letters[positionRow + k][positionCol - l]; // assigning letters to usedLetters array on same index
                            heavyRow[positionRow + k]++;                                                               // incrementing the heavyRow array and also going to next rows
                            heavyCol[positionCol - l]++;                                                               // incrementing the heavyCol array and also going to prevoius columns
                            k++;
                            l++;
                        }
                    }
                }



                return true;
            }
            else
            {
                counter = 0;
            }
        }
    }

    return false;
}

bool bottomToTopLEFTDiognalSearch(char **letters, char **usedLetters, char *word, int GridSize, int wordLength, double &timeSum, int *heavyRow, int *heavyCol)
{
    int counter = 0;

    auto startWord = chrono::high_resolution_clock::now();

    int row;
    int column;

    int positionRow;
    int positionCol;

    for (int i = GridSize - 1; i >= 0; i--)
    {
        for (int j = GridSize - 1; j >= 0; j--)
        {
            if (letters[i][j] == word[0]) // if letter is matched with the first letter of the word
            {
                counter = 1;

                row = i - 1;    // going to previous row
                column = j - 1; // going to previous column

                for (int k = 1; k < wordLength; k++)
                {
                    // checking if next letter matches or not and also checking row and column must be greaater or equal to 0
                    if (row >= 0 && column >= 0 && letters[row][column] == word[k])
                    {
                        counter++; // if letter is matched then incrementing the counter
                        row--;     // also going to previous row
                        column--;  // also going to previous column

                        if (counter == wordLength) // if counter is equal to the word length
                        {
                            positionRow = row + 1; // recording the starts position of the word
                            positionCol = column + 1;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (counter == wordLength)
            {
                auto endWord = chrono::high_resolution_clock::now(); // Stop measuring time

                int k = 0;
                int l = 0;

                for (int i = 0; i < GridSize; i++)
                {
                    for (int j = 0; j < GridSize; j++)
                    {
                        // if position is found
                        if (i == positionRow + k && j == positionCol + l && k < wordLength)
                        {
                            usedLetters[positionRow + k][positionCol + l] = letters[positionRow + k][positionCol + l]; // assigning letters to usedLetters array on same index
                            heavyCol[positionCol + l]++;                                                               // incrementing the heavyCol array and also going to next columns
                            heavyRow[positionRow + k]++;                                                               // incrementing the heavyRow array and also going to next rows
                            k++;
                            l++;
                        }
                    }
                }
                // printing time taken to find the word
                chrono::duration<double> elapsedTimeWord = chrono::duration_cast<chrono::duration<double>>(endWord - startWord);



                return true;
            }
            else
            {
                counter = 0;
            }
        }
    }

    return false;
}
