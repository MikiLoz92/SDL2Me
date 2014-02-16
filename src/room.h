//__________________________________________________________________________
//      _________________   ____    ________    _____                       |
//     /   _____/\______ \ |    |   \_____  \  /     \   ____               |
//     \_____  \  |    |  \|    |    /  ____/ /  \ /  \_/ __ \              |
//     /        \ |    `   \    |___/       \/    Y    \  ___/              |
//    /_______  //_______  /_______ \_______ \____|__  /\___ \              |
//            \/         \/        \/       \/       \/     \/              |
//__________________________________________________________________________|
//
// Copyright © 2013 Miguel Vera Belmonte AKA MikiLoz92.
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

/*! \file Room header file*/
/*! \page Functions */

/*! \mainpage SDL2Me Tutorial
 *
 * \section intro_sec Introduction
 *
 * SDL2Me, or S2M for short, is a library that uses SDL2 in order to bring a more
 * familiar game development environment, implementing concepts such as Sprites,
 * Cameras, Rooms, etc.
 * It is inspired in the way Game Maker software (by YoYoGames) handles game programming.
 *
 * \section actual_use_sec Actual use example
 *
 * This is an example of how to initialise the libraries and draw a simple Sprite on the screen:
 * \code{.cpp}
#include "S2M.h"

// Create an Options instance by checking the config file specified.
// This will load all configurations into memory.
Options gOptions = Options("config.cfg");

// Create the Graphics instance based on the game screen size specified and the Options instance.
Graphics gGraphics = Graphics(320,240,"S2M Test",&Options);

// Create a Room and make it current.
Room gRoom = Room(); // Default black Room
gGraphics.setCurrentRoom(gRoom);

// Create a first and only Sprite.
Sprite *test = gGraphics.createSprite("test.bmp",16,16,0);
test->x = 0;
test->y = 0;

// Game Loop
while (true) {

	// Update the graphics
	gGraphics.update()
}

\endcode
 * \section ideal_use_sec IDEAL use example
 *
 * This is an example of how to initialise the libraries and draw a simple Sprite on the screen,
 * following the desired patterns and main goals to accomplish of these libraries.
 * \code{.cpp}
#include "S2M.h"

// Create an Options instance by checking the config file specified.
// This will load all configurations into memory.
Options gOptions = Options("config.cfg");

// Create the Graphics instance based on the game screen size specified and the Options instance.
Graphics gGraphics = Graphics(320,240,"S2M Test",&Options);

// Create a Room and make it current.
Room gRoom = Room(); // Default black Room
S2M_MakeCurrentRoom(gRoom);

// Create a first and only Sprite.
Sprite *testSprite = gGraphics.createSprite("test.bmp",16,16,0); // After this it still won't show in the screen.

// Create an object bound to that Sprite.
Object *testObject = gRoom.createObject(testSprite);

// Game Loop
while (true) {

	// Update the room
	S2M_UpdateRoom(); 	// Will call the current Room's update method
						// The current Room's update method will call each object's update method.
						// Each object's update method will update its associated sprite's position.
						// The Graphics instance handles the Sprites update method, so no need for those calls here...

	// Update the graphics
	gGraphics.update()
}

\endcode
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#include "RapidXML/rapidxml.hpp"
#include "defines.h"

using namespace std;
using namespace rapidxml;

// Forward declarations
class Object;
class Sprite;
class Graphics;
class Background;
class Camera;
struct event;

bool compareObjectsByDepth(Object *obj1, Object *obj2);
bool compareBackgroundsByDepth(Background *bg1, Background *bg2);

//! Every Room operation is included here.
namespace S2M_Room {
	//! Adds a Background to the current Room's background vector.
	void AddBackground(Background *background);
	//! Loads a script from a file and to the current Room.
	void LoadScript(string filename);
	//! Loads the default script of the current Room.
	void LoadScript();
}

//! An abstraction of a certain space within a game.
/*! Rooms are a very abstract concept, much like objects. They represent
 * a certain part of the game, like a level, the game menu or the rolling
 * credits screen. */
class Room {
public:
	//! DEPRECATED: The constructor.
	/*! Creates a Room from a file.
	 * \param filename the design file
	 * \param scriptname the script file */
	Room(string filename, string scriptname);

	//! The simple constructor.
	/*! Creates an empty black Room with the game dimensions. */
	Room();

	//! The intermediate constructor.
	/*! Creates an empty black Room with the specified dimensions.
	 * \param w the Room's width
	 * \param h the Rooms height */
	Room(int w, int h);

	//! The destructor.
	/*! Destroys the Room and all its associated tile textures. */
	~Room();

	//! Creates all instances in the Room.
	void parseObjects(map <string, Object *(*)(float, float, Room*)> objectMap);

	//! Get the Room's width.
	/*! \return the Room's width \sa getHeight() */
	int getWidth();

	//! Get the Room's height.
	/*! \return the Room's height \sa getWidth() */
	int getHeight();

	//! Sets the pointer to the default Camera instance.
	/*! The Graphics instance needs a Camera instance pointer in order to know at any moment
	 * which part of the Room to draw on the screen.
	 * \param camera a pointer to a Camera instance */
	void setCamera(Camera *c);

	//! Adds an Object to the Room.
	/*! \param object the Object to add. \sa addBackground() */
	void addObject(Object *object);

	//! Adds a Background to the Room.
	/*! Right after this the background vector will get sorted. 
	 * \param object the Background to add. \sa addObject() */
	void addBackground(Background *background);

	//! The update method.
	virtual void update();

	//! The default camera
	Camera *camera;

	//! Next Room pointer (when transitioning).
	Room *nextRoom;

	//! Previous Room pointer (in case you need it).
	Room *prevRoom;

	//! A function that sorts Sprites by its depth.
	friend bool compareObjectsByDepth(Object *obj1, Object *obj2);
	friend bool compareBackgroundsByDepth(Background *bg1, Background *bg2);

	friend void S2M_Room::LoadScript(string filename);
	friend void S2M_Room::LoadScript();
	friend class Graphics;
	friend class Entity;

protected:
	xml_node<> *map_node;
	int width, height, wtile, htile, wtileset;
	int pfirstgid;
	vector<Object *> objects;
	vector<Background *> backgrounds;
	vector<event> events;
	vector<vector<vector<int>>> tmap;
	vector<vector<int>> pmap;
	SDL_Texture *tileset;
	//Graphics *graphics;
};

//! Stands for TileRoom. It's a Room that is populated by tiles.
/*! What makes this type of Room useful is that you can have multiple tilesets within
 * the same Room. Whenever you want to use the nth tileset just store the first tile
 * number of the given tileset on the pfirstgid vector. */
class TRoom : public Room {
public:
	//! Default constructor. Loads up tile information from a file using function f.
	/*! Creates a Room from a file.
	 * \param filename a file that has the Room's tile information
	 * \param (*f)(string, *Room) a pointer to a function that populates the Room */
	TRoom(string filename, vector<int> (*f)(string, TRoom*));

	//! Default destructor.
	~TRoom();

	//! Sets the TileMap.
	/*! \param tm the Tile Map	*/
	void setTileMap(vector<vector<vector<int>>> tm);

	//! Set the PermissionMap.
	/*! \param pm the Permission Map */
	void setPermissionMap(vector<vector<int>> pm);

	//! Set the default tileset.
	void setTileset(SDL_Texture *t);

protected:
	int wtile, htile;
	vector<vector<vector<int>>> tmap;
	vector<vector<int>> pmap;
	SDL_Texture *tileset;
};

class TdRoom : public TRoom {

};

// Cosas como curEvent, etc.

extern Room *gRoom;

//! Create an empty Room.
//Room *S2M_CreateRoom();
//Room *S2M_CreateRoom(int w, int h);
//Room *S2M_CreateRoom(string filename, string scriptname);
//void S2M_SetRoom(Room *room);
//! Transition smoothly to a given Room.
/*! \param room room to transition to
 * \param t transition type: defined in \link defines.h \endlink */
//template <class T>
//void S2M_GoToRoom(Room *room);
//void S2M_UpdateRoom();


//! A Room's background.
class Background {
public:
	//! The constructor.
	/*!
	 * \param filename the image to load
	 * \param style */
	Background(string filename, char s);

	//! Another constructor.
	/*
	 * \param filename the image to load
	 * \param style 
	 * \param xspe
	 * \param yspe
	 * \param d depth in the room (the greater the further away)
	 */
	Background(string filename, char s, float xspe, float yspe, float d);

	//! The destructor.
	/*! Frees the texture and destroys the Background. */
	~Background();

	int getWidth();
	int getHeight();
	float getDepth();

	void update();

	friend class Graphics;

	float x, y;
	float xspeed, yspeed;
	float depth;

private:
	char style;
	int width, height;
	//! The Background texture, after applying style transformations.
	SDL_Texture *image;
	SDL_Texture *texture;
};

//! Manages the Screen's viewport on a Room.
class Camera {
public:
	//! The constructor.
	/*! The constructor takes the Object to follow as a parameter and follows it around.
	 * \param object the Object to follow around */
	Camera(Object * object);

	//! Another constructor.
	/*!
	 * This constructor makes the Camera stay static on the given coordinates (top-left side
	 * of the screen). Useful when a sudden change in the viewport is needed.
	 * \param x the horizontal position on Room of the Camera
	 * \param y the vertical position on Room of the Camera
	 * \param graphics a pointer to a Graphics instance from where to get the game
	 * width and height
	 */
	Camera(int x, int y);

	//! The destructor
	~Camera();

	//! Sets the Camera speed
	/*! 
	 * \param xspe horizontal speed
	 * \param yspe vertical speed
	 */
	void setSpeed(int xspe, int yspe);

	//! Takes the camera on a smooth ride or instant leap towards the given object.
	/*!
	 * Won't stop until the object is centered on the screen.
	 * \param object the object to go to.
	 * \param smooth whether you want a smooth travel to the given object or not (instant leap)
	 */
	void goTo(Object * object, bool smooth);

	//! Locks the Camera and takes it on a smooth ride or an instant leap towards the destination point.
	/*!
	 * Won't stop until the destination point is on the top-left side of the screen.
	 * \param x the horizontal coordinate of the destination point
	 * \param y the vertical coordinate of the destination point
	 * \param smooth whether you want a smooth travel to the destination point or not
	 * (instant leap)
	 */
	void goTo(int x, int y, bool smooth);

	//! Locks the Camera's position so that it won't follow the object it's supposed to.
	void lock();

	//! Releases the Camera from a previous lock.
	void release();

	//! DEBUG FUNCTION
	void move(int dx, int dy);

	//! The default update method.
	/*!
	 * Overridable method. You can implement any path you would like your camera to follow
	 * as long as you modify the x and y coordinates whithin this method.
	 */
	void update();

	//! Camera position variables
	float x, y;
	float xspeed, yspeed;
	float xtarget, ytarget;
	bool mode;
	bool returning = false;
	float defaultspeed = 16;
	Object *object;

	friend class Graphics;
	friend class Background;

private:
	bool isTravelling;
};

#endif
