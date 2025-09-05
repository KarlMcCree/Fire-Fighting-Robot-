#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <HTTPClient.h>
#include <SoftwareSerial.h>
#include <WebServer.h>
#include "HardwareSerial.h"

const char* ssid = "McCree_5B9B78";
const char* password = "afolabi123";
WebServer server(80);

#define API_KEY "AIzaSyDeeO1EI7RldaLgYyMVoaG4RV_zFEllcRI"
#define DATABASE_URL "https://firerobot-project-default-rtdb.europe-west1.firebasedatabase.app/"  // Add trailing slash

// Optional: If using Email/Password sign-in (not needed for database secret access)
#define USER_EMAIL "opawumivictor@gmail.com"
#define USER_PASSWORD "123456789"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

String controlCommand = "None";
unsigned long lastFirebaseCheck = 0;
const unsigned long firebaseInterval = 1000; // Check every 1 second

//Sensor Pins
//Here we'll be Using more than one FLame Sensor 
#define FLAME_SENSOR_1_PIN 16 // Flame sensor 1 pin
#define FLAME_SENSOR_2_PIN 17  // Flame sensor 2
//LED On the ESP32 board
#define LED_PIN 2
#define ECHO_PIN 19 //Echo pin
#define TRIG_PIN 18 //Trigger pin
#define SERVO 23 //Servo
#define enA 33//Enable1 L298 Pin enA 
#define in1 14 //Motor1  L298 Pin in1 
#define in2 27 //Motor1  L298 Pin in1 
#define in3 26 //Motor2  L298 Pin in1 
#define in4 25 //Motor2  L298 Pin in1 
#define enB 13 //Enable2 L298 Pin enB
#define relay_Pin 15 //m Relay control pin 
#define Gas_SensorPin 34 // MQ-6 gas sensor analog pin 13
#define BUZZER_PIN 32 //m Buzzer pin['[]]
#define MODEM_RX 21 //m SIM800L TX to ESP32 RX#
#define MODEM_TX 22

 // mSIM800L RX to ESP32 TX
#define L_S 4 //IR left Sensor 
#define R_S 5 //IR Right sensor 

HardwareSerial sim800(2);
  
bool manualMode = false;
int remoteCommand = 0;
unsigned long lastCommandTime = 0;

const long desiredDistance = 30; // Adjustable

  int Set=15;
  int distance_L, distance_F, distance_R;


void setup() {
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT);// declare ultrasonic sensor Echao pin as input
  pinMode(TRIG_PIN, OUTPUT); // declare ultrasonic sensor Trigger pin as Output 
  pinMode(SERVO, OUTPUT);// declare as output for Servo
  pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
  pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 
  pinMode(FLAME_SENSOR_1_PIN, INPUT); // Set flame sensor pin as input
  pinMode(FLAME_SENSOR_2_PIN, INPUT); // Set flame sensor pin as input
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);//Buzzer  Pin
  pinMode(Gas_SensorPin,INPUT); //MQ6 pin
  pinMode(relay_Pin, OUTPUT);      // Set relay pin as output which is a DigitalWritePin
  pinMode(R_S, INPUT); // declare if sensor as input  
  pinMode(L_S, INPUT); // declare ir sensor as input

  sim800.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);

  //Servo motor Rotatory motion
  for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(SERVO, angle);  }
  for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(SERVO, angle);  }
  for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(SERVO, angle);  }
  distance_F = Ultrasonic_read();
  delay(500);

  Serial.println("Fire Dectection System Initialized");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi.");
  Serial.println("Local IP: " + WiFi.localIP());


  // Firebase config
  config.api_key = "AIzaSyDeeO1EI7RldaLgYyMVoaG4RV_zFEllcRI";
  config.database_url = "https://firerobot-project-default-rtdb.europe-west1.firebasedatabase.app/";

  // If using Email/Password auth
  auth.user.email = "opawumivictor@gmail.com";
  auth.user.password = "123456789";

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);


}

void loop() {

  server.handleClient();

  // Check Firebase for remote commands every 1 second
  if (millis() - lastFirebaseCheck >= firebaseInterval) {
    lastFirebaseCheck = millis();

    if (Firebase.ready() && Firebase.RTDB.getString(&fbdo, "/Control_Command")) {


      controlCommand = fbdo.stringData();
      Serial.print("Control Command from Firebase: ");
      Serial.println(controlCommand);

      if (controlCommand == "Forward") {
        forward();
        manualMode = true;
      } else if (controlCommand == "Backward") {
        backword();
        manualMode = true;
      } else if (controlCommand == "Left") {
        turnLeft();
        manualMode = true;
      } else if (controlCommand == "Right") {
        turnRight();
        manualMode = true;
      } else if (controlCommand == "Stop") {
        stopMotors();
        manualMode = false;
      }

      // Clear command to prevent repeat execution
      Firebase.RTDB.setString(&fbdo, "/Control_Command", "None");
    } else {
      Serial.println("Error reading Firebase Control_Command:");
      Serial.println(fbdo.errorReason());
    }
  }
                             
  //If no manual command for 10s, return to autonomous mode
  if (manualMode && (millis() - lastCommandTime > 10000)) {
    manualMode = false;
    stopMotors();
    Serial.println("Manual control timeout — back to autonomous mode.");
  }


//intiallizing the Flame Sensor 
  //Read the state of each flame sensor
  
  int flameSensor1State = digitalRead(FLAME_SENSOR_1_PIN);
  int flameSensor2State = digitalRead(FLAME_SENSOR_2_PIN);

  if (flameSensor1State == HIGH || flameSensor2State == HIGH ) {
    Serial.println("Fire detected by Flame Sensors!...");
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON");
    moveTowardsFire();
    

  if (Firebase.ready()) {
      if (Firebase.RTDB.setString(&fbdo, "/Fire_Status", "Fire Detected")) {
          Serial.println("Fire status sent to Firebase");
      } else {
          Serial.println(fbdo.errorReason());
      }
  }
 else {
    Serial.println("No fire detected by any Flame Sensor!...");
    digitalWrite(LED_PIN, LOW);
    //digitalWrite(relay_Pin, HIGH);
    Serial.println("LED OFF");

    if (Firebase.RTDB.setString(&fbdo, "/Fire_Status", "Fire not detected")) {
      Serial.println("Fire status sent to Firebase");
    } else {
      Serial.println(fbdo.errorReason());
    }
  }

    delay(1000);


//Uses a servo and ultrasonic sensor to check left and right Determines which way is clear Decides where to turn
  distance_F = Ultrasonic_read();
  Serial.print("D F=");
  Serial.println(distance_F);

  //Infrared sensor pin
  if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 0)) {
    if (distance_F > Set) {
    forward();

    //update Firebase that path is clear
    Firebase.RTDB.setString(&fbdo, "/Obstacle_Status", "Path is clear");

    } else {
      Serial.println("Obstacle detected! Checking sides...");
  
      // Send status to Firebase
      Firebase.RTDB.setString(&fbdo, "/Obstacle_Status", "Obstacle detected, checking sides...");

      Check_side(); // decide left/right movement
    }

  }
  else if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 0)) {
    turnRight();           // Line detected on right sensor — turn right
  }
  else if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 1)) {
    turnLeft();            // Line detected on left sensor — turn left
  }
    delay(10);


  
  //Gas Sensor Readings on firebase between 5 and 15 percent
  int gasValue = analogRead(Gas_SensorPin); 
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // Send gas value to Firebase
  if (Firebase.RTDB.setInt(&fbdo, "/Gas_Sensor_Value", gasValue)) {
    Serial.println(" Gas value sent to Firebase ");
  } else {
    Serial.print(" Firebase error: ");
    Serial.println(fbdo.errorReason());
  }

  // Check if the gas concentration exceeds a certain threshold
  if (gasValue > 1000) { // Adjust this threshold based on your sensor
    digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
    Serial.println("Gas Leak detected! Buzzer ON.");
    // Send gas status to Firebase
    Firebase.RTDB.setString(&fbdo, "/Gas_Status", "Gas Leak detected! Buzzer ON.");


  } else {
    digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
    Serial.println("No gas detected. Buzzer OFF.");
    // Send gas status to Firebase
    Firebase.RTDB.setString(&fbdo, "/Gas_Status", "No gas detected. Buzzer OFF.");

  }
  delay(1000);

}

  void moveTowardsFire() {

    digitalWrite(relay_Pin, HIGH); // Make sure relay is off first

    // Implement your logic to move the robot towards the fire
    long distance = getDistance(); // Measure distance to the fire

  	// If the distance is greater than the desired distance, move forward
    if (distance > desiredDistance) {
    	forward(); // Move towards the fire
      Serial.println("Moving towards fire...");
    } else {
	     stopMotors(); // Stop when the desired distance is reached
     	 Serial.println("Reached safe distance from fire. Waiting for instructions.");
        	  
      digitalWrite(relay_Pin, LOW); // Activate pump
      delay(10000); // Wait 10 seconds to extinguish fire

      digitalWrite(relay_Pin, HIGH); // Turn pump OFF
      Serial.println(" Fire extinguished. Backing up...");

      callsPhone();

      // Step 1: Reverse a bit
      backword();
      delay(950);

      stopMotors();
      delay(500);

      // Step 2: Realign using IR sensors
      while ((digitalRead(R_S) == 1) || (digitalRead(L_S) == 1)) {
         if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 0)) {
          turnLeft();
        } else if ((digitalRead(L_S) == 1) && (digitalRead(R_S) == 0)) {
          turnRight();
        } else {
          stopMotors(); // Line is centered again
          break;
        }
    }

    Serial.println(" Returned to line.");
			}
  }

  void servoPulse (int pin, int angle){
      int pwm = (angle*11) + 500;      // Convert angle to microseconds
      digitalWrite(pin, HIGH);
      delayMicroseconds(pwm);
      digitalWrite(pin, LOW);
      delay(30); // Refresh cycle of servo
  }
   
  long Ultrasonic_read(){
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    long time = pulseIn (ECHO_PIN, HIGH);
    return time / 29 / 2;
  }

void compareDistance(){
    
    if(distance_L > distance_R){
    turnRight();
    delay(500);
    forward();
    delay(600);
    turnLeft();
    delay(500);
    forward();
    delay(600);  
    turnLeft();
    delay(400);

  }
  else{

    turnLeft();
    delay(500);
    forward();
    delay(600);
    turnRight();
    delay(500);
    forward();
    delay(600);
    turnRight();
    delay(400);
    }
}

void Check_side(){

    stopMotors();
    delay(100);
  for (int angle = 70; angle <= 140; angle += 5)  {
    servoPulse(SERVO, angle);  
    }
  delay(300);
  distance_R = Ultrasonic_read();
  Serial.print("D R=");
  Serial.println(distance_R);
  delay(100);

  for (int angle = 140; angle >= 0; angle -= 5)  {
    servoPulse(SERVO, angle);  
  }

  delay(500);
  distance_L = Ultrasonic_read();
  Serial.print("D L=");
  Serial.println(distance_L);
  delay(100);

  for (int angle = 0; angle <= 70; angle += 5)  {
    servoPulse(SERVO, angle);  
  }

  delay(300);
  compareDistance();
}
//Sim call Function
void callsPhone(){

  Serial.println("Initializing SIM800L...");
  delay(1000);

  sim800.println("AT");  
  updateSerial();

  sim800.println("ATD+2348133548591;");  // Replace with your number
  updateSerial();
  delay(20000); // Wait 20 seconds

  sim800.println("ATH");  // Hang up
  updateSerial();
}


//Sim function
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    sim800.write(Serial.read());
  }
  while (sim800.available()) {
    Serial.write(sim800.read());
  }
}  
  long getDistance() {
    digitalWrite(TRIG_PIN, LOW); // Ensure the trigger pin is low
    delayMicroseconds(2); // Wait for 2 microseconds
    digitalWrite(TRIG_PIN, HIGH); // Send a 10 microsecond pulse to trigger
    delayMicroseconds(10); // Wait for 10 microseconds
    digitalWrite(TRIG_PIN, LOW); // Stop the pulse

    // Read the echo pin
    long duration = pulseIn(ECHO_PIN, HIGH); // Measure the duration of the echo
    long distance = duration * 0.034 / 2; // Calculate distance in cm

    return distance; // Return the measured distance
}

void forward(){  //forword
  digitalWrite(in1, LOW);//Left Motor backword Pin, Ensure left motor is not moving forward
  digitalWrite(in2, HIGH);//Left Motor forword Pin, Set left motor to move forward
  analogWrite(enA, 130);

  digitalWrite(in3, HIGH);//Right Motor forword Pin, Set right motor to move forward
  digitalWrite(in4, LOW);//Right Motor backword Pin, Ensure right motor is not moving backward
  analogWrite(enB, 130);

}
void backword(){ //backword
  digitalWrite(in1, HIGH);//Left Motor backword Pin 
  digitalWrite(in2, LOW);//Left Motor forword Pin 
  analogWrite(enA, 130);

  digitalWrite(in3, LOW);//Right Motor forword Pin 
  digitalWrite(in4, HIGH); //Right Motor backword Pin 
  analogWrite(enB, 130);
 

 

}
void turnRight(){ //turnRight
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 0);      // Left motor off

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 130);     // Right motor off
  
}
void turnLeft(){ //turnLeft
 // Left motor stops, Right motor moves forward
   digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 130);      // Left motor off

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);    

}
void stopMotors(){ //stop
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
analogWrite(enA, 0);

digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
analogWrite(enB, 0);
}

