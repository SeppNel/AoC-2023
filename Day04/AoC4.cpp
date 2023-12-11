#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::vector;
using std::string;
using std::cout;

class Card
{
public:
    int id;
    vector<int> winNumbers;
    vector<int> myNumbers;

};

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file\n";
        exit(EXIT_FAILURE);
    }

    vector<Card> cards;

    string line;
    int cardId = 1;
    while (getline(inputFile, line)) {
        Card card;

        //string idText = line.substr(0, line.find(":"));
        //card.id = stoi(idText.substr(idText.find(" ") + 1));
        card.id = cardId;

        string winText = line.substr(line.find(":") + 2, line.find("|") - line.find(":") - 3);

        while (winText.find(" ") != line.npos) {
            if (winText[0] == ' ') {
                winText.erase(0, 1);
            }
            string sub = winText.substr(0, winText.find(" "));
            card.winNumbers.push_back(stoi(sub));
            winText = winText.substr(winText.find(" ") + 1);
        }

        string sub = winText.substr(0, winText.find(" "));
        card.winNumbers.push_back(stoi(sub));


        string myText = line.substr(line.find("|") + 2);

        while (myText.find(" ") != line.npos) {
            string sub = myText.substr(0, myText.find(" "));
            if (sub != "") {
                card.myNumbers.push_back(stoi(sub));
            }
            
            myText = myText.substr(myText.find(" ") + 1);
            if (myText[0] == ' ') {
                myText.erase(0, 1);
            }
        }

        sub = myText.substr(0, myText.find(" "));
        card.myNumbers.push_back(stoi(sub));

        cards.push_back(card);
        cardId++;
    }

    int totalPoints = 0;

    for (auto card : cards) {
        int points = 0;
        for (int num : card.myNumbers) {
            if (std::find(card.winNumbers.begin(), card.winNumbers.end(), num) != card.winNumbers.end()) {
                //cout << "Found " << num << " in card " << card.id << "\n";
                if (points == 0) {
                    points++;
                }
                else {
                    points *= 2;
                }
            }
        }
        cout << "Points for card " << card.id << ": " << points << "\n";
        totalPoints += points;
    }

    cout << totalPoints << "\n";

    int lastId = cards.back().id;

    for (size_t c = 0; c < cards.size(); c++) {
        Card card = cards[c];
        int win = 0;
        for (int num : card.myNumbers) {
            if (std::find(card.winNumbers.begin(), card.winNumbers.end(), num) != card.winNumbers.end()) {
                win++;
            }
        }

        for (size_t i = 0; i < win; i++) {
            int cardToCopy = card.id + i;
            if (cardToCopy <= lastId) {
                cards.push_back(cards[cardToCopy]);
            }
        }
    }

    cout << cards.size() << "\n";

    inputFile.close();
}
