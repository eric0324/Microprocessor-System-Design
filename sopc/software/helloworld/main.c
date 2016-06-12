/*
 * main.c
 *
 *  Created on: 2016/6/12
 *      Author: JH
 */

#include "io.h"
#include "alt_types.h"
#include "system.h"

void sw_get_command(alt_u32 sw_base, int*prd){
	*prd = IORD(sw_base, 0) & 0x000003ff;
}

int main(){
	int prd;
	while(1){
		sw_get_command(PIO_SW_BASE, &prd);
		printf("%d", &prd);

	}
}
