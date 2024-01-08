/*
 Name: Nolan McKivergan
 Email: npmckivergan@crimson.ua.edu
 Course Section: Fall 2023 CS 201
 Homework #: 2
 To Compile: "g++ p2.cpp"
 To Run: "./a.exe" followed by a space and the name of the text file containing the source data (including .txt extension)
*/

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;

//Struct to hold a unique word and the number of times it appears
class WordCounter {
   string word;//Value of unique word
   int count;//Number of times the word occurs
   public:
   //To be instantiated upon first instance of a word
   WordCounter(string word) {
      this->word = word;
      count = 1;
   }

   //To be called each time the word is found
   void increment() {
      count++;
   }

   //Getter methods
   string getWord() {
      return word;
   }
   int getCount() {
      return count;
   }
};

int main(int argc, char* argv[]) {
   //Start timer
   auto starttime = std::chrono::steady_clock::now();

   //Read in words from file and push to string vector
   ifstream inputFile;
   string inputFileName = argv[1];
   string word;
   inputFile.open(inputFileName);
   vector<string> words;
   while (inputFile >> word) {
      words.push_back(word);
   }

   //Sort words alphabetically
   sort(words.begin(), words.end());

   //Count occurrences of each word
   vector<WordCounter*> uniqueWords;//To hold each unique word and their counts
   WordCounter *curr = new WordCounter(words.at(0));//Record initial word at beginning of vector
   uniqueWords.push_back(curr);
   for (int x = 1; x < words.size(); x++) {//Loop through all remaining words
      if (words.at(x) == curr->getWord()) {//If the current word is the same as the current uniqueword, increment
         curr->increment();
      }
      else {//Otherwise, record new uniqueword and set as current
         curr = new WordCounter(words.at(x));
         uniqueWords.push_back(curr);
      }
   }

   //Labmda expression to sort uniqueword instances based first on count descending and then alphabetically
   auto sortCount = [] (WordCounter *wc1, WordCounter *wc2) -> bool {
      if (wc1->getCount() == wc2->getCount()) {
         return wc1->getWord() < wc2->getWord();
      }
      return wc1->getCount() > wc2->getCount();
   };

   //Sort unique words with above lambda expression
   sort(uniqueWords.begin(), uniqueWords.end(), sortCount);

   //Stop timer
   auto endtime = std::chrono::steady_clock::now();

   //Record time elapsed
   int timeTaken = chrono::duration_cast<chrono::microseconds>(endtime - starttime).count();

   // Print info to console
   cout << "Number of words: " << words.size() << endl;
   cout << "Time taken: " << timeTaken << " uS" << endl;
   for (int x = 0; x < uniqueWords.size(); x++) {
      cout << uniqueWords.at(x)->getWord() << ": " << uniqueWords.at(x)->getCount() << endl;
   }

   // Push info to an output file
   ofstream output("output.txt");
   output << "Number of words: " << words.size() << endl;
   output << "Time taken: " << timeTaken << " uS" << endl;
   for (int x = 0; x < uniqueWords.size(); x++) {
         output << uniqueWords.at(x)->getWord() << ": " << uniqueWords.at(x)->getCount() << endl;
      }
}