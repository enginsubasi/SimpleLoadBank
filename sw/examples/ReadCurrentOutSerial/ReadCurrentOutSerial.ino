/**
  ******************************************************************************
  *
  * @file:      ReadCurrentOutSerial
  * @author:    Engin Subasi
  * @e-mail:    enginsubasi@gmail.com
  * @address:   github.com/enginsubasi/SimpleLoadBank
  *
  * @version:   v 0.0.1
  * @cdate:     30/06/2019
  * @mdate:     30/06/2019
  * @history:   30/06/2019 Created
  *
  * @about:     Read current out serial
  * @device:    Generic Arduino boards
  *
  * @content:
  *     FUNCTIONS:
  *         adcToCurrent    : Returns current value in milliamps
  *         
  * @notes:
  *
  ******************************************************************************
  */

const double rshunt = 0.050;  // Ohm
const double ri     = 3000;   // Ohm
const double rf     = 3000;   // Ohm
double gain = 0;

uint32_t sensorValue = 0;
double currentValue = 0;

const uint32_t adcVoltageRef = 5;
const uint32_t adcUpValue = 1023;
const int analogInPin = A0;  // Analog input pin that the SLB output is attached to


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);

  gain = 1 + ( rf / ri );
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  currentValue = adcToCurrentMilliamp ( sensorValue );

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(currentValue2);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}

double adcToCurrentMilliamp ( uint32_t adcValue )
{
  double current = 0;

  current = adcValue; /* to cast operation in double domain */

  current = ( ( current * adcVoltageRef ) / adcUpValue );

  current /= gain;

  current /= rshunt;

  return ( current );
}
