#include "Frame.h"

struct Frame* initFrame(){
	struct Frame* f = (struct Frame*)malloc(sizeof(struct Frame));
	f->element_size = 0;
	return f;
}

struct Frame* initMainFrame(){
	struct Frame* f = initFrame();
	f->elements = (struct Frame**)malloc(4*sizeof(struct Frame*));
	f->elements[0] = initMenuFrame(f);
	f->elements[1] = initActionFrame();
	f->elements[2] = initSongPanel();
	f->elements[3] = initPlaylistPanel();
	f->drawFrame = drawMainFrame;
	f->element_size = 4;
	f->button_size = 0;
	f->currentPanel = 0;
	return f;
}

struct Frame* initMenuFrame(struct Frame* mainFrame){
	struct Frame* mf = initFrame();
	mf->buttons = (struct Button**)malloc(2*sizeof(struct Button*));
	mf->buttons[0] = initMenuButton(5, "All Songs", 0x123456, 0, mainFrame);
	mf->buttons[1] = initMenuButton(35, "Playlists", 0x123456, 1, mainFrame);
	mf->drawFrame = drawMenuFrame;
	mf->button_size = 2;
	return mf;
}

struct Frame* initActionFrame(){
	struct Frame* af = initFrame();
	af->bg_image = loadSDImage("GR3.BMP");
	af->buttons = (struct Button**)malloc(5*sizeof(struct Button*));
	af->buttons[0] = initActionButton(0);
	af->buttons[0]->stats[0] = loadSDImage("PLAY2.BMP"); //size 30x30
	af->buttons[1] = initActionButton(1);
	af->buttons[1]->stats[0] = loadSDImage("STOP.BMP"); //size 20x20
	af->buttons[2] = initActionButton(2);
	af->buttons[2]->stats[0] = loadSDImage("PAUSE.BMP");
	af->buttons[3] = initActionButton(3);
	af->buttons[3]->stats[0] = loadSDImage("PREV.BMP");
	af->buttons[4] = initActionButton(4);
	af->buttons[4]->stats[0] = loadSDImage("NEXT.BMP");
	af->drawFrame = drawActionFrame;
	af->button_size = 5;
	return af;
}

struct Frame* initSongPanel(){
	struct Frame* sp = initFrame();
	sp->buttons = (struct Button**)malloc(50*sizeof(struct Button*));
	int i = 1;
	int init_song_y = 4;
	for (i = 1; i < db.num_of_songs; i++){
		sp->buttons[i] = initSongButton(61, init_song_y, db.songs[i]->song_name, 0x123456);
		init_song_y = init_song_y+3;
	}
	sp->drawFrame = drawSongPanel;
	sp->background_col = 0;
	sp->button_size = db.num_of_songs; // starts from 1
	return sp;
}

struct Frame* initPlaylistPanel(){
	struct Frame* pp = initFrame();
	pp->buttons = (struct Button**)malloc(50*sizeof(struct Button*));
	int i = 1;
	int init_playlist_y = 4;
	for (i = 1; i < db.num_of_lists; i++){
		pp->buttons[i] = initPlaylistButton(61, init_playlist_y, db.playlists[i]->list_name, 0x123456);
		init_playlist_y += 3;
	}
	pp->drawFrame = drawPlaylistPanel;
	pp->button_size = db.num_of_lists; // starts from 1
	return pp;
}

/**
 * Draws all elements of mainFrame. All backgrounds are
 * loaded and drawn in this function.
 */
void drawMainFrame(struct Frame* this){
	int i = 0;
	// do not draw the last element (playlist)
	for (i = 0; i < this->element_size - 1; i++){
		this->elements[i]->drawFrame(this->elements[i]);
	}
	// TODO: put all backgrounds in here.
	// make a struct Image array in mainFrame
	struct Image* bg = loadSDImage("AND.BMP");
	draw_notransparent(241, 13, bg);
	drawVerticalLine(240, 12, 183, 0xFFFFFF);
}

void drawMenuFrame(struct Frame* this){
	int x1, y1, x2, y2;
	drawHorizontalLine(0, 0, SCREEN_WIDTH-1, 0xFFFFFF);
	drawHorizontalLine(0, 11, SCREEN_WIDTH-1, 0xFFFFFF);
	x1 = 0; y1 = 1;
	x2 = x1 + 10;
	y2 = 11;
	while (x2 <= 320){
		drawBox(x1, y1, x2, y2, 0xe711ce);
		x1+=10;
		x2+=10;
	}
	this->buttons[0]->draw(this->buttons[0]);
	this->buttons[1]->draw(this->buttons[1]);
}

void drawActionFrame(struct Frame* this){
	drawHorizontalLine(0, 195, SCREEN_WIDTH-1, 0xFFFFFF);
	draw_notransparent(0, 196, this->bg_image);;
	int i = 0;
	for (i = 0; i < this->button_size; i++){
		this->buttons[i]->draw(this->buttons[i]);
	}
}

void drawSongPanel(struct Frame* this){
	int i = 1;
	for (i = 1; i < db.num_of_songs; i++){
		this->buttons[i]->draw(this->buttons[i]);
	}
}

void drawPlaylistPanel(struct Frame* this){
	int i = 1;
	for (i = 1; i < db.num_of_lists; i++){
		this->buttons[i]->draw(this->buttons[i]);
	}
}

void clearSongPanel(){
	int y = SONG_Y_POSITION;
	int i = 0;
	for (i = 0; i < 15; i++){
		alt_up_char_buffer_string(char_buffer, "               ", 61, y);
		y += 3;
	}
}
void displayLoadingScreenVGA(){
	struct Image* testImg;
	while ((testImg = loadSDImage("TEST.BMP")) == NULL);
	draw(35, 35, testImg);
	killImage(testImg);
	alt_up_char_buffer_clear(char_buffer);
	alt_up_char_buffer_string(char_buffer, "Initialization Completed", 27, 5);
}



