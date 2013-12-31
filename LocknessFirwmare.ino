
  //RX is blue wire
  //TX is yellow wire
  #include <SoftwareSerial.h>
  #include <Servo.h> 
  #include <EEPROM.h>
    
  Servo servoMain;  
  SoftwareSerial mySerial(10, 11); // RX, TX
  int currentStatus = 2; 
  

void setup()  
{
    Serial.begin(9600);
    while (!Serial) {;}
  
    Serial.println("Serial Check:.......PASS");
    mySerial.begin(9600);
    Serial.println("My Serial Baud Rate:.......9600");
     
}

void loop(){
          
      if (mySerial.available()){
        
        char received_char = mySerial.read();
        decode_cmd(received_char); 
        int angle_pos = servoMain.read();
        //Serial.print("Angle: ");
        //Serial.println(angle_pos);
        
      }
}
   
void servo_lock(){
 
  servoMain.attach(7);
  servoMain.write(196); // Turn Servo Right to 135 degrees
  delay(1000);
  
}  

void servo_unlock(){
  
  servoMain.attach(7);
  servoMain.write(96); // Turn Servo Right to 135 degrees
  delay(1000);
  
}  

void decode_cmd(char received){
    
    if(received == 'l'){
      
   
   if(currentStatus == 1){
         
        Serial.println("Door already locked.");  
        
      }   
      else{
      currentStatus = 1;
      Serial.println("Locked the door.");
      servo_lock();
      servoMain.detach();
      }
    }
    else if(received == 'u'){
      
      
      if(currentStatus == 0){
         
        Serial.println("Door already unlocked.");  
        
      }
      else{
      currentStatus = 0; 
      Serial.println("Unlocked the door.");
      servo_unlock();
      servoMain.detach();
      }
      
    }
    else if(received == 0x0D || received == 0x0A){
      
     //Serial.println("New line received."); 
     //Catch the carriage return/new line 
    
    }
    else{
     
      Serial.println("Command not recognized.");
   
    }
  
}
  

