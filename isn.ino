#include "LedControl.h"
#include "Volume.h"

/* -----------------
       VAIRABLES
   ----------------- */
   
LedControl lc=LedControl(10,12,11,4);
Volume vol;

int trig = 2;
int echo = 3;
int potPin = 2;
int potVolPin = 1;
int potVal = 0; 
int potVolVal = 0;

int pos0 = 0;
int pos1 = 1;
int pos2 = 2;
int pos3 = 3;
int pos4 = 4;
int pos5 = 5;
int pos6 = 6;
int pos7 = 7;

long lecture_echo;

float cm;
float frequence;

/* -----------------
    INITIALISATION
   ----------------- */

void setup(){
  for (int i = 0; i <= 3; i++) {
    lc.shutdown(i,false);
    lc.setIntensity(i,10);
    lc.clearDisplay(i);
  }

  vol.begin();
  
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  
  Serial.begin(9600);
  Serial.println ("--- DEBUT ---");
}

/* -----------------
       EXECUTION
   ----------------- */

void loop(){
  potVal = analogRead(potPin);
  potVolVal = analogRead(potVolPin);
  potentiometre();
  
  ultrason();

  frequence = cm*potVal/32;

  volume();

  for (int i = potVal/127; i >= 0; i--) {
    delay(i*100);
    sinus();
  }

  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);

  console();
}

/* -----------------
       FONCTIONS
   ----------------- */

void ultrason() { //Système ultrason
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  lecture_echo = pulseIn(echo,HIGH);
  
  cm = lecture_echo / 58;
}

void volume() { //Détecte le potentiomètre pour changer le volume
  if (potVolVal/4 ==0) {
    for (int i = 0; i <= 3; i++) {
      lc.shutdown(i,true);
    }
    vol.noTone();
  } else {
    for (int i = 0; i <= 3; i++) {
      lc.shutdown(i,false);
    }
    vol.tone(frequence,potVolVal/4);
    vol.delay(0);
  }
}

void potentiometre() { //Permet d'afficher le palier de valeur des potentiomètres à la matrice
  for (int i = potVal/127; i >= 0; i--) {
    lc.setLed(0,i,7,true);
  }

  for (int i = potVolVal/127; i >= 0; i--) {
    lc.setLed(3,i,0,true);
  }
}

void sinus() { //Affiche une Sinus sur les écrans 1 et 2 de la matrice
  if (pos0<=16) {
    if (pos0 <= 8){
        lc.setLed(2,pos0,0,true);
        lc.setLed(1,pos0,7,true);
    }
  
    if (pos0 > 8) {
      lc.setLed(2,16-pos0,0,true);
      lc.setLed(1,16-pos0,7,true);
    }
  } else {
    pos0 = 0;
  } 
  pos0++;

  if (pos1<=16) {
      if (pos1 <= 8); {
        lc.setLed(2,pos1,1,true);
        lc.setLed(1,pos1,6,true);
      }
      if (pos1 > 8) {
        lc.setLed(2,16-pos1,1,true);
        lc.setLed(1,16-pos1,6,true);
      }
    } else {
      pos1 = 0;
  }
  pos1++;

  if (pos2<=16) {
    if (pos2 <= 8); {
      lc.setLed(2,pos2,2,true);
      lc.setLed(1,pos2,5,true);
     }
     if (pos2 > 8) {
      lc.setLed(2,16-pos2,2,true);
      lc.setLed(1,16-pos2,5,true);
     }
   } else {
      pos2 = 0;
  }
  pos2++;

  if (pos3<=16) {
    if (pos3 <= 8); {
      lc.setLed(2,pos3,3,true);
      lc.setLed(1,pos3,4,true);
    }
    if (pos3 > 8) {
      lc.setLed(2,16-pos3,3,true);
      lc.setLed(1,16-pos3,4,true);
    }
  } else {
    pos3 = 0;
  }
  pos3++;

  if (pos4<=16) {
    if (pos4 <= 8); {
      lc.setLed(2,pos4,4,true);
      lc.setLed(1,pos4,3,true);
    }
    if (pos4 > 8) {
      lc.setLed(2,16-pos4,4,true);
      lc.setLed(1,16-pos4,3,true);
    }
  } else {
    pos4 = 0;
  }
  pos4++;

  if (pos5<=16) {
    if (pos5 <= 8); {
      lc.setLed(2,pos5,5,true);
      lc.setLed(1,pos5,2,true);
    }
    if (pos4 > 8) {
      lc.setLed(2,16-pos5,5,true);
      lc.setLed(1,16-pos5,2,true);
    }
  } else {
    pos5 = 0;
  }
  pos5++;
  
  if (pos6<=16) {
    if (pos6 <= 8); {
      lc.setLed(2,pos6,6,true);
      lc.setLed(1,pos6,1,true);
    }
    if (pos6 > 8) {
      lc.setLed(2,16-pos6,6,true);
      lc.setLed(1,16-pos6,1,true);
    }
  } else {
    pos6 = 0;
  }
  pos6++;
  
  if (pos7<=16) {
    if (pos7 <= 8); {
      lc.setLed(2,pos7,7,true);
      lc.setLed(1,pos7,0,true);
    }
    if (pos7 > 8) {
      lc.setLed(2,16-pos7,7,true);
      lc.setLed(1,16-pos7,0,true);
    }
  } else {
    pos7 = 0;
  }
  pos7++;
} 

void console() { //Affiche les valeurs à la console Arduino
  Serial.print("--------------------\n");

  Serial.print("Valeur Pot: ");
  Serial.println(potVal);

  Serial.print("Valeur Pot2: ");
  Serial.println(potVolVal);

  Serial.print("Distance en cm: ");
  Serial.println(cm);
  
  Serial.print("Fréquence: ");
  Serial.println(frequence);
}
