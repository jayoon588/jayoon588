/**
 * @file drop.cpp
 * @author Curtis Ackland (cacklan@uwo.ca) Evan Goldrick (egoldric@uwo.ca)
 * @brief Item drops
 * @version 0.1
 * @date 2021-11-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "drop.h"

/**
 * @brief Construct a new Drop:: Drop object
 * 
 * @param xPos of drop
 * @param yPos of drop
 * @param drop_type what item dropped
 * @param parent ItemGroup
 */
Drop::Drop(double xPos, double yPos, DropTypes drop_type, QGraphicsItem * parent):QGraphicsItemGroup(parent){
    this->dropType = drop_type;
    setPos(xPos, yPos);
    drop = new QGraphicsRectItem(-dropSize/2, -dropSize/2, dropSize, dropSize, this);
    QBrush brush;
    QTransform transform;
    transform.translate(-dropSize/2, -dropSize/2);
    drop->setPen(Qt::NoPen);

    if(dropType == DropTypes::Health) {
        brush.setTextureImage(QImage("resources/Health_Drop.png"));
    } else if(dropType == DropTypes::Shield) {
        brush.setTextureImage(QImage("resources/Shield_Drop"));
    } else if(dropType == DropTypes::Pistol) {
        brush.setTextureImage(QImage("resources/Pistol_Drop"));
    } else if(dropType == DropTypes::AR) {
        brush.setTextureImage(QImage("resources/AR_Drop"));
    } else if(dropType == DropTypes::Laser) {
        brush.setTextureImage(QImage("resources/Laser_Drop"));
    } else if(dropType == DropTypes::RocketLauncher) {
        brush.setTextureImage(QImage("resources/RL_Drop"));
    } else if(dropType == DropTypes::PistolAmmo) {
        brush.setTextureImage(QImage("resources/Pistol_Ammo"));
    } else if(dropType == DropTypes::ARAmmo) {
        brush.setTextureImage(QImage("resources/AR_Ammo"));
    } else if(dropType == DropTypes::LaserAmmo) {
        brush.setTextureImage(QImage("resources/Laser_Ammo"));
    } else if(dropType == DropTypes::RocketAmmo) {
        brush.setTextureImage(QImage("resources/RL_Ammo"));
    }
    brush.setTransform(transform);
    drop->setBrush(brush);
}

/**
 * @brief Destroy the Drop:: Drop object
 * 
 */
Drop::~Drop(){

}

/**
 * @brief checks if the drop is colliding with the other QtGraphicsItem
 * 
 * @param other QtGraphicsItem
 * @param mode type of collision
 * @return true if collision
 * @return false if no collision
 */
bool Drop::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode){
    return drop->collidesWithItem(other, mode);
} 

/**
 * @brief get the drop painter
 * 
 * @return QPainterPath 
 */
QPainterPath Drop::shape() const {
    return drop->shape();
}

/**
 * @brief get the type of drop
 * 
 * @return drop type 
 */
Drop::DropTypes Drop::getDropType(){
    return dropType;
}