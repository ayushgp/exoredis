#include "ClientSocket.h"
#include "SocketException.h"
#include "Query.h"
#include "QueryException.h"

#include <string>
#include <iostream>

int main ( int argc, char* argv[] ) {
        try {
                ClientSocket client_socket ( "localhost", 30000 );
                std::string reply,query;
                while(true) {
                        try {
                                std::getline( std::cin, query );
                                try {
                                        Query q = Query(query);
                                }
                                catch(QueryException& e) {
                                        std::cout << "Error processing the query: "
                                                << e.description() << std::endl;
                                }
                                client_socket << query;
                                client_socket >> reply;
                        }
                        catch ( SocketException& e) {
                                std::cout << "Error in connecting to the server."
                                        " Please try restarting both the client "
                                        "and server:" << e.description() << "\n";
                        }
                        std::cout << "We received this response from the server:\n\"" << reply << "\"\n";
                }

        }
        catch ( SocketException& e ){
                std::cout << "Exception was caught:" << e.description() << "\n";
        }
        return 0;
}
