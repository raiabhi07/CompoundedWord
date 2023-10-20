#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to check if a word is compounded
bool isCompounded(string word, unordered_set<string>& wordSet) {
    if (wordSet.count(word) > 0) {
        return true;
    }
    for (int i = 1; i < word.length(); i++) {
        string prefix = word.substr(0, i);
        if (wordSet.count(prefix) > 0) {
            string suffix = word.substr(i);
            if (isCompounded(suffix, wordSet)) {
                return true;
            }
        }
    }
    return false;
}

// Function to find the longest and second-longest compounded words
pair<string, string> findLongestCompoundedWords(vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    string longest = "";
    string secondLongest = "";
    for (string& word : wordList) {
        wordSet.erase(word);
        if (isCompounded(word, wordSet)) {
            if (word.length() > longest.length()) {
                secondLongest = longest;
                longest = word;
            } else if (word.length() > secondLongest.length()) {
                secondLongest = word;
            }
        }
        wordSet.insert(word);
    }
    return make_pair(longest, secondLongest);
}

int main() {
    auto startTime = high_resolution_clock::now();

    // Read the input file
    ifstream inputFile("Input_02.txt");
    vector<string> wordList;
    string line;
    while (getline(inputFile, line)) {
        line.erase(line.find_last_not_of("\r\n") + 1);
        wordList.push_back(line);
    }

    auto result = findLongestCompoundedWords(wordList);
    string longestCompounded = result.first;
    string secondLongestCompounded = result.second;

    auto endTime = high_resolution_clock::now();
    auto processingTime = duration_cast<milliseconds>(endTime - startTime).count();

    cout << "Longest Compound Word: " << longestCompounded << endl;
    cout << "Second Longest Compound Word: " << secondLongestCompounded << endl;
    cout << "Time taken to process file Input_02.txt: " << processingTime << " milliseconds" << endl;

    return 0;
}
