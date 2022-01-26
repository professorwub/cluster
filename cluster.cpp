#include <vector>

int cluster(const std::vector<std::vector<double>>& data, double radius, std::vector<unsigned>& clusterID, std::vector<unsigned>& parent)
{
    // Get some convenience values
    int numObs = data.size();
    int numAtr = data[0].size();
    double radius2 = radius * radius;

    // Construct neighbor array
    std::vector<std::vector<unsigned>> neighbors;
    neighbors.resize(numObs);
    for (auto obs1 = 1; obs1 < numObs; obs1++)
        for (auto obs2 = 0; obs2 < obs1; obs2++)
        {
            double distance = 0.0;
            for (auto atr = 0; atr < numAtr; atr++)
                distance += (data[obs1][atr] - data[obs2][atr]) * (data[obs1][atr] - data[obs2][atr]);
            if (distance <= radius2)
            {
                neighbors[obs1].push_back(obs2);
                neighbors[obs2].push_back(obs1);
            }
        }

    // Calculate degree of each node (for convenience)
    std::vector<int> degree;
    degree.resize(numObs, 0);
    for (auto obs = 0; obs < numObs; obs++)
        degree[obs] = neighbors[obs].size();

    // Initialize cluster IDs
    clusterID.resize(numObs, 0);
    int numClusters = 0;

    // Initialize parents
    parent.resize(numObs);
    for (auto obs = 0; obs < numObs; obs++)
        parent[obs] = obs; // start out as orphan

    // Determine parent for each observation
    for (auto obs = 0; obs < numObs; obs++) 
    {
        // Find neighbor with most neighbors
        for (auto nbr : neighbors[obs])
        {
            if (degree[nbr] > degree[parent[obs]] || (degree[nbr] == degree[parent[obs]] && nbr > parent[obs]))
                parent[obs] = nbr;
        }
        // Check for orphan
        if (parent[obs] == obs)
            clusterID[obs] = ++numClusters; // new cluster
    }

    // Finish clustering recursively
    for (auto obs = 0; obs < numObs; obs++)
    {
        auto obs1 = obs;
        while (clusterID[obs1] == 0)
            obs1 = parent[obs1];
        clusterID[obs] = clusterID[obs1];
    }
    return numClusters;
}