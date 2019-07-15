#define ENA_m1 5        // Enable/speed motor Front Right 
#define ENB_m1 6        // Enable/speed motor Back Right
#define ENA_m2 10       // Enable/speed motor Front Left
#define ENB_m2 11       // Enable/speed motor Back Left

#define IN_11  2        // L298N #1 in 1 motor Front Right
#define IN_12  3        // L298N #1 in 2 motor Front Right
#define IN_13  4        // L298N #1 in 3 motor Back Right
#define IN_14  7        // L298N #1 in 4 motor Back Right

#define IN_21  8        // L298N #2 in 1 motor Front Left
#define IN_22  9        // L298N #2 in 2 motor Front Left
#define IN_23  12       // L298N #2 in 3 motor Back Left
#define IN_24  13       // L298N #2 in 4 motor Back Left

#define THKL   19 

void delay_s(int);

unsigned char data;            //Int to store app data state.
int speedCar = 100, speedLeftRight = 145;     // 50 - 255.

void setup() {  
    pinMode(ENA_m1, OUTPUT);
    pinMode(ENB_m1, OUTPUT);
    pinMode(ENA_m2, OUTPUT);
    pinMode(ENB_m2, OUTPUT);
  
    pinMode(IN_11, OUTPUT);
    pinMode(IN_12, OUTPUT);
    pinMode(IN_13, OUTPUT);
    pinMode(IN_14, OUTPUT);
    
    pinMode(IN_21, OUTPUT);
    pinMode(IN_22, OUTPUT);
    pinMode(IN_23, OUTPUT);
    pinMode(IN_24, OUTPUT);

    pinMode(THKL, INPUT);
    
    Serial.begin(115200); 
    Serial.println("Done setup!!");
} 

void goAhead(){ // OKEE

      digitalWrite(IN_11, HIGH);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13, HIGH);
      digitalWrite(IN_14,LOW);
      analogWrite(ENB_m1, speedCar);


      digitalWrite(IN_21, HIGH);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar);


      digitalWrite(IN_23, HIGH);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar);
  }

void goBack(){ //OKEE

      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, HIGH);
      analogWrite(ENB_m1, speedCar);


      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, speedCar);


      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, speedCar);
  }

void goRight(){ 
      digitalWrite(IN_11, HIGH);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedLeftRight);

      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14,HIGH);
      analogWrite(ENB_m1, speedLeftRight);


      digitalWrite(IN_21, HIGH);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedLeftRight);


      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, speedLeftRight);
  }

void goLeft(){
      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, speedLeftRight);


      digitalWrite(IN_13, HIGH);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedLeftRight);

      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, speedLeftRight);


      digitalWrite(IN_23, HIGH);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedLeftRight);       
  }

void stopCar(){  
      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar);


      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar);

  
      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar);

      
      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar);
}


void goBack_1(){ //OKEE

      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, 70);


      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, HIGH);
      analogWrite(ENB_m1, 70);


      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, 70);


      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, 70);
  }

boolean flag = false;
void loop()
{ 
    if ((digitalRead(THKL)==HIGH) && flag==false)
    {
        stopCar();
        delay(300);
        if ((digitalRead(THKL)==HIGH))
        {
            delay_s(500);
            flag = true;
        }
    }
    else
    {
        if ((digitalRead(THKL)==LOW) && flag==true)
            flag = false;
        if (Serial.available() > 0) 
        {
            data = Serial.read();
            Serial.println(data);
            switch (data) 
            {
                 case 'F': goAhead();       break;
                 case 'B': goBack();        break;
                 case 'L': goLeft();        break;
                 case 'R': goRight();       break;
                 case '1': speedCar = 60;   break;
                 case '2': speedCar = 70;   break;
                 case '3': speedCar = 80;   break;
                 case '4': speedCar = 90;   break;
                 case '5': speedCar = 100;  break;
                 case 'S': stopCar();       break;
             }
        }
    }
}


void delay_s(int sec)
{
    for(int i=0; i<(2*sec); i++)
    {
        if (digitalRead(THKL)==LOW)  break;
        delay(5);
    }
}
  








  
/*
void delay_s(int sec)
{
    for(int i=0; i<sec; i++)
    {
       Serial.println("Dang delay");
       delay(1000);
    }
}
  



int dem = 0;
boolean ttN = true, ttO = false, enaGB = false;
void loop()
{ 
    if (dem==1 && data == 48)
    {
        goBack_1(); 
        enaGB = true;
        //delay(1000);  luu y!!
        Serial.println("goBack");
    }
    if (dem==2 && data == 49 && enaGB == true)
    {
        stopCar();
        enaGB = false;
        Serial.println("Stop");
        delay_s(4);
        dem = 0;
    }
  
	if (Serial.available() > 0) 
	{
		data = Serial.read();
    Serial.println(data);
    
    if(data == 49)
    {
       dem++;  
       if (dem > 2) dem = 0;
       Serial.print("Dem = ");
       Serial.println(dem);
    }
    else if(enaGB==false)
    {
    		switch (data) 
    		{
    			case 'F': goAhead();       break;
    			case 'B': goBack();        break;
    			case 'L': goLeft();        break;
    			case 'R': goRight();       break;
    			case '1': speedCar = 60;   break;
    			case '2': speedCar = 70;   break;
    			case '3': speedCar = 80;   break;
    			case '4': speedCar = 90;   break;
    			case '5': speedCar = 100;  break;
    			case 'S': stopCar();       break;
    		}
    }
	}
}
*/
