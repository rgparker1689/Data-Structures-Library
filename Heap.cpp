#include <iostream>
#include <cstdlib>
#include "CDA.cpp"
using namespace std;

template <typename keytype>
class Heap
{
    private:
        CDA<keytype> data;
        keytype left(keytype parent);
        keytype right(keytype parent);
        int size;
        
        void heapyify_down(){
        }

        void heapify_up(){
        }
    
    public:

        // Default Constructor
        Heap(){
            size = 0;
        }

        // Constructor given data
        Heap(keytype k[], int s){
            for(int i = 0; i < s; i++){
                Insert(k[i]);
            }
        }

        // Copy Constructor
        Heap(const Heap &source){
        }

        // Copy Assignment Operator
        Heap& operator=(Heap source){
        })

        // Destructor
        ~Heap(){
            delete data;
        }

        // Return min without modifying
        keytype peekKey(){
        }

        // Remove min and return it
        keytype extractMin(){
        }

        // Insert key into heap
        void insert(keytype k){
        }

        // Print keys in array starting at root
        void printKey(){
        }

        int size(){
            return size;
        }
};

