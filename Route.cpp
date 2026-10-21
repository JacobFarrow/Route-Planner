#include "Route.h"
#include <iomanip>

Route::Route()
    : totalDistance(0.0)
{
}

Route::Route(const std::vector<std::string>& stops, double totalDistance)
    : stops(stops), totalDistance(totalDistance)
{
}

bool Route::isFound() const
{
    return !stops.empty();
}

double Route::getTotalDistance() const
{
    return totalDistance;
}

int Route::getStopCount() const
{
    return static_cast<int>(stops.size());
}

std::ostream& operator<<(std::ostream& out, const Route& route)
{
    if (!route.isFound())
    {
        out << "No route found.";
        return out;
    }

    out << "Route: ";
    for (size_t i = 0; i < route.stops.size(); ++i)
    {
        if (i > 0)
        {
            out << " -> ";
        }
        out << route.stops[i];
    }

    out << std::endl << "Total distance: " << std::fixed << std::setprecision(1)
        << route.totalDistance << " miles";

    return out;
}
