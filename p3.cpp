/*
 Name: Nolan McKivergan
 Email: npmckivergan@crimson.ua.edu
 Course Section: Fall 2023 CS 201
 Homework #: 3
 Instructions to compile: g++ p3.cpp
 Instructions to run: "./a.exe" followed by a space and then the data and query files seperated by a space, both with .txt extension included
*/

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <chrono>

using namespace std;

int main(int argc, char *argv[]) {

    //Start stopwatch for total time
    auto startTotalTime = std::chrono::steady_clock::now();

    //Unordered maps to map movie titles to actor name vectors, and actor names to movie title vectors
    unordered_map<string, vector<string>> movie_actors, actor_movies;

    //Helper strings for read-in process
    string line, movie, actor, query;

    //Helper vectors to temporarily store actors
    vector<string> actors;

    //Int to record number of movies in data file
    int records = 0;

    //Helper int for read-in process
    int i = 0;

    //Regex for parsing
    regex delim("/");

    //Data file input stream
    ifstream dbfile(argv[1]);

    ofstream output("output.txt");
    
    //Step 1: Parse data and populate unordered maps
    //Start stopwatch for build time
    auto startTime = std::chrono::steady_clock::now();
    while (getline(dbfile, line)) {
	    // parse each line for tokens delimited by "/"
	    auto begin = std::sregex_token_iterator(line.begin(), line.end(), delim, -1);
	    auto end = std::sregex_token_iterator();
        movie = *begin;//Record current movie
	    ++begin;//Move into actors
        //Parse actors
	    for (std::sregex_token_iterator word = begin; word != end; ++word) {
            actor = *word;
            actors.push_back(actor);//Record in list of all actors for a movie
            actor_movies[actor].push_back(movie);//Map current actor to current movie
	    }
        movie_actors[movie] = actors;//Map current movie title to all recorded actors for that movie
        actors.clear();//Clear actors buffer
        records++;//Move to next movie
	}

    //Stop stopwatch and record time
    auto endTime = std::chrono::steady_clock::now();
    int buildTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
	dbfile.close();//Close file

    //Query file stream
    ifstream queryfile(argv[2]);

    //Helper ints
    int x, y;

    //Step 2: Parse queries and perform searches
    //Start stopwatch for search time
    startTime = std::chrono::steady_clock::now();
    while (getline(queryfile, query)) {
        //Push query to output
        output << query << endl;

        //Determine if query is a movie title or actor name by looking for parenthesis
        if (query.find('(') != string::npos) {
            //Query is a movie
            //Output all actors in vector returned by searching the query in movie_actors
            y = movie_actors[query].size();
            if (y > 0) {
                for (x = 0; x < y; x++) {
                    output << "\t\t" << movie_actors[query].at(x) << endl;
                }
            }
            else {
                //Handle case where the vector is empty (i.e. the movie doesn't exist in the data file)
                output << "\t\tNone found" << endl;
            }
            
        }
        else {
            //Query is an actor
            //Output all movies in vector returned by searching the query in actor_movies
            y = actor_movies[query].size();
            if (y > 0) {
                for (x = 0; x < y; x++) {
                    output << "\t\t" << actor_movies[query].at(x) << endl;
                }
            }
            else {
                //Handle case where the vector is empty (i.e. the actor doesn't exist in the data file)
                output << "\t\tNone found" << endl;
            }
        }
        output << endl;
    }

    //Stop stopwatch and record search time
    endTime = std::chrono::steady_clock::now();
    int searchTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

    //Stop 
    int totalTime = chrono::duration_cast<chrono::microseconds>(endTime - startTotalTime).count();

    output << "Number of records:    " << records << endl;
    output << "Time taken to build:  " << buildTime << " uS" << endl;
    output << "Time taken to search: " << searchTime << " uS" << endl;
    output << "Total time taken:     " << totalTime << " uS" << endl;
}