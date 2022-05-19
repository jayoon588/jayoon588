/**
 * @file view.cpp
 * @author Curtis Ackland (cacklan@uwo.ca)
 * @brief Singleton to access the view
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "view.h"
#include <QStyle>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QDesktopWidget>

View* View::view = NULL;

/**
 * @brief Returns the instance of view
 * 
 * @return View& 
 */
View& View::instance(){
    if(view == NULL){
        view = new View();
    }
    return *view;
}

/**
 * @brief Construct a new View:: View object
 * 
 */
View::View():QGraphicsView(){
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setMouseTracking(true);
	this->setCursor(Qt::CrossCursor);
    this->show();
    this->setInteractive(false);
}

/**
 * @brief Destroy the View:: View object
 * 
 */
View::~View(){

}

/**
 * @brief Whenever the mouse moves the mouse position is stored
 * 
 * @param event 
 */
void View::mouseMoveEvent(QMouseEvent* event){
    QGraphicsView::mouseMoveEvent(event);
    pos = event->pos();
}

/**
 * @brief Keeps track when the mouse is pressed down
 * 
 * @param event 
 */
void View::mousePressEvent(QMouseEvent *event){
    QGraphicsView::mouseMoveEvent(event);
    mouseDown = true;
}

/**
 * @brief Keeps track of when a mouse button is released
 * 
 * @param event 
 */
void View::mouseReleaseEvent(QMouseEvent *event){
    QGraphicsView::mouseMoveEvent(event);
    mouseDown = false;
}

/**
 * @brief Stores each key event in a set so no duplicate keys can be added (helps when a player presses W+D and moves diagonally for example)
 * 
 * @param event 
 */
void View::keyPressEvent(QKeyEvent *event){
    QGraphicsView::keyPressEvent(event);
    key.insert(event->key());
}

/**
 * @brief When a key is released it erases that key from the set
 * 
 * @param event 
 */
void View::keyReleaseEvent(QKeyEvent *event){
    QGraphicsView::keyReleaseEvent(event);
    key.erase(event->key());
}

/**
 * @brief Returns the set of keys that are being pressed
 * 
 * @return std::set<int> 
 */
std::set<int> View::getKey(){
    return key;
}

/**
 * @brief returns the position of the mouse
 * 
 * @return QPoint& 
 */
QPoint& View::getPos(){
    return pos;
}

/**
 * @brief Checks if mouse is being clicked
 * 
 * @return true 
 * @return false 
 */
bool View::getMouseDown(){
    return mouseDown;
}

/**
 * @brief gets the current window width
 * 
 * @return int window width
 */
int View::getAdjustedWindowWidth(){
    return (this->windowHandle()->width() - 2);
}

/**
 * @brief gets the current window height
 * 
 * @return int window height
 */
int View::getAdjustedWindowHeight(){
    return (this->windowHandle()->height() - 2);
}


