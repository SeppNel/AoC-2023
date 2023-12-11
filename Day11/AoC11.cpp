#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <span>

#define ullong unsigned long long
#define llong long long

using std::string;
using std::vector;
using std::cout;

const int EXPAND_FACTOR = 1000000 - 1;

struct Galaxy
{
	llong x;
	llong y;
	int id;
};

llong manhatanDistance(const Galaxy a, const Galaxy b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void print2D(vector<vector<char>> v) {
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = 0; j < v[i].size(); j++) {
			cout << v[i][j] << " ";
		}
		cout << "\n";
	}
}

ullong offsetOfRow(int row, vector<vector<char>>& image) {
	ullong offset = 0;
	for (size_t it = 0; it < row; ++it) {
		if (find(image[it].begin(), image[it].end(), '#') != image[it].end()) {
			continue;
		}

		offset += EXPAND_FACTOR;
	}

	return offset;
}

ullong offsetOfCol(int col, vector<vector<char>>& image) {
	ullong offset = 0;
	for (size_t c = 0; c < col; ++c) {
		bool hashtag = false;
		for (auto row : image) {
			if (row[c] == '#') {
				hashtag = true;
				break;
			}
		}

		if (!hashtag) {
			offset += EXPAND_FACTOR;
		}
	}

	return offset;
}

int main() {
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open()) {
		cout << "Error opening file\n";
		exit(EXIT_FAILURE);
	}

	vector<vector<char>> image;
	string line;
	while (getline(inputFile, line)) {
		vector<char> tmp;
		for (size_t i = 0; i < line.size(); i++) {
			tmp.push_back(line[i]);
		}

		image.push_back(tmp);
	}
	inputFile.close();

	//print2D(image);

	vector<Galaxy> galaxis;
	for (size_t i = 0; i < image.size(); i++) {
		for (size_t j = 0; j < image[i].size(); j++) {
			if (image[i][j] == '#') {
				Galaxy tmp = { i + offsetOfRow(i, image), j + offsetOfCol(j, image), galaxis.size() + 1 };
				galaxis.push_back(tmp);
			}
		}
	}

	llong sum = 0;
	for (auto& g : galaxis) {
		for (auto& g2 : galaxis) {
			if (g.id >= g2.id) {
				continue;
			}

			llong md = manhatanDistance(g, g2);
			sum += md;
		}
	}
	cout << "Sum: " << sum;

}
