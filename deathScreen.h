/**
 * @file deathScreen.h
 * @author Curtis Ackland (cacklan@uwo.ca)
 * @brief Implementation of death screen
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef DEATH_SCREEN_H
#define DEATH_SCREEN_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <view.h>
#include "menuButton.h"
#include "leaderboard.h"
#include <QInputDialog>
#include <QDialog>
/**
 * @class DeathScreen
 * @brief Creates a death screen for player to submit their final score
 * 
 */
class DeathScreen{
    public:
        explicit DeathScreen(int finalScore);
        ~DeathScreen();
};

#endif