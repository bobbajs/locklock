#ifndef BUTTON_H
#define BUTTON_H
#include "Global.h"

enum Type{menu = 0, action = 1, song = 2, none = 3};
struct Button{
	enum Type buttonType;
	struct Frame* mainPanel;
	int type;
	int x_pos, y_pos;
	char* name;
	int bg_color;
	struct Image* stats[2]; // show diff image when clicked
	void (*draw)(struct Button*);
	void (*collide) (struct Frame*);
};

struct Button* initButton();
struct Button* initMenuButton(int, char*, int, int);
struct Button* initSongButton(int, int, char*, int);
struct Button* initPlaylistButton(int, int, char*, int);
void drawMenuButton(struct Button*);
void drawSongButton(struct Button*);
void dummyDraw(struct Button*);
void menuButtonCollide(struct Frame*);
void playlistMenuButtonCollide(struct Frame*);
void allSongsMenuButtonCollide(struct Frame*);
void dummyCollide(struct Button*);


#endif /* BUTTON_H_ */
