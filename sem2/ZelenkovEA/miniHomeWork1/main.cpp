#include <iostream>
#include <vector>

using namespace std;
int main() {

    vector<string>text;
    text.push_back("Hello, how are you?");
    text.push_back("Today is a beautiful day!");
    text.push_back("I love programming.");
    text.push_back("Cats and dogs are wonderful pets.");
    text.push_back("Time flies when you're having fun.");
    text.push_back("Reading books is a great way to spend time.");
    text.push_back("Breakfast is the most important meal of the day.");
    text.push_back("Today I plan to do some sports.");
    text.push_back("Traveling is the best way to relax and gain new experience.");
    text.push_back("Music helps me relax and concentrate.");
    text.push_back("Working in a team can be very productive.");
    text.push_back("Sometimes it's better to just relax and not think about anything.");
    text.push_back("Learning always opens up new horizons.");
    text.push_back("A smile is the best thing you can wear.");
    text.push_back("Life is beautiful when you have goals and dreams.");
    char simbol = 'L';
    auto firstSimbolCounter = [&](const string& str) {
        return count_if(str.begin(), str.end(), [&](char c) {
            return c == simbol;
        });
    };

    int simbolCounter = 0;
    for (const auto& str : text) {
        simbolCounter += firstSimbolCounter(str);
    }
    cout << "В векторе содержится " << simbolCounter << " символа "<< simbol<< " вначале строк"<<endl;
    return 0;
}
