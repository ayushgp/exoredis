/*
* The data structures, string and sorted set
*/
#include <string>
#include <map>
#include <set>

struct kv_string {
        std::string value;
        long long exp_time;
};

struct kv_bool {
        std::map <int, bool> value;
        long long exp_time;
};

struct zset {
        std::map <double, std::set <std::string> > sorted_set;
        long long exp_time;
};
