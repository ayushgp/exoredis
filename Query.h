//Implementation of Query class
#ifndef Query_class
#define Query_class


#include <iostream>
#include <string>
#include <vector>

class Query{
        private:
                enum Type {
                        GET,
                        SET,
                        SETEX,
                        SETPX,
                        SETNX,
                        SETXX,
                        GETBIT,
                        SETBIT,
                        ZADD,
                        ZCARD,
                        ZCOUNT,
                        ZRANGE,
                        SAVE
                };

                std::string init_query, parsed_query;
                std::vector<std::string> args;
                Type check_type(std::string);
                void buildQuery();
        public:
                Query(const std::string&);
                std::string getParsedQuery();
};

#endif
