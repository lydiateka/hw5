#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleFind(string& curr_word, size_t index, string floating, const set<string>& dict, set<string>& words);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
   string curr_word = in; 
   set<string> words; 
   wordleFind(curr_word, 0, floating, dict, words); 
   return words; 

}

// Define any helper functions here
void wordleFind(string& curr_word, size_t index, string floating, const set<string>& dict, set<string>& words) { 
    // If there is no more floating letters and the word is in the dictionary, add it to the set 
    if (index == curr_word.length()) { 
        if (floating.empty() && dict.find(curr_word) != dict.end()) {
            words.insert(curr_word); 
        }
        return; 
    }

    // If the current index is not a blank, recurse to the next open index
    if (curr_word[index] != '-') {
        wordleFind(curr_word, index + 1, floating, dict, words);
    }

    else { 
        // Try placing each floating letter in the current index
        for (size_t i = 0; i < floating.size(); i++) { 
            char letter = floating[i]; 
            curr_word[index] = letter; 
            
            // Remove used floating letter
            string temp_floating = floating; 
            temp_floating.erase(i, 1); 

            // Recurse to next open position
            wordleFind(curr_word, index + 1, temp_floating, dict, words); 
            curr_word[index] = '-';
        }  
        int blanks = 0; 
        for (size_t i = 0; i < curr_word.size(); i++) { 
            if (curr_word[i] == '-') { 
                blanks++;
            }
        }

        // If there are more blanks than floating letters, try a-z in the remaining positions
        if (blanks > (int)floating.size()) {
            for (char letter = 'a'; letter <= 'z'; letter++) { 
                // Skip floating letters
                if (floating.find(letter) == string::npos) {
                    curr_word[index] = letter; 
                    wordleFind(curr_word, index + 1, floating, dict, words); 
                }
            }
            // Backtrack 
            curr_word[index] = '-';
        }
       
    }

}

