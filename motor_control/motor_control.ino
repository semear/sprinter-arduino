#include <Stepper.h>

int pinStart = 4;
int pinCount = 6;
int pinDir = 13;
int pinStep = 12;
int oneTurn = 20;
int pinDirLED1 = 8;
int pinDirLED2 = 9;

Stepper motor(oneTurn, pinStart, pinStart + 1, pinStart + 2, pinStart + 3);

void setup(){
  Serial.begin(9600);
  
  for(int i = 0; i < pinCount; i++){
    pinMode(pinStart + i, OUTPUT);
    digitalWrite(pinStart + i, LOW);
  }
  
  
  
  pinMode(pinStep, INPUT);
  pinMode(pinDir, INPUT);
  
}

void loop(){
  motor.setSpeed(60);
  boolean wasSigOn = false;
  while(true){
    int sig = digitalRead(pinStep);
    int turn = (digitalRead(pinDir) == HIGH) ? 1 : -1;

    
    boolean doStep = false;
    if(sig == HIGH){
      if(!wasSigOn){
        Serial.println("STEP");
        doStep = true;
      }
      wasSigOn = true;
    }else{
      wasSigOn = false;
    }
    
    if(turn > 0){
      digitalWrite(pinDirLED1, HIGH);
      digitalWrite(pinDirLED2, LOW);
    }else{
      digitalWrite(pinDirLED1, LOW);
      digitalWrite(pinDirLED2, HIGH);
    }
    
    if(!doStep){
      continue;
    }
    
    if(turn > 0){
      motor.step(1);
    }else{
      motor.step(-1);
    }
  }
}
