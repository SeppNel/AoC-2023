#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define ont unsigned __int8

using std::cout;
using std::string;
using std::vector;

struct Box {
	vector<std::pair<string, int>> contents;

	vector<std::pair<string, int>>::iterator findLabelPos(string label) {
		contents.begin();
		
		for (auto i = contents.begin(); i != contents.end(); i++) {
			if (i->first == label) {
				return i;
			}
		}
	}
};

ont hash(const string s) {
	ont val = 0;
	for (size_t i = 0; i < s.length(); i++) {
		val += s[i];
		val *= 17;
	}
	return val;
}

vector<string> split(string l) {
	vector<string> s;
	while (l.find(",") != l.npos) {
		s.push_back(l.substr(0, l.find(",")));
		l = l.substr(l.find(",") + 1);
	}
	s.push_back(l);
	
	return s;
}

string getLabel(const string s) {
	string label;
	if (s.find("-") != s.npos) {
		label = s.substr(0, s.find("-"));
	}
	else {
		label = s.substr(0, s.find("="));
	}

	return label;
}

int main() {
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open()) {
		cout << "Error opening file";
		exit(EXIT_FAILURE);
	}

	string line;
	getline(inputFile, line);
	vector<string> steps = split(line);
	
	vector<Box> boxes(256);
	for (auto step : steps) {
		string label = getLabel(step);
		ont h = hash(label);
		vector<std::pair<string, int>>::iterator labelPos = boxes[h].findLabelPos(label);

		if (step.find("-") != step.npos) {
			if (labelPos != boxes[h].contents.end()) {
				boxes[h].contents.erase(labelPos);
			}
		}
		else {
			int num = stoi(step.substr(step.find("=") + 1));
			if (labelPos != boxes[h].contents.end()) {
				labelPos->second = num;
			}
			else {
				boxes[h].contents.push_back({ label, num });
			}
		}
	}

	int sum = 0;

	for (size_t i = 0; i < boxes.size(); i++) {
		Box box = boxes[i];
		for (size_t j = 0; j < box.contents.size(); j++) {
			int focalLen = box.contents[j].second;
			sum += (i + 1) * (j + 1) * focalLen;
		}
	}

	cout << "Total: " << sum << "\n";
}