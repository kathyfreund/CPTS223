/***************************************************************************
 *
 *  Sorting algorithms and counting work - Insertion sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented insertionsort
 *
 */

#ifndef __INSTRUMENTEDIS_H
#define __INSTRUMENTEDIS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void instrumentedInsertionSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();           // Grab starting time before sort


	// MA TODO: implement insertion sort plus logging compares, moves/swaps
    for(int p = 1; p < a.size(); ++p)
    {
        int tmp = std::move(a[p]);
        int j;


        for(j = p; j > 0 && ++stats.compares && tmp < a[j - 1]; --j)
        {
            stats.moves++;
            a[j] = std::move(a[j-1]);

        }
        a[j] = std::move(tmp);
        
    }



	clock_t time_end = clock();             // Grab ending time after sort
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
