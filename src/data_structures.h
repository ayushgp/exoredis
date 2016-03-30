#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES
#include <string>
#include <set>

long long current_system_time(){
        return std::chrono::duration_cast< std::chrono::milliseconds >(
                system_clock::now().time_since_epoch()
        ).count();
}

struct kvpair {
        long long expire_time;
        std::string value;
        kvpairs( std::string val ) : value( val ) {
                expire_time = -1;
        }
        kvpairs( std::string val, long long exp_time ) :
                value( val ),
                expire_time( exp_time ) { }
};

struct zset {
        struct element {
                long long expire_time;
                double value;
                std::set< std::string > str_set;
        };
        std::map<std::string, element> set_map;
        push(double key, std::string value){
                if(set_map[key].expire_time > )
        }
};

#endif
