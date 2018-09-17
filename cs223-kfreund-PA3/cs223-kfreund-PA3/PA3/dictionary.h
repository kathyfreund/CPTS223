/*
 *  dictionary.h -- A hash-based dictionary for searching definitions
 *   Copyright 2017 - Aaron S. Crandall <acrandal@gmail.com>
 */

#ifndef __DICT_H
#define __DICT_H

#include "hashtable.h"
#include "word.h"
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>

class Dictionary
{

	private:
		Hashtable<string, Word> _dict;  // Primary dictionary store

	void parseline( string line )
    {
		
        string token;
        string word;
        string def;
        string file_name;
        string file_in;
        int foo;
        int to_print;

        for(int i = 0; i < line.length(); ++i) //lowercase converter
        {
            line[i] = tolower(line[i]);
        }

        token = line.substr(0, line.find(" "));
       

        if(token == "help") ////////////////////////////////////////////////////////////////////////////////////////DONE
        {
            cout << "Here are the possible commands you can use:" << endl;
            cout << endl;

            cout << "help -> print out command help" << endl;
            cout << "add “word” “definition” -> Add (or update!) a word and it’s definition." << endl;
            cout << "remove “word” -> Remove a given word. Must handle quotes" << endl;
            cout << "define “word” -> Define a word by printing out it’s definition or “unknown word”" << endl;
            cout << "load “filename” -> Load in a JSON file of dictionary words" << endl;
            cout << "unload “filename” -> Remove words from a given JSON file of dictionary words" << endl;
            cout << "size -> Print out current number of words in the dictionary" << endl;
            cout << "clear -> Remove ALL words from the dictionary" << endl;
            cout << "print [#words] -> Print out all words, unless user gives a maximum number" << endl;
            cout << "random -> Print out a single word chosen randomly from the dictionary" << endl;
            cout << "quit -> Quit the user interface and shut down" << endl;
         }
         else if(token == "add") ////////////////////////////////////////////////////////////////////////////////////////DONE
         {
            string input = line.substr(line.find(" ") + 1); //should be everything after add

            if(input[0] == '"') //word has quotations
            {
                word = input.substr(1, input.find(" ")-2);
                input = input.substr(input.find(" ")+1);
            }
            else //word has no quotations
            {
                word = input.substr(0, input.find(" "));
                input = input.substr(input.find(" ")+1);
            }


            if(input[0] == '"') //if definition has quotations
            {
                def = input.substr(input.find('"')+1, input.length()-2);

            }
            else
            {
                def = input;
            }

            //cout << "Word is: " << word << endl; //debugging
            //cout << "Definition is: " << def << endl; //debugging

            _dict.insert(word, Word(word, def));

            if(_dict.contains(word))
            {
                cout << "Word Added!" << endl;
            }
            else
            {
                //cout << "Oh no! Something went wrong - Debug then try again." << endl;
            }
         }
         else if(token == "remove") ////////////////////////////////////////////////////////////////////////////////////////DONE
         {
            string input = line.substr(line.find(" ") + 1);
            if(input[0] == '"') //word has quotations
            {
                word = input.substr(1, input.find(" ")-2);
            }
            else //word has no quotations
            {
                word = input.substr(0, input.find(" "));
            }
            //cout << word << endl; //debugging
            foo = _dict.remove(word);

            if(_dict.contains(word))
            {
                cout << "Oh no! Something went wrong - Debug then try again." << endl;
            }
            else
            {
                cout << "Word Removed!" << endl;
            }
         }
         else if(token == "define") ////////////////////////////////////////////////////////////////////////////////////////DONE
         {
            string input = line.substr(line.find(" ") + 1);
            if(input[0] == '"') //word has quotations
            {
                word = input.substr(1, input.find(" ")-2);
            }
            else //word has no quotations
            {
                word = input.substr(0, input.size());
            }

            cout << word << endl;

            if(_dict.contains(word))
            {
                Word * found = _dict.find(word);
                //cout << found->to_string();
                cout << "Definition for -" << word << "- is: " << found->definition << endl;
            }
            else
            {
                cout << "Unknown word, please try again." << endl;
            }

         }
         else if(token == "load") ////////////////////////////////////////////////////////////////////////////////////////DONE
         {
            string input = line.substr(line.find(" ") + 1);
            if(input[0] == '"') //word has quotations
            {
                file_name = input.substr(1, input.find(" ")-2);
            }
            else //word has no quotations
            {
                file_name = input.substr(0, input.find(" "));
            }
            ifstream in(file_name);
            getline(in, file_in); //get the first dummy line
            getline(in, file_in); //get second dummy line

            while(getline(in, file_in))
            {
                for(int i = 0; i < file_in.length(); ++i) //make all load inserts lowercase
                {
                    file_in[i] = tolower(file_in[i]);
                }

                if(file_in == "  ]") //last line
                {
                    break;
                }
                //cout << file_in << endl; //debugging
                input = file_in.substr(14);
                word = input.substr(0, input.find('"'));
                def = input.substr(input.find(":") + 3);
                def = def.substr(0, def.length()-3);

                /*
                cout << input << endl; //debugging
                cout << word << endl;
                cout << def << endl;
                */

                _dict.insert(word, Word(word, def)); //insert words
            }

         }
         else if(token == "unload") ////////////////////////////////////////////////////////////////////////////////////////DONE
         {
            string input = line.substr(line.find(" ") + 1); //same as load, except deleting items now
            if(input[0] == '"') //word has quotations
            {
                file_name = input.substr(1, input.find(" ")-2);
            }
            else //word has no quotations
            {
                file_name = input.substr(0, input.find(" "));
            }
            ifstream in(file_name);
            getline(in, file_in); //get the first dummy line
            getline(in, file_in); //get second dummy line

            while(getline(in, file_in))
            {
                for(int i = 0; i < file_in.length(); ++i) //make all load inserts lowercase
                {
                    file_in[i] = tolower(file_in[i]);
                }

                if(file_in == "  ]") //last line
                {
                    break;
                }
                //cout << file_in << endl; //debugging
                input = file_in.substr(14);
                word = input.substr(0, input.find('"'));

                /*
                cout << input << endl; //debugging
                cout << word << endl;
                */

                _dict.remove(word);
            }
         }
         else if(token == "size") ////////////////////////////////////////////////////////////////////////////////////////DONE
         {
            cout << "Current number of words in the dictionary is: " << _dict.size() << endl;
         }
         else if(token == "clear") ////////////////////////////////////////////////////////////////////////////////////////DONE
         {
            _dict.clear();
            cout << "Dictionary has been cleared! Proof - size is now: " << _dict.size() << endl;
         }
         else if(token == "print") ////////////////////////////////////////////////////////////////////////////////////////NEEDS WORK
         {
            string input = line.substr(line.find(" ") + 1);
            if(input[0] == '"') //word has quotations
            {
                word = input.substr(1, input.find(" ")-2);
            }
            else //word has no quotations
            {
                word = input.substr(0, input.size());
            }


            if(!word.empty())
            {
                stringstream pass(word);
                pass >> to_print;
                _dict.printMax(to_print);
            }
            else
            {
                _dict.printMax(_dict.size()); //print all
            }
         }
         else if(token == "random") ///////////////////////////////////////////////////////////////////////////////////////NEEDS WORK
         {
            _dict.printRandom();
         }
         else if(token == "quit")////////////////////////////////////////////////////////////////////////////////////////DONE, SORTA?
         {
            cout << "Using std::exit(0) - turned off for testing purposes" << endl;
            //std::exit(0);
         }
         else
         {
            cout << "No such command, try again!" << endl;
         }

	}

	public:
		Dictionary()	// Default constructor
		 { }

	/**
	 *  Run the main dictionary user interface
	 */
	void run_ui() {
		// print out header
		cout << "+------------------------------------------+" << endl;
		cout << "|-- Welcome to the best dictionary evar! --|" << endl;
		cout << "+------------------------------------------+" << endl;

		string instr;
		cout << " Enter command (^D or EOF quits): ";
        
        //cin >> instr;// read in user input until eof

		while (getline(cin, instr)) {
			cout << endl << " --debug-- Entered command: " << instr << endl;
            
			parseline(instr);
			// call function based on line contents
			// print results

			cout << "Enter command: ";
		}
		cout << endl;
	}

};


#endif
