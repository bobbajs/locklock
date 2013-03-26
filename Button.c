#include "Button.h"

struct Button* initButton(){
	struct Button* b = (struct Button*)malloc(sizeof(struct Button));
	b->name = NULL;
	b->x_pos = 0;
	b->y_pos = 0;
	b->buttonType = 3;
	return b;
}

struct Button* initMenuButton(int x, char* name, int color, int type){
	struct Button* b = initButton();
	b->name = name;
	b->x_pos = x;
	b->y_pos = 1; // all menu buttons have to be drawn at y = 1
	b->draw = drawMenuButton;
	b->type = type;
	b->collide = menuButtonCollide;
	return b;
}

struct Button* initSongButton(int x, int y, char* name, int color){
	struct Button* sb = initButton();
	sb->name = name;
	sb->x_pos = x;
	sb->y_pos = y;
	sb->draw = drawSongButton;
	return sb;
}

struct Button* initPlaylistButton(int x, int y, char* name, int color){
	struct Button* pb = initButton();
	pb->name = name;
	pb->x_pos = x;
	pb->y_pos = y;
	pb->draw = drawMenuButton;
	return pb;
}

void drawMenuButton(struct Button* this){
	// right now just write
	alt_up_char_buffer_string(char_buffer, this->name, this->x_pos, this->y_pos);
}

void drawSongButton(struct Button* this){
	// TODO: draw with different gradient background color,
	// may need to add integer as parameter.
	alt_up_char_buffer_string(char_buffer, this->name, this->x_pos, this->y_pos);
	int i;
	/*for (i = 0; i < 10; i++) {
		drawHorizontalLine(241, 13+i, 78, 0xe711ce);
	}*/
}

void dummyDraw(struct Button* this){

}

void menuButtonCollide(struct Frame* this){
	/*switch(this->eltype){
	case 0: // "All Songs" menu button
		allSongsMenuButtonCollide(this);
		break;
	case 1: // "Playlists" menu button
		playlistMenuButtonCollide(this);
		break;
	default:
		break;
	}*/
}

void playlistMenuButtonCollide(struct Frame* this){
	clearSongPanel();
	if (this->elements[3] == NULL){
		printf("Playlist frame is NULL\n");
		return;
	}
	this->elements[3]->drawFrame(this->elements[3]);
}

void allSongsMenuButtonCollide(struct Frame* this){
	clearSongPanel();
	if (this->elements[2] == NULL){
		printf("All Songs frame is NULL\n");
		return;
	}
	this->elements[2]->drawFrame(this->elements[2]);
}



