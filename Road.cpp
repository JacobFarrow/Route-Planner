#include "Road.h"

Road::Road(const std::string& destination, double distance)
    : destination(destination), distance(distance)
{
}

std::string Road::getDestination() const
{
    return destination;
}

double Road::getDistance() const
{
    return distance;
}
