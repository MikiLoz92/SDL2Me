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

#include "object.h"

// Since we need to acces a Sprite's internal variables, we need to have more information
// about the class than just its simple forwarddeclaration (in object.h), so we include its
// header in the implementation. We won't get circular dependencies this way.
#include "graphics.h"

Object::Object(Sprite *sprite, float x, float y, char d) {
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	depth = d;
	sprCenter = {sprite->getWidth()/2, sprite->getHeight()/2};
	rect = {int(x), int(y), sprite->rect.w, sprite->rect.h};
	//this->room = room;
	//image = SDL_CreateTexture(room->graphics->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sprite->w, sprite->h);
}

Object::Object(float x, float y) {
	sprite = nullptr;
	depth = 0; 
}

Object::~Object() {

}

void Object::setAnimation(int i) {
	if (sprite) {
		if (i < int(sprite->getAnimationsSize())) {
			sprAnimation = i;
			sprSpeed = 16;
		} else cout << "Trying to set animation to " << i << " but index out of range... (size=" << sprite->getAnimationsSize() << ")" << endl;
	}
}

int Object::getAnimation() {
	return sprAnimation;
}

void Object::setDepth(char d) {
	depth = d;
}

char Object::getDepth() {
	return depth;
}

float Object::getNextX() {
	return xnext;
}

float Object::getNextY() {
	return ynext;
}

void Object::update() {

}

void Object::updateSpr() {
	if (sprite) {
		// Update the rect.
		//rect.x = int(round(x + sprite->rect.x));
		//rect.y = int(round(y + sprite->rect.y));
		if (sprFlip == SDL_FLIP_HORIZONTAL) {
			rect.x = int(round(x + sprite->rect.x - sprite->getWidth() + sprite->getXCenter() ));
		} else {
			rect.x = int(round(x + sprite->rect.x - sprite->getXCenter()));
		} 
		rect.y = int(round(y + sprite->rect.y));
		//cout << "object x: " << x << " bbox x: " << rect.x << endl;

		/*if (sprFlip == SDL_FLIP_HORIZONTAL) {
			sprite->setCenter(sprite->getWidth()-sprite->getXCenter(),0);
		} else {
			sprite->setCenter(4,0);
		}*/

		if (sprAnimation != -1) {
			if (sprSpeedCounter == sprSpeed-1) {
				if (animationFrame >= sprite->animations[sprAnimation].size()-1) {
					animationFrame = 0;
				} else animationFrame++;
				sprSpeedCounter = 0;
			} else {
				sprSpeedCounter++;
			}
			sprFrame = sprite->animations[sprAnimation][animationFrame];
			//cout << sprSpeedCounter << endl;
		} else {
			sprFrame = sprDefaultFrame;
			sprSpeedCounter = 0;
		}

		//xnext = x + xspeed;
		//ynext = y + yspeed;
	}
}

Warp::Warp(float x, float y) : Object(x, y) {
	this->x = x;
	this->y = y;
	cout << "Creating WARP" << endl;
}

Warp::~Warp() {

}