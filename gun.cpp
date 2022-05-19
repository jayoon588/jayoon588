/**
 * @file gun.cpp
 * @author Calvin Nguyen (cnguy66@uwo.ca), Curtis Ackland (cacklan@uwo.ca)
 * @brief implementation for the gun class
 * @version 1.0
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "gun.h"

/**
 * @brief Construct a new Gun and set the gun type
 * 
 * @param gun gun type
 */
Gun::Gun(std::string gun, QRectF player,  QGraphicsItem * parent){

    gun_type = gun;
    gun_model = new QGraphicsRectItem(0, 0, 0, 0, parent);
    gun_model->setPen(QPen(Qt::NoPen));
    if(gun_type == "Pistol"){
        gun_model->setRect(-player.width()/2, -player.height()/2 - 8, 5, 10);

        QTransform transform;
        transform.translate(0, -5);
        QBrush brush;
        brush.setTextureImage(QImage("resources/Pistol_Hold.png"));
        brush.setTransform(transform);
        gun_model->setBrush(brush);

        max_ammo_capacity = 120;
        ammo_capacity = 100;
        ammo_type = "Pistol";
        max_magazine_capacity = 5;
        magazine_capacity = max_magazine_capacity;
        reloadSpeed = 60; //Takes 1 second to reload
        fire_rate = 30;
        damage = 30;
    } else if(gun_type == "AR"){
        gun_model->setRect(-player.width()/2, -player.height()/2 - 16, 5, 20);

        QTransform transform;
        transform.translate(0, -10);
        QBrush brush;
        brush.setTextureImage(QImage("resources/AR_Hold.png"));
        brush.setTransform(transform);
        gun_model->setBrush(brush);

        max_ammo_capacity = 180;
        ammo_capacity = 100;
        ammo_type = "AR";
        max_magazine_capacity = 30;
        magazine_capacity = max_magazine_capacity;
        reloadSpeed = 75;
        fire_rate = 10;
        damage = 30;
    } else if(gun_type == "RL"){
        gun_model->setRect(-player.width()/2, -player.height()/2 - 16, 5, 50);

        QTransform transform;
        transform.translate(0, -31);
        QBrush brush;
        brush.setTextureImage(QImage("resources/RL_Hold.png"));
        brush.setTransform(transform);
        gun_model->setBrush(brush);

        max_ammo_capacity = 20;
        ammo_capacity = 15;
        ammo_type = "RL";
        max_magazine_capacity = 1;
        magazine_capacity = max_magazine_capacity;
        reloadSpeed = 180;
        fire_rate = 10;
        damage = 100;
    } else if(gun_type == "Laser"){
        gun_model->setRect(-player.width()/2, -player.height()/2 - 16, 5, 20);

        QTransform transform;
        transform.translate(0, -11);
        QBrush brush;
        brush.setTextureImage(QImage("resources/Laser_Hold.png"));
        brush.setTransform(transform);
        gun_model->setBrush(brush);

        max_ammo_capacity = 500;
        ammo_capacity = 400;
        ammo_type = "Laser";
        max_magazine_capacity = 100;
        magazine_capacity = max_magazine_capacity;
        reloadSpeed = 240;
        fire_rate = 2;
        damage = 10;
    }

}

/**
 * @brief gets the gun type of the gun object
 * 
 * @return std::string of gun type
 */
std::string Gun::getGunType(){

    return gun_type;

}

/**
 * @brief gets the gun ammo type of gun object
 * 
 * @return std::string of gun ammo type
 */
std::string Gun::getAmmoType(){

    return ammo_type;

}


/**
 * @brief gets the Maximum magazines the player is allowed to carry for this gun
 * 
 * @return int of maximum magazines
 */
int Gun::getMaxMagazineCapacity(){

    return max_magazine_capacity;

}

/**
 * @brief gets the current num of magazines the player is holding for this gun
 * 
 * @return int of magazines
 */
int Gun::getCurrentMagazineCapacity(){
    return magazine_capacity;

}

/**
 * @brief sets how many bullets are left in the magazine
 * 
 * @param newCapacity 
 */
void Gun::setCurrentMagazineCapacity(int newCapacity){
    magazine_capacity = newCapacity;
}

int Gun::getMaxAmmoCapacity() {
    return max_ammo_capacity;
}

void Gun::setMaxAmmoCapacity(int newCapacity) {
    max_ammo_capacity = newCapacity;
}

/**
 * @brief gets the num of ammo the player is holding for this gun
 * 
 * @return int of ammo
 */
int Gun::getAmmoCount(){

    return ammo_capacity;

}

/**
 * @brief Sets the total ammo count for the gun (ammo that is not in the gun)
 * 
 * @param count 
 */
void Gun::setAmmoCount(int count){
    ammo_capacity = count;
}

/**
 * @brief gets the reload speed for the gun
 * 
 * @return int of reload speed
 */
int Gun::getReloadSpeed(){

    return reloadSpeed;

}

/**
 * @brief gets how much of the reload cooldown is left
 * 
 * @return int 
 */
int Gun::getReloadTimeLeft(){
    return reloadTimeLeft;
}

/**
 * @brief sets how much of the reload cooldown if left
 * 
 * @param timeLeft 
 */
void Gun::setReloadTimeLeft(int timeLeft){
    reloadTimeLeft = timeLeft;
}

/**
 * @brief gets the time it takes in between shots
 * 
 * @return int 
 */
int Gun::getFireRate(){
    return fire_rate;
}

/**
 * @brief gets the cooldown time left before the gun can take the next shot
 * 
 * @return int 
 */
int Gun::getFireRateCD(){
    return fire_rate_cd;
}

/**
 * @brief updates the cooldown time left before the gun can take the next shot
 * 
 * @param rate 
 */
void Gun::setFireRateCD(int rate){
    fire_rate_cd = rate;
}

/**
 * @brief Gets the guns damage
 * 
 * @return int 
 */
int Gun::getGunDamage(){
    return damage;
}

/**
 * @brief Shows the gun model on the screen
 * 
 */
void Gun::showGun(){
    gun_model->show();
}

/**
 * @brief Hides gun model on the screen
 * 
 */
void Gun::hideGun(){
    gun_model->hide();
}

/**
 * @brief Gets the gun model the player is holding
 * 
 * @return QGraphicsRectItem* 
 */
QGraphicsRectItem* Gun::getGunModel(){
    return gun_model;
}

/**
 * @brief Destroy the Gun object
 * 
 */
Gun::~Gun(){
    delete gun_model;
}