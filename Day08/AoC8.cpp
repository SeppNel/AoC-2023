#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <numeric>

#define ullong unsigned long long

using std::cout;
using std::string;
using std::vector;

int main() {
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open()) {
		cout << "Error opening file\n";
		exit(EXIT_FAILURE);
	}

	string directions;
	getline(inputFile, directions);

	string line;
	getline(inputFile, line);

	std::map<string, std::pair<string, string>> nodes;

	while (getline(inputFile, line)) {
		string node = line.substr(0, 3);
		string dir1 = line.substr(line.find("(") + 1, 3);
		string dir2 = line.substr(line.find(",") + 2, 3);

		nodes.insert({ node, { dir1, dir2 } });
	}

	vector<string> startingNodes;
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (i->first[2] == 'A') {
			startingNodes.push_back(i->first);
		}
	}

	vector<ullong> steps4each;
	for (string node : startingNodes) {
		ullong steps = 0;
		int dirIndex = 0;
		while (node[2] != 'Z') {
			char direction = directions[dirIndex];
			if (direction == 'L') {
				node = nodes[node].first;
			}
			else {
				node = nodes[node].second;
			}

			if (dirIndex + 1 == directions.size()) {
				dirIndex = 0;
			}
			else {
				dirIndex++;
			}
			steps++;
		}
		steps4each.push_back(steps);
	}

	ullong lcm = steps4each[0];
	for (size_t i = 1; i < steps4each.size(); i++) {
		lcm = std::lcm(lcm, steps4each[i]);
	}
	
	cout << lcm << "\n";
}