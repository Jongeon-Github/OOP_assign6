/*
* Filename: AmFmRadio.h
* Project: OOP-assign2 (and assign4, 6)
* Student ID: 8790144
* By: Jongeon Lee
* Date: Jul 29, 2023
* Description: This is a class representing a radio with AM/FM capabilities.
*/

#ifndef AMFMRADIO_H
#define AMFMRADIO_H

struct Freqs
{
	int AMFreq;
	float FMFreq;
};

class AmFmRadio {
private:
	Freqs	presets[5];
	Freqs	previousFreq;
	Freqs	currentFreq;
	double	current_station;
	char	initDisplay[20];
	char	userScanDisplay;
	char	band[3];
	char	userInputBuf[20];
	int		previousVolume;
	int		userVolume;
	int		volume;
	bool	on;
	bool	displayOutput;

public:

	// Initialize the values.
	AmFmRadio(bool On = false);
	AmFmRadio(bool On, Freqs initPresets[5]);
	~AmFmRadio();

	// Toggles the power state of the car radio.
	void PowerToggle();

	// Prompts the user to set the volume of the car radio.
	void SetVolume();
	void SetVolume(int vol);
	
	// Toggles the frequency band between AM and FM.
	void ToggleBand();

	// Sets the specified button (radio preset) with the current station.
	int SetPresetButton(int buttonNum);

	// Sets the current station to the radio preset specified by the button number.
	int SelectPresetButton(int buttonNum);

	// Displays the current settings of the car radio.
	void ShowCurrentSettings();

	// Changes the frequency up in increments of 0.2 for FM or 10 for AM.
	void ScanUp();

	// Changes the frequency down in increments of 0.2 for FM or 10 for AM.
	void ScanDown();

	//  Gets the current volume of the car radio.
	int GetCurrentVolume();

	// Gets the current frequency of the car radio.
	Freqs GetCurrentFrequency();

	// Checks if the car radio is currently displaying output.
	bool GetDisplayOutput();

	// Sets the display output state of the car radio.
	void SetDisplayOutput(bool display);


	/* feedback fix */
	const char* GetBand(); // Gets the current band of the car radio.
	Freqs GetPresets(int i); // Gets the present index of the car radio.
	double SetCurrentStation(); // Sets the current station of the car radio.
	bool GetPowerOn(); // Gets the radio power on or off.

};
#endif