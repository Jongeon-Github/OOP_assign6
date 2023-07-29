/*
* Filename: PioneerAM.h
* Project: OOP-assign6
* Student ID: 8790144
* By: Jongeon Lee
* Date: Jul 29, 2023
* Description: Implementation of PioneerCarRadio, representing a Pioneer car radio
*              working exclusively with the AM frequency band.
*/

#ifndef PIONEERAM_H
#define PIONEERAM_H

#include "PioneerCarRadio.h"
#include <string>
#include <iomanip>


class PioneerAM : public PioneerCarRadio {
public:
    PioneerAM() : PioneerCarRadio() {
        displayDestructor = true;
    }

    virtual ~PioneerAM() {
        if (displayDestructor) {
            cout << "Destroying Pioneer XS440-AM Radio" << endl;
        }
        displayDestructor = false;
    }

    // Radio frequency scan up
    virtual void ScanUp() override {
        double currentFrequency = GetCurrentStation();
        if (strcmp(GetBand(), "AM") == 0) {
            if (currentFrequency < 1700.0) {
                currentFrequency += 10.0;
            }
            else {
                currentFrequency = 530.0;
            }
        }
        SetCurrentStation(currentFrequency);
    }

    // Radio frequency scan down
    virtual void ScanDown() override {
        double currentFrequency = GetCurrentStation();
        if (strcmp(GetBand(), "AM") == 0) {
            if (currentFrequency > 530.0) {
                currentFrequency -= 10.0;
            }
            else {
                currentFrequency = 1700.0;
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
            cout << "Pioneer XS440-AM Radio" << endl;
            cout << (AmFmRadio::GetPowerOn() ? "Radio is On" : "Radio is Off") << endl;
            cout << "Volume: " << AmFmRadio::GetCurrentVolume() << endl;
            cout << "Current Station: " << current_station << " " << AmFmRadio::GetBand() << endl;
            cout << "AM Buttons:" << endl;
            int numElements = 5;
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
            cout << "Pioneer XS440-AM Radio" << endl;
            cout << (AmFmRadio::GetPowerOn() ? "Radio is On" : "Radio is Off") << endl << endl;
        }
    }
};

#endif
