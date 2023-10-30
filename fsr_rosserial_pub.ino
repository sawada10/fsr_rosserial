/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
// include neccesary library
#include <ros.h>
#include <std_msgs/Float32.h>

// ros message instance
ros::NodeHandle nh;

// ros message type
std_msgs::Float32 fsr_value;

// publisher instance
// node: fsr_publisher
// topic: power
// message instance: fsr_value
ros::Publisher fsr_publisher("power", &fsr_value);

// the setup routine runs once when you press reset:
void setup() {
  
  nh.initNode();
  nh.advertise(fsr_publisher);
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  float sensorValue = analogRead(A1);
  // print out the value you read:
  Serial.print("weight = ");
  Serial.print(sensorValue/1024*200);
  fsr_value.data = sensorValue/1024*200;
  fsr_publisher.publish(&fsr_value);
  Serial.println(" N");
  nh.spinOnce();
  delay(1000);        // delay in between reads for stability
}
