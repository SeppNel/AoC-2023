#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>



using std::vector;
using std::string;
using std::cout;

const std::set<char> SPECIAL_CHARS = { '*', '#', '$', '+', '&', '%', '/', '@', '=', '-' };
const char GEAR = '*';

std::map<int, vector<int>> gearMap;

class Gear
{
public:
    Gear(int, int);
    int number1;
    int number2;
};

Gear::Gear(int o, int t) {
    number1 = o;
    number2 = t;
}

int main(){
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file\n";
        exit(EXIT_FAILURE);
    }

    vector<vector<char>> inputMatrix;

    string line;
    while (getline(inputFile, line)) {
        vector<char> tmp;
        for (size_t i = 0; i < line.size(); i++){
            tmp.push_back(line[i]);
        }
        inputMatrix.push_back(tmp);
    }

    int totalSum = 0;
    
    for (size_t row = 0; row < inputMatrix.size(); row++){
        for (size_t col = 0; col < inputMatrix[row].size(); col++) {
            if (!isdigit(inputMatrix[row][col])) {
                continue;
            }
            
            string number(1, inputMatrix[row][col]);
            int firstIndex = col;
            col++;
            
            while (col < inputMatrix[row].size() && isdigit(inputMatrix[row][col])) {
                number.push_back(inputMatrix[row][col]);
                col++;
            }

            int lastIndex = col - 1;

            bool valid = false;
            //cout << "Number: " << number << "\n";
            for (size_t r = row > 0 ? row - 1 : 0; r < inputMatrix.size() && r < row + 2; r++) {
                for (size_t i = firstIndex > 0 ? firstIndex - 1 : 0; i < inputMatrix[r].size() && i < lastIndex + 2; i++) {
                    //cout << "Checking position: " << r << ", " << i << "\n";

                    if (inputMatrix[r][i] == GEAR) {
                        int uniqueIndex = r * inputMatrix[r].size() + i;
                        if (gearMap.contains(uniqueIndex)) {
                            gearMap[uniqueIndex].push_back(stoi(number));
                        }
                        else {
                            vector<int> tmp;
                            tmp.push_back(stoi(number));

                            gearMap.insert(std::pair<int, vector<int>>(uniqueIndex, tmp));
                        }
                    }

                    if (SPECIAL_CHARS.find(inputMatrix[r][i]) != SPECIAL_CHARS.end()) {
                        valid = true;
                    }
                }
            }

            if (valid) {
                //cout << "Valid number: " << number << "\n";
                totalSum += stoi(number);
            }
        }
    }

    int gearRatio = 0;

    for (auto gear : gearMap) {
        if (gear.second.size() == 2) {
            gearRatio += gear.second[0] * gear.second[1];
        }
    }


    cout << totalSum << "\n";
    cout << gearRatio << "\n";


}
