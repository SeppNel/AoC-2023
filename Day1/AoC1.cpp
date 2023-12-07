#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

void prepass() {
    vector<string> textNumbers = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    vector<string> numbers = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    std::fstream inputFile;
    inputFile.open("input.txt", std::ios::in);
    if (!inputFile.is_open()) {
        cout << "Error opening file";
        exit(EXIT_FAILURE);
    }

    std::ofstream outputFile("inputPrepass.txt");
    if (!outputFile.is_open()) {
        cout << "Error opening file";
        exit(EXIT_FAILURE);
    }

    string line;
    while (std::getline(inputFile, line)) {

        for (size_t i = 0; i < textNumbers.size(); i++) {
            string text = textNumbers[i];
            size_t pos = line.find(text);
            if (pos != string::npos) {
                line.replace(pos + 1, text.length() - 2, numbers[i]);
                i--;
            }
        }

        outputFile << line + "\n";
    }
    inputFile.close();
    outputFile.close();
}

int main()
{
    prepass();

    std::fstream inputFile;
    inputFile.open("inputPrepass.txt", std::ios::in);
    if (!inputFile.is_open()) {
        cout << "Error opening file";
        exit(EXIT_FAILURE);
    }

    int totalSum = 0;
    string line;
    while (std::getline(inputFile, line)) {
        cout << line << "\n";

        string first;
        for (size_t i = 0; i < line.size(); i++)
        {
            if (std::isdigit(line[i])) {
                first = string(1, line[i]);
                break;
            }
        }

        string last;
        for (int i = line.size() - 1; i >= 0; i--)
        {
            if (std::isdigit(line[i])) {
                last = string(1, line[i]);
                break;
            }
        }

        int number = stoi(first + last);
        totalSum += number;
    }
    inputFile.close();

    cout << totalSum << "\n";
}