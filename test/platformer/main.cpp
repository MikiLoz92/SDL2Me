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

#include "../../src/S2M.h"
#include "../../src/S2M_Platformer.h"
#include "../../src/transitions/TFlipExpo.h"
#include "healthbar.h"

/*vector<int> populateRoom (string filename, TRoom *room) {

	vector<vector<vector<int>>> tmap;
	vector<vector<int>> pmap;
	vector<int> data;
	int pfirstgid;

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

	xml_node<> *map_node = mapxml.first_node("map");
	int wtile = atoi(map_node->first_attribute("tilewidth")->value());
	data.push_back(wtile);
	int htile = atoi(map_node->first_attribute("tileheight")->value());
	data.push_back(htile);
	data.push_back(atoi(map_node->first_attribute("width")->value()) * wtile);
	data.push_back(atoi(map_node->first_attribute("height")->value()) * htile);

	xml_node<> *tileset_node = map_node->first_node("tileset");
	xml_node<> *layer_node = map_node->first_node("layer");

	while (tileset_node != NULL) {
		string tilesetName = tileset_node->first_attribute("name")->value();
		if ( tilesetName != "permissions") {
			stringstream ss;
			ss << "res/" << tileset_node->first_node("image")->first_attribute("source")->value();
			string s = ss.str();
			int tilesetwidth = atoi(tileset_node->first_node("image")->first_attribute("width")->value());
			room->setTileset(gGraphics->loadTexture(s,false));
		} else {
			pfirstgid = atoi(tileset_node->first_attribute("firstgid")->value());
		} tileset_node = tileset_node->next_sibling("tileset");
	}
	while (layer_node != NULL) {
		string layerName = layer_node->first_attribute("name")->value();
		if (layerName != "Permissions") {
			cout << "CACACACACA" << endl;
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
			for (int i = 0; i < layer.size(); i++) {
				for (int j = 0; j < layer[i].size(); j++) {
					cout << layer[i][j] << "-";
				} cout << endl;
			}
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

	room->setTileMap(tmap);
	room->setPermissionMap(pmap);
	return data;
}*/


int main( int argc, char* args[] ) {

	S2M_CreateGraphics();

	//Room *room = S2M_CreateRoom(640,480);

	//TRoom *room =  new TRoom("res/map.tmx", &populateRoom);
	//Room *room = new Room("res/map.tmx", "res/script.txt");
	Room *room = S2M_CreateRoom<Room>("res/map.tmx", "res/script.txt");

	//cout << room->x << endl;
	S2M_SetRoom(room);
	//S2M_Room::LoadScript("res/script.txt");

	Room *room2 = S2M_CreateRoom<Room>("res/map2.tmx", "res/script.txt");

	Background bg0 = Background("res/gfx/csbg0.png", S2M_BGSTYLE_STATIC, 0, 0, -1);
	Background bg1 = Background("res/gfx/csbg1.png", S2M_BGSTYLE_PARALLAX, -0.25, 0, 4);
	Background bg2 = Background("res/gfx/csbg2.png", S2M_BGSTYLE_PARALLAX, -0.5, 0, 3);
	Background bg3 = Background("res/gfx/csbg3.png", S2M_BGSTYLE_PARALLAX, -1, 0, 2);
	Background bg4 = Background("res/gfx/csbg4.png", S2M_BGSTYLE_PARALLAX, -1.5, 0, 1);
	S2M_Room::AddBackground(&bg3);
	S2M_Room::AddBackground(&bg1);
	S2M_Room::AddBackground(&bg4);
	S2M_Room::AddBackground(&bg2);
	S2M_Room::AddBackground(&bg0);

	Background bg20 = Background("res/gfx/bgForest0.png", S2M_BGSTYLE_STATIC, 0, 0, -1);
	room2->addBackground(&bg20);

	Sprite *sprNate = S2M_CreateSprite("res/gfx/nate.bmp",16,16);
	sprNate->setCenter(7,0);
	Sprite *sprQuote = S2M_CreateSprite("res/gfx/quote.png",16,16);
	Sprite *sprNeko = S2M_CreateSprite("res/gfx/luffy2.png",32,32);

	Entity *objNate = S2M_CreateEntity(sprNate, 192, 0,1);
	Entity *objNeko = S2M_CreateEntity(sprNeko, 16, 16,1);
	Entity *objQuote = S2M_CreateEntity(sprQuote, 8,8,1);
	objNate->bindJoystick(gJoystick);
	sprNate->addAnimation({0,1,2,3});
	objNate->setAnimation(0);

	Camera gCamera = Camera(objNate);
	gRoom->setCamera(&gCamera);

	HealthBar h = HealthBar();
	HealthBar *healthBar = &h;
	ManaBar m = ManaBar();
	ManaBar *manaBar = &m;

	SDL_Event e;

	// Game Loop
	while (true) {

		if (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				//delete gGraphics;
				break;
			}
		}

		S2M_UpdateJoystick();

		// KEYBOARD CODE
		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
		if( currentKeyStates[ SDL_SCANCODE_UP ] ) {
			objNate->setAnimation(-1);
		} else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) {
			objNate->setAnimation(-1);
		} else if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
			objNate->setAnimation(0);
		} else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
			objNate->setAnimation(0);
		} else if( currentKeyStates[ SDL_SCANCODE_RETURN ] ) {
			break;
		} else if (currentKeyStates[SDL_SCANCODE_X]) { 
			gCamera.goTo(304+8,336+8,false);
			//gCamera.goTo(0,0,false);
		} else if (currentKeyStates[SDL_SCANCODE_C]) {
			gCamera.release();
		} else {
			objNate->setAnimation(-1);
			gCamera.setSpeed(0,0);
		}

		if (gJoystick->getBtnPressed(2)) {
			S2M_GoToRoom<TFlipExpo>(room2);
		}

	    S2M_Update();
	}

	exit(0);
}

