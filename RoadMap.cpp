#include "RoadMap.h"
#include <fstream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

bool RoadMap::hasCity(const std::string& name) const
{
    return cities.find(name) != cities.end();
}

bool RoadMap::addCity(const std::string& name)
{
    if (name.empty() || hasCity(name))
    {
        return false;
    }

    cities[name] = std::make_shared<City>(name);
    return true;
}

bool RoadMap::addRoad(const std::string& from, const std::string& to, double distance)
{
    if (from == to || distance <= 0 || !hasCity(from) || !hasCity(to))
    {
        return false;
    }

    if (cities.at(from)->hasRoadTo(to))
    {
        return false;
    }

    cities.at(from)->addRoad(to, distance);
    cities.at(to)->addRoad(from, distance);
    return true;
}

bool RoadMap::removeRoad(const std::string& from, const std::string& to)
{
    if (!hasCity(from) || !hasCity(to))
    {
        return false;
    }

    bool removedForward = cities.at(from)->removeRoad(to);
    bool removedBackward = cities.at(to)->removeRoad(from);
    return removedForward && removedBackward;
}

Route RoadMap::findShortestRoute(const std::string& start, const std::string& end) const
{
    if (!hasCity(start) || !hasCity(end))
    {
        return Route();
    }

    const double infinity = std::numeric_limits<double>::infinity();
    std::map<std::string, double> distances;
    std::map<std::string, std::string> previous;

    for (std::map<std::string, std::shared_ptr<City>>::const_iterator it = cities.begin(); it != cities.end(); ++it)
    {
        distances[it->first] = infinity;
    }
    distances[start] = 0.0;

    typedef std::pair<double, std::string> QueueEntry;
    std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry>> queue;
    queue.push(QueueEntry(0.0, start));

    while (!queue.empty())
    {
        QueueEntry current = queue.top();
        queue.pop();

        double currentDistance = current.first;
        std::string currentCity = current.second;

        if (currentDistance > distances[currentCity])
        {
            continue;
        }

        if (currentCity == end)
        {
            break;
        }

        const std::list<Road>& roads = cities.at(currentCity)->getRoads();
        for (std::list<Road>::const_iterator road = roads.begin(); road != roads.end(); ++road)
        {
            double newDistance = currentDistance + road->getDistance();
            std::string neighbor = road->getDestination();

            if (newDistance < distances[neighbor])
            {
                distances[neighbor] = newDistance;
                previous[neighbor] = currentCity;
                queue.push(QueueEntry(newDistance, neighbor));
            }
        }
    }

    if (distances[end] == infinity)
    {
        return Route();
    }

    std::vector<std::string> stops;
    std::string step = end;
    stops.push_back(step);

    while (step != start)
    {
        step = previous[step];
        stops.push_back(step);
    }

    std::reverse(stops.begin(), stops.end());
    return Route(stops, distances[end]);
}

int RoadMap::getCityCount() const
{
    return static_cast<int>(cities.size());
}

void RoadMap::display(std::ostream& out) const
{
    if (cities.empty())
    {
        out << "The map is empty." << std::endl;
        return;
    }

    for (std::map<std::string, std::shared_ptr<City>>::const_iterator it = cities.begin(); it != cities.end(); ++it)
    {
        out << *(it->second) << std::endl;
    }
}

bool RoadMap::loadFromFile(const std::string& fileName)
{
    std::ifstream file(fileName);

    if (!file)
    {
        return false;
    }

    cities.clear();

    std::string type;
    while (file >> type)
    {
        if (type == "CITY")
        {
            std::string name;
            file >> name;
            addCity(name);
        }
        else if (type == "ROAD")
        {
            std::string from;
            std::string to;
            double distance;
            file >> from >> to >> distance;
            addRoad(from, to, distance);
        }
    }

    return true;
}

bool RoadMap::saveToFile(const std::string& fileName) const
{
    std::ofstream file(fileName);

    if (!file)
    {
        return false;
    }

    for (std::map<std::string, std::shared_ptr<City>>::const_iterator it = cities.begin(); it != cities.end(); ++it)
    {
        file << "CITY " << it->first << std::endl;
    }

    for (std::map<std::string, std::shared_ptr<City>>::const_iterator it = cities.begin(); it != cities.end(); ++it)
    {
        const std::list<Road>& roads = it->second->getRoads();
        for (std::list<Road>::const_iterator road = roads.begin(); road != roads.end(); ++road)
        {
            if (it->first < road->getDestination())
            {
                file << "ROAD " << it->first << " " << road->getDestination()
                     << " " << road->getDistance() << std::endl;
            }
        }
    }

    return true;
}
