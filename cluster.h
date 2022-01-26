#pragma once

#include <vector>

/// <summary>
/// Function to find clusters based on directed graph
/// 
/// Clustering algorithm based on directed graphs as described
/// in "A graph-theoretic approach to nonparametric cluster analysis"
/// by Koontz et al.in IEEE Trans.on Computers, September 1976.
/// </summary>
/// <param name="data">Matrix of observations (rows) and attributes (columns)</param>
/// <param name="radius">Distance threshold parameter</param>
/// <param name="clusterID">Vector to collect cluster IDs</param>
/// <param name="parent">Vector to collect parent node for graphing</param>
/// <returns>Number of clusters found</returns>
int cluster(const std::vector<std::vector<double>>& data, double radius, std::vector<unsigned>& clusterID, std::vector<unsigned>& parent);
