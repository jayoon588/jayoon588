/**
 * @file leaderboard.cpp
 * @author Calvin Nguyen (cnguy66@uwo.ca)
 * @brief implentation of the Leaderboard class
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "leaderboard.h"

using namespace std;

Leaderboard* Leaderboard::LBinstance = NULL;

/**
 * @brief method to get instance of Leaderboard class
 * 
 * @return const Leaderboard&
 */
Leaderboard& Leaderboard::instance(){

    //creates new instance
    if (LBinstance == NULL){
        LBinstance = new Leaderboard();
    }

    return *LBinstance;

}

/**
 * @brief Constructor that open the leaderboard text file.
 * 
 */
Leaderboard::Leaderboard(){
    this->leaderboardFile.open("leaderboard.txt");
}

/**
 * @brief Destructor that closes the file
 * 
 */
Leaderboard::~Leaderboard(){
    this->leaderboardFile.close();
}

/**
 * @brief submits new player score that will read and write to the leaderboard text file
 * 
 * @param playerScore new player score
 * @param playerName new player name
 */
void Leaderboard::submitScore(int playerScore, string playerName){
    
    //checks if file is empty
    if (this->leaderboardFile.peek() == ifstream::traits_type::eof()){
        
        //These three lines are executed because file cannot be written after .peek()
        this->leaderboardFile.close();
        this->leaderboardFile.clear();
        this->leaderboardFile.open("leaderboard.txt");

        //writes single entry
        this->leaderboardFile << playerName << " " << to_string(playerScore);
        this->leaderboardFile.flush();

    }

    else{

        //These three lines are executed because file cannot be written after .peek()
        this->leaderboardFile.close();
        this->leaderboardFile.clear();
        this->leaderboardFile.open("leaderboard.txt");

        string line;

        //vector keeps track of names on leaderboard
        vector<string> names;
        //vector keeps track of scores on leaderboard
        vector<int> scores;

        //for each entry in the leaderboard...
        while (getline(this->leaderboardFile, line)){

            istringstream iss(line);
            string token;

            //adds name to name vector
            getline(iss, token, ' ');
            names.push_back(token);

            //adds score to score vector
            getline(iss, token, ' ');
            scores.push_back(stoi(token));     
            

        }

        //reverses both vectors so that they are lowest - highest
        reverse(scores.begin(), scores.end());
        reverse(names.begin(), names.end());

        //adds the new player name and score entry to the ordered vectors
        auto it = upper_bound(scores.cbegin(), scores.cend(), playerScore);
        scores.insert(it, playerScore);
        auto it2 = find(scores.cbegin(), scores.cend(), playerScore);
        int index = distance(scores.cbegin(), it2);
        names.insert(names.begin() + index, playerName); 

        //Reopen file for write and erase file contents
        this->leaderboardFile.close();
        this->leaderboardFile.clear();
        this->leaderboardFile.open("leaderboard.txt", std::ofstream::out | std::ofstream::trunc);

        //write scores to file
        int count = 0;
        for(int i = (scores.size() - 1); i >= 0; i--){

            count++;

            if ((i > 0) && (count != 10)){
                string newEntry = names[i] + " " + to_string(scores[i]);
                this->leaderboardFile << newEntry << endl;
            }
            else{
                string newEntry = names[i] + " " + to_string(scores[i]);
                this->leaderboardFile << newEntry;
            }

            //ensures only 10 entries will be in the file
            if (count == 10)
                break;

        }

    }

}

/**
 * @brief retreive the scores in the leaderboard
 * 
 * @return const vector<string> 
 */
const vector<string> Leaderboard::getLeaderboard(){

    string line;

    vector<string> entries;
    this->leaderboardFile.close();
    this->leaderboardFile.clear();
    this->leaderboardFile.open("leaderboard.txt");
    while (getline(this->leaderboardFile, line)){

        entries.push_back(line);

    }

    //closes and reopens the file so that the file pointer is reset
    this->leaderboardFile.close();
    this->leaderboardFile.clear();
    this->leaderboardFile.open("leaderboard.txt");

    return entries;

}
