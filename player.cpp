/**
 * @file player.cpp
 * @authors Calvin Nguyen (cnguy66@uwo.ca), Evan Goldrick (egoldric@uwo.ca), Curtis Ackland (cacklan@uwo.ca)
 * @brief implementation of the player class
 * @version 1.0
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "player.h"

/**
 * @brief constructor initializes position and direction of player which inherits from QGraphicsItem
 * @param initialX initial x pos
 * @param initialY initial y pos
 * @param initialD initial direction in radians
 */
Player::Player(double initialX, double initialY, double initialD, QGraphicsItem * parent):QGraphicsItemGroup (parent) {

    player = new QGraphicsRectItem (-(HITBOX_SIZE/2), -(HITBOX_SIZE/2), HITBOX_SIZE, HITBOX_SIZE, this);
    
    QPen outline;
    outline.setStyle(Qt::NoPen);
    player->setPen(outline);
    
    QTransform transform;
    transform.translate(-(HITBOX_SIZE/2), -(HITBOX_SIZE/2));

    QBrush brush;
    brush.setTextureImage(QImage("resources/Monke.png"));
    brush.setTransform(transform);
    player->setBrush(brush);

    

    inventory = new Inventory(QRectF(0, 0, HITBOX_SIZE, HITBOX_SIZE), this);
    setSelectedGun(1);
    this->setPos(initialX, initialY);
    this->setRotation(initialD);
}

/**
 * @brief Responsible for the melee functions for the player
 */
void Player::melee(){
    
}

/**
 * @brief Checks collision with another QGraphicsItem (in which each game object should inherit from)
 * 
 * @param other object that is checking collision with
 * @param mode specifies the type of collision
 * @return true if there is a collision
 * @return false if there is no collision
 */
bool Player::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const {
    return player->collidesWithItem(other, mode);
}

/**
 * @brief takes away from player's health or shield when called, dies when health reaches 0
 * @param dmg the amount that is taken away
 */
void Player::hit(int dmg){
    if (shield > 0){
        shield = shield - dmg;
        if (shield < 0){
            health = health + shield;
            shield = 0;
        }
    }
    else {
        health = health - dmg;
    }
}

/**
 * @brief gets the players health
 * @return the player's health
 */
int Player::getHealth(){
    return health;
}

/**
 * @brief sets the players health
 * 
 * @param health the players new health value
 */
void Player::setHealth(int health) {
    this->health = health;
}

/**
 * @brief gets the player's shield
 * 
 * @return int 
 */
int Player::getShield() {
    return shield;
}

/**
 * @brief sets the player's shield
 * 
 * @param shield the player's new shield value
 */
void Player::setShield(int shield) {
    this->shield = shield;
}

/**
 * @brief function to call when a player dies
 * @return 
 */
bool Player::isDead(){
    if (health <= 0){
        return true;
    }
    return false;
}

/**
 * @brief destructor that gets rid of the player object
 */
Player::~Player(){
    delete player;
}

/**
 * @brief Returns shape of player to collide with 
 * 
 * @return QPainterPath 
 */
QPainterPath Player::shape() const {
    return player->shape();
}

/**
 * @brief Gets player's inventory
 * 
 * @return Inventory* 
 */
Inventory* Player::getInventory(){
    return inventory;
}

/**
 * @brief Reduces the all of player's cooldowns by one if they are active (reload, firing a gun)
 * 
 */
void Player::cooldown(){

    if(getSelectedGun()->getReloadTimeLeft() != 0){
        getSelectedGun()->setReloadTimeLeft(getSelectedGun()->getReloadTimeLeft() - 1);
        if(getSelectedGun()->getReloadTimeLeft() == 0){
            if(getSelectedGun()->getAmmoCount() > (getSelectedGun()->getMaxMagazineCapacity() - getSelectedGun()->getCurrentMagazineCapacity())){
                getSelectedGun()->setAmmoCount(getSelectedGun()->getAmmoCount() - (getSelectedGun()->getMaxMagazineCapacity() - getSelectedGun()->getCurrentMagazineCapacity()));
                getSelectedGun()->setCurrentMagazineCapacity(getSelectedGun()->getMaxMagazineCapacity());
            } else {
                getSelectedGun()->setCurrentMagazineCapacity(getSelectedGun()->getCurrentMagazineCapacity() + getSelectedGun()->getAmmoCount());
                getSelectedGun()->setAmmoCount(0);
            }
        }
    }

    if(getSelectedGun()->getFireRateCD() != 0){
        getSelectedGun()->setFireRateCD(getSelectedGun()->getFireRateCD() - 1);
    }

}

/**
 * @brief Sets the gun that the player is holding and updates the screen to show that gun
 * 
 * @param selected 
 */
void Player::setSelectedGun(int selected){
    selected_gun = selected;
    if(selected_gun == 1){
        inventory->getGunPrim()->showGun();
        inventory->getGunSec()->hideGun();
    } else if(selected_gun == 2){
        inventory->getGunSec()->showGun();
        inventory->getGunPrim()->hideGun();
    }
}

/**
 * @brief get the player hitbox/size
 * 
 * @return int lenght of hitbox
 */
int Player::getPlayerHitBox(){
    return HITBOX_SIZE;
}

/**
 * @brief gets the player hit box as a QRectF object
 * 
 * @return QRectF of player hitbox
 */
QRectF Player::getPlayerHitBoxRect() {
    return QRectF(0, 0, HITBOX_SIZE, HITBOX_SIZE);
}

/**
 * @brief set the guns of the player
 * 
 * @param gun new gun to set
 */
void Player::setSelectedGunObj(Gun *gun) {
    if (selected_gun == 1) {
        inventory->setGunPrim(gun);
    } else if (selected_gun == 2) {
        inventory->setGunSec(gun);
    }
}

/**
 * @brief Returns the gun that the player is holding
 * 
 * @return Gun* 
 */
Gun* Player::getSelectedGun(){
    if(selected_gun == 1){
        return inventory->getGunPrim();
    } else if(selected_gun == 2){
        return inventory->getGunSec();
    }
    throw std::out_of_range("Selected gun is invalid");
}

/**
 * @brief checks if the player has the gun passed in the paremeter
 * 
 * @param type string for gun type
 * @return int 1 if primary gun matches, 2 if secondary gun matches, 0 if non matches
 */
int Player::hasGunType(std::string type) {
    if (inventory->getGunPrim()->getGunType() == type) {
        return 1;
    } else if (inventory->getGunSec()->getGunType() == type) {
        return 2;
    } else {
        return 0;
    }
}

/**
 * @brief get player speed
 * 
 * @return double
 */
double Player::getSpeed(){
    return SPEED;
}