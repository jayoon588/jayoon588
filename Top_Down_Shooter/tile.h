/**
 * @file tile.h
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Implementation of tiles
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QBrush>
#include <QPen>
#include <QColor>

/**
 * @class Tile  
 * @brief Creates tiles for the map which is used for obstacles and movement for enemies and players
 * 
 */
class Tile : public QGraphicsItemGroup {
private:
    QGraphicsRectItem *rect = nullptr;
    int tileType = -1;
    bool walkable = 1;
public:
    Tile(int, QGraphicsItem * = nullptr);
    ~Tile();
    virtual QPainterPath shape();
    virtual bool collidesWithItem(const QGraphicsItem *, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;
    int getTileType();
    bool getWalkable();
};