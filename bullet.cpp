/**
 * @file bullet.h
 * @author Curtis Ackland (cacklan@uwo.ca)
 * @brief bullet class definition
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "bullet.h"

/**
 * @brief Construct a new Bullet:: Bullet object
 * 
 * @param originX x position where bullet is spawned
 * @param originY y position where bullet is spawned
 * @param xVel x distance bullet moves everytime moveBullet is called
 * @param yVel y distance bullet moves everytime moveBullet is called
 * @param parent Parent of who calls the bullet
 */
Bullet::Bullet(double originX, double originY, double bulletX, double bulletY, std::string gun, int damage, QGraphicsItem * parent):QGraphicsItemGroup (parent){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    QPen pen;
    pen.setStyle(Qt::NoPen);
    if(gun == "Pistol"){
        brush.setColor(Qt::gray);
        bullet = new QGraphicsRectItem(-1, -2.5, 3, 5, this);
        setPos(originX, originY);
        bullet->setBrush(brush);
    } else if(gun == "AR"){
        brush.setColor(Qt::gray);
        bullet = new QGraphicsRectItem(-1.5, -3.5, 3, 7, this);
        setPos(originX, originY);
        bullet->setBrush(brush);
    } else if(gun == "RL"){
        brush.setColor(Qt::darkGreen);
        bullet = new QGraphicsRectItem(-1.5, -3.5, 3, 7, this);
        setPos(originX, originY);
        bullet->setBrush(brush);
    } else if(gun == "Laser"){
        brush.setColor(Qt::red);
        bullet = new QGraphicsRectItem(-1.5, -3.5, 3, 7, this);
        setPos(originX, originY);
        bullet->setBrush(brush);
    } else {
        throw std::invalid_argument("Invalid bullet type");
    }
    this->gunType = gun;
    this->xVel = velocity*sin((atan2(bulletX, bulletY)));
    this->yVel = velocity*cos((atan2(bulletX, bulletY)));
    setRotation(180 - ((atan2(bulletX, bulletY)/M_PI) * 180));
    this->damage = damage;
}
/**
 * @brief Destroy the Bullet object
 * 
 */
Bullet::~Bullet(){

}

/**
 * @brief To move the bullet according to the x and y velocity each frame
 * 
 */
void Bullet::moveBullet(){
    setPos(pos().x() + xVel, pos().y() + yVel);
}

/**
 * @brief gets the damage the bullet will do
 * 
 * @return int 
 */
int Bullet::getDamage(){
    return damage;
}

/**
 * @brief gets gun type of bullet
 * 
 * @return std::string 
 */
std::string Bullet::getGunType(){
    return gunType;
}

/**
 * @brief Test collision with given GraphicsItem
 * 
 * @param item Item the bullet is checking collision with
 * @param mode Type of collision being run. Default is ItersectsItemShape
 * @return true When the item and bullet are colliding
 * @return false When the item and bullet are not colliding
 */
bool Bullet::collidesWithItem(const QGraphicsItem* item, Qt::ItemSelectionMode mode){
    return bullet->collidesWithItem(item, mode);
}



