#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <vector>
#include <iostream>

class Route
{
private:
    std::vector<std::string> stops;
    double totalDistance;

public:
    Route();
    Route(const std::vector<std::string>& stops, double totalDistance);

    bool isFound() const;
    double getTotalDistance() const;
    int getStopCount() const;

    friend std::ostream& operator<<(std::ostream& out, const Route& route);
};

#endif
