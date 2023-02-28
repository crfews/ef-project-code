/* T-2-5
 * Date Last Modified: 2023/02/28
 * Code Description - the code powers a string of LEDs dependent on whether a ball tilt sensor is triggered
 */

/* ledPin - pin the LED is connected to
 * sensorPin - pin the ball tilt sensor is connected to
 * sensorValue - store whether ball tilt sensor measures low or high
 * lastDebounceTime - time since the ball tilt sensor was activated
 * debounceDelay - the time interval for the ball to settle on or off to prevent flickering
 */
const int ledPin = 10;
const int sensorPin = 4;
int sensorValue;
int lastTiltState = HIGH;

long lastDebounceTime = millis();
long debounceDelay = 50;

/* This code initializes the pins used for the ball tilt sensor, the 
 * LED, and Serial.
 */ 
void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = digitalRead(sensorPin);
  /* If the value of the sensor is different than the previous loop,
   * don't change the LED state yet and update the debounce time.
   */
  if(sensorValue != lastTiltState) {
    lastDebounceTime = millis();
  }
  /* If the time in the loop is less than the delay,
   * check if the sensor reads high or not.
   * If the sensor is off and the light is on, set the tilt state to off
   * If the sensor is on, switch the light value
   */
  if((millis() - lastDebounceTime) > debounceDelay) {

    if (sensorValue != lastTiltState) {
      lastTiltState = sensorValue;
      if (sensorValue == HIGH) {
        lastTiltState = !lastTiltState;
      }
    }
  }
  /* write the value to the LEDs*/
  digitalWrite(ledPin, sensorValue);
  lastTiltState = sensorValue;
}
