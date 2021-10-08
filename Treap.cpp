#include <iostream>
#include <cstdlib>
using namespace std;

template <typename keytype>
class TreapNode
{
    public:
        keytype key;
        float priority;
        TreapNode* left;
        TreapNode* right;
        TreapNode* parent;
        
        TreapNode(keytype k, float p){
            key = k;
            priority = p;
            left = right = parent = nullptr;
        }

        TreapNode(keytype k){
            key = k;
            priority = (float)(rand() % 100) / 100;
            left = right = parent = nullptr;
        }
};


template <typename keytype>
class Treap
{
    private:
        TreapNode<keytype>* root;
        int num_nodes;
        int in_order[];

    public:

        // Default constructor, empty tree
        Treap<keytype>(){
            num_nodes = 0;
            root = nullptr;
        }

        // Constructor with nodes and size
        Treap<keytype>(keytype k[], float p[], int s){
            root = nullptr;
            num_nodes = 0;
            for(int i = 0; i < s; i++){
                cout<<"inserting: "<<k[i]<<endl;
                insert(k[i], p[i]);
            }
        }

        // Copy constructor
        Treap(const Treap &source){
        }

        // Copy assignment operator
        Treap& operator=(Treap source){
        }

        // Destructor
        ~Treap(){
        }

        float search(keytype k){
            TreapNode<keytype>* ptr = root;
            while(true){
                if(ptr->key == k){
                    return ptr->priority;
                }
                else if(ptr->key > k){
                    if(ptr->left != nullptr){
                        ptr = ptr->left;
                    } else {
                        return -1;
                    }
                }
                else if(ptr->key < k){
                    if(ptr->right != nullptr){
                        ptr = ptr->right;
                    } else {
                        return -1;
                    }
                }
            }
        }
        
        TreapNode<keytype>* rightRotate(TreapNode<keytype>* root){
            TreapNode<keytype>* l = root->left;
            l->parent = root->parent;
            if(l->parent != nullptr && l->parent->left == root){
                l->parent->left = l;
            } else if(l->parent != nullptr&& l->parent->right == root){
                l->parent->right = l;
            }
            root->left = l->right;
            root->parent = l;
            l->right = root;
            root = l;
            return root;
        }

        TreapNode<keytype>* leftRotate(TreapNode<keytype>* root){
            TreapNode<keytype>* r = root->right;
            r->parent = root->parent;
            if(r->parent != nullptr && r->parent->left == root){
                r->parent->left = r;
            } else if(r->parent != nullptr && r->parent->right == root){
                r->parent->right = r;
            }
            root->right = r->left;
            root->parent = r;
            r->left = root;
            root = r;
            return root;
        }

        void checkViolation(TreapNode<keytype>* root){
            if(root->left != nullptr && (root->left->priority < root->priority || (root->left->priority == root->priority && root->left->key < root->key))){
                cout<<"Right rotating..."<<endl;
                root = rightRotate(root);
                if(root->parent != nullptr){
                    checkViolation(root->parent);
                } else {
                    this->root = root;
                }
            } else if(root->right != nullptr && (root->right->priority < root->priority || (root->right->priority == root->priority && root->right->key < root->key))){
                cout<<"Left rotating..."<<endl;
                root = leftRotate(root);
                if(root->parent != nullptr){
                    checkViolation(root->parent);
                } else {
                    this->root = root;
                }
            }
            return;
        }
        // Insert with given priority
        void insert(keytype k, float p){
            num_nodes++;
            if(root == nullptr){
                root = new TreapNode<keytype>(k,p);
                cout<<root->key<<" "<<root->priority<<endl;
                return;
            }
            TreapNode<keytype>* ptr = root;
            while(true){
                if(k < ptr->key){
                    if(ptr->left != nullptr){
                        ptr = ptr->left;
                    } else {
                        ptr->left = new TreapNode<keytype>(k,p);
                        ptr->left->parent = ptr;
                        checkViolation(ptr);
                        return;
                    }
                } else {
                    if(ptr->right != nullptr){
                        ptr = ptr->right;
                    } else {
                        ptr->right = new TreapNode<keytype>(k,p);
                        ptr->right->parent = ptr;
                        checkViolation(ptr);
                        return;
                    }
                }
            }
        }

        // Insert with random priority in range [0, 1]
        void insert(keytype k){
            num_nodes++;
            if(root == nullptr){
                root = new TreapNode<keytype>(k);
                cout<<root->key<<" "<<root->priority<<endl;
                return;
            }
            TreapNode<keytype>* ptr = root;
            while(true){
                if(k < ptr->key){
                    if(ptr->left != nullptr){
                        ptr = ptr->left;
                    } else {
                        ptr->left = new TreapNode<keytype>(k);
                        cout<<ptr->left->key<<" "<<ptr->left->priority<<endl;
                        ptr->left->parent = ptr;
                        checkViolation(ptr);
                        return;
                    }
                } else {
                    if(ptr->right != nullptr){
                        ptr = ptr->right;
                    } else {
                        ptr->right = new TreapNode<keytype>(k);
                        cout<<ptr->right->key<<" "<<ptr->right->priority<<endl;
                        ptr->right->parent = ptr;
                        checkViolation(ptr);
                        return;
                    }
                }
            }
        }

        int remove(keytype k){
        }

        int rank(keytype k){
        }

        keytype select(int pos){
        }

        keytype predecessor(keytype k){
        }

        keytype successor(keytype k){
        }

        int size(){
            return num_nodes;
        }

        void preorder(){
            preorder_helper(root);
            cout<<endl;
        }

        void preorder_helper(TreapNode<keytype>* root){
            cout<<root->key;
            cout<<",";
            if(root->left != nullptr){
                preorder_helper(root->left);
            }
            cout<<"recursed left!"<<endl;
            if(root->right != nullptr){
                preorder_helper(root->right);
            }
        }

        void inorder(){
            inorder_helper(root);
        }

        void inorder_helper(TreapNode<keytype>* root){
            if(root->left != nullptr){
                inorder_helper(root->left);
            }
            cout<<" "<<root->key<<" with p: "<<root->priority<<endl;
            if(root->right != nullptr){
                inorder_helper(root->right);
            }
        }
        void postorder(){
            postorder_helper(root);
        }

        void postorder_helper(TreapNode<keytype>* root){
            if(root->left != nullptr){
                postorder_helper(root->left);
            }
            if(root->right != nullptr){
                postorder_helper(root->right);
            }
            cout<<root->key;
            cout<<",";
        }

        bool check_priority(){
            return priority_checker(root);
        }

        bool priority_checker(TreapNode<keytype>* root){
            if(root->left != nullptr && root->left->priority < root->priority){
                return false;
            }
            if(root->right != nullptr && root->right->priority < root->priority){
                return false;
            }
            bool leftbool, rightbool;
            if(root->left != nullptr){
                leftbool = priority_checker(root->left);
            } else {
                leftbool = true;
            }
            if(root->right != nullptr){
                rightbool = priority_checker(root->right);
            } else {
                rightbool = true;
            }
            return leftbool && rightbool;
        }



};

int main(int argc, char **argv){
    int keys[5] = {3, 1, 3, 5, 2};
    float pris[5] = {.1, .1, .4, .6, .8};
    Treap<int> treap(keys, pris, 5);
    treap.inorder();
    treap.preorder();
    cout<<treap.check_priority()<<endl;
}