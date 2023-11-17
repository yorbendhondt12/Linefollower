#include "SerialCommand.h"
#include "EEPROMAnything.h"

#define SerialPort Serial
#define Baudrate 115200

SerialCommand sCmd(SerialPort);
bool debug;
unsigned long previous, calculationTime;
const int sensor [] = {A5, A4, A3, A2, A1, A0};

uint16_t sensorValues[6];

struct param_t
{
  unsigned long cycleTime;
  int black[6];
  int white[6];
  /* andere parameters die in het eeprom geheugen moeten opgeslagen worden voeg je hier toe ... */
} params;

void setup()
{
  Serial.begin(Baudrate);
  
  sCmd.addCommand("set", onSet);
  sCmd.addCommand("debug", onDebug);
  sCmd.addCommand("calibrate", onCalibrate);
  sCmd.setDefaultHandler(onUnknownCommand);

  EEPROM_readAnything(0, params);

  pinMode(13, OUTPUT);
  Serial.println("ready");
}

void loop()
{
  sCmd.readSerial();
 
  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;

    int normalised [6];

    SerialPort.print("normalised values: ");
    for (int i = 0; i < 6; i++)
    {
      normalised[i] = map (analogRead(sensor[i]), params.black[i], params.white[i], 0, 1000);
      SerialPort.print(normalised[i]);
      SerialPort.print(" ");
    }
    SerialPort.println();

    }

  unsigned long difference = micros() - current;
  if (difference > calculationTime) calculationTime = difference;
}

void onUnknownCommand(char *command)
{
  SerialPort.print("unknown command: \"");
  SerialPort.print(command);
  SerialPort.println("\"");
}

void onSet()
{
  char* param = sCmd.next();
  char* value = sCmd.next();  
  
  if (strcmp(param, "cycle") == 0) params.cycleTime = atol(value);
  /* parameters een nieuwe waarde geven via het set commando doe je hier ... */
  
  EEPROM_writeAnything(0, params);
}

void onDebug()
{
  SerialPort.print("cycle time: ");
  SerialPort.println(params.cycleTime);
  
  SerialPort.print("black: ");
  for (int i = 0; i < 6; i++)
  {
      SerialPort.print(params.black[i]);
      SerialPort.print(" ");
  }

  SerialPort.print(" ");
  
  SerialPort.print("white: ");
  for (int i = 0; i < 6; i++)
  {
      SerialPort.print(params.white[i]);
      SerialPort.print(" ");
  }

  SerialPort.print(" ");
  SerialPort.print("calculation time: ");
  SerialPort.println(calculationTime);
  calculationTime = 0;
}

void onCalibrate()
{
  char* param = sCmd.next();

  if (strcmp(param, "black") ==0 )
  {
    SerialPort.print("start met zwart te kalibreren... ");
    for (int i = 0; i < 6; i++) params.black[i] = analogRead(sensor[i]);
    SerialPort.println("klaar");
  }
  else if (strcmp(param, "white") ==0 )
  {
    SerialPort.print("start met wit te kalibreren... ");    
    for (int i = 0; i < 6; i++) params.white[i] = analogRead(sensor[i]);  
    SerialPort.println("klaar");      
  }

  EEPROM_writeAnything(0, params);
}
