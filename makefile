JSON_C_DIR=/usr/local
CFLAGS += -I$(JSON_C_DIR)/include/json-c
LDFLAGS+= -L$(JSON_C_DIR)/lib -ljson-c

hellomake: jsonParser.cpp
	g++ server.cpp jsonParser.cpp spellChecker.cpp trie.cpp -o jsonParser $(CFLAGS) $(LDFLAGS)
	./jsonParser

clean: 
	rm -f *.o jsonParser