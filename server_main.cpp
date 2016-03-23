#include "ServerSocket.h"
#include "SocketException.h"
#include "server_config.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <fstream>

/*
* Import all key value pairs and sets from the dumpfile.
*/
void import_from_file(const std::string& path,
                        std::map<std::string,std::string>& kv_map,
                        std::map<std::string,std::map<int,bool> >& bit_map,
                        std::map<std::string,std::set<std::string> >){
        std::ifstream dump = (path);
        for( std::string line; getline(dump, line);){
                switch(line[0]){
                        case '':

                                break;
                        case '!':

                }
        }

}

int main ( int argc, char* argv[] ) {
        std::string dump_file_path = DEFAULT_FILE_PATH;
        char c;
        while ((c = getopt (argc, argv, "f:")) != -1)
                switch (c)
        {
                case 'f':
                        dump_file_path = optarg;
                        break;
                default:
                        std::cout << "\nInvalid arguments. Use -f \"/path/to/file\" to import data from file. Default file is ~/.exoredis\n";
        }

        try {
                // Create the socket
                ServerSocket server ( 15000 );
                std::cout << "ExoRedis server running on 0.0.0.0:15000" << std::endl;
                while(true) {
                        ServerSocket new_sock;
                        server.accept ( new_sock );
                        try {
                                while(true) {
                                        std::string data;
                                        new_sock >> data;
                                        new_sock << data;
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
