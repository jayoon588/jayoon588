/**
 * @file map.cpp
 * @author Curtis Ackland (cacklan@uwo.ca)
 * @brief Creates a grid based map to create obstacle and walkable tiles
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "map.h"

/**
 * @brief Construct a new Map
 * 
 * @param width of tile grid
 * @param length of tile grid
 * @param parent GraphicsItemGroup
 */
Map::Map(int width, int length, QGraphicsItem *parent) : QGraphicsItemGroup(parent){
    mapWidth = width;
    mapLength = length;
    map = new Tile**[width];
    for(int i = 0; i < width; i++){
        map[i] = new Tile*[length];
        for(int j = 0; j < length; j++){
            if(i == 0 || i == width - 1 || j == 0 || j == length - 1){
                map[i][j] = new Tile(1, this);
            } else {
                int r = std::rand() % 15;
                if(r == 0){
                    map[i][j] = new Tile(1, this);
                } else {
                    map[i][j] = new Tile(0, this);
                }   
            }
            map[i][j]->setPos(i * 50 + 25, j * 50 + 25);
        }
    }

    //set background
    ground = new QGraphicsRectItem(50, 50, 5000, 5000, this);
    ground->setPen(QPen(Qt::NoPen));
    ground->setZValue(-100);

    //add custom image
    QBrush brush;
    brush.setTextureImage(QImage("resources/Map.png"));
    ground->setBrush(brush);

}

/**
 * @brief Destroy the Map:: Map object
 * 
 */
Map::~Map(){

}

/**
 * @brief get the tile grid of the map
 * 
 * @return Tile*** 
 */
Tile*** Map::getMap(){
    return map;
}

/**
 * @brief get the tile width of the map
 * 
 * @return int tile width
 */
int Map::getMapWidth() {
    return mapWidth;
}

/**
 * @brief get the tile height of the map
 * 
 * @return int tile width
 */
int Map::getMapLength() {
    return mapLength;
}