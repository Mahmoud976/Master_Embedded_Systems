
#include"driver.h"

const int Threshold = 20;
volatile uint32_t Pressure_Val = 10;
int main (){


	GPIO_INITIALIZATION();

	while (1)
	{
		Pressure_Val = getPressureVal();

		if (Pressure_Val >= Threshold)
		{
			Set_Alarm_actuator(0);
			Delay(50000);
			Set_Alarm_actuator(1);
		}
		else
		{
			Set_Alarm_actuator(1);
		}
	}

}
