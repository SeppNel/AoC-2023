#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#define ulong unsigned long

using std::cout;
using std::string;
using std::vector;

#define ulong unsigned long

/*
std::map<unsigned long, unsigned long> seedToSoil;
std::map<unsigned long, unsigned long> soilToFertilizer;
std::map<unsigned long, unsigned long> fertilizerToWater;
std::map<unsigned long, unsigned long> waterToLight;
std::map<unsigned long, unsigned long> lightToTemp;
std::map<unsigned long, unsigned long> tempToHumidity;
std::map<unsigned long, unsigned long> humidityToLocation;
*/



class entry
{
public:
    entry(ulong, ulong, ulong);
    unsigned long src;
    unsigned long dst;
    unsigned long len;
};


class map
{
public:
    vector<entry> entries;

};

entry::entry(ulong src, ulong dst, ulong len) {
    this->src = src;
    this->dst = dst;
    this->len = len;
}

map seedToSoil;
map soilToFertilizer;
map fertilizerToWater;
map waterToLight;
map lightToTemp;
map tempToHumidity;
map humidityToLocation;

int main()
{
    std::fstream inputFile;
    inputFile.open("input.txt", std::ios::in);
    if (!inputFile.is_open()) {
        cout << "Error opening file";
        exit(EXIT_FAILURE);
    }

    string line;
    std::getline(inputFile, line);
    string seedsStr = line.substr(line.find(":") + 2);

    vector<unsigned long> seeds;
    while (seedsStr.find(" ") != string::npos) {
        unsigned long num = stoul(seedsStr.substr(0, seedsStr.find(" ")));
        seeds.push_back(num);
        seedsStr = seedsStr.substr(seedsStr.find(" ") + 1);

        if (seedsStr.find(" ") == string::npos) {
            unsigned long num = stoul(seedsStr);
            seeds.push_back(num);
        }
    }

    int mapCounter = 0;
    while (std::getline(inputFile, line)) {
        if (line == "") {
            continue;
        }

        if (line.find(":") != string::npos) {
            mapCounter++;
            continue;
        }

        //std::map<unsigned long, unsigned long> *pMap = nullptr;
        map* pMap = nullptr;
        switch (mapCounter)
        {
        case 1:
            pMap = &seedToSoil;
            break;
        case 2:
            pMap = &soilToFertilizer;
            break;
        case 3:
            pMap = &fertilizerToWater;
            break;
        case 4:
            pMap = &waterToLight;
            break;
        case 5:
            pMap = &lightToTemp;
            break;
        case 6:
            pMap = &tempToHumidity;
            break;
        case 7:
            pMap = &humidityToLocation;
            break;
        }

        //cout << "Line: " << line << "\n";

        unsigned long dest = stoul(line.substr(0, seedsStr.find(" ")));
        line = line.substr(line.find(" ") + 1);

        unsigned long src = stoul(line.substr(0, seedsStr.find(" ")));
        line = line.substr(line.find(" ") + 1);

        unsigned long len = stoul(line);

        //cout << src << ", " << dest << ", " << len << "\n";

        entry tmp(src, dest, len);

        pMap->entries.push_back(tmp);

        /*

        for (size_t i = 0; i < len; i++){
            //pMap->insert(std::pair<int,int>(src, dest));
            (*pMap)[src] = dest;
            src++;
            dest++;
            //cout << i << " inside loop\n";
        }
        */
    }

    inputFile.close();

    cout << "Finished parsing file\n";

    unsigned long lowest = ULONG_MAX;
    for (auto seed : seeds) {
        ulong soil, fert, water, light, temp, humi, location;

        bool found = false;
        for (auto entry : seedToSoil.entries) {
            if (seed >= entry.src && seed <= entry.src + entry.len) {
                //cout << entry.src << ", " << entry.dst << ", " << entry.len << "\n";
                soil = seed + (entry.dst - entry.src);
                found = true;
                break;
            }
        }

        if (!found) {
            soil = seed;
        }


        found = false;
        for (auto entry : soilToFertilizer.entries) {
            if (soil >= entry.src && soil <= entry.src + entry.len) {
                fert = soil + (entry.dst - entry.src);
                found = true;
                break;
            }
        }

        if (!found) {
            fert = soil;
        }


        found = false;
        for (auto entry : fertilizerToWater.entries) {
            if (fert >= entry.src && fert <= entry.src + entry.len) {
                water = fert + (entry.dst - entry.src);
                found = true;
                break;
            }
        }

        if (!found) {
            water = fert;
        }


        found = false;
        for (auto entry : waterToLight.entries) {
            if (water >= entry.src && water <= entry.src + entry.len) {
                light = water + (entry.dst - entry.src);
                found = true;
                break;
            }
        }

        if (!found) {
            light = water;
        }

        found = false;
        for (auto entry : lightToTemp.entries) {
            if (light >= entry.src && light <= entry.src + entry.len) {
                temp = light + (entry.dst - entry.src);
                found = true;
                break;
            }
        }

        if (!found) {
            temp = light;
        }

        found = false;
        for (auto entry : tempToHumidity.entries) {
            if (temp >= entry.src && temp <= entry.src + entry.len) {
                humi = temp + (entry.dst - entry.src);
                found = true;
                break;
            }
        }

        if (!found) {
            humi = temp;
        }

        found = false;
        for (auto entry : humidityToLocation.entries) {
            if (humi >= entry.src && humi <= entry.src + entry.len) {
                location = humi + (entry.dst - entry.src);
                found = true;
                break;
            }
        }

        if (!found) {
            location = humi;
        }


        if (location < lowest) {
            lowest = location;
        }

        cout << "Seed " << seed << ", Soil " << soil << ", Fertilizer " << fert << ", Water " << water << ", Light " << light << ", Temperature " << temp << ", Humidity " << humi << ", Location " << location << "\n";
    }

    /*
    unsigned long lowest = ULONG_MAX;
    for (auto seed : seeds) {
        unsigned long soil = seedToSoil.count(seed) == 1 ? seedToSoil[seed] : seed;
        unsigned long fert = soilToFertilizer.count(soil) == 1 ? soilToFertilizer[soil] : soil;
        unsigned long water = fertilizerToWater.count(fert) == 1 ? fertilizerToWater[fert] : fert;
        unsigned long light = waterToLight.count(water) == 1 ? waterToLight[water] : water;
        unsigned long temp = lightToTemp.count(light) == 1 ? lightToTemp[light] : light;
        unsigned long humi = tempToHumidity.count(temp) == 1 ? tempToHumidity[temp] : temp;
        unsigned long location = humidityToLocation.count(humi) == 1 ? humidityToLocation[humi] : humi;

        if (location < lowest) {
            lowest = location;
        }

        cout << "Seed " << seed << ", Soil " << soil << ", Fertilizer " << fert << ", Water " << water << ", Light " << light << ", Temperature " << temp << ", Humidity " << humi << ", Location " << location << "\n";
    }
    */

    cout << lowest << "\n";

}