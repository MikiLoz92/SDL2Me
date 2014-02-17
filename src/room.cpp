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

#include "room.h"

// Since we need to acces an Object's and Sprite's internal variables, we need to have more information
// about the class than just its simple forward declaration (in room.h), so we include its
// header in the implementation. We won't get circular dependencies this way.
#include "object.h"
#include "graphics.h"
#include "pause.h"
#include "script.h"
#include <stdlib.h>

// ALTAMENTE DEBUGEOSO/DEBUGIBLE/DEBUGEADO: ¡¡¡¡FRICKIN' GLOBALS!!!!
Room *gRoom;

/*
Room *S2M_CreateRoom() {
	Room *room = new Room();
	return room;
}*/
/*Room *S2M_CreateRoom(int w, int h) {
	Room *room = new Room(w,h);
	return room;
}*/
/*Room *S2M_CreateRoom(string filename, string scriptname) {
	Room *room = new Room(filename, scriptname);
	return room;
}*/
/*void S2M_SetRoom(Room *room) {
	gRoom = room;
}*/

/*template <class T>
void S2M_GoToRoom(Room *room) {
	gGraphics->setTransition(new T(S2M_TRANSITION_CLOSE));
	gRoom->nextRoom = room;
}*/

// Hay que instanciar todas las funciones con cada clase de Transición.
//template void S2M_GoToRoom<Transition>(Room *room);

/*void S2M_UpdateRoom() {
	gRoom->update();
}*/

bool compareObjectsByDepth(Object *obj1, Object *obj2) {
	return obj1->getDepth() > obj2->getDepth();
} 

bool compareBackgroundsByDepth(Background *bg1, Background *bg2) {
	if (bg1->getDepth() == -1) return false;
	else return bg1->getDepth() < bg2->getDepth();
}

Room::Room() {
	width = gGraphics->getGameWidth();
	height = gGraphics->getGameHeight();
	camera = nullptr;
}

Room::Room(int w, int h) {
	width = w;
	height = h;
	camera = nullptr;
}

Room::~Room() {
	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
}

int Room::getWidth() {
	return width;
}

int Room::getHeight() {
	return height;
}

void Room::update() {
	// Actualizamos la Cámara
	if (camera)	camera->update();

	// Reordenar los objetos a cada frame es una tarea tediosa que puede suponer un incremento
	// del 100% de trabajo de la CPU para cantidades abundantes de objetos (~8000 obj.).
	// NO SERÍA MEJOR ORDENARLOS SOLO CUANDO SE AÑADE UNO NUEVO???? DUH
	sort(objects.begin(), objects.end(), compareObjectsByDepth);
	//cout << objects.size() << " objects." << endl;

	// Dereferenciar cada objeto, sin embargo, es una tarea relativamente barata, ya que apenas
	// aumenta en un 10% el trabajo de la CPU para la misma copiosa cantidad de objetos.
	if (!gameInPause) {
		for (int i = 0; i < int(objects.size()); i++) {
			objects[i]->update();
			objects[i]->updateSpr();

			/**/cout << "Object#" << i << " x: " << objects[i]->x << " y: " << objects[i]->y << endl;
		}	
	}

	// Hay que comprobar si se activa algún evento y en ese caso, ejecutarlo.
	// TODO

	// Actualizamos cada Background
	for (int i = 0; i < int(backgrounds.size()); i++) {
		backgrounds[i]->update();
	}
}

void Room::drawBackgrounds() {

	for (int i = backgrounds.size()-1; i >= 0 ; i--) {
		Background *bg = backgrounds[i];
		gGraphics->drawTexture(bg->texture, int(bg->x), int(bg->y), bg->getWidth(), bg->getHeight());
		if (bg->x < 0) {
			gGraphics->drawTexture(bg->texture, int(bg->x) + bg->getWidth(), int(bg->y), bg->getWidth(), bg->getHeight());
		} else if (bg->x > 0) {
			gGraphics->drawTexture(bg->texture, int(bg->x) - bg->getWidth(), int(bg->y), bg->getWidth(), bg->getHeight());
		}
	} 

}

void Room::drawInstances() {

	float cx, cy;
	if (gRoom->camera) { cx = int(gRoom->camera->x); cy = int(gRoom->camera->y); }
	else { cx = 0; cy = 0; }

	for (int i = 0; i < objects.size(); i++) {

		Sprite *sprite = objects[i]->sprite;
		Object *object = objects[i];

		if (object->x < cx+320 && object->y < cy+240 && sprite) {
			
			int w = sprite->width;
			int h = sprite->height;

			SDL_Rect *src = sprite->getRect(object->sprFrame);
			SDL_Rect dest;
			if (object->sprFlip == SDL_FLIP_HORIZONTAL)	dest = {int(round(object->x-cx))-sprite->getWidth()+sprite->getXCenter(),int(round(object->y-cy))-sprite->ycenter,w,h};
			else dest = {int(round(object->x-cx))-sprite->xcenter,int(round(object->y-cy))-sprite->ycenter,w,h};

			SDL_RenderCopyEx(gGraphics->getRenderer(),sprite->texture, src, &dest, object->sprAngle, &(object->sprCenter), object->sprFlip);
			
			/* DEBUG: Draw each object's rect */
			/**/SDL_Rect onScreen = {object->rect.x-int(cx), object->rect.y-int(cy)-sprite->ycenter, object->rect.w, object->rect.h};
			/**/SDL_SetRenderDrawColor(gGraphics->getRenderer(),255,30,0,0);
			/**/SDL_RenderDrawRect(gGraphics->getRenderer(),&onScreen);
			/**/SDL_SetRenderDrawColor(gGraphics->getRenderer(),0,0,0,0);
		}
	}

}

void Room::draw() {
	drawBackgrounds();
	drawInstances();
}

void Room::setCamera(Camera *c) {
	camera = c;
}

void Room::addObject(Object *object) {
	cout << "Adding object to room" << endl;
	objects.push_back(object);
}

void Room::addBackground(Background *bg) {
	cout << "Adding Background to room" << endl;
	backgrounds.push_back(bg);
	sort(backgrounds.begin(), backgrounds.end(), compareBackgroundsByDepth);
}

/*TRoom::TRoom(string filename, vector<int> (*f)(string fname, TRoom *room)) {
	vector<int> data = f(filename, this);
	wtile = data[0];
	htile = data[1];
	width = data[2];
	height = data[3];
}*/

TRoom::TRoom(string filename, string scriptname) {

	// MAP PART
	xml_document<> mapxml;
	ifstream file;
	file.exceptions( ifstream::failbit );
	try {
		file.open(filename);
	} catch (ifstream::failure e) {
		cerr << "Error: resource \"" << filename << "\" is missing." << endl;
	}
	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	mapxml.parse<0>(&buffer[0]);

	// Leer atributos del mapa
	map_node = mapxml.first_node("map");
	wtile = atoi(map_node->first_attribute("tilewidth")->value());
	htile = atoi(map_node->first_attribute("tileheight")->value());
	width = atoi(map_node->first_attribute("width")->value()) * wtile;
	height = atoi(map_node->first_attribute("height")->value()) * htile;

	/**/cout << "Map width: " << width << " Map height: " << height << endl;

	xml_node<> *tileset_node = map_node->first_node("tileset");
	xml_node<> *layer_node = map_node->first_node("layer");

	while (tileset_node != NULL) {
		string tilesetName = tileset_node->first_attribute("name")->value();
		if ( tilesetName != "permissions") {
			stringstream ss;
			ss << "res/" << tileset_node->first_node("image")->first_attribute("source")->value();
			string s = ss.str();
			wtileset = atoi(tileset_node->first_node("image")->first_attribute("width")->value());
			tileset = gGraphics->loadTexture(s,false);
		} else {
			pfirstgid = atoi(tileset_node->first_attribute("firstgid")->value());
		} tileset_node = tileset_node->next_sibling("tileset");
	}

	while (layer_node != NULL) {
		string layerName = layer_node->first_attribute("name")->value();
		if (layerName != "Permissions") {
			xml_node<> *data_node = layer_node->first_node("data");
			string layerText = data_node->value();
			vector<vector<int>> layer;
			vector<string> lines = S2M_Script::SplitString(layerText,'\n');
			for (int i = 0; i < lines.size(); i++) {
				vector<string> strLine = S2M_Script::SplitString(lines[i],',');
				vector<int> intLine;
				for (int j = 0; j < strLine.size(); j++) {
					intLine.push_back(atoi(strLine[j].c_str()));
				} layer.push_back(intLine);
			}
			/*for (int i = 0; i < layer.size(); i++) {
				for (int j = 0; j < layer[i].size(); j++) {
					cout << layer[i][j] << "-";
				} cout << endl;
			}*/
			tmap.push_back(layer);
		} else {
			xml_node<> *data_node = layer_node->first_node("data");
			string layerText = data_node->value();
			vector<string> lines = S2M_Script::SplitString(layerText,'\n');
			for (int i = 0; i < lines.size(); i++) {
				vector<string> strLine = S2M_Script::SplitString(lines[i],',');
				vector<int> intLine;
				for (int j = 0; j < strLine.size(); j++) {
					intLine.push_back(atoi(strLine[j].c_str()));
				} pmap.push_back(intLine);
			}
			for (int i = 0; i < pmap.size(); i++) {
				for (int j = 0; j < pmap[i].size(); j++) {
					cout << pmap[i][j] << "-";
				} cout << endl;
			}
		} layer_node = layer_node->next_sibling("layer");
	}

	// SCRIPT PART
	S2M_Script::ParseFile(scriptname);

	camera = nullptr;
}

TRoom::~TRoom() {
	SDL_DestroyTexture(tileset);
}

void TRoom::parseObjects(map <string, Object *(*)(float, float, Room*)> objectMap) {

	// Leer capa de objetos y crear instancias
	xml_node<> *objectgroup_node = map_node->first_node("objectgroup");
	while (objectgroup_node != NULL) {
		xml_node<> *object_node = objectgroup_node->first_node("object");
		while (object_node != NULL) {
			char *type = object_node->first_attribute("type")->value();
			Object *(*b)(float, float, Room*) = objectMap.find(type)->second;
			int x = atoi(object_node->first_attribute("x")->value());
			int y = atoi(object_node->first_attribute("y")->value());
			cout << x << " " << y;
			(*b)(x,y,this);
			object_node = object_node->next_sibling("object");
		} objectgroup_node = objectgroup_node->next_sibling("objectgroup");
	}

}

void TRoom::setTileMap(vector<vector<vector<int>>> tm) {
	cout << "TM SIZEEEEEEEEEEEEEEE " << tm.size() <<endl;
	tmap = tm;
	cout << "TMAP SIZEEEEEEEEEEEEEEE " << tmap.size() <<endl;
}

void TRoom::setPermissionMap(vector<vector<int>> pm) {
	pmap = pm;
}

void TRoom::setTileset(SDL_Texture *t) {
	tileset = t;
	int w, h;
	SDL_QueryTexture(t, NULL, NULL, &w, &h);
	cout << "Dimensiones: " << w << " " << h << endl;
}

void TRoom::drawTileMap() {

	float cx, cy;
	if (gRoom->camera) { cx = int(gRoom->camera->x); cy = int(gRoom->camera->y); }
	else { cx = 0; cy = 0; }

	int wtileset;
	SDL_QueryTexture(tileset,NULL,NULL,&wtileset,NULL);
	div_t divresult;
	int x, y;
	for (int i = 0; i < tmap.size(); i++) {
		for (int j = 0; j < tmap[i].size(); j++) {
			for (int k = 0; k < tmap[i][j].size(); k++) {
				divresult = div(tmap[i][j][k]-1,wtileset/wtile);
				y = divresult.quot;
				x = divresult.rem;
				SDL_Rect src = {x*wtile,y*htile,wtile,htile};
				SDL_Rect dest = {int(round(k*wtile-cx)),int(round(j*htile-cy)),wtile,htile};
				SDL_RenderCopy(gGraphics->getRenderer(),tileset,&src,&dest);
			}
		}
	}

}

void TRoom::draw() {
	drawBackgrounds();
	drawTileMap();
	drawInstances();
}

Background::Background(string filename, char s) {
	x = 0;
	y = 0;
	xspeed = 0;
	yspeed = 0;
	texture = gGraphics->loadTexture(filename,true);
	SDL_QueryTexture(texture,NULL,NULL,&width,&height);
	style = s;
	if (style == S2M_BGSTYLE_FILL) {
		image = SDL_CreateTexture(gGraphics->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gGraphics->getGameWidth(), gGraphics->getGameHeight());
		gGraphics->blitTexture(texture, image, 0, 0, gGraphics->getGameWidth(), gGraphics->getGameHeight(), true);
	}
}

Background::Background(string filename, char s, float xspe, float yspe, float d) {
	x = 0;
	y = 0;
	xspeed = xspe;
	yspeed = yspe;
	depth = d;
	texture = gGraphics->loadTexture(filename,true);
	SDL_QueryTexture(texture,NULL,NULL,&width,&height);
	style = s;
	if (style == S2M_BGSTYLE_FILL) {
		image = SDL_CreateTexture(gGraphics->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gGraphics->getGameWidth(), gGraphics->getGameHeight());
		gGraphics->blitTexture(texture, image, 0, 0, gGraphics->getGameWidth(), gGraphics->getGameHeight(), true);
	}
}

Background::~Background() {
	/*SDL_DestroyTexture(texture);
	SDL_DestroyTexture(image);*/ //Da SegFault si una no está inicializada
}

int Background::getWidth() {
	return width;
}

int Background::getHeight() {
	return height;
}

float Background::getDepth() {
	return depth;
}

void Background::update() {
	float cxs, cys;
	if (gRoom->camera) { cxs = int(gRoom->camera->xspeed); cys = int(gRoom->camera->yspeed); }
	else { cxs = 0; cys = 0; }

	if (style != S2M_BGSTYLE_STATIC) {
		if (depth > 0) x += xspeed - cxs * (-1.0/depth);
		//y += yspeed - gRoom->camera->yspeed;
	}
	if (abs(x) > width) {
		div_t divresult;
		divresult = div(x,width);
		x = divresult.rem;
	}
	if (y == -height) y = 0;
}

void S2M_Room::AddBackground(Background *bg) {
	gRoom->addBackground(bg);
}

void S2M_Room::LoadScript(string filename) {
	gRoom->events = S2M_Script::ParseFile(filename);
}

void S2M_Room::LoadScript() {

}

Camera::Camera(Object * object) {
	x = object->x - gGraphics->getGameWidth()/2;
	y = object->y - gGraphics->getGameHeight()/2;
	xspeed = 0;
	yspeed = 0;
	this->object = object;
	mode = S2M_CAMERA_AUTOMATIC;
}

Camera::Camera(int x, int y) {
	x = x;
	y = y;
	xspeed = 0;
	yspeed = 0;
	xtarget = x;
	ytarget = y;
	mode = S2M_CAMERA_MANUAL;
}

Camera::~Camera() {

}

void Camera::setSpeed(int xspe, int yspe) {
	xspeed = xspe;
	yspeed = yspe;
}

void Camera::move(int dx, int dy) {
	x += dx;
	y += dy;
}

void Camera::goTo(int x, int y, bool smooth) {
	mode = S2M_CAMERA_MANUAL;
	xtarget = x;
	ytarget = y;
	if (!smooth)
	{
		this->x = x - gGraphics->getGameWidth()/2;
		this->y = y - gGraphics->getGameHeight()/2;
	}
}

void Camera::lock() {
	mode = S2M_CAMERA_MANUAL;
}

void Camera::release() {
	mode = S2M_CAMERA_AUTOMATIC;
	returning = true;
}

void Camera::update() {
	if (mode == S2M_CAMERA_AUTOMATIC) {
		xtarget = object->x + object->sprite->getWidth()/2;
		ytarget = object->y + object->sprite->getHeight()/2;
	}

	if (mode==S2M_CAMERA_MANUAL || returning) {
		if (xtarget + gGraphics->getGameWidth()/2 > gRoom->getWidth()) xtarget = gRoom->getWidth()-gGraphics->getGameWidth()/2;
		else if (xtarget < gGraphics->getGameWidth()/2) xtarget = gGraphics->getGameWidth()/2;
		if (ytarget + gGraphics->getGameHeight()/2 > gRoom->getHeight()) ytarget = gRoom->getHeight()-gGraphics->getGameHeight()/2;
		else if (ytarget < gGraphics->getGameHeight()/2) ytarget = gGraphics->getGameHeight()/2;
	}

	if (round(x+gGraphics->getGameWidth()/2) == round(xtarget)) { xspeed = 0; x = xtarget - gGraphics->getGameWidth()/2; }
	else xspeed = ( xtarget - gGraphics->getGameWidth()/2 - x ) / defaultspeed;
	if (round(y+gGraphics->getGameHeight()/2) == round(ytarget)) { yspeed = 0; y = ytarget - gGraphics->getGameHeight()/2; }
	else yspeed = ( ytarget - gGraphics->getGameHeight()/2 - y ) / defaultspeed;

	x += xspeed;
	y += yspeed;

	if (xspeed == 0 && yspeed == 0) returning = false;

	if (x < 0) { x = 0; xspeed = 0; }
	else if (x > gRoom->getWidth()-gGraphics->getGameWidth()) { x = gRoom->getWidth()-gGraphics->getGameWidth(); xspeed = 0; }
	if (y < 0) { y = 0; yspeed = 0; }
	else if (y > gRoom->getHeight()-gGraphics->getGameHeight()) { y = gRoom->getHeight()-gGraphics->getGameHeight(); yspeed = 0; }

}