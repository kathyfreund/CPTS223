/**
 *  Basic hash table implementation
 *   Aaron S. Crandall - 2017 <acrandal@gmail.com>
 *
 */

#ifndef __HASH_H
#define __HASH_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include "word.h"
#include <locale>
#include <cstdlib>
#include <time.h>
#include <sstream>

using namespace std;


template <typename KEYTYPE, typename VALTYPE>
class Hashtable
{
	private:

        //ADDED VECTOR AND RUNNING NUMBER OF ELEMENTS - book's idea
        vector< list<Word> > table; //a vector of buckets, each bucket has an array of values(Word)
        int current_elements;


		void rehash() ////////////////////////////////////////////////////////DONE - WORKING
        {
            vector<list<Word>> old = table;

            table.resize(nextPrime(2*table.size()));
            for (auto & thisList : table)
            {
                thisList.clear();
            }

            //copying
            current_elements = 0;
            for(auto & thisList : old) //so expensive :(
            {
                for(auto & x : thisList)
                {
                    insert(x.myword, std::move(x));
                }
            }
		}
              

		//Function that takes the key (a string or int) and returns the hash key
		int hash_function(int key) /////////////////////////////////////////////DONE
        {
			//cout << " Hashing with int type keys." << endl;
            int size = bucket_count();
            return key % size;

		}
		int hash_function(string key) ///////////////////////////////////////////DONE
        {

			//cout << " Hashing with string type keys." << endl;
            int hashVal = 0;

            for (char ch : key) //algorithm from book figure 5.4
            {
                hashVal = 37 * hashVal + ch;
            }

            return hashVal % table.size();
         
		}



//*************************************PUBLIC************************************************//

		
	public:

    
		Hashtable( int startingSize = 101 ) //MESSED AROUND HERE A BIT
		{
            current_elements = 0;
            table.resize(startingSize); //https://stackoverflow.com/questions/37196329/c-standard-vector-resize-function
		}

		/**
		 *  Add an element to the hash table
		 */
		bool insert(KEYTYPE key, VALTYPE val) /////////////////////////////////DONE
        {
            int hash = hash_function(key);
            while(hash > table.size())
            {
                rehash();
            }
            auto & whichList = table[hash];

            for(list<Word>::iterator it = whichList.begin(); it != whichList.end(); ++it)
            {
                if((*it).myword == key)
                {
                    cout << "Word alread exists! Rewriting..." << endl;
                    (*it) = val;
                    return false;

                }
            }

            whichList.push_back(val);
            current_elements++;

            load_factor(); //check if need to rehash

            return true;

		}

		/**
		 *  Return whether a given key is present in the hash table
		 */
		bool contains(KEYTYPE key) ///////////////////////////////////////////WORKS
        {
            int hash = hash_function(key);
            auto & whichList = table[hash];

            for(list<Word>::iterator it = whichList.begin(); it != whichList.end(); ++it)
            {
                if((*it).myword == key)
                {
                    return true;
                }
            }
            return false;



		}


		/**
		 *  Completely remove key from hash table
		 *   Returns number of elements removed
		 */
		int remove(KEYTYPE key) /////////////////////////////////////////////WORKS
        {
			int hash = hash_function(key);
            auto & whichList = table[hash];
            for(list<Word>::iterator it = whichList.begin(); it != whichList.end(); ++it)
            {
                //cout << (*it).myword << endl; //debugging
                if((*it).myword == key)
                {
                    whichList.erase(it);
                    current_elements--;
                    return 1;
                }
            }
            return 0;
		}

		/**
		 *  Searches the hash and returns a pointer
		 *  Pointer to Word if found, or nullptr if nothing matches
		 */
		VALTYPE *find(KEYTYPE key) ///////////////////////////////////////////WHAT IS WRONG HERE???
        {
            int hash = hash_function(key);
            auto & whichList = table[hash];
            for(list<Word>::iterator it = whichList.begin(); it != whichList.end(); ++it)
            {
                if((*it).myword == key)
                {
                    return &(*it);

                }
            }
			return nullptr;
		}

		/**
		 *  Return current number of elements in hash table
		 */
		int size() //////////////////////////////////////////////////////////////DONE - WORKING
        {
            return current_elements;
		}

		/**
		 *  Return true if hash table is empty, false otherwise
		 */
		bool empty() ////////////////////////////////////////////////////////////DONE - WORKING
        {
            int total = size();
            if(total == 0)
            {
                return(true);
            }
			    return(false);
		}

		/**
		 *  Calculates the current load factor for the hash
		 */
		float load_factor() /////////////////////////////////////////////////////DONE - WORKING
        {
                int current_size = size();
                int buckets = bucket_count();
                float load = (float)current_size/(float)buckets;

                if(load > 1)
                {
                    rehash();
                }

                return load;

		}

		/**
		 *  Returns current number of buckets (elements in vector)
		 */
		int bucket_count() ///////////////////////////////////////////////////////DONE - WORKING
        {
			return table.size();
		}

		/**
		 *  Deletes all elements in the hash
		 */
		void clear() ////////////////////////////////////////////////////////////DONE - WORKING
        {
			table.clear();
            current_elements = 0;
		}





        //ADDED HELPER FUNCTIONS - see rehash function
        //https://gist.github.com/alabombarda/f3944cd68dda390d25cb
        int nextPrime(int n)
        {
            int next = n;
            bool found = false;

            while (!found)
            {
                next++;
                if(isPrime(next))
                {
                    found = true;
                }
            }
            return next;
        }

        bool isPrime(int n)
        {
            for (int i = 2; i <= n/2; i++)
            {
                if(n % i == 0)
                {
                    return false;
                }
            }
            return true;
        }



        //MORE ADDED FUNCTIONS - see dictionary.h parseLine function
        void printMax(int max)
        {

            /*
            int count = 0;
            while (count <= max)
            {
                if(table[count].size() != 0) //check bucket
                {
                    for (auto v : table[count]) //print out while there are items in array
                    {
                        cout << v.myword << endl;
                        count++;
                        if(count <= max) //break loop if max prints are obtained mid-array
                        {
                            break;
                        }
                    }
                }
            }
            cout << max << " items have been printed out." << endl;
            */

        }

        void printRandom() //only getting one random number, keeps on repeating
        {


            srand(time(NULL));
            int random = rand();
            cout << random << endl;
            int hash = random % table.size();


            while(table[hash].empty()) //while random index has an empty bucket
            {
                random = rand();
                hash = random % table.size();
            }
            //after while breaks - found bucket that has stuff in it
            auto whichList = table[hash];
            random = rand() % whichList.size();
            list<Word>::iterator it = whichList.begin();
            std::advance(it, random);

            //giving me a lot of weird symbols
            cout << "Random Word - " << (*it).myword << ": " << (*it).definition << endl;

        }

};


#endif
