#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Function to calculate Euclidean distance between two points
double calculateDistance(vector<double>& point1, vector<double>& point2) 
{
    double distance = 0.0;
    for (size_t i = 0; i < point1.size(); ++i) 
    {
        distance += pow(point1[i] - point2[i], 2);
    }
    return sqrt(distance);
}

// Function to assign each point to its nearest centroid
void assignClusters(vector<vector<double>>& data, vector<vector<double>>& centroids, vector<int>& clusterAssignments) 
{
    for (size_t i = 0; i < data.size(); ++i) 
    {
        double minDistance = numeric_limits<double>::max();
        int nearestCentroid = 0;
        for (size_t j = 0; j < centroids.size(); ++j) 
        {
            double distance = calculateDistance(data[i], centroids[j]);
            if (distance < minDistance) 
            {
                minDistance = distance;
                nearestCentroid = j;
            }
        }
        clusterAssignments[i] = nearestCentroid;
    }
}

// Function to update centroids based on assigned clusters
void updateCentroids(vector<vector<double>>& data, vector<int>& clusterAssignments, vector<vector<double>>& centroids)
{
    vector<int> clusterCounts(centroids.size(), 0);
    vector<vector<double>> newCentroids(centroids.size(), vector<double>(data[0].size(), 0.0));

    // Sum up points assigned to each centroid
    for (size_t i = 0; i < data.size(); ++i) 
    {
        int cluster = clusterAssignments[i];
        for (size_t j = 0; j < data[i].size(); ++j) 
        {
            newCentroids[cluster][j] += data[i][j];
        }
        clusterCounts[cluster]++;
    }

    // Calculate new centroids by taking the average of points in each cluster
    for (size_t i = 0; i < centroids.size(); ++i) 
    {
        for (size_t j = 0; j < centroids[i].size(); ++j) 
        {
            if (clusterCounts[i] != 0) 
            {
                newCentroids[i][j] /= clusterCounts[i];
            }
        }
    }

    centroids = newCentroids;
}

// Main K-means function
vector<int> kMeans(vector<vector<double>>& data, int k) 
{
    // Randomly initialize centroids
    vector<vector<double>> centroids;
    for (int i = 0; i < k; ++i)
    {
        centroids.push_back(data[rand() % data.size()]);
    }

    vector<int> clusterAssignments(data.size(), 0);

    // Run iterations until convergence
    bool converged = false;
    while (!converged) 
    {
        // Assign points to nearest centroid
        assignClusters(data, centroids, clusterAssignments);

        // Update centroids
        std::vector<std::vector<double>> oldCentroids = centroids;
        updateCentroids(data, clusterAssignments, centroids);

        // Check for convergence
        converged = (oldCentroids == centroids);
    }

    return clusterAssignments;
}

int main() 
{
    // Sample data
    vector<vector<double>> data = 
    {
        {2.0, 3.0}, {2.0, 4.0}, {3.0, 5.0},
        {7.0, 5.0}, {8.0, 5.0}, {7.0, 4.0},
        {4.0, 1.0}, {3.0, 2.0}, {3.0, 1.0}
    };

    // Number of clusters
    int k = 2;

    // Perform K-means clustering
    vector<int> clusterAssignments = kMeans(data, k);

    // Output cluster assignments
    cout << "Cluster assignments:\n";
    for (size_t i = 0; i < data.size(); ++i) 
    {
        cout << "(" << data[i][0] << ", " << data[i][1] << ") -> Cluster " << clusterAssignments[i] << endl;
    }

    return 0;
}
