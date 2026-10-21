#include <iostream>
#include <string>
#include "RoadMap.h"

using namespace std;

const string MAP_FILE = "map.txt";

void displayMenu()
{
    cout << endl;
    cout << "Route Planner Menu:" << endl;
    cout << "0. Quit Program" << endl;
    cout << "1. Display map" << endl;
    cout << "2. Find shortest route" << endl;
    cout << "3. Add a city" << endl;
    cout << "4. Add a road" << endl;
    cout << "5. Remove a road" << endl;
    cout << "6. Save map to file" << endl;
    cout << "7. Reload map from file" << endl;
    cout << "Your choice: ";
}

string promptForCity(const string& prompt)
{
    string name;
    cout << prompt;
    cin >> name;
    return name;
}

void findRoute(RoadMap& roadMap)
{
    string start = promptForCity("Enter the starting city: ");
    string end = promptForCity("Enter the destination city: ");

    if (!roadMap.hasCity(start) || !roadMap.hasCity(end))
    {
        cout << "One or both cities are not on the map." << endl;
        return;
    }

    cout << roadMap.findShortestRoute(start, end) << endl;
}

void addCity(RoadMap& roadMap)
{
    string name = promptForCity("Enter the city name (one word): ");

    if (roadMap.addCity(name))
    {
        cout << "City added." << endl;
    }
    else
    {
        cout << "That city is already on the map." << endl;
    }
}

void addRoad(RoadMap& roadMap)
{
    string from = promptForCity("Enter the first city: ");
    string to = promptForCity("Enter the second city: ");

    double distance;
    cout << "Enter the distance in miles: ";
    if (!(cin >> distance))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid distance." << endl;
        return;
    }

    if (roadMap.addRoad(from, to, distance))
    {
        cout << "Road added." << endl;
    }
    else
    {
        cout << "Road could not be added. Check that both cities exist, are different, the distance is greater than zero, and the road is not already on the map." << endl;
    }
}

void removeRoad(RoadMap& roadMap)
{
    string from = promptForCity("Enter the first city: ");
    string to = promptForCity("Enter the second city: ");

    if (roadMap.removeRoad(from, to))
    {
        cout << "Road removed." << endl;
    }
    else
    {
        cout << "No road was found between those cities." << endl;
    }
}

void saveMap(RoadMap& roadMap)
{
    if (roadMap.saveToFile(MAP_FILE))
    {
        cout << "Map saved to " << MAP_FILE << "." << endl;
    }
    else
    {
        cout << "Could not save the map." << endl;
    }
}

void loadMap(RoadMap& roadMap)
{
    if (roadMap.loadFromFile(MAP_FILE))
    {
        cout << "Loaded " << roadMap.getCityCount() << " cities from " << MAP_FILE << "." << endl;
    }
    else
    {
        cout << "Could not open " << MAP_FILE << ". Starting with an empty map." << endl;
    }
}

int main()
{
    RoadMap roadMap;
    loadMap(roadMap);

    int choice = -1;

    while (choice != 0)
    {
        displayMenu();

        if (!(cin >> choice))
        {
            if (cin.eof())
            {
                break;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Please try again." << endl;
            choice = -1;
            continue;
        }

        switch (choice)
        {
        case 0:
            cout << "Goodbye!" << endl;
            break;
        case 1:
            roadMap.display(cout);
            break;
        case 2:
            findRoute(roadMap);
            break;
        case 3:
            addCity(roadMap);
            break;
        case 4:
            addRoad(roadMap);
            break;
        case 5:
            removeRoad(roadMap);
            break;
        case 6:
            saveMap(roadMap);
            break;
        case 7:
            loadMap(roadMap);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
