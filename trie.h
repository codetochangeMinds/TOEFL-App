#ifndef TRIE_H_
#define TRIE_H_

#include<stdbool.h>
#include <bits/stdc++.h>
#include<string>

using namespace std;

#define ALPHABET_SIZE 26

struct trieNode{
	struct trieNode *children[ALPHABET_SIZE];
	bool isEndOfWord;
};

extern struct trieNode* root;

int charToAscii(char x);
struct trieNode *getNode(void);
void insert(struct trieNode *, const char *);
bool search(struct trieNode *, const char *);
bool isLastNode(struct trieNode* );
int printAutoSuggestions(struct trieNode* , const char *, string *);
void suggestRec(struct trieNode *, const char *, string *);

// functions of jsonParser
void createTrie();
string find_something(const char *);

//functions of spellchecker
string ret_cor_word(string ,string );
vector<string> edit1distance(string );
string getstring(char );
map<string, int> count_words(string );


#endif