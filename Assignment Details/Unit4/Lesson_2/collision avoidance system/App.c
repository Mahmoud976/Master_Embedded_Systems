#include"App.h"

void C_A_system() {
	volatile int i;
	while (1) {
		printf("****************************************************\n");
		readDistance();
		ControlMotor();
		for (i = 0; i < 500000000; i++);
		printf("\n****************************************************\n");

	}
}