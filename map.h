/**
 * @file map.h
 * @author Curtis Ackland (cacklan@uwo.ca)
 * @brief Implementation of Map
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef MAP_H
#define MAP_H

#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QPoint>
#include <vector>
#include "tile.h"
/**
 * @class Map   
 * @brief Creates a map for the game
 * 
 */
class Map : public QGraphicsItemGroup{

    private:
        int mapWidth;
        int mapLength;
        Tile ***map;
        QGraphicsRectItem *ground = nullptr;
    public:
        Map(int width, int length, QGraphicsItem *parent = nullptr);
        ~Map();
        Tile*** getMap();
        int getMapWidth();
        int getMapLength();
};

#endif