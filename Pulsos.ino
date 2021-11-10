/* PWM sin Hardware para distintas salidas V 1.0
 * Realizado por:
 * 
 * - Johnatan David Alvarez Vera
 * - Leonardo José Viana De Avila
 * 
 * SOFTWARE PARA PROCESADORES 
 */


typedef struct
{
  unsigned long previous, current;
  float         frecuencia;
  float         period;
  float         dutyCycle;
  int           outputPin;
  int           state;
}PWM_T; 

void create_pulso_setup(PWM_T *fsm,unsigned long previous,unsigned long current,float period,float frecuencia,float dutyCycle, int outputPin,int state)
{
  fsm->previous = previous;
  fsm->current=current;
  fsm->frecuencia=frecuencia;
  fsm->period=period;
  fsm->dutyCycle=dutyCycle;
  fsm->outputPin=outputPin;
  fsm->state=state;
 }

void create_pulso(PWM_T *fsm){
    switch(fsm->state){
      case 0:
      if (fsm->current - fsm->previous<fsm->period * fsm->dutyCycle){
       fsm->current=micros();
        fsm->state=0;
        } else{
         digitalWrite(fsm->outputPin,LOW);
        fsm->previous=fsm->current=micros();
       fsm->state=1;
      }
      break;
    
      case 1:
      if (fsm->current - fsm->previous<fsm->period * (1 - fsm->dutyCycle)){
        fsm->current=micros();
        fsm->state=1;
        } else{
        digitalWrite(fsm->outputPin,HIGH);
        fsm->previous=fsm->current=micros();
        fsm->state=0;
    }
    break;
  }
}

PWM_T PWM_0,PWM_1,PWM_2,PWM_3,PWM_4,PWM_5,PWM_6,PWM_7;

void setup(){

  
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);


  create_pulso_setup(&PWM_0,micros(),micros(),20000,1000000/20000,0.25,1,0);
  create_pulso_setup(&PWM_1,micros(),micros(),30000,1000000/30000,0.5,2,0);
  create_pulso_setup(&PWM_2,micros(),micros(),50000,1000000/50000,0.75,3,0);
  create_pulso_setup(&PWM_3,micros(),micros(),70000,1000000/70000,0.5,4,0);
  create_pulso_setup(&PWM_4,micros(),micros(),100000,1000000/100000,0.5,5,0);
  create_pulso_setup(&PWM_5,micros(),micros(),200000,1000000/200000,0.5,6,0);
  create_pulso_setup(&PWM_6,micros(),micros(),500000,1000000/500000,0.5,7,0);
  create_pulso_setup(&PWM_7,micros(),micros(),10000,1000000/10000,0.5,8,0);
}

void loop(){
  create_pulso(&PWM_0);      
  create_pulso(&PWM_1);
  create_pulso(&PWM_2);
  create_pulso(&PWM_3);
  create_pulso(&PWM_4);
  create_pulso(&PWM_5);
  create_pulso(&PWM_6);
  create_pulso(&PWM_7);
}
