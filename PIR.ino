/***********************************************
* Program to control my living room light and  *
* giving me 20 minutes to read before sleeping.*                        *
*                                              *
* By: Omar Gamal .. c.omargamal@gmail.com      *
*                                              *
* version 1.1  ...  24/2/2016                  *
************************************************/

//this code is used for NO relay

int mode = 5;       //ON/OFF the system pin
int led = 8;        //led pin
int pir = 9;        //PIR sensor pin
int state;          //state of the pir
int i=0;            //main loop counter
int j=0;            //sleep counter
int notif = 3;      //notification LED


void pulse()    //the pulse for keeping light ON
{
  digitalWrite(notif, HIGH);
  delay(100);
  digitalWrite(notif, LOW);
}




void sleep()
{
  for(j=0; (digitalRead(mode) == LOW) && (j<=250); j++)
  {
    digitalWrite(notif, HIGH);
    delay(100);
    digitalWrite(notif, LOW);
    delay(100);
    digitalWrite(notif, HIGH);
    delay(100);
    digitalWrite(notif, LOW);
    delay(4500);
  }
  if(digitalRead(mode) == LOW)
  {
    digitalWrite(led, HIGH);
  }
}




void setup() {
  pinMode(5, INPUT);    //ON/OFF the whole system
  pinMode(8, OUTPUT);   //LED pin
  pinMode(9, INPUT);    //PIR sesnor pin
  pinMode(3, OUTPUT);
  digitalWrite(led, HIGH); //led is HIGH = light is initially LOW
  digitalWrite(notif, HIGH);
  delay(4000);          //to let the system takes no arbitrary readings from the sensor
  digitalWrite(notif, LOW);
  delay(1000);
}





void loop() 
{ 
  while (digitalRead(mode) == HIGH)    //checks for the mode of operation
  {
    switch (digitalRead(pir))
    {
      case HIGH:
      delay(500);           //to avoid sudden ON
      digitalWrite(led, LOW);
      break;

      case LOW:
      for(i=0; digitalRead(pir) == LOW ;i++)
      {
        pulse();
        delay(1000);        //waiting 2 minutes before OFF the led
        if(i == 300)
        {
          digitalWrite(led, HIGH);
          state = HIGH;
        }
      }
      i=0;
      break;
    }
  }

    sleep();
    j=0;
}
