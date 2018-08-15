#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h> 


#define B3 2024
#define C4 1915
#define D4 1700
#define E4 1519
#define F4 1432
#define FS4 1352
#define G4 1275
#define GS4 415
#define A4 1136
#define AS4 1073
#define B4 1014
#define C5 956
#define D5 852

#define PIXELNUM 6
#define PIXELPIN 14
#define PIXELON  12
#define TONEPIN  4

#define SLEEPSECONDS 5


int song = 1;
bool mute = 1;
int rstReason;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel( PIXELNUM, PIXELPIN); 



/*******************************************************
 * Songs
 ********************************************************/

int tempo = 100;

int  Frostylength = 31;
int  Frostynotes[] = {G4, E4, F4, G4, C5, B4, C5, D5, C5, B4, A4, G4,0, B4, C5, D5, C5, B4, A4, A4, G4, C5, E4, G4, A4, G4, F4, E4, D4, C4, 0};
int  Frostybeats[] = {4, 4, 1, 2, 4, 1, 1, 2, 2, 2, 2, 4, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 4, 1};

int  Merrylength = 31;
int  Merrynotes[] = {D4, G4, G4, A4, G4, FS4, E4, E4, E4, A4, A4, B4, A4, G4, FS4, D4, D4, B4, B4, C5, B4, A4, G4, E4, D4, D4, E4, A4, FS4, G4, 0};
int  Merrybeats[] = {2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 4, 1};

int  Jinglelength = 27;
int  Jinglenotes[] = {B4, B4, B4, B4, B4, B4, B4, D5, G4, A4, B4,0, C5, C5, C5, C5, C5, B4, B4, B4, B4, A4, A4, B4, A4, D5, 0};
int  Jinglebeats[] = {2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 4,4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 1};

int Decklength = 18;
int Decknotes[] = {G4, F4, E4, D4, C4, D4, E4, C4, D4, E4, F4, D4, E4, D4, C4, B3, C4, 0};
int Deckbeats[] = {4, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 4, 1, 2, 2, 4, 1};

void setup() {

  Serial.begin(115200);
  pixels.begin();
  if (mute == false) pinMode(TONEPIN, OUTPUT);


  rst_info *rsti;
  rsti = ESP.getResetInfoPtr();
  rstReason = rsti->reason;
  Serial.println();
  Serial.print("ESP.getResetReason = ");
  Serial.println(ESP.getResetReason());
  Serial.println(String("ResetInfo.reason = ") + rstReason);

 
}

void loop() {


 
  // If reset button is pressed
  //if ( rstReason == 6) {
     song = random(0,4);
  
     Serial.print("Play song ");
     Serial.println(song);
     digitalWrite(PIXELON, HIGH);
  
     switch (song) {
      case 1:
        Frosty();
        song++;
        break;
      case 2:
        Merry();
        song++;
        break;
      case 3:
        Deck();
        song++;
        break;
      case 4:
        Jingle();
        song = 1;
        break;
    } 
  
  
    digitalWrite(PIXELON, LOW);
    digitalWrite(PIXELPIN, HIGH);
    Serial.println("EndLoop");
    ESP.deepSleep(SLEEPSECONDS*1000*1000);

//  }
//  else {
//
//    // Comprobar número de pulsaciones e ir a dormir....
//
//    Serial.println();
//    Serial.println(rstReason,DEC);
//    ESP.deepSleep(SLEEPSECONDS*1000*1000);
//    
//  }

}



void showRandomColors(int numPixel) { 

  int pixelColor[numPixel][3];
  
  //Fill Array of colors
  for (int i=0; i<numPixel; i++) {
    for (int j=0; j<3; j++) {
      pixelColor[i][j] = random(0,51);
    } 
    
    pixels.setPixelColor(i, pixels.Color(pixelColor[i][0], pixelColor[i][1], pixelColor[i][2])); // Set random colors

  }

  pixels.show();

}



void Frosty() {
  for (int i = 0; i < Frostylength; i++) {
    if (Frostynotes[i] == 0) {
      delay(Frostybeats[i] * tempo); // rest
      noTone(TONEPIN);
    } else {
      playNote(Frostynotes[i], Frostybeats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2);
    if (Frostynotes[i + 1] == Frostynotes[i]) {
      noTone(TONEPIN);
    }
  }
  noTone(TONEPIN);
}

void Merry() {
  for (int i = 0; i < Merrylength; i++) {
    if (Merrynotes[i] == 0) {
      delay(Merrybeats[i] * tempo); // rest
      noTone(TONEPIN);
    } else {
      playNote(Merrynotes[i], Merrybeats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2);
    if (Merrynotes[i + 1] == Merrynotes[i]) {
      noTone(TONEPIN);
    }
  }
  noTone(TONEPIN);
}

void Deck() {
  for (int i = 0; i < Decklength; i++) {
    if (Decknotes[i] == 0) {
      delay(Deckbeats[i] * tempo); // rest
      noTone(TONEPIN);
    } else {
      
      playNote(Decknotes[i], Deckbeats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2);
    if (Decknotes[i + 1] == Decknotes[i]) {
      noTone(TONEPIN);
    }
  }
  noTone(TONEPIN);
}

void Jingle() {
  for (int i = 0; i < Jinglelength; i++) {
    if (Jinglenotes[i] == 0) {
      delay(Jinglebeats[i] * tempo); // rest
      noTone(TONEPIN);
    } else {
      
      playNote(Jinglenotes[i], Jinglebeats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2);
    if (Jinglenotes[i + 1] == Jinglenotes[i]) {
      noTone(TONEPIN);
    }
  }
  noTone(TONEPIN);
}

void playNote(int note, int duration) {

  showRandomColors(PIXELNUM);
  playTone(note, duration);

}


void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(TONEPIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(TONEPIN, LOW);
    delayMicroseconds(tone);
  }
}

  


