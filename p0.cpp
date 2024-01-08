/*
 Name: Nolan McKivergan
 Email: npmckivergan@crimson.ua.edu
 Course Section: Fall 2023 CS 201
 Homework #: 0
 Instructions to Compile: Run the command "g++ p0.cpp"
 Instructions to Execute: Run the command "./a.exe" followed by a space and the name of the text file containing the data (including .txt extension)
*/

//Necessary includes
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>
using namespace std;

//Class holding basic information about a movie i.e. the name and year it was released
class MovieInfo {
    string name;
    string year;
    public:
    //Constructor for MovieInfo object
    MovieInfo(string line) {
        stringstream line_ss(line);
        string name_and_title;
        getline(line_ss, name_and_title, '/');
        name = name_and_title.substr(0, name_and_title.find_last_of('(') - 1);
        year = name_and_title.substr(name_and_title.find_last_of('(') + 1, 4);
    }
    //Getter methods for name and year
    string getName() {
        return name;
    }
    string getYear() {
        return year;
    }
};

//Class holding string literal of line from text file alogn with information object
class Line {
    public:
    string line;
    MovieInfo *info;
    //Constructor for line object
    Line(string line) {
        this->line = line;
        info = new MovieInfo(line);
    }
    //Getter mehtod for line string
    string getLine() {
        return line;
    }
    //Getter method for info
    MovieInfo *getInfo() {
        return info;
    };
};

//Main driver code for file read, sort, and new file creation
int main(int argc, char* argv[]) {

    //Source for timing procedure: https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9

    //Start timer for complete process
    auto startTotalTime = chrono::high_resolution_clock::now();

    //Read in file from arguments
    string inputFileName = argv[1];

    int times[4];//Array to hold measured execution times

    //Prepare ifstream and vector to receive lines
    ifstream inputFile;
    inputFile.open(inputFileName);
    string line;
    vector<Line*> lines;

    //Create collection and measure time taken
    auto startTime = chrono::high_resolution_clock::now();//Start timer
    //Read in all lines from file and push to vector
    while(getline(inputFile, line)) {
        lines.push_back(new Line(line));
    }
    auto endTime = chrono::high_resolution_clock::now();//Stop timer
    times[0] = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();//Record time to form collection

    //Define lambda expressions for sorts
    //Source for sorting procedure: https://www.walletfox.com/course/sortvectorofcustomobjects11.php
    auto sortYear = [] (Line *line1, Line *line2) -> bool {
        //Handle case where years are the same
        if (line1->getInfo()->getYear() == line2->getInfo()->getYear()) {
            return line1->getInfo()->getName() < line2->getInfo()->getName();
        }
        else {
            return line1->getInfo()->getYear() < line2->getInfo()->getYear();
        }
    };
    auto sortName = [] (Line *line1, Line *line2) -> bool {
        //Handles case where names are the same
        if (line1->getInfo()->getName() == line2->getInfo()->getName()) {
            return line1->getInfo()->getYear() < line2->getInfo()->getYear();
        }
        else {
            return line1->getInfo()->getName() < line2->getInfo()->getName();
        }
    };

    //Sort lines with lambdas and push to new files

    //Sort by name process first
    startTime = chrono::high_resolution_clock::now();//Start timer
    sort(lines.begin(), lines.end(), sortName);//Sort with lambda
    endTime = chrono::high_resolution_clock::now();//Stop timer
    times[1] = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();//Record time to sort by name

    //Make new file and push strings from sorted line objects
    ofstream byName(string(argv[1]).substr(0, 7) + "ByName.txt");
    for (int x = 0; x < lines.size(); x++) {
        byName << lines.at(x)->getLine();
    }

    //Sort by year process next
    startTime = chrono::high_resolution_clock::now();//Start timer
    sort(lines.begin(), lines.end(), sortYear);//Sort with lambda
    endTime = chrono::high_resolution_clock::now();//End timer
    times[2] = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();(endTime - startTime).count();//Record time to sort by year

    //Make new file and push strings from sorted line objects
    ofstream byYear(string(argv[1]).substr(0, 7) + "ByYear.txt");
    for (int x = 0; x < lines.size(); x++) {
        byYear << lines.at(x)->line;
    }

    //End timer for complete process
    auto endTotalTime = chrono::high_resolution_clock::now();
    times[3] = chrono::duration_cast<chrono::microseconds>(endTotalTime - startTotalTime).count();//Record total time

    //Print info
    cout << "Number of records:\t" << " " << lines.size() << endl;
    cout << endl;
    cout << "Execution times (microseconds):" << endl;
    cout << endl;
    cout << "Time to form collection: " << times[0] << " uS" << endl;
    cout << "Time to sort by year: \t" << " " << times[1] << " uS" << endl;
    cout << "Time to sort by name:\t" << " " << times[2] << " uS" << endl;
    cout << "Total time taken:\t" << " " << times[3] << " uS" << endl;
}