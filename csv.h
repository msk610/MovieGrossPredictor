//
//  csv.h
//  MovieGross
//
//
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#ifndef csv_h
#define csv_h

#include <vector>
#include <fstream>

//CSV File Processor
namespace CsvProc {
    //Data Structure to process inputted csv file
    class Csv{
        //members
        std::vector<std::vector<float>>matrix;
    public:
        //global members for MAX and MIN of Data
        std::vector<float>MAX,MIN;
        
        //constructor
        Csv(std::ifstream& csv,int columns);
        
        //method to return the data matrix
        std::vector<std::vector<float>>getDataMatrix();
        
    };
}


#endif /* csv_h */
