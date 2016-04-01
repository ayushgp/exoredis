/*
* The data structures, string and sorted set
*/
#ifndef STRUCTURES
#define STRUCTURES

#include <string>
#include <map>
#include <set>

struct kv_string {
        std::string value;
        long long exp_time;
        kv_string(std::string v): value(v), exp_time(-1) {}
};

struct zset {
        std::map <double, std::set <std::string> > sorted_set;
        long long exp_time;
};

#endif
