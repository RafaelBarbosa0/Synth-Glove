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

// Melody buzzer array.
MusicWithoutDelay melodyArray[5] = {melodyBuzzerOne, melodyBuzzerTwo, melodyBuzzerThree, melodyBuzzerFour, melodyBuzzerFive};

// Buzzer variables.
int buzzerVolume = 90;

// Flex sensor pins.
const int flexLeftThumb = A0;
const int flexLeftIndex = A1;
const int flexLeftMiddle = A2;

const int flexRightThumb = A3;
const int flexRightIndex = A4;
const int flexRightMiddle = A5;
const int flexRightRing = A6;
const int flexRightPinky = A7;

// Left hand flex array.
int leftFlexArray[3] = {flexLeftThumb, flexLeftIndex, flexLeftMiddle};

// Right hand flex array.
int rightFlexArray[5] = {flexRightThumb, flexRightIndex, flexRightMiddle, flexRightRing, flexRightPinky};

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
  chordBuzzerOne.setVolume(buzzerVolume);
  chordBuzzerTwo.setVolume(buzzerVolume);
  chordBuzzerThree.setVolume(buzzerVolume);

  melodyBuzzerOne.setVolume(buzzerVolume);
  melodyBuzzerTwo.setVolume(buzzerVolume);
  melodyBuzzerThree.setVolume(buzzerVolume);
  melodyBuzzerFour.setVolume(buzzerVolume);
  melodyBuzzerFive.setVolume(buzzerVolume);

  // Get amount of raised fingers on left hand.
  int raisedFingers = 2;

  // Check if each finger on left hand is flexed or not.
  // For each non flexed finger, add one to raised finger count.
  for(int i = 0; i < 3; i++)
  {
    bool fingerFlexed;

    fingerFlexed = IsFlexed(leftFlexArray[i]);

    if(fingerFlexed == true)
    {
      raisedFingers--;
    }
  }


  // Left hand behavior.
  // Get correct chord array according to left hand orientation.

  If there is at least one raised fingers a chord will play.
  if(raisedFingers >= 0)
  {
      // Unmute instruments if are muted.
      if(chordBuzzerOne.isMuted())
      {
        chordBuzzerOne.mute(false);
        chordBuzzerTwo.mute(false);
        chordBuzzerThree.mute(false);
      }

      // Tonic chords.
      if(mpu6050.getAngleY() > -rotationTreshold && mpu6050.getAngleY() < rotationTreshold)
      {
        // Correct chord is played according to amount of raised fingers.
        PlayChord(tonicChords[raisedFingers][0], tonicChords[raisedFingers][1], tonicChords[raisedFingers][2]);
      }

      // Dominant and subdominant only have 2 chords so if 3 fingers are raised we act as if there's 2.
      if(raisedFingers == 2) raisedFingers = 1;

      // Subdominant chords.
      else if(mpu6050.getAngleY() < -rotationTreshold)
      {
        // Correct chord is played according to amount of raised fingers.
        PlayChord(subdominantChords[raisedFingers][0], subdominantChords[raisedFingers][1], subdominantChords[raisedFingers][2]);
      }

      // Dominant chords.
      else if(mpu6050.getAngleY() > rotationTreshold)
      {
        // Correct chord is played according to amount of raised fingers.
        PlayChord(dominantChords[raisedFingers][0], dominantChords[raisedFingers][1], dominantChords[raisedFingers][2]);
      }
  }

  // If there are no raised fingers, no chord will play.
  else
  {
    // Mute buzzers if unmuted.
    if(chordBuzzerOne.isMuted() == false)
    {
    chordBuzzerOne.mute(true);
    chordBuzzerTwo.mute(true);
    chordBuzzerThree.mute(true);
    }

    // Reset previous note.
    previousNoteOne = 0;
    previousNoteTwo = 0;
    previousNoteThree = 0;
  }

  // Right hand behavior.
  for(int i = 0; i < 5; i++)
  {
    bool rightFlexed;
    rightFlexed = IsFlexed(rightFlexArray[i]);

    if(rightFlexed)
    {
      melodyArray[i].mute(false);

      melodyArray[i].setFrequency(pentatonicScale[i]);
    }
    else
    {
      melodyArray[i].mute(true);
    }
  }
}


// Functions //

// Receives a pin interfacing with flex sensor and checks if flex sensor is flexed or not.
bool IsFlexed(int pin)
{
  // Read value from flex sensor on analog pin.
  int flexValue;
  flexValue = analogRead(pin);

  // Check if it's flexed according to value.
  bool flexed;
  // CHANGE LATER.
  if(pin == A3)
  {
    if(flexValue >= 1018) flexed = false;
    else flexed = true;
  }

  else flexed = false;

  // Return bool.
  return flexed;
}

// Receives the notes for a chord and plays them, forming the chord.
void PlayChord(float noteOne, float noteTwo, float noteThree)
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

  // Save played notes to previously played to avoid overlap on next cycle.
  previousNoteOne = noteOne;
  previousNoteTwo = noteTwo;
  previousNoteThree = noteThree;
}