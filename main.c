#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "io.h"
#include "alt_types.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
int SW_get();
int Btn_get();
void init(alt_up_char_buffer_dev *);
void startBoard(int board[][5])
{
    int line, column;
        for(line=0 ; line < 5 ; line++ )
            for(column=0 ; column < 5 ; column++ )
                board[line][column]=-1;
}

void showBoard(int board[][5])
{

    int line, column;

        printf("\t1 \t2 \t3 \t4 \t5");
        printf("\n");

        for(line=0 ; line < 5 ; line++ ){
            printf("%d",line+1);
            for(column=0 ; column < 5 ; column++ ){
                if(board[line][column]==-1){
                    printf("\t~");
                }else if(board[line][column]==0){
                    printf("\t*");
                }else if(board[line][column]==1){
                    printf("\tX");
                }

            }
            printf("\n");
        }

    }

void startShips(int ships[][2]){
        srand(time(NULL));
        int ship, last;

        for(ship=0 ; ship < 3 ; ship++){
            ships[ship][0]= rand()%5;
            ships[ship][1]= rand()%5;

            //let's check if this shot was not tried
            //if it was, just get out of the 'do while' loop when draws a pair that was not tried
            for(last=0 ; last < ship ; last++){
                if( (ships[ship][0] == ships[last][0])&&(ships[ship][1] == ships[last][1]) )
                    do{
                        ships[ship][0]= rand()%5;
                        ships[ship][1]= rand()%5;
                    }while( (ships[ship][0] == ships[last][0])&&(ships[ship][1] == ships[last][1]) );
            }

        }
    }

void giveShot(int shot[2])
{
		int sum =0;
		 printf("Column?\n");
		 usleep(5000000);
        do{
        	shot[0] = SW_change(SW_get());
        }while(shot[0]>20);
        shot[0]--;

        printf("Yes, sir\n");

        usleep(500000);

        printf("Column?\n");
        do{
        	shot[1] = SW_change(SW_get());
        }while(shot[1]>20);
        shot[1]--;
        printf("Yes, sir\n");

        usleep(500000);

}

int hitship(int shot[2], int ships[][2])
{
    int ship;

        for(ship=0 ; ship < 3 ; ship++){
            if( shot[0]==ships[ship][0] && shot[1]==ships[ship][1]){
                return 1;
            }
        }
        return 0;
    }


void changeBoard(int shot[2], int ships[][2], int board[][5]){
        if(hitship(shot,ships))
            board[shot[0]][shot[1]]=1;
        else
            board[shot[0]][shot[1]]=0;
    }

int  pc(int difficulty){
  int pcHint = (rand()%100) + 1;
  if (difficulty == 1) {
    if(pcHint > 25)
      return 1;
    else
      return 0;
  }else if(difficulty == 2){
    if(pcHint > 50)
      return 1;
    else
      return 0;
  }else if(difficulty == 3){
    if(pcHint > 75)
      return 1;
    else
      return 0;
  }else{
    if(pcHint > 90)
      return 1;
    else
      return 0;
  }
}

int main() {
	alt_up_char_buffer_dev *CHAR_BUFFER;
	CHAR_BUFFER = alt_up_char_buffer_open_dev("/dev/video_character_buffer_with_dma");
	init(CHAR_BUFFER);

	int difficulty = 0;
	int board[5][5];
	int ships[3][2];
	int shot[2];
	int attempts = 0, hits = 0, pcHints = 0;

	char titleRow1[100]="  ______ ____ _____    __  _  _______ _______ ";
	char titleRow2[100]=" /  ___// __ \\\\__  \\   \\ \\/ \\/ /\\__  \\\\_  __ \\";
	char titleRow3[100]=" \\___ \\\\  ___/ / __ \\_  \\     /  / __ \\|  | \\/";
	char titleRow4[100]="/____  >\\___  >____  /   \\/\\_/  (____  /__|  ";
	char titleRow5[100]="     \\/     \\/     \\/                \\/       ";


	alt_up_char_buffer_string(CHAR_BUFFER,titleRow1 ,16,12);
	alt_up_char_buffer_string(CHAR_BUFFER,titleRow2 ,16,14);
	alt_up_char_buffer_string(CHAR_BUFFER,titleRow3 ,16,16);
	alt_up_char_buffer_string(CHAR_BUFFER,titleRow4 ,16,18);
	alt_up_char_buffer_string(CHAR_BUFFER,titleRow5 ,16,20);

	alt_up_char_buffer_string(CHAR_BUFFER, "Luffy, Select the waters you want to enter",20,28);
	alt_up_char_buffer_string(CHAR_BUFFER, "(1) New World - If you get a new world, you can become the One Piece.",5,32);
	alt_up_char_buffer_string(CHAR_BUFFER, "(2) Grand Line - The world's greatest ocean.",5,34);
	alt_up_char_buffer_string(CHAR_BUFFER, "(3) Red Line - It is divided into two parts of the world's oceans.",5,36);
	alt_up_char_buffer_string(CHAR_BUFFER, "(4) East Blue - weakest sea.",5,38);

	do{
	  difficulty = SW_change(SW_get());

	}while(difficulty>20);

	startBoard(board);
	startShips(ships);

	printf("\n");

	do{
	printf("\n\n\n\n\n\n");
	showBoard(board);
	giveShot(shot);
	attempts++;

	if(hitship(shot,ships)){
		printf("You hit a ship with the shot (%d,%d)\n",shot[0]+1,shot[1]+1);
		hits++;
	}

	if(pc(difficulty)){
	  pcHints++;
	  printf("Enemy attack you.");
	}

	changeBoard(shot,ships,board);

	if (pcHints == 3)
	  break;

	}while(hits!=3);

	if (hits==3) {
	printf("\n\n\nFinished game. You win");
	}else{
	printf("\n\n\nFinished game. You lost");
	}
}



int SW_get(){
	return IORD(PIO_SW_BASE, 0) & 0x000003ff;
}


int Btn_get(){
	return IORD(PIO_BTN0_BASE, 0);
}

int SW_change(int original){
	if(original == 1)
		return 1;
	else if(original == 2)
		return 2;
	else if(original == 4)
		return 3;
	else if(original == 8)
		return 4;
	else if(original == 16)
		return 5;
	else if(original == 32)
		return 6;
	else if(original == 64)
		return 7;
	else if(original == 128)
		return 8;
	else
		return 50;
}

void init(alt_up_char_buffer_dev * CHAR_BUFFER){
	alt_up_char_buffer_init(CHAR_BUFFER);
	alt_up_char_buffer_clear(CHAR_BUFFER);
}
