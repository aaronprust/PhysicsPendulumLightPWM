
//ATtiny85 RGB color fading Mood Light NOW WITH LIGHT SENSING CAPABILI

const int redPin = 3; 
const int grnPin = 4; 
const int bluPin = 2;
const int sensor = 0;

const int highVal = HIGH;
const int lowVal = LOW;

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 5;    // the debounce time; increase if the output flickers

float currentRedVal = 0, currentGreenVal = 0, currentBlueVal = 0;


int colorMode = 0;

struct _Object {
   void (* functionPointer)();
};

struct _Object Object;
 
 struct _circle {
   float x;
   float y;
   float mass;
};

struct _line {
   float x0, x;
   float y0, y;
};

//Physics Constants
float d2Theta1 = 0;
float d2Theta2 = 0;
float dTheta1  = 0;
float dTheta2  = 0;
float Theta1   = 0*(PI)/2;
float Theta2   = 2.3*(PI)/2;
float m1     = 10;
float m2     = 5;
float l1     = 64;
float l2     = 64;
float X0     = 64;
float Y0     = 0;
float g      = 9.8;
float time   = 0.3;

struct _circle circle1;
  struct _circle circle2;
  struct _line line1;
  struct _line line2;

// list of functions possible to start with


//  fadeWhiteUpAndDown
  //fadeColorsUpAndDown


void setup()
{
  pinMode(redPin, OUTPUT);    
  pinMode(grnPin, OUTPUT);    
  pinMode(bluPin, OUTPUT);
  pinMode(sensor, INPUT_PULLUP);

  digitalWrite(redPin, lowVal);
  digitalWrite(grnPin, lowVal);
  digitalWrite(bluPin, lowVal);
   
  Object.functionPointer = fadePendulum;
  
  
/*
var line1 = {x0: X0, y0: Y0, x: 0, y: 0};
  var line2 = {x0: 0, y0: 0, x: 0, y: 0};
  var circle1 = {x: X0+l1*sin(Theta1), y: Y0+l1*cos(Theta1), mass: m1};
  var circle2 = {x: X0+l1*sin(Theta1)+l2*sin(Theta2), y: Y0+l1*cos(Theta1)+l2*cos(Theta2), mass: m2};
  */
  line1.x0 = X0;
  line1.y0 = Y0;
  line1.x = 0;
  line1.y = 0;
  
  line2.x0 = 0;
  line2.y0 = 0;
  line2.x = 0;
  line2.y = 0;
  
  circle1.x =  X0+l1*sin(Theta1);
  circle1.y = Y0+l1*cos(Theta1);
  circle1.mass = m1;
  
  circle2.x =  X0+l1*sin(Theta1)+l2*sin(Theta2);
  circle2.y = Y0+l1*cos(Theta1)+l2*cos(Theta2);
  circle2.mass = m2;
  
  //attachInterrupt(sensor,wakeUpNow, LOW); // interrupt : INT0 (pin 2) (works on LOW, nothing else works)
}

void loop() {

  //setSolidRed();
  //Object.functionPointer();
 
  pulseWidthModulationColor(currentRedVal, currentGreenVal, currentBlueVal);
  readModeSwitchValue();
  
  Object.functionPointer();


 
 
 //  redtoyellow();
  //  yellowtogreen();
//    greentocyan();
 //   cyantoblue();
  //  bluetomagenta();
  // magentatored();
}

boolean initialized = 0;

float redAngle = 0, greenAngle = 0, blueAngle, redSin, greenSin, blueSin, whiteAngle, whiteAngle2, whiteAngle3, whiteSin, whiteSin2, whiteSin3;
float whiteFadeSpeed = 0.01;
float whiteFadeSpeed2 = 0.001;
float whiteFadeSpeedVarying = 0, whiteSinVarying, whiteFadeSpeedVarying2, whiteSinVarying2;
/*
function animate(circle1, circle2, line1, line2, canvas, context) {
  mu      =  1+m1/m2;
  d2Theta1  =  (g*(sin(Theta2)*cos(Theta1-Theta2)-mu*sin(Theta1))-(l2*dTheta2*dTheta2+l1*dTheta1*dTheta1*cos(Theta1-Theta2))*sin(Theta1-Theta2))/(l1*(mu-cos(Theta1-Theta2)*cos(Theta1-Theta2)));
  d2Theta2  =  (mu*g*(sin(Theta1)*cos(Theta1-Theta2)-sin(Theta2))+(mu*l1*dTheta1*dTheta1+l2*dTheta2*dTheta2*cos(Theta1-Theta2))*sin(Theta1-Theta2))/(l2*(mu-cos(Theta1-Theta2)*cos(Theta1-Theta2)));
  dTheta1   += d2Theta1*time;
  dTheta2   += d2Theta2*time;
  Theta1    += dTheta1*time;
  Theta2    += dTheta2*time;

  circle1.x = X0+l1*sin(Theta1);
  circle1.y = Y0+l1*cos(Theta1);
  circle2.x = X0+l1*sin(Theta1)+l2*sin(Theta2);
  circle2.y = Y0+l1*cos(Theta1)+l2*cos(Theta2);

  line1.x  = circle1.x;
  line1.y  = circle1.y;
  line2.x0 = circle1.x;
  line2.y0 = circle1.y;
  line2.x  = circle2.x;
  line2.y  = circle2.y;

  context.clearRect(0, 0, canvas.width, canvas.height);

  drawLine(line1, context);
  drawLine(line2, context);
  drawCircle(circle1, context);
  drawCircle(circle2, context);
}
*/

float mu; 
float adjustedVal;
float adjustedVal2;
float adjustedVal3;
float adjustedVal4;

float lastTime;
float timeBeforeLast;

void fadePendulum()
{
  lastTime = millis();
  
  timeBeforeLast += lastTime;
  
   mu      =  1+m1/m2;
   
  /* if(timeBeforeLast - lastTime > random(1000000, 9000000))
  {
      dTheta2 = PI/10;
  }  
  */
  /*if (dTheta1 == 0)
  {
    dTheta1 = PI;
    
  }
  if (dTheta2 == 0)
  {
    dTheta2 = PI;
    
  }*/

  d2Theta1  =  (g*(sin(Theta2)*cos(Theta1-Theta2)-mu*sin(Theta1))-(l2*dTheta2*dTheta2+l1*dTheta1*dTheta1*cos(Theta1-Theta2))*sin(Theta1-Theta2))/(l1*(mu-cos(Theta1-Theta2)*cos(Theta1-Theta2)));
  d2Theta2  =  (mu*g*(sin(Theta1)*cos(Theta1-Theta2)-sin(Theta2))+(mu*l1*dTheta1*dTheta1+l2*dTheta2*dTheta2*cos(Theta1-Theta2))*sin(Theta1-Theta2))/(l2*(mu-cos(Theta1-Theta2)*cos(Theta1-Theta2)));
  dTheta1   += d2Theta1*time;
  dTheta2   += d2Theta2*time;
  Theta1    += dTheta1*time;
  Theta2    += dTheta2*time;

  if(Theta1 > 2*PI)
  {
    Theta1 -= 2*PI;
  }
  
  if(Theta2 > 2*PI)
  {
    Theta2 -= 2*PI;
  }

  circle1.x = X0+l1*sin(Theta1);
  circle1.y = Y0+l1*cos(Theta1);
  circle2.x = X0+l1*sin(Theta1)+l2*sin(Theta2);
  circle2.y = Y0+l1*cos(Theta1)+l2*cos(Theta2);

  line1.x  = circle1.x;
  line1.y  = circle1.y;
  line2.x0 = circle1.x;
  line2.y0 = circle1.y;
  line2.x  = circle2.x;
  line2.y  = circle2.y;
  
  adjustedVal = circle2.x + 128;
  adjustedVal2 = circle2.y + 128;
    adjustedVal3 = circle1.x + 128;
    adjustedVal4 = circle1.y + 128;
  
    adjustedVal = constrain(adjustedVal, 0, 255); 
    adjustedVal2 = constrain(adjustedVal2, 0, 255); 
    adjustedVal3 = constrain(adjustedVal3, 0, 255); 
     adjustedVal4 = constrain(adjustedVal4, 0, 255); 

    currentRedVal = adjustedVal;
    currentGreenVal = adjustedVal2;
    currentBlueVal = adjustedVal4;
    
     if (adjustedVal > 1)
     {
   //   currentBlueVal = 0;
     }
    else
    {
  
 d2Theta1 = 0;
 d2Theta2 = 0;
 dTheta1  = 0;
 dTheta2  = 0;
 Theta1   = 0*(PI)/2;
 Theta2   = 2.3*(PI)/2;
 m1     = 10;
 m2     = 5;
 l1     = 64;
 l2     = 64;
 X0     = 64;
 Y0     = 0;
 g      = 11.8;
 time   = 0.3;
 
    }

  
}

void fadeWhiteUpAndDown()
{

  if(whiteAngle < 6.283)
  {
    whiteAngle = whiteAngle + whiteFadeSpeed;
    whiteSin = sin(whiteAngle) * 127.5 + 127.5;
    currentRedVal = whiteSin;
    currentGreenVal = whiteSin;
    currentBlueVal = whiteSin;
  }
  else
  {
    whiteAngle = 0;
  }  
}

void fadeWhiteUpAndDownInterferingWaves()
{
 if(whiteAngle < 6.283)
  {
    whiteAngle = whiteAngle + whiteSinVarying;
    whiteSin = sin(whiteAngle) * 127.5 + 127.5;
    whiteAngle2 = whiteAngle2 + whiteSinVarying2;
    whiteSin2 = sin(whiteAngle2) * 127.5 + 127.5;
    float sinSum;
    sinSum = sqrt((whiteSin2 - whiteSin)*(whiteSin2 - whiteSin));
    if(sinSum > 255)
     {
       sinSum = 255;
     }
     if(sinSum < 0)
     {
       sinSum = 0;
     }
    currentRedVal = sinSum;
    currentGreenVal = sinSum;
    currentBlueVal = sinSum;
  }
  else
  {
    whiteAngle = 0;
  }  
  if(whiteFadeSpeedVarying < 6.283)
  {
    whiteFadeSpeedVarying = whiteFadeSpeedVarying + 0.005;
//    out = sin(in) * range + offset
    whiteSinVarying = sin(whiteFadeSpeedVarying)/50;
    
  }
  else
  {
    whiteFadeSpeedVarying = 0;
  }  
   if(whiteFadeSpeedVarying2 < 6.283)
  {
    whiteFadeSpeedVarying2 = whiteFadeSpeedVarying2 + 0.0001;
//    out = sin(in) * range + offset
    whiteSinVarying2 = sin(whiteFadeSpeedVarying2)/50;
    
  }
  else
  {
    whiteFadeSpeedVarying2 = 0;
  }  
}

void fadeWhiteUpAndDownWithVaryingFadeSpeed()
{

  if(whiteAngle < 6.283)
  {
    whiteAngle = whiteAngle + whiteSinVarying;
    whiteSin = sin(whiteAngle) * 127.5 + 127.5;
    currentRedVal = whiteSin;
    currentGreenVal = whiteSin;
    currentBlueVal = whiteSin;
  }
  else
  {
    whiteAngle = 0;
  }  
  if(whiteFadeSpeedVarying < 6.283)
  {
    whiteFadeSpeedVarying = whiteFadeSpeedVarying + 0.001;
//    out = sin(in) * range + offset
    whiteSinVarying = sin(whiteFadeSpeedVarying)/25;
    
  }
  else
  {
    whiteFadeSpeedVarying = 0;
  }  
}

void fadeColorsUpAndDown()
{

  if(redAngle < 6.283)
  {
    redAngle = redAngle + 0.01;
    redSin = sin(redAngle) * 127.5 + 127.5;
    currentRedVal = redSin;
  }
  else
  {
    redAngle = 0;
  }  
  if(greenAngle < 6.283)
  {
    greenAngle = greenAngle + 0.01;
    greenSin = cos(greenAngle) * 127.5 + 127.5;
    currentGreenVal = greenSin;
  }
  else
  {
    greenAngle = 0;
  }  
  
  if(blueAngle < 6.283)
  {
    blueAngle = blueAngle + 0.001;
    blueSin = sin(blueAngle) * 127.5 + 127.5;
    currentBlueVal = blueSin;
  }
  else
  {
    blueAngle = 0;
  }
}

void setSolidWhite()
{
  currentRedVal = 255;
  currentGreenVal = 255;
  currentBlueVal = 255;
}

void setSolidGreen()
{
  currentRedVal = 0;
  currentGreenVal = 255;
  currentBlueVal = 0;
}


void setSolidRed()
{
  currentRedVal = 255;
  currentGreenVal = 0;
  currentBlueVal = 0;
}

void setSolidBlue()
{
  currentRedVal = 0;
  currentGreenVal = 0;
  currentBlueVal = 255;
}

void setSolidYellow()
{
  currentRedVal = 255;
  currentGreenVal = 50;
  currentBlueVal = 0;
}

void setSolidPurple()
{
  currentRedVal = 255;
  currentGreenVal = 0;
  currentBlueVal = 255;
}


void setMode()
{
      if (colorMode > 7)
    {
      colorMode = 0;
    }
  
  // set the LED:
//  digitalWrite(ledPin, ledState);
  
   if(colorMode == 0)
     {
        Object.functionPointer = setSolidPurple;
     }
     else if (colorMode == 1)
     {
          Object.functionPointer = fadePendulum;
     }
     else if (colorMode == 2)
     {
        Object.functionPointer = setSolidRed;
     }
     else if (colorMode == 3)
     {
          Object.functionPointer = fadeColorsUpAndDown;
     }
     else if (colorMode == 4)
     {
        Object.functionPointer = setSolidBlue;
//        Object.functionPointer = setSolidRed;
     }
     else if (colorMode == 5)
     {          
          Object.functionPointer = fadeWhiteUpAndDownWithVaryingFadeSpeed;
     }
     else if (colorMode == 6)
     {
        Object.functionPointer = setSolidYellow;
//        Object.functionPointer = setSolidRed;
     }
     else if (colorMode == 7)
     {
     //     Object.functionPointer = fadeWhiteUpAndDownInterferingWaves;
//        Object.functionPointer = setSolidRed;
          Object.functionPointer = fadeWhiteUpAndDown;
     }
     else if (colorMode == 8)
     {
//          Object.functionPointer = fadeWhiteUpAndDownInterferingWaves;
        Object.functionPointer = setSolidWhite;
     }
     else if (colorMode == 9)
     {
//          Object.functionPointer = fadeWhiteUpAndDownInterferingWaves;
          Object.functionPointer = fadeWhiteUpAndDown;
     }
     else
     {

       currentRedVal = 255;
       currentGreenVal = 255;
       currentBlueVal = 255;
     }
}


void readModeSwitchValue(){
// read the state of the switch into a local variable:
  int reading = digitalRead(sensor);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        colorMode++;
          setMode();
         // Object.functionPointer();
 
      }
    }
  }
}

void wakeUpNow() 
{
  //execute wakeup code here before going back to loop
 currentRedVal = 0;
 currentGreenVal = 0;
 currentBlueVal = 255;
 }

void pulseWidthModulationColor(byte redVal, int greenVal, int blueVal)
{
  for (int i = 0; i < 256; i++)
  {
    if (i <= redVal)
    {
      digitalWrite(redPin, highVal); 
    }
    else
    {
      digitalWrite(redPin, lowVal); 
    }
    if (i <= greenVal)
    {
      digitalWrite(grnPin, highVal); 
    }
    else
    {
      digitalWrite(grnPin, lowVal); 
    }
        if (i <= blueVal)
    {
      digitalWrite(bluPin, highVal); 
    }
    else
    {
      digitalWrite(bluPin, lowVal); 
    }
/*   digitalWrite(redPin, i <= redVal);
   digitalWrite(grnPin, i <= greenVal);
   digitalWrite(bluPin, i <= blueVal);*/
  }
}
