#include "time.h"

int time[3];
int date[3];
	
unsigned char askCMOS(int val){
	outb(0x70,val);
	return inb(0x71);
}

int* getTime(){
	time[0] =askCMOS(0x04);
	time[1]=askCMOS(0x02);
	time[2]=askCMOS(0x00);

 	int registerB = askCMOS(0x0B);
 
	if (!(registerB & 0x04)) {
		time[0] = (time[0] & 0x0F) + ((time[0] / 16) * 10);
		time[1] = (time[1] & 0x0F) + ((time[1] / 16) * 10);
		time[2] = ( (time[2] & 0x0F) + (((time[2] & 0x70) / 16) * 10) ) | (time[2] & 0x80);
	}
	if (!(registerB & 0x02) && (time[0] & 0x80)) {
		time[0] = ((time[0] & 0x7F) + 12) % 24;
	}
	return time;
}


int* getDate(){
	date[0] =askCMOS(0x07);
	date[1]=askCMOS(0x08);
	date[2]=askCMOS(0x09);
	int century = askCMOS(0x32);
	//if (century!=0) century=askCMOS(century);

 	int registerB = askCMOS(0x0B);
 
	if (!(registerB & 0x04)) {
		date[0] = (date[0] & 0x0F) + ((date[0] / 16) * 10);
		date[1] = (date[1] & 0x0F) + ((date[1] / 16) * 10);
		date[2] = ( (date[2] & 0x0F) + (((date[2] & 0x70) / 16) * 10) ) | (date[2] & 0x80);
		century = (century & 0x0F) + ((century / 16) * 10);
	}
	date[2]+=century*100;
	if (!(registerB & 0x02) && (date[0] & 0x80)) {
		date[0] = ((date[0] & 0x7F) + 12) % 24;
	}
	return date;
}
