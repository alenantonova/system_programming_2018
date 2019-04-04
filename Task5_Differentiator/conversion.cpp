#include "DiffTree.hpp"

int get_priority(Node* cur_node) {
    node type = cur_node->type;
    if(type == NUM || type == VAR) {
        return 0;
    }
    if(type == COS || type == SIN) {
        return 1;
    }
    if(type == POW) {
        return 2;
    }
    if(type == MUL || type == DIV) {
        return 3;
    }
    if(type == ADD || type == SUB) {
        return 4;
    }
}

std::string get_answer(Node* root) {
    std::string left, right;
    if (root->left != nullptr) {
        left = get_answer(root->left);
        if(get_priority(root->left) > get_priority(root)) {
            left = "(" + left +")";
        }
    }
    if (root->right != nullptr) {
        right = get_answer(root->right);
        if(get_priority(root->right) > get_priority(root)) {
            right = "(" + right +")";
        }
    }
    std::string ans;
    switch(root->type) {
        case NUM: {
            std::ostringstream ss;
            ss << root->val;
            ans = ss.str();
            break;
        }
        case VAR: {
            if (root->val == 1) {
                ans = "x";
            } else {
                ans = "y";
            }
            break;
        }
        case ADD: {
            ans = left + " + " + right ;
            break;
        }
        case SUB: {
            ans = left + " - " + right;
            break;
        }
        case MUL: {
            ans = left + "*" + right;
            break;
        }
        case DIV: {
            ans = left + "/" + right;
            break;
        }
        case POW: {
            ans = left + "^" + right;
            break;
        }
        case SIN: {
            ans = "sin" + right;
            break;
        }
        case COS: {
            ans = "cos" + right;
            break;
        }
        case LN: {
            ans = "ln" + right;
        }
    }
    return ans;
}

void write_ans(std::string exp) {
    DiffTree t(exp);
    t.get_expression_tree();
    printf("f(x, y) = %s\n", exp.c_str());
    std::string ans1 = get_answer(get_derivative_tree(t.root, 1));
    std::string ans2 = get_answer(get_derivative_tree(t.root, 2));
    printf("(df/dx)(x, y) = %s\n", ans1.c_str());
    printf("(df/dy)(x, y) = %s\n\n", ans2.c_str());
    return;
}