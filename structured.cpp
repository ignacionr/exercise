#include <iostream>
#include <cstdlib>
#include <ctime>

// structured theme programming
// breaking down big problems into smaller ones

// I wish there was an easier way to generate random numbers in a range
// min and max are passed by value (the function operates on copies!)
int generateRandomInt(int min, int max)
{
    std::srand(std::time(nullptr));
    return min + int(((long)std::rand() * max) / RAND_MAX);
}

// Language is our base class
class Language
{
public:
    // polymorphic method
    virtual void print(std::string const &message) = 0;
};

class Formal : public Language
{
    void print(std::string const &message) override
    {
        std::cout << message << std::endl;
    }
};

class Reversing : public Language
{
    void print(std::string const &message) override
    {
        std::string reversed(message.rbegin(), message.rend());
        std::cout
            << reversed << std::endl;
    }
};

class Red : public Language
{
    void print(std::string const &message) override
    {
        for (auto c : message)
        {
            std::cout << c;
            if (c == ' ')
            {
                std::cout << " red ";
            }
        }
        std::cout << std::endl;
    }
};

// function declaration:
// <return type> <name> (<parameter list>)
// attempts is passed by reference (so side effects are gotten!)
int promptTheUserForANumberAndSpendOneAttempt(int &attempts, Language *pLanguage)
{
    pLanguage->print("You have " + std::to_string(attempts) + " attempts to guess it!");
    pLanguage->print("what is that number?");
    int userGuess;
    std::cin >> userGuess;
    attempts--;
    return userGuess;
}

int main()
{
    Red language;
    Language *pLanguage = &language;
    auto myNumber = generateRandomInt(1, 10);
    pLanguage->print("The computer has picked a number between 1 and 10");

    bool found{false};
    for (int attempts{3}; attempts > 0 && !found;)
    {
        auto userGuess{promptTheUserForANumberAndSpendOneAttempt(attempts, pLanguage)};
        if (myNumber == userGuess) // branching structure (if)
        {
            pLanguage->print("YES! my number was " + std::to_string(myNumber));
            found = true;
        }
        else if (myNumber < userGuess)
        {
            pLanguage->print("No. My number is lower.");
        }
        else
        {
            pLanguage->print("No. My number is greater than that.");
        }
    }
    pLanguage->print("Game over!");
    return 0;
}