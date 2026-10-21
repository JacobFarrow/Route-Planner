#ifndef ROADMAP_H
#define ROADMAP_H

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include "City.h"
#include "Route.h"

class RoadMap
{
private:
    std::map<std::string, std::shared_ptr<City>> cities;

public:
    bool hasCity(const std::string& name) const;
    bool addCity(const std::string& name);
    bool addRoad(const std::string& from, const std::string& to, double distance);
    bool removeRoad(const std::string& from, const std::string& to);

    Route findShortestRoute(const std::string& start, const std::string& end) const;

    int getCityCount() const;
    void display(std::ostream& out) const;

    bool loadFromFile(const std::string& fileName);
    bool saveToFile(const std::string& fileName) const;
};

#endif
