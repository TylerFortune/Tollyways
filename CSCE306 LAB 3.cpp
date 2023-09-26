// CSCE306 LAB 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
// --------------Functions----------------

// gets total mins from hour value
double getMin(double hour) {
	return hour * 60;
}
// converts speed to mph and takes in total time spent on the trip
double mph(double total) {
	return total / 60.00;
}
// takes in the paramiter time (being total time for the trip)
// returns the traveltime
double travelTime(double totalTime) {
	return 14.5 / totalTime;
}

// ------------MAIN FUNCTION---------------
int main()
{
	ifstream inFile;
	ofstream outFile;
	string inFileName = "readings.txt";
	string outFileName = "results.txt";
	string line;
	vector<string> lines;
	int amtLines = 0;

	// Variables used for calculations
	double DHours, OHours, DMin, OMin; //variable to store time crossing tollways
	double totalOMins, totalDMins, overallMins; //stores the total time in minutes
	double travelMins; // Time it took to travel between the tollway
	double speed; // Stores the speed of the car
	string licenseplate;

	outFile.open(outFileName); // Open out file
	if (!outFile.is_open()) {
		cout << "Error - cannot open " << outFileName << endl;  // Program Error
		return 1;
	}


	inFile.open(inFileName);  // Open read file
	if (inFile.is_open()) {
		int i = 0;
		// Stores the values in the in file and prints output
		while (getline(inFile, line)) {
			lines.push_back(line);
		}
	}
	else {
		cout << "Error - cannot open " << inFileName << endl;  // Program Error
		return 1;
	}
	// Print file inputs
	cout << "These are the following contents in the file: \n ";
	for (int i = 0; i < lines.size(); i++) {
		cout << lines[i] << "\n";
	}

	// Convert file content into variables for calculations
	for (int i = 0; i < lines.size(); i++) {
		// stores the first lines of input
		string tempString = lines[i];

		// Create an input stream
		istringstream iss(tempString);

		// Get the first value
		string token;
		getline(iss, token, ';');
		licenseplate = token; // Save the first entry

		// Convert the rest of the values
		getline(iss, token, ';');
		DHours = atof(token.c_str());

		getline(iss, token, ';');
		DMin = atof(token.c_str());

		getline(iss, token, ';');
		OHours = atof(token.c_str());

		getline(iss, token, ';');
		OMin = atof(token.c_str());

		// Convers hours to minutes and gets time in minutes before midnight
		totalOMins = getMin(OHours) + OMin;
		totalDMins = getMin(DHours) + DMin;
		if (totalOMins == 0.0 || totalDMins == 0.0) {
			return 1;
		}
		// Write to output File
		else
		{
			// Total time it took to pass through the tollways
			overallMins = totalOMins - totalDMins;

			// Gets the time in minutes that it took to travel
			speed = mph(overallMins);

			// Calculates to mph
			travelMins = travelTime(speed);

			// Displays tickets based on input.
			if (travelMins < 60) {
				string  tempString = licenseplate + " " + to_string(travelMins) + " Not Speeding \n";
				outFile << tempString;
			}
			else if (60 < travelMins && travelMins <= 70)
			{
				outFile << licenseplate << " " << travelMins << " Speeding. $125 Ticket. \n";
			}
			else if (70 < travelMins && travelMins <= 85)
			{
				outFile << licenseplate << " " << travelMins << " Speeding. $275 Ticket. \n";
			}
			else {
				outFile << licenseplate << " " << travelMins << " Speeding. $500 Ticket. \n";
			}

		}

	}
	outFile.close();
	inFile.close();
}
