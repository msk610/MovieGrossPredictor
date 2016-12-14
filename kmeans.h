//
//  kmeans.h
//  MovieGross
//
//
//  Copyright © 2016 ArsenKevinMD. All rights reserved.
//

#ifndef kmeans_h
#define kmeans_h

#include <vector>
#include "movie.h"

//K-Means Clustering Namespace
namespace KmeansCluster {
    //Data Structure to help K-Means Clustering
    class KMeans{
    private:
        //setup three clusters for the clustering and two for last centroids and current centroids
        std::vector<MovieData::Movie>cluster1,cluster2,cluster3,last,current,all;
        
    public:
        //method find the closest cluster to add
        void addToClosest(MovieData::Movie&aMovie);
        
        //method to initialize rand centroids and clusters
        void initialize(std::vector<MovieData::Movie> movies);
        
        //method to get the mean of a cluster
        std::vector<float> mean(std::vector<MovieData::Movie>&cluster);
        
        //method to get centroid closest to mean of cluster
        MovieData::Movie getCentroid(std::vector<MovieData::Movie>&cluster,std::vector<float> mean);
        
        //method to get the centroid of a cluster
        MovieData::Movie centroid(std::vector<MovieData::Movie>&movies);
        
        //method to setup centroids
        bool setupCentroids();
        
        //method to make the clusters
        void cluster();
        
        //method to get the distance from a point to rest of cluster
        float avgDistance(std::vector<MovieData::Movie>&cluster,int index);
        
        //method to find distance from cluster from a point
        float distanceFromCluster(MovieData::Movie&c,std::vector<MovieData::Movie>&cluster);
        
        //method to return silhoute value
        float silh(std::vector<MovieData::Movie>&a,std::vector<MovieData::Movie>&b,int index);
        
        //method to print the silhoute for each cluster
        void printSil();
        
        //method to predict movie gross
        float predict(MovieData::Movie aMovie);
        
        
    };
    
}



#endif /* kmeans_h */
