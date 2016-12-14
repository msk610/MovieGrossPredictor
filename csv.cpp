//
//  csv.cpp
//  MovieGross
//
//
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#include <stdio.h>
#include "csv.h"
#include <sstream>
#include <string>
#include <iostream>
#include <exception>

using namespace std;
//CSV Processor Definitions
namespace CsvProc {
    
    //constructor
    Csv::Csv(ifstream& csv,int columns){
        //initialize MIN and MAX matrices with dummy values
        for(int i = 0; i < columns; ++i){
            MIN.push_back(INT_MAX);
            MAX.push_back(INT_MIN);
        }
        //setup a line buffer
        string line;
        
        //while not EOF
        while (getline(csv,line)) {
            //make a new row
            vector<float>mtxRow;
            
            //process the line
            istringstream row(line);
            
            //setup column buffer and column count
            int mtxCol = 0;
            string column;
            
            //go through each column and append it to matrix row
            while(getline(row,column,',')){
                //convert the string to float
                float colVal;
                try{
                    colVal = stof(column);
                }
                catch(exception& e){
                    cerr << "Could not convert value: " << column << endl;
                    exit(-10);
                }
                //check for min and max
                if(MIN[mtxCol] > colVal) MIN[mtxCol] = colVal;
                if(MAX[mtxCol] < colVal) MAX[mtxCol] = colVal;
                
                //push the column value to the row and increment column
                ++mtxCol;
                mtxRow.push_back(colVal);
            }
            //add row to matrix
            matrix.push_back(mtxRow);
        }
    }
    
    //method to return the data matrix
    vector<vector<float>>Csv::getDataMatrix(){
        return matrix;
    }
    
}
