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

#ifndef OBJECT_H
#define OBJECT_H

#include <cmath>
#include <SDL2/SDL.h>
#include "room.h"

class Sprite;
class Graphics;

bool compareObjectsByDepth(Object *obj1, Object *obj2);

//! Anything that can be positioned within a Room.
/*! As long as it has x and y coordinates it can be considered an object. */
class Object {
public:
	//! Default constructor.
	/*! \param sprite the Sprite the Object's gonna use
	 * \param x horizontal position on the Room
	 * \param y vertical position on the Room
	 * \param d depth on the Room, the higher the furthest away */
	Object(Sprite *sprite, float x, float y, char d);

	//! Default destructor.
	~Object();

	//! Sets the current animation
	/*! \param i the animation number */
	void setAnimation(int i);

	//! Gets the current animation number.
	/*! \return The current animation number. */
	int getAnimation();

	//! Sets the current sprite's frame and stops the current animation.
	/*! \param i the frame number */
	void setFrame(int i);

	//! Gets the current frame number of the Sprite.
	/*! \return The current image number. */
	int getFrame();

	//! Sets the Object's depth on the Room.
	/*! \param d the depth to be set to */
	void setDepth(char d);

	//! Gets the Object's depth on the Room.
	/*! \return The Object's depth on the Room. */
	char getDepth();

	//! Get the object's horizontal position on the next frame.
	/*! \return The object's horizontal position on the next frame. */
	float getNextX();

	//! Get the object's vertical position on the next frame.
	/*! \return The object's vertical position on the next frame. */
	float getNextY();

	//! Overridable update method. You'll need it.
	virtual void update();

	//! Overridable method. Updates all sprite-related variables.
	/*! Internally, it is always called after the general update method. This
	 * is because we don't want to update the Sprite until we've done the logic
	 * of the Object. Think about it as a simple Input->Output procedure. */
	virtual void updateSpr();

	//! Horizontal position on the Room.
	float x;
	//! Vertical position on the Room.
	float y;
	//! Current Sprite pointer.
	Sprite *sprite;

	friend void Room::update();
	friend class Graphics;

protected:
	//! Next frame's horizontal position on the Room.
	float xnext;
	//! Next frame's vertical position on the Room.
	float ynext;

	int sprDefaultFrame = 0;
	int animationFrame = 0;
	int sprFrame = 0;
	int sprAnimation = -1;
	int sprSpeed;
	int sprSpeedCounter = 0;
	//! Defines a rotation for the Object's Sprite.
	/*! If you're not gonna use this variable, delete it from source files */
	double sprAngle = 0;
	//! Rotating center point. By default it is the Sprite's center.
	/*! Same as before: if not gonna use it, delete */
	SDL_Point sprCenter;
	//! Flipping flags for the Object's Sprite.
	SDL_RendererFlip sprFlip = SDL_FLIP_NONE;
	//! Default object's depth on screen.
	char depth;
	//! Default SDL_Rect.
	SDL_Rect rect;
};

// TODO: Pasar variables públicas a privadas y construir sets & gets.

#endif