#include <Stepper.h>

int pinStart = 22;
int pinCount = 6;
int pinDir = 52;
int pinStep = 53;
int oneTurn = 20;
int pinDirLED = 50;

Stepper motor(oneTurn, pinStart, pinStart + 1, pinStart + 2, pinStart + 3);

void setup(){
  Serial.begin(9600);
  
  for(int i = 0; i < pinCount; i++){
    pinMode(pinStart + i, OUTPUT);
    digitalWrite(pinStart + i, LOW);
  }
  
  pinMode(pinDir, INPUT);
  pinMode(pinStep, INPUT);

  
  pinMode(pinDirLED, OUTPUT);
  digitalWrite(pinDirLED, HIGH);
  
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
      digitalWrite(pinDirLED, HIGH);
    }else{
      digitalWrite(pinDirLED, LOW);
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
