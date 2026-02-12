#include "ultrasonic.h"

int distance = 0;

static void  randam() {
	int min = 40;
	int max = 60;
	// Formula: rand() % (max - min + 1) + min
	distance = (rand() % (max - min + 1)) + min;

}

void measureDistance(){
	randam();
	printf("the sensor read %d\n", distance);
}

int sendDistance(){
	printf("Send %d to the MCU",distance);
	return distance;
}