#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::cout;
using std::string;
using std::vector;

const int MAX_R = 12;
const int MAX_G = 13;
const int MAX_B = 14;

class Set
{
public:
    int red = 0;
    int green = 0;
    int blue = 0;

    bool posible = true;
};


class Game{
public:
    Game(int);
    bool posible();
    int maxRed();
    int maxGreen();
    int maxBlue();
    int Power();

    vector<Set> sets;
    int id;

};

Game::Game(int i) {
    id = i;
}

bool Game::posible() {
    bool ret = true;
    for (auto set : sets) {
        if (!(set.posible)) {
            ret = false;
            break;
        }
    }

    return ret;
}

int Game::maxRed() {
    int max = 0;
    for (auto set : sets) {
        if (set.red > max) {
            max = set.red;
        }
    }

    return max;
}

int Game::maxGreen() {
    int max = 0;
    for (auto set : sets) {
        if (set.green > max) {
            max = set.green;
        }
    }

    return max;
}

int Game::maxBlue() {
    int max = 0;
    for (auto set : sets) {
        if (set.blue > max) {
            max = set.blue;
        }
    }

    return max;
}

int Game::Power() {
    return maxRed() * maxGreen() * maxBlue();
}


void setValuesSet(string setText, Set& set) {
    int num = stoi(setText);

    string comColor = setText.substr(setText.find(" ") + 1);

    if (comColor == "red") {
        set.red = num;
    }
    else if (comColor == "green") {
        set.green = num;
    }
    else {
        set.blue = num;
    }
}

int main()
{
    std::fstream inputFile;
    inputFile.open("input.txt", std::ios::in);
    if (!inputFile.is_open()) {
        cout << "Error opening file";
        exit(EXIT_FAILURE);
    }

    vector<Game> games;

    string line;
    while (std::getline(inputFile, line)) {
        cout << line << "\n";

        string first;
        string str1 = line.substr(0, line.find(":"));
        str1 = str1.substr(str1.find(" "));
        int id = stoi(str1);

        Game game(id);

        string dataString = line.substr(line.find(":") + 2);

        size_t setPos = dataString.find(";");
        while (setPos != string::npos) {
            Set set;
            string setText = dataString.substr(0, setPos);

            size_t comPos = setText.find(",");
            while (comPos != string::npos) {
                string com = setText.substr(0, comPos);

                setValuesSet(com, set);

                setText = setText.substr(comPos + 2);
                comPos = setText.find(",");
            }

            setValuesSet(setText, set);

            game.sets.push_back(set);

            dataString = dataString.substr(setPos + 2);
            setPos = dataString.find(";");
        }

        Set set;
        size_t comPos = dataString.find(",");
        while (comPos != string::npos) {
            string com = dataString.substr(0, comPos);

            setValuesSet(com, set);

            dataString = dataString.substr(comPos + 2);
            comPos = dataString.find(",");
        }

        setValuesSet(dataString, set);

        game.sets.push_back(set);

        games.push_back(game);
    }

    inputFile.close();

    for (auto& game : games) {
        for (auto& set : game.sets) {
            if (set.red > MAX_R || set.green > MAX_G || set.blue > MAX_B) {
                set.posible = false;
            }
        }
    }

    int sum = 0;
    for (auto game : games) {
        if (game.posible()) {
            sum += game.id;
        }
    }

    cout << "Suma: " << sum << "\n";


    int sumPower = 0;
    for (auto game : games) {
        sumPower += game.Power();
    }

    cout << "Power: " << sumPower << "\n";
}