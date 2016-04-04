#include "ServerSocket.h"
#include "SocketException.h"
#include "server_config.h"
#include "structures.h"
#include "QueryProcessing.h"

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

        //Declare the structures
        std::map <std::string, kv_string> kv_map;
        std::map <std::string, zset> zset_map;

        try {
                // Create the socket
                ServerSocket server ( 15000 );
                // std::signal(SIGINT, close_connection);
                std::cout << "ExoRedis server running on 0.0.0.0:15000" << std::endl;
                std::string res;
                while(true) {
                        ServerSocket new_sock;
                        server.accept ( new_sock );
                        try {
                                while(true) {
                                        std::string data;
                                        new_sock >> data;
                                        res = process_query(data, kv_map, zset_map);
                                        new_sock << res;
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
