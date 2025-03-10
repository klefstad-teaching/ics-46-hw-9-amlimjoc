#include "ladder.h"
#include <unordered_set>

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << << " [" << word1 << ", " << word2 << "]" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {

}

bool is_adjacent(const string& word1, const string& word2) {

}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    unordered_set<string> visited_words;
    visited_words.insert(begin_word);

    while(!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop()
        string last_word = ladder.back()

        for (const string&word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end() ) {
                vector<string> new_ladder = ladder;
                new_ladder.push.back(word);
                visited.insert(word);

                if (word == end_word) return new_ladder; // word found

                ladder_queue.push(new_ladder);
            }
        }
    }
    return {}; // not found
}

void load_words(set<string> & word_list, const string& file_name) {

}

void print_word_ladder(const vector<string>& ladder) {

}

void verify_word_ladder(){

}