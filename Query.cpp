// Implementation of Query Class

#include "Query.h"
#include "QueryException.h"

std::string lower(std::string str){
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

Query::Query( const std::string& q ) : init_query(q) {
        int query_length = q.length();
        for( int i = 0, k = 0; i < query_length; i++, k++) {
                args.push_back("");

                //TODO: Make this work even if there is a quote in between the quotes
                if(q[i] == '"') {
                        i++;
                        while(q[i] != '"') {
                                args[k] += q[i];
                                i++;
                                if (i == query_length)
                                        throw QueryException("Invalid Query.");
                        }
                        i++;
                        continue;
                }

                while(i < query_length && q[i] != ' '){
                        args[k] += q[i];
                        i++;
                }
        }
        try {
                buildQuery();
        }
        catch (QueryException& e){
                throw e;
        }
}

void Query::buildQuery(){
        std::string query_type = lower(args[0]);
        
}
