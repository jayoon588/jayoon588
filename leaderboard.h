/**
 * @file leaderboard.h
 * @author Calvin Nguyen (cnguy66@uwo.ca)
 * @brief header file for Leaderboard class
 * @version 1.0
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

/**
 * @class Leaderboard
 * @brief Leaderboard class for reading and writing leaderboard file
 * 
 */
class Leaderboard{
    public:
        virtual ~Leaderboard();
        static Leaderboard& instance();
        void submitScore (int playerScore, std::string playerName);
        const std::vector<std::string> getLeaderboard(); 

    protected:
        Leaderboard();
    
    private:
        Leaderboard (const Leaderboard& other);
        Leaderboard& operator= (const Leaderboard& other);
        mutable std::fstream leaderboardFile;
        static Leaderboard* LBinstance;
};

#endif