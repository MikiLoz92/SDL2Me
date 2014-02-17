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

#ifndef ENTITY_H
#define ENTITY_H

#include "../object.h"
#include "../joystick.h"
#include "../defines.h"

class Sprite;

//! Any Object that is affected by gravity or capable of random motion.
/*! Contrary to popular definition, an Entity is defined in S2M as any type
 * of object (living, mechanic, inanimated) that is capable of being affected
 * by gravity and having random motion at any given time of the game. */
class Entity: public Object {
public:
	//! Deafult constructor. Works just like it would work with an Object.
	Entity(Sprite *sprite, float x, float y, char d);
	//! Constructor.
	//Entity(float x, float y);
	//! Default destructor. Works just like it would work with an Object.
	~Entity();
	//! Check if a collision is ocurring in any direction.
	/*! \param dir the direction to check the collision at.
	 * \return Whether it is ocurring or not */
	bool collidesOn(char dir);
	//! Binds a new Joystick instance to the Entity.
	void bindJoystick(Joystick *j);
	//! Overridable update method.
	/*! If you derive the Entity class be sure to place
	 * \code{.cpp}Entity::update();\endcode
	 * on the END of the new class' update method so it can implement the Entity default
	 * update method, which implements Object's as well. */
	virtual void update();
	virtual void updateSpr();
private:
	Joystick *joystick = new Joystick;
	// Physics
	float xspeed, yspeed;
	float FRICTION = 51.0/512.0;
	float GRAVITY = 80.0/512.0;
	float JUMPING_GRAVITY = 32.0/512.0;
	float MAX_VX = 812.0/512.0;
	float MAX_VY = 1535.0/512.0;
	float WALK_ACCEL = 85.0/512.0;
	float AIR_ACCEL = 32.0/512.0;
	float JUMP_SPEED = 1280.0/512.0;
	bool onGround;
	bool facing = false;
	bool jump = false;
	vector<bool> collision = {false,false,false,false};
};


//! An Entity that can be controlled directly with user input.
/*! A Hero is a type of Entity that can be controlled with an assigned Joystick.
 * The default assigned Joystick is \link gJoystick \endlink, but you can assign any other
 * VirtualJoystick if you want your Hero's movement to be script/code-determined. */
class Hero: public Entity {
public:
private:
};


//! An Entity that can't be directly controlled with user input.
class NPC: public Entity {
public:
private:
};

#endif