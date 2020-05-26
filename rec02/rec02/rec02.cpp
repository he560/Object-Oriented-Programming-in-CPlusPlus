//Hellen Ekpo
//Recitation 2
//2/20/2020
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct HydroCarbon {
    vector<string> name;
    int carbon = 0;
    int hydrogen = 0;
};

void open(ifstream& ifs);

void insert(const string& name, HydroCarbon& compound, vector<HydroCarbon>& compounds);

size_t findCompound(const vector<HydroCarbon>& compounds);

void addCompounds(ifstream& ifs, vector<HydroCarbon>& compounds);

void sortCompounds(vector<HydroCarbon>& compounds);

void displayCompounds(const vector<HydroCarbon>& compounds);

int main() {
    ifstream ifs;
    vector<HydroCarbon> compounds;
    open(ifs);
    addCompounds(ifs, compounds);
    sortCompounds(compounds);
    displayCompounds(compounds);
    ifs.close();
}

void open(ifstream& ifs) {
    bool test = false;
    string filename;
    while (!test) {
        cout << "What is the name of the file you want to open?" << endl;
        cin >> filename;
        ifs.open(filename);
        if (!ifs) {
            cout << "Could not open the file.\n" << "Try again.\n" << endl;
            ifs.clear();
        }
        else {
        test = true;
        }
    }
}

size_t findCompound(const HydroCarbon& compound, const vector<HydroCarbon>& compounds) {
    for(size_t i = 0; i < compounds.size(); ++i) {
        if (compound.carbon == compounds[i].carbon &&
            compound.hydrogen == compounds[i].hydrogen) {
                return i;
        }
    }
    return compounds.size();
}

void insert(const string& name, HydroCarbon& compound, vector<HydroCarbon>& compounds) {
    size_t index = findCompound(compound, compounds);
    if(index == compounds.size()) {
        compound.name.push_back(name);
        compounds.push_back(compound);
    }
    else {
        compounds[index].name.push_back(name);
    }
}


void addCompounds(ifstream& ifs, vector<HydroCarbon>& compounds) {
    while(ifs) {
        string name;
        char c, h;
        HydroCarbon compound;
        ifs >> name >> c >> compound.carbon
        >> h >> compound.hydrogen;
        insert(name, compound, compounds);
    }
}

void sortCompounds(vector<HydroCarbon>& compounds) {
    for (size_t ndx = 0; ndx < compounds.size(); ++ndx) {
        bool test = true;
        for (size_t i = 0; i < compounds.size()-1; ++i) {
            if (compounds[i].carbon > compounds[i+1].carbon) {
                swap(compounds[i], compounds[i+1]);
                test = false;
            }
            else if (compounds[i].carbon == compounds[i+1].carbon) {
                if (compounds[i].hydrogen > compounds[i+1].hydrogen) {
                    swap(compounds[i], compounds[i+1]);
                    test = false;
                }
            }
        }
    }
}

void displayCompounds(const vector<HydroCarbon>& compounds) {
    for(size_t i = 1; i < compounds.size(); ++i) {
        cout << "C" << compounds[i].carbon << "H" << compounds[i].hydrogen << " ";
        for(size_t ndx = 0; ndx < compounds[i].name.size(); ++ndx) {
            cout << compounds[i].name[ndx] << " ";
        }
        cout << endl;
    }
}

