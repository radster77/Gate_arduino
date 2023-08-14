// AUTOMATIC GATE BY RN V.1.2

#define operationTime 23000
#define buttonPressedTime 20

int buttonA = 2;
int buttonB = 3;
int buttonC = 4;
int buttonD = 5;

int output1 = 7;
int output2 = 8;
int state = 5;
unsigned long currentTime = 0;
//unsigned long currentTime = millis();
unsigned long lastTime = 0;
unsigned long timer = 0;

int buttonAState = digitalRead(buttonA);
int buttonBState = digitalRead(buttonB);
int buttonCState = digitalRead(buttonC);
int buttonDState = digitalRead(buttonD);

void setup() 
{
pinMode(output1, OUTPUT);
pinMode(output2, OUTPUT);

Serial.begin(9600);

}

void loop()
{

   if (buttonAState == HIGH)    //OPEN
  {
    
    currentTime = millis();
    lastTime = currentTime;
    timer = currentTime - lastTime;
    
            while (timer < buttonPressedTime ) 
             {
                   currentTime = millis();
                   timer = currentTime - lastTime;
             }
             if (buttonAState == HIGH)
                     {
                       state = 1;
                     }
             else
                     {
                      state=5;
                     }
  
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
  digitalWrite(output1, HIGH);//SET ACTUATOR DIRECTION TO OPEN
  Serial.println("SET ACTUATOR DIRECTION TO OPEN");
  delay(1000);
  digitalWrite(output2, HIGH);//SET ACTUATOR POWER ON
  Serial.println("POWER ON");
  
  currentTime = millis();     //SET OPEN TIME
  lastTime = currentTime;                  
  timer=currentTime-lastTime;  
             
  while(timer<operationTime)           //OPENING TIME
                {
                  
                 currentTime = millis();    
                 timer=currentTime-lastTime;
                                        
                      if (buttonBState == HIGH) // STOP OPENING IF BUTTON B IS PRESSED
                      {
                        Serial.println("Button B pressed while gate opening");
                        delay(500);
                        state = 2;
                        break;
                      }

                      if (buttonCState == HIGH)
                      {
                        Serial.println("Button C pressed while gate opening");
                        delay(500);
                        state = 5;
                        break;
                      }

                      if (buttonDState == HIGH)
                      {
                        Serial.println("Button D pressed while gate opening");
                        delay(500);
                        state = 5;
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
  digitalWrite(output1, LOW);//SETTING ACTUATOR DIRECTION TO CLOSE

  delay(1000);
  
  digitalWrite(output2, HIGH);//ACTUATOR POWER ON
  
  currentTime = millis();    
  lastTime = currentTime;                   
  timer=currentTime-lastTime;               
  while(timer<operationTime)
                {
                 currentTime = millis();     //obecny czas:1000
                 timer=currentTime-lastTime;
                 
                      if (buttonAState == HIGH)
                      {
                        Serial.println("Button A pressed while gate closing");
                        delay(200);
                        state = 1;
                        break;
                      }

                      if (buttonCState == HIGH)
                      {
                        Serial.println("Button C pressed while gate closing");
                        delay(200);
                        state = 5;
                        break;
                      }

                      if (buttonDState == HIGH)
                      {
                        Serial.println("Button D pressed while gate closing");
                        delay(200);
                        state = 5;
                        break;
                      }
                }
   
  digitalWrite(output2, LOW);

  }

else if (state == 3)
{
  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  delay(300);
  state = 5;
  
}
else if (state == 4)
{
  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  delay(300);
  state = 5;
}

  else if (state == 5)//IDLE
  
  {
  Serial.println("STATE 5 IDLE");
  digitalWrite(output1, LOW);
  currentTime = millis();  
  lastTime = currentTime;                  
  timer=currentTime-lastTime;   
  while( buttonAState &&  buttonBState && buttonDState && buttonDState == LOW )  
                {
                 currentTime = millis();            
                 timer=currentTime-lastTime;
                 if (timer > 1000)
                 {
                  unsigned long czas = timer/1000;
                  Serial.println(czas);
                  lastTime = currentTime;
                 }
                  
                }
   


   
  }
}

 
