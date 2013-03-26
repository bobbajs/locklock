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
	void (*collide) (struct Button*);
};

struct Button* initButton();
struct Button* initMenuButton(int, char*, int, int, struct Frame*);
struct Button* initSongButton(int, int, char*, int);
struct Button* initPlaylistButton(int, int, char*, int);
void drawMenuButton(struct Button*);
void drawSongButton(struct Button*);
void dummyDraw(struct Button*);
void menuButtonCollide(struct Button*);
void playlistMenuButtonCollide(struct Button*);
void allSongsMenuButtonCollide(struct Button*);
void dummyCollide(struct Button*);


#endif /* BUTTON_H_ */
