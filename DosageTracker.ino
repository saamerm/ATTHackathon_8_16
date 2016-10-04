//This code is flashed onto a Particle Photon device
// ------------
// Alarm
// ------------

int led2 = D7; 
int pushButton = D0; // Push button is connected to D2
int pushButtonState=HIGH; 


void setup() {
pinMode(pushButton, INPUT_PULLUP); 
pinMode(led2, OUTPUT);
Particle.function("led", ledToggle);
        Serial.begin(9600);

  }
void loop() 
{
  pushButtonState = digitalRead(pushButton);
  delay(100); 
  if(pushButtonState == LOW)
  { //If we push down on the push button
    digitalWrite(led2, HIGH);  // Turn ON the LED
    Particle.publish("pushButtonState","Pressed",60,PRIVATE);
    
    Particle.variable("pushedButton", "push");

    delay(1000); 
                    Particle.variable("pushedButton", "unpush");

  }
  else
  {
    digitalWrite(led2, LOW);   // Turn OFF the LED 
  }
}

int ledToggle(String command) {
 
    if (command=="on") {
        while(pushButtonState == HIGH)
        {
            delay(100); 
            digitalWrite(led2,LOW);
            delay(100); 
            pushButtonState = digitalRead(pushButton);
            digitalWrite(led2,HIGH);
        }
        Particle.variable("pushedButton", "push");

        delay(1000);
                Particle.variable("pushedButton", "unpush");

        digitalWrite(led2,LOW);
        return 1;
    }
    else if (command=="off") 
    {
        digitalWrite(led2,LOW);
        return 0;
    }
    else {
        return -1;
    }
}
