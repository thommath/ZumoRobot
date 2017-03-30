// TONES  ==========================================
#define  a2s    117
#define  d3     147
#define  d3s    156
#define  e3     165
#define  f3     175
#define  f3s    185
#define  g3     196
#define  a3s    233
#define  b3     247

#define  c4     262 
#define  d4     294 
#define  d4s    311
#define  e4     330 
#define  f4     349
#define  f4s    370 
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

#define MAX_COUNT 18

class Music{
    // MELODY and TIMING  =======================================
    //  melody[] is an array of notes, accompanied by beats[],
    
//    const int MAX_COUNT = 9; // Melody length, for looping.
    
    int melody[MAX_COUNT];
    int beats[MAX_COUNT];
    
  
    int soundPin;
    long tempo = 700;  // Set overall tempo
    long pauseTime = tempo/25;  // Set length of pause between notes
    int frequency = 0;  
    int beat = 0;
    long duration  = 0;
    
    
    int cliffhanger = 0;
    int cliffhangerino = 0;
    
  public:

    Music(int pin){
      soundPin = pin;
      
      melody[0] = d4;
      melody[1] = d4;
      melody[2] = d4;
      melody[3] = a3s;
      melody[4] = f4;
      melody[5] = d4;
      melody[6] = a3s;
      melody[7] = f4;
      melody[8] = d4;
      melody[9] = a4;
      melody[10] = a4;
      melody[11] = a4;
      melody[12] = a4s;
      melody[13] = f4;
      melody[14] = d4;
      melody[15] = a3s;
      melody[16] = f4;
      melody[17] = d4;
      

      beats[0] = 2;
      beats[1] = 2;
      beats[2] = 2;
      beats[3] = 3;
      beats[4] = 6;
      beats[5] = 2;
      beats[6] = 3;
      beats[7] = 6;
      beats[8] = 1;
      beats[9] = 2;
      beats[10] = 2;
      beats[11] = 2;
      beats[12] = 3;
      beats[13] = 6;
      beats[14] = 2;
      beats[15] = 3;
      beats[16] = 6;
      beats[17] = 1;
      
      
    }


    void init(){
      pinMode(soundPin, OUTPUT);
    }
    
    void play(){
      if (cliffhanger >= MAX_COUNT) {
        cliffhanger = 0;
        cliffhangerino = 0;
      }
      if (cliffhangerino == 0){
        frequency = melody[cliffhanger];
        beat = beats[cliffhanger];
        duration = tempo / beat; // Set up timing
        tone(soundPin, frequency, duration);
      }
      
      cliffhangerino++;
      
      if (cliffhangerino > (duration+pauseTime)/10.0){
        cliffhangerino = 0;
        cliffhanger++;
      }
    }

    String getStuff(){
      return String(cliffhanger) + " " + String(cliffhangerino);
    }
};

/*#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
*/
