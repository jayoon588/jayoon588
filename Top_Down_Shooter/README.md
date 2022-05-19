# Return Of Monke
## Requirements
* Must have QT5
* Must have QT multimedia5
* Must have Boost

## How to install requirements
~~~bash
sudo apt install qt5-default
sudo apt install qtmultimedia5-dev
sudo apt install libboost-dev
~~~
## How To Run
~~~bash
qmake ReturnOfMonke.pro
make
./ReturnOfMonke
~~~

## Controls
M1 - Shoot
W - Move up
A - Move left
S - Move down
D - Move right
F - Pick up drop
1 - Switch to Primary Gun
2 - Switch to Secondary Gun
3 - Use Health pack
4 - Use Shield pack

## How we are building the project

We will be implementing many of the graphics using the Qt library, specifically the QtGraphics classes.

Most of the objects that will be drawn will inherit from Qt objects (e.g. QGraphicsItem) as they already have coordinates, direction, and more data and methods that can be inherited.

