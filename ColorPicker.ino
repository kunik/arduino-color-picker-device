const unsigned int RED = 9;
const unsigned int GREEN = 10;
const unsigned int BLUE = 11;

const unsigned int DELAY = 30;
const unsigned int STEP = 5;

const unsigned long MAX_RGB_VALUE = 16777215;
const unsigned int MAX_COLOR_VALUE = 255;

unsigned long color;
byte red;
byte green;
byte blue;

void setup()  { 
  Serial.begin(9600);
} 

void loop()  {
  if (Serial.available()) {
    color = parseHexFromSerial();
    Serial.println(color);

    blue = color / 65536;
    green = (color-(blue*65536)) / 256;
    red = color -(blue*65536) - (green*256);

    analogWrite(RED, red);
    analogWrite(GREEN, green);
    analogWrite(BLUE, blue);
  }

  delay(DELAY);
}

unsigned long parseHexFromSerial() {
  char hex_string[6] = {
    '0'  };
  long res;
  int i = 0;

  while (Serial.available() && i < 6) {
    hex_string[i] = Serial.read();
    i++;
  }

  res = strtoul(hex_string, 0, 16);

  return res;
}

unsigned long parseLongFromSerial() {
  unsigned long result = 0;
  int c;

  while (Serial.available()) {
    c = Serial.read() - '0';

    if (c > 9) {
      return result;
    }

    result = result * 10 + c;
  }

  return result;
}

void fadeIn(int pin) {
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue += STEP) { 
    // sets the value (range from 0 to 255):
    analogWrite(pin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(DELAY);                            
  }
}

void fadeOut(int pin) {
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -= STEP) { 
    // sets the value (range from 0 to 255):
    analogWrite(pin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(DELAY);                            
  }
}




