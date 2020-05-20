#include<iostream>
#include<string>
#include "MidiFile.h"

using namespace std;

int main() 
{

	string fileName;
	cout << "Please enter the MIDI path: ";
	cin >> fileName;
	cout << "Loading MIDI, this may take some time if the note count is high." << endl;

	smf::MidiFile midiInfo;
	midiInfo.read(fileName);

	unsigned long noteCount = midiInfo.linkNotePairs();

	//This integer will be set to the amount of notes with a velocity of 31 or lower
	unsigned long lowVeloCount = 0;

	//Finds the amount of notes with velocities 31 or lower
	for (int track = 0; track < midiInfo.getTrackCount(); track++) {
		for (int event = 0; event < midiInfo[track].size(); event++) {
			if (midiInfo[track][event].isNoteOn()) {
				if (midiInfo[track][event].getVelocity() <= 31) {
					lowVeloCount++;
				}
			}
		}
	}

	//Calculates the percentage of spammy notes
	double midiSize = noteCount;
	double spamCount = lowVeloCount;
	double spamPercentage = spamCount / midiSize;
	spamPercentage = spamPercentage * 100;

	cout << "\n" << midiInfo.getFilename() << " contains " << noteCount << " notes" << endl;
	cout << "\n" << "The amount of quiet velocities in this MIDI is " << lowVeloCount << endl;
	cout << "\n" << "This MIDI is " << spamPercentage << "% spam!" << "\n" << endl;

	system("pause");
	//Destructor
	cout << "Closing program, this may take some time if you loaded a large MIDI file.";
	smf::MidiEventList midiEventList;
	midiEventList.clear();
	return 0;

}