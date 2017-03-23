const int soundPin      = 2;
const int buttonPin     = 12;

int buttonState = 0; 

// TONES  ==========================================
#define  a2s    117
#define  d3     147
#define  d3s    156
#define  e3     165
#define  f3     175
#define  g3     196
#define  a3s    233
#define  b3     247

#define  c4     262 
#define  d4     294 
#define  d4s    311
#define  e4     330 
#define  f4     349 
#define  g4     392 
#define  g4s    415
#define  a4     440 
#define  a4s    466
#define  b4     494 
#define  c5     523 
#define  c5s    554
#define  d5     587
#define  d5s    622
#define  e5     659
#define  f5     698
#define  f5s    740
#define  g5     784
#define  g5s    831

// Define a special note, 'R', to represent a rest
#define  R     0

// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[],
int melody[] = { d3, d3, d3, a2s, f3, d3, a2s, f3, d3 };
int beats[]  = { 2, 2, 2, 3, 6, 2, 3, 6, 1 };
int MAX_COUNT = 9; // Melody length, for looping.

long tempo = 1000;  // Set overall tempo
long pauseTime = tempo/25;  // Set length of pause between notes
int frequency = 0;  
int beat = 0;
long duration  = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(soundPin, OUTPUT);  
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
  // put your main code here, to run repeatedly:  
  // Set up a counter to pull from melody[] and beats[]
    for (int i=0; i<MAX_COUNT; i++) {
      frequency = melody[i];
      beat = beats[i];
      duration = tempo / beat; // Set up timing
      tone(soundPin, frequency, duration);
      delay(duration);
      delay(pauseTime); // A pause between notes...
    }
    delay(500); // A pause between melodies.
  }

}
