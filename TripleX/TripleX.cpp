#include <iostream>
#include <ctime>

void PrintTitle()
{
    std::cout << "  _____             _      _ __     _            __  __  \n";
    std::cout << " |_   _|    _ _    (_)    | '_ \\   | |     ___   \\ \\/ /  \n";
    std::cout << "   | |     | '_|   | |    | .__/   | |    / -_)   >  <   \n";
    std::cout << "  _|_|_   _|_|_   _|_|_   |_|__   _|_|_   \\___|  /_/\\_\\  \n";
    std::cout << "_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| \n";
    std::cout << "\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\n\n";
}

void PrintLevelIntroduction(int Difficulty)
{
    std::cout << "You are a secret agent breaking into a " << Difficulty << " level secure server room...\n";
    std::cout << "You need to enter the correct code to continue...\n\n";
}

bool PlayGame(int Difficulty)
{
    PrintLevelIntroduction(Difficulty);

    // Declare 3 constant random numbers
    const int CodeA = rand() % Difficulty + Difficulty;
    const int CodeB = rand() % Difficulty + Difficulty;
    const int CodeC = rand() % Difficulty + Difficulty;

    // Calculates the CodeSum and CodeProduct of the previous generated random numbers
    const int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProduct = CodeA * CodeB * CodeC;

    // Prints CodeSum and CodeProduct
    std::cout << "Hints:\n";
    std::cout << "+ There are 3 numbers in the code\n";
    std::cout << "+ The code add-up to: " << CodeSum << std::endl;
    std::cout << "+ The codes multiply to give: " << CodeProduct << std::endl;

    // Stores player guess
    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;
    std::cout << "You entered: " << GuessA << GuessB << GuessC << "..." std::endl;
    std::cout << "........................\n";

    // Checks if player guess is correct
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;
    if (GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        std::cout << "Well done! You have guessed the right code, keep it going!\n";
        return true;
    }

    std::cout << "Ups! You have entered a wrong combination and now you you'll die...\n";
    return false;
}

int main()
{
    srand(time(NULL)); // Seeds random generator to have a sequence based on time of day
    PrintTitle();

    bool bLevelComplete = true;
    int LevelDifficulty = 1;
    const int MaxLevelDifficulty = 10;
    while (bLevelComplete && LevelDifficulty <= MaxLevelDifficulty)
    {
        bLevelComplete = PlayGame(LevelDifficulty);

        // Clears any errors and discards buffer
        std::cin.clear();
        std::cin.ignore();

        LevelDifficulty++;
    }

    if (bLevelComplete)
    {
        std::cout << "\n Great work!! You got all the files! Now get out of there! .......";
    }

    return 0;
}