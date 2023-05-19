/* CSCI 200: Final Project
 *
 * Author: Katrina Ngo
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * This is a blood typing game where the objective is to heal a patient that needs a blood transfusion, so the user has to give the patient
 * the correct blood type in order to heal them. The user will also have to determine what blood type the patient is beforehand, in which a guide
 * will be provided on how to perform that.
 */

#include "Patient.h"
#include "Blood.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


vector<Blood> generateBloodBags() {
    vector<Blood> bloodOptions;
    // generate 6 new blood bags and return as a vector
    for (int i = 0; i < 6; i++) {
        Blood blood = Blood();
        bloodOptions.push_back(blood);
    }
    return bloodOptions;
}

int main() {
    srand(time(0));
    string playerName;
    ifstream inFile;
    ofstream outFile("patient_log.txt");
    string input;
    cout << "Please enter your name: ";
    getline(cin, playerName);
    outFile << "Caretaker: " << playerName << endl;
    cout << endl;
    string moveOn;
    string keepPlaying;
    vector<Patient> patientLog;

    cout << endl << "-------------------------------------------------------------------------------------" << endl << "You are about to perform blood typing on a patient sample." << endl;
    
    // prompt user if they want to learn how blood typing works
    do {
        cout << "Would you like to learn how blood typing works? (Y or N): ";
        cin >> moveOn;
        cin.get();
        if (moveOn == 'Y' || moveOn == 'y' || moveOn == 'N' || moveOn == 'n') {
            break;
        } else {
            cout << endl << "PLEASE TYPE Y OR N" << endl;
        }
    }
    while (moveOn != 'Y' || moveOn != 'y' || moveOn != 'N' || moveOn != 'n');

    // print out all info on blood typing if user says yes
    if (moveOn == 'Y' || moveOn == 'y') {
        inFile.open("data/bloodTypingInfo.txt");
        cout << endl;
        while (getline(inFile, input)) {
            cout << input << endl;
            usleep(500000);
        }
        cout << endl;
        cout << "PRESS ENTER TO CONTINUE ";
        cin.get();
        inFile.close();
    }

    // print out all instructions for game
    inFile.open("data/instructions.txt");
    cout << endl << "-------------------------------------------------------------------------------------" << endl;
    while (getline(inFile, input)) {
        cout << input << endl;
        usleep(500000);
    }

    cout << endl << "PRESS ENTER TO START GAME ";
    cin.get();

    // while user wants to keep playing
    while (keepPlaying != 'N' && keepPlaying != 'n') {
        cout << endl << "-------------------------------------------------------------------------------------" << endl;
        string bloodInput;
        string choice;
        Patient currentPatient = Patient(); // create new patient
        patientLog.push_back(currentPatient); // add current patient to log of patients
        currentPatient.getBloodType().performBloodTyping(); // have user perform blood typing
        usleep(100000);

        string bloodTypeLower;
        // convert blood type to lowercase
        for (int i = 0; i < currentPatient.getBloodType().printBloodType().length(); i++) {
            bloodTypeLower += tolower(currentPatient.getBloodType().printBloodType().at(i));
        }

        // while user cannot determine patient's correct blood type, continue to prompt user for correct type
        do {
            cout << "Type in patient's blood type (i.e. AB+, O-): ";
            cin >> bloodInput;
            cin.get();
            cout << endl;
            // if blood type matches blood type of patient, print correct
            if (bloodInput == currentPatient.getBloodType().printBloodType() || bloodInput == bloodTypeLower) {
                cout << endl << "CORRECT!" << endl;
                break;
            } else {
                cout << "INCORRECT! TRY AGAIN" << endl << endl;
            }
        }
        while (bloodInput != currentPatient.getBloodType().printBloodType() || bloodInput == bloodTypeLower);

        cout << "PRESS ENTER TO CONTINUE ";
        cin.get();
        vector<Blood> bloodOptions;

        // while patient's health is above 0 and there are still blood bags required to heal patient, have user give blood to patient
        while (currentPatient.getNumBags() > 0 && currentPatient.getHealth() > 0) {
            bloodOptions = generateBloodBags();
            bool isValid;
            do {
                isValid = true;
                cout << endl << "-------------------------------------------------------------------------------------" << endl;
                currentPatient.examinePatient();
                cout << endl << setw(20);

                for (int i = 0; i < bloodOptions.size(); i++) {
                    cout << "(" << i+1 << ") " << bloodOptions.at(i).printBloodType() << " ";
                }

                cin.clear();
                cout << endl << endl << "Input Blood Bag (Type number)" << endl << "Generate Blood Bags (Type 'G')" << endl << "Input: ";
                cin >> choice;
                cout << endl;

                // check if the input is either a number of a character
                for(int i = 0; i < choice.length(); i++) {
                    if(!isdigit(choice[i]) && !isalpha(choice[i])) {
                        isValid = false;
                        break;
                    }
                }

                // check if user input is valid
                // if input is valid, is a character that is either 'g' or 'G' and has a length of 1, input is acceptable
                if (isValid && isalpha(choice[0]) && (choice == 'g' || choice == 'G') && (choice.length() == 1)) {
                    // while user inputs 'G' or 'g', continue generating blood bags
                    while (choice == 'G' || choice == 'g') {
                        cout << endl << "-------------------------------------------------------------------------------------" << endl;
                        currentPatient.examinePatient(); // display current health status of patient
                        cout << endl << setw(20);
                        bloodOptions = generateBloodBags(); // generate new blood bags

                        // print all the blood options user has
                        for (int i = 0; i < bloodOptions.size(); i++) {
                            cout << "(" << i+1 << ") " << bloodOptions.at(i).printBloodType() << " ";
                        }

                        cout << endl << endl << "Input Blood Bag (Type number)" << endl << "Generate Blood Bags (Type 'G')" << endl << "Input: ";
                        cin >> choice;
                        cin.clear();
                        cout << endl;
                    }
                // if input is valid and is an integer between 1 and 6 and has length of 1, input is acceptable as a blood option
                } else if (isValid && isdigit(choice[0]) && (stoi(choice) >= 1) && (stoi(choice) <= 6) && (choice.length() == 1)) {
                    break;
                } else {
                    cout << setw(62) << "----------------------------------------" << endl << setw(62) << "|  PLEASE INPUT A VALID NUMBER OR 'G'  |" << endl << setw(62) << "----------------------------------------" << endl;
                    usleep(600000);
                }
            }
            while (!((isValid && (choice.length() == 1) && (isdigit(choice[0]) && (stoi(choice) >= 1) && (stoi(choice) <= 6))) || (isalpha(choice[0]) && (choice == 'g' || choice == 'G'))));

            currentPatient.giveBloodBag(bloodOptions.at(stoi(choice)-1)); // determines if patient can receive blood type and updates health accordingly

            // if blood type given is compatible with patient blood type, let user know
            if (currentPatient.getBloodType().compareBloodType(bloodOptions.at(stoi(choice)-1))) {
                cout << setw(50) << "---------------" << endl << setw(50) << "|  GOOD JOB!  |" << endl << setw(50) << "---------------" << endl;
            } else {
                cout << setw(53) << "---------------------" << endl << setw(53) << "|  OUCH! TRY AGAIN  |" << endl << setw(53) << "---------------------" << endl;
            }
            usleep(500000);
        }
        // write out results to file for current patient
        outFile << "Patient #" << patientLog.size() << ":" << endl << "Patient Blood Type: " << patientLog.at(patientLog.size()-1).getBloodType().printBloodType() << endl;

        if (currentPatient.getHealth() > 0) {
            cout << "YOUR PATIENT IS HEALED!" << endl;
            outFile << "Patient was healed by caretaker." << endl << endl;
        } else {
            cout << "YOUR PATIENT IS DEAD!" << endl;
            outFile << "Patient was killed by caretaker." << endl << endl;
        }

        // prompt user if they want to continue playing
        do {
            cout << "Play again? (Y or N): ";
            cin >> keepPlaying;
            if (keepPlaying.length() == 1 && (keepPlaying == 'Y' || keepPlaying == 'y' || keepPlaying == 'N' || keepPlaying == 'n')) {
                break;
            } else {
                cout << endl << "PLEASE TYPE Y OR N" << endl;
            }
        }
        while (keepPlaying != 'Y' || keepPlaying != 'y' || keepPlaying != 'N' || keepPlaying != 'n' || keepPlaying.length() != 1);
    }
    cout << "Thank you for playing! Check the patient_log.txt for your results." << endl;
    return 0;
}