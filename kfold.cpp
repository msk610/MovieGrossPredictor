//
//  kfold.cpp
//  MovieGross
//
//  Created by MD Shihabul Kabir on 12/13/16.
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#include <stdio.h>
#include "kfold.h"
#include <math.h>

using namespace std;
using namespace MovieData;
using namespace KnearestAlgo;
using namespace PerceptronAlgo;

namespace KfoldValidation {
    //function to do 2 fold cross validation and return the best model for knn
    Knn bestKNN(vector<Movie>train){
        //initialize where to begin and size of the sample chunk
        int sampleSize = train.size()/2;
        //do the fold 4 times and find the best model
        vector<Knn>models;
        int bestIndex = 0;
        float bestError = INT_MAX;
        int current = 0, last = sampleSize;
        for(int i =0; i < 2; ++i){
            //split of training and testing
            vector<Movie>newTesting;
            vector<Movie>newTraining;
            for(int j =current; j < last; ++j){
                if(j < train.size()) newTesting.push_back(train[j]);
            }
            for(int y =0; y < train.size(); ++y){
                if(y<current || y > last) newTraining.push_back(train[y]);
            }
            current += sampleSize;
            last += sampleSize;
            
            //make a model
            Knn model = Knn(newTraining);
            models.push_back(model);
            //test the model
            float errPercent=0, count =0, avgError = 0;
            for(Movie m : newTesting){
                float expected = model.predict(m);
                float actual = m[GROSS];
                float difference = fabsf(expected - actual);
                errPercent += (difference/expected);
                ++count;
            }
            if(count == 0) avgError = INT_MAX;
            else avgError = errPercent/count;
            if(avgError < bestError){
                bestError = avgError;
                bestIndex = i;
            }
        }
        return models[bestIndex];
    }
    
    //function to do 4 fold cross validation and return the best model for knn
    Perceptron bestPerceptron(vector<Movie>train){
        //initialize where to begin and size of the sample chunk
        int sampleSize = train.size()/4;
        //do the fold 4 times and find the best model
        vector<Perceptron>models;
        int bestIndex = 0;
        float bestError = INT_MAX;
        int current = 0, last = sampleSize;
        for(int i =0; i < 4; ++i){
            //split of training and testing
            vector<Movie>newTesting;
            vector<Movie>newTraining;
            for(int j =current; j < last; ++j){
                if(j < train.size()) newTesting.push_back(train[j]);
            }
            for(int y =0; y < train.size(); ++y){
                if(y<current || y > last) newTraining.push_back(train[y]);
            }
            current += sampleSize;
            last += sampleSize;
            
            //make a model
            Perceptron model = Perceptron(newTraining,.5);
            for(int i =0; i < 20; ++i){
                model.train();
            }
            models.push_back(model);
            //test the model
            float errPercent=0, count =0, avgError = 0;
            for(Movie m : newTesting){
                float expected = model.predict(m);
                float actual = m[GROSS];
                float difference = fabsf(expected - actual);
                errPercent += (difference/expected);
                ++count;
            }
            if(count == 0) avgError = INT_MAX;
            else avgError = errPercent/count;
            if(avgError < bestError){
                bestError = avgError;
                bestIndex = i;
            }
        }
        return models[bestIndex];
    }
}
