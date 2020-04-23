// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();
    if (bGameOver)
    {
        SetupGame();
        return;
    }
    ProcessGuess(Input);
}

void UBullCowCartridge::SetupGame()
{
    bGameOver = false;
    if (GuessedWords.Num() == Words.Num())
    {
        PrintLine(TEXT("GAME OVER"));
        return;
    }

    do
    {
        WordToGuess = *Words[FMath::RandRange(0, Words.Num() - 1)];
    } while (HasBeenGuessed(WordToGuess));

    Lives = WordToGuess.Len();

    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(
        TEXT("Guess the %i %s"), WordToGuess.Len(), TEXT("letters hidden word!"));
    PrintLine(TEXT("You have %i chances, type your guess \nand press enter to continue..."), Lives);
}

void UBullCowCartridge::EndGame()
{
    PrintLine(TEXT("The hidden word was %s"), *WordToGuess);
    PrintLine(TEXT("Press Enter to try again with a different word"));
    bGameOver = true;
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    if (WordToGuess.Equals(Guess))
    {
        PrintLine(TEXT("You guessed the hidden word!"));
        GuessedWords.Add(WordToGuess);
        EndGame();
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("You should type a word without \nrepeating letters, try again!"));
        return;
    }

    Lives--;
    if (Lives <= 0)
    {
        PrintLine(TEXT("You ran out of chances to guess...\n"));
        EndGame();
        return;
    }

    if (WordToGuess.Len() != Guess.Len())
    {
        PrintLine(TEXT("Ups, wrong length, remember that the word \n to guess is %i characters long"), WordToGuess.Len());
    }
    else
    {
        PrintLine(TEXT("The guess was not correct"));
    }

    FBullCowCount Count = GetBullCows(Guess);

    PrintLine(TEXT("You have %i bulls, and  %i cows"), Count.Bulls, Count.Cows);
    PrintLine(TEXT("You have %i chances, type another guess \nand press enter to continue..."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
{
    char ActualChar;
    for (int32 CharIndex = 0; CharIndex < Word.Len(); CharIndex++)
    {
        ActualChar = Word[CharIndex];
        for (int32 ComparisonIndex = CharIndex + 1; ComparisonIndex < Word.Len(); ComparisonIndex++)
        {
            if (ActualChar == Word[ComparisonIndex])
            {
                return false;
            }
        }
    }

    return true;
}

bool UBullCowCartridge::HasBeenGuessed(const FString &Word)
{
    return GuessedWords.Find(Word) != INDEX_NONE;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString &Guess) const
{
    FBullCowCount Count;
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == WordToGuess[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < Guess.Len(); HiddenIndex++)
        {
            if (Guess[HiddenIndex] == WordToGuess[GuessIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }

    return Count;
}