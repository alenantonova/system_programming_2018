#include "DiffTree.hpp"


Node* DiffTree::third_prior_operations() {
    Node* new_left = second_prior_operations();
    /*if(sub_expression(expression[pos])){
        pos++;
        new_left = third_prior_operations();
        pos++;
    } else {
        new_left = second_prior_operations();
    }*/
    while(expression[pos] == '+' || expression[pos] == '-') {
        node cur_type = ADD;
        if(expression[pos] == '-') {
            cur_type = SUB;
        }
        pos++;
        Node* new_right = second_prior_operations();
        //Node new_node(cur_type, new_left, new_right);
        Node *p = new Node(cur_type, new_left, new_right);
        new_left = p;
    }
    return new_left;
}

Node* DiffTree::second_prior_operations() {
    Node* new_node = first_prior_operations();
    /*if(sub_expression(expression[pos])){
        pos++;
        new_node = third_prior_operations();
        pos++;
    } else {
        new_node = first_prior_operations();
    }*/
    while(expression[pos] == '*' || expression[pos] == '/') {
        node cur_type = MUL;
        if(expression[pos] == '/') {
            cur_type = DIV;
        }
        pos++;
        Node* new_right = first_prior_operations();
        Node *p = new Node(cur_type, new_node, new_right);
        new_node = p;
    }
    return new_node;
}

Node* DiffTree::first_prior_operations() {
    Node* new_node = zero_prior_operations();
    /*if(sub_expression(expression[pos])){
        pos++;
        new_node = third_prior_operations();
        pos++;
    }
    if(expression[pos+1] == '^') {
        new_node = zero_prior_operations();
    }*/
    while(expression[pos] == '^' || expression[pos] == 'c' || expression[pos] == 's' ||
            expression[pos] == 'l') {
            node cur_type;
            if (expression[pos] == '^') {
                cur_type = POW;
                pos++;
            } else if(expression[pos] == 'c') {
                cur_type = COS;
                pos += 3;
            } else if(expression[pos] == 's'){
                cur_type = SIN;
                pos += 3;
            } else {
                cur_type = LN;
                pos += 2;
            }
            Node* new_right = zero_prior_operations();
            Node *p;
            if(cur_type == POW) {
                p = new Node(cur_type, new_node, new_right);
            } else {
                p = new Node(cur_type, nullptr, new_right);
            }
            new_node = p;
    }
    return new_node;
}

Node* DiffTree::zero_prior_operations() {
    Node* new_node = empty;
    if(sub_expression(expression[pos])){
        pos++;
        new_node = third_prior_operations();
        pos++;
        return new_node;
    }
    if (isalnum(expression[pos]) || expression[pos] == '.') {
        if(isalpha(expression[pos])) {
            int num;
            if (expression[pos] == 'c' || expression[pos] == 's' || expression[pos] == 'l') {
                return new_node;
            }
            if (expression[pos] == 'x') {
                num = 1;
            } else {
                num = 2;
            }
            pos++;
            Node n(VAR, nullptr, nullptr, num);
            *new_node = n;
            return new_node;
        }
        std::string num;
        while(isdigit(expression[pos]) || expression[pos] == '.') {
            num.push_back(expression[pos]);
            pos++;
        }
        Node p(NUM, nullptr, nullptr, atof(num.c_str()));
        *new_node = p;
        return new_node;

    }
    return new_node;
}

void DiffTree::get_expression_tree() {
    root = third_prior_operations();
}