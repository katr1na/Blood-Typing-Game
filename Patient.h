#ifndef PATIENT_H
#define PATIENT_H
#include "Blood.h"

class Patient {
    public:
    /**
     * @brief create a new Patient with randomized health, bloodtype, and number of blood bags needed to be healed
     * 
     */
    Patient();

    /**
     * @brief return Blood of Patient
     * 
     * @return Blood 
     */
    Blood getBloodType() const;

    /**
     * @brief return number of blood bags needed to heal Patient
     * 
     * @return int 
     */
    int getNumBags() const;

    /**
     * @brief return current health of Patient
     * 
     * @return int 
     */
    int getHealth() const;

    /**
     * @brief determines if Patient can receive given bloodBag and updates health accordingly
     * 
     * @param bloodBag 
     */
    void giveBloodBag(Blood bloodBag);

    /**
     * @brief print out the health, blood type, and number of remaining blood bags for Patient
     * 
     */
    void examinePatient() const;

    /**
     * @brief increase or decrease health appropriately 
     * 
     * @param getsTreated 
     */
    void updateHealthStatus(bool getsTreated);

    private:
    Blood mBloodType; // Patient blood type
    int mHealth; // Patient health 
    int mNumBloodBagsRequired; // number of blood bags needed to heal Patient
};

#endif