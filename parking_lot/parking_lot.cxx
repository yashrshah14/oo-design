#include <iostream>
#include <vector>
#include <unordered_map>

enum Type
{
    SMALL = 1;
    MEDIUM = 2;
    LARGE = 3;
};

struct ParkingSpot
{
    Type type;
    int row;
    int col;
    bool is_occupied;
};

class Vehicle
{
    private:
        std::string m_license_plate;
        Type t;
};

class ParkingLot
{
    public:
        ParkingLot(int rows, int cols, int floors)
        {
            m_parking_map.resize(floors);
            for(auto& floor:m_parking_map)
            {
                floor.resize(rows);
                for(auto& row: floor)
                {
                    row.resize(cols);
                }
            }
        }
        bool car_arrives(Vehicle* v)
        {
            // Park vehicle in empty spot and update hash map.
            for(int floor = 0; floor < m_floors; floor++)
            {
                for(int row = 0; row < m_rows; row++)
                {
                    for(int col = 0; col < m_cols; col++)
                    {
                        if(m_parking_map[floor][row][col]->type >= v->type && !m_parking_map[floor][row][col]->is_occupied)
                        {
                            m_parking_map[floor][row][col]->is_occupied = true;
                            m_vehicle_lookup[v->m_license_plate] = m_parking_map[floor][row][col];
                            return true;
                        }
                    }
                }
            }
            // if no vacant spot is available, return false.
            return false;
        }

        void car_leaves(Vehicle* v)
        {
            ParkingSpot* spot = m_vehicle_lookup[v->m_license_plate];
            spot->is_occupied = false;
            m_vehicle_lookup.erase(v->m_license_plate);
        }
    private:
        int m_rows;
        int m_cols;
        int m_floors;
        vector<vector<vector<ParkingSpot*>>> m_parking_map;
        unordered_map<std::string, ParkingSpot*> m_vehicle_lookup; // license plate is key, and ParkingSpot is value
    
};