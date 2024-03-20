#include <iostream>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <cmath>    // for math operations

using namespace std;

// Structure to represent a data point
struct Point 
{
    double x;
    double y;
};

// Function to calculate Euclidean distance between two points
double calculateDistance(Point p1, Point p2) 
{
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

// Function to assign each point to the nearest centroid
void assignPointsToCentroids(const vector<Point>& points, const vector<Point>& centroids, vector<int>& assignments) 
{
    // Iterate through each data point
    for (size_t i = 0; i < points.size(); ++i) 
    {
        double minDist = numeric_limits<double>::max(); // Initialize minimum distance to maximum value
        int closestCentroid = -1; // Initialize index of the closest centroid to an invalid value

        // Iterate through each centroid to find the nearest one
        for (size_t j = 0; j < centroids.size(); ++j) 
        {
            double dist = calculateDistance(points[i], centroids[j]); // Calculate distance between point and centroid
            if (dist < minDist) 
            { // Check if current distance is smaller than minimum distance
                minDist = dist; // Update minimum distance
                closestCentroid = j; // Update index of closest centroid
            }
        }

        assignments[i] = closestCentroid; // Assign the point to the nearest centroid
    }
}

// Function to update centroids based on the assigned points
void updateCentroids(const vector<Point>& points, const vector<int>& assignments, vector<Point>& centroids) 
{
    vector<int> clusterSizes(centroids.size(), 0); // Initialize vector to store cluster sizes
    vector<Point> newCentroids(centroids.size(), {0.0, 0.0}); // Initialize vector to store new centroids

    // Iterate through each data point
    for (size_t i = 0; i < points.size(); ++i) 
    {
        int cluster = assignments[i]; // Get the cluster assignment for the point
        newCentroids[cluster].x += points[i].x; // Add the x-coordinate of the point to the corresponding cluster centroid
        newCentroids[cluster].y += points[i].y; // Add the y-coordinate of the point to the corresponding cluster centroid
        clusterSizes[cluster]++; // Increment the size of the cluster
    }

    // Calculate the mean of each cluster to update the centroids
    for (size_t i = 0; i < centroids.size(); ++i) 
    {
        if (clusterSizes[i] > 0) 
        { // Check if the cluster has assigned points
            centroids[i].x = newCentroids[i].x / clusterSizes[i]; // Update the x-coordinate of the centroid
            centroids[i].y = newCentroids[i].y / clusterSizes[i]; // Update the y-coordinate of the centroid
        }
    }
}

// Function to perform K-means clustering
vector<Point> kMeans(const vector<Point>& points, int k, int maxIterations) 
{
    vector<Point> centroids(k); // Initialize centroids vector
    vector<int> assignments(points.size()); // Initialize assignments vector

    // Initialize centroids randomly
    srand(time(nullptr));
    for (int i = 0; i < k; ++i) 
    {
        int index = rand() % points.size(); // Randomly select an index from the points
        centroids[i] = points[index]; // Set centroid to the randomly selected point
    }

    // Perform iterations
    for (int iter = 0; iter < maxIterations; ++iter) 
    {
        assignPointsToCentroids(points, centroids, assignments); // Assign each point to the nearest centroid
        updateCentroids(points, assignments, centroids); // Update centroids based on the assigned points
    }

    return centroids; // Return the final centroids
}

int main() {
    // Sample data points
    vector<Point> points = {{1.0, 2.0}, {2.0, 3.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0},
                        {1000.0, 1001.0}, {1001.0, 1002.0}, {1002.0, 1003.0}, {1004.0, 1005.0}, {1006.0, 1007.0}};

    // Number of clusters
    int k = 500;

    // Maximum number of iterations
    int maxIterations = 1000;

    // Perform K-means clustering
    vector<Point> centroids = kMeans(points, k, maxIterations);

    // Print centroids
    cout << "Centroids:" << endl;
    for (const auto& centroid : centroids) 
    {
        cout << "(" << centroid.x << ", " << centroid.y << ")" << endl;
    }

    return 0;
}
