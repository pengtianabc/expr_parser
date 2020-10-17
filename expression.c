#include "expression.h"

static node_t* alloc_node()
{
    node_t *node = (node_t*)malloc(sizeof(node_t));
    if (node == NULL)
        return 0;
    memset(node, 0, sizeof(node_t));
    return node;
}

static int eval_eq_node(node_t *node)
{
    int ret = strcmp(node->left_child->value.string_literal, node->right_child->value.string_literal);
    return (ret == 0);
}

static int eval_ne_node(node_t *node)
{
    return !eval_eq_node(node);
}

static int eval_ct_node(node_t *node)
{
    char *ret = strstr(node->left_child->value.string_literal, node->right_child->value.string_literal);
    return (ret != 0);
}

static int eval_in_node(node_t *node)
{
    char *ret = strstr(node->right_child->value.string_literal, node->left_child->value.string_literal);
    return (ret != 0);
}

static int eval_ge_node(node_t *node)
{
    int ret = strcmp(node->left_child->value.string_literal, node->right_child->value.string_literal);
    return (ret >= 0);
}

static int eval_gt_node(node_t *node)
{
    int ret = strcmp(node->left_child->value.string_literal, node->right_child->value.string_literal);
    return (ret > 0);
}

static int eval_le_node(node_t *node)
{
    int ret = strcmp(node->left_child->value.string_literal, node->right_child->value.string_literal);
    return (ret <= 0);
}

static int eval_lt_node(node_t *node)
{
    int ret = strcmp(node->left_child->value.string_literal, node->right_child->value.string_literal);
    return (ret < 0);
}

node_t* make_op_node(enum operation op)
{
    node_t* node = alloc_node();
    node->type = OP;
    node->value.op = op;
    return node;
}

node_t* make_op_node_not(enum operation op)
{
    node_t* node = alloc_node();
    node->type = OP;
    node->value.op = op;
    node->is_not = 1;
    return node;
}

void not_node(node_t* node) {
    node->is_not = !node->is_not;
}

node_t* make_left_node(char *literal)
{
    node_t *node = alloc_node();
    node->type = LEFT;
    node->value.string_literal = literal;
    return node;
}

node_t * make_right_node(char *literal)
{
    node_t *node = alloc_node();
    node->type = RIGHT;
    node->value.string_literal = literal;
    return node;
}

int evaluate_expression(node_t *root)
{
    int ret = 0;
    if (!root) return 1;
    switch (root->type) {
        case LEFT:
        case RIGHT:
            ret = 1; goto lbl_end;
        case OP:
            break;
    }
    switch (root->value.op) {
        case EQ:
            ret = eval_eq_node(root); goto lbl_end;
        case NE:
            ret = eval_ne_node(root); goto lbl_end;
        case CT:
            ret = eval_ct_node(root); goto lbl_end;
        case IN:
            ret = eval_in_node(root); goto lbl_end;
        case GT:
            ret = eval_gt_node(root); goto lbl_end;
        case GE:
            ret = eval_ge_node(root); goto lbl_end;
        case LT:
            ret = eval_lt_node(root); goto lbl_end;
        case LE:
            ret = eval_le_node(root); goto lbl_end;
        case AND:
            ret = (evaluate_expression(root->left_child)
                    && evaluate_expression(root->right_child)); goto lbl_end;
        case OR:
            ret = (evaluate_expression(root->left_child)
                    || evaluate_expression(root->right_child)); goto lbl_end;
    }
lbl_end:
    if (root->is_not)
        return !ret;
    return ret;
}

void print_expression(node_t *root)
{
    const char **ops = operation_name;
    if (!root) return;
    if (root->is_not) {
        printf("!");
    }
    if (root->left_child)
        printf("%s", "(");
    switch(root->type) {
        case OP:
            break;
        case LEFT:
            // printf("%s", "(");
            break;
        case RIGHT:
            break;
        default:
            break;
    }
    
    print_expression(root->left_child);
    switch(root->type) {
        case OP:
            printf(" %s ", ops[root->value.op]);
            break;
        case LEFT:
            printf("%s", root->value.string_literal);
            break;
        case RIGHT:
            printf("%s", root->value.string_literal);
            break;
        default:
            break;
    }
    print_expression(root->right_child);
    // if (root->is_not) {
    //     printf(" )");
    // }
    if (root->right_child)
        printf("%s", ")");
    switch(root->type) {
        case OP:
            break;
        case LEFT:
            break;
        case RIGHT:
            // printf("%s", ")");
            break;
        default:
            break;
    }
}
