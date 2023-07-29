/*
* Filename: PioneerCarRadio.h
* Project: OOP-assign4 (and assign6)
* Student ID: 8790144
* By: Jongeon Lee
* Date: Jul 29, 2023
* Description: Header file for the PioneerCarRadio class.
*/

#ifndef PIONEERCARRADIO_H
#define PIONEERCARRADIO_H

#include "AmFmRadio.h"

using namespace std;

class PioneerCarRadio : public AmFmRadio
{
private:

public:
    // Constructor and Destructor
    PioneerCarRadio();
    virtual ~PioneerCarRadio();

    // Gets key from user`s input
    void UserKey(char key);

    // Runs the car radio program
    void Run();

    // Display all information of car radio
    virtual void ShowCurrentSettings();

    virtual void ToggleFrequency();
    virtual void ScanUp();
    virtual void ScanDown();
    
};
#endif  