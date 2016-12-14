//
//  main.cpp
//  MovieGross
//
//
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "csv.h"
#include "movie.h"
#include <string>
#include "knn.h"
#include "kmeans.h"
#include <math.h>
#include "perceptron.h"
#include "kfold.h"

using namespace std;
using namespace CsvProc;
using namespace MovieData;
using namespace KnearestAlgo;
using namespace KmeansCluster;
using namespace PerceptronAlgo;
using namespace KfoldValidation;



const string trainFile = "/Users/mdkabir/Documents/MovieGross/MovieGross/train_moviedata.csv";
const string testFile = "/Users/mdkabir/Documents/MovieGross/MovieGross/test_moviedata.csv";



//function to run a specific algorithm
void runAlgorithm(vector<Movie>&train,vector<Movie>&test,Csv&t1,Csv&t2){
    cout << "Movie Gross Predicter: " << endl;
   cout <<"========================================" << endl;
    cout << "Enter 1 to run K-NN algorithm" << endl;
     cout << "Enter 2 to run K-Means algorithm" << endl;
     cout << "Enter 3 to run Perceptron algorithm" << endl;
     cout <<"========================================" << endl;
    cout << "Press any numbers aside from 1,2,3 to exit..." << endl;
    cout <<"========================================" << endl;
    cout << endl;
    int algo;
    cin >> algo;
    
    switch (algo) {
        //option 1
        case 1:
        {
            chrono::high_resolution_clock::time_point time1 = chrono::high_resolution_clock::now();
            //K-Nearest-Neighbor Algorithm (validated)
            Knn knn = bestKNN(train); //2 Fold Cross Validated
            Knn knn2 = Knn(train);
    
            //loop through and predict the gross
            float errPercent=0, count =0, errP2 = 0;
            for(Movie& m : test){
                float expected = knn.predict(m);
                float exp2 = knn2.predict(m);
                
                float actual = m[GROSS];
                float difference = fabsf(expected - actual);
                float diff2 = fabsf(exp2 - actual);
                
                errPercent += (difference/expected);
                errP2 +=(diff2/exp2);
                ++count;
                
            }
            chrono::high_resolution_clock::time_point time2 = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>( time2 - time1 ).count();
            cout <<"========================================" << endl;
            cout << "K-NN 2 Fold Cross Validated Error: " << (errPercent/count)*100 << "%" << endl;
            cout << "K-NN Unvalidated Error: " << (errP2/count)*100 << "%" << endl;
            cout << "Average Runtime: " << duration/float(2) << " miliseconds" << endl;
            cout <<"========================================" << endl;
            
            break;
        }
        
        //option 2
        case 2:
        {
            chrono::high_resolution_clock::time_point time1 = chrono::high_resolution_clock::now();
            //K-Means Algorithm
            KMeans km = KMeans();
            //Intialize the set
            km.initialize(train);
            //Make the cluster
            km.cluster();
            //loop through and predict the gross
            float errPercent2=0, count2 =0;
            for(Movie& m : test){
                float expected = km.predict(m);
                float actual = m[GROSS];
                float difference = fabsf(expected - actual);
                errPercent2 += (difference/expected);
                ++count2;
            }
            chrono::high_resolution_clock::time_point time2 = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>( time2 - time1 ).count();
            cout <<"========================================" << endl;
            cout <<"K-Means Average Error: " << (errPercent2/count2)*100 << "%" << ", Approximate Runtime: " << duration << " milliseconds" << endl;
            cout <<"========================================" << endl;
            break;
        }
            
        //option 3
        case 3:
        {
            chrono::high_resolution_clock::time_point time1 = chrono::high_resolution_clock::now();
            //Perceptron Algorithm
            Perceptron neuron = bestPerceptron(train); //4 Fold Cross Validated
            Perceptron n2 = Perceptron(train,.5); //Unvalidated
            
            //train the perceptron
            for(int i  =0; i < 10; ++i){
                neuron.train();
                n2.train();
            }
            //go through and predict the gross
            float errPercent=0, count =0, ep2 = 0;
            for(Movie& m : test){
                float expected = neuron.predict(m);
                float en2 = n2.predict(m);
                float actual = m[GROSS];
                
                float difference = fabsf(expected - actual);
                float difn2 = fabsf(en2 - actual);
                errPercent += (difference/expected);
                ep2 += (difn2/expected);
                ++count;
                
            }
            chrono::high_resolution_clock::time_point time2 = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>( time2 - time1 ).count();
            cout <<"========================================" << endl;
            cout << "Perceptron 4 Fold Cross Validated Error: " << (errPercent/count)*100 << "%" << endl;
            cout << "Perceptron Unvalidated Error: " << (ep2/count)*100 << "%" << endl;
            cout << "Average Runtime: " << duration/float(2) << " miliseconds" << endl;
            cout <<"========================================" << endl;
            break;
        }
        default:
        {
            cout << "Exiting Program..." << endl;
            exit(-1);
            break;
        }
    }
}




int main(int argc, const char * argv[]) {
    // initialize matrices and vectors needed
    vector<vector<float>>train,test;
    vector<Movie>trainset,testset;
    
    //open the train file
    ifstream trainF(trainFile);
    //check if file path exits
    if(!trainF){
        cerr << "Couldn't find train file" << endl;
        exit(-20);
    }
    
    //open the test file
    ifstream testF(testFile);
    //check if file path exits
    if(!testF){
        cerr << "Couldn't find test file" << endl;
        exit(-20);
    }

    //process the train csv
    Csv trainCsv(trainF,24);
    train = trainCsv.getDataMatrix();
    
    //go through train matrix and make the movie objects
    for(int i = 0; i < train.size(); ++i){
        Movie movie = Movie(train[i]);
        movie.normalize(trainCsv);
        trainset.push_back(movie);
    }
    
    //process the test csv
    Csv testCsv(testF,24);
    test = testCsv.getDataMatrix();
    
    //go through train matrix and make the movie objects
    for(int i = 0; i < test.size(); ++i){
        Movie movie = Movie(test[i]);
        movie.normalize(testCsv);
        testset.push_back(movie);
    }
    
    while(true){
        runAlgorithm(trainset, testset, trainCsv, testCsv);
    }
    
    
    return 0;
}
