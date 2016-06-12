#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "io.h"
#include "alt_types.h"
int SW_get();
int Btn_get();

int main(){
	int sw_num;
	int num_stack[10];
	int stack_index = -1;
	int i;
	int btn_sel;

	while(1){
		sw_num = SW_get();

		printf("%d", sw_num);

		//for(i =0;i>1000000;i++){};
		usleep(300000);
	}
	return 0;
}



int SW_get(){
	return IORD(PIO_SW_BASE, 0) & 0x000003ff;
}


int Btn_get(){
	return IORD(PIO_BTN0_BASE, 0);
}
