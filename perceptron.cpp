//
//  perceptron.cpp
//  MovieGross
//
//
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#include <stdio.h>
#include "movie.h"
#include "perceptron.h"
#include "math.h"

using namespace std;
using namespace MovieData;

//Perceptron Namespace
namespace PerceptronAlgo {
    
    //constructor
    Perceptron::Perceptron(vector<Movie>&train,float rate){
        //initialize members
        learningRate = rate;
        for(int i = 0; i < 24; ++i){
            //set weights as 1 to begin
            weights.push_back(1);
        }
        trainingSet = train;
    }
    
    //method to train perceptron
    void Perceptron::train(){
        //go through training set
        for(Movie& c : trainingSet){
            float value = 0.0;
            //go through each attribute
            for(int i = 0; i < 24; ++i){
                if(i != GROSS) value += weights[i]*c[i];
            }
            //calculate the error
            float error = c[GROSS]-value;
            
            //update the weights
            for(int i = 0; i < 24; ++i){
                if(i != GROSS) weights[i] = weights[i]+(learningRate*error*c[i]);
            }
        }
        //update the learning rate
        updateLearningRate();
    }
    
    //method to predict whether a county voted a democrat or republican
    float Perceptron::predict(Movie &aMovie){
        float value = 0.0;
        //go through each attribute and get the value
        for(int i = 0; i < 24; ++i){
            if(i != GROSS) value += weights[i]*aMovie[i];
        }
        //return value
        return value;
    }
    
    //method to lower the learning rate after going through the data set once
    void Perceptron::updateLearningRate(){
        //make learning rate 1/10 the previous
        learningRate /= 10;
    }
}

