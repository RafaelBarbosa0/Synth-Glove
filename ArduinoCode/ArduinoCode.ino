// Libraries.
#include <MPU6050_tockn.h>
#include <MusicWithoutDelay.h>
#include <synth.h>
#include <tables.h>
#include <Wire.h>

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
float tonicChords[3][3] =
{
  // C
  {noteC, noteE, noteG},
  // Em
  {noteE, noteG, noteB},
  // Am
  {noteA, noteC, noteE}
};

// Subdominant.
float subdominantChords[2][3] =
{
  // Dm
  {noteD, noteF, noteA},
  // F
  {noteF, noteA, noteC}
};

// Dominant.
float dominantChords[2][3] =
{
  // G
  {noteG, noteB, noteD},
  // Bd
  {noteB, noteD, noteF}
};

// Pentatonic array.
float pentatonicScale[5] = {noteC, noteD, noteE, noteG, noteA};

// MPU object
MPU6050 mpu6050(Wire);

// Chord rotation threshold.
float rotationTreshold = 35;

// Previously played chord notes.
float previousNoteOne;
float previousNoteTwo;
float previousNoteThree;

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
  Serial.begin(9600);

  // Setup and calibrate MPU.
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  // Initialize instruments.
  chordBuzzerOne.begin(CHB, TRIANGLE, ENVELOPE0, 0);
  chordBuzzerTwo.begin(TRIANGLE, ENVELOPE0, 0);
  chordBuzzerThree.begin(TRIANGLE, ENVELOPE0, 0);

  melodyBuzzerOne.begin(TRIANGLE, ENVELOPE0, 0);
  melodyBuzzerTwo.begin(TRIANGLE, ENVELOPE0, 0);
  melodyBuzzerThree.begin(TRIANGLE, ENVELOPE0, 0);
  melodyBuzzerFour.begin(TRIANGLE, ENVELOPE0, 0);
  melodyBuzzerFive.begin(TRIANGLE, ENVELOPE0, 0);
}

void loop() 
{
  // Gets all data from MPU
  mpu6050.update();

  // Update instruments.
  chordBuzzerOne.update();
  chordBuzzerTwo.update();
  chordBuzzerThree.update();

  melodyBuzzerOne.update();
  melodyBuzzerTwo.update();
  melodyBuzzerThree.update();
  melodyBuzzerFour.update();
  melodyBuzzerFive.update();

  // Set instruments volume.
  chordBuzzerOne.setVolume(100);
  chordBuzzerTwo.setVolume(100);
  chordBuzzerThree.setVolume(100);

  melodyBuzzerOne.setVolume(100);
  melodyBuzzerTwo.setVolume(100);
  melodyBuzzerThree.setVolume(100);
  melodyBuzzerFour.setVolume(100);
  melodyBuzzerFive.setVolume(100);

  // Get amount of raised fingers on left hand.
  int raisedFingers = 0;

  // Left hand behavior.
  // Get correct chord array according to left hand orientation.
  if(mpu6050.getAngleY() > -rotationTreshold && mpu6050.getAngleY() < rotationTreshold)
  {
    // Correct chord is played according to amount of raised fingers.
    playChord(tonicChords[raisedFingers][0], tonicChords[raisedFingers][1], tonicChords[raisedFingers][2]);
  }

  else if(mpu6050.getAngleY() < -rotationTreshold)
  {
    playChord(subdominantChords[raisedFingers][0], subdominantChords[raisedFingers][1], subdominantChords[raisedFingers][2]);
  }

  else if(mpu6050.getAngleY() > rotationTreshold)
  {
    playChord(dominantChords[raisedFingers][0], dominantChords[raisedFingers][1], dominantChords[raisedFingers][2]);
  }
}

// Receives the notes for a chord and plays them, forming the chord.
void playChord(float noteOne, float noteTwo, float noteThree)
{
  // If were playing the same chord we don't want to run this again, so return.
  if(noteOne == previousNoteOne && noteTwo == previousNoteTwo && noteThree == previousNoteThree)
  {
    return;
  }

  // Play notes.
  chordBuzzerOne.setFrequency(noteOne);
  chordBuzzerTwo.setFrequency(noteTwo);
  chordBuzzerThree.setFrequency(noteThree);

  Serial.println("Played");

  // Save played notes to previously played to avoid overlap on next cycle.
  previousNoteOne = noteOne;
  previousNoteTwo = noteTwo;
  previousNoteThree = noteThree;
}