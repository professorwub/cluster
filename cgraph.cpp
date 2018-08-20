#include "cgraph.h"

Cgraph::Cgraph(int n) : numNodes(n), cgraph(new Cnode[n])
{
    for (int obs = 0; obs < numNodes; obs++)
    {
        cgraph[obs].numNeighbors = 0;
        cgraph[obs].parent = 0;
        cgraph[obs].clusterNo = 0;
        cgraph[obs].neighbors.clear();
    }
}

void Cgraph::addNeighbor(int obs1, int obs2)
{
    cgraph[obs1].neighbors.push_front(obs2);
    cgraph[obs2].neighbors.push_front(obs1);
    cgraph[obs1].numNeighbors++;
    cgraph[obs2].numNeighbors++;
}

int Cgraph::cluster()
{
    // Determine parent nodes and identify orphans as cluster centers
    int numClusters = 0;
    for (int obs = 0; obs < numNodes; obs++)
    {
        int nmax = cgraph[obs].numNeighbors;
        int pnode = obs;
        for (int& nbr : cgraph[obs].neighbors)
            if (cgraph[nbr].numNeighbors > nmax || ((cgraph[nbr].numNeighbors == nmax) && (nbr > pnode)))
            {
                nmax = cgraph[nbr].numNeighbors;
                pnode = nbr;
            }
        cgraph[obs].parent = pnode;
        if (pnode == obs) // orphan defines a new cluster
        {
            numClusters++;
            cgraph[obs].clusterNo = numClusters;
        }
    }
    // Assign non-orphan nodes to clusters recursively
    for (int obs = 0; obs < numNodes; obs++)
    {
        int pnode = obs;
        while (cgraph[pnode].clusterNo == 0)
            pnode = cgraph[pnode].parent;
        cgraph[obs].clusterNo = cgraph[pnode].clusterNo;
    }
    return numClusters;
}
