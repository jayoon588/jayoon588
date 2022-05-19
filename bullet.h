/**
 * @file bullet.h
 * @author Curtis Ackland (cacklan@uwo.ca), Calvin Nguyen (cnguy66@uwo.ca)
 * @brief bullet class definition
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <math.h>
/**
 * @class Bullet
 * @brief Bullet stores everything needed for a bullet to exist
 * 
 */
class Bullet : public QGraphicsItemGroup{

    private:
        QGraphicsRectItem * bullet;
        double xVel;
        double yVel;
        double bulletWidth; //USE LATER
        double bulletHeight;
        int damage;
        double velocity = 5; 
        std::string gunType;

    public:
        Bullet(double playerX, double playerY, double bulletX, double bulletY, std::string gun, int damage, QGraphicsItem * parent = nullptr);
        ~Bullet();
        void moveBullet();
        int getDamage();
        std::string getGunType();
        virtual bool collidesWithItem(const QGraphicsItem*, Qt::ItemSelectionMode mode=Qt::IntersectsItemShape);
    
};


#endif