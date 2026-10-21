#include "City.h"
#include <iomanip>

City::City(const std::string& name)
    : name(name)
{
}

std::string City::getName() const
{
    return name;
}

const std::list<Road>& City::getRoads() const
{
    return roads;
}

bool City::hasRoadTo(const std::string& destination) const
{
    for (std::list<Road>::const_iterator it = roads.begin(); it != roads.end(); ++it)
    {
        if (it->getDestination() == destination)
        {
            return true;
        }
    }
    return false;
}

void City::addRoad(const std::string& destination, double distance)
{
    roads.push_back(Road(destination, distance));
}

bool City::removeRoad(const std::string& destination)
{
    for (std::list<Road>::iterator it = roads.begin(); it != roads.end(); ++it)
    {
        if (it->getDestination() == destination)
        {
            roads.erase(it);
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const City& city)
{
    out << city.name << ":";

    if (city.roads.empty())
    {
        out << " (no roads)";
        return out;
    }

    for (std::list<Road>::const_iterator it = city.roads.begin(); it != city.roads.end(); ++it)
    {
        out << std::endl << "    -> " << it->getDestination()
            << " (" << std::fixed << std::setprecision(1) << it->getDistance() << " miles)";
    }

    return out;
}
