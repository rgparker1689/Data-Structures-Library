#include <iostream>
#include <cstdlib>
#include "CDA.cpp"
using namespace std;

template <typename keytype>
struct node {
    node* parent;
    node* child;
    node* left;
    node* right;
    keytype key;
    int rank;

    public:
        node(keytype k){
            parent = nullptr;
            child = nullptr;
            left = nullptr;
            right = nullptr;
            key = k;
            rank = 0;
        }

        node(){
            parent = nullptr;
            child = nullptr;
            left = nullptr;
            right = nullptr;
            rank = 0;
        }
};

template <typename keytype>
class FibHeap
{
    private:
        node<keytype>* minimum;
        node<keytype>* listStart;
        node<keytype>* listEnd;
        CDA<node<keytype>*> degreeList;
        int roots;

    
        node<keytype>* mergeHeaps(node<keytype>* H1, node<keytype>* H2){ // Makes H2 a child of H1
            H2->right = H1->child;
            if(H1->child != nullptr){
                // cout<<"setting "<<H2->key<<" to point to "<<H1->child->key<<endl;
            }
            H2->parent = H1;
            H2->left = nullptr;
            H1->child = H2;
            H1->rank++;
            return H1;
        }

        void consolidate(){
            node<keytype>* iterator = listStart;
            node<keytype>* temp;
            int D;

            for(int i = 0; i < 50; i++){
                if(degreeList[i] != nullptr){
                    degreeList[i] = nullptr;
                }
            }

            for(int i = 0; i < roots; i++){
                // cout<<"Iterator: "<<iterator->key<<endl;
                D = iterator->rank;
                while(degreeList[D] != nullptr){
                    if(iterator->key < degreeList[D]->key){
                        // cout<<"Giving "<<iterator->key<<" child "<<degreeList[D]->key<<endl;
                        iterator = mergeHeaps(iterator, degreeList[D]);
                    } else if(iterator->key > degreeList[D]->key){
                        // cout<<"Giving "<<degreeList[D]->key<<" child "<<iterator->key<<endl;
                        temp = iterator->right;
                        if(temp != nullptr){
                            // cout<<"Temp has val "<<temp->key<<endl;
                        }
                        iterator = mergeHeaps(degreeList[D], iterator);
                        iterator->right = temp;
                    }
                    degreeList[D] = nullptr;
                    D++;
                }
                degreeList[iterator->rank] = iterator;
                if(iterator->right != nullptr){
                    // cout<<"Shifting from "<<iterator->key<<" to "<<iterator->right->key<<endl;
                }
                iterator = iterator->right;
                if(iterator == nullptr){
                    break;
                }
                if(degreeList[D] == nullptr){
                    degreeList[D] = iterator;
                }
            }

            // cout<<"Hit here!"<<endl;
            // for(int i = 0; i < degreeList.Length();i++){
            //     if(degreeList[i] != nullptr){
            //         cout<<"Degree: "<<i<<" key: "<<degreeList[i]->key<<endl;
            //     }
            // }
            // cout<<"Passed it"<<endl;

            bool started = false;
            node<keytype>* navigator = nullptr;
            for(int i = 0; i < 50; i++){
                if(degreeList[i] != nullptr){
                    if(!started){
                        listStart = degreeList[i];
                        minimum = degreeList[i];
                        navigator = degreeList[i];
                        started = true;
                    } else {
                        navigator->right = degreeList[i];
                        degreeList[i]->left = navigator;
                        navigator = navigator->right;
                        navigator->right = nullptr;
                        if(navigator->key < minimum->key){
                            minimum = navigator;
                        }
                    }
                }
            }
            listEnd = navigator;         
        }


    public:

        // Default Constructor
        FibHeap(){
            roots = 0;
            degreeList = CDA<node<keytype>*>(50, nullptr);
            listStart = nullptr;
            listEnd = nullptr;
            minimum = nullptr;
        }

        // Constructor given array
        FibHeap(keytype k[], int s){
            roots=0;
            degreeList = CDA<node<keytype>*>(50, nullptr);
            listStart = nullptr;
            listEnd = nullptr;
            minimum = nullptr;
            for(int i = 0; i < s; i++){
                insert(k[i]);
            }
            consolidate();
        }

        // Destructor
        ~FibHeap(){
        }

        // Return mininum without modifying heap
        keytype peekKey(){
            return minimum->key;
        }

        node<keytype>* findMin(){
            node<keytype>* tempMin = listStart;
            node<keytype>* navigator = tempMin;
            while(navigator != nullptr){
                if(navigator->key < tempMin->key){
                    tempMin = navigator;
                }
                navigator = navigator->right;
            }
            return tempMin;
        }

        // Return and remove minimum key from heap
        keytype extractMin(){
            keytype extracted = minimum->key;
            if(minimum->right == nullptr && minimum->left ==nullptr){
                listStart = nullptr;
                if(minimum->child != nullptr){
                    if(listStart == nullptr){
                        listStart = minimum->child;
                    } else {
                        listEnd->right = minimum->child;
                        minimum->child->left = listEnd;
                    }
                    minimum = findMin();
                    consolidate();
                }
                return extracted;
            }
            if(minimum == listStart){
                listStart = minimum->right;
            } else {
                minimum->left->right = minimum->right;
                // cout<<"Set "<<minimum->left->key<<" to point to min's right"<<endl;
            }
            if(minimum == listEnd){
                listEnd = minimum->left;
            } else {
                minimum->right->left = minimum->left;
            }
            // Minimum has been excised from list
            if(minimum->child != nullptr){
                if(listStart == nullptr){
                    listStart = minimum->child;
                } else {
                    listEnd->right = minimum->child;
                    minimum->child->left = listEnd;
                }
            }
            consolidate();
            return extracted;
        }

        // Insert a key
        void insert(keytype k){
            if(listStart == nullptr){
                listStart = new node<keytype>(k);
                minimum = listStart;
                listEnd = listStart;
            } else {
                node<keytype>* temp = new node<keytype>(k);
                if(temp->key < minimum->key){
                    minimum = temp;
                }
                listEnd->right = temp;
                temp->left = listEnd;
                listEnd = temp;
            }
            // cout<<"Inserted: "<<k<<" so end should be: "<<listEnd->key<<" and start is currently "<<listStart->key<<endl;
            roots++;   
        }

        // Merge heap H2 into current heap, consume H2 (set pointer to null)
        void merge(FibHeap<keytype> &H2){
            if(H2.listStart == nullptr){
                return;
            }
            listEnd->right = H2.listStart;
            listEnd->right->left = listEnd;
            listEnd = H2.listEnd;
            H2.listStart = nullptr;

            minimum = findMin();
            listEnd = findEnd();
        }

        // Recursively "preorder" prints binomial heap
        void recursivePrint(node<keytype>* start){
            while(start != nullptr){
                cout<<start->key<<" ";
                recursivePrint(start->child);
                start = start->right;
            }
        }

        // Print keys in heap. When printing binomial tree, print size followed by modified preoder traversal
        void printKey(){
            node<keytype>* upper = listStart;
            
            while(upper != nullptr){
                cout<<"B"<<upper->rank<<endl;
                cout<<upper->key<<" ";
                recursivePrint(upper->child);
                cout<<endl<<endl;
                upper = upper->right;
            }
        }

        node<keytype>* recursiveCopy(node<keytype>* source_node){
            node<keytype>* new_node = new node<keytype>(source_node->key);
            new_node->rank = source_node->rank;
            if(source_node->right != nullptr){
                new_node->right = recursiveCopy(source_node->right);
                new_node->right->left = new_node;
            }
            if(source_node->child != nullptr){
                new_node->child = recursiveCopy(source_node->child);
                new_node->child->parent = new_node;
            }
            return new_node;
        }

        node<keytype>* findEnd(){
            node<keytype>* navigator = listStart;
            while(navigator->right != nullptr){
                navigator = navigator->right;
            }
            return navigator;
        }

        FibHeap(const FibHeap &source){
            roots = source.roots;
            degreeList = CDA<node<keytype>*>(50, nullptr);
            listStart = recursiveCopy(source.listStart);
            minimum = findMin();
            listEnd = findEnd();
        }


        FibHeap& operator=(FibHeap source){
            roots = source.roots;
            degreeList = CDA<node<keytype>*>(50, nullptr);
            listStart = recursiveCopy(source.listStart);
            minimum = findMin();
            listEnd = findEnd();
            return *this;
        }

        void pubConsolidate(){
            consolidate();
        }


};