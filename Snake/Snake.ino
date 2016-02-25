/*
 Name:		Snake.ino
 Created:	2/19/2016 6:20:04 PM
 Author:	Lenovo
 Editor:	http://www.visualmicro.com
*/

#include <SnakeLib.h>
#include <Thread.h>

SnakeStruct *snake;
Thread *myThread;
void movimiento();

void setup() {

	snake = new SnakeStruct();
	myThread = new Thread();


	for (int thisPin = 0; thisPin < 8; thisPin++) {
		// initialize the output pins:
		pinMode(snake->col[thisPin], OUTPUT);
		pinMode(snake->row[thisPin], OUTPUT);
		// take the col pins (i.e. the cathodes) high to ensure that
		// the LEDS are off:
		digitalWrite(snake->col[thisPin], HIGH);
	}

	// initialize the pixel matrix:
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			snake->pixels[x][y] = HIGH;
		}
	}
	
	//snake->timer->initialize(250000);
	//snake->timer->attachInterrupt(SnakeStruct::moverseStatic);
	//myThread->onRun();

	myThread->onRun(movimiento);
	myThread->setInterval(500);

	Serial.begin(9600);
	//interrupts();

}

void loop() {
	if (myThread->shouldRun())
		myThread->run();

	snake->readSensors();
	// draw the screen:

	if (!snake->lose) {
		snake->refreshScreen();
		//change direction
		snake->changeDirecction();
	}
	//else {
		//Añadir algun mensaje si se desea
		//delay(200);
	//}
}

void movimiento() {
	if (!snake->lose){
		snake->moverse();
	}
}

