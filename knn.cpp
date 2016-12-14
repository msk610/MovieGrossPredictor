//
//  knn.cpp
//  MovieGross
//
//  
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include "knn.h"
#include <math.h>
#include <iostream>

using namespace std;
using namespace MovieData;

//K-Nearest Neighbor Algorithm
namespace KnearestAlgo {
    
    //constructor
    Knn::Knn(vector<Movie>&train){
        trainingSet = train;
    }
    
    //method to predict approximate movie gross
    float Knn::predict(Movie& aMovie){
        
        //make a pair of distances and gross
        vector<pair<float, float>> gross;
        
        //go through and store each eucledian distances with its Movie
        for(Movie m: trainingSet){
            pair<float, float>p;
            p.first = m - aMovie;
            p.second = m[GROSS];
            gross.push_back(p);
        }
        
        //sort the vector
        sort(gross.begin(),gross.end());
        
        //count accumulate the gross of neighbors
        float total = 0;
        for(int i =0; i < 43; ++i){
            total += gross[i].second;
        }
        
        //conduct simple inflation calculations
        float avg = total/43;
        return avg;
    }
}

