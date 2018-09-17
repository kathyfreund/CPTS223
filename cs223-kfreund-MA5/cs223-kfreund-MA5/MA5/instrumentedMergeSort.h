/***************************************************************************
 *
 *  Sorting algorithms and counting work - Merge sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented mergesort
 *
 */

#ifndef __INSTRUMENTEDMS_H
#define __INSTRUMENTEDMS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;



void merge(vector<int> & a, vector<int> & tmpArray, int leftPos, int rightPos, int rightEnd, SortStats & stats)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;


    while(leftPos <= leftEnd && rightPos <= rightEnd)
    {
        if(a[leftPos] <= a[rightPos])
        {
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
            stats.moves++;
        }
        else
        {
            tmpArray[tmpPos++] = std::move(a[rightPos++]);
            stats.moves++;
        }
        stats.compares++;
    }
    while(leftPos <= leftEnd)
    {
        tmpArray[tmpPos++] = std::move(a[leftPos++]);
        stats.moves++;
    }
    while(rightPos <= rightEnd)
    {
        tmpArray[tmpPos++] = std::move(a[rightPos++]);
        stats.moves++;
    }
    for(int i = 0; i < numElements; ++i, --rightEnd)
    {
        a[rightEnd] = std::move(tmpArray[rightEnd]);
        stats.moves++;
    }
}


void mergeSort(vector<int> & a, vector<int> & tmpArray, int left, int right, SortStats & stats)
{
    if(left < right) //should always be right
    {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center, stats);
        mergeSort(a, tmpArray, center + 1, right, stats);
        merge(a, tmpArray, left, center + 1, right, stats);
    }


}



void instrumentedMergeSort( vector<int> & a, SortStats & stats )
{
    clock_t time_begin = clock();       // Grab presort time


    // MA TODO: Implement Merge Sort plus logging compares and moves/swaps
    vector<int> tmpArray(a.size());
    mergeSort(a, tmpArray, 0, a.size() - 1, stats);

    clock_t time_end = clock();         // Grab time when sort complete
    stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}


#endif
