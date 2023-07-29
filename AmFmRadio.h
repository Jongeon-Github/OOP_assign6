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

using namespace std;

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
	char*   copyBand;

public:

	// Initialize the values.
	AmFmRadio(bool On = false);
	AmFmRadio(bool On, Freqs initPresets[5]);
	virtual ~AmFmRadio() = default;
	bool displayDestructor;
	
	// Prompts the user to set the volume of the car radio.
	void SetVolume();
	void SetVolume(int vol);
	
	void PowerToggle(); // Toggles the power state of the car radio.
	
	void ToggleBand(); // Toggles the frequency band between AM and FM.
	
	int SetPresetButton(int buttonNum);	// Sets the specified button (radio preset) with the current station.
	
	int SelectPresetButton(int buttonNum);	// Sets the current station to the radio preset specified by the button number.
	
	virtual void ShowCurrentSettings();	// Displays the current settings of the car radio.
	
	virtual void ScanUp();	// Changes the frequency up in increments of 0.2 for FM or 10 for AM.
	
	virtual void ScanDown();	// Changes the frequency down in increments of 0.2 for FM or 10 for AM.
	
	int GetCurrentVolume() const;	//  Gets the current volume of the car radio.
	
	Freqs GetCurrentFrequency() const;	// Gets the current frequency of the car radio.
	
	bool GetDisplayOutput() const;	// Checks if the car radio is currently displaying output.
	
	void SetDisplayOutput(bool display);	// Sets the display output state of the car radio.
	
	const char* GetBand(); // Modify to a const member function to get the current band of the car radio.
	
	Freqs GetPresets(int i); // Modify to a const member function to get the present index of the car radio.
	
	double SetCurrentStation(double setValue); // Add function to set the current station of the car radio.
	
	double GetCurrentStation(); // Add function to get the current station freq of the car radio.
	
	bool GetPowerOn(); // Gets the radio power on or off
	
	virtual void ToggleFrequency(); // Toggle the radio frequency

	void SetInitialFreqWorld();

};
#endif