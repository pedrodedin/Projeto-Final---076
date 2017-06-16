#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (7, 8); 
byte addresses[][7] = {"canal1","canal2"}; 


char incomingByte;
char mensagem[100];
int i=0;
char fim=0;

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(124); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.openWritingPipe( addresses[1]);
  myRadio.startListening();
}


void loop()  
{
 //Transmissao
  if(Serial.available()>0)
  {       
          myRadio.stopListening();
          Serial.print("Eu:");
          while(Serial.available()>0)
               {
                  incomingByte= Serial.read(); 
                  Serial.print(incomingByte);
                  if(!myRadio.write(&incomingByte, sizeof(char)))
                  {
                    Serial.println("Erro na Transmisão");
                  }
                }
          myRadio.startListening();
  }



  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
        myRadio.read( &incomingByte, sizeof(incomingByte) );
        if(incomingByte!='\n')
        {
            mensagem[i]= incomingByte;
            i++;
        }
        else
        {
            mensagem[i]='\0';
            i=0;
            fim=1;
        }
      
    }

  }

  if(fim)
  {
      Serial.print("Pessoa:");
      Serial.println(mensagem);
      fim=0;
     
  }

}
