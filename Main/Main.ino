// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      40




// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int color = 1;
float read1 = 0;
float read2 = 0;
int countRead = 0;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show(); // Initialize all pixels to 'off'
  pixels.setBrightness(20);

  // to view print
  Serial.begin(9600);
}



void loop() {
  // READ FROM MICRO  
  // read the value from the sensor:
  int sensorPin = 1;    //Microphone Sensor Pin on analog 4
  int sensorValue = 0;
  sensorValue = analogRead(sensorPin); 
  
  // print out the value you read:
  float var = log((float)sensorValue);
  float db = 16.801 * var ;// + 9.872;

  //Serial.println(countRead);
  
  countRead = countRead +1;
  if(countRead==1){
    read1 = db;
    return;
  }else if(countRead==2){
    read2 = db;
    return;
  }else if(countRead==3){
    db = (read1+read2+db)/3;
    countRead = 0;
  }
  Serial.println(db); // To debug

  // calculate new color
  int newColor;

  if(db > 70){
    newColor=2; // Red
  } else if (db < 60) {
    newColor=0; // Green
  } else {
    newColor=1; // Orange
  }
  
  //Serial.println("Color "); 
  //Serial.println(color);
  //Serial.println(newColor);
  //Serial.println("### "); 
  // if color is diference since last check
  if(color != newColor){ 
    //Serial.println("Dif ");
    if(newColor == 0){
      colorRandomPixel(pixels.Color(0, 255, 0),10); //GREEN
    }else if(newColor == 1){
      colorRandomPixel(pixels.Color(255, 250, 0),20);// Orange
    }else if(newColor == 2){
      colorWipe(pixels.Color(255, 0, 0)); // RED
    }
  }else{
    //Serial.println("Igual ");
  }
  color = newColor;
  
  //delay(1000);
  delay(500);
}


// color some pixeis from shield
void colorRandomPixel(uint32_t c,int num_pixel){
  int selectedRadomLed[num_pixel];
  for( int i=0 ;i < num_pixel; i++){
    int randomPixel =  0;
    randomPixel = random(0,NUMPIXELS);  
    selectedRadomLed[i] = randomPixel ;
  }
  colorWipe(pixels.Color(0, 0, 0)); 
  colorWipeArray(c,selectedRadomLed,num_pixel); 
}


// Fill the dots one after the other with a color
void colorWipeArray(uint32_t c,int array[], int maxi) {
  for(uint16_t i=0; i<maxi; i++) {
    pixels.setPixelColor(array[i], c);
    pixels.show();
    //delay(50);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    //delay(50);
  }
}


