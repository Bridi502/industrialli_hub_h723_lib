#ifndef INDUSTRIALLI_PWRSTATUSHUB_H
#define INDUSTRIALLI_PWRSTATUSHUB_H

#include <Arduino.h>
#include <stdlib.h>
#include <SPI.h>

#define PGOOD1 PC2_C
#define PGOOD2 PC3_C

class industrialli_pwrStatusHub
{
private:
    
public:
void begin(); //inicia os pinos
bool statusPGOOD1(); //retorna verdadeiro para operacao normal do trilho de 3.3V
bool statusPGOOD2(); //retorna verdadeiro para operacao normal do trilho de 5.0V
void test(); //Serial print dos status PGOOD1 e PGOOD2
};



#endif