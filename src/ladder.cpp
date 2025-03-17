#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " [" << word1 << ", " << word2 << "]" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    if (str1 == str2) return true;
    if (abs(len1 - len2) > 1) return false;

    int i = 0, j = 0, difference = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            difference++;
            if (difference > d) return false;
            if (len1 > len2) i++; 
            else if (len1 < len2) j++; 
            else { i++; j++; }
        } else { i++; j++; }
    }
    
    if (i < len1 || j < len2) difference++;
    return difference == d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};

    set<string> local_set = word_list;
    queue<vector<string>> queue_path;
    queue_path.push({begin_word});
    local_set.erase(begin_word);

    while (!queue_path.empty()) {
        vector<string> word_ladder = queue_path.front();
        queue_path.pop();
        string cur_word = word_ladder.back();

        if (cur_word == end_word) return word_ladder;

        for (auto word = local_set.begin(); word != local_set.end();) {
            if (is_adjacent(cur_word, *word)) {
                vector<string> updated_ladder = word_ladder;
                updated_ladder.push_back(*word);
                queue_path.push(updated_ladder);
                word = local_set.erase(word);
            } else {
                ++word;
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream curFile(file_name);
    if (!curFile.is_open()) {
        error("", "", "Cannot open file!");
        return;
    }
    for (string word; getline(curFile, word);) {
        if (!word.empty()) word_list.insert(word);
    }
    curFile.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (!ladder.empty()) {
        cout << "Word ladder found: ";
        for (const auto& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    } else {
        error("", "", "No word ladder found.");
    }
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    vector<string> ladder = generate_word_ladder("code", "data", word_list);
    if (ladder.empty()) {
        error("code", "data", "No ladder found.");
        return;
    }

    for (size_t i = 0; i < ladder.size() - 1; i++) {
        if (!is_adjacent(ladder[i], ladder[i + 1])) {
            error(ladder[i], ladder[i + 1], "Words not adjacent.");
        }
    }

    print_word_ladder(ladder);
    cout << "Word ladder works." << endl;
}
