#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>

using std::string;
using std::cout;
using std::vector;

const vector<char> validCards = { 'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

enum HandRank {
	HighCard,
	Pair,
	TwoPair,
	ThreeOAK,
	Full,
	FourOAK,
	FiveOAK
};

std::map<char, int> countAll(string s) {
	std::map<char, int> rVal;
	for (size_t i = 0; i < s.length(); i++) {
		rVal[s[i]]++;
	}
	return rVal;
}

int countJokers(string s) {
	int rVal = 0;
	for (size_t i = 0; i < s.length(); i++) {
		if (s[i] == 'J') {
			rVal++;
		}
	}
	return rVal;
}

class Play {
public:
	Play(string, int);
	int bid;
	string hand;
	HandRank rank;
	int jokers;

private:
	HandRank calcHandRank();
	HandRank calcHandRankJokers();
};

Play::Play(string s, int b) {
	hand = s;
	bid = b;
	jokers = countJokers(s);
	if (jokers > 0) {
		rank = calcHandRankJokers();
	}
	else {
		rank = calcHandRank();
	}
	
}

bool operator<(Play const& p1, Play const& p2){
	if (p1.rank != p2.rank) {
		return p1.rank < p2.rank;
	}

	for (size_t i = 0; i < p1.hand.length(); i++){
		char card1 = p1.hand[i];
		char card2 = p2.hand[i];
		if (card1 == card2) {
			continue;
		}

		auto it = std::find(validCards.begin(), validCards.end(), card1);
		int index1 = std::distance(validCards.begin(), it);

		it = std::find(validCards.begin(), validCards.end(), card2);
		int index2 = std::distance(validCards.begin(), it);

		return index1 < index2;
	}
}

HandRank Play::calcHandRank() {
	std::map<char, int> count = countAll(hand);


	int numOnes = 0;
	int numTwos = 0;
	int numThrees = 0;
	for (std::map<char, int>::iterator it = count.begin(); it != count.end(); ++it) {
		if (it->second == 4) {
			return FourOAK;
		}
		else if (it->second == 5) {
			return FiveOAK;
		}

		if (it->second == 1) {
			numOnes++;
		}
		else if (it->second == 2) {
			numTwos++;
		}
		else if (it->second == 3) {
			numThrees++;
		}
	}

	if (numOnes == 5) {
		return HighCard;
	}
	else if (numTwos == 2) {
		return TwoPair;
	}
	else if (numTwos == 1 && numThrees == 1) {
		return Full;
	}
	else if (numTwos == 1) {
		return Pair;
	}
	else if (numThrees == 1 && numOnes == 2) {
		return ThreeOAK;
	}
	else {
		cout << "WTF are you doing here\n";
	}
}

HandRank Play::calcHandRankJokers() {
	if (jokers == 4 || jokers == 5) {
		return FiveOAK;
	}

	std::map<char, int> count = countAll(hand);

	int numOnes = 0;
	int numTwos = 0;
	int numThrees = 0;
	for (std::map<char, int>::iterator it = count.begin(); it != count.end(); ++it) {
		if (it->second == 4) {
			return FiveOAK;
		}

		if (it->second == 1) {
			numOnes++;
		}
		else if (it->second == 2) {
			numTwos++;
		}
		else if (it->second == 3) {
			numThrees++;
		}
	}

	if (jokers == 1) {
		if (numThrees == 1) { // 1 Jokers, 3 equal, 1 unique
			return FourOAK;
		}
		else if (numTwos == 2) { // 1 Jokers, 2 equal, 2 equal
			return Full;
		}
		else if (numTwos == 1) { // 1 Joker, 2 equal, 2 unique
			return ThreeOAK;
		}
		else { // 1 Joker, 4 equal
			return Pair;
		}
	}
	else if (jokers == 2) {
		if (numThrees == 1) { // 2 Jokers, 3 equal
			return FiveOAK;
		}
		else if (numTwos == 1) { // 2 Jokers, 3 unique
			return ThreeOAK; 
		}
		else if (numTwos == 2) { // 2 Jokers, 2 equal, 1 unique
			return FourOAK;
		}
	}
	else if (jokers == 3) {
		if (numTwos == 1) { // 3 Jokers, 2 equal
			return FiveOAK;
		}
		else { // 3 Jokers, 2 unique
			return FourOAK;
		}
	}
}

int main() {
	std::multiset<Play> plays;

	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open()) {
		cout << "Error opening file\n";
		exit(EXIT_FAILURE);
	}

	string line;
	while (getline(inputFile, line)) {
		string handText = line.substr(0, line.find(" "));
		int bid = stoi(line.substr(line.find(" ") + 1));

		Play tmp(handText, bid);
		plays.insert(tmp);
	}

	int factor = 1;
	int total = 0;
	for (std::multiset<Play>::iterator it = plays.begin(); it != plays.end(); it++) {
		total += it->bid * factor;
		factor++;
	}

	cout << total;

}