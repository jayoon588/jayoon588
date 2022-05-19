/**
 * @file player.h
 * @author Calvin Nguyen (cnguy66@uwo.ca) , Evan Goldrick (egoldric@uwo.ca), Curtis Ackland (cacklan@uwo.ca)
 * @brief header file for the player class
 * @version 1.0
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <iostream>
#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <stdexcept>
#include "inventory.h"
#include "gun.h"

/**
 * @class Player
 * @brief Player class that stores all information about the player
 */
class Player : public QGraphicsItemGroup{
    private:
        QGraphicsRectItem * player;
        const int HITBOX_SIZE = 30;
        int health = 100;
        int shield = 0;
        int melee_cd;
        int selected_gun;
        const int MELEE_CD_LEN = 1;
        Inventory *inventory;
        double SPEED = 3;
    
    public:
        Player(double initialX, double initialY, double initialD, QGraphicsItem * parent = nullptr);
        ~Player();
        void melee();
        virtual bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;
        virtual QPainterPath shape() const;
        void hit(int dmg);
        int getHealth();
        void setHealth(int);
        int getShield();
        void setShield(int);
        bool isDead();
        Gun* getSelectedGun();
        void setSelectedGun(int);
        void setSelectedGunObj(Gun*);
        Inventory* getInventory();
        void cooldown();
        int getPlayerHitBox();
        QRectF getPlayerHitBoxRect();
        int hasGunType(std::string);
        double getSpeed();
};

#endif
