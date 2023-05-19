#ifndef BLOOD_H
#define BLOOD_H

#include <string>

class Blood {
    public:
    /**
     * @brief create a new Blood by randomizing it's type
     * 
     */
    Blood();

    /**
     * @brief return blood type as a string
     * 
     * @return std::string 
     */
    std::string printBloodType() const;

    /**
     * @brief return true if Patient has blood A type
     * 
     * @return true 
     * @return false 
     */
    bool getA() const;

    /**
     * @brief return true if Patient has blood B type
     * 
     * @return true 
     * @return false 
     */
    bool getB() const;

    /**
     * @brief return true if Patient has blood O type 
     * 
     * 
     * @return true 
     * @return false 
     */
    bool getO() const;

    /**
     * @brief return true if Patient has RH factor
     * 
     * @return true 
     * @return false 
     */
    bool getRH() const;

    /**
     * @brief performs blood typing on Patient blood and prints which type agglutinates
     * 
     */
    void performBloodTyping() const;

    /**
     * @brief returns true if implicit Blood parameter is compatible with given Blood otherBlood
     * 
     * @param otherBlood 
     * @return true 
     * @return false 
     */
    bool compareBloodType(Blood otherBlood) const;

    private:
    bool isA;
    bool isB;
    bool isO;
    bool hasRH;
};

#endif