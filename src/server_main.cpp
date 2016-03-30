#include "ServerSocket.h"
#include "SocketException.h"
#include "server_config.h"
#include "structures.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>
#include <stdexcept>


/*
* Import all key value pairs and sets from the dumpfile.
*/

// void import_from_file(const std::string& path,
//         std::map <std::string, kv_string>& kv_map,
//          std::map <std::string, kv_bool>& bit_map,
//          std::map <std::string, zset>& zset_map) {
//
//         std::ifstream dump;
//         dump.open(path.c_str());
//         for( std::string line; getline(dump, line);) {
//                 //Determine type of entry
//                 switch(line[0]) {
//                         //Key value pair
//                         case 's':
//                                 std::vector<std::string> parts = deocde_kv_entry(line);
//                                 kv_string *kv = new kv_string();
//                                 kv->exp_time = parts[1];
//                                 kv->value = parts[3];
//                                 kv_map[parts[2]] = *kv;
//                                 break;
//                         //Sorted set
//                         case 'z':
//                                 zset *z = new zset();
//
//                                 break;
//                         //Bits mapped to a string
//                         case 'b':
//                                 break;
//                 }
//         }
//         dump.close();
//
// }

void split_in_args(std::vector<std::string>& qargs, std::string command){
        int len = command.length();
        bool qot = false, sqot = false;
        int arglen;
        for(int i = 0; i < len; i++) {
                int start = i;
                if(command[i] == '\"') {
                        i++;
                        start++;
                        qot = true;
                }
                else if(command[i] == '\'') {
                        i++;
                        start++;
                        sqot = true;
                }

                if(qot) {
                        while(i<len && command[i] != '\"')
                                i++;
                        if(i<len)
                                qot = false;
                        arglen = i-start;
                        i++;
                        while(i<len && command[i]==' ')
                                i++;
                }
                else if(sqot) {
                        while(i<len && command[i] != '\'')
                                i++;
                        if(i<len)
                                sqot = false;
                        arglen = i-start;
                        i++;
                        while(i<len && command[i]==' ')
                                i++;
                }
                else{
                        while(i<len && command[i]!=' ')
                                i++;
                        arglen = i-start;
                }
                if(arglen == 1) continue;
                qargs.push_back(command.substr(start, arglen));
        }
        for(int i=0;i<qargs.size();i++){
                std::cout<<qargs[i]<<std::endl;
        }
        std::cout<<qargs.size()<<std::endl;
        if(qot || sqot){
                throw std::string("-ERR Protocol error: unbalanced quotes in request");
        }
}

std::string wrong_args_error(std::string command){
        return "-ERR wrong number of arguments for '"+command+"' command\n\r";
}
std::string process_query(std::string query, std::map <std::string, kv_string>& kv_map,
        std::map <std::string, kv_bool>& bit_map,
        std::map <std::string, zset>& zset_map){

                std::vector<std::string> qargs;
                try{
                        split_in_args(qargs,query);
                }
                catch(std::string err){
                        return err;
                }
                if(qargs[0] == "get"){
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
                else if(qargs[0] == "set"){
                        if(qargs.size()==3){
                                kv_string *new_entry = new kv_string();
                                new_entry->value = qargs[2];
                                kv_map[qargs[1]] = *new_entry;
                        }
                }
                else {
                        return "Command not found!";
                }
}

int main ( int argc, char* argv[] ) {
        std::string dump_file_path = DEFAULT_FILE_PATH;
        char c;

        //check for an input file
        while ((c = getopt (argc, argv, "f:")) != -1){
                switch (c) {
                        case 'f':
                        dump_file_path = optarg;
                        break;
                        default:
                        std::cout << "\nInvalid arguments. Use -f \"/path/to/file\" to import data from file. Default file is ../.exoredis\n";
                }
        }

        std::map <std::string, kv_string> kv_map;
        std::map <std::string, kv_bool> bit_map;
        std::map <std::string, zset> zset_map;

        // import_from_file(dump_file_path ,kv_map, bit_map, zset_map);

        try {
                // Create the socket
                ServerSocket server ( 15000 );
                std::cout << "ExoRedis server running on 0.0.0.0:15000" << std::endl;
                std::string res;
                while(true) {
                        ServerSocket new_sock;
                        server.accept ( new_sock );
                        try {
                                while(true) {
                                        std::string data;
                                        new_sock >> data;
                                        res = process_query(data, kv_map, bit_map, zset_map);
                                        new_sock << res;
					std::cout << data;
                                }
                        }
                  catch(SocketException&) {}
                }
        }
        catch ( SocketException& e ){
                std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
        }
        return 0;
}
