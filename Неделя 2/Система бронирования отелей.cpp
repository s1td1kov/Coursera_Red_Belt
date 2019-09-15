#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct Event {
    int64_t time;
    string hotel_name;
    int client_id;
    int room_count;
};

class HotelManager {
public:
    HotelManager() {}
    
    void Book(int64_t time, const string& hotel_name,
              int client_id, int room_count) {
        events.push({time, hotel_name, client_id, room_count});
        clients[hotel_name][client_id] += room_count;
        rooms[hotel_name] += room_count;
        Adjust(time);
    }
    
    size_t GetClients(const string& hotel_name) {
        return clients[hotel_name].size();
    }
    
    size_t GetRooms(const string& hotel_name) {
        return rooms[hotel_name];
    }
    
private:
    queue<Event> events;
    map<string, map<int, int>> clients;
    map<string, int> rooms;
    
    void Adjust(int64_t current_time) {
        while (!events.empty() && events.front().time + 86400 <= current_time) {
            auto first = events.front();
            clients[first.hotel_name][first.client_id] -= first.room_count;
            if (clients[first.hotel_name][first.client_id] == 0) {
                clients[first.hotel_name].erase(first.client_id);
            }
            
            rooms[first.hotel_name] -= first.room_count;
            
            events.pop();
        }
    }
};


int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int query_count;
    cin >> query_count;
    
    HotelManager hotelmanager;
    
    for (int i = 0; i < query_count; ++i) {
        string operation;
        cin >> operation;
        
        if (operation == "BOOK") {
            int64_t time;
            string hotel_name;
            int client_id;
            int room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            hotelmanager.Book(time, hotel_name, client_id, room_count);
        } else if (operation == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotelmanager.GetClients(hotel_name) << '\n';
        } else if (operation == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotelmanager.GetRooms(hotel_name) << '\n';
        }
    }
    
    return 0;
}
