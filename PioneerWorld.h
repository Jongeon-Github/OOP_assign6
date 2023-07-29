/*
* Filename: PioneerWorld.h
* Project: OOP-assign6
* Student ID: 8790144
* By: Jongeon Lee
* Date: Jul 29, 2023
* Description: Implementation of PioneerWorld radio, extending "PioneerAM" to represent a Pioneer car radio
*              with worldwide AM frequency support and scanning functionalities.
*/

#ifndef PIONEERWORLD_H
#define PIONEERWORLD_H

#include "PioneerAM.h"
#include <iostream>
#include <conio.h>

class PioneerWorld : public PioneerAM {
public:
    PioneerWorld() : PioneerAM() {
        displayDestructor = true;
        SetInitialFreqWorld();
        PowerToggle();
        SetCurrentStation(531);
        PowerToggle();
    }

    virtual ~PioneerWorld() {
        if (displayDestructor) {
            cout << "Destroying Pioneer XS440-WRLD Radio" << endl;
        }
        displayDestructor = false;
    }

    // Radio frequency scan up
    virtual void ScanUp() override {
        double currentFrequency = GetCurrentStation();
        if (strcmp(GetBand(), "AM") == 0) {
            if (currentFrequency < 1602.0) {
                currentFrequency += 9.0;
            }
            else {
                currentFrequency = 531.0;
            }
        }
        SetCurrentStation(currentFrequency);
    }

    // Radio frequency scan down
    virtual void ScanDown() override {
        double currentFrequency = GetCurrentStation();
        if (strcmp(GetBand(), "AM") == 0) {
            if (currentFrequency > 531.0) {
                currentFrequency -= 9.0;
            }
            else {
                currentFrequency = 1602.0;
            }
        }
        SetCurrentStation(currentFrequency);
    }

    virtual void ToggleFrequency() override {}

    // Radio current configuration display
    virtual void ShowCurrentSettings() override {
        // Display the status and information of the car radio
        if (AmFmRadio::GetPowerOn()) {
            double current_station = round(AmFmRadio::GetCurrentStation() * 100) / 100;
            cout << "Pioneer XS440-WRLD Radio" << endl;
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
                    cout << i + matchArrayNum << ":" << setw(8) << setfill(' ') << AmFmRadio::GetPresets(i).AMFreq << endl << endl;
                }
            }
        }
        else {
            cout << "Pioneer XS440-WRLD Radio" << endl;
            cout << (AmFmRadio::GetPowerOn() ? "Radio is On" : "Radio is Off") << endl << endl;
        }
    }
};

#endif
