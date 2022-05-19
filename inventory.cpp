/**
 * @file inventory.cpp
 * @author Curtis Ackland (cacklan@uwo.ca), Calvin Nguyen
 * @brief 
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "inventory.h"

/**
 * @brief Constuctor gives pistol in inventory to start and initalizes the rest to nothing
 */
Inventory::Inventory(QRectF player, QGraphicsItem * parent){
    gun_primary = new Gun("AR", player, parent);
    gun_secondary = new Gun("Pistol", player, parent);
    setHealthAmount(0);
    setShieldAmount(0);
}

/**
 * @brief changes primary gun to a new gun
 * @param *newGun is the new primary gun
 */
void Inventory::setGunPrim(Gun *newGun) {
    gun_primary = newGun;
}

/**
 * @brief gets current primary gun
 * @return primary gun 
 */
Gun* Inventory::getGunPrim(){
    return gun_primary;
}

/**
 * @brief changes secondary gun to a new gun
 * @param *newGun is the new secondary gun
 */
void Inventory::setGunSec(Gun *newGun){

    //if current secondary gun is the same as replacing gun, do nothing.
    gun_secondary = newGun;

}

/**
 * @brief gets current secondary gun
 * @return secondary gun 
 */
Gun* Inventory::getGunSec(){
    return gun_secondary;
}

/**
 * @brief sets new number of health packs in inventory
 * @param amount is new number of health packs
 */
void Inventory::setHealthAmount(int amount){
    amount_health = amount;
}

/**
 * @brief gets number of health packs in inventory
 * @return current number of health packs
 */
int Inventory::getHealthAmount(){
    return amount_health;
}

/**
 * @brief sets new number of shield packs in inventory
 * @param amount is new number of shield packs
 */
void Inventory::setShieldAmount(int amount){
    amount_shield = amount;
}

/**
 * @brief gets number of shield packs in inventory
 * @return current number of shield packs
 */
int Inventory::getShieldAmount(){
    return amount_shield;
}

/**
 * @brief Destructor
 */
Inventory::~Inventory(){

}


