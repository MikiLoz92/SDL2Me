#ifndef TFLIPEXPO_H
#define TFLIPEXPO_H

#include "../graphics.h"
#include "../defines.h"

float easeInExpo (float t,float b , float c, float d) {
	return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
}

float easeOutExpo (float t, float b , float c, float d) {
	return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
}

class TFlipExpo : public Transition {
public:
	TFlipExpo(bool m, bool s);
	~TFlipExpo();
	virtual void changeMode();
	virtual bool update();
protected:
	//! Current state of the Transition, represented by an integer.
	int step = 0;
	//! Number of frames that the Transition lasts.
	const int maxstep = 60;
};

TFlipExpo::TFlipExpo(bool m, bool s) : Transition(m,s) {
	texture = SDL_CreateTexture(gGraphics->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gGraphics->getGameWidth(), gGraphics->getGameHeight());
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(gGraphics->getRenderer(), texture);
	SDL_SetRenderDrawColor(gGraphics->getRenderer(),0,0,0,0);
	SDL_RenderClear(gGraphics->getRenderer());
	SDL_SetRenderTarget(gGraphics->getRenderer(), NULL);
	//mode = m;
}

TFlipExpo::~TFlipExpo() {
	SDL_DestroyTexture(texture);
}

void TFlipExpo::changeMode() {
	Transition::changeMode();
	step = 0;
}

bool TFlipExpo::update() {
	if (step >= maxstep) {
		done = true;
		return true;
	} else {
		if (mode == S2M_TRANSITION_CLOSE) {
			step++;
			float i = easeOutExpo(step,0,gGraphics->getGameWidth(),maxstep);
			SDL_Rect rect = { 0, 0, int(round(i)), gGraphics->getGameHeight() };
			SDL_SetRenderTarget(gGraphics->getRenderer(), texture);
			SDL_SetRenderDrawColor(gGraphics->getRenderer(), 0, 0, 0, 0);
			SDL_RenderClear(gGraphics->getRenderer());
			SDL_SetRenderDrawColor(gGraphics->getRenderer(), 0, 0, 0, 255);
			SDL_RenderFillRect(gGraphics->getRenderer(), &rect);
			SDL_SetRenderTarget(gGraphics->getRenderer(), NULL);
			SDL_Rect src = {0, 0, gGraphics->getGameWidth(), gGraphics->getGameHeight()};
			SDL_RenderCopy(gGraphics->getRenderer(), texture, &src, &src);
			cout << int(round(i)) << endl;
		} else {
			step++;
			float i = easeInExpo(step,0,gGraphics->getGameWidth(),maxstep);
			SDL_Rect rect = { int(round(i)), 0, gGraphics->getGameWidth()-int(round(i)), gGraphics->getGameHeight() };
			SDL_SetRenderTarget(gGraphics->getRenderer(), texture);
			SDL_SetRenderDrawColor(gGraphics->getRenderer(), 0, 0, 0, 0);
			SDL_RenderClear(gGraphics->getRenderer());
			SDL_SetRenderDrawColor(gGraphics->getRenderer(), 0, 0, 0, 255);
			SDL_RenderFillRect(gGraphics->getRenderer(), &rect);
			SDL_SetRenderTarget(gGraphics->getRenderer(), NULL);
			SDL_Rect src = {0, 0, gGraphics->getGameWidth(), gGraphics->getGameHeight()};
			SDL_RenderCopy(gGraphics->getRenderer(), texture, &src, &src);
			cout << int(round(i)) << endl;
		}
	} return false;
}

#endif