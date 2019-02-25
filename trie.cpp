#include<stdio.h>
#include<string>
#include<stdlib.h>
#include"trie.h"
#include <string.h>

struct trieNode* root;

int charToAscii(char x){
	return (int)(x) - (int)('a');
}

//to create and return a new trieNode
struct trieNode *getNode()
{
	struct trieNode *temp = (struct trieNode *)malloc(sizeof(struct trieNode));

    //initialize all the children with NULL values
	if(temp != NULL) 
    { 
        int i; 
        temp->isEndOfWord = false; 
        for (i = 0; i < ALPHABET_SIZE; i++) 
   			temp->children[i] = NULL; 
    }
  
    return temp; 
};

//to insert a word into the trie
void insert(struct trieNode *root, const char *word){
	struct trieNode *crawl;
	int i, index;

	crawl = root;

	int length = strlen(word);

    //traverse till the prefix mismatch and then insert latter characters
	for(i = 0; i<length; i++){
		index = charToAscii(word[i]);
		
		if(!crawl->children[index])
			crawl->children[index] = getNode();

		crawl = crawl->children[index];
	}

	crawl->isEndOfWord = true;
}

//search for a given word in the trie
bool search(struct trieNode *root, const char *word){
	struct trieNode *crawl;
	int i;

	crawl = root;

	int length = strlen(word);

    //traverse till any letter mismatch
	for(i = 0; i<length; i++){
		if(!crawl->children[charToAscii(word[i])])
			return false;

		crawl = crawl->children[charToAscii(word[i])];
	}

    //also check if given string is an ending word if found
	if(crawl->isEndOfWord == true)
		return true;
}

//check if the given node is the last node i.e. it does not have any children
bool isLastNode(struct trieNode* root) 
{
	for(int i = 0; i < ALPHABET_SIZE; i++){
    	if(root->children[i] != NULL) 
            return false; 
    }
    return true; 
}

//suggest words by recursion
void suggestRec(struct trieNode *root, const char *currprefix, string *finalSuggests){
	if(root->isEndOfWord){
        *finalSuggests += currprefix;
		*finalSuggests += " ";
    }

	if(isLastNode(root)) 
        return; 

  	int i, temp;
  	char t[2];
  	char newprefix[20];

    for(i = 0; i < ALPHABET_SIZE; i++) 
    {
		if(root->children[i]) 
        {
  			strcpy(newprefix, currprefix);

    		temp = i+97;
			strcpy(t, (char *)(&temp));

			//append current character to currPrefix string 			
			strcat(newprefix, t);
  
            //recur over the rest
            suggestRec(root->children[i], newprefix, finalSuggests);
        }
    }
}

// print suggestions for given query prefix. 
int printAutoSuggestions(struct trieNode* root, const char *query, string *finalSuggests) 
{ 
    struct trieNode* pCrawl = root; 
  
    // Check if prefix is present and find the 
    // the node (of last level) with last character 
    // of given string. 
    int level;
    int n = strlen(query);
    for (level = 0; level < n; level++) 
    { 
        int index = charToAscii(query[level]); 
  
        // no string in the Trie has this prefix 
        if (!pCrawl->children[index]) 
            return 0; 
  
        pCrawl = pCrawl->children[index]; 
    } 
    
    // If prefix is last node of tree (has no 
    // children) 
    bool isLast = isLastNode(pCrawl); 
  
    // If there are are nodes below last 
    // matching character. 
    if (!isLast) 
    {
        suggestRec(pCrawl, query, finalSuggests); 
        return 1; 
    } 
}