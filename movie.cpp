//
//  movie.cpp
//  MovieGross
//
//  
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#include <stdio.h>

#include <stdio.h>
#include "movie.h"
#include <math.h>

using namespace std;
using namespace CsvProc;

//MovieData definitions
namespace MovieData{
    
    //constructor
    Movie::Movie(vector<float>data){
        attr = data;
    }
    //method to normalize the data
    void Movie::normalize(Csv&csv){
        //iterate and use normalizing formula
        for(int i = 0; i < attr.size(); ++i){
            attr[i] = (attr[i] - csv.MIN[i])/(csv.MAX[i]-csv.MIN[i]);
        }
    }
        
    //Operator to return attribute value
    float Movie::operator[](int index){
        return attr[index];
    }
    
    //Operator to return eucledian distance
    float Movie::operator-(Movie& aMovie){
        float dist = 0;
        for(int i = 0; i < attr.size(); ++i){
            if(i != GROSS) dist += powf(attr[i]-aMovie[i], 2);
        }
        return sqrtf(dist);
    }
    
    
    
    //Operator to return whether two Movies are the same
    bool Movie::operator==(Movie& aMovie){
        for(int i = 0; i < attr.size(); ++i){
            if(attr[i] != aMovie[i]) return false;
        }
        return true;
    }
    
    
}
