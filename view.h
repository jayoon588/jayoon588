/**
 * @file view.h
 * @author Curtis Ackland (cacklan@uwo.ca)
 * @brief Singleton to access the view
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef VIEW_HEADER
#define VIEW_HEADER
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QWindow>
#include <set>

/**
 * @class View
 * @brief Creates a view for the player's movement and gameplay
 * 
 */
class View : public QGraphicsView{
    
    public:
        virtual ~View();
        static View& instance();
        virtual void mouseMoveEvent(QMouseEvent*);
        virtual void mousePressEvent(QMouseEvent*);
        virtual void mouseReleaseEvent(QMouseEvent*);
        virtual void keyPressEvent(QKeyEvent*);
        virtual void keyReleaseEvent(QKeyEvent*);
        int getAdjustedWindowWidth();
        int getAdjustedWindowHeight();
        std::set<int> getKey();
        bool getMouseDown();
        QPoint& getPos();
    protected:
        View();
    private:
        static View* view;
        QPoint pos;
        bool mouseDown = false;
        std::set<int> key;
    
};

#endif