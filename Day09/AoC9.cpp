#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;
using std::cout;

void getNumbersFromString(string s, vector<int>& v) {
	std::istringstream ss(s);
	int n;
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

int main() {
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open()) {
		cout << "Error opening file";
		exit(EXIT_FAILURE);
	}

	int sum = 0;
	string line;
	while (getline(inputFile, line)) {
		vector<int> nums;
		getNumbersFromString(line, nums);

		std::reverse(nums.begin(), nums.end()); // for Part 2

		vector<vector<int>> seq;

		vector<int> curr = nums;
		bool allZero = false;
		while (!allZero) {
			allZero = true;
			vector<int> v;
			for (size_t i = 0; i < curr.size() - 1; i++) {
				int diff = curr[i + 1] - curr[i];
				v.push_back(diff);
				if (diff != 0) {
					allZero = false;
				}
			}
			curr = v;
			seq.push_back(v);
		}

		for (auto n : nums) {
			cout << n << " ";
		}
		cout << "\n";

		for (auto v : seq) {
			for (auto n : v) {
				cout << n << " ";
			}
			cout << "\n";
		}



		int lastVal = 0;
		for (int index = seq.size() - 1; index >= 0; index--) {
			int n = lastVal + seq[index].back();
			seq[index].push_back(n);
			lastVal = n;
		}

		int n = lastVal + nums.back();
		nums.push_back(n);

		sum += n;

		cout << n << "\n";
	}

	cout << sum;
}