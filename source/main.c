#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <3ds.h>

enum SELECTION {
	rock,
	paper,
	scissors
};
typedef enum SELECTION SELECTION;

SELECTION mySelection = rock;
SELECTION cpSelection;

int tieCount = 0;
int winCount = 0;
int loseCount = 0;

void printMenu(SELECTION mySelection) {
	if (mySelection == rock)
		printf("%s\n", "> rock");
	else if (mySelection != rock)
		printf("%s\n", "  rock");
	if (mySelection == paper)
		printf("%s\n", "> paper");
	else if (mySelection != paper)
		printf("%s\n", "  paper");
	if (mySelection == scissors)
		printf("%s\n", "> scissors");
	else if (mySelection != scissors)
		printf("%s\n", "  scissors");
	printf("\n");
}

void printScores() {
	printf("\x1b[7;0HTied: %d Won: %d Lost: %d\n\n", tieCount, winCount, loseCount);
}

void setup() {
	time_t t;
	srand((unsigned) time(&t));
}

void changeSelection(u32 key){
	if ((key & KEY_DUP) && (mySelection > 0))
		mySelection--;
	else if ((key & KEY_DDOWN) && (mySelection < 2))
		mySelection++;
}

void compSelection() {
	int selection = rand() % 3;
	cpSelection = selection;
}

void play() {
	printScores();
	compSelection();
	printf("\x1b[9;0H");// move cursor to "opponent's choice"
	printf("\x1B[0K"); // clears line
	if ( mySelection == cpSelection ) {
		printf("\n");
		tieCount++;
		printf("%s\n", "Tied!\x1B[0K");//prints and clears rest of line
	}
	else if ( mySelection == rock ) {
		if ( cpSelection == scissors ) {
			printf("Your opponent chose scissors.\n");
			winCount++;
			printf("%s\n", "You Won!");
		}else {
			printf("Your opponent chose paper.\n");
			loseCount++;
			printf("%s\n", "You Lost!");
		}
	}
	else if ( mySelection == paper ){
		if ( cpSelection == rock ) {
			printf("Your opponent chose rock.\n");
			winCount++;
			printf("%s\n", "You Won!");
		}else{
			printf("Your opponent chose scissors.\n");
			loseCount++;
			printf("%s\n", "You Lost!");
		}
	}
	else if ( mySelection == scissors ) {
		if ( cpSelection == paper ) {
			printf("Your opponent chose paper.\n");
			winCount++;
			printf("%s\n", "You Won!");
		}else {
			printf("Your opponent chose rock.\n");
			loseCount++;
			printf("%s\n", "You Lost!");
		}
	}
}

int main()
{
	gfxInitDefault();
	consoleInit(GFX_TOP,NULL);

	setup();

	while (aptMainLoop()){
		gspWaitForVBlank();
		hidScanInput();

		printf("\x1b[1;15HRock Paper Scissors!\n\n");
		printMenu(mySelection);
		printScores();

		u32 kDown = hidKeysDown();

		if (kDown & KEY_START)
			break;
		else if ((kDown & KEY_DUP) || (kDown & KEY_DDOWN))
			changeSelection(kDown);
		else if (kDown & KEY_A)
			play();

		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}
