const int BLACK = 1;
const int WHITE = 0;
//const int RED_LED = 12;
const int IR_SENSOR_1 = 2;
const int IR_SENSOR_2 = 3;
const int IR_SENSOR_3 = 4;
const int IR_SENSOR_4 = 5;
const int IR_SENSOR_5 = 6;
const int IR_SENSOR_6 = 7;
const int IR_SENSOR_7 = 8;
const int IR_SENSOR_8 = 9;
//const int IR_SENSOR_L = A4;
//const int IR_SENSOR_R = A5;
const int PWM_LM = 11;
const int PWM_RM = 10;
const int LM_1 = A0;
const int LM_2 = A1;
const int RM_1 = A2;
const int RM_2 = A3;
const float Kp=10;
const float Ki=0;
const float Kd=2;
float I=0,prevError=0;
int s[9],count=0,redLight=0;
const int defaultSpeed = 55;
int k =0,n;
int IR;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 //pinMode(RED_LED,OUTPUT);
 pinMode(IR_SENSOR_1,INPUT);
 pinMode(IR_SENSOR_2,INPUT);
 pinMode(IR_SENSOR_3,INPUT);
 pinMode(IR_SENSOR_4,INPUT);
 pinMode(IR_SENSOR_5,INPUT);
 pinMode(IR_SENSOR_6,INPUT);
 pinMode(IR_SENSOR_7,INPUT);
 pinMode(IR_SENSOR_8,INPUT);
 //pinMode(IR_SENSOR_L,INPUT);
 //pinMode(IR_SENSOR_R,INPUT);
 pinMode(PWM_LM,OUTPUT);
 pinMode(PWM_RM,OUTPUT);
 pinMode(LM_1,OUTPUT);
 pinMode(LM_2,OUTPUT);
 pinMode(RM_1,OUTPUT);
 pinMode(RM_2,OUTPUT); 
}

float computeError()
{
   float error;
   s[1]=digitalRead(IR_SENSOR_1);
   s[2]=digitalRead(IR_SENSOR_2);
   s[3]=digitalRead(IR_SENSOR_3);
   s[4]=digitalRead(IR_SENSOR_4);
   s[5]=digitalRead(IR_SENSOR_5);
   s[6]=digitalRead(IR_SENSOR_6);
   s[7]=digitalRead(IR_SENSOR_7);
   s[8]=digitalRead(IR_SENSOR_8);
   //IR=digitalRead(IR_SENSOR_R);
 error=(-4*(!s[1])-3*(!s[2])-2*(!s[3])-1*(!s[4])+1*(!s[5])+2*(!s[6])+3*(!s[7])+4*(!s[8]))/((!s[1])+(!s[2])+(!s[3])+(!s[4])+(!s[5])+(!s[6])+(!s[7])+(!s[8]));

  return error;
}
void turnRight()
 {
  
  while(1)//while(s[1]==BLACK&&s[2]==BLACK&&s[3]==BLACK&&s[4]==WHITE&&s[5]==WHITE&&s[6]==BLACK&&s[7]==BLACK&&s[8]==BLACK)
  { s[1]=digitalRead(IR_SENSOR_1);
   s[2]=digitalRead(IR_SENSOR_2);
   s[3]=digitalRead(IR_SENSOR_3);
   s[4]=digitalRead(IR_SENSOR_4);
   s[5]=digitalRead(IR_SENSOR_5);
   s[6]=digitalRead(IR_SENSOR_6);
   s[7]=digitalRead(IR_SENSOR_7);
   s[8]=digitalRead(IR_SENSOR_8);
   //IR=digitalRead(IR_SENSOR_R);
   digitalWrite(LM_1,1);
   digitalWrite(LM_2,0);
   digitalWrite(RM_1,1);
   digitalWrite(RM_2,1);
   analogWrite(PWM_LM,80);
   analogWrite(PWM_RM,0);
   s[1]=digitalRead(IR_SENSOR_1);
   s[2]=digitalRead(IR_SENSOR_2);
   s[3]=digitalRead(IR_SENSOR_3);
   s[4]=digitalRead(IR_SENSOR_4);
   s[5]=digitalRead(IR_SENSOR_5);
   s[6]=digitalRead(IR_SENSOR_6);
   s[7]=digitalRead(IR_SENSOR_7);
   s[8]=digitalRead(IR_SENSOR_8);
  // IR=digitalRead(IR_SENSOR_R);
  if(s[1]==WHITE&&s[2]==WHITE&&s[3]==WHITE&&s[4]==WHITE&&s[5]==WHITE&&s[6]==WHITE&&s[7]==WHITE&&s[8]==WHITE)//&&IR==1)
  { while(1)
    {digitalWrite(LM_1,1);
     digitalWrite(LM_2,1);
     digitalWrite(RM_1,1);
     digitalWrite(RM_2,1);
     analogWrite(PWM_LM,0);
     analogWrite(PWM_RM,0);
     //digitalWrite(RED_LED,HIGH);
    }
  } 
   if(s[1]==BLACK&&s[2]==BLACK&&s[3]==BLACK&&s[4]==WHITE&&s[5]==WHITE&&s[6]==BLACK&&s[7]==BLACK&&s[8]==BLACK)
   break;
   
  }
 }
void turnLeft()
 {
  
  while(1)//while(s[1]==BLACK&&s[2]==BLACK&&s[3]==BLACK&&s[4]==WHITE&&s[5]==WHITE&&s[6]==BLACK&&s[7]==BLACK&&s[8]==BLACK)
  { s[1]=digitalRead(IR_SENSOR_1);
   s[2]=digitalRead(IR_SENSOR_2);
   s[3]=digitalRead(IR_SENSOR_3);
   s[4]=digitalRead(IR_SENSOR_4);
   s[5]=digitalRead(IR_SENSOR_5);
   s[6]=digitalRead(IR_SENSOR_6);
   s[7]=digitalRead(IR_SENSOR_7);
   s[8]=digitalRead(IR_SENSOR_8);
   //IR=digitalRead(IR_SENSOR_R);
   digitalWrite(LM_1,1);
   digitalWrite(LM_2,1);
   digitalWrite(RM_1,1);
   digitalWrite(RM_2,0);
   analogWrite(PWM_LM,0);
   analogWrite(PWM_RM,80);
   if(s[1]==BLACK&&s[2]==BLACK&&s[3]==BLACK&&s[4]==WHITE&&s[5]==WHITE&&s[6]==BLACK&&s[7]==BLACK&&s[8]==BLACK)
   break;
  }
 }
 void inch()
 {
  //continueLine();
  delay(350);
  stopMotor();
  delay(250);
   s[1]=digitalRead(IR_SENSOR_1);
   s[2]=digitalRead(IR_SENSOR_2);
   s[3]=digitalRead(IR_SENSOR_3);
   s[4]=digitalRead(IR_SENSOR_4);
   s[5]=digitalRead(IR_SENSOR_5);
   s[6]=digitalRead(IR_SENSOR_6);
   s[7]=digitalRead(IR_SENSOR_7);
   s[8]=digitalRead(IR_SENSOR_8);
  // IR=digitalRead(IR_SENSOR_R);
 }
 void stopMotor()
 {
   digitalWrite(LM_1,1);
   digitalWrite(LM_2,1);
   digitalWrite(RM_1,1);
   digitalWrite(RM_2,1);
   analogWrite(PWM_LM,0);
   analogWrite(PWM_RM,0);
 }
void PID(float error)
{   
 /*  float p;
   int Kp=10;
   p=Kp*error;
   speedLM=defaultSpeed+p;
   speedRM=defaultSpeed-p;*/
   float p,d,pid;
   int speedLM,speedRM;
   p=Kp*error;
   if(error==0)
   I=0;
   I=I+(Ki*error);
   d=Kd*(error-prevError);
   pid=p+I+d;
   prevError=error;
   speedLM=defaultSpeed+pid;
   speedRM=defaultSpeed-pid;
   if(speedLM>255)
    speedLM=255;
    if(speedRM>255)
    speedRM=255;
    if(speedLM<0)
    speedLM=0;
   if(speedRM<0)
   speedRM=0; 
   digitalWrite(LM_1,1);
   digitalWrite(LM_2,0);
   digitalWrite(RM_1,1);
   digitalWrite(RM_2,0);
   analogWrite(PWM_LM,speedLM);
   analogWrite(PWM_RM,speedRM);
}
void continueLine()
{
  PID(0.0);
}
void turnReverse()
{ 
  //delay(1000);
  while(1)//while(s[1]==BLACK&&s[2]==BLACK&&s[3]==BLACK&&s[4]==WHITE&&s[5]==WHITE&&s[6]==BLACK&&s[7]==BLACK&&s[8]==BLACK)
  { s[1]=digitalRead(IR_SENSOR_1);
   s[2]=digitalRead(IR_SENSOR_2);
   s[3]=digitalRead(IR_SENSOR_3);
   s[4]=digitalRead(IR_SENSOR_4);
   s[5]=digitalRead(IR_SENSOR_5);
   s[6]=digitalRead(IR_SENSOR_6);
   s[7]=digitalRead(IR_SENSOR_7);
   s[8]=digitalRead(IR_SENSOR_8);
   //IR=digitalRead(IR_SENSOR_R);
   digitalWrite(LM_1,0);
   digitalWrite(LM_2,1);
   digitalWrite(RM_1,1);
   digitalWrite(RM_2,0);
   analogWrite(PWM_LM,80);
   analogWrite(PWM_RM,80);
   s[1]=digitalRead(IR_SENSOR_1);
   s[2]=digitalRead(IR_SENSOR_2);
   s[3]=digitalRead(IR_SENSOR_3);
   s[4]=digitalRead(IR_SENSOR_4);
   s[5]=digitalRead(IR_SENSOR_5);
   s[6]=digitalRead(IR_SENSOR_6);
   s[7]=digitalRead(IR_SENSOR_7);
   s[8]=digitalRead(IR_SENSOR_8);
   //IR=digitalRead(IR_SENSOR_R);
  if(s[1]==WHITE&&s[2]==WHITE&&s[3]==WHITE&&s[4]==WHITE&&s[5]==WHITE&&s[6]==WHITE&&s[7]==WHITE&&s[8]==WHITE)//&&IR==1)
  { while(1)
    {digitalWrite(LM_1,1);
     digitalWrite(LM_2,1);
     digitalWrite(RM_1,1);
     digitalWrite(RM_2,1);
     analogWrite(PWM_LM,0);
     analogWrite(PWM_RM,0);
   //  digitalWrite(RED_LED,HIGH);
    }
  } 
   if(s[1]==BLACK&&s[2]==BLACK&&s[3]==BLACK&&s[4]==WHITE&&s[5]==WHITE&&s[6]==BLACK&&s[7]==BLACK&&s[8]==BLACK)
  {digitalWrite(LM_1,1);
   digitalWrite(LM_2,1);
   digitalWrite(RM_1,1);
   digitalWrite(RM_2,1);
   analogWrite(PWM_LM,0);
   analogWrite(PWM_RM,0);
   delay(200);
   break;
 }
}
}
void loop() 
{ 
  float error;
  error=computeError();
  PID(error);

   s[1]=digitalRead(IR_SENSOR_1);
   s[2]=digitalRead(IR_SENSOR_2);
   s[3]=digitalRead(IR_SENSOR_3);
   s[4]=digitalRead(IR_SENSOR_4);
   s[5]=digitalRead(IR_SENSOR_5);
   s[6]=digitalRead(IR_SENSOR_6);
   s[7]=digitalRead(IR_SENSOR_7);
   s[8]=digitalRead(IR_SENSOR_8);
   //IR=digitalRead(IR_SENSOR_R);
  if(s[1]==WHITE&&s[2]==WHITE&&s[3]==WHITE&&s[4]==WHITE&&s[5]==WHITE&&s[6]==WHITE&&s[7]==WHITE&&s[8]==WHITE)//&&IR==1)
  { while(1)
    {digitalWrite(LM_1,1);
     digitalWrite(LM_2,1);
     digitalWrite(RM_1,1);
     digitalWrite(RM_2,1);
     analogWrite(PWM_LM,0);
     analogWrite(PWM_RM,0);
     //digitalWrite(RED_LED,HIGH);
    }
  }   
  else {if(s[1]==WHITE&&s[2]==WHITE&&s[3]==WHITE&&s[4]==WHITE&&s[5]==WHITE&&s[6]==WHITE&&s[7]==WHITE&&s[8]==WHITE)
        { 
          inch();
          if(s[1]==WHITE&&s[2]==WHITE&&s[3]==WHITE&&s[4]==WHITE&&s[5]==WHITE&&s[6]==WHITE&&s[7]==WHITE&&s[8]==WHITE)//&&IR==1)
            { while(1)
              {digitalWrite(LM_1,1);
               digitalWrite(LM_2,1);
               digitalWrite(RM_1,1);
               digitalWrite(RM_2,1);
               analogWrite(PWM_LM,0);
               analogWrite(PWM_RM,0);
               //digitalWrite(RED_LED,HIGH);
              }
            }   
          
          else if(s[1]==WHITE&&s[2]==WHITE&&s[3]==WHITE&&s[4]==WHITE&&s[5]==WHITE&&s[6]==WHITE&&s[7]==WHITE&&s[8]==WHITE)
          {
            continueLine();
            delay(1000);
            stopMotor();
//            digitalWrite(RED_LED,HIGH);
            redLight=1; 
          }
          else if(s[4]==WHITE||s[5]==WHITE)
          {
            turnRight();
          }
          else if(s[1]==BLACK&&s[2]==BLACK&&s[3]==BLACK&&s[4]==BLACK&&s[5]==BLACK&&s[6]==BLACK&&s[7]==BLACK&&s[8]==BLACK)
          {
            turnRight();
          }
        }
        
  else if((s[4]==WHITE&&s[5]==WHITE&&s[6]==WHITE&&s[7]==WHITE&&s[8]==WHITE)||s[7]==WHITE||s[8]==WHITE)
       {
        turnRight();
        /*inch();
        if(s[4]==WHITE&&s[5]==WHITE)
        {
          turnRight();
        }  
        else if(s[1]==BLACK&&s[2]==BLACK&&s[3]==BLACK&&s[4]==BLACK&&s[5]==BLACK&&s[6]==BLACK&&s[7]==BLACK&&s[8]==BLACK)
        {
          turnRight(); 
        }
        */
       }

    else if(s[1]==WHITE&&s[2]==WHITE&&s[3]==WHITE&&s[4]==WHITE&&s[5]==WHITE)
       {int i, flag4=0;
        for(i=0;i<100;i++)
        {
           s[1]=digitalRead(IR_SENSOR_1);
           s[2]=digitalRead(IR_SENSOR_2);
           s[3]=digitalRead(IR_SENSOR_3);
           s[4]=digitalRead(IR_SENSOR_4);
           s[5]=digitalRead(IR_SENSOR_5);
           s[6]=digitalRead(IR_SENSOR_6);
           s[7]=digitalRead(IR_SENSOR_7);
           s[8]=digitalRead(IR_SENSOR_8);
          // IR=digitalRead(IR_SENSOR_R);
           if(s[7]==WHITE||s[8]==WHITE)
           {turnRight();
            flag4=1;
            break;
           }
           if(flag4=0)
       {   s[1]=digitalRead(IR_SENSOR_1);
           s[2]=digitalRead(IR_SENSOR_2);
           s[3]=digitalRead(IR_SENSOR_3);
           s[4]=digitalRead(IR_SENSOR_4);
           s[5]=digitalRead(IR_SENSOR_5);
           s[6]=digitalRead(IR_SENSOR_6);
           s[7]=digitalRead(IR_SENSOR_7);
           s[8]=digitalRead(IR_SENSOR_8);
           //IR=digitalRead(IR_SENSOR_R);
        {if(s[4]==WHITE&&s[5]==WHITE)
        {
          continueLine();
        }  
          if(s[1]==WHITE&&s[2]||WHITE&&s[3]||WHITE||s[4]==WHITE||s[5]==WHITE&&s[6]==BLACK&&s[7]==BLACK&&s[8]==BLACK)
        { 
          turnLeft();
        }
       }
        }
       }
       }   
          

  else if(s[1]==BLACK&&s[2]==BLACK&&s[3]==BLACK&&s[4]==BLACK&&s[5]==BLACK&&s[6]==BLACK&&s[7]==BLACK&&s[8]==BLACK)
         {inch();
          stopMotor();
          turnReverse(); 
        }
}
}
