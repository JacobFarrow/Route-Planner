#ifndef ROAD_H
#define ROAD_H

#include <string>

class Road
{
private:
    std::string destination;
    double distance;

public:
    Road(const std::string& destination, double distance);

    std::string getDestination() const;
    double getDistance() const;
};

#endif
