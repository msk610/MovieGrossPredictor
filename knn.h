//
//  knn.h
//  MovieGross
//
//
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#ifndef knn_h
#define knn_h

#include "movie.h"
#include <vector>

//K-Nearest Neighbor Algorithm
namespace KnearestAlgo {
    
    //Data structure to process knn algorithm
    class Knn{
        
    private:
        //Member to store training set
        std::vector<MovieData::Movie>trainingSet;
        
    public:
        //constructor
        Knn(std::vector<MovieData::Movie>&train);
        
        //method to predict approximate movie gross
        float predict(MovieData::Movie& aMovie);
    };
    
    
}



#endif /* knn_h */
