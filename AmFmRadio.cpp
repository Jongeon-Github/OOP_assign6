/*
* Filename: AmFmRadio.cpp
* Project: OOP-assign2 (and assign4)
* Student ID: 8790144
* By: Jongeon Lee
* Date: Jul 29, 2023
* Description: This represents a radio with AM/FM capabilities, allowing users
*             to control power, volume, frequency, presets, and display settings.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "AmFmRadio.h"

#pragma warning(disable:4996)

#define EQUAL 0

using namespace std;


/*
* Function: AmFmRadio(bool On)
* Description: Initialize the values.
* Parameters: bool On : Radao On/Off
*/

AmFmRadio::AmFmRadio(bool On) {
    
    // Initialize member variables
    on = false;
    userVolume = (int)0;
    volume = (int)0;
    previousVolume = (int)0;
    previousFreq = { (int)530, (float)87.9 };
    currentFreq = { (int)530, (float)87.9 };
    strcpy(band, "AM");
    band[sizeof(band) - 1] = '\0';
    strcpy(userInputBuf, "\0");
    current_station = (double)530.0;
    SetDisplayOutput(true);
    copyBand = new char[3];
    for (int i = 0; i < 5; ++i) {
        presets[i].AMFreq = (int)530;
    }
    for (int j = 0; j < 5; ++j) {
        presets[j].FMFreq = (float)87.9;
    }
    displayDestructor = true;
}


/*
* Function: AmFmRadio(bool On, Freqs initialPresets[5])
* Description: Initialize the values.
* Parameters
*       bool On : Radao On/Off
*       Freqs initialPresets[5] : Set frequency from user
* Returns:
*/

AmFmRadio::AmFmRadio(bool On, Freqs initPresets[5]) {
    // Initialize member variables with initial presets
    on = false;
    userVolume = (int)0;
    volume = (int)0;
    previousVolume = (int)0;
    previousFreq = { (int)530, (float)87.9 };
    currentFreq = { (int)530, (float)87.9 };
    strcpy(band, "AM");
    band[sizeof(band) - 1] = '\0';
    strcpy(userInputBuf, "\0");
    current_station = (double)530.0;
    SetDisplayOutput(on);
    copyBand = new char[3];
    for (int i = 0; i < 5; ++i) {
        presets[i].AMFreq = initPresets[i].AMFreq;
        presets[i].FMFreq = initPresets[i].FMFreq;
    }
    displayDestructor = true;
}


/*
* Function: PowerToggle()
* Description: Toggles the power state of the car radio.
* Parameters: None
* Returns: None
*/

void AmFmRadio::PowerToggle() {
    if (on == true) {
        // Turn off the radio
        on = false;
        previousVolume = volume;
        volume = 0;
    }
    else {
        // Turn on the radio
        on = true;
        if (previousVolume == 0) {
            volume = 0;
        }
        else {
            volume = previousVolume;
        }

        if (previousFreq.AMFreq != 530) {
            currentFreq.AMFreq = previousFreq.AMFreq;
        }
        /* feedback fix */
        else {
            currentFreq.AMFreq = (int)530; // Set default AM frequency if previous frequency was 530
        }
     
        if (previousFreq.FMFreq != 87.9) {
            currentFreq.FMFreq = previousFreq.FMFreq;
        }
        /* feedback fix */
        else {
            currentFreq.FMFreq = (float)87.9; // Set default FM frequency if previous frequency was 87.9
        }
    }
}


/*
* Function: SetVolume()
* Description: Prompts the user to set the volume of the car radio.
* Parameters: None
* Returns: None
*/

void AmFmRadio::SetVolume() {
    if (on) {
        cout << "Enter the volume level (0 - 100): ";
        fgets(userInputBuf, sizeof(userInputBuf), stdin);
        userVolume = atoi(userInputBuf);       
        SetVolume(userVolume);
    }
    else {
        // delete for requirements
//        cout << "AmFm Radio is off." << endl;
    }
}


/*
* Function: SetVolume(int vol)
* Description: Prompts the user to set the volume of the car radio.
* Parameters: int vol : User input to set volume.
* Returns: None.
*/

void AmFmRadio::SetVolume(int vol) {
    /* feedback fix */
    if (vol < 0) {
        vol = 0;
        cout << "## The available volume is from 0 to 100." << endl;
        cout << "## Automatically changes to 0" << endl << endl;
    }
    else if (vol > 100) {
        vol = 100;
        cout << "## The available volume is from 0 to 100." << endl;
        cout << "## Automatically changes to 100" << endl << endl;
    }
    volume = vol;
}


/*
* Function: ToggleBand()
* Description: Toggles the frequency band between AM and FM.
* Parameters: None.
* Returns: None.
*/

void AmFmRadio::ToggleBand() {
    if (on) {
        // Toggle between AM and FM bands
        currentFreq = GetCurrentFrequency();
        if (strcmp(band, "AM") == EQUAL) {
            strcpy(band, "FM");
            current_station = (double)currentFreq.FMFreq;
        }
        else {
            strcpy(band, "AM");
            current_station = (double)currentFreq.AMFreq;
        }
    }
    else {
        // delete for requirements
//        cout << "AmFm Radio is off." << endl;
    }
}


/*
* Function: SetPresetButton(int buttonNum)
* Description: Sets the specified button (radio preset) with the current station.
* Parameters: int buttonNum : User input to set presents list.
* Returns: int value : 1 is Set button is working well, 0 is invaild number, -2 is Radao is off.
*/

int AmFmRadio::SetPresetButton(int buttonNum) {
    if (on && buttonNum >= 0 && buttonNum < 5) {
        // Set the preset button with the current frequency based on the current band
        if (strcmp("AM", band) == EQUAL) {
            presets[buttonNum].AMFreq = (int)current_station;
        }
        else {
            presets[buttonNum].FMFreq = round((float)current_station * 100) / 100;
        }
        return 1; // Set button is working well
    }
    else if (!on) {
        // delete for requirements
//        cout << "AmFm Radio is off." << endl;
        return -2;  // Radio is off
    }
    else {
        return 0;
    }
}


/*
* Function: SelectPresetButton(int buttonNum)
* Description: Sets the current station to the radio preset specified by the button number.
* Parameters: int buttonNum : User input to select Freq.
* Returns: 1 is Set button is working well, 0 is invaild number, -2 is Radao is off.
*/

int AmFmRadio::SelectPresetButton(int buttonNum) {
    if (on && buttonNum >= 0 && buttonNum < 5) {
        // Select the preset button and set the current frequency based on the current band
        if (strcmp("AM", band) == EQUAL) {
            current_station = (int)presets[buttonNum].AMFreq;
            currentFreq.AMFreq = (int)current_station;
        }
        else {
            current_station = (float)presets[buttonNum].FMFreq;
            currentFreq.FMFreq = (float)current_station;
        }
        return 1; // Set button is working well
    }
    else if (!on) {
        // delete for requirements
//        cout << "AmFm Radio is off." << endl;
        return -2;  // Radio is off
    }
    else {
        return 0;
    }
}


/*
* Function: ShowCurrentSettings()
* Description: Displays the current settings of the car radio.
* Parameters: None.
* Returns: None.
*/

void AmFmRadio::ShowCurrentSettings() {
    // Display the current settings of the radio
    /* feedback fix */
    if (displayOutput == true)
    {
        current_station = round(current_station * 100) / 100;
        cout << endl << "*** Current Settings ***" << endl;
        cout << (on ? " - Radio is On" : " - Radio is Off") << endl;
        cout << " - Volume: " << volume << endl;
        cout << " - Current Frequency: " << band << ": " << current_station << endl;
        cout << endl << "AM/FM Frequency list" << endl;
        cout << "AM List: " << presets[0].AMFreq << ", " << presets[1].AMFreq << ", " << presets[2].AMFreq << ", " << presets[3].AMFreq << ", " << presets[4].AMFreq << endl;
        cout << "FM List: " << presets[0].FMFreq << ", " << presets[1].FMFreq << ", " << presets[2].FMFreq << ", " << presets[3].FMFreq << ", " << presets[4].FMFreq << endl << endl;
    }   
}


/*
* Function: ScanUp()
* Description: Changes the frequency up in increments of 0.2 for FM or 10 for AM.
* Parameters: None.
* Returns: None.
*/

void AmFmRadio::ScanUp() {
    if (on) {
        previousFreq = GetCurrentFrequency();
        // Frequenct UP for AM
        if (strcmp(band, "AM") == EQUAL) {
            if (previousFreq.AMFreq != 0) {
                previousFreq.AMFreq += 10; // each +10 for AM
                currentFreq.AMFreq = previousFreq.AMFreq;
                current_station = currentFreq.AMFreq;
                if (previousFreq.AMFreq > 1700) {
                    previousFreq.AMFreq = 530;
                    currentFreq.AMFreq = previousFreq.AMFreq;
                    current_station = currentFreq.AMFreq;
                }
            }

        }
        else {
            // Frequenct up for FM
            previousFreq.FMFreq += (float)0.2; // each +0.2 for FM
            currentFreq.FMFreq = previousFreq.FMFreq;
            current_station = currentFreq.FMFreq;
            if (previousFreq.FMFreq > 107.9) {
                previousFreq.FMFreq = (float)87.9;
                currentFreq.FMFreq = previousFreq.FMFreq;
                current_station = currentFreq.FMFreq;
            }
        }
    }
    else {
        // delete for requirements
//        cout << "AmFm Radio is off." << endl;
    }
}


/*
* Function: ScanDown()
* Description: Changes the frequency down in increments of 0.2 for FM or 10 for AM.
* Parameters: None.
* Returns: None.
*/

void AmFmRadio::ScanDown() {
    if (on) {
        previousFreq = GetCurrentFrequency();
        // Frequenct down for AM
        if (strcmp(band, "AM") == EQUAL) {
            if (previousFreq.AMFreq != 0) {
                previousFreq.AMFreq -= 10; // each -10 for AM
                currentFreq.AMFreq = previousFreq.AMFreq;
                current_station = currentFreq.AMFreq;
                if (previousFreq.AMFreq < 530) {
                    previousFreq.AMFreq = 1700;
                    currentFreq.AMFreq = previousFreq.AMFreq;
                    current_station = currentFreq.AMFreq;
                }
            }
        }
        else {
        // Frequenct down for FM
        previousFreq.FMFreq -= (float)0.2; // each -0.2 for FM
        currentFreq.FMFreq = previousFreq.FMFreq;
        current_station = currentFreq.FMFreq;
        if (previousFreq.FMFreq < 87.9) {
            previousFreq.FMFreq = (float)107.9;
            currentFreq.FMFreq = previousFreq.FMFreq;
            current_station = currentFreq.FMFreq;
            }
        }
    }
    else {
        // delete for requirements
//       cout << "AmFm Radio is off." << endl;
    }
}


/*
* Function: GetCurrentVolume()
* Description: Gets the current volume of the car radio.
* Parameters: None
* Returns: return current volume as int.
*/

int AmFmRadio::GetCurrentVolume() const {
    return volume;
}


/*
* Function: GetCurrentFrequency()
* Description: Gets the current frequency of the car radio.
* Parameters: None
* Returns: return current requency as struct Freqs.
*/

Freqs AmFmRadio::GetCurrentFrequency() const {
    return currentFreq;
}


/*
* Function: GetDisplayOutput()
* Description: Checks if the car radio is currently displaying output.
* Parameters: None
* Returns: return displayOutput as bool.
*/

bool AmFmRadio::GetDisplayOutput() const {
    return displayOutput;
}


/*
* Function: SetDisplayOutput(bool display)
* Description: Sets the display output state of the car radio.
* Parameters: bool display : The display is that showing all information or not.
* Returns: None
*/

void AmFmRadio::SetDisplayOutput(bool display) {
    displayOutput = display;
}


/*
* Function: GetPowerOn()
* Description: Get the radio on or off
* Parameters: None
* Returns: return current radio power status
*/

bool AmFmRadio::GetPowerOn() {
    return on;
}


/* feedback fix (3 functions modified by feedback) */
/*
* Function: GetBand()
* Description: Gets the current band of the car radio.
* Parameters: None
* Returns: return current band
*/

const char* AmFmRadio::GetBand() {
    return band; 
}


/*
* Function: GetPresets(int i)
* Description: Get the radio`s preset frequency.
* Parameters: int i : The number is that user sets index.
* Returns: return the index as struct Freqs
*/

Freqs AmFmRadio::GetPresets(int i) {
    return presets[i];
}



/*
* Function: SetCurrentStation()
* Description: set the radio frequency.
* Parameters: None
* Returns: return current station value as double
*/

double AmFmRadio::SetCurrentStation(double setValue) {
    if (on) {
        if (strcmp(band, "AM") == 0) {
            currentFreq.AMFreq = (int)setValue;
            current_station = (double)currentFreq.AMFreq;
        }
        else {
            currentFreq.FMFreq = (float)setValue;
            current_station = (double)currentFreq.FMFreq;
        }
    }
    return current_station;
}

double AmFmRadio::GetCurrentStation() {
    return current_station; 
}


void AmFmRadio::ToggleFrequency() {
    if (strcmp(band, "AM") == 0) {
        strcpy(band, "FM");
        current_station = currentFreq.FMFreq;
    }
    else {
        strcpy(band, "AM");
        current_station = currentFreq.AMFreq;
    }
}

void AmFmRadio::SetInitialFreqWorld() {
    for (int i = 0; i < 5; ++i) {
        presets[i].AMFreq = (int)531;
    }
}