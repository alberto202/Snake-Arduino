/*
 Name:		SnakeLib.h
 Created:	2/19/2016 6:20:04 PM
 Author:	Lenovo
 Editor:	http://www.visualmicro.com
*/

#ifndef _SnakeLib_h
#define _SnakeLib_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SnakeStruct {
	// 2-dimensional array of row pin numbers:
public:		const int row[8] = {
		2, 7, 19, 5, 13, 18, 12, 16
	};

	// 2-dimensional array of column pin numbers:
public:		const int col[8] = {
		6, 11, 10, 3, 17, 4, 8, 9
	};

	// 2-dimensional array of pixels:
public: 	int pixels[8][8];

	// cursor position:
public: 	int	x;
public: 	int y;
public: 	int prevx;
public: 	int prevy;
public:		bool lose;

public: 	int* serpientex;
public: 	int* serpientey;
public: 	long bolaX;
public: 	long bolaY;
public: 	int direccion; //0 abajo, 1 derecha, 2 arriba, 3 izquierda
public: 	float velocidad;
public:		int totalBolas;

	SnakeStruct();
	SnakeStruct(SnakeStruct *copy);
	void readSensors(void);
	void refreshScreen(void);
	void changeDirecction(void);
	void* moverse(void);
	void comprobarBola(void);
	void comprobarSerpiente(void);
};

#endif

