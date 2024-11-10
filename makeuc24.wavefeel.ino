// Accelerometer/mouse tracking code has been taken from github repositories (airmouse4saken)
#include <MPU6050.h>
#include <Mouse.h>
#include <Keyboard.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;
int SENSOR_PIN = 2;
int SENSOR2_PIN = 4;
int SENSOR3_PIN = 6;
int SENSOR4_PIN = 9;
int SENSOR5_PIN = 11;


int x, y;

int modeswitch = 10;

int mode = 0;

void setup() {
  Serial.begin(9600);

  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1)
      ;
  }
 

  pinMode(modeswitch, INPUT);

  Keyboard.begin();
}

void loop() {
  int currentState = digitalRead(SENSOR_PIN);
  int currentState2 = digitalRead(SENSOR2_PIN);
  int currentState3 = digitalRead(SENSOR3_PIN);
  int currentState4 = digitalRead(SENSOR4_PIN);
  int currentState5 = digitalRead(SENSOR5_PIN);
  if (digitalRead(modeswitch) == LOW)  
  {
    //add 1 to the current value of the mode variable
    mode = mode + 1;
    delay(500);
  }

  if (mode == 0) {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    vx = -(gx + 300) / 150;  // change 300 from 0 to 355 //changed to -(gx)
    vy = (gz - 100) / 150;   // same here about "-100"  from -355 to 0

    Serial.print("gx = ");
    Serial.print(gx);
    Serial.print(" | gz = ");
    Serial.print(gz);

    Serial.print("        | X = ");
    Serial.print(vx);
    Serial.print(" | Y = ");
    Serial.println(vy);

    Mouse.move(vx, vy);

    delay(20);
   if (currentState5 == LOW) {
    
  Mouse.press(MOUSE_LEFT);
     delay(200);
      Mouse.release(MOUSE_LEFT);
  }
  }
  if (mode == 1) {
    Serial.println("mode 1");
    if (currentState == LOW) {

      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('t');
      
     
      Keyboard.releaseAll();  
      delay(500);
    }
    if (currentState2 == LOW) {
 
   Keyboard.press(KEY_LEFT_CTRL);   
  Keyboard.press('e');             
  delay(100);                     
  Keyboard.releaseAll();          
  delay(1000);                     
  Keyboard.press(KEY_LEFT_GUI);     
  Keyboard.press('h');    
  delay(100);                    
  Keyboard.releaseAll();           
    delay(500);
  }
if (currentState3 == LOW) {
   
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('d');
    
   
    Keyboard.releaseAll();  
    delay(500);
  }
  if (currentState4 == LOW) {
    
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();  
    delay(500);
  }
 
  } else if (mode == 2) {
    mode = 0;
    delay(500);
  }
}