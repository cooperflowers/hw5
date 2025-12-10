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



bool fixCheck(const std::string& word, const std::string& in, int wid);       //check matching fixed letters
bool floatCheck(const std::string& word, int wid, const std::string& remaining);   //check if all floating letters appear //after fix check



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    std::set<std::string> valid;         // set of all valid words

    
    for (std::set<std::string>::const_iterator it = dict.begin();       //for for all dict words
         it != dict.end();
         ++it)
    {
        const std::string& word = *it;     // current dictionary word on current iterator

        if (word.size() != in.size()) {     //check for same size
            continue;
        }

        bool lower = true;
        for (size_t i = 0; i < word.size(); ++i) {      // checking lowercase
            if (word[i] < 'a' || word[i] > 'z') {
                lower = false;
                break;
            }
        }
        if (!lower) {
            continue;                               //won't consider uppercase
        }


        if (!fixCheck(word, in, 0)) {          //check fixed slots word to in
            continue;
        }

        if (!floatCheck(word, 0, floating)) {      //checks floating slots, do the floating letters appear anywhere
            continue;
        }

        valid.insert(word);
    }

    return valid;


    
}

// Define any helper functions here





bool fixCheck(const std::string& word, const std::string& in, int wid){

    if (wid == (int)in.size()) {                  //base case when reached end
        return true;
    }

    if (in[wid] != '-' && word[wid] != in[wid]) {             //position has a letter that does not match or is not -, false
        return false;
    }

    return fixCheck(word, in, wid + 1);           //move on
}



bool floatCheck(const std::string& word, int wid, const std::string& remaining){            //checks for remaining floating letters


    if (wid == (int)word.size()) {                  //end of word base case
        return remaining.empty();                   //false if not all floating were found
    }

    char c = word[wid];                  // current 

    for (size_t j = 0; j < remaining.size(); ++j) {         //loop to check if c matches any remaining
        
        if (remaining[j] == c) {                            //match found
           
            std::string next = remaining;               //copy remaining
            next.erase(j, 1);              

            return floatCheck(word, wid + 1, next);     //recurse to check next character
        }
    }
    
    return floatCheck(word, wid + 1, remaining);
}