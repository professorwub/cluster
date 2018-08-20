#ifndef CGRAPH_H
#define CGRAPH_H

#include <forward_list>

class Cgraph
{
public:
    Cgraph(int);
    ~Cgraph() {delete[] cgraph;}

    int getParent(int obs) const {return cgraph[obs].parent;}
    int getClusterNo(int obs) const {return cgraph[obs].clusterNo;}

    void addNeighbor(int, int);
    int cluster();
private:
    int numNodes;
    struct Cnode
    {
        int numNeighbors;
        int parent;
        int clusterNo;
        std::forward_list<int> neighbors;
    } *cgraph;
};

#endif // CGRAPH_H
