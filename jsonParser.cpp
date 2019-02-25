#include<stdio.h>
#include<iostream>
#include<ctype.h>
#include<string>
#include<regex>
#include"trie.h"
#include<json-c/json.h>

using namespace std;

//to find a word in the json file
string find_something(const char *key){
	struct json_object *tmp, *main_obj, *meaning_array, *meaning_array_obj, *meaning_array_obj_def;
	struct json_object *synonyms_array, *synonym_word;
	char filename[] = "wordset/data/a.json";
	int i, arraylen;

	//creating a new json object according to our needs to send to client
	struct json_object *jobj = json_object_new_object();
	struct json_object *status = json_object_new_boolean(10);
	struct json_object *synArray = json_object_new_array();
	struct json_object *meanArray = json_object_new_array();

	filename[13] = tolower(key[0]);	//find the json file with first char of the key
	main_obj = json_object_from_file(filename);	//get the main object from the file
	json_object_object_get_ex(main_obj, key, &tmp); //find the word in the main_obj

	if(tmp != NULL){
		meaning_array = json_object_object_get(tmp, "meanings");

		if(meaning_array != NULL){	// meaning_array is an array of objects
			arraylen = json_object_array_length(meaning_array);

			for (i = 0; i < arraylen; i++){
				// get the i-th object in meaning_array
				meaning_array_obj = json_object_array_get_idx(meaning_array, i);
				
				// get the name attribute in the i-th object
				meaning_array_obj_def = json_object_object_get(meaning_array_obj, "def");

				string temp = json_object_get_string(meaning_array_obj_def);
				json_object *tempStr = json_object_new_string(temp.c_str());

				//adding this definition to our meaning array which we will send to client
				json_object_array_add(meanArray, tempStr);

				synonyms_array = json_object_object_get(meaning_array_obj, "synonyms");
				if(synonyms_array != NULL){
					for (int j = 0; j < json_object_array_length(synonyms_array); j++){
						synonym_word = json_object_array_get_idx(synonyms_array, j);
						temp = json_object_get_string(synonym_word);

						tempStr = json_object_new_string(temp.c_str());

						//also adding synonyms to our synonyms array
						json_object_array_add(synArray, tempStr);
					}
					status = json_object_new_boolean(10);
				}
			}
		}

		json_object_object_add(jobj,"status", status);
		json_object_object_add(jobj,"meanings", meanArray);
	 	json_object_object_add(jobj,"synonyms", synArray);
	}
	else{
		string correct_word = ret_cor_word(key ,"corpus");
		json_object *tempStr;

		if(correct_word=="UNDEFINED")
			tempStr = json_object_new_string("We couldn't find the word as it is outside the range of spell checker.");
		else
			tempStr = json_object_new_string(("Did you mean : "+correct_word).c_str());

		status = json_object_new_boolean(0);
		json_object_array_add(synArray, tempStr);

		json_object_object_add(jobj,"synonyms", synArray);
		json_object_object_add(jobj,"status", status);
	}
	return json_object_get_string(jobj);
}

void createTrie(){
	struct json_object *main_obj, *meaning_array, *meaning_array_obj, *meaning_array_obj_def;
	int arraylen, i;
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char filename[] = "wordset/data/a.json";
	char *ptr;

    root = getNode();

    regex expr("[a-z]*");	//to remove the words with hyphen or spaces etc.

	//to insert all the words from json files to the trie
	for(i = 0; i<26; i++){
		filename[13] = alphabet[i];
		main_obj = json_object_from_file(filename);	//get the main object from the file

		if(main_obj != NULL){
			//iterate over all the given words and insert them into trie
			json_object_object_foreach(main_obj, key, val){
				if(regex_match(key, expr)){
					insert(root, key);
				}		//insert the word into the trie
			}
		}
	}
	return;
}