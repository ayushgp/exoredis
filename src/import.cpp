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
