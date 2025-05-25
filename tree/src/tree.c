#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEPTH 10
#define MAX 100

typedef struct _tree_t {
    int val;
    struct _tree_t *left;
    struct _tree_t *right;
} tree_t;

tree_t *make_tree()
{
    tree_t *root = malloc(sizeof(*root));
    if (!root) return NULL;

    root->left = NULL;
    root->right = NULL;
    return root;
}

void insert_tree(tree_t **root, int val)
{
    if (!(*root)) {
        *root = make_tree();
        (*root)->val = val;
    } else if (val < (*root)->val) {
        insert_tree(&((*root)->left), val);
    } else {
        insert_tree(&((*root)->right), val);
    }
}

void print_tree(tree_t *root, int depth)
{
    depth += 4;
    if (root) {
        print_tree(root->right, depth);
        for (int i = 4; i < depth; ++i) {
            printf(" ");
        }
        printf("%d\n", root->val);
        print_tree(root->left, depth);
    } else {
        for (int i = 4; i < depth; ++i) {
            printf(" ");
        }
        printf("NULL\n");
    }
}

void plot_tree(tree_t *root, FILE *f, int *count)
{
    if (root->left) {
        fprintf(f, "    %d -> %d;\n", root->val, root->left->val);
        plot_tree(root->left, f, count);
    } else {
        fprintf(f, "    null_%d [style=invis];\n", *count);
        fprintf(f, "    %d -> null_%d;\n", root->val, *count);
        *count += 1;
    }

    if (root->right) {
        fprintf(f, "    %d -> %d;\n", root->val, root->right->val);
        plot_tree(root->right, f, count);
    } else {
        fprintf(f, "    null_%d [style=invis];\n", *count);
        fprintf(f, "    %d -> null_%d;\n", root->val, *count);
        *count += 1;
    }
}

bool output(const char *flag)
{
    const char* o = "-o";
    const char* output = "--output";
    return strcmp(flag, o) == 0 || strcmp(flag, output) == 0;
}

void print_help()
{
    printf("USAGE:\n");
    printf("    tree -h, --help: prints this `help` message.\n");
    printf("    tree -p, --print: prints tree representation to STDOUT.\n");
    printf("    tree -o, --output <output_file.dot>: outputs tree representation to a dot file.\n");
}

void handle_flag_error(const char* msg)
{
    printf("ERROR: %s\n", msg);
    print_help();
    exit(69);
}

bool output_flag = false;
bool print_stdout = false;
char *output_file;

int main(int argc, char **argv)
{
    if (argc > 1) {
        char *flag = *(++argv);
        if (strcmp(flag, "-o") == 0 || strcmp(flag, "--output") == 0) {
            output_flag = true;
            output_file = *(++argv);
            if (output_file == NULL) handle_flag_error("Output file missing");
        } else if (strcmp(flag, "-p") == 0 || strcmp(flag, "--print") == 0) {
            print_stdout = true;
        } else if (strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0) {
            print_help();
            exit(0);
        } else {
            handle_flag_error("Unknown flag");
        }
    } else {
        print_help();
        exit(0);
    }

    srand(time(0));

    int n[DEPTH];
    int taken[MAX];

    int val = rand()%MAX;
    for (size_t i = 0; i < DEPTH; ++i) {
        taken[val] = 1;
        n[i] = val + 1;
        do {
            val = rand()%MAX;
        } while (taken[val] == 1);
    }

    tree_t *root = make_tree();
    assert(root != NULL);
    root->val = n[0];

    for (size_t i = 1; i < DEPTH; ++i) {
        insert_tree(&root, n[i]);
    }

    if (output_flag) {
        int count = 0;
        FILE *f = fopen(output_file, "w");
        fprintf(f, "digraph T {\n");
        plot_tree(root, f, &count);
        fprintf(f, "}\n");
        fclose(f);
    } else if (print_stdout) {
        int depth = 0;
        print_tree(root, depth);
    }

    return 0;
}
