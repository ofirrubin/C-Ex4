//
//  GraphAlgo.h
//  Ex4
//
//  Created by Ofir Rubin on 29/12/2021.
//

#ifndef GraphAlgo_h
#define GraphAlgo_h

#include <stdio.h>
#include "Graph.h"


void printShortestPath(Graph* g, int src, int dest);
int getShortestPathDist(Graph* g, int src, int dest);
Node* shortestPath(Graph* g, int src, int dest);
double tsp_from(Graph* g, Node* nodes, int start_at);
double tsp(Graph* g, Node* nodes);
#endif /* GraphAlgo_h */

