#include "graph.h"

void read_graph(FILE* file, struct graph* g) {
    char line[256];
    int row = 0;

    while (fgets(line, sizeof(line), file)) {
        int col = 0;
        char* token = strtok(line, " ");
        while (token) {
            int value = atoi(token);
            g->nodes[row][col++] = value;
            if (col-1 <= row) {
                g->nodes[col-1][row] = value;
            }
            token = strtok(NULL, " ");
        }
        row++;
    }
    g->num_nodes = row;
}

void write_dot(FILE* file, struct graph* g) {
    fprintf(file, "digraph G {\n");
    for (int i = 0; i < g->num_nodes; i++) {
        for (int j = i; j < g->num_nodes; j++) {
            if (g->nodes[i][j]) {
                fprintf(file, "  %d -> %d;\n", i, j);
            }
        }
    }
    fprintf(file, "}\n");
}


void generate_graph(unsigned long long n, unsigned long long e, bool adjacency, bool incidence) {
    struct graph g = {0};
    int** matrix;
    unsigned long long m;
    if (adjacency) {
        matrix = (int**) malloc(n * sizeof(int*));
        for (unsigned long long i = 0; i < n; i++) {
            matrix[i] = (int*) calloc(n, sizeof(int));
        }
        m = e;
    }
    else {
        matrix = (int**) malloc(n * sizeof(int*));
        for (unsigned long long i = 0; i < n; i++) {
            matrix[i] = (int*) calloc(e, sizeof(int));
        }
        m = e;
    }

    srand(time(NULL));
    unsigned long long counter = 0;
    while (counter < e) {
        unsigned long long i = rand() % n;
        unsigned long long j = rand() % n;
        if (i == j) {
            if (adjacency) {
                if (matrix[i][j] == 0) {
                    matrix[i][j] = 1;
                    counter++;
                }
            }
            else {
                if (counter < m) {
                    matrix[i][counter] = 1;
                    matrix[j][counter] = 1;
                    counter++;
                }
            }
        }
        else if (!adjacency && (counter + 1) < m) {
            if (matrix[i][counter] == 0 && matrix[j][counter] == 0) {
                matrix[i][counter] = 1;
                matrix[j][counter] = 1;
                counter += 2;
            }
        }
        else if (adjacency) {
            if (matrix[i][j] == 0 && matrix[j][i] == 0) {
                matrix[i][j] = 1;
                matrix[j][i] = 1;
                counter++;
            }
        }
    }
    if (adjacency) {
        write_matrix_to_file(matrix, n, n, "adjacency_matrix.txt");
        FILE* file = fopen("adjacency_matrix.txt", "r");
        read_graph(file, &g);
        fclose(file);
        file = fopen("graph.dot", "w");
        if (file == NULL) {
            fprintf(stderr, "Error. Unable to open file.\n");
            exit(1);
        }
        write_dot(file, &g);
        fclose(file);
        system("dot -Tpng graph.dot -o graph.png");
    }
    if (incidence) {
        write_matrix_to_file(matrix, n, m, "incidence_matrix.txt");
        FILE *fp;
        FILE *fp1;
        int vertices = 0, edges = -1;
        fp=fopen("incidence_matrix.txt","r");
        fp1 = fopen("graph.dot", "w");
        fprintf(fp1,"digraph G {\n");
        if(fp==NULL)
        {
            printf("Error with opening file!");
            exit(0);
        }
        while (! feof(fp))
        {
            if (fgetc(fp) == '\n')
                vertices++;
        }
        fseek(fp, 0, 0);
        char buffer[BUFFER_SIZE];
        fgets(buffer, BUFFER_SIZE, fp);
        char *token = strtok(buffer, " ");
        while(token != NULL)
        {
            edges++;
            token = strtok(NULL, " ");
        }
        fseek(fp,0,0);
        int incidence_matrix[vertices][edges];
        int i, j;
        for (i = 0; i < vertices; i++) {
            for (j = 0; j < edges; j++) {
                fscanf(fp, "%d", &incidence_matrix[i][j]);
            }
            fscanf(fp, "\n");
        }
        for (j = 0; j < edges; j++) {
            int vertex1 = -1, vertex2 = -1;
            for (i = 0; i < vertices; i++) {
                if (incidence_matrix[i][j] == 1) {
                    if (vertex1 == -1) {
                        vertex1 = i + 1;
                    }
                    else {
                        vertex2 = i + 1;
                    }
                }
            }
            if (vertex1 != -1 && vertex2 != -1) {
                fprintf(fp1,"    %d -> %d\n", vertex1, vertex2);
            }
        }
        fprintf(fp1,"}");
        fclose(fp);
        fclose(fp1);
        system("dot -Tpng graph.dot -o graph.png");
    }
}

void write_matrix_to_file(int** matrix, unsigned long long n, unsigned long long m, char* file_path) {
    FILE *fp = fopen(file_path, "w");
    if (!fp) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    for (unsigned long long i = 0; i < n; i++) {
        for (unsigned long long j = 0; j < m; j++) {
            fprintf(fp, "%d ", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}
