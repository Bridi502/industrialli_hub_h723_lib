#include "industrialli_anlgInHub.h"

void industrialli_analogInputsHub::begin(void)
{ // inicia as entradas analogicas e seta para a leitura de 0-10V

    pinMode(ADC_01, INPUT);
    pinMode(ADC_02, INPUT);
    pinMode(ADC_03, INPUT);
    pinMode(ADC_04, INPUT);

    pinMode(ANLG_SEL_01, OUTPUT);
    pinMode(ANLG_SEL_02, OUTPUT);
    pinMode(ANLG_SEL_03, OUTPUT);
    pinMode(ANLG_SEL_04, OUTPUT);
    // LOW - 0-10V
    // HIGH - 0-20mA
    digitalWrite(ANLG_SEL_01, LOW);
    digitalWrite(ANLG_SEL_02, LOW);
    digitalWrite(ANLG_SEL_03, LOW);
    digitalWrite(ANLG_SEL_04, LOW);

    analogReadResolution(12);
    getIntParamVREF();
}
void industrialli_analogInputsHub::setReadMode(uint8_t anlgPin, uint8_t readMode)
{ // escolhe o tipo de leitura
    // 1 - 0-20mA
    // 0 - 0-10V

    _anlgPin = anlgPin;
    _readMode = readMode;

    if (_anlgPin == 0)
    {
        if (_readMode == 1)
        {
            digitalWrite(ANLG_SEL_01, HIGH);
            ledsCtrl.ledOn(0);
            //ledsCtrl.ledsUpdate();

        }
        else
        {
            digitalWrite(ANLG_SEL_01, LOW);
            ledsCtrl.ledOff(0);
            //ledsCtrl.ledsUpdate();
        }
    }

    else if (_anlgPin == 1)
    {
        if (_readMode == 1)
        {
            digitalWrite(ANLG_SEL_02, HIGH);
            ledsCtrl.ledOn(1);
            //ledsCtrl.ledsUpdate();
        }
        else
        {
            digitalWrite(ANLG_SEL_02, LOW);
            ledsCtrl.ledOff(1);
            //ledsCtrl.ledsUpdate();
        }
    }

    else if (_anlgPin == 2)
    {
        if (_readMode == 1)
        {
            digitalWrite(ANLG_SEL_03, HIGH);
            ledsCtrl.ledOn(2);
            //ledsCtrl.ledsUpdate();
        }
        else
        {
            digitalWrite(ANLG_SEL_03, LOW);
            ledsCtrl.ledOff(2);
            //ledsCtrl.ledsUpdate();
        }
    }
    else if (_anlgPin == 3)
    {
        if (_readMode == 1)
        {
            digitalWrite(ANLG_SEL_04, HIGH);
            ledsCtrl.ledOn(3);
            //ledsCtrl.ledsUpdate();
        }
        else
        {
            digitalWrite(ANLG_SEL_04, LOW);
            ledsCtrl.ledOff(3);
            //ledsCtrl.ledsUpdate();
        }
    }
}
int industrialli_analogInputsHub::readRawInput(uint8_t anlgPin)
{ // seta a leitura para 0-10V e retorna o valor da entrada

    _anlgPin = anlgPin;
    // analogReadResolution(12);

    if (_anlgPin == 0)
    {
        _VIN_RAW[0] = analogRead(ADC_01);
        _pin = 0;
    }

    else if (_anlgPin == 1)
    {
        _VIN_RAW[1] = analogRead(ADC_02);
        _pin = 1;
    }

    else if (_anlgPin == 2)
    {
        _VIN_RAW[2] = analogRead(ADC_03);
        _pin = 2;
    }
    else if (_anlgPin == 3)
    {
        _VIN_RAW[3] = analogRead(ADC_04);
        _pin = 3;
    }

    return _VIN_RAW[_pin];
}
int industrialli_analogInputsHub::getVRefRaw(void)
{
    // obtem o valor da leitura da tensao de referencia interna
    _VREF_RAW = analogRead(AVREF);
    return _VREF_RAW;
}
double industrialli_analogInputsHub::getVIN(uint8_t anlgPin)
{
    // obtem a tensao de saida na entrada selecionada
    _anlgPin = anlgPin;
    _VDDA = (_VREF_INTERNAL * _bitsADC) / getVRefRaw();
    _VIN[_anlgPin] = _VDDA / _bitsADC * readRawInput(_anlgPin);
    return _VIN[_anlgPin];
}
double industrialli_analogInputsHub::get010V(uint8_t anlgPin)
{
    // obtem a tensao de 0-10V na entrada selecionada

    _anlgPin = anlgPin;
    _VDDA = (_VREF_INTERNAL * _bitsADC) / getVRefRaw();
    //_VIN010[_anlgPin] = getVIN(_anlgPin) * (10.00 / 3.30);
    _VIN010[_anlgPin] = getVIN(_anlgPin) * (10.00 / _VDDA);
    return _VIN010[_anlgPin];
}
double industrialli_analogInputsHub::get020mA(uint8_t anlgPin)
{
    // obtem  a corrente de 0-20mA na entrada selecionada
    _anlgPin = anlgPin;
    _VDDA = (_VREF_INTERNAL * _bitsADC) / getVRefRaw();
    _AIN020[_anlgPin] = getVIN(_anlgPin) * (20.00 / _VDDA);
    //_AIN020[_anlgPin] = getVIN(_anlgPin) * (20.00 /3.30);
    return _AIN020[_anlgPin];
}
bool industrialli_analogInputsHub::alarm020mA(uint8_t anlgPin, float threshold)
{
    // alerta de falha para leitura 0-20mA
    _anlgPin = anlgPin;
    if (get020mA(_anlgPin) < threshold)
    {
        ledsCtrl.ledOn(31);
        _alarm = true;
    }
    else
    {
        ledsCtrl.ledOff(31);
        _alarm = false;
    }
    return _alarm;
}
int industrialli_analogInputsHub::getIntParamVREF(void){
    _VREFINT = *((unsigned short *)0x1FF1E860); // VDDA = 3.3V@30degreeC
    _VREF_INTERNAL = _VREFINT;
    
    return _VREFINT;
}
int industrialli_analogInputsHub::getIntParamTSCAL1(void){
    
    _TS_CAL1 = *((unsigned short *)0x1FF1E820); //TEMP_RAW1 = 3.3V@30degreeC
   
    return _TS_CAL1;
}
int industrialli_analogInputsHub::getIntParamTSCAL2(void){
    
    _TS_CAL2 = *((unsigned short *)0x1FF1E840); //TEMP_RAW2 = 3.3V@130degreeC
    return _TS_CAL2;
}