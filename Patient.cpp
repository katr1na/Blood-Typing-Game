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
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Patient::Patient() {
    mNumBloodBagsRequired = rand()%4+1;
    mBloodType = Blood();
    mHealth = 25 - mNumBloodBagsRequired*5;
}

Blood Patient::getBloodType() const {
    return mBloodType;
}

int Patient::getNumBags() const {
    return mNumBloodBagsRequired;
}

int Patient::getHealth() const {
    return mHealth;
}

void Patient::giveBloodBag(Blood bloodBag) {
    // check if patient can receive this blood type
    bool getsTreated = mBloodType.compareBloodType(bloodBag);
    updateHealthStatus(getsTreated);
    if (getsTreated) {
        // decrement blood bags required if treated
        mNumBloodBagsRequired--;
    } else {
        // increase blood bags required otherwise
        mNumBloodBagsRequired++;
    }
}

void Patient::examinePatient() const {
    cout << setw(50) << "Current Health: " << mHealth << "/25" << endl << setw(50) << "Number of Blood Bags Left: " << mNumBloodBagsRequired << endl << setw(50) << "Blood Type: " << mBloodType.printBloodType() << endl;
}

void Patient::updateHealthStatus(bool getsTreated) {
    if (getsTreated) {
        // increment health bar if treated
        mHealth += 5;
    } else {
        // decrement health bar otherwise
        mHealth -= 5;
    }
}