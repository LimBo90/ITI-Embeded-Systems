/*
 * main.c
 *
 *  Created on: Apr 17, 2019
 *      Author: Administrator
 */

#define F_CPU 8000000
#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "HLCD_interface.h"
#include "HKPD_interface.h"

#define BUFFER_SIZE 20

u32 calculate(u8 cmd, u32 n1, u32 n2);
u8 getCmd(u8 snum[]);

int main(){
	HLCD_init();
	HKPD_init();
	u8 snum[BUFFER_SIZE] = {0};
	u32 res = 0;
	u8 cmd, prev_cmd = '=';

	while(1){
		cmd = getCmd(snum);
		if(cmd == '='){
			if(prev_cmd == '='){
				res = 1;
				HLCD_clearDisplay();
				snum[0] = '\0';
			}else{
				HLCD_clearDisplay();
				res = calculate(prev_cmd, res, atoi(snum));
				itoa(res, snum, 10);
				HLCD_writeStr(snum);
			}
		}else{
			if(prev_cmd = '=' && res == 0)
				res = atoi(snum);
			else
				res = calculate(cmd, res, atoi(snum));
		}
		prev_cmd = cmd;
	}
}

u8 getCmd(u8 snum[]){
	u8 c = NULL_CHARACTER;
	int i=0;
	while(1){
		c = HKPD_getKey();
		if(c == NULL_CHARACTER)
			continue;
		HLCD_writeData(c);
		if( c == '-' || c == '*' || c == '+' || c == '=')
			break;
		snum[i] = c;
		i++;
	}
	snum[i] = '\0';
	return c;
}

u32 calculate(u8 cmd, u32 n1, u32 n2){
	switch(cmd){
		case '+':
			return n1 + n2;
		case '-':
			return n1 - n2;
		case '*':
			return n1 * n2;
		default:
			return 0;
	}
}

