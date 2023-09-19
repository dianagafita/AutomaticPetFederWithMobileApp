#include <Servo.h>
Servo servoMotor;  
int angle = 90;
const int pompaApa = 9;
void setup() {
Serial.begin(115200);
servoMotor.attach(10);  
servoMotor.write(angle);  
pinMode(pompaApa, OUTPUT); 
digitalWrite(pompaApa, HIGH); 
}
void loop()
{ 
if (Serial.available()) 
{
    char receivedChar = Serial.read();
      Serial.print("Semnalul trimis de la aplicatie este ");
      Serial.println(receivedChar);
        if (receivedChar == '1') { 
            Serial.print("Porneste pompa de apa.");
            digitalWrite(pompaApa, LOW); 
             delay(25000);
            digitalWrite(pompaApa, HIGH); 
        } else if (receivedChar == '0') { 
             Serial.print("Opreste pompa de apa.");
             digitalWrite(pompaApa, HIGH);
        }
          else if (receivedChar == '2') 
            { Serial.print("Porneste servo-motorul."); 
              int angle = 90; 
               servoMotor.attach(10);  
               angle += 30;
               servoMotor.write(angle);
               delay(1000); 
               servoMotor.detach();
            }
          else if (receivedChar == '3') 
          {  Serial.print("Opreste servo-motorul.");
             int angle = 90; 
             servoMotor.attach(10);  
             angle -= 40;
             servoMotor.write(angle);
             delay(1000); 
             servoMotor.detach();
              } 
}
}


