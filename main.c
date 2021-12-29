//
//  main.c
//  Ex4
//
//  Created by Ofir Rubin on 27/12/2021.
//

#include "GraphAlgo.h"
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int test(void){
    Graph* g = createGraph();
    addNode(g, 0, 1);
    addNode(g, 1, 10);
    addNode(g, 2, 5);
    addNode(g, 3, 0);
    addNode(g, 4, 9);
    if (addEdge(g, 0, 2, 3) == True)
        printf("Edge added from 0 to 2...\n");
    addEdge(g, 0, 3, 10);
    if (addEdge(g, 2, 3, 4) == True)
        printf("Edge added from 2 to 3...\n");
    
    printf("\n");
    
    
    Node* s = shortestPath(g, 0, 3);
    Node* ptr = s;
    while(ptr != NULL){
        printf("%d ", ptr->id_);
        ptr = ptr -> next;
    }
    removeNodeEdges(s);
    free(s);
    
    double w = getShortestPathDist(g, 0, 3);
    printf("%f\n\n", w);
    printGraph(g);
    printf("\n\n\n");
    
    
    Node* tspList = createNode(0, 0);
    //addEdgeFrom(tspList, 1, 0);
    addEdgeFrom(tspList, 2, 0);
    addEdgeFrom(tspList, 3, 0);
    printf("%.2f\n", tsp_from(g, tspList, 0));
    removeNodeEdges(tspList);
    free(tspList);
    
    
    freeGraph(g);
    return 0;
}


int main() {
    char command = getchar();
    while (command == 'A' || command == 'B' || command == 'C' || command == 'T'){ // T is internal test
        if (command == 'A'){
        }
        else if (command == 'B'){
            
        }
        else if (command == 'C'){
            
        }
        else if (command == 'T'){
            test();
        }
        else
            return 0;
        
        command = getchar();
    }
    return 0;
}
