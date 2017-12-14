//Laundry app


// First, we're going to make some variables.
// This is our "shorthand" that we'll use throughout the program:

int led1 = D0; // Instead of writing D0 over and over again, we'll write led1
// You'll need to wire an LED to this one to see it blink.

int led2 = D7; // Instead of writing D7 over and over again, we'll write led2
// This one is the little blue LED on your board. On the Photon it is next to D7, and on the Core it is next to the USB jack.
int pin = A0;

int photoresistor = A1;
int power = A5; 

int analogvalue_light;
int analogvalue;

int Status = 0; 

bool light = false;
bool door_Open = false;
bool door_Close = true;

bool in_Use = false;

int doorOpen = 0;
int doorClose = 1;


// Having declared these variables, let's move on to the setup function.
// The setup function is a standard part of any microcontroller program.
// It runs only once when the device boots up or is reset.

void setup() {

  // We are going to tell our device that D0 and D7 (which we named led1 and led2 respectively) are going to be output
  // (That means that we will be sending voltage to them, rather than monitoring voltage that comes from them)

  // It's important you do this here, inside the setup() function rather than outside it or in the loop function.

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pin, INPUT);
  pinMode(photoresistor,INPUT);
  pinMode(power,OUTPUT); 
//  Particle.variable("analogvalue", &analogvalue, INT);
  
 // Particle.variable("analogvalue_light", &analogvalue_light, INT);
 
  Particle.variable("Status", &Status, INT);
 // Particle.variable("Flag", Flag, String);
  /// Particle.variable("Flag", Flag, String);
  digitalWrite(power,HIGH);
  
}

// Next we have the loop function, the other essential part of a microcontroller program.
// This routine gets repeated over and over, as quickly as possible and as many times as possible, after the setup function is called.
// Note: Code that blocks for too long (like more than 5 seconds), can make weird things happen (like dropping the network connection).  The built-in delay function shown below safely interleaves required background activity, so arbitrarily long delays can safely be done if you need them.

void loop() {
  // To blink the LED, first we'll turn it on...
 
  int mag_value = analogRead(pin);
  int light_value =  analogRead(photoresistor);
  
  analogvalue = mag_value;
  analogvalue_light = light_value;
  
  digitalWrite(led1, HIGH);
  digitalWrite(led2,HIGH);
  
 // if( value == 1){
  //digitalWrite(led1, HIGH);
  //digitalWrite(led2, HIGH);
  

delay(3000);
Particle.publish("Light", String(analogvalue_light));
Particle.publish("Magnetic", String(analogvalue));

 if (light_value < 300){
     light = false;
 }

 //if light is on
 if (light_value > 350){
     light = true;
     in_Use = true;
      }
 //check the door
 if(in_Use == true){
     bool f1 = false;
     if(mag_value < 100){
        // door_Close = false;
         door_Open = true;
         doorOpen = 1;
       //  doorClose =0;
        // f1 = true;
     }
    
     
 }
 
 Particle.publish("DoorOpen", String(doorOpen));
// Particle.publish("DoorClose", String(doorClose));
  //check machine availability

 /*if(light == false && in_Use == false){
      Status = 0;
  }else if (light == false && in_Use == true){
      Status = 0
 
}
}*/

if(light == false && in_Use == false){
    Status =0;
}else if (light == false && in_Use ==true){
    if(door_Open == true){
        Status = 0;
        in_Use = false;
        door_Open = false;
    }
}else{
    Status = 1;
}
 
} 

 


