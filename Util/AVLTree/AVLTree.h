//
// Created by seuns on 11/12/2020.
//
#include "iostream"
#include <vector>
#include<cstdlib>
#include<cstring>
using namespace std;
#ifndef SEARCHENGINETEMPLATES_AVLTREE_H
#define SEARCHENGINETEMPLATES_AVLTREE_H
template <typename t>
class AVLTree{
    private:
        class Node{
            public:
                t data;
                Node* left;
                Node* right;
                int height;
                Node(const t& data){
                    this->data = data;
                    height = 0;
                    left = nullptr;
                    right = nullptr;
                }
        };
        Node* root;
        int size;
        //empties trees and clears pointers
        void emptyTree(Node*& currentNode){
            if(currentNode == nullptr)
                return;
            emptyTree(currentNode->left);
            emptyTree(currentNode->right);
            delete currentNode;
            currentNode = nullptr;
        }

        //recursive insert function
        void insert(const t& data, Node*& node){
            if(node == nullptr) {
                node = new Node(data);
                size++;
            }
            else if(data < node->data){
                insert(data, node->left);
                if(height(node->left) - height(node->right)  > 1 ){
                    if(data < node->left->data)
                        case1(node);
                    else
                        case2(node);
                }
            }
            else if(data > node->data){
                insert(data, node->right);
                if(height(node->right) - height(node->left)  > 1 ){
                    if(data > node->right->data)
                        case4(node);
                    else
                        case3(node);
                }
            }
            else{
                return;
            }

            node->height = max(height(node->left), height(node->right))+1;
        }
        //prints the values in the AVLTree in order
        void inorder(Node*& node){
            if(node == nullptr){
                return;
            }
            inorder(node->left);
            cout << node->data << endl; // TODO: getID works but not what we want
            inorder(node->right);
        }

        void inorder15(Node*& node, int& count, char* documentPath){
            if(node == nullptr || count > 13){ //13 ?????? why does this work
                return;
            }
            this->inorder15(node->left, count, documentPath);
            count++;
            if(count > 15){
                return;
            }
            cout << count << endl;
            char initial[300];
            strcpy(initial, documentPath);
            const char* tempDoc = ("/"+ node->data.getID()+".json").c_str();
            strcat(initial, tempDoc);
                cout << node->data.getID() << "\n\tLocation: " << realpath(initial, NULL) << endl << endl;
            this->inorder15(node->right, count, documentPath);
        }
        void inorder(Node*& node, vector<t*>& vals){
            if(node == nullptr){
                return;
            }
            inorder(node->left, vals);
            vals.push_back(&(node->data));
            inorder(node->right, vals);
        }
        //searches AVLTree for key
        Node* search(Node*& root, const t& key, const int& differ){
            // Base Cases: root is null or key is present at root
            if (root == nullptr || root->data == key)
                return root;

            // Key is greater than root's key
            if (key > root->data)
                return search(root->right, key);

            // Key is smaller than root's key
            return search(root->left, key);
        }
        //searches an AVLTree based on name
        Node* search(Node*& root, const t& key){
            // Base Cases: root is null or key is present at root
            if (root == nullptr || root->data == key)
                return root;

            // Key is greater than root's key
            if (root->data < key)
                return search(root->right, key);

            // Key is smaller than root's key
            return search(root->left, key);
        }

        //searches an AVLTree based on name
        Node* search(Node*& root, const t& key, const bool& set){
            // Base Cases: root is null or key is present at root
            if (root == nullptr || root->data == key)
                return root;

            // Key is greater than root's key
            if (root->data < key)
                return search(root->right, key, set);

            // Key is smaller than root's key
            return search(root->left, key, set);
        }

        //left left rotation
        void case1(Node*& k2){
            Node* k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2->height = max(height(k2->left), height(k2->right)) + 1;
            k1->height = max(height(k1->left), k2->height) + 1;

            k2 = k1;
        }

        //right right rotation
        void case4(Node*& k1){
            Node* k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            k1->height = max(height(k1->left), height(k1->right)) + 1;
            k2->height = max(height(k2->left), k1->height) + 1;

            k1 = k2;
        }

        //left right rotation
        void case2(Node*& k3){
            case4(k3->left);
            case1(k3);
        }

        //right left rotation
        void case3(Node*& k1){
            case1(k1->right);
            case4(k1);
        }

    public:
        //default constructor
        AVLTree(){
            root = nullptr;
            size = 0;
        }
        //destructor empties tree
        ~AVLTree(){
            emptyTree();
        }
        void emptyTree(){
            if (std::is_pointer<t>::value) {
                cout << "delete" << endl;
                emptyTree(this->root);
            }
        }

        // height of the tree
        int height(Node*& currentNode){
            if (currentNode == nullptr)
                return 0;
            return currentNode->height;
        }

        // height of the tree
        int height(){
            if (root == nullptr)
                return 0;
            return root->height;
        }


        // A utility function to get maximum
        // of two integers
        int max(int a, int b){
            return (a > b)? a : b;
        }



        //public insert that starts the recursive insert process
        void insert(const t& data){
            insert(data, this->root);
        }

        //public inorder that starts the recursive inorder process
        void inorder(){
            inorder(this->root);
        }
        //returns number of nodes
        int& getSize(){
            return this->size;
        }
        //checks if value exists in tree
        bool containsVal(const t& key){
            if(search(this->root, key, 3) != nullptr){
                return true;
            }
            return false;
        }
        //checks if tree contains based on string value
        bool contains(const t& key){
            if(search(this->root, key) != nullptr)
                return true;
            return false;
        }
        //if it contains the value then returns the value
        t& getObjValue(const t& key){
            return (search(this->root, key, 3))->data;
        }
        //if it contains the value corresponding to the string then returns the value
        t* getValue(const t& key){
            return &((search(this->root, key))->data);
        }

        //if it contains the value corresponding to the string then returns the value
        t& operator [] (const t& key) const{
            return (search(this->root, key))->data;
        }

        vector<t*> toArrayInOrder() {
            vector<t*> vals;
            inorder(this->root, vals);
            return vals;
        }

        void inorder15(char*& documentPath){
            int i = 0;
            inorder15(this->root, i, documentPath);
        }

        void forWords(){
            emptyTreeForWord(this->root);
        }

        void forAuthors(){
            emptyTreeForAuthors(this->root);
        }

        bool containsForSet(const t& key){
            if(search(this->root, key, true) != nullptr)
                return true;
            return false;
        }

};
#endif //SEARCHENGINETEMPLATES_AVLTREE_H
