#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::cout;

const vector<char> PIPES = { '|', '-', 'L', 'J', '7', 'F' };

vector<vector<char>> readInput(std::ifstream& inputFile) {
	vector<vector<char>> inputMatrix;
	string line;
	while (getline(inputFile, line)) {
		vector<char> tmp;
		for (int i = 0; i < line.size(); i++) {
			tmp.push_back(line[i]);
		}
		inputMatrix.push_back(tmp);
	}

	inputFile.close();

	return inputMatrix;
}
std::pair<int, int> findStart(const vector<vector<char>>& m) {
	for (size_t i = 0; i < m.size(); i++) {
		for (size_t j = 0; j < m[i].size(); j++) {
			if (m[i][j] == 'S') {
				return { i, j };
			}
		}
	}

	cout << "Start not found\n";
	exit(EXIT_FAILURE);
}

char decodeStart(const vector<vector<char>>& m, std::pair<int, int> startIndex) {
	int row = startIndex.first;
	int col = startIndex.second;

	size_t r2 = row + 2 < m.size() ? row + 2 : row;
	size_t c2 = col + 2 < m[0].size() ? col + 2 : col;

	char one = '.';
	std::pair<int, int> oneIndex;
	char two = '.';
	std::pair<int, int> twoIndex;

	for (size_t r = row - 1 >= 0 ? row - 1 : row; r < r2; r++) {
		for (size_t c = col - 1 >= 0 ? col - 1 : col; c < c2; c++) {
			if (m[r][c] == '.' || m[r][c] == 'S') {
				continue;
			}

			if ((r == row - 1 && c == col - 1) || (r == row - 1 && c == col + 1) || (r == row + 1 && c == col - 1) || (r == row + 1 && c == col + 1)) {
				continue;
			}

			if ((r == row - 1 && c == col) && (m[r][c] == '-' || m[r][c] == 'J' || m[r][c] == 'L')) {
				continue;
			}

			if ((r == row + 1 && c == col) && (m[r][c] == '-' || m[r][c] == 'F' || m[r][c] == '7')) {
				continue;
			}

			if ((r == row && c == col - 1) && (m[r][c] == '|' || m[r][c] == 'J' || m[r][c] == '7')) {
				continue;
			}

			if ((r == row && c == col + 1) && (m[r][c] == '|' || m[r][c] == 'L' || m[r][c] == 'F')) {
				continue;
			}

			if (one == '.') {
				one = m[r][c];
				oneIndex = { r, c };
			}
			else {
				two = m[r][c];
				twoIndex = { r, c };
				break;
			}
		}
	}

	char returnVal = 'S';

	if (oneIndex.first == startIndex.first - 1 && twoIndex.second == startIndex.second - 1) { // Up, Left
		returnVal = 'J';
	}
	else if (oneIndex.first == startIndex.first - 1 && twoIndex.second == startIndex.second + 1) { // Up, Right
		returnVal = 'L';
	}
	else if (oneIndex.first == startIndex.first - 1 && twoIndex.second == startIndex.second) { // Up, Down
		returnVal = '|';
	}
	else if (oneIndex.second == startIndex.second - 1 && twoIndex.first == startIndex.first + 1) { //Left, Down
		returnVal = '7';
	}
	else if (oneIndex.second == startIndex.second - 1 && twoIndex.first == startIndex.first) { //Left, Right
		returnVal = '-';
	}
	else if (oneIndex.first == startIndex.first) { // Right, Down
		returnVal = 'F';
	}


	if (returnVal == 'S') {
		cout << "Error al decodificar start\n";
		cout << oneIndex.first << ", " << oneIndex.second << " | " << twoIndex.first << ", " << twoIndex.second << "\n";
		exit(EXIT_FAILURE);
	}

	return returnVal;
}


int main() {
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open()) {
		cout << "Error opening file";
		exit(EXIT_FAILURE);
	}

	vector<vector<char>> inputMatrix = readInput(inputFile);
	std::pair<int, int> startIndex = findStart(inputMatrix);

	char startChar = decodeStart(inputMatrix, startIndex);

	std::pair<int, int> prevPosition = startIndex;
	std::pair<int, int> currPosition;

	if (startChar == '-') {
		currPosition = { startIndex.first, startIndex.second + 1 }; // go right
	}
	else if (startChar == '|') {
		currPosition = { startIndex.first + 1, startIndex.second }; // go down
	}
	else if (startChar == 'L') {
		currPosition = { startIndex.first, startIndex.second + 1 }; // go right
	}
	else if (startChar == 'J') {
		currPosition = { startIndex.first, startIndex.second - 1 }; // go left
	}
	else if (startChar == '7') {
		currPosition = { startIndex.first + 1, startIndex.second }; // go down
	}
	else if (startChar == 'F') {
		currPosition = { startIndex.first + 1, startIndex.second }; // go down
	}

	vector<vector<int>> stepMatrix(inputMatrix.size(), vector<int>(inputMatrix[0].size(), 0));
	char currChar = inputMatrix[currPosition.first][currPosition.second];
	int steps = 1;
	stepMatrix[currPosition.first][currPosition.second] = steps;
	while (currChar != 'S') {
		//cout << currChar << "\n";
		std::pair<int, int> tmpPosition = currPosition;
		if (currChar == '-') {
			if (prevPosition.second < currPosition.second) {
				currPosition = { currPosition.first, currPosition.second + 1 };
			}
			else {
				currPosition = { currPosition.first, currPosition.second - 1 };
			}
		}
		else if (currChar == '|') {
			if (prevPosition.first < currPosition.first) {
				currPosition = { currPosition.first + 1, currPosition.second };
			}
			else {
				currPosition = { currPosition.first - 1, currPosition.second };
			}
		}
		else if (currChar == 'L') {
			if (prevPosition.first < currPosition.first) {
				currPosition = { currPosition.first, currPosition.second + 1 };
			}
			else {
				currPosition = { currPosition.first - 1, currPosition.second };
			}
		}
		else if (currChar == 'J') {
			if (prevPosition.first < currPosition.first) {
				currPosition = { currPosition.first, currPosition.second - 1 };
			}
			else {
				currPosition = { currPosition.first - 1, currPosition.second };
			}
		}
		else if (currChar == '7') {
			if (prevPosition.first > currPosition.first) {
				currPosition = { currPosition.first, currPosition.second - 1 };
			}
			else {
				currPosition = { currPosition.first + 1, currPosition.second };
			}
		}
		else if (currChar == 'F') {
			if (prevPosition.first > currPosition.first) {
				currPosition = { currPosition.first, currPosition.second + 1 };
			}
			else {
				currPosition = { currPosition.first + 1, currPosition.second };
			}
		}

		prevPosition = tmpPosition;
		currChar = inputMatrix[currPosition.first][currPosition.second];
		steps++;
		stepMatrix[currPosition.first][currPosition.second] = steps;
	}

	float far = stepMatrix[startIndex.first][startIndex.second] / 2;
	//stepMatrix[startIndex.first][startIndex.second] = 0;

	cout << far << "\n";


	//part2 from other guy, I didnt know how to do it, but Raycasting to check if it is inside is smart
	char next_char = 0;
	int check = 0;
	int count = 0;
	int line_len = inputMatrix.size();
	int char_len = inputMatrix[0].size();
	for (int i = 0; i < line_len; i++) {
		for (int j = 0; j < char_len; j++) {
			if (stepMatrix[i][j] == 0) {
				check = 0;
				for (int k = j + 1; k < char_len; k++) {

					next_char = inputMatrix[i][k];
					if ((next_char == '|' || next_char == 'L' || next_char == 'J') && (stepMatrix[i][k] != 0)) {
						check++;
					}
				}
				if (check % 2) {
					count++;
				}
			}
		}
	}

	cout << count;
}