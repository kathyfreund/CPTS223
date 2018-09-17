/***************************************************************************
 *
 *  Sorting algorithms and counting work - Quicksort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented quicksort
 *
 */

#ifndef __INSTRUMENTEDQS_H
#define __INSTRUMENTEDQS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;



void actualSort(vector<int> & a, SortStats & stats)
{
    if(a.size() > 1)
    {
        vector<int> smaller;
        vector<int> same;
        vector<int> larger;

        auto chosenOne = a[a.size() / 2];

        for(auto & i : a)
        {
            if(i < chosenOne)
            {
                stats.compares++;
                stats.moves++;
                smaller.push_back(std::move(i));
            }
            else if(chosenOne < i)
            {
                stats.compares += 2;
                stats.moves++;
                larger.push_back(std::move(i));
            }
            else
            {
                stats.compares += 2;
                stats.moves++;
                same.push_back(std::move(i));
            }

        }

        actualSort(smaller, stats);
        actualSort(larger, stats);

        std::move(begin(smaller), end(smaller), begin(a));
        stats.moves += smaller.size();
        std::move(begin(same), end(same), begin(a) + smaller.size());
        stats.moves += same.size();
        std::move(begin(larger), end(larger), end(a) - larger.size());
        stats.moves += larger.size();
    }

}


void instrumentedQuickSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();       // Grab time before the sort


    // MA TODO: implement quicksort and track compares + moves
    actualSort(a, stats); //gets called recursively

	clock_t time_end = clock();         // Grab time after the sort
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
