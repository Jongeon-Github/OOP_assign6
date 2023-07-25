/*
* Filename: PioneerCarRadio.cpp
* Project: OOP-assign4 (and assign6)
* Student ID: 8790144
* By: Jongeon Lee
* Date: Jul 29, 2023
* Description: Implementation of the PioneerCarRadio class which represents a car radio system.
*/

#include "PioneerCarRadio.h"
#include "AmFmRadio.h"
#include <iostream>
#include <conio.h>
#include <iomanip>

#pragma warning(disable:4996)

using namespace std;


/*
* Function: PioneerCarRadio()
* Description: Initializes the radio.
* Parameters: None
*/

PioneerCarRadio::PioneerCarRadio() {
    // Start with the radio off
    AmFmRadio::PowerToggle();
}


/*
* Function: ~PioneerCarRadio()
* Description: Destructor for the PioneerCarRadio class.
* Parameters: None
*/

PioneerCarRadio::~PioneerCarRadio() {
    cout << "PioneerCarRadio is being destroyed." << std::endl;
}


/*
* Function: Run()
* Description: Runs the car radio system
* Parameters: None
* Returns: None
*/

void PioneerCarRadio::Run() {
    char key = {0};
    bool operation = true;
    while (operation) {
        key = getch();
        UserKey(key);
        if (key == 'x') {
            operation = false;
        }
    }
}


/*
* Function: UserKey(char key)
* Description: Handles the user's key input and performs actions based on the input.
* Parameters: char key: A character representing the user's input key.
* Returns: None
*/

void PioneerCarRadio::UserKey(char key) {
    int currentVolume = 0;
    int volumeUp = 1;
    int volumeDown = -1;
    
    switch (key) {
    case 'o':
        AmFmRadio::PowerToggle();
        break;
    case '+':
        currentVolume = AmFmRadio::GetCurrentVolume() + volumeUp;
        AmFmRadio::SetVolume(currentVolume);
        break;
    case '_':
        currentVolume = AmFmRadio::GetCurrentVolume() + volumeDown;
        AmFmRadio::SetVolume(currentVolume);
        break;
    case '=':
        AmFmRadio::ScanUp();
        break;
    case '-':
        AmFmRadio::ScanDown();
        break;
    case 'b':
        AmFmRadio::ToggleBand();
        break;
    case '1':
        AmFmRadio::SelectPresetButton(0);
        break;
    case '2':
        AmFmRadio::SelectPresetButton(1);
        break;
    case '3':
        AmFmRadio::SelectPresetButton(2);
        break;
    case '4':
        AmFmRadio::SelectPresetButton(3);
        break;
    case '5':
        AmFmRadio::SelectPresetButton(4);
        break;
    case '!':
        AmFmRadio::SetPresetButton(0);
        break;
    case '@':
        AmFmRadio::SetPresetButton(1);
        break;
    case '#':
        AmFmRadio::SetPresetButton(2);
        break;
    case '$':
        AmFmRadio::SetPresetButton(3);
        break;
    case '%':
        AmFmRadio::SetPresetButton(4);
        break;
    case 'x':
        return;
    default:
        return;
    }
    ShowCurrentSettings();
}


/*
* Function: DisplayPioneerRadio()
* Description: Displays the status and information of the Pioneer car radio.
* Parameters: None
* Returns: None
*/

//void PioneerCarRadio::DisplayPioneerRadio() {
void PioneerCarRadio::ShowCurrentSettings() {
        // Display the status and information of the car radio
    if (AmFmRadio::GetPowerOn() == true) {
        double current_station = round(AmFmRadio::SetCurrentStation() * 100) / 100;
        cout << "Pioneer XS440" << endl;
        cout << (AmFmRadio::GetPowerOn() ? "Radio is On" : "Radio is Off") << endl;
        cout << "Volume: " << AmFmRadio::GetCurrentVolume() << endl;
        cout << "Current Station: " << current_station << " " << AmFmRadio::GetBand() << endl;
        cout << "AM Buttons:" << endl;
        int numElements = 5; // number of presets array
        int matchArrayNum = 1;
        for (int i = 0; i < numElements; i++) {
            if (i < numElements - matchArrayNum) {
                cout << i + matchArrayNum << ":" << setw(8) << setfill(' ') << AmFmRadio::GetPresets(i).AMFreq << ",  ";
            }
            else {
                cout << i + matchArrayNum << ":" << setw(8) << setfill(' ') << AmFmRadio::GetPresets(i).AMFreq << endl;
            }
        }
        cout << "FM Buttons:" << endl;
        for (int i = 0; i < numElements; i++) {
            if (i < numElements - matchArrayNum) {
                cout << i + matchArrayNum << ":" << setw(8) << setfill(' ') << AmFmRadio::GetPresets(i).FMFreq << ",  ";
            }
            else {
                cout << i + matchArrayNum << ":" << setw(8) << setfill(' ') << AmFmRadio::GetPresets(i).FMFreq << endl << endl;
            }
        }
    }
    else {
        cout << "Pioneer XS440" << endl;
        cout << (AmFmRadio::GetPowerOn() ? "Radio is On" : "Radio is Off") << endl << endl;
    }
}
