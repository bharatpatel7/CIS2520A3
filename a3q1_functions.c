#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"

Variable variables[10];
int varCount = 0; 

// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node* createNode(char *data){

        Node *newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        exit(1); 
    }

    strcpy(newNode->data, data);
    newNode->left = newNode->right = NULL;
    return newNode;

}

// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node* parseExpression(char *expr) {

    Node *root = NULL;
    Node *current = NULL;
    Node *stack[100];
    int top = -1;
    
    for (int i = 0; expr[i] != '\0'; i++) {

        if (expr[i] == '(') {
           
            if (current != NULL) {
                stack[++top] = current;
            }

        } else if (isdigit(expr[i]) || expr[i] == '.') {
          
            char num[10];
            int j = 0;
            while (isdigit(expr[i]) || expr[i] == '.') {
                num[j++] = expr[i++];
            }

            num[j] = '\0';
            i--;  

            Node *newNode = createNode(num);

            if (root == NULL) {
                root = newNode;
                current = newNode;
            } else {
                if (current->left == NULL) {
                    current->left = newNode;
                } else {
                    current->right = newNode;
                }
                current = newNode;
            }

        } else if (isalpha(expr[i])) {

            char var[10];
            int j = 0;
            while (isalpha(expr[i])) {
                var[j++] = expr[i++];
            }

            var[j] = '\0';
            i--;  

            Node *newNode = createNode(var);

            if (root == NULL) {
                root = newNode;
                current = newNode;
            } else {
                if (current->left == NULL) {
                    current->left = newNode;
                } else {
                    current->right = newNode;
                }
                current = newNode;
            }

        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
          
            Node *newNode = createNode((char[]){expr[i], '\0'});

            
            newNode->left = current;

            if (top >= 0) {

                Node *parent = stack[top--];
                if (parent->left == NULL) {
                    parent->left = newNode;
                } else {
                    parent->right = newNode;
                }

            } else {
                root = newNode;
            }

            current = newNode;

        } else if (expr[i] == ')') {

            if (top >= 0) {
                current = stack[top--];
            }

        }
        
        // if (current == NULL) {
        //     printf("Warning: 'current' is NULL at index %d\n", i);
        // }
    }

    return root;
}



// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root){

        if (root == NULL) return;
        printf("%s ", root->data);
        preorder(root->left);
        preorder(root->right);

}

// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root){

        if (root == NULL) return;

        if (isdigit(root->data[0])) {
            printf("%s ", root->data);
        } else {
            printf("(");
            inorder(root->left);
            printf("%s ", root->data);
            inorder(root->right);
            printf(")");
        }

}

// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root){

        if (root == NULL) return;
        postorder(root->left);
        postorder(root->right);
        printf("%s ", root->data);

}

// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root){

        if (root == NULL) return;

        if (isalpha(root->data[0])) {

                int isFound = 0;
        
                for (int i = 0; i < varCount; i++) {
                        if (strcmp(variables[i].varName, root->data) == 0) {
                        isFound = 1;
                        break;
                        }
                }

                if (!isFound && varCount < 10) {
                strcpy(variables[varCount].varName, root->data);
                printf("Enter value for %s: ", root->data);
                scanf("%f", &variables[varCount].value);
                varCount++;
                }
        }
    
        promptVariables(root->left);
        promptVariables(root->right);

}

// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root) {

    if (root == NULL) {
        return 0;
    }

    if (isdigit(root->data[0]) || root->data[0] == '.') {
        return atof(root->data);
    } else if (isalpha(root->data[0])) {

        for (int i = 0; i < varCount; i++) {
            if (strcmp(root->data, variables[i].varName) == 0) {
                return variables[i].value;
            }
        }

    }

    float leftValue = calculate(root->left);
    float rightValue = calculate(root->right);

    if (root->data[0] == '+') {
        return leftValue + rightValue;
    } else if (root->data[0] == '-') {
        return leftValue - rightValue;
    } else if (root->data[0] == '*') {
        return leftValue * rightValue;
    } else if (root->data[0] == '/') {
        if (rightValue == 0) {

            printf("Error: Division by 0\n");
            return 0; 
        }

        return leftValue / rightValue;

    }

    return 0;
}



