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

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#include "Easings/Expo.h"
#include "options.h"
#include "object.h"
#include "gui.h"

using namespace std;

class Sprite;
class Transition;

//! Controlls everything graphics-related.
/*! The Graphics class is an abstraction of everything graphic-based in the game.
 * Every operation that involves graphics should need a pointer to this class. */
class Graphics {
public:
	//! The constructor.
	/*! Creates a new window and gives it a caption. Uses logical size instead of window size.
	 * What this means is that it will create a window based on the size you input times the scaling
	 * integer that the Options instance has, based on what you have specified in the config file.
	 * \param winWidth the game width
	 * \param winHeight the game height
	 * \param winCaption the window caption
	 * \param options a pointer to an Options instance
	 * \sa ~Graphics */
	Graphics(int logWidth, int logHeight, string winCaption, Options * options);

	//! The destructor.
	/*! Destroys the current window, frees all existing textures and by all means finishes the game.
	 * \sa Graphics */
	~Graphics();

	//! Loads a bitmap file and makes it an SDL_Texture.
	/*! \param filename the bitmap to load (extension included)
	 * \param drawable indicates if the texture can or cannot be altered over time
	 * \return Pointer to SDL_Texture representing the loaded bitmap */
	SDL_Texture* loadTexture(string filename, bool drawable);

	//! Draws a texture directly on the screen.
	/*! This function draws a texture onscreen, bypassing viewports.
	 * \param source the texture to blit
	 * \param x horizontal position on screen
	 * \param y vertical position on screen
	 * \param w width to scale the given texture to
	 * \param h height to scale the given texture to */
	void drawTexture(SDL_Texture* source, int x, int y, int w, int h);

	//! Blits a source texture into a destination texture.
	/*! \param tsrc the source texture
	 * \param tdest the destination texture
	 * \param x destination horizontal position
	 * \param y destination vertical position
	 * \param clear whether to clear or not the destination texture before blitting */
	void blitTexture(SDL_Texture* tsrc, SDL_Texture* tdest, int x, int y, bool clear);

	//! Blits a source texture into a destination texture.
	/*! This method lets you scale your texture.
	 * \param tsrc the source texture
	 * \param tdest the destination texture
	 * \param x destination horizontal position
	 * \param y destination vertical position
	 * \param w width to scale the given texture to
	 * \param h height to scale the given texture to
	 * \param clear whether to clear or not the destination texture before blitting */
	void blitTexture(SDL_Texture* tsrc, SDL_Texture* tdest, int x, int y, int w, int h, bool clear);

	//! Blits a source texture into a destination texture.
	/*! This method is a bit more complex but gives you access to cropping and scaling your textures.
	 * \param tsrc the source texture
	 * \param tdest the destination texture
	 * \param src SDL_Rect of the source texture
	 * \param dest SDL_Rect of the destination texture
	 * \param clear whether to clear or not the destination texture before blitting */
	void blitTexture(SDL_Texture* tsrc, SDL_Texture* tdest, SDL_Rect* src, SDL_Rect* dest, bool clear);

	//! Flips the game screen and updates all instantiated Sprites.
	void update();

	//! Adds a Sprite to the \link sprites \endlink vector.
	/*! \param sprite the sprite pointer to add */
	void addSprite(Sprite * sprite);

	//! Adds a GUIElement to the \link guielements \endlink vector.
	/*! \param g the GUIElement to add */
	void addGUIElement(GUIElement *g);

	//! Gets the game width.
	/*! \return The game width. */
	int getGameWidth();

	//! Gets the game height.
	/*! \return The game height. */
	int getGameHeight();

	//! Get a pointer to the current transition.
	/*! \return Pointer to the current transition. */
	Transition *getTransition();

	//! Make a Transition occur instantaniously.
	/*! \param t pointer to a Transition to make. */
	void setTransition(Transition *t);

	//! Return a pointer to the default renderer.
	/*! \return Pointer to the default renderer. */
	SDL_Renderer *getRenderer();

	//! The game window SDL_Window instance pointer.
	SDL_Window* window;
	
	//! The game renderer SDL_Renderer instance pointer.
	SDL_Renderer* renderer;

protected:
	//! The game width.
	int gamewidth;
	//! The game height.
	int gameheight;
	//! DEPRECATED: A buffer to hold the whole screen.
	SDL_Texture *buffer;
	//! Pointer to the Options instance.
	Options *gOptions;
	//! Vector containing every single Sprite that is being used.
	vector<Sprite *> sprites;
	//! Vector containing every single GUIElement.
	vector<GUIElement *> guielements;
	//! Current transition pointer.
	/*! When NULL, no transition is taking effect. */
	Transition *trans;
};

//! Global instance of Graphics.
/*! Yeah, yeah, I know it's bad to have globals, but whatever, I'm just a C++ noob. */
extern Graphics *gGraphics;
extern Options *gOptions;

//! Creates the global Graphics instance.
/*! \return A pointer to the global Graphics instance. */
Graphics *S2M_CreateGraphics();

//! Updates the game's graphics
void S2M_UpdateGraphics();

//! A simple abstraction of a set of images and animations.
/*! A Sprite instance must be instantiated by each object who wants to have
 * a screen representation. */
class Sprite {
public:
	//! The constructor.
	/*! \param filename the bitmap filename where all the sprite images are to be loaded
	 * \param w the width of each image
	 * \param h the height of each image */
	Sprite(string filename, int w, int h);

	//! The destructor.
	/*! Destroys the Sprite and frees its textures. */
	~Sprite();

	//! Returns the Sprite's width.
	/*! /return The Sprite's width. */
	int getWidth();

	//! Returns the Sprite's height.
	/*! /return The Sprite's height. */
	int getHeight();

	//! Sets both the horizontal and vertical coordinates of the Sprite's center.
	/*! \param x horizontal coordinate of the Sprite's center
	 * \param y vertical coordinate of the Sprite's center */
	void setCenter(int xc, int yc);

	int getXCenter();
	int getYCenter();

	//! Gets the given frame's SDL_Rect on the Sprite texture.
	/*! \param i the frame number
	 * \return A pointer to an SDL_Rect structure. */
	SDL_Rect *getRect(int i);

	//! Adds an animation to the animations vector.
	/*! Each Sprite has a vector of animations, which are nothing more than image numbers
	 * arranged by order. They play in sequence and in the established order.
	 * \param animation a vector of numbers that represent frames */
	void addAnimation(vector<int> animation);

	//! Gets an animation from the animations vector.
	/*! \param i the animation index
	 * \return A vector containing the animation on the given index */
	vector<int> retAnimation(int i);

	//! Get the total number of animations.
	/*! \return The total number of animations. */
	int getAnimationsSize();

	//! An overridable update method in case you need it (?).
	virtual void update();

	friend void Graphics::update();
	friend void Object::update();
	friend class Graphics;
	friend void Room::drawInstances();
	friend class Object;

protected:
	//! The texture containing every single frame of the Sprite.
	SDL_Texture *texture;
	//! Sprite's width.
	int width;
	//! Sprite's height.
	int height;
	//! Sprite's texture width.
	int wtexture;
	//! Sprite's texture height.
	int htexture;
	//! Horizontal coordinate of the Sprite's center.
	int xcenter = 0;
	//! Vertical coordinate of the Sprite's center.
	int ycenter = 0;
	//! Animation vector.
	vector < vector<int> > animations;
	//! Vector containing each frame's bounding boxes.
	vector < vector<SDL_Rect> > bboxes;
	//! Bounding Box.
	SDL_Rect rect;
};

//! Takes care of transitioning towards another Room.
class Transition {
public:
	//! Default constructor.
	/*! \param m Transition mode (opening or closing)
	 * \param s Whether a single (just closing) or double (opening AND closing)
	 * Transition. */
	Transition(bool m, bool s);

	//! Default destructor.
	~Transition();

	//! Get the Transition type.
	bool getMode();

	//! Know whether this is a single or double Transition.
	bool isSingle();

	//! Return the delay time.
	int getDelay();

	//! Reset the Transition to opposite mode.
	virtual void changeMode();

	//! Overridable update method, in case you want to implement your own transitions.
	virtual bool update();

protected:
	//! The texture that will be blit on the screen.
	SDL_Texture *texture;
	//! Whether the Transition is completed or not.
	bool done = false;
	//! Transition mode (opening or closing).
	bool mode;
	//! Whether it is a single Transition (just closing) or a double (opening AND closing).
	bool single;
	//! Delay time (in ms) between opening and closing.
	int delay = 800;
};

#endif