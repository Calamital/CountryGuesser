#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>

std::string CAPITAL;
std::string LANGUAGE;
std::string NAME;
std::string RELIGION;
std::string POPULATION;

std::vector<std::string> capitals = {};
std::vector<std::string> languages = {};
std::vector<std::string> names = {};
std::vector<std::string> religions = {};
std::vector<std::string> populations = {};

std::ifstream CAPITALS("country-data/capitals.json");
std::ifstream LANGUAGES("country-data/languages.json");
std::ifstream NAMES("country-data/names.json");
std::ifstream RELIGIONS("country-data/religions.json");
std::ifstream POPULATIONS("country-data/populations.json");

std::string getcountry(int index) { return names[2 + (index * 3)].substr(20, (names[2 + (index * 3)]).size() - 21); }
std::string getcapital(std::string country) 
{ 
    for (int capitalindex = 0; capitalindex < capitals.size(); ++capitalindex) 
    {
        if (capitals[capitalindex].size() < 20) { continue; } 
        if (capitals[capitalindex].substr(20, capitals[capitalindex].size() - 22) == country) { return capitals[capitalindex + 1].substr(17, capitals[capitalindex + 1].size() - 18); }
    }
    return "";
}
std::string getlanguages(std::string country) 
{ 
    for (int languageindex = 0; languageindex < languages.size(); ++languageindex)
    {
        if (languages[languageindex].size() < 20) { continue; }
        if (languages[languageindex].substr(20, languages[languageindex].size() - 22) == country)
        {
            std::string foundlanguages;
            while (languages[languageindex + 2].size() > 12) 
            { 
                int depletion;
                if (languages[languageindex + 2].substr(languages[languageindex + 2].size() - 1, 1) == ",") { depletion = 15; } else { depletion = 14; }
                foundlanguages += languages[languageindex + 2].substr(13, languages[languageindex + 2].size() - depletion) + ", ";
                ++languageindex;
            }
            return foundlanguages.substr(0, foundlanguages.size() - 2);
        }
    }
    return "";
}
std::string getreligion(std::string country) 
{ 
    for (int religionindex = 0; religionindex < religions.size(); ++religionindex) 
    {
        if (religions[religionindex].size() < 20) { continue; } 
        if (religions[religionindex].substr(20, religions[religionindex].size() - 22) == country) 
        {
            if (religions[religionindex + 1].substr(21, religions[religionindex + 1].size() - 22) == "ul") { return "null"; }
            return religions[religionindex + 1].substr(21, religions[religionindex + 1].size() - 22); 
        }
    }
    return "";
}
std::string getpopulation(std::string country)
{
    for (int populationindex = 0; populationindex < populations.size(); ++populationindex) 
    {
        if (populations[populationindex].size() < 20) { continue; } 
        if (populations[populationindex].substr(20, populations[populationindex].size() - 22) == country) { return populations[populationindex + 1].substr(22, populations[populationindex + 1].size() - 22); }
    }
    return "";
}

void initiate()
{
    while (std::getline(CAPITALS, CAPITAL)) { capitals.push_back(CAPITAL); }
    while (std::getline(LANGUAGES, LANGUAGE)) { languages.push_back(LANGUAGE); }
    while (std::getline(NAMES, NAME)) { names.push_back(NAME); }
    while (std::getline(RELIGIONS, RELIGION)) { religions.push_back(RELIGION); }
    while (std::getline(POPULATIONS, POPULATION)) { populations.push_back(POPULATION); }
}
int main()
{
    std::string input;
    initiate();
    srand(time(NULL));

    std::cout << "Say anything to begin! \n:: ";
    std::cin >> input;
    while (true)
    {
        std::string rngcountry = getcountry(rand() % (names.size() / 3));
        std::string correct = "";
        std::string given = "";
        std::cout << "\nThis country has a population of " + getpopulation(rngcountry) + ".";
        std::cout << "\nThis country mainly practices " + getreligion(rngcountry) + ".";
        std::cout << "\nThis country primarly speaks { " + getlanguages(rngcountry) + " }.";
        std::cout << "\nThis country's capital is " + getcapital(rngcountry) + ".";
        std::cout << "\n\nWhat country has been selected? \n:: ";
        std::cin >> input;
        for (auto letter: input) { given += tolower(letter); }
        for (auto letter: rngcountry) { correct += tolower(letter); }
        if (correct == given) { std::cout << "Correct! Congratulations! Moving on...\n"; }
        else { std::cout << "Incorrect. The country was " + rngcountry + ". Moving on...\n"; }
    }
    return 0;
}