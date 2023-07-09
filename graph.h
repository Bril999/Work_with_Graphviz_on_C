#ifndef RK3
#define RK3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#define MAX_NODES 100
#define BUFFER_SIZE 1024

struct graph {
    int nodes[MAX_NODES][MAX_NODES];
    int num_nodes;
};

void generate_graph(unsigned long long n, unsigned long long e, bool adjacency, bool incidence);
void write_matrix_to_file(int** matrix, unsigned long long n, unsigned long long m, char* file_path);
void write_dot(FILE* file, struct graph* g);
void read_graph(FILE* file, struct graph* g);

#endif /*RK3*/