/*
* main.cpp
*
* COSC 051 Spring 2019
* Project #2
*
* Due on: February 26, 2019
* Author: jsk142
*
*
* In accordance with the class policies and Georgetown's
* Honor Code, I certify that, with the exception of the
* class resources and those items noted below, I have neither
* given nor received any assistance on this project.
*
* References not otherwise commented within the program source code.
* Note that you should not mention any help from the TAs, the professor,
* or any code taken from the class textbooks.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//Global constants

const string PROMPT_WELCOME = "\nWelcome to the BHMSI move cost calculator.";
const string PROMPT_FILE = "Please enter the full path and name of the input file:";
const string ERROR_FILE_OPEN = "ERROR opening input data file, please check name and path:";
const string SUCCESS_FILE_OPEN = "File succesfully opened for input:";
const string PROMPT_ERROR = "The program will now end, Goodbye.";
const string PROMPT_TEST = "TESTING: output of each row of the file:";
const string ERROR_MOVE_SOON = "ERROR: the move date is too soon after the estimate date";
const string ERROR_MOVE_LONG = "ERROR: the move date is too long after the estimate date"; 
const string ERROR_MOVE_TYPE = "ERROR: the move type is not valid";
const string ERROR_DISTANCE = "ERROR: the distance of this move is over the maximum allowed";
const string ERROR_WEIGHT_MIN = "ERROR: the weight of items moved is under the minimum allowed";
const string ERROR_WEIGHT_MAX = "ERROR: the weight of items moved is over the maximum allowed";
const string ERROR_PIANO = "ERROR: the number of pianos moved is over the maximum allowed";
const string ERROR_ORIGIN = "ERROR: the answer for stairs > 15 at origin is not valid";
const string ERROR_DESTINATION = "ERROR: the answer for stairs > 15 at destination is not valid";
const string ERROR_CONTACT = "Conctact customer to resolve issues:  ";
const string PROMPT_BYE = "Thank you for using the BHMSI move cost calculator (Bulk Data Version)";

const double PRICE_PER_POUND_FOR_PACKING_AND_LOADING_B = 0.065;   
const double PRICE_PER_POUND_FOR_PACKING_AND_LOADING_W = 0.256;
const double PRICE_PER_POUND_FOR_PACKING_AND_LOADING_C = 0.459;
const double PRICE_PER_POUND_PER_MILE_B = 0.0011;
const double PRICE_PER_POUND_PER_MILE_W = 0.0011;
const double PRICE_PER_POUND_PER_MILE_C = 0.0012;

const int PIANO_SURCHARGE_0 = 275;
const int PIANO_SURCHARGE_1 = 575;
const int PIANO_SURCHARGE_2 = 1075;
const int STAIRS_SURCHARGE = 132;

int main()
{  

   //Variables

   ifstream inFile;
   string fileName = "";
   string headings = "";
   string moveNumber = "";
   string nameAndEmail = "";
   
   char moveType, 
        originStairs,
        destinationStairs;
   char ch = '?';

   int orderYear,
       orderMonth,
       orderDay,
       moveYear,
       moveMonth,
       moveDay,
       moveDistance,
       minimumWeight,
       moveWeight,
       movePiano;
   int moveStairs = 0;
   int rowCount = 0;
   int errorCount = 0;
   int basicCount = 0;
   int wallCount = 0;
   int completeCount = 0;
   int distanceBTotal = 0;
   int distanceWTotal = 0;
   int distanceCTotal = 0;
   int weightBTotal = 0;
   int weightWTotal = 0;
   int weightCTotal = 0;

   double packingCost, 
          movingCost, 
          pianoCost, 
          stairsCost,
          totalCost;
   double costBTotal = 0;
   double costWTotal = 0;
   double costCTotal = 0;

   bool boolMove = true;
   bool boolDistance = true;

   cout << PROMPT_WELCOME << endl << endl; //Output brief greeting message
   cout << PROMPT_FILE << endl; //Output prompt for complete path and file name

   cin >> fileName;

   inFile.open( fileName.c_str () );

   if ( !inFile ) //If file fails to open, output error message
   {   cout << ERROR_FILE_OPEN << endl << fileName << endl;
       cout << PROMPT_ERROR << endl << endl;
   }
   else //If file succesfully opens, process data rows
   {   cout << SUCCESS_FILE_OPEN << endl << fileName << endl;
       
       getline( inFile, headings );
   
       cout << "heading row: " << endl << headings << endl << endl;
       cout << PROMPT_TEST << endl << endl << endl;
       cout << "   Order       Move    Move      Dist.    Weight   Number    Stairs   Move" 
            << "          Total" << endl;
       cout << "   Date        Date    Code    (miles)   (pounds)  Pianos    O    D   Number" 
            << "        Cost ($)" << endl;
       cout << "-----------------------------------------------------------------------------" 
            << "----------------" << endl;

       while ( inFile >> moveNumber >> orderYear >> ch >> orderMonth >> ch >> orderDay >> moveYear
               >> ch >> moveMonth >> ch >> moveDay >> moveType >> moveDistance >> moveWeight 
               >> movePiano >> originStairs >> destinationStairs 
               && getline( inFile, nameAndEmail ) )
       {
           rowCount++; 
           
           cout << setfill('0');
           cout << orderYear << "/" << setw(2) << orderMonth << "/" << setw(2) <<orderDay << "  ";
           cout << moveYear << "/" << setw(2) << moveMonth << "/" << setw(2) << moveDay << "  ";
           
           //Data validation
           //Output appropriate error messages

           if (moveDistance < 1)
           {   moveDistance = 1;
               minimumWeight = 1200;
           }

           else if (moveDistance >= 1 && moveDistance <= 600)
           {   minimumWeight = 1200;
           }

           else if (moveDistance > 600 && moveDistance <= 3200)
           {   minimumWeight = 2 * moveDistance;
           }

           else
           {   boolDistance = false;
           }

           if (movePiano < 0)
           {   movePiano = 0;
           }

           cout << setfill(' ');
           cout << moveType << setw(11) << moveDistance << setw(11) << moveWeight << setw(7) 
                << movePiano;
           cout << "       " << originStairs << "    " << destinationStairs;
 
           if (moveYear != orderYear)
           {   moveMonth += 12;
           }

           if (moveMonth - orderMonth < 2)
           {   cout << endl << "        " << ERROR_MOVE_SOON;
               boolMove = false;
           }
 
           if (moveMonth - orderMonth > 7)
           {   cout << endl << "        " << ERROR_MOVE_LONG;
               boolMove = false;
           }

           if (moveType != 'B' && moveType != 'b' && moveType != 'W' && moveType != 'w' 
               && moveType != 'C' && moveType != 'c')
           {   cout << endl << "        " << ERROR_MOVE_TYPE;
               boolMove = false;
           }

           if (!boolDistance)
           {   cout << endl << "        " << ERROR_DISTANCE;
               boolMove = false;
           }

           if (moveWeight < minimumWeight)
           {   cout << endl << "        " << ERROR_WEIGHT_MIN;
               boolMove = false;
           }

           if (moveWeight > 18000)
           {   cout << endl << "        " << ERROR_WEIGHT_MAX;
               boolMove = false;
           }

           if (movePiano > 3)
           {   cout << endl << "        " << ERROR_PIANO;
               boolMove = false;
           }

           if (originStairs != 'Y' && originStairs != 'y' && originStairs != 'N' 
               && originStairs != 'n')
           {   cout << endl << "        " << ERROR_ORIGIN;
               boolMove = false;
           }

           if (destinationStairs != 'Y' && destinationStairs != 'y' && destinationStairs != 'N' 
               && destinationStairs != 'n')
           {   cout << endl << "        " << ERROR_DESTINATION;
               boolMove = false;
           }

           //If record contains errors, output customer's name and email

           if (!boolMove) 
           {   cout << endl << "        " << ERROR_CONTACT << nameAndEmail << endl << endl;
               errorCount++; 
           }
             
           //If record is correct, output the move estimate number and the total cost of the move

           if (boolMove) 
           {   
               if (moveType == 'B' || moveType == 'b')
               {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_B * moveWeight;
                   movingCost = PRICE_PER_POUND_PER_MILE_B * moveWeight * moveDistance;
               } 

               if (moveType == 'W' || moveType == 'w')
               {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_W * moveWeight; 
                   movingCost = PRICE_PER_POUND_PER_MILE_W * moveWeight * moveDistance;
               } 

               if (moveType == 'C' || moveType == 'c')
               {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_C * moveWeight;
                   movingCost = PRICE_PER_POUND_PER_MILE_C * moveWeight * moveDistance;
               } 

               if (originStairs == 'Y' || originStairs == 'y')
               {   moveStairs += 1;
               }

               if (destinationStairs == 'Y' || destinationStairs == 'y')
               {   moveStairs += 1;
               }

               if (moveStairs == 0)
               {   pianoCost = movePiano * PIANO_SURCHARGE_0;
                   stairsCost = moveStairs * STAIRS_SURCHARGE;
               }
     
               if (moveStairs == 1)
               {   pianoCost = movePiano * PIANO_SURCHARGE_1;
                   stairsCost = moveStairs * STAIRS_SURCHARGE;
               }

               if (moveStairs == 2)
               {   pianoCost = movePiano * PIANO_SURCHARGE_2;
                   stairsCost = moveStairs * STAIRS_SURCHARGE;
               }
     
               totalCost = packingCost + movingCost + pianoCost + stairsCost;

               //Keep counters and running totals for each type of move

               if (moveType == 'B' || moveType == 'b')
               {   basicCount++;
                   distanceBTotal += moveDistance;
                   weightBTotal += moveWeight;
                   costBTotal += totalCost;
               } 

               if (moveType == 'W' || moveType == 'w')
               {   wallCount++;
                   distanceWTotal += moveDistance;
                   weightWTotal += moveWeight;
                   costWTotal += totalCost;
               }        

               if (moveType == 'C' || moveType == 'c')
               {   completeCount++;
                   distanceCTotal += moveDistance;
                   weightCTotal += moveWeight;
                   costCTotal += totalCost;
               }   

               cout << fixed << showpoint << setprecision(2);
               cout << "  " << moveNumber << setw(12) << totalCost << endl;
           }

           boolMove = true;
           boolDistance = true;
           moveStairs = 0;
       }

       //Output summary table
  
       cout << endl << endl << endl << "Total Records = " << rowCount;
       cout << "  Records with Errors = " << errorCount;
       cout << "  Records without Errors = " << (rowCount - errorCount) << endl << endl;
       cout << "                  " << "TOTALS (records without errors)" << endl << endl;
       cout << "       Type        Count    Distance     Weight        Cost" << endl;
       cout << "       ----------------------------------------------------------" << endl;
       cout << "       Basic" << setw(11) << basicCount << setw(12) << distanceBTotal 
            << setw(12) << weightBTotal << "   $" << setw(12) << costBTotal << endl;
       cout << "       Wall Pack" << setw(7) << wallCount << setw(12) << distanceWTotal 
            << setw(12) << weightWTotal << "   $" << setw(12) << costWTotal << endl;
       cout << "       Complete" << setw(8) << completeCount << setw(12) << distanceCTotal 
            << setw(12) << weightCTotal << "   $" << setw(12) << costCTotal << endl << endl;
       cout << PROMPT_BYE << endl << endl;

   }

   return 0;
}     
