//
//  main.c
//  Ex4
//
//  Created by Ofir Rubin on 27/12/2021.
//

#include "GraphAlgo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

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

double getNum(char *lastChar){
    char* chrs = calloc(1, sizeof(double) + 1); // At the maximum, each will represent a (double) number
    int ptr = 0;
    if (isdigit(*lastChar))
        chrs[ptr] = (*lastChar);
    else
        ptr --;
    do{
        chrs[++ptr] = getchar();
    }
    while (ptr < sizeof(double) && (isdigit(chrs[ptr]) || chrs[ptr] == '.'));
    *lastChar = chrs[ptr];
    chrs[ptr] = 0;
    double n = atof(chrs);
    n = truncf(n * 1000.0) / 1000.0; // Ignoring everything after the 3th of the dot.
    free(chrs);
    return n;
}

char edgesInput(Node* n, char c){
    return '\0';
}

int main() {
    Graph* g = NULL;
    char command = getchar();
    char c;
    while (command == 'A' || command == 'B' || command == 'C' || command == 'D' || command == 'T'){ // T is internal test
        c = getchar(); // Skip the current char (suppose to be space)
        if (command == 'A'){
            double nodeID = getNum(&c);
            if (g != NULL)
                freeGraph(g);
            g = createGraph();
            addNode(g, nodeID, 0);
            do{
                c = getchar();
                double dest = getNum(&c);
                double weight = getNum(&c);
                addEdge(g, nodeID, dest, weight);
            }while(c == ' ');
            printGraph(g);
            printf("\n");
        }
        else if (command == 'B'){
            double id_ = getNum(&c);
            if(g == NULL)
                g = createGraph();
            Node* n = getNode(g, id_);
            if (n != NULL)
                removeNodeEdges(n); // Clear node edges if not exists
            else
                n = addNode(g, id_, 0); // Create node if not exists
            
            c = getchar();
            while (isdigit(c) || c == ' '){ // Otherwise we finished and c is the next command.
                double dest = getNum(&c);
                double weight = getNum(&c);
                addEdgeFrom(n, dest, weight); // We already have the node pointer so we can add it directly.
            }
            printGraph(g);
        }
        else if (command == 'C'){
            
            c = getchar();
        }
        else if (command == 'D')
        {
            double id_ = getNum(&c);
            removeNode(g, id_);
            // printf("removed node %f\n", id_);
            //c = getchar();
        }
        else if (command == 'T'){
            test();
            c = getchar();
        }
        else
            return 0;
        while (c == ' ' || c == '\n')
            c = getchar();
        command = c; //getchar();
    }
    if (g != NULL)
        freeGraph(g);
    return 0;
}
