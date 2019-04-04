#include "DiffTree.hpp"

Node* get_derivative_tree(Node* exp_root, int var_ind) {
    Node* left = empty;
    if (exp_root->left != nullptr) {
        left = get_derivative_tree(exp_root->left, var_ind);
    }
    Node* right = empty;
    if (exp_root->right != nullptr) {
        right = get_derivative_tree(exp_root->right, var_ind);
    }
    Node *root = new Node(EMPTY);
    switch(exp_root->type) {
        case NUM: {
            root->val = 0;
            root->type = NUM;
            break;
        }
        case VAR: {
            if (exp_root->val == var_ind) {
                root->val = 1;
                root->type = NUM;
            } else {
                root->val = 0;
                //root->type = VAR;
            }
            root->type = NUM;
            break;
        }
        case ADD: { root->left = left;
            root->right = right;
            root->type = ADD;
            break ;
        }
        case SUB: {
            root->left = left;
            root->right = right;
            root->type = SUB;
            break;
        }
        case MUL: {
            Node* left1 = new Node(MUL, left, exp_root->right);
            Node* right1 = new Node(MUL, right, exp_root->left);
            root->left = left1;
            root->right = right1;
            root->type = ADD;
            break;
        }
        case DIV: {
            Node *numeral_left = new Node(MUL, left, exp_root->right);
            Node *numeral_right = new Node(MUL, right, exp_root->left);
            Node *numeral = new Node(SUB, numeral_left, numeral_right);
            Node *pow = new Node(NUM, nullptr, nullptr, 2);
            Node *denominator = new Node(POW, exp_root->right, pow);
            root->left = numeral;
            root->right = denominator;
            root->type = DIV;
            break;
        }
        case POW: {
            if(exp_root->right->type == NUM) {
                //Node* deg = exp_root->right;
                Node *coef = new Node(NUM, nullptr, nullptr, 1);
                Node *new_deg = new Node(SUB, exp_root->right, coef);
                Node *new_pow = new Node(POW, exp_root->left, new_deg);
                //Node *right_exp = new Node(MUL, exp_root->right, new_pow);
                root->left = new Node(MUL, exp_root->right, left);
                root->right = new_pow;
                root->type = MUL;
            } else {
                root->left = exp_root;
                Node *ln = new Node(LN, nullptr, exp_root->left);
                Node *mul = new Node(MUL, exp_root->right, ln);
                root->right = get_derivative_tree(mul, var_ind);
                root->type = MUL;
            }
            break;
        }
        case SIN: {
            Node *cos = new Node(COS, nullptr, exp_root->right);
            root->left = cos;
            root->right = right;
            root->type = MUL;
            break;
        }
        case COS: {
            Node *neg = new Node(NUM, nullptr, nullptr, -1);
            Node *sin = new Node(SIN, nullptr, exp_root->right);
            Node *l_exp = new Node(MUL, neg, sin);
            root->left = l_exp;
            root->right = right;
            root->type = MUL;
            break;
        }
        case LN: {
            root->type = DIV;
            root->left = right;
            root->right = exp_root->right;
        }
    }
    simplify(root);
    return root;
}

