#include "structures.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdexcept>

typedef std::vector<std::string> str_vector;
typedef std::map <std::string, kv_string> KV_map;
typedef std::map <std::string, zset> ZSET_map;

void split_in_args(str_vector& qargs, std::string command);

std::string process_query(std::string query, KV_map& kv_map, ZSET_map& zset_map);
