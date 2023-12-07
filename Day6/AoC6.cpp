#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#define uint unsigned int
#define ulong unsigned long
#define ullong unsigned long long

using std::string;
using std::cout;
using std::vector;

void getNumbersFromString(string s, vector<ullong> &v) {
    std::istringstream ss(s);
    ullong n;
    while (true) {
        if (ss >> n) {
            v.push_back(n);
        }
        else if (ss.eof()) { // End of file reached
            break;
        }
        else { // Clear the fail bit and ignore the non-numeric character
            ss.clear();
            ss.ignore();
        }
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

    vector<ullong> time;
    vector<ullong> distance;

    string line;
    std::getline(inputFile, line);
    getNumbersFromString(line, time);

    std::getline(inputFile, line);
    getNumbersFromString(line, distance);

    int numRaces = time.size();

    ullong mult = 1;
    for (size_t i = 0; i < numRaces; i++){
        ullong t = time[i];
        ullong record = distance[i];


        ullong ways = 0;
        for (size_t h = 1; h < t - 1; h++) {
            ullong reached = h * (t - h);
            if (reached > record) {
                ways++;
            }
        }

        mult *= ways;
    }

    cout << mult << "\n";
}