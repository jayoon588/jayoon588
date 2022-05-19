/**
 * @file main.cpp
 * @author Evan Goldrick (egoldric@uwo.ca), Curtis Ackland (cacklan@uwo.ca)
 * @brief Main entry point for starting the game
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "scene.h"
#include "view.h"
#include <qdesktopwidget.h>
#include <QGuiApplication>
#include <QScreen>
/**
 * @brief Main program for starting the game
 * 
 * @param argc number of command line args
 * @param argv command line args
 * @return int returns the return value of the QApplication
 */
int main(int argc, char **argv) {
	QApplication a(argc, argv);
	View::instance(); // Constructing view
	Scene *scene = new Scene();
	QRectF sceneSize = QRectF(0, 0, 1280, 720);
	View::instance().resize(1280, 720);
	View::instance().setScene(scene);
	View::instance().setSceneRect(sceneSize);

	return a.exec();
}
