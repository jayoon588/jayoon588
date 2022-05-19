/**
 * @file leaderboardMenu.h
 * @author Calvin Nguyen (cnguy66@uwo.ca)
 * @brief header file for the leaderboard menu
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef LEADER_MENU_H
#define LEADER_MENU_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <view.h>
#include "menuButton.h"
#include "leaderboard.h"
/**
 * @class LeaderboardMenu
 * @brief Creates a leaderboard menu screen
 * 
 */
class LeaderboardMenu : public QGraphicsItemGroup {
    public:
        explicit LeaderboardMenu(QGraphicsItem *parent = nullptr);
        ~LeaderboardMenu();
        int leaderboardLoop();
    private:
        MenuButton *backButton;
        QGraphicsTextItem *display;
        QGraphicsRectItem *background;
        const QString generateEntries();
};

#endif