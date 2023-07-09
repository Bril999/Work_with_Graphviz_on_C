#include "graph.h"

int main(int argc, char* argv[]) {
    unsigned long long n = 0, e = 0;
    bool adjacency = false, incidence = false;
    int opt;

    while ((opt = getopt(argc, argv, "n:e:ai")) != -1) {
        switch (opt) {
            case 'n':
                n = strtoull(optarg, NULL, 10);
                break;
            case 'e':
                e = strtoull(optarg, NULL, 10);
                break;
            case 'a':
                adjacency = true;
                break;
            case 'i':
                incidence = true;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s -n <value> -e <value> [-a] [-i]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (n == 0 || e == 0 || (!adjacency && !incidence)) {
        fprintf(stderr, "Usage: %s -n <value> -e <value> [-a] [-i]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    generate_graph(n, e, adjacency, incidence);

    return 0;
}