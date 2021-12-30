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

int main() {
    Graph* g = NULL;
    char command = getchar();
    char c;
    while (command == 'A' || command == 'B' || command == 'S' || command == 'D' || command == 'T'){
        c = getchar(); // Skip the current char (suppose to be space)
        if (command == 'A'){
            if (g != NULL)
                freeGraph(g);
            g = createGraph();
            int inputs = getNum(&c); // How many elements to receive
            while (inputs > 0){
                while (c == ' ' || c == 'n') // Ignore empty spaces
                    c = getchar();
                if (! isdigit(c)) break;
                double nodeID = getNum(&c);
                addNode(g, nodeID, 0);
                while(c == ' ')
                {
                    c = getchar();
                    if (! isdigit(c)) continue;
                    double dest = getNum(&c);
                    addNode(g, dest, 0);
                    double weight = getNum(&c);
                    addEdge(g, nodeID, dest, weight);
                }
                inputs --;
            }
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
                addNode(g, dest, 0);
                double weight = getNum(&c);
                addEdgeFrom(n, dest, weight); // We already have the node pointer so we can add it directly.
                c = getchar();
            }
        }
        else if (command == 'S'){
            double src = getNum(&c);
            double dest = getNum(&c);
            int d = getShortestPathDist(g, src, dest); // You can also save double and output double
            printf("Dijsktra shortest path: %d \n", d);
        }
        else if (command == 'D')
        {
            double id_ = getNum(&c);
            if (g != NULL)
                removeNode(g, id_);
        }
        else if (command == 'T'){
            int num = getNum(&c);
            num --;
            Node* tspList = createNode(getNum(&c), 0);
            while(num > 0){
                addEdgeFrom(tspList, getNum(&c), 0);
                num --;
            }
            int t = tsp(g, tspList); // You could also save and print as double
            printf("TSP shortest path: %d\n ", t);
            removeNodeEdges(tspList);
            free(tspList);
        }
        else
            return 0;
        while (c == ' ')
            c = getchar();
        command = c; //getchar();
    }
    if (g != NULL)
        freeGraph(g);
    return 0;
}
