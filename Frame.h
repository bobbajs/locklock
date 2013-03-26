#ifndef UI_H_
#define UI_H_
#include "Global.h"

#define SONG_Y_POSITION 4
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

struct Frame{
	struct Frame** elements;
	struct Button** buttons;
	int element_size;
	int background_col;
	struct Image* bg_image;

	void (*drawFrame)(struct Frame*);
};

struct Frame* initFrame();
struct Frame* initMainFrame();
struct Frame* initMenuFrame();
struct Frame* initActionFrame();
struct Frame* initSongPanel();
struct Frame* initPlaylistPanel();
void drawMainFrame(struct Frame* this);
void drawMenuFrame(struct Frame* this);
void drawActionFrame(struct Frame* this);
void drawSongPanel(struct Frame* this);
void clearSongPanel();
void getSongs();
void getPlaylists();
void displayLoadingScreenVGA();

#endif /* FRAME_H_ */
