#include "ladder.h"
#include <unordered_set>

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " [" << word1 << ", " << word2 << "]" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();

    if (abs(len1 - len2) > d) return false;
    
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));

    for (int i = 0; i <= len1; i++) dp[i][0] = i;
    for (int j = 0; j <= len2; j++) dp[0][j] = j;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i][j - 1]) + 1;
            }
        }
    }

    return dp[len1][len2] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    int len1 = word1.length(), len2 = word2.length();
    
    if (abs(len1 - len2) > 1) return false;

    if (len1 == len2) { 
        // same length
        int diff_count = 0;
        for (int i = 0; i < len1; i++) {
            if (word1[i] != word2[i]) diff_count++;
            if (diff_count > 1) return false;
        }
        return diff_count == 1;
    } 

    if (len1 > len2) std::swap(word1, word2);
    
    // different elngths
    int i = 0, j = 0, diff_count = 0;
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            diff_count++;
            if (diff_count > 1) return false;
            j++;
        } else {
            i++;
            j++;
        }
    }
    return true;
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    unordered_set<string> visited_words;
    visited_words.insert(begin_word);

    while(!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string&word : word_list) {
            if (is_adjacent(last_word, word) && visited_words.find(word) == visited_words.end() ) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                visited_words.insert(word);

                if (word == end_word) return new_ladder; // word found

                ladder_queue.push(new_ladder);
            }
        }
    }
    return {}; // not found
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) { 
        error("","", "Could not open file.");
        return;    
    }

    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) { error("","", "Ladder is empty or not found.");}

    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {cout << " -> ";}
    }
    cout << endl;
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");

    vector<string> ladder = generate_word_ladder("code", "data", word_list);
    if (ladder.empty()) { error("code", "data", "No ladder found."); }

    for (size_t i = 0; i < ladder.size() - 1; i++) {
        if (!is_adjacent(ladder[i], ladder[i + 1])) {
            error(ladder[i], ladder[i + 1], "Words not adjacent.");
        }

        cout << "Word ladder works." << endl;
    }
}   

