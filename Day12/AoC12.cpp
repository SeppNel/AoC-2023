#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#define uint unsigned int

using std::cout;
using std::string;
using std::vector;

std::unordered_map<string, string> memo;


template<typename T>
bool inVector(T needle, const vector<T>& haystack) {
	return std::find(haystack.begin(), haystack.end(), needle) != haystack.end();
}

vector<int> countGroups(const string& l) {
	vector<int> count;
	int inrow = 0;
	for (size_t i = 0; i < l.size(); i++) {
		if (l[i] == '#') {
			inrow++;
		}
		else if (inrow > 0) {
			count.push_back(inrow);
			inrow = 0;
		}

		if (i == l.size() - 1 && l[i] == '#') {
			count.push_back(inrow);
		}
	}

	return count;
}

void generateCombinations(std::string& str, const vector<int>& pos, int index, const vector<int>& correctCount, int& correctCombos) {
	if (index >= str.size()) {
		if (countGroups(str) == correctCount) {
			correctCombos++;
		}
		return;
	}

	while (std::find(pos.begin(), pos.end(), index) == pos.end()) {
		index++;
		if (index == str.size()) {
			if (countGroups(str) == correctCount) {
				correctCombos++;
			}
			return;
		}
	}

	// Replace '?' with '.' and recurse
	str[index] = '.';
	generateCombinations(str, pos, index + 1, correctCount, correctCombos);

	// Replace '?' with '#' and recurse
	str[index] = '#';
	generateCombinations(str, pos, index + 1, correctCount, correctCombos);

	// Restore the original character at this position
	str[index] = '?';
}

int handleLine(string l, const vector<int>& correctCount) {
	int unk = std::count(l.begin(), l.end(), '?');
	
	string line = l;
	vector<int> unkpos(unk);

	for (size_t i = 0; i < unk; i++) {
		int pos = line.find('?');
		unkpos[i] = pos;
		line[pos] = '.';
	}

	int correctCombos = 0;
	generateCombinations(l, unkpos, 0, correctCount, correctCombos);

	return correctCombos;
}


int main() {
	std::ifstream inputFile("inputEx.txt");
	if (!inputFile.is_open()) {
		cout << "Error opening file";
		exit(EXIT_FAILURE);
	}

	int sum = 0;
	string line;
	while (getline(inputFile, line)) {
		string springLine = line.substr(0, line.find(" "));
		string crcLine = line.substr(line.find(" ") + 1);

		vector<int> correctCombo;
		while (crcLine.find(',') != crcLine.npos) {
			correctCombo.push_back(stoi(crcLine.substr(0, crcLine.find(','))));
			crcLine = crcLine.substr(crcLine.find(',') + 1);
		}
		correctCombo.push_back(stoi(crcLine));
		
		int c = handleLine(springLine, correctCombo);
		sum += c;

		cout << "Combos: " << c << "\n";
	}
	cout << sum << "\n";
}