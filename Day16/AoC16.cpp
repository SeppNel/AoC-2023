#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

using std::cout;
using std::string;
using std::vector;
using std::unordered_set;

struct VisitedSpot{
	char direction;
	uint8_t positionX;
	uint8_t positionY;
	
	VisitedSpot(char d, uint8_t x, uint8_t y){
	    direction = d;
	    positionX = x;
	    positionY = y;
	}

	void print(){
		cout << "Direction: " << direction << ", X: " << positionX << ", Y: " << positionY;
	}
};

namespace std {
    template<>
    struct hash<VisitedSpot> {
        inline size_t operator()(const VisitedSpot& x) const {
            return std::hash<std::string>()(std::to_string(x.direction) + std::to_string(x.positionX) + std::to_string(x.positionY));
        }
    };

	template <>
	struct equal_to<VisitedSpot> {
		inline bool operator()(const VisitedSpot& a, const VisitedSpot& b) const {
			return a.direction == b.direction && a.positionX == b.positionX && a.positionY == b.positionY;
		}
	};
}


struct Spot{
	char type;
	bool energy;
	
	Spot(char c){
		type = c;
		energy = false;
	}
};

struct Ray{
	char direction;
	int8_t positionX;
	int8_t positionY;
	
	Ray(char d, int8_t x, int8_t y){
	    direction = d;
	    positionX = x;
	    positionY = y;
	}
};

void print2D(vector<vector<Spot*>> v) {
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = 0; j < v[i].size(); j++) {
			cout << v[i][j]->type << " ";
		}
		cout << "\n";
	}
}

void print2DEnergyzed(vector<vector<Spot*>> v) {
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = 0; j < v[i].size(); j++) {
			if(v[i][j]->energy){
				cout << "# ";
			}
			else{
				cout << ". ";
			}
		}
		cout << "\n";
	}
}

uint countEnergy(const vector<vector<Spot>> &v){
	uint total = 0;
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = 0; j < v[i].size(); j++) {
			total += v[i][j].energy;
		}
	}
	return total;
}

uint process(Ray* initialRay, vector<vector<Spot>> matrix){
	unordered_set<VisitedSpot> visited;

	vector<Ray*> rays;
	rays.push_back(initialRay);

    while(!rays.empty()){
		//cout << "Rays: " << rays.size() << "\n";
    	for (uint i = 0; i < rays.size(); i++){
    	    Ray* r = rays[i];
    		switch (r->direction){
    			case 'r':
    				r->positionX++;
    				break;
    			case 'l':
    				r->positionX--;
    				break;
    			case 'u':
    				r->positionY--;
    				break;
    			case 'd':
    				r->positionY++;
    				break;
    		}
    		//cout << "X: " << r->positionX << ", Y: " << r->positionY << ", Dir: " << r->direction << "\n";
    		
    		if((r->positionY < 0 || r->positionY >= matrix.size()) || (r->positionX < 0 || r->positionX >= matrix[0].size())){
    		    rays.erase(rays.begin() + i);
    		    delete r;
    		    //cout << "Deleted. " << rays.size() << " left\n";
    		    continue;
    		}

			VisitedSpot currentSpot = {r->direction, r->positionX, r->positionY};

			if(visited.contains(currentSpot)){
				rays.erase(rays.begin() + i);
    		    delete r;
    		    //cout << "Deleted. " << rays.size() << " left\n";
    		    continue;
			}

			visited.insert(currentSpot);
    		
    		//check what is in that spot
    		Spot spot = matrix[r->positionY][r->positionX];
			matrix[r->positionY][r->positionX].energy = true;
    		switch (spot.type){
    			case '\\':
    				switch (r->direction){
            			case 'r':
            				r->direction = 'd';
            				break;
            			case 'l':
            				r->direction = 'u';
            				break;
            			case 'u':
            				r->direction = 'l';
            				break;
            			case 'd':
            				r->direction = 'r';
            				break;
            		}
    				break;
    			case '/':
    				switch (r->direction){
            			case 'r':
            				r->direction = 'u';
            				break;
            			case 'l':
            				r->direction = 'd';
            				break;
            			case 'u':
            				r->direction = 'r';
            				break;
            			case 'd':
            				r->direction = 'l';
            				break;
            		}
    				break;
    			case '|':
    				if(r->direction == 'l' || r->direction == 'r'){
    				    r->direction = 'u';
    				    Ray* newRay = new Ray('d', r->positionX, r->positionY);
                    	rays.push_back(newRay);
    				}
    				break;
    			case '-':
    				if(r->direction == 'u' || r->direction == 'd'){
    				    r->direction = 'l';
    				    Ray* newRay = new Ray('r', r->positionX, r->positionY);
                    	rays.push_back(newRay);
    				}
    				break;
    			default:
    			    continue;
    		}
    	}
	}

	uint count = countEnergy(matrix);
	//cout << count << " Energized\n";
	return count;
}

int main(){
    std::ifstream inputFile("input.txt");
	if (!inputFile.is_open()) {
		cout << "Error opening file\n";
		exit(EXIT_FAILURE);
	}

	vector<vector<Spot>> matrix;

	string line;
	while (getline(inputFile, line)) {
		vector<Spot> chars;
		for (char c : line){
			Spot s = Spot(c);
			chars.push_back(s);
		}
		matrix.push_back(chars);
	}

	uint maxCount = 0;
	char maxDir;
	int8_t maxX = 0;
	int8_t maxY = 0;
	
	char initialDir = 'd';
	for(uint8_t i = 0; i < matrix[0].size(); i++){
		Ray* initialRay = new Ray(initialDir, i, -1);
		
		uint count = process(initialRay, matrix);
		if(count > maxCount){
			maxCount = count;
			maxDir = initialDir;
			maxX = i;
			maxY = -1;
		}
	}

	initialDir = 'u';
	for(uint8_t i = 0; i < matrix[0].size(); i++){
		Ray* initialRay = new Ray(initialDir, i, matrix.size());
		
		uint count = process(initialRay, matrix);
		if(count > maxCount){
			maxCount = count;
			maxDir = initialDir;
			maxX = i;
			maxY = matrix.size();
		}
	}

	initialDir = 'r';
	for(uint8_t i = 0; i < matrix.size(); i++){
		Ray* initialRay = new Ray(initialDir, -1, i);
		
		uint count = process(initialRay, matrix);
		//cout << count << "\n";
		if(count > maxCount){
			maxCount = count;
			maxDir = initialDir;
			maxX = -1;
			maxY = i;
		}
	}

	initialDir = 'l';
	for(uint8_t i = 0; i < matrix.size(); i++){
		Ray* initialRay = new Ray(initialDir, matrix[0].size(), i);
		
		uint count = process(initialRay, matrix);
		if(count > maxCount){
			maxCount = count;
			maxDir = initialDir;
			maxX = matrix[0].size();
			maxY = i;
		}
	}

	cout << maxCount << " going in " << maxDir << " starting at " << static_cast<int>(maxX) << " | " << static_cast<int>(maxY) << "\n";
	return 0;
}