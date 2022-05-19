/**
 * @file tile.cpp
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Implementation of tile class
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "tile.h"

/**
 * @brief Construct a new Tile:: Tile object
 * 
 * @param tileType 1 if the plyaer cant walk on the tile, 0 if the player can
 * @param parent GraphicsItemGroup
 */
Tile::Tile(int tileType, QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
    this->tileType = tileType;
    rect = new QGraphicsRectItem(-25, -25, 50, 50, this);
    rect->setPen(QPen(Qt::NoPen));
    // temporary values
    if (tileType == 0) {
        walkable = 1;
    } else if (tileType == 1) { // not walkable
        rect->setBrush(QBrush(QColor(0,0,0)));
        walkable = 0;
    } else { // Invalid type
        rect->setBrush(QBrush(QColor(255,0,255)));
        walkable = 0;
    }
}

/**
 * @brief Destroy the Tile:: Tile object
 * 
 */
Tile::~Tile() {
    delete rect;
}

/**
 * @brief get the shape of tile
 * 
 * @return QPainterPath 
 */
QPainterPath Tile::shape() {
    return rect->shape();
}

/**
 * @brief check if the current object is colliding with another object
 * 
 * @param other QGrapgicsItem
 * @param mode type of collision
 * @return true if collision
 * @return false if no collision
 */
bool Tile::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const {
    return rect->collidesWithItem(other, mode);
}

/**
 * @brief get the type of tile
 * 
 * @return int 1 if player cant walk on tile, 0 if they can
 */
int Tile::getTileType() {
    return tileType;
}

/**
 * @brief get if the tile is walkable
 * 
 * @return true if it is
 * @return false if it is not
 */
bool Tile::getWalkable() {
    return walkable;
}