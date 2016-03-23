# exoredis
A minimalistic redis implementation in C++ 

##.EDB format
Exoredis uses a *.edb format to store its database files. 

    exoredis                                        #Every .edb file starts with this word.
    15949863 s foo.bar:baz "Just a little string"   #Every entry here is in order expiry time(in ms), value type, key and encoded value.
    -1 i foo.baz "154"                              #-1 expiry time means never
    -1 z foo 1:{"one","uno"} 2:{"two"} 3:{"three"}  #Sorted sets are stored in sorted order.
    -1 b bar {1,4,6,9}                              #All the values present in this set are set to true
    
The various value types used are:

    s   Simple String
    z   Sorted set
    b   Bit set
