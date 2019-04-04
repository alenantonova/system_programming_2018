#include "DiffTree.hpp"

extern bool isnull(Node* node) {
    return node->type == NUM && node->val == 0;
}

extern bool isone(Node* node) {
    return node->type == NUM && node->val == 1;
}

void simplify_mul(Node* cur_node) {
    simplify(cur_node->left);
    simplify(cur_node->right);
    if(isnull(cur_node->left) || isnull(cur_node->right)) {
        cur_node->left = nullptr;
        cur_node->right = nullptr;
        cur_node->val = 0;
        cur_node->type = NUM;
        return;
    }
    if (isone(cur_node->left)) {
        *cur_node = *cur_node->right;
        return;
    }
    if (isone(cur_node->right)) {
        *cur_node = *cur_node->left;
        return;
    }
    if(eq_types(cur_node->left, cur_node->right)) {
        node type = cur_node->left->type;
        if (type == NUM) {
            cur_node->val = cur_node->left->val * cur_node->right->val;
            cur_node->left = nullptr;
            cur_node->right = nullptr;
            cur_node->type = NUM;
            return;
        }
        if (type == VAR) {
            if (eq_vals(cur_node->left, cur_node->right)) {
                cur_node->val = 0;
                cur_node->right = new Node(NUM, nullptr, nullptr, 2);
                cur_node->type = POW;
                return;
            }
        }
        if (type == SIN || type == COS) {
            if(eq_var(cur_node->left->right, cur_node->right->right)) {
                cur_node->val = 0;
                cur_node->right = new Node(NUM, nullptr, nullptr, 2);
                cur_node->type = POW;
            }
            return;
        }
        if (type == POW) {
            if(eq_var(cur_node->left->left, cur_node->right->left)) {
                cur_node->val = 0;
                double new_deg = cur_node->left->right->val + cur_node->right->left->val;
                cur_node->right = new Node(NUM, nullptr, nullptr, new_deg);
                cur_node->type = POW;
            }
            return;
        }
    }
    if(cur_node->left->type == DIV) {
        Node* mul = new Node(MUL, cur_node->right, cur_node->left->left);
        cur_node->right = cur_node->left->right;
        cur_node->left = mul;
        cur_node->type = DIV;
    }
    if(cur_node->right->type == DIV) {
        Node* mul = new Node(MUL, cur_node->left, cur_node->right->left);
        cur_node->right = cur_node->right->right;
        cur_node->left = mul;
        cur_node->type = DIV;
    }
}

void simplify_div(Node* cur_node) {
    simplify(cur_node->left);
    simplify(cur_node->right);
    if(isnull(cur_node->left)) {
        cur_node->left = nullptr;
        cur_node->right = nullptr;
        cur_node->val = 0;
        cur_node->type = NUM;
        return;
    }
    if (isone(cur_node->right)) {
        *cur_node = *cur_node->left;
        return;
    }
    if(eq_types(cur_node->left, cur_node->right)) {
        node type = cur_node->left->type;
        if (type == NUM) {
            cur_node->val = cur_node->left->val / cur_node->right->val;
            cur_node->left = nullptr;
            cur_node->right = nullptr;
            cur_node->type = NUM;
            return;
        }
        if (type == VAR) {
            if (eq_vals(cur_node->left, cur_node->right)) {
                cur_node->val = 1;
                cur_node->right = nullptr;
                cur_node->left = nullptr;
                cur_node->type = NUM;
                return;
            }
        }
        if (type == SIN || type == COS) {
            if(eq_var(cur_node->left->right, cur_node->right->right)) {
                cur_node->val = 1;
                cur_node->right = nullptr;
                cur_node->left = nullptr;
                cur_node->type = NUM;
            }
            return;
        }
        if (type == POW) {
            if(eq_var(cur_node->left->left, cur_node->right->left)) {
                cur_node->val = 0;
                double new_deg = cur_node->left->right->val - cur_node->right->left->val;
                cur_node->right = new Node(NUM, nullptr, nullptr, new_deg);
                cur_node->type = POW;
            }
            return;
        }
    }
}

void simplify_add(Node* cur_node) {
    simplify(cur_node->left);
    simplify(cur_node->right);
    if (isnull(cur_node->left)) {
        *cur_node = *cur_node->right;
        return;
    }
    if (isnull(cur_node->right)) {
        *cur_node = *cur_node->left;
        return;
    }
    if(eq_types(cur_node->left, cur_node->right)) {
        node type = cur_node->left->type;
        if (type == NUM) {
            cur_node->val = cur_node->left->val + cur_node->right->val;
            cur_node->left = nullptr;
            cur_node->right = nullptr;
            cur_node->type = NUM;
            return;
        }
        if (type == VAR) {
            if (eq_vals(cur_node->left, cur_node->right)) {
                cur_node->val = 0;
                cur_node->left = new Node(NUM, nullptr, nullptr, 2);
                cur_node->type = MUL;
            }
            return;
        }
        if (type == SIN || type == COS) {
            if(eq_var(cur_node->left->right, cur_node->right->right)) {
                cur_node->val = 0;
                cur_node->left = new Node(NUM, nullptr, nullptr, 2);
                cur_node->type = MUL;
            }
            return;
        }
    }
    if(cur_node->right->type == MUL) {
        if(cur_node->right->left->val == -1) {
            cur_node->type = SUB;
            cur_node->right = cur_node->right->right;
            simplify_sub(cur_node);
        }
    }
}

void simplify_sub(Node* cur_node) {
    simplify(cur_node->left);
    simplify(cur_node->right);
    if (isnull(cur_node->left)) {
        *cur_node = *cur_node->right;
        return;
    }
    if (isnull(cur_node->right)) {
        *cur_node = *cur_node->left;
        return;
    }
    if(eq_types(cur_node->left, cur_node->right)) {
        node type = cur_node->left->type;
        if (type == NUM) {
            cur_node->val = cur_node->left->val - cur_node->right->val;
            cur_node->left = nullptr;
            cur_node->right = nullptr;
            cur_node->type = NUM;
            return;
        }
        if (type == VAR) {
            if (eq_vals(cur_node->left, cur_node->right)) {
                cur_node->val = 0;
                cur_node->left = nullptr;
                cur_node->right = nullptr;
                cur_node->type = NUM;
            }
            return;
        }
        if (type == SIN || type == COS) {
            if(eq_var(cur_node->left->right, cur_node->right->right)) {
                cur_node->val = 0;
                cur_node->left = nullptr;
                cur_node->right = nullptr;
                cur_node->type = NUM;
            }
            return;
        }
    }
    if(cur_node->right->type == MUL) {
        if(cur_node->right->left->val == -1) {
            cur_node->type = ADD;
            cur_node->right = cur_node->right->right;
            simplify_add(cur_node);
        }
    }
}

void simplify_pow(Node* cur_node) {
    simplify(cur_node->left);
    simplify(cur_node->right);
    if (isnull(cur_node->left)) {
        cur_node->val = 0;
        cur_node->left = nullptr;
        cur_node->right = nullptr;
        cur_node->type = NUM;
        return;
    }
    if (isnull(cur_node->right)) {
        cur_node->val = 1;
        cur_node->left = nullptr;
        cur_node->right = nullptr;
        cur_node->type = NUM;
        return;
    }
    if (isone(cur_node->left)) {
        cur_node->val = 1;
        cur_node->left = nullptr;
        cur_node->right = nullptr;
        cur_node->type = NUM;
        return;
    }
    if (isone(cur_node->right)) {
        *cur_node = *cur_node->left;
        return;
    }

}

void simplify(Node* node) {
    if(node == nullptr || node->type == NUM || node->type == VAR) {
        return;
    }
    simplify(node->left);
    simplify(node->right);
    //double left_num = node->left->val;
    //double right_num = node->right->val;
    switch(node->type) {
        case ADD: {
            simplify_add(node);
            break;
        }
        case SUB: {
            simplify_sub(node);
            break;
        }
        case MUL: {
            simplify_mul(node);
            break;
        }
        case DIV: {
            simplify_div(node);
            break;
        }
        case POW: {
            simplify_pow(node);
            break;
        }
    }
}
