//
//  kfold.h
//  MovieGross
//
//
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#ifndef kfold_h
#define kfold_h

#include "movie.h"
#include <vector>
#include "knn.h"
#include "perceptron.h"

namespace KfoldValidation {
    //function to cross validate for KNN models
    KnearestAlgo::Knn bestKNN(std::vector<MovieData::Movie>train);
    //function to cross validate for Perceptron models
    PerceptronAlgo::Perceptron bestPerceptron(std::vector<MovieData::Movie>train);
}

#endif /* kfold_h */
