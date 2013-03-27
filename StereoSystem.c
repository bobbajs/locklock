
#include "Global.h"

bool loadSDCard(alt_up_sd_card_dev* device) {
	if((device = alt_up_sd_card_open_dev("/dev/SD_Card")) != NULL) {
		if (alt_up_sd_card_is_Present()) {
			printf("Card connected.\n");
			if (alt_up_sd_card_is_FAT16()) {
				printf("FAT16 file system detected.\n");
				return true;
			} else {
				printf("Unknown file system.\n");
			}
		}
	}
	return false;
}

int main()
{
	//SD device initialization
	alt_up_sd_card_dev *device_reference = NULL;
	while(!loadSDCard(device_reference)) {
		printf("SD card is not connected.\n");
	}

	initVGA();
	initAudioDeviceController();
	initSoundMixer();

	struct CmdScheduler* scheduler = initCmdScheduler();

	//Serial device initialization
	com = initRS232(scheduler);

	initPushKeyController();

	initDatabase();
	initMemory();
	//sync database
	//dBTester();
	update();

	alt_up_char_buffer_clear(char_buffer);
	struct Cursor* cursor = initCursor(10, 200);
	//Test VGA Output
	struct Image* testImg;
	struct Image* testImg1;
	//while((testImg = loadSDImage("TEST.BMP")) == NULL);
	//while((testImg1 = loadSDImage("ART3.BMP")) == NULL);
	//draw(35, 35, testImg);
	//draw(0, 20, testImg1);
	//killImage(testImg);
	//alt_up_char_buffer_string(char_buffer, "Initialization Completed", 27, 5);
	//graphicTester();
	//Test End

	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_char_buffer_clear(char_buffer);
	struct Frame* mainFrame = initMainFrame();
	mainFrame->drawFrame(mainFrame);

	int i = 2;
	int count = 0;
	playSong(db.songs[1], 100, 0, 0);
	updateMixer();
	enableAudioDeviceController();


	float x = getCursorX(cursor);
	while(1) {
		count++;
		cmdProcessing(scheduler);
		updateMixer();

		//compareRange2(cursor->super->r, mainFrame->elements[0]->buttons[1]->range, 1);
		//compareRange2(cursor->super->r, mainFrame->elements[0]->buttons[0]->range, 0);
		//if (count % 150000 == 0){
		checkTxtBtnCollision(cursor, mainFrame->elements[0]->buttons[0]);
		checkTxtBtnCollision(cursor, mainFrame->elements[0]->buttons[1]);
		checkImgBtnCollision(cursor, mainFrame->elements[1]->buttons[0]);
		//}

		//while (x <= 310){
		updateCursor(cursor, (int)x, 200);
		x+=0.005;
		//}
		if(x >= 310)
		x = 0;

		//i = soundTester(i);


	}


	return 0;
}
