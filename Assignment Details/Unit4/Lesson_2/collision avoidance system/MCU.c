#include"MCU.h"

int distanc = 0;

void readDistance() {
	measureDistance();
	distanc = sendDistance();
}

void ControlMotor() {
	if (distanc < 50)
	{
		SetSpeed(0);

	}

	else
	{
		SetSpeed(30);
	}

}