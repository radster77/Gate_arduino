// AUTOMATIC GATE BY RN V.1

#define operationTime 20000

int buttonA = 2;
int buttonB = 3;
int buttonC = 4;
int buttonD = 5;

int output1 = 7;
int output2 = 8;
int state = 5;
unsigned long currentTime = millis();
unsigned long lastTime = 0;
unsigned long timer = 0;

void setup() 
{
pinMode(output1, OUTPUT);
pinMode(output2, OUTPUT);

Serial.begin(9600);

}

void loop()
{
int buttonAState = digitalRead(buttonA);
int buttonBState = digitalRead(buttonB);
int buttonCState = digitalRead(buttonC);
int buttonDState = digitalRead(buttonD);

  
   if (buttonAState == HIGH)//OPEN
  {
    state = 1;
  } 
  else if (buttonBState == HIGH)//CLOSE
  {
    state = 2;
  }
  else if (buttonCState == HIGH)
  {
    state = 3;
  }
  else if (buttonDState == HIGH)
  {
  state = 4;
  }
  else 
  {
  state = 5;
  }
  
gateOperation(state);
  
}

void gateOperation(int buttonState)
{

 if (state == 1)//GATE OPENING
  {
  digitalWrite(output1, HIGH);//SET ACTUATOR DIRECTION TO OPEN pin 7
  delay(1000);
  digitalWrite(output2, HIGH);//SET ACTUATOR POWER ON pin8
  
  currentTime = millis();     //SET OPEN TIME
  lastTime = currentTime;                  
  timer=currentTime-lastTime;  
             
  while(timer<operationTime)           //OPENING TIME
                {
                  
                 currentTime = millis();    
                 timer=currentTime-lastTime;
                                     
                int buttonBState = digitalRead(buttonB);    // STOP OPENING IF BUTTON B IS PRESSED
                      if (buttonBState == HIGH)
                      {
                        Serial.println("Button B pressed while gate opening");
                       
                        state = 2;
                        break;
                      }
                }
                 
    digitalWrite(output2, LOW);
    Serial.println("ACTUATORS POWERED OFF in state 1");
    delay(300);
    digitalWrite(output1, LOW);
    state = 5;
  }
  
  
  else if (state == 2)//GATE CLOSING
  
  {
  digitalWrite(output1, LOW);//SETTING ACTUATOR DIRECTION TO OPEN

  delay(1000);
  
  digitalWrite(output2, HIGH);//ACTUATOR POWER ON
  
  currentTime = millis();    
  lastTime = currentTime;                   
  timer=currentTime-lastTime;               
  while(timer<operationTime)
                {
                 currentTime = millis();     //obecny czas:1000
                 timer=currentTime-lastTime;
                 int buttonAState = digitalRead(buttonB);
                      if (buttonAState == HIGH)
                      {
                        Serial.println("Button A pressed while gate opening");
                       
                        state = 1;
                        break;
                      }
                }
   
  digitalWrite(output2, LOW);

  }

else if (state == 3)
{
  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  delay(2000);
  state = 5;
  
}
else if (state == 4)
{
  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  delay(2000);
  state = 5;
}

  else if (state == 5)//IDLE
  
  {
  digitalWrite(output1, LOW);
  currentTime = millis();  
  lastTime = currentTime;                  
  timer=currentTime-lastTime;   
    while(timer<500)            //timer do poprawy bo blokuje program
                {
                 unsigned long currentTime = millis();
                 timer=currentTime-lastTime;
                }
    //Serial.println("idle");


   
  }
  else
  {
    Serial.println("else idle");
  }
}

 
