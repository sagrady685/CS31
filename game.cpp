#include "utilities.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const char WORDFILENAME[] = "/Users/sarahgrady/Desktop/words.txt";

int playOneRound(const char words[][7], int nWords, int wordnum) {
    
    int score = 0, goldCount = 0, silverCount = 0, i = 0;
    char probeWord[10000];
    char hiddenWord[7];
    strcpy(hiddenWord, words[wordnum]);
    bool winner = false;
    bool validProbe = true;
    bool realWord = false; // need this bool value in addition to validProve
    
    if ((nWords < 0)  || (wordnum < 0 || wordnum >= nWords)) {
        return -1;
    }
    
    while (true) { // use of while true to conduct looping of probe word until return
        cout << "Probe word: ";
        cin.getline(probeWord, 10000, '\n');
        score ++;
    
        // not matching word database
        for (i = 0; i < nWords; i++){
            if (strcmp(probeWord, words[i]) == 0) {
                realWord = true;
            }
         }
        
        if (realWord == false){
            cout << "I don't know that word.\n";
            score --;
        }
        
        // checking for word validity
        for (int a = 0; a < strlen(probeWord); a++) {
            if (!isalpha(probeWord[a])) {
                validProbe = false;
            }
            else if (!islower(probeWord[a])) {
                validProbe = false;
            }
            else if (strlen(probeWord) > 6 && strlen(probeWord) < 4) {
                validProbe = false;
            }
        }
        
        if (validProbe == false) {
            cout << "Your probe word must be a word of 4 to 6 lower case letters.\n";
            score --;
        }
       
        // only if word is valid and exists may it check for gold and silver
        if (validProbe == true && realWord == true) {
            for (i = 0; i < strlen(probeWord) && i < strlen(words[wordnum]); i++) { // gold check
                if (probeWord[i] == hiddenWord[i]) {
                    goldCount++;
                    hiddenWord[i] = '*'; // '*' used a s place holder so silver check will not recount
                    probeWord[i] = '*';
                }
            }
            for (i = 0; i < strlen(probeWord); i++) {
                for (int k = 0; k < strlen(words[wordnum]); k++) { // silver check
                    if ((probeWord[i] == hiddenWord[k]) && (probeWord[i] != '*')) {
                        hiddenWord[k] = '*';
                        silverCount++;
                        break; // without break, program will count silver for every letter incriment
                    }
                }
            }
            
            // copying hidden word back due to '*' adjustment in loop
            strcpy(hiddenWord, words[wordnum]);
            
            if (goldCount == strlen(hiddenWord)) { // correct word
                winner = true;
                return score;
            }
            
            cout << "Golds: " << goldCount << ", Silvers: " << silverCount << endl;
            
            // reset count for next probe word
            goldCount = 0;
            silverCount = 0;
        }
    }
    return 0;
}

int main() {
    
    char allWords[10000][7];
    double averageScore = 0, score = 0, totalScore = 0;
    int rounds = 0, minTries = 0, maxTries = 0;
    
    cout << "How many rounds do you want to play? ";
    cin >> rounds;
    cin.ignore(10000, '\n');
    
    if (rounds < 0) {
        cout << "The number of rounds must be positive.\n";
        return 0;
    }
    
    // gets all words
    int totalWords = getWords(allWords, 10000, WORDFILENAME);
    if (totalWords < 1) {
        cout << "No words were loaded, so I can't play the game.\n";
        return 0;
    }
    
    // picks a random word from total words
    int wordCount = randInt(0, totalWords - 1);
    
    // plays the game
    for (int i = 0; i < rounds; i ++) {
        wordCount = randInt(0, totalWords - 1);
        cout << "Round " << i + 1 << endl;
        cout << "The hidden word is " << strlen(allWords[wordCount]) << " letters long.\n";
        score = playOneRound(allWords, totalWords, wordCount);
        
        // comparison to get max and min
        if (score > maxTries) {
            maxTries = score;
        }
        if (score > 0) {
            minTries = score;
        }
        if (score < maxTries) {
            minTries = score;
        }
        if (score > 1) {
            cout << "You got it in " << score << " tries.";
        }
        else if (score == 1) {
            cout << "You got it in 1 try.";
        }
        
        totalScore += score; //placeholder for total score
        averageScore = totalScore / (i + 1);
        
        cout << fixed << setprecision(2) << endl;
        cout << "Average: " << averageScore << ", minimum: " << minTries << ", maximum: " << maxTries << endl;
        
        }
    }
