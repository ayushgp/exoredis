#ifndef QueryException_class
#define QueryException_class

#include <string>
#include <iostream>

class QueryException {
        public:
                QueryException ( std::string s ) : m_s ( s ) {}
                ~QueryException (){}
                std::string description() { return m_s; }

        private:
                std::string m_s;
};

#endif
