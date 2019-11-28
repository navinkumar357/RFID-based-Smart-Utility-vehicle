//HC-SR04 Sensor connection
  const int trigPin = 11;
  const int echoPin = 12;
  const int ust1=4;
  const int use1=3;
  const int ust2=2;
  const int use2=13;
  long duration; // left ultrasonic
  int distance;  // left ultrasonic
  long duration1; // right ultrasonic
  int distance1; // right ultrasonic
  long dura;     //centre 
  int dist;      //centre
  int in1 =5;  
  int in2 =6;            
  int in3 =7;
  int in4 =8; 
  int en1=9;
  int en2=10;
   
  void setup()
  {
    
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
    pinMode(ust1, OUTPUT); 
    pinMode(use1, INPUT);
    pinMode(ust2, OUTPUT); 
    pinMode(use2, INPUT);
    
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(en1,OUTPUT);
    pinMode(en2,OUTPUT);
    
    Serial.begin(9600);
  }
  void loop() 
  {
    digitalWrite(trigPin, LOW);            // left
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
    Serial.print("Distance left: ");
    Serial.println(distance);


    digitalWrite(ust1, LOW);            //right
    delayMicroseconds(2);
    digitalWrite(ust1, HIGH);
    delayMicroseconds(10);
    digitalWrite(ust1, LOW);
    duration1 = pulseIn(use1, HIGH);
    distance1= duration1*0.034/2;
    Serial.print("Distance_right: ");
    Serial.println(distance1);


    digitalWrite(ust2, LOW);            //centre
    delayMicroseconds(2);
    digitalWrite(ust2, HIGH);
    delayMicroseconds(10);
    digitalWrite(ust2, LOW);
    dura = pulseIn(use2, HIGH);
    dist= dura*0.034/2;
    Serial.print("Distance_centre: ");
    Serial.println(dist);
    //delay(5000);


  if(dist<=35)
    {
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      analogWrite(en1,0);
      analogWrite(en2,0);
      Serial.println("Stop centre");
      //delay(1000);
    }
     else if(distance<=35)
    {
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      analogWrite(en1,0);
      analogWrite(en2,0);
      Serial.println("Stop left");
      //delay(1000);
    }
     else if(distance1<=35)
    {
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      analogWrite(en1,0);
      analogWrite(en2,0);
      Serial.println("Stop right");
      //delay(1000);
    }
    else if(dist>150)
    {
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      analogWrite(en1,0);
      analogWrite(en2,0);
      Serial.println("Far centre");
      //delay(1000);
    }
    else if(distance>150)
    {
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      analogWrite(en1,0);
      analogWrite(en2,0);
      Serial.println("Far left");
      //delay(1000);
    }
   else if(distance1>150)
    {
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      analogWrite(en1,0);
      analogWrite(en2,0);
      Serial.println("Far right");
      //delay(1000);
    }
  else if ((dist>35 && dist<=50) && (((dist<= distance) && (dist< distance1)) || ((dist<= distance) && (dist< distance1))))
    { 
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      analogWrite(en1,160);
      analogWrite(en2,160);
      
      Serial.println("F 10");
      //delay(1000);
    }
    else if ((distance>35 && distance<=50) && ((distance< dist) && (distance< distance1)))
    { 
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      analogWrite(en1,240);
      analogWrite(en2,240);
      
      Serial.println("L 10");
      //delay(1000);
    }
   else if ((distance1>35 && distance1<=50)  && ((distance1< distance) && (distance1< dist)))
    { 
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      analogWrite(en1,240);
      analogWrite(en2,240);
      
      Serial.println("R 10");
      //delay(1000);
    }  
    
 
  else if((dist>50 && dist<=100)  && (((dist<= distance) && (dist< distance1)) || ((dist< distance) && (dist<= distance1))))
    {
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      analogWrite(en1,160);
      analogWrite(en2,160);
      Serial.println("F 30");
      //delay(1000);
    }
    else if((distance>50 && distance<=100) && ((distance< dist) && (distance< distance1)))
      {
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      analogWrite(en1,240);
      analogWrite(en2,240);
      Serial.println("L 30");
      //delay(1000); 
      } 
   else if((distance1>50 && distance1<=100)  && ((distance< dist) && (distance< distance1)))
      {
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      analogWrite(en1,240);
      analogWrite(en2,240);
      Serial.println("R 30");
      //delay(1000); 
    }    
    
    
    }
    
      










 
