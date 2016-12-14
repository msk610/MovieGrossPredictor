//
//  perceptron.h
//  MovieGross
//
//
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#ifndef perceptron_h
#define perceptron_h

#include "movie.h"
#include <vector>


//Perceptron Namespace
namespace PerceptronAlgo {
    
    //Data structure to process the perceptron algorithm
    class Perceptron{
        
    private:
        //Member to manage learning rate
        float learningRate;
        //Member to store weights
        std::vector<float>weights;
        //Member to store training data set
        std::vector<MovieData::Movie>trainingSet;
        
    public:
        //constructor
        Perceptron(std::vector<MovieData::Movie>&train,float rate);
        
        //method to train perceptron
        void train();
        
        //method to predict overall gross
        float predict(MovieData::Movie& aMovie);
        
        //method to update learning rate
        void updateLearningRate();
    };
    
    
}


#endif /* perceptron_h */
