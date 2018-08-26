#ifndef OBJECTPARSEFSM_H
#define OBJECTPARSEFSM_H

#include"fsmCommon.h"
#include<iostream>
#include<string>
#include"JSONobject.h"

typedef enum { WAITING_FOR_OBJOPENER, WAITING_FOR_OPENING_QUOT, WAITING_FOR_CLOSING_QUOT,WAITING_FOR_COLON,\
WAITING_FOR_DATAOPENING_BRACKETS, WAITING_FOR_DATACLOSING_BRACKETS, WAITING_FOR_OBJCLOSER,END} stateType;
#define STATE_COUNT 8


typedef enum { OPENING_BRACKETS, CLOSING_BRACKETS,QUOTATION, COLON,OPENING_SQ_BRACKETS,CLOSING_SQ_BRACKETS} eventType;
#define EVENT_COUNT 4

typedef enum{OBJECT,ARRAY} parseMode;

class objectParseFSM
{
public:
	objectParseFSM(char* JSONstring); //constructor
	bool fsmStartParsing(void);//empieza a parsear un string en busca de objetos(esta es la fsm)
	error_t getError();  //devuelve una estructura error con el tipo de error ocurrido, NO_ERROR en caso de no haber error
	string getObjName(); //devuelve el nombre del objeto recibido
	JSONmember* getMemberArray(); //devuelve el puntero al arreglo de miembros
private:
	string name;//aqui se guardara el nombre del objeto, si es un arreglo se guarda "null"
	JSONmember* toSave; //arreglo que se crea dinamicamente con todos los miembros del objeto encontrados, se envia luego al programa principal
	error_t err;
	event_t event_;
	parseMode mode;

	/*rutinas de accion*/
	void setMode(void* mode);
	


	void fsmStep(event_t ev);//realiza un paso de la fsm
	event_t generateEvent(char* JSONstring);//genera a partir de los strings recibidos los eventos para la fsm
	void setError(int errorType, const char* errorString);//para facilitar el seteo del error dentro de la fsm
	cell_t fsmTable[STATE_COUNT][EVENT_COUNT] = { {} };




};

#endif