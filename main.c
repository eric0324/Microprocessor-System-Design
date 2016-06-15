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
	alt_up_char_buffer_dev *CHAR_BUFFER;
	CHAR_BUFFER = alt_up_char_buffer_open_dev("/dev/video_character_buffer_with_dma");
	init(CHAR_BUFFER);
    int line, column;

    alt_up_char_buffer_string(CHAR_BUFFER, "1",20,10);
    alt_up_char_buffer_string(CHAR_BUFFER, "2",30,10);
    alt_up_char_buffer_string(CHAR_BUFFER, "3",40,10);
    alt_up_char_buffer_string(CHAR_BUFFER, "4",50,10);
    alt_up_char_buffer_string(CHAR_BUFFER, "5",60,10);

    alt_up_char_buffer_string(CHAR_BUFFER, "1",10,15);
    alt_up_char_buffer_string(CHAR_BUFFER, "2",10,20);
    alt_up_char_buffer_string(CHAR_BUFFER, "3",10,25);
    alt_up_char_buffer_string(CHAR_BUFFER, "4",10,30);
    alt_up_char_buffer_string(CHAR_BUFFER, "5",10,35);

	for(line=0 ; line < 5 ; line++ ){
		for(column=0 ; column < 5 ; column++ ){
			if(board[line][column]==-1){
				alt_up_char_buffer_string(CHAR_BUFFER, "~",(20+10*line),(15+5*column));
			}else if(board[line][column]==0){
				alt_up_char_buffer_string(CHAR_BUFFER, "*",(20+10*line),(15+5*column));
			}else if(board[line][column]==1){
				alt_up_char_buffer_string(CHAR_BUFFER, "X",(20+10*line),(15+5*column));
			}

		}
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
	alt_up_char_buffer_dev *CHAR_BUFFER;
	CHAR_BUFFER = alt_up_char_buffer_open_dev("/dev/video_character_buffer_with_dma");
	int sum =0;
	alt_up_char_buffer_string(CHAR_BUFFER, "Luffy, Tell me x - axis?",10,40);
	usleep(2500000);
	do{
		shot[0] = SW_change(SW_get());
	}while(shot[0]>20);
	shot[0]--;

	alt_up_char_buffer_string(CHAR_BUFFER, "Okay!!!",10,42);

	alt_up_char_buffer_string(CHAR_BUFFER, "Tell me  y - axis?",10,44);
	usleep(2500000);
	do{
		shot[1] = SW_change(SW_get());
	}while(shot[1]>20);
	shot[1]--;
	alt_up_char_buffer_string(CHAR_BUFFER, "Attack!!!",10,46);
	usleep(2500000);

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

	char titleRow1[100]="   _____ ______           __          __     _____  ";
	char titleRow2[100]="  / ____|  ____|   /\\     \\ \\        / /\\   |  __ \\ ";
	char titleRow3[100]=" | (___ | |__     /  \\     \\ \\  /\\  / /  \\  | |__) |";
	char titleRow4[100]="  \\___ \\|  __|   / /\\ \\     \\ \\/  \\/ / /\\ \\ |  _  / ";
	char titleRow5[100]="  ____) | |____ / ____ \\     \\  /\\  / ____ \\| | \\ \\ ";
	char titleRow6[100]=" |_____/|______/_/    \\_\\     \\/  \\/_/    \\_\\_|  \\_\\";

	char talkT[100]=" --------------------------------------------------------";
	char talkM[100]="|                                                        |";
	char talkB[100]=" --------------------------------------------------------";

	char win1[100]="  ____                        ";
	char win2[100]=" |  _ \\                       ";
	char win3[100]=" | |_) | ___   ___  _ __ ___  ";
	char win4[100]=" |  _ < / _ \\ / _ \\| '_ ` _ \\ ";
	char win5[100]=" | |_) | (_) | (_) | | | | | |";
	char win6[100]=" |____/ \\___/ \\___/|_| |_| |_|";

	char lost1[100]="  _      ____   _____ _______ ";
	char lost2[100]=" | |    / __ \\ / ____|__   __|";
	char lost3[100]=" | |   | |  | | (___    | |   ";
	char lost4[100]=" | |   | |  | |\\___ \\   | |   ";
	char lost5[100]=" | |___| |__| |____) |  | |   ";
	char lost6[100]=" |______\\____/|_____/   |_|   ";

	char end1[100]="            _______ ____           ____  ______      ";
	char end2[100]="           |__   __/ __ \\         |  _ \\|  ____|   ";
	char end3[100]="              | | |  \\/ |        | |_) | |__            ";
	char end4[100]="              | | | |\\/| |        |  _ <|  __|            ";
	char end5[100]="              | | | //\\\\ |        | |_) | |____               ";
	char end6[100]="   _____ ____ |_|  \\____/___ _____|____/|______|______ _____  ";
	char end7[100]="  / ____/ __ \\| \\ | |__   __|_   _| \\ | | |  | |  ____|  __ \\ ";
	char end8[100]=" | |   | |  | |  \\| |  | |    | | |  \\| | |  | | |__  | |  | |";
	char end9[100]=" | |   | |  | | . ` |  | |    | | | . ` | |  | |  __| | |  | |";
	char end10[100]=" | |___| |__| | |\\  |  | |   _| |_| |\\  | |__| | |____| |__| |";
	char end11[100]="  \\_____\\____/|_| \\_|  |_|  |_____|_| \\_|\\____/|______|_____/ ";

	char gameover1[100]="   _____          __  __ ______ ";
	char gameover2[100]="  / ____|   /\\   |  \\/  |  ____|";
	char gameover3[100]=" | |  __   /  \\  | \\  / | |__   ";
	char gameover4[100]=" | | |_ | / /\\ \\ | |\\/| |  __|  ";
	char gameover5[100]=" | |__| |/ ____ \\| |  | | |____ ";
	char gameover6[100]="  \\_____/_/    \\_\\_|__|_|______|";
	char gameover7[100]="  / __ \\ \\    / /  ____|  __ \\  ";
	char gameover8[100]=" | |  | \\ \\  / /| |__  | |__) | ";
	char gameover9[100]=" | |  | |\\ \\/ / |  __| |  _  /  ";
	char gameover10[100]=" | |__| | \\  /  | |____| | \\ \\  ";
	char gameover11[100]="  \\____/   \\/   |______|_|  \\_\\ ";

	alt_up_char_buffer_string(CHAR_BUFFER,titleRow1 ,14,12);
	alt_up_char_buffer_string(CHAR_BUFFER,titleRow2 ,14,14);
	alt_up_char_buffer_string(CHAR_BUFFER,titleRow3 ,14,16);
	alt_up_char_buffer_string(CHAR_BUFFER,titleRow4 ,14,18);
	alt_up_char_buffer_string(CHAR_BUFFER,titleRow5 ,14,20);
	alt_up_char_buffer_string(CHAR_BUFFER,titleRow6 ,14,22);

	alt_up_char_buffer_string(CHAR_BUFFER, "Luffy, Select the location you want to enter",18,28);
	alt_up_char_buffer_string(CHAR_BUFFER, "(1) New World - If you get a new world, you can become the One Piece.",5,32);
	alt_up_char_buffer_string(CHAR_BUFFER, "(2) Grand Line - The world's greatest ocean.",5,34);
	alt_up_char_buffer_string(CHAR_BUFFER, "(3) Red Line - It is divided into two parts of the world's oceans.",5,36);
	alt_up_char_buffer_string(CHAR_BUFFER, "(4) East Blue - weakest sea.",5,38);

	do{
	  difficulty = SW_change(SW_get());

	}while(difficulty>20);

	startBoard(board);
	startShips(ships);

	do{

	showBoard(board);
	giveShot(shot);
	attempts++;

	if(hitship(shot,ships)){
		init(CHAR_BUFFER);
		alt_up_char_buffer_string(CHAR_BUFFER,win1 ,16,8);
		alt_up_char_buffer_string(CHAR_BUFFER,win2 ,16,10);
		alt_up_char_buffer_string(CHAR_BUFFER,win3 ,16,12);
		alt_up_char_buffer_string(CHAR_BUFFER,win4 ,16,13);
		alt_up_char_buffer_string(CHAR_BUFFER,win5 ,16,14);
		alt_up_char_buffer_string(CHAR_BUFFER,win6 ,16,16);

		if((hits == 1) && (difficulty==4)){
			alt_up_char_buffer_string(CHAR_BUFFER,talkT ,10,18);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,20);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Zoro                                                   |",10,22);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,24);
			alt_up_char_buffer_string(CHAR_BUFFER,"| I'm going to be the world's greatest swordsman!        |",10,26);
			alt_up_char_buffer_string(CHAR_BUFFER,"| All I have left is my destiny!                         |",10,28);
			alt_up_char_buffer_string(CHAR_BUFFER,"| My name may be infamous......                          |",10,30);
			alt_up_char_buffer_string(CHAR_BUFFER,"| but it's gonna shake the world!!!                      |",10,32);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,34);
			alt_up_char_buffer_string(CHAR_BUFFER,talkB ,10,36);
		}else if((hits == 1) && (difficulty==3)){
			alt_up_char_buffer_string(CHAR_BUFFER,talkT ,10,18);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,20);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Nefertari Vivi                                         |",10,22);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,24);
			alt_up_char_buffer_string(CHAR_BUFFER,"| At our next meeting ...... ......                      |",10,28);
			alt_up_char_buffer_string(CHAR_BUFFER,"| you still want to call me friend?.                     |",10,30);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,32);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,34);
			alt_up_char_buffer_string(CHAR_BUFFER,talkB ,10,36);
		}else if((hits == 1) && (difficulty==2)){
			alt_up_char_buffer_string(CHAR_BUFFER,talkT ,10,18);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,20);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Brook                                                  |",10,22);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,24);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Can I appreciate your   panties?                       |",10,26);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,28);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,30);
			alt_up_char_buffer_string(CHAR_BUFFER,talkB ,10,32);
		}else if((hits == 1) && (difficulty==1)){
			alt_up_char_buffer_string(CHAR_BUFFER,talkT ,10,18);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,20);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Sanji                                                  |",10,22);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,24);
			alt_up_char_buffer_string(CHAR_BUFFER,"| If you are a man!                                      |",10,26);
			alt_up_char_buffer_string(CHAR_BUFFER,"| You need to forgive the woman's lies!                  |",10,28);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,30);
			alt_up_char_buffer_string(CHAR_BUFFER,talkB ,10,32);
		}else{
			alt_up_char_buffer_string(CHAR_BUFFER,talkT ,10,18);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,20);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Luffy                                                  |",10,22);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,24);
			alt_up_char_buffer_string(CHAR_BUFFER,"| I'm Luffy!                                             |",10,26);
			alt_up_char_buffer_string(CHAR_BUFFER,"| The Man Who Will Become Pirate King!!                  |",10,28);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,30);
			alt_up_char_buffer_string(CHAR_BUFFER,talkB ,10,32);
		}

		usleep(9000000);
		hits++;
	}

	if(pc(difficulty)){
		init(CHAR_BUFFER);
		alt_up_char_buffer_string(CHAR_BUFFER,lost1 ,16,8);
		alt_up_char_buffer_string(CHAR_BUFFER,lost2 ,16,10);
		alt_up_char_buffer_string(CHAR_BUFFER,lost3 ,16,12);
		alt_up_char_buffer_string(CHAR_BUFFER,lost4 ,16,13);
		alt_up_char_buffer_string(CHAR_BUFFER,lost5 ,16,14);
		alt_up_char_buffer_string(CHAR_BUFFER,lost6 ,16,16);

		if((pcHints == 1) && (difficulty==4)){
			alt_up_char_buffer_string(CHAR_BUFFER,talkT ,10,18);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,20);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Zoro                                                   |",10,22);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,24);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Behind the sword, swordsmen shame!                     |",10,26);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,28);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,30);
			alt_up_char_buffer_string(CHAR_BUFFER,talkB ,10,32);
		}else if((pcHints == 1) && (difficulty==3)){
			alt_up_char_buffer_string(CHAR_BUFFER,talkT ,10,18);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,20);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Chopper                                                |",10,22);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,24);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Doctors! Doctors!                                      |",10,26);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Where is the doctor!?                                  |",10,28);
			alt_up_char_buffer_string(CHAR_BUFFER,"|  Yes I am a doctor!                                    |",10,30);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,32);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,34);
			alt_up_char_buffer_string(CHAR_BUFFER,talkB ,10,36);
		}else if((pcHints == 1) && (difficulty==2)){
			alt_up_char_buffer_string(CHAR_BUFFER,talkT ,10,18);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,20);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Usopp                                                  |",10,22);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,24);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Just live                                              |",10,26);
			alt_up_char_buffer_string(CHAR_BUFFER,"| There will be a lot of things happen to make you happy |",10,28);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,30);
			alt_up_char_buffer_string(CHAR_BUFFER,talkB ,10,32);
		}else if((pcHints == 1) && (difficulty==1)){
			alt_up_char_buffer_string(CHAR_BUFFER,talkT ,10,18);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,20);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Usopp                                                  |",10,22);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,24);
			alt_up_char_buffer_string(CHAR_BUFFER,"| As a man, there is not time to escape!                 |",10,26);
			alt_up_char_buffer_string(CHAR_BUFFER,"| That is a dream made fun of by others!                 |",10,28);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,30);
			alt_up_char_buffer_string(CHAR_BUFFER,talkB ,10,32);
		}else{
			alt_up_char_buffer_string(CHAR_BUFFER,talkT ,10,18);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,20);
			alt_up_char_buffer_string(CHAR_BUFFER,"| Luffy                                                  |",10,22);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,24);
			alt_up_char_buffer_string(CHAR_BUFFER,"| I'm Luffy!                                             |",10,26);
			alt_up_char_buffer_string(CHAR_BUFFER,"| The Man Who Will Become Pirate King!!                  |",10,28);
			alt_up_char_buffer_string(CHAR_BUFFER,talkM ,10,30);
			alt_up_char_buffer_string(CHAR_BUFFER,talkB ,10,32);
		}

		usleep(9000000);
		pcHints++;
	}

	changeBoard(shot,ships,board);

	if (pcHints == 3)
	  break;

	}while(hits!=3);

	if (hits==3) {
		init(CHAR_BUFFER);
		alt_up_char_buffer_string(CHAR_BUFFER,end1 ,10,16);
		alt_up_char_buffer_string(CHAR_BUFFER,end2 ,10,18);
		alt_up_char_buffer_string(CHAR_BUFFER,end3 ,10,20);
		alt_up_char_buffer_string(CHAR_BUFFER,end4 ,10,22);
		alt_up_char_buffer_string(CHAR_BUFFER,end5 ,10,24);
		alt_up_char_buffer_string(CHAR_BUFFER,end6 ,10,26);
		alt_up_char_buffer_string(CHAR_BUFFER,end7 ,10,28);
		alt_up_char_buffer_string(CHAR_BUFFER,end8 ,10,30);
		alt_up_char_buffer_string(CHAR_BUFFER,end9 ,10,32);
		alt_up_char_buffer_string(CHAR_BUFFER,end10,10,34);
		alt_up_char_buffer_string(CHAR_BUFFER,end11,10,36);
	}else{
		init(CHAR_BUFFER);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover1 ,15,16);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover2 ,15,18);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover3 ,15,20);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover4 ,15,22);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover5 ,15,24);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover6 ,15,26);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover7 ,15,28);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover8 ,15,30);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover9 ,15,32);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover10,15,34);
		alt_up_char_buffer_string(CHAR_BUFFER,gameover11,15,36);
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
