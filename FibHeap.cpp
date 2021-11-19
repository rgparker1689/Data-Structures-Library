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
    int key;
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
};

template <typename keytype>
class FibHeap
{
    private:
        node<keytype>* minimum;
        node<keytype>* listStart;
        node<keytype>* listEnd;


        
        // Consolidate
        void consolidate(){
            CDA<node<keytype>*> upperLevel(50, nullptr);
            node<keytype>* topIterator = listStart;
            while(topIterator != nullptr){
                cout<<"Checking for "<<topIterator->key<<endl;
                if(upperLevel[topIterator->rank] != nullptr){

                    node<keytype>* botIterator = topIterator;
                    node<keytype>* other = upperLevel[botIterator->rank];

                    if(other->key < botIterator->key){ // Existing node is smaller, append this to it
                        // First new upper level directing
                        botIterator->left->right = botIterator->right;
                        if(botIterator->right != nullptr){
                            botIterator->right->left = botIterator->left;
                        }
                        if(listEnd == botIterator){
                            listEnd = other;
                        }

                        // Next attach iterator to new parent
                        botIterator->parent = other;
                        botIterator->right = other->child;
                        if(other->child != nullptr){
                            other->child->left = botIterator;
                        }
                        // Recursively attach parent's children as siblings for iterator and its children
                        // node<keytype>* rightRecursor = other->child;
                        // node<keytype>* leftRecursor = botIterator;
                        // while(rightRecursor != nullptr){
                        //     node<keytype>* sentinel = leftRecursor; // This will travel to the farthest-right sibling of iterator's child
                        //     while(sentinel->right != nullptr){
                        //         sentinel = sentinel->right;
                        //     }
                        //     sentinel->right = rightRecursor;
                        //     rightRecursor->left = sentinel;
                        //     rightRecursor = rightRecursor->child;
                        //     leftRecursor = leftRecursor->child;
                        // }

                        // Finally, set new child relationship for "other"
                        other->child = botIterator;
                        other->rank++;
                        upperLevel[botIterator->rank] = nullptr;
                        topIterator = other;


                    } else if(other->key > botIterator->key){ // Existing node is bigger, append it to this

                    }

                } else {
                    upperLevel[topIterator->rank] = topIterator;
                    topIterator = topIterator->right;
                }
            }
        }


    public:

        // Default Constructor
        FibHeap(){
            listStart = nullptr;
            listEnd = nullptr;
            minimum = nullptr;
        }

        // Constructor given array
        FibHeap(keytype k[], int s){
            listStart = nullptr;
            listEnd = nullptr;
            minimum = nullptr;
            for(int i = 0; i < s; i++){
                insert(k[i]);
            }
        }

        // Destructor
        ~FibHeap(){
        }

        // Return mininum without modifying heap
        keytype peekKey(){
            return minimum->key;
        }

        // Return and remove minimum key from heap
        keytype extractMin(){
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
        }

        // Merge heap H2 into current heap, consume H2 (set pointer to null)
        void merge(FibHeap<keytype> &H2){
            if(H2.listStart == nullptr){
                return;
            }
            node<keytype>* minSearcher = H2.listStart;
            listEnd->right = H2.listStart;
            listEnd->right->left = listEnd;
            listEnd = H2.listEnd;
            H2.listStart = nullptr;

            while(minSearcher != nullptr){
                if(minSearcher->key < minimum->key){
                    minimum = minSearcher;
                }
                minSearcher = minSearcher->right;
            }
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

        void pubConsolidate(){
            consolidate();
        }


};


int main(){
    int arr[] = {1, 2};
    FibHeap<int> fheap(arr, 2);
    fheap.printKey();
    fheap.pubConsolidate();
    fheap.printKey();

    int other[] = {3, 4};
    int third[] = {5,7, 9, 12};
    FibHeap<int> gheap(other, 2);
    FibHeap<int> hheap(third, 4);
    fheap.merge(gheap);
    cout<<endl;
    fheap.printKey();
    fheap.pubConsolidate();
    cout<<endl;
    fheap.printKey();
    fheap.merge(hheap);
    cout<<endl;
    fheap.printKey();
    fheap.pubConsolidate();
    cout<<endl;
    fheap.printKey();
}