#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

struct Ray{
	char direction;
	int positionX;
	int positionY;
};

void print2D(vector<vector<char>> v) {
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = 0; j < v[i].size(); j++) {
			cout << v[i][j] << " ";
		}
		cout << "\n";
	}
}

int main(){
    std::ifstream inputFile("inputEx.txt");
	if (!inputFile.is_open()) {
		cout << "Error opening file";
		exit(EXIT_FAILURE);
	}

	vector<vector<char>> matrix;

	string line;
	while (getline(inputFile, line)) {
		vector<char> chars;
		for (char c : line){
			chars.push_back(c);
		}
		matrix.push_back(chars);
	}

	Ray initialRay = {'r', 0, 0};
	vector<Ray> rays;
	rays.push_back(initialRay);

	for(Ray r : rays){
		switch (r.direction){
			case 'r':
				positionX++;
				break;
			case 'l':
				positionX--;
				break;
			case 'u':
				positionY--;
				break;
			case 'd':
				positionY++;
				break;
		}

		//check what is in that spot
		//process whatever is in that spot
	}

	//print2D(matrix);
}