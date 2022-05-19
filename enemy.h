/**
 * @file enemy.h
 * @author Evan Goldrick (egoldric@uwo.ca), David Lin (dlin72@uwo.ca)
 * @brief Definition of Enemy
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <string.h>
#include <iostream>
#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include "player.h"
#include <QtCore/qmath.h>
#include <boost/numeric/ublas/vector.hpp>
#include "HUDbar.h"

#ifndef ENEMY_H
#define ENEMY_H

/**
 * @class Enemy
 * @brief Enemy class that stores all information about the enemy
 */
class Enemy : public QGraphicsItemGroup{
    private:
        QGraphicsRectItem * enemy;
        QGraphicsEllipseItem * attackRange;
        HUDbar *healthBar;

        std::string name;
        int hitbox_size;
        int maxHealth;
        int health = maxHealth;
        int damage = 1;
        int attackCdTimeleft = 0;
        int attackCdFullTime = 100;
        double attackRadius;

        int movementSpeed;


    public:
        Enemy(std::string, double, double, double, int, int, double, double, QGraphicsItem * parent = nullptr);
        ~Enemy();
        
        void attack(Player *target);
        void move(Player *target);
        bool inRange(Player *target);
        virtual bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;
        void hit(int dmg);
        int getHealth();
        bool isDead();
        void setCooldownLength(int);
        void cooldown();
        virtual QPainterPath shape() const;
};

#endif