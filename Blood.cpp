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

#include "Blood.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>
using namespace std;

Blood::Blood() {
    // if random number is 0, type is A
    if (rand()%3 == 0) {
    isA = true;
    // if random number is 0, type is B
    if (rand()%2 == 0) {
        isB = true; // blood type can be AB
    } else {
        isB = false; // blood type must be A
    }
    isO = false; // blood cannot be type O if it is A or B or AB
    } else if (rand()%3 == 1) { // if random number is 1
        isB = true; // blood type is B
        if (rand()%2 == 0) {
            isA = true; // blood type can be AB
        } else {
            isA = false; // blood type must be B
        }
        isO = false; // blood cannot be type O if it is A or B or AB
    } else {
        // blood type must be O
        isO = true;
        isA = false;
        isB = false;
    }
    if (rand()%2 == 0) {
        // blood type is positive
        hasRH = true;
    } else {
        hasRH = false;
    }
}

string Blood::printBloodType() const {
    string bloodType = "";
    if (isA) {
        bloodType += "A";
    }
    if (isB) {
        bloodType += "B";
    }
    if (isO) {
        bloodType += "O";
    }
    if (hasRH) {
        bloodType += "+";
    } else {
        bloodType += "-";
    }
    return bloodType;
}

bool Blood::getA() const {
    return isA;
}

bool Blood::getB() const {
    return isB;
}

bool Blood::getO() const {
    return isO;
}

bool Blood::getRH() const {
    return hasRH;
}

void Blood::performBloodTyping() const {
    cout << "Key:" << endl << "Anti-A agglutinates: blood is type A" << endl << "Anti-B agglutinates: blood is type B" << endl << "Anti-A and anti-B agglutinate: blood is type AB" << endl << "Neither agglutinate: blood is type O" << endl << endl << "Anti-RH agglutinates: blood is positive" << endl << "Anti-RH does not agglutinate: blood is negative" << endl;
    cout << endl << "-------------------------------------------------------------------------------------" << endl;
    cout << setw(50) << right << "Mixing anti-A serum..." << endl << endl;
    usleep(500000);
    if (isA) {
        cout << setw(50) << right << "[ Agglutination occurs! ]" << endl;
    } else {
        cout << setw(55) << right << "[ Agglutination does not occur. ]" << endl;
    }
    cout << endl << "-------------------------------------------------------------------------------------" << endl;
    cout << setw(50) << right << "Mixing anti-B serum..." << endl << endl;
    usleep(500000);
    if (isB) {
        cout << setw(50) << right << "[ Agglutination occurs! ]" << endl;
    } else {
        cout << setw(55) << right << "[ Agglutination does not occur. ]" << endl;
    }
    cout << endl << "-------------------------------------------------------------------------------------" << endl;
    cout << setw(50) << right << "Mixing anti-RH serum..." << endl << endl;
    usleep(500000);
    if (hasRH) {
        cout << setw(50) << right << "[ Agglutination occurs! ]" << endl;
    } else {
        cout << setw(55) << right << "[ Agglutination does not occur. ]" << endl;
    }
    cout << endl << "-------------------------------------------------------------------------------------" << endl;
}

bool Blood::compareBloodType(Blood otherBlood) const {
    bool otherIsA = otherBlood.getA();
    bool otherIsB = otherBlood.getB();
    bool otherIsO = otherBlood.getO();
    bool otherHasRH = otherBlood.getRH();
    // if patient blood is A+: A+, A-, O+, O-
    // if patient blood is A-: A-, O-
    if (isA && (otherIsA || otherIsO) && !otherIsB) {
        if ((!hasRH && !otherHasRH)) {
            return true;
        } else if (hasRH) {
            return true;
        }
    }
    // if patient blood is B+: B+, B-, O+, O-
    // if patient blood is B-: B-, O-
    if (isB && (otherIsB || otherIsO) && !otherIsA) {
        if ((!hasRH && !otherHasRH)) {
            return true;
        } else if (hasRH) {
            return true;
        }
    }
    // if patient has AB+: can receive all types (AB+ is universal recipient)
    // if patient blood is AB-: compatible with AB-, A-, B-, O-
    if (isA && isB && ((otherIsA && otherIsB) || otherIsO)) {
        if ((!hasRH && !otherHasRH)) {
            return true;
        } else if (hasRH) {
            return true;
        }
    }
    // if other blood is 0-: compatible with all types (O- is universal donor)
    // if patient blood is O-: compatible with O-
    if (isO && otherIsO) {
        if ((!hasRH && !otherHasRH)) {
            return true;
        } else if (hasRH) {
            return true;
        }
    }

    return false;
}