/*
* Filename: ultimateRadio.cpp
* Project: OOP-assign6
* Student ID: 8790144
* By: Jongeon Lee
* Date: Jul 29, 2023
* Description: This assignment enhances the C code by implementing inheritance, dynamic memory allocation,
*              exception handling, and virtual functions.
*/


#include <stdio.h>
#include <iostream>
#include <cstring>
#include "AmFmRadio.h"
#include "PioneerCarRadio.h"
#include "PioneerAM.h"
#include "PioneerWorld.h"

using namespace std;

// Function prototype
PioneerCarRadio* createRadio(const string& radioType);

int main(int argc, char* argv[]) {
    PioneerCarRadio* pRadio = nullptr;

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <radio_type>" << endl;
        cout << "Available radio types: car, am, world" << endl;
        return -1;
    }

    string radioType = argv[1];

    try {
        pRadio = createRadio(radioType);
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return -1;
    }

    pRadio->Run();
    delete pRadio;

    return 0;
}


/*
* Function: createRadio(const string& radioType)
* Description: Make a memory allocation for new type of radio
* Parameters: const string& radioType: User seleceted radio type
* Returns: return new type of Pioneer radio pointer
*/

PioneerCarRadio* createRadio(const string& radioType) {
    if (radioType == "car")
        return new PioneerCarRadio();
    else if (radioType == "am")
        return new PioneerAM();
    else if (radioType == "world")
        return new PioneerWorld();
    else
        throw runtime_error("Invalid radio type");
}