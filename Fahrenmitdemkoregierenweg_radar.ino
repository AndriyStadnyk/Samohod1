 //серво
#include <Servo.h>
#include <math.h>
Servo servoa;
int pos=90;

 int cm , x;   

#define N 5
//мотор А
int IN_1 = 7;
int IN_2 = 6;
int ENA = 2;
//мотор В
int ENB = 3;
int IN_3 = 5;
int IN_4 = 4;
//відстань
int echoPin = 9; 
int trigPin = 8; 
 //int rotation = 0;
void setup()
{
  
Serial.begin (9600);
pinMode(IN_1,OUTPUT);
pinMode(IN_2,OUTPUT);
pinMode(ENA,OUTPUT);
pinMode(IN_3,OUTPUT);
pinMode(IN_4,OUTPUT);
pinMode(ENB,OUTPUT);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
servoa.attach(10);
   
}
//функції окремо до моторів
void motorAforward( ) {
 digitalWrite (IN_1, LOW);
 digitalWrite (IN_2, HIGH);
 analogWrite(ENA,50);
}
  void motorBforward( ) {
 digitalWrite (IN_3,LOW );
 digitalWrite (IN_4, HIGH);
 analogWrite(ENB,50);
}
void motorAbackward( ) {
 digitalWrite (IN_1, HIGH);
 digitalWrite (IN_2, LOW);
 analogWrite(ENA,50);
}
void motorBbackward( ) {
 digitalWrite (IN_3, HIGH);
 digitalWrite (IN_4, LOW);
 analogWrite(ENB,50);
}
void motorAstop( ) {
 digitalWrite (IN_1, HIGH);
 digitalWrite (IN_2, HIGH);
 analogWrite(ENA,0);
}
void motorBstop( ) {
 digitalWrite (IN_3, HIGH);
 digitalWrite (IN_4, HIGH);
 analogWrite(ENB,0);
}
// Функції вперед,назад і тд
void forward ( ) {
 motorAforward();
 motorBforward();
}
void backward ( ) {
 motorAbackward();
 motorBbackward();
}
void left( ) {
 motorAforward();
 motorBbackward();
}
void right () {
 motorAbackward();
 motorBforward();
 
}
void breakMotors() {
 motorAstop();
 motorBstop();
}
void steep()
{
   forward();
    delay(100);
    breakMotors();
    delay(200);
}
void correctsteep()
{
  steep();
  servoa.write(180);
  int leftcorrect = 0 ;
  leftcorrect = Duration();
 delay(100);
  if(leftcorrect > 27 && leftcorrect <35)
    {
      left();
      delay(25);
    }
  if(leftcorrect < 15)
    {
      right();
      delay(25);
    }
}
void correctright()
{   
  int a[12];
  for( int n=0;n<12;n++)
  {
            servoa.write(n*15);
             a[n]=Duration();
  }
  int max1 = a[0];
        int index = 0;
        for (int z = 0; z < 12; z++)
        {
            if (a[z] > max1)
            {
                max1 = a[z];
                index = z;
            }
        }
   index++;
  if(index < 7) 
    {
      int chao=0;
   int pohsho=0;
   int pohsho2=0;
      for( int e=5;e>=0;e++){
          pohsho=a[e-1];
          chao=a[e]-pohsho;
          if(abs(chao) > 50){
            break;
          pohsho2=e+1;
          }
    left();
    delay(pohsho2*70);   
    }
    }
   else
    {
   int chao1=0;
   int pohsho3=0;
   int pohsho4=0;
      for( int e=6;e<12;e++){
          pohsho3=a[e+1]; 
          chao1=a[e]-a[e+1];
          if(chao1 > 50){
            break;
            pohsho4=(e+1)-5;
          }
      }
      left();
      delay(pohsho4*70);
    }
}
int  leftMsr()
{ 
  int leftAvg = 0 ;
  servoa.write(180);
  leftAvg = Measure2();
  delay(500);
if (leftAvg <25 && leftAvg != 0  )
  {
    return 1 ; 
  }
else
{
    if ( leftAvg > 25 || leftAvg == 0 )
  {
    return 0 ; 
  }
}

}
int  forwardMsr()
{ 
  int forwardAvg = 0 ;
  servoa.write(90);
  
  forwardAvg = Measure1();
  delay(200);
if (forwardAvg <25 && forwardAvg != 0  )
  {
    return 1 ; 
  }
else
  {
    if ( forwardAvg > 25 || forwardAvg == 0 )
    {
      return 0 ; 
    }
  }

}

int Duration()
{
  int duration, cm; 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH ,8000); 
  cm = (duration*.0343)/2;
//  Serial.print(cm); 
 // Serial.println(" "); 
   
 return cm;
}
int Measure2()
{
    int avg = 0 , Sum = 0 ;
    int M[N] ; 
    for (int i = 0 ; i < N ; i++)
      {
        M[i] = Duration();
        Sum  = Sum + M[i];
      }
   avg = Sum / 5 ; 
   for(int i  = 0 ;i <N ; i++)
      {
        if(M[i] == 0)
          {
             avg = 0;
          }
      }
   return avg ; 
}
int Measure1()
{
    int avg = 0 , Sum = 0 ;
    int K[N] ; 
    for (int i = 0 ; i < N ; i++)
      {
          K[i] = Duration();
          Sum  = Sum + K[i];
      }
   avg = Sum / 5 ; 
   for(int i  = 0 ;i <N ; i++)
    {
      if(K[i] == 0)
        {
          avg = 0;
        }
    }
    return avg ; 
}
void loop()
{
  int k = 0 ; 
  int f1 = 0 ; 
  int f2 = 0 ; 
 f1 = forwardMsr(); 
 Serial.println(f1); 
while(f1 == 0 )
  {
    steep();
    Serial.println(" "); 
    f1 = forwardMsr();
    Serial.println(f1); 
    if(f1 == 1 )
      {
        break;
      }
  }
  steep();
  delay(100);
  steep();
  delay(100);
  steep();
  delay(100);
  correctright();
  k++;
  delay(350);
  breakMotors();
  delay(100);
  int f3=leftMsr();
  delay(100);
  Serial.println("start"); 
  Serial.println("спереду="); 
  Serial.print(f3); 
  int f4=forwardMsr();
  delay(100);
  Serial.println("зліва="); 
  Serial.print(f4);
  Serial.println("end");
  do{
      correctsteep();
      f3=leftMsr();
      delay(200);
      f4=forwardMsr();
      delay(200);
      Serial.println("e");
    }
  while(f4>0&&f3==0); 
  forward();
  delay(300);
  breakMotors();
  delay(200);
  left();
  delay(350);
  steep();
  k = 0 ;
  delay(350);
  steep();  
}

 
