// WordCount.cpp

#include "WordCount.h"
#include <regex>
#include <sstream>


using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int total = 0;
	for (size_t i = 0; i < CAPACITY; ++i) {
        for (const auto &pair : table[i]) {
            total += pair.second;
        }
    }
    return total;
}

int WordCount::getNumUniqueWords() const {
    int c = 0;
    for (const auto *cur = table; cur < table + CAPACITY; ++cur) {
        c += cur->size();
    }
    return c;
}


int WordCount::getWordCount(std::string word) const {
	word = makeValidWord(word);
    size_t index = hash(word);
    for (const auto &pair : table[index]) {
        if (pair.first == word) {
            return pair.second;
        }
    }
    return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	word = makeValidWord(word);
    if (word.empty()){
            return 0;
    } 
    size_t index = hash(word);
    for (auto &pair : table[index]) {
        if (pair.first == word) {
            pair.second++;
            return pair.second;
        }
    }
    table[index].push_back(std::make_pair(word, 1));
    return 1;
}

int WordCount::decrWordCount(std::string word) {
	word = makeValidWord(word);
    size_t index = hash(word);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->first == word) {
            if (it->second > 1) {
                it->second--;
                return it->second;
            } else {
                table[index].erase(it);
                return 0;
            }
        }
    }
    return -1;
}

bool WordCount::isWordChar(char c) {
	return (std::isalpha(c) || c == '-' || c == '\'');
}

std::string WordCount::makeValidWord(std::string word) {
	 //do not forget std::
	std::transform(word.begin(), word.end(), word.begin(),[](unsigned char c) { return std::tolower(c); });

    if (word.empty()){
            return "";
    } 
    word = std::regex_replace(word, std::regex("^[^a-zA-Z]+|[^a-zA-Z]+$"), "");

    string result;
    for (size_t i = 0; i < word.size(); ++i) {
        if (isalpha(word[i]) || ((word[i] == '-' || word[i] == '\'') && i > 0 && i < word.size() - 1)) {
            result += word[i];
        }
    }
    return result ;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
 	std::vector<std::pair<std::string, int>> result;

    for (size_t i = 0; i < CAPACITY; ++i) {
        for (const auto &pair : table[i]) {
            result.push_back(pair);
        }
    }

    std::sort(result.begin(), result.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
    return a.first > b.first;
	});

    for (const auto &pair : result) {
        out << pair.first << "," << pair.second << "\n";
    }
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	std::vector<std::pair<std::string, int>> result;

    for (size_t i = 0; i < CAPACITY; ++i) {
        for (const auto &pair : table[i]) {
            result.push_back(pair);
        }
    }

    std::sort(result.begin(), result.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
	});


    for (const auto &pair : result) {
        out << pair.first << "," << pair.second << "\n";
    }
}

void WordCount::addAllWords(std::string text) {
	std::istringstream stream(text);
    std::string word;

    while (stream >> word) {
        word = makeValidWord(word);
        if (word.size() > 0) {
            incrWordCount(word);
        }
    }
}
