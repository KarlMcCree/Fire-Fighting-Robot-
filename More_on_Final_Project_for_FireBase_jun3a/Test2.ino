// #define TINY_GSM_MODEM_SIM800
// #define SerialMon Serial
// #define SerialAT Serial1
// #define TINY_GSM_DEBUG SerialMon
// #define GSM_PIN ""

// #define ADMIN_NUMBER "+8801715497977"
// #define TINY_GSM_DEBUG SerialMon

// #include <TinyGsmClient.h>

// #ifdef DUMP_AT_COMMANDS
// #include <StreamDebugger.h>
// StreamDebugger debugger(SerialAT, SerialMon);
// TinyGsm modem(debugger);
// #else
// TinyGsm modem(SerialAT);
// #endif

// // ESP32 and SIM800l pins
// #define MODEM_TX 17
// #define MODEM_RX 18


// String phoneNumber = "";
// String message = "";
// bool isReceivingMessage = false;

// void setup() {
//   SerialMon.begin(115200);
//   delay(1000);

//   SerialMon.println("Wait ...");
//   SerialAT.begin(9600, SERIAL_8N1, MODEM_TX, MODEM_RX);
//   delay(3000);
//   SerialMon.println("Initializing modem ...");
//   delay(1000);
//   Serial.println("Modem will restart now. Please Wait");
//   modem.restart();


//   if (GSM_PIN && modem.getSimStatus() != 3) {
//     modem.simUnlock(GSM_PIN);
//   }

//   SerialMon.print("Waiting for network...");
//   if (!modem.waitForNetwork()) {
//     SerialMon.println(" fail");
//     delay(10000);
//     return;
//   }
//   SerialMon.println(" success");

//   if (modem.isNetworkConnected()) {
//     DBG("Network connected");
//   }

//   String cop = modem.getOperator();
//   DBG("Operator:", cop);

//   int csq = modem.getSignalQuality();
//   DBG("Signal quality:", csq);

//   SerialAT.print("AT+CMGF=1\r");
//   delay(1000);

//   SerialAT.print("AT+CNMI=2,2,0,0,0\r");
//   delay(1000);
//   String smsMessage = "Device Ready";
//   Serial.println("Sending a device started Message: ");
//   Serial.println(smsMessage);
//   modem.sendSMS(ADMIN_NUMBER, smsMessage);
// }

// void loop() {
//   while (SerialAT.available()) {
//     String response = SerialAT.readStringUntil('\n');
//     response.trim();
//     if (response.startsWith("+CMT: ")) {
//       phoneNumber = extractPhoneNumber(response);
//       isReceivingMessage = true;
//     }
//     else if (isReceivingMessage) {
//       message = response;
//       isReceivingMessage = false;
//       Serial.println("New Incomming Message: ");
//       Serial.println("Message: " + message);
//       Serial.println("Phone Number: " + phoneNumber);
//       Serial.println();
//     }
//   }
// }

// String extractPhoneNumber(String response) {
//   int startIndex = response.indexOf("\"") + 1;
//   int endIndex = response.indexOf("\",", startIndex);
//   return response.substring(startIndex, endIndex);
// // }
// #define BUZZER_PIN 32  // Change this to your actual buzzer pin

// void setup() {
//   pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
// }

// void loop() {
//   digitalWrite(BUZZER_PIN, HIGH); // Turn ON buzzer
//   delay(1000);                    // Wait for 1 second
//   digitalWrite(BUZZER_PIN, LOW);  // Turn OFF buzzer
//   delay(1000);                    // Wait for 1 second
// }

// const int RELAY_PIN = 15;  // Connect the IN pin of relay module to pin 7 (change as needed)

// void setup() {
//   Serial.begin(115200);
//   pinMode(RELAY_PIN, OUTPUT);     // Set relay pin as OUTPUT
//   digitalWrite(RELAY_PIN, LOW); 
//    // Start with relay OFF (or HIGH if using active-low)
// }

// void loop() {
//   digitalWrite(RELAY_PIN, HIGH);  // Turn relay ON
//   Serial.println(" relay on");
//   delay(5000);                    // Wait 1 second
//   digitalWrite(RELAY_PIN, LOW);   // Turn relay OFF
//   Serial.println(" relay off");
//   delay(5000);                    // Wait 1 second
// }

///Final sim module code 

// #define MODEM_RX 21  // ESP32 RX ← SIM800L TX
// #define MODEM_TX 22  // ESP32 TX → SIM800L RX (⚠️ Use voltage divider on TX pin!)

// #include "HardwareSerial.h"
// HardwareSerial sim800(2);  // Use UART2

// void setup() {
//   Serial.begin(115200);           // Serial monitor
//   sim800.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);  // SIM800L serial

//   Serial.println("Initializing SIM800L...");
//   delay(1000);

//   sim800.println("AT");  // Test AT
//   updateSerial();
  
//   // sim800.println("AT+CMGF=1");  // Text mode
//   // updateSerial();
//   // sim800.println("AT+CMGS=\"+2348133548591\"");  //change ZZ with country code and xxxxxxxxxxx with phone number to sms
//   // updateSerial();
//   // sim800.print("Last Minute");  //text content
//   // updateSerial();
//   // sim800.write(26);
//   // Optional: Set how SMS are displayed
//   // sim800.println("AT+CNMI=1,2,0,0,0");
//   // updateSerial();

//   // === CALL a Number ===
//   sim800.println("ATD+2348133548591;");  // Replace with your phone number
//   updateSerial();
//   delay(20000); // Wait 20 seconds for the call

//   sim800.println("ATH");  // Hang up
//   updateSerial();
//  }

// void loop() {
//   // Nothing in loop
// }

// void updateSerial() {
//   delay(500);
//   while (Serial.available()) {
//     sim800.write(Serial.read());  // Forward from Serial Monitor to SIM800L
//   }
//   while (sim800.available()) {
//     Serial.write(sim800.read());  // Forward SIM800L response to Serial Monitor
//   }
// }
