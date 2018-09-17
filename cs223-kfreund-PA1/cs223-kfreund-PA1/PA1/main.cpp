/*
 * Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations
 * Now also doing testing & height calculations
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 *  * Also doing height calculations
 *
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
#include <cstring>
#include "BST.h"
#include "TestData.h"
using namespace std;

/*
 *  Interface to run all tests if --test is passed on command line
 */
void runTests() {
    cout << " [x] Running tests. " << endl;
    TestData *testing = new TestData();         // Create object with testing data and interfaces

  BST<int> *bst_test = new BST<int>;

    /* Should make a tree like this:
              10
         5          14
     1      7           17
                            19
                          18
   */
    int testval = testing->get_next_minitest();
    while( testval >= 0 ){
        bst_test->add( testval );
        testval = testing->get_next_minitest();
    }
    cout << " [x] Should print out in pre order: 10 5 1 7 14 17 19 18 " << endl;
  cout << " [x] Resulting print out test:      ";
    bst_test->printPreOrder();
  cout << endl;

    cout << " [x] Should print a tree height of  : 5" << endl;
  cout << " [x] Currently calculating height of: ";
  cout << bst_test->height();
  cout << endl;
}


/*
 * Generate the CSV file for the project output here
 */
void genCSV() {
    cout << " [x] Generating CSV output file. " << endl;
    //cout << " [!!!] UNIMPLEMENTED - Need to generate the CSV file based on the tree height growth." << endl;

    /*  Sample of how to use the TestData structure for getting the test data sets
    int sorted = testing->get_next_sorted();  
    while(sorted >= 0){
        bst_sorted->add( sorted );
        sorted = testing->get_next_sorted();
    }
    cout << "Sorted height: " << bst_sorted->height() << endl;
  */

    // make a file: OutputData-BST.csv
    ofstream csv_file;
    csv_file.open ("OutputData-BST.csv");

    csv_file << "N, log_2(N), Sorted, Balanced, Scrambled #0, Scrambled #1, Scrambled #2, Scrambled #3, Scrambled #4 \n";
    //csv_file << "0, 0, 0, 0, 0, 0, 0, 0, 0 \n"; //first round

        // make 7 trees (sorted, balanced, scrambled[0..4])
        BST<int> *bst_sorted = new BST<int>, *bst_balanced = new BST<int>, *bst_scram0 = new BST<int>,
        *bst_scram1 = new BST<int>, *bst_scram2 = new BST<int>, *bst_scram3 = new BST<int>, *bst_scram4 = new BST<int>;

        int set0 = 0, set1 = 1, set2 = 2, set3 = 3, set4 = 4;
        TestData *testing = new TestData();

        int node_count = 0;
        double log_2 = 0;

        int sorted = testing->get_next_sorted();
        int balanced = testing->get_next_balanced();
        int scram0 = testing->get_next_scrambled(set0);
        int scram1 = testing->get_next_scrambled(set1);
        int scram2 = testing->get_next_scrambled(set2);
        int scram3 = testing->get_next_scrambled(set3);
        int scram4 = testing->get_next_scrambled(set4);

        // fill trees with data from TestData 

        //  -- as you fill, get the heights and output to CSV file: log_2 N, height sorted, height balanced, height scrambled[0..4]
        //  -- fill until the get_next_* functions return -1

        //while (any one of these still have stuff to print)
        while ((sorted >= 0) || (balanced >= 0) || (scram0 >= 0) || (scram1 >= 0) || (scram2 >= 0) || (scram3 >= 0) || (scram4 >= 0))
        {

            csv_file << node_count++ << ", "; //******************Node

            log_2 = log2(node_count);
            csv_file << log_2 << ", "; //**************************Log_2


            if (sorted >= 0) //********************************Sorted
            {   

                bst_sorted->add(sorted);
                sorted = testing->get_next_sorted();
                csv_file << bst_sorted->height();
            }
            //else 
            //{
                csv_file << ", ";

            //}

            if (balanced >= 0) //************************Balanced
            {
                bst_balanced->add(balanced);
                balanced = testing->get_next_balanced();
                csv_file << bst_balanced->height();
            }
            //else 
            //{
                csv_file << ", ";

            //}

            if (scram0 >= 0) //************************Scrambled 0
            {
                bst_scram0->add(scram0);
                scram0 = testing->get_next_scrambled(set0);
                csv_file << bst_scram0->height();
            }
            //else 
            //{
                csv_file << ", ";
               
            //}

            if (scram1 >= 0) //************************Scrambled 1
            {
                bst_scram1->add(scram1);
                scram1 = testing->get_next_scrambled(set1);
                csv_file << bst_scram1->height();
            }
            //else 
            //{
                csv_file << ", ";
            //}

            if (scram2 >= 0) //*************************Scrambled 2
            {
                bst_scram2->add(scram2);
                scram2 = testing->get_next_scrambled(set2);
                csv_file << bst_scram2->height();
            }
            //else 
            //{
                csv_file << ", ";
            //}

            if (scram3 >= 0) //***************************Scrambled 3
            {
                bst_scram3->add(scram3);
                scram3 = testing->get_next_scrambled(set3);
                csv_file << bst_scram3->height();
            }
            //else 
            //{
                csv_file << ", ";
            //}

            if (scram4 >= 0) //***************************Scrambled 4
            {
                bst_scram4->add(scram4);
                scram4 = testing->get_next_scrambled(set4);
                csv_file << bst_scram4->height();
            }
            //else 
            //{
                csv_file << ", ";

            //}



            csv_file << endl;

        }

        cout << "BREAKPOINT - LOOP COMPLETED SUCCESSFULLY" << endl;


        csv_file.close();
}


/*
 *   Main function for execution
 */
int main( int argc, char* argv[] ) {
    if( argc > 1 && !strcmp(argv[1], "--test") )
    {
        cout << " [x] Program in test mode, doing simple tests. " << endl;
        runTests();  // testing should just do a simple tree insert set and search
    }
    else
    {
        cout << " [x] Program built and running in full CSV generation mode. " << endl;
        genCSV();
    }
    return 0;
}