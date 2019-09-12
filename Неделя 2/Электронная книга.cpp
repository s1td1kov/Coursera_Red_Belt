#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;

class ReadingManager {
public:
    ReadingManager() : pages_(1001, 0) {}
    
    void Read(const int& user_id, const int& page_count)  {
        for (int i = users_[user_id]; i < page_count; ++i) {
            ++pages_[i];
        }
        users_[user_id] = page_count;
        
    }
    double Cheer(const int& user_id) const {
        
        if (users_.count(user_id) == 0) {
            return 0.0;
        }
        
        const size_t users_size = users_.size();
        
        const int page_read = users_.at(user_id);
        
        if (users_size == 1u) {
            return 1.0;
        }
        
        if (page_read == 1) {
            return 0.0;
        }
        
        if (page_read == 1000) {
            return (users_size - pages_[999]) * 1.0 / (users_size - 1);
        }
        
        if (pages_[page_read - 1] == 1) {
            return 1.0;
        }
        
        const int better = pages_[page_read];
        const int like = pages_[page_read - 1] - better;
        const int worse = users_size - better - like;
        
        return  worse * 1.0 / (users_size - 1);
        
    }
private:
    map<int, int> users_;
    vector<int> pages_;
};


int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ReadingManager manager;
    
    int query_count;
    cin >> query_count;
    
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;
        
        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
    return 0;
}
