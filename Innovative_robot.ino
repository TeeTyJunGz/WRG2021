// PIR SERVO LCD LED BUZZER IR RELAY 1,2,3
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Adafruit_MLX90614.h>

int relay1 = 3; 
int relay2 = 4; 
int relay3 = 5;
int PIR = 10;// PIR
int val = 0;
int buzzer = 2;
int led = 3;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);

// SETUP
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  Serial.println("Adafruit MLX90614 test");  
  pinMode(relay1, OUTPUT); //  pump 1 measure temp
  pinMode(relay2, OUTPUT); // pump 2 alcohol
  pinMode(relay3, OUTPUT); // mask
  pinMode(PIR, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  lcd.begin(16, 2);
  mlx.begin();
  myservo.attach(9); 
}

void loop() {
   // TEMPERATURE
  Serial.print("Ambient = "); 
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); 
  Serial.print(mlx.readObjectTempC()); 
  Serial.println("*C");
  Serial.println();
  //PIR
  val = digitalRead(PIR); 
  Serial.print("val = "); 
  Serial.println(val); 
  
  // TEMPERATURE
  if ((mlx.readObjectTempC() <= 37.5)&& (mlx.readObjectTempC() >= 34.0)){ 
   lcd.setCursor(2, 0);
   lcd.print(mlx.readObjectTempC());
  }
    else{
      lcd.setCursor(6, 0);
      lcd.print("please");
      lcd.setCursor(4,1);
      lcd.print("measure again");
     
  }
  
  // TRASH
  if (val == 0) { 
    myservo.write(90);
    delay(1500);
    myservo.write(0);
    delay(1500);
  }
    else{
      myservo.write(0);  
  }
  
 // ALCOHOL
 digitalWrite(buzzer, HIGH);
 delay(2000);
 digitalWrite(led, HIGH);
 delay(2000);
 lcd.setCursor(1, 0);
 lcd.print("taking alcohol"); 
 digitalWrite(relay1,HIGH);
 delay (3000);
 digitalWrite(relay1,LOW);
 Serial.print("ALL DONE ALCOHOL");
   
// MASK
 digitalWrite(relay3,HIGH); 
 delay (2000);
 digitalWrite(relay3,LOW);
 Serial.print("ALL DONE MASK");

 //disinfect
 digitalWrite(relay2,HIGH); 
 delay (2000);
 digitalWrite(relay2,LOW);
 Serial.print("ALL DONE DISINFECTED");
 Serial.print("END OF PROCESS");
}
