#include "QueryProcessing.h"

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdexcept>

void split_in_args(str_vector& qargs, std::string command){
        int len = command.length()-2;
        bool qot = false, sqot = false;
        int arglen;
        for(int i = 0; i < len;) {
                int start = i;
                if(command[i] == '\"') qot = true;
                else if(command[i] == '\'') sqot = true;
                if(qot){
                        start++;
                        i++;
                        while(i<len && command[i] != '\"')
                                i++;
                        if(i>=len) break;
                        else qot = false;
                        arglen = i-start-1;
                        i++;
                }
                else if(sqot){
                        start++;
                        i++;
                        while(i<len && command[i] != '\'')
                                i++;
                        if(i>=len) break;
                        else sqot = false;
                        arglen = i-start-1;
                        i++;
                }
                else{
                        while(i<len && command[i] != ' ')
                        i++;
                        arglen = i-start;
                }
                while(i<len && command[i] == ' ') i++;
                qargs.push_back(command.substr(start, arglen));
        }
        if(qot || sqot){
                throw std::string("-ERR Protocol error: unbalanced quotes in request");
        }
}

std::string wrong_args_error(std::string command){
        return "-ERR wrong number of arguments for '"+command+"' command\n\r";
}
std::string process_query(std::string query, KV_map& kv_map, ZSET_map& zset_map){

                std::vector<std::string> qargs;
                try{
                        split_in_args(qargs,query);
                }
                catch(std::string err){
                        return err;
                }
                if(!qargs[0].compare("set")){
                        if(qargs.size()==3){
                                KV_map::iterator kv_iter = kv_map.find(qargs[1]);
                                if(kv_iter == kv_map.end())
                                        kv_map.insert(std::make_pair(qargs[1], kv_string(qargs[2])));
                                else{
                                        kv_iter->second.value = qargs[2];
                                }
                                return "+OK\n\r";
                        }
                        else{
                                return wrong_args_error("set");
                        }
                }
                else if(!qargs[0].compare("get")){
                        if(qargs.size() != 2)
                                return wrong_args_error("get");
                        else {
                                try {
                                        kv_string result = kv_map.at(qargs[1]);
                                        std::stringstream ss;
                                        ss << "$" << result.value.length() << "\n\r" << result.value << "\n\r";
                                        return ss.str();
                                }
                                catch(const std::out_of_range& oor){
                                        return "$-1\n\r";
                                }
                        }
                }
                else if(!qargs[0].compare("getbit")){
                        if(qargs.size() == 3){
                                try {
                                        kv_string result = kv_map.at(qargs[1]);
                                        std::stringstream ss;
                                        int bit = atoi(qargs[2].c_str());
                                        ss << ":" << (result.value[bit] & 1<<((bit%8))) <<"\n\r";
                                        return ss.str();
                                }
                                catch(const std::out_of_range& oor){
                                        return ":0\n\r";
                                }
                        }
                        else
                                return wrong_args_error("getbit");
                }
                else if(!qargs[0].compare("setbit")){
                        if(qargs.size() == 4){

                        }
                        else
                                return wrong_args_error("getbit");
                }
                else if(!qargs[0].compare("zadd")){

                }
                else if(!qargs[0].compare("zrange")){

                }
                else if(!qargs[0].compare("zcard")){

                }
                else if(!qargs[0].compare("zcount")){

                }
                else if(!qargs[0].compare("save")){
                        if(qargs.size() == 1){
                                return "Saved changes to ./.exoredis.edb";
                        }
                        else
                                return wrong_args_error("save");
                }
                else {
                        return "Command not found!";
        }
}
