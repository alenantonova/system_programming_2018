#include<iostream>
#include<cstdio>
#include<string>
#include<sstream>
#include<vector>

#define sub_expression(x) x == '('
#define empty new Node(EMPTY)
#define eq_types(n1, n2) n1->type == n2->type
#define eq_vals(n1, n2) n1->val == n2->val
#define eq_var(n1, n2) (eq_types(n1, n2) && eq_vals(n1, n2))

enum node {EMPTY, NUM, VAR, MIN, ADD, SUB, MUL, DIV, POW, SIN, COS, LN};

struct Node {
    Node* left;
    Node* right;
    node type;
    double val;

    Node(node t, Node* l= nullptr, Node* r = nullptr,
         double v = 0) : type(t), left(l), right(r), val(v) {}
};

class DiffTree {
private:
    std::string expression;
    int pos;
public:
    Node* root;
    DiffTree(std::string str) {
        expression = str;
        pos = 0;
    }
    void get_expression_tree();
    Node* third_prior_operations();
    Node* second_prior_operations();
    Node* first_prior_operations();
    Node* zero_prior_operations();
};

void simplify(Node* root);
void simplify_add(Node* cur_node);
void simplify_sub(Node* cur_node);
void simplify_mul(Node* cur_node);
void simplify_div(Node* cur_node);
void simplify_pow(Node* cur_node);

Node* get_derivative_tree(Node* exp_root, int var_ind);

int get_priority(Node* cur_node);
std::string get_answer(Node* root);
void write_ans(std::string exp);