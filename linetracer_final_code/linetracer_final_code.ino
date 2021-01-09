//모터변수 m1=왼쪽 모터,m2=오른쪽모터
int m1=5, m2=6, e1=4, e2=7;
int m1memory=0,m2memory=0;
double add_value =0;


//IR센서 변수
int sensor1=9, sensor2=10, sensor3=11, sensor4=12;
int sensor1_v, sensor2_v, sensor3_v, sensor4_v;

//스위치,상태 변수
int state=0; char input;
int switch_pin=13, switch_value, switch_yes=1;

void setup() 
{
  Serial.begin(9600);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
}

void loop() 
{
  re:
  sensor1_v=digitalRead(sensor1);
  sensor2_v=digitalRead(sensor2);
  sensor3_v=digitalRead(sensor3);
  sensor4_v=digitalRead(sensor4);
  
  
 /*Serial Monitor를 사용해 라인트레이서의 상태를 전환하려면 이 코드를 사용한다.
  if(Serial.available())
  {
    input=Serial.read();
    switch(input)
    {
      case 'g':
        state=1;break;
       case 's':
        state=0;break;
      default:
        break;
    }
  }
  */
      
  //스위치를 이용해 라인트레이서의 상태를 전환하려면 이 코드를 사용한다.
  switch_value=digitalRead(switch_pin);
  if(switch_value==0)//스위치를 누르면
  {
    if(switch_yes==1)
    {
      state = 1-state;
      switch_yes=0;
    }
  }
  if(switch_value==1)//스위치에서 손때면
  {
    switch_yes=1;
  }  

  if(state==0)
  {
    analogWrite(m1,0);
    analogWrite(m2,0);
  }

  

  if(state==1)
  {
    /*
    digitalWrite(e1,LOW);
    digitalWrite(e2,HIGH);
    analogWrite(m1,255);
    analogWrite(m2,255);
    delay(500);
    */
    
    if(sensor1_v+sensor2_v+sensor3_v+sensor4_v==0)
    {
       /*
       digitalWrite(e1,LOW);
       digitalWrite(e2,HIGH);
       analogWrite(m1,90-(add_value+40));
       analogWrite(m2,90+(add_value+40));
       */

       if(add_value<0)
       {
        digitalWrite(e1,LOW);
        digitalWrite(e2,LOW);
        analogWrite(m1,150-add_value);
        analogWrite(m2,50);
       }
       if(add_value>0)
       {
        digitalWrite(e1,HIGH);
        digitalWrite(e2,HIGH);
        analogWrite(m1,50);
        analogWrite(m2,150+add_value);
       }
       goto re;
    }
  
    add_value=(sensor1_v*(-60)+sensor2_v*(-30)+sensor3_v*30+sensor4_v*60)/(1+sensor1_v+sensor2_v+sensor3_v+sensor4_v);

    digitalWrite(e1,LOW);
    digitalWrite(e2,HIGH);
    analogWrite(m1,150-add_value);
    analogWrite(m2,150+add_value);

    if(sensor1_v+sensor2_v+sensor3_v+sensor4_v==4)
    {
       analogWrite(m1,0);
       analogWrite(m2,0);
    }
  
  } 

}
