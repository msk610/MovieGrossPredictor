//
//  movie.h
//  MovieGross
//
//  
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#ifndef movie_h
#define movie_h

#include <vector>
#include "csv.h"

//Global constants
const int GROSS = 7;
const int YEAR = 19;

//namespace for movie object
namespace MovieData {
    //data structure to process movie data
    class Movie{
        //members
        std::vector<float>attr;
    public:
        //constructor
        Movie(std::vector<float>data);
        
        //method to normalize the data
        void normalize(CsvProc::Csv& csv);
        
        //Operator to return attribute value
        float operator[](int index);
        
        //Operator to return eucledian distance
        float operator-(Movie& aMovie);
        
        //Operator to return whether two Movies are the same
        bool operator==(Movie& aMovie);
        
    };
}




#endif /* movie_h */
