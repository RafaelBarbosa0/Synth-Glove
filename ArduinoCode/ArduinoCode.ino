#include <MusicWithoutDelay.h>
#include <synth.h>
#include <tables.h>

// Notes.
const float noteA = 440.00;
const float noteB = 493.88;
const float noteC = 261.63;
const float noteD = 293.66;
const float noteE = 329.63;
const float noteF = 349.23;
const float noteG = 392.00;

// Chord arrays.
// Tonic.
float chordC[3] = {noteC, noteE, noteG};
float chordEm[3] = {noteE, noteG, noteB};
float chordAm[3] = {noteA, noteC, noteE};

// Subdominant.
float chordDm[3] = {noteD, noteF, noteA};
float chordF[3] = {noteF, noteA, noteC};

// Dominant.
float chordG[3] = {noteG, noteB, noteD};
float chordBd[3] = {noteB, noteD, noteF};

// Pentatonic array.
float pentatonicScale[5] = {noteC, noteD, noteE, noteG, noteA};

// Buzzers.
// Chord buzzers.
MusicWithoutDelay chordBuzzerOne;
MusicWithoutDelay chordBuzzerTwo;
MusicWithoutDelay chordBuzzerThree;

// Melody buzzers.
MusicWithoutDelay melodyBuzzerOne;
MusicWithoutDelay melodyBuzzerTwo;
MusicWithoutDelay melodyBuzzerThree;
MusicWithoutDelay melodyBuzzerFour;
MusicWithoutDelay melodyBuzzerFive;

void setup() 
{

}

void loop() 
{

}
