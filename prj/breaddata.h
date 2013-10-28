#ifndef BREADDATA_H
#define BREADDATA_H

#include <vector>
#include <string>

class breadData
{
public:
    breadData();
    //read in data file that provides all information
    bool readData(const char*);

    //access functions
    unsigned int getWhite(){return whiteSticks;}
    unsigned int getWheat(){return wheatSticks;}

    //set functions
    void setWhite(unsigned int x){ whiteSticks = x;}
    void setWheat(unsigned int x){ wheatSticks = x;}


private:
    //daily sales of the week to be read in from data file
    std::vector<std::string> dailySales;
    //stick amount
    unsigned int whiteSticks;
    unsigned int wheatSticks;

};

#endif // BREADDATA_H
