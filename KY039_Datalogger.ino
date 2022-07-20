#include <SPI.h>
#include <SD.h>
#include <stdlib.h>

//Variaveis para cartao SD
const int CS = 4;
char dataString[7];
int sensorPin = 0;
int period = 200;

int HearHate_porSegundo=0;
int HearHate_porMin = 0;
int count = 0;
int countBeat=0;
const int Calibration_Value = 10;

float oldValue = 0;
float rawValue = 0;

File meuArquivo;

void setup()
{
 
  pinMode(CS, OUTPUT);
  Serial.begin(9600);
  delay(100);
  
  Serial.print("Inicializando cartao SD...");
  if (!SD.begin(CS)) 
  {
    Serial.println("Falha na Inicializacao!");
    return;
  }
  Serial.println("Inicializacao terminada");
  delay(100);
  
}


void loop()
{
   rawValue = analogRead (sensorPin);

   if( abs(rawValue - oldValue) >= Calibration_Value)
   {
      countBeat++;
   }
   count++;

   //cada 1 segundo faz essa conta
   if(count == 10)
   {
      HearHate_porSegundo = countBeat;
      HearHate_porMin =60*countBeat;
      Serial.print("HearHate_porSegundo");
      Serial.println(HearHate_porSegundo);
      Serial.print("HearHate_porMin");
      Serial.println(HearHate_porMin);
      count=0;
      countBeat=0;
      salvaDadosLogger(HearHate_porMin);
   }
   
  oldValue = rawValue;
  delay(period);
}

bool salvaDadosLogger(int HearHate_porMin)
{
  dtostrf(HearHate_porMin,5,2,dataString);
  
  if (meuArquivo = SD.open("log.txt",FILE_WRITE)) 
  {
    
    //Escreve no cartao SD por meio do objeto meuArquivo 
    meuArquivo.println(dataString);
    meuArquivo.close();
  } 
  else 
  {
    // se o arquivo nao abrir, mostra msg de erro
    Serial.println("Erro ao abrir log.txt");
  }
}