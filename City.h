#ifndef CITY_H
#define CITY_H

#include <string>
#include <list>
#include <iostream>
#include "Road.h"

class City
{
private:
    std::string name;
    std::list<Road> roads;

public:
    City(const std::string& name);

    std::string getName() const;
    const std::list<Road>& getRoads() const;

    bool hasRoadTo(const std::string& destination) const;
    void addRoad(const std::string& destination, double distance);
    bool removeRoad(const std::string& destination);

    friend std::ostream& operator<<(std::ostream& out, const City& city);
};

#endif
