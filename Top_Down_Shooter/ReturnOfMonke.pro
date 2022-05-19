QT       += core widgets multimedia
TARGET = ReturnOfMonke
TEMPLATE = app 
SOURCES += main.cpp scene.cpp mainMenu.cpp menuButton.cpp mainGame.cpp bullet.cpp player.cpp HUDbar.cpp score.cpp view.cpp enemy.cpp gun.cpp inventory.cpp cooldownTimer.cpp gunInfo.cpp HUD.cpp drop.cpp tile.cpp map.cpp leaderboard.cpp leaderboardMenu.cpp deathScreen.cpp
HEADERS += scene.h mainMenu.h menuButton.h mainGame.h bullet.h player.h HUDbar.h score.h view.h enemy.h gun.h inventory.h cooldownTimer.h gunInfo.h HUD.h drop.h tile.h map.h leaderboard.h leaderboardMenu.h deathScreen.h
QMAKE_CXXFLAGS += -g
