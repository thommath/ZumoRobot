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

#define MAX_COUNT 13

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
      
      melody[0] = d3;
      melody[1] = d3;
      melody[2] = d3;
      melody[3] = a2s;
      melody[4] = f3;
      melody[5] = d3;
      melody[6] = a2s;
      melody[7] = f3;
      melody[8] = d3;
      melody[9] = f3;
      melody[10] = f3;
      melody[11] = f3;
      melody[12] = f3s;

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
