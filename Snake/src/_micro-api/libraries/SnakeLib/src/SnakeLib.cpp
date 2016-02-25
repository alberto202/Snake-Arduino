/*
 Name:		SnakeLib.cpp
 Created:	2/19/2016 6:20:04 PM
 Author:	Lenovo
 Editor:	http://www.visualmicro.com
*/

#include <SnakeLib.h>

SnakeStruct::SnakeStruct() {

	// cursor position:
	x = 4;
	y = 3;
	prevx = 4;
	prevy = 3;
	lose = 0;

	totalBolas = 1;
	serpientex = new int[totalBolas];
	serpientey = new int[totalBolas];

	serpientex[0] = 5;
	serpientey[0] = 5;

	randomSeed(millis());
	bolaX = (int)random(0, 7);
	bolaY = (int)random(0, 7);

	direccion = 0; //0 abajo, 1 derecha, 2 arriba, 3 izquierda
	velocidad = 1.0;

}

SnakeStruct::SnakeStruct(SnakeStruct *copy) {

	// cursor position:
	x = copy->x;
	y = copy->y;
	prevx = copy->prevx;
	prevy = copy->prevy;
	lose = copy->lose;
	totalBolas = copy->totalBolas;
	serpientex = copy->serpientex;
	serpientey = copy->serpientey;

	bolaX = copy->bolaX;
	bolaY = copy->bolaY;
	direccion = copy->direccion; //0 abajo, 1 derecha, 2 arriba, 3 izquierda
	velocidad = copy->velocidad;

}

void SnakeStruct::readSensors(void) {
	x = 7 - map(analogRead(A0), 0, 1023, 0, 7);
	y = map(analogRead(A1), 0, 1023, 0, 7);
}

void SnakeStruct::refreshScreen(void) {
	// iterate over the rows (anodes):
	pixels[bolaX][bolaY] = LOW;
		

	for (int thisRow = 0; thisRow < 8; thisRow++) {
		// take the row pin (anode) high:
		digitalWrite(row[thisRow], HIGH);
		//digitalWrite(row[aleX], HIGH);
		// iterate over the cols (cathodes):
		for (int thisCol = 0; thisCol < 8; thisCol++) {
			// get the state of the current pixel;
			int thisPixel = pixels[thisRow][thisCol];
			// when the row is HIGH and the col is LOW,
			// the LED where they meet turns on:
			digitalWrite(col[thisCol], thisPixel);
			// turn the pixel off:
			if (thisPixel == LOW) {
				digitalWrite(col[thisCol], HIGH);
				//digitalWrite(col[aleY], HIGH);
			}
		}
		// take the row pin low to turn off the whole row:
		digitalWrite(row[thisRow], LOW);
		//digitalWrite(row[aleX], LOW);
	}
}

void SnakeStruct::changeDirecction(void) {

	if (x != 4 || y != 3) { //posicion central del joystick
		if (prevx != x || prevy != y) {
			if (prevx > x && direccion != 0) {
				direccion = 2;
			}
			else if (prevx < x && direccion != 2) {
				direccion = 0;
			}
			else if (prevy > y && direccion != 1) {
				direccion = 3;
			}
			else if (prevy < y && direccion != 3) {
				direccion = 1;
			}
		}
		prevx = x;
		prevy = y;
	}
}

void* SnakeStruct::moverse(void) {
	
	for (int i = 0; i < totalBolas; i++) {
		pixels[serpientex[i]][serpientey[i]] = HIGH;
	}

	
	int swapx = serpientex[0];
	int swapy = serpientey[0];

	
	switch (direccion) {
	case 0:
		serpientex[0]++;
		if (serpientex[0] > 7) serpientex[0] = 0;
		break;
	case 1:
		serpientey[0]++;
		if (serpientey[0] > 7) serpientey[0] = 0;
		break;
	case 2:
		serpientex[0]--;
		if (serpientex[0] < 0) serpientex[0] = 7;
		break;
	case 3:
		serpientey[0]--;
		if (serpientey[0] < 0) serpientey[0] = 7;
		break;
	default:
		Serial.println("Algo a pasado con direccion");
		break;
	}

	for (int i = totalBolas -2; i >= 0 ; i--) {
		if (i != 0) {
			serpientex[i+1] = serpientex[i];
			serpientey[i+1] = serpientey[i];
		}
		else {
			serpientex[i + 1] = swapx;
			serpientey[i + 1] = swapy;
		}
	}
	
	comprobarSerpiente();
	comprobarBola();
	for (int i = 0; i < totalBolas; i++) {
		pixels[serpientex[i]][serpientey[i]] = LOW;
	}
}

void SnakeStruct::comprobarBola(void)
{
	int* copyx;
	int* copyy;
	if (serpientex[0] == bolaX && serpientey[0] == bolaY)
	{

		pixels[bolaX][bolaY] = HIGH;
		
		bolaX = random(0, 7);
		bolaY = random(0, 7);

		//pixels[bolaX][bolaY] = LOW;

		totalBolas++;
		if (totalBolas % 3 == 1)
		{
			velocidad *= 1.2;
			//timer->initialize(250000 / velocidad);
		}

		copyx = new int[totalBolas];
		copyy = new int[totalBolas];

		for (int i = 1; i < totalBolas; i++) {
			copyx[i] = serpientex[i-1];
			copyy[i] = serpientey[i-1];
		}

		delete[] serpientex;
		delete[] serpientey;

		serpientex = copyx;
		serpientey = copyy;
		
		serpientex[0] = serpientex[1];
		serpientey[0] = serpientey[1];
	}
}

void SnakeStruct::comprobarSerpiente(void) {
	if(totalBolas > 4){
		for (int i = 4; i < totalBolas; i++) {
			if (serpientex[i] == serpientex[0] && serpientey[i] == serpientey[0])
				lose = true;
		}
	}
	
}