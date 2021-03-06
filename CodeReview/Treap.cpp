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
        int left_size;
        int right_size;
        
        TreapNode(keytype k, float p){
            left_size = right_size = 0;
            key = k;
            priority = p;
            left = right = parent = nullptr;
        }       

        TreapNode(keytype k){
            left_size = right_size = 0;
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
                // cout<<"inserting: "<<k[i]<<endl;
                insert(k[i], p[i]);
            }
        }

        //Recursive Copy-Building Function
        TreapNode<keytype>* RecurCopy(TreapNode<keytype>* node){
            TreapNode<keytype>* new_node = new TreapNode<keytype>(node->key, node->priority);
            new_node->left_size = node->left_size;
            // TreapNode<keytype> new_node(node->key, node->priority);
            if(node->left != nullptr){
                new_node->left = RecurCopy(node->left);
                new_node->left->parent = new_node;
            }
            if(node->right != nullptr){
                new_node->right = RecurCopy(node->right);
                new_node->right->parent = new_node;
            }
            return new_node;
        }

        // Copy constructor
        Treap(const Treap &source){
            num_nodes = source.num_nodes;
            if(source.root == nullptr){
                root = nullptr;
            }
            root = RecurCopy(source.root);
        }

        // Copy assignment operator
        Treap& operator=(Treap source){
            num_nodes = source.num_nodes;
            if(source.root == nullptr){
                root = nullptr;
            }
            root = RecurCopy(source.root);
            return *this;
        }

        void RecurDelete(TreapNode<keytype>* node){
            if(node->left != nullptr){
                RecurDelete(node->left);
            }
            if(node->right != nullptr){
                RecurDelete(node->right);
            }
            delete node;
        }

        // Destructor
        ~Treap(){
            if(root == nullptr){
                return;
            } else {
                RecurDelete(root);
            }
        }

        int rank(keytype k){
            TreapNode<keytype>* ptr = root;
            if(ptr == nullptr){
                return -1;
            }
            int cur_rank = 1+root->left_size;
            while(true){
                if(ptr->key < k){
                    if(ptr->right == nullptr){
                        return -1;
                    } else {
                        ptr = ptr->right;
                        cur_rank += (1 + ptr->left_size);
                    }
                } else if(ptr->key > k){
                    if(ptr->left == nullptr){
                        return -1;
                    } else {
                        ptr = ptr->left;
                        cur_rank -= (1 + ptr->right_size);
                    }
                } else{
                    return cur_rank;
                }
            }
            cout<<"last";
            return -1;
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
            TreapNode<keytype>* lr = l->right;
            l->parent = root->parent;
            if(l->parent != nullptr && l->parent->left == root){
                l->parent->left = l;
            } else if(l->parent != nullptr&& l->parent->right == root){
                l->parent->right = l;
            }
            //Adjusted l's parent relationship
            root->left_size = l->right_size;
            l->right_size = root->right_size + root->left_size + 1;
            root->left = lr;
            if(lr != nullptr){
                lr->parent = root;
            }
            l->right = root;
            root->parent = l;
            return root->parent;
        }

        TreapNode<keytype>* leftRotate(TreapNode<keytype>* root){
            TreapNode<keytype>* r = root->right;
            TreapNode<keytype>* rl = r->left;
            r->parent = root->parent;
            if(r->parent != nullptr && r->parent->left == root){
                r->parent->left = r;
            } else if(r->parent != nullptr && r->parent->right == root){
                r->parent->right = r;
            }
            //Adjusted r's parent relationship
            root->right = rl;
            root->right_size = r->left_size;
            r->left_size = root->left_size + root->right_size + 1;
            if(rl != nullptr){
                rl->parent = root;
            }
            r->left = root;
            root->parent = r;
            return root->parent;
        }

        void checkViolation(TreapNode<keytype>* root){
            if(root->left != nullptr && (root->left->priority < root->priority || (root->left->priority == root->priority && root->left->key < root->key))){
                // cout<<"Right rotating..."<<endl;
                root = rightRotate(root);
                // cout<<"checking again for parent: "<<root->right->key<<endl;
                checkViolation(root->right);
                // cout<<"passed!"<<endl;
                if(root->parent != nullptr){
                    checkViolation(root->parent);
                } else {
                    this->root = root;
                }
            } else if(root->right != nullptr && (root->right->priority < root->priority || (root->right->priority == root->priority && root->right->key < root->key))){
                // cout<<"Left rotating..."<<endl;
                root = leftRotate(root);
                // cout<<"checking again for parent: "<<root->left->key<<endl;
                checkViolation(root->left);
                // cout<<"passed!"<<endl;
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
                // cout<<root->key<<" "<<root->priority<<endl;
                return;
            }
            TreapNode<keytype>* ptr = root;
            while(true){
                if(k < ptr->key){
                    if(ptr->left != nullptr){
                        ptr->left_size++;
                        ptr = ptr->left;
                    } else {
                        ptr->left = new TreapNode<keytype>(k,p);
                        ptr->left->parent = ptr;
                        ptr->left_size++;
                        checkViolation(ptr);
                        return;
                    }
                } else {
                    if(ptr->right != nullptr){
                        ptr->right_size++;
                        ptr = ptr->right;
                    } else {
                        ptr->right = new TreapNode<keytype>(k,p);
                        ptr->right_size++;
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
                return;
            }
            TreapNode<keytype>* ptr = root;
            while(true){
                if(k < ptr->key){
                    if(ptr->left != nullptr){
                        ptr = ptr->left;
                    } else {
                        ptr->left = new TreapNode<keytype>(k);
                        // cout<<ptr->left->key<<" "<<ptr->left->priority<<endl;
                        ptr->left->parent = ptr;
                        checkViolation(ptr);
                        return;
                    }
                } else {
                    if(ptr->right != nullptr){
                        ptr = ptr->right;
                    } else {
                        ptr->right = new TreapNode<keytype>(k);
                        // cout<<ptr->right->key<<" "<<ptr->right->priority<<endl;
                        ptr->right->parent = ptr;
                        checkViolation(ptr);
                        return;
                    }
                }
            }
        }

        int remove(keytype k){
            TreapNode<keytype>* ptr = root;
            if(ptr == nullptr){
                return 0;
            }
            //Returned if empty tree

            while(true){
                if(ptr->key == k){
                    break;
                }
                else if(ptr->key < k){
                    if(ptr->right != nullptr){
                        ptr = ptr->right;
                    } else {
                        return 0;
                    }
                }
                else if(ptr->key > k){
                    if(ptr->left != nullptr){
                        ptr = ptr->left;
                    } else {
                        return 0;
                    }
                }
            }
            num_nodes--;
            // Pointer has reached relevant node or returned 0

            if(ptr->left == nullptr && ptr->right == nullptr){
                if(ptr->parent->right == ptr){
                    ptr->parent->right = nullptr;
                }
                else if(ptr->parent->left == ptr){
                    ptr->parent->left = nullptr;
                }
                delete ptr;
                return 1;
                // Node is already a leaf and is deleted
            }

            if(ptr->left == nullptr && ptr->right != nullptr){
                if(ptr->parent->right == ptr){
                    ptr->parent->right = ptr->right;
                    ptr->right->parent = ptr->parent;
                } else if(ptr->parent->left == ptr){
                    ptr->parent->left = ptr->right;
                    ptr->right->parent = ptr->parent;
                }
                TreapNode<keytype>* rev_ptr = ptr;
                while(true){
                    if(rev_ptr->parent == nullptr){
                        break;
                    }
                    if(rev_ptr->parent->key <= rev_ptr->key){
                        rev_ptr->parent->right_size--;
                    } else{
                        rev_ptr->parent->left_size--;
                    }
                    rev_ptr = rev_ptr->parent;
                }
                delete ptr;
                return 1;
                // has only right child
            }

            else if(ptr->right == nullptr && ptr->left != nullptr){
                if(ptr->parent->right == ptr){
                    ptr->parent->right = ptr->left;
                    ptr->left->parent = ptr->parent;
                } else if(ptr->parent->left == ptr){
                    ptr->parent->left = ptr->left;
                    ptr->left->parent = ptr->parent;
                }
                TreapNode<keytype>* rev_ptr = ptr;
                while(true){
                    if(rev_ptr->parent == nullptr){
                        break;
                    }
                    if(rev_ptr->parent->key <= rev_ptr->key){
                        rev_ptr->parent->right_size--;
                    } else{
                        rev_ptr->parent->left_size--;
                    }
                    rev_ptr = rev_ptr->parent;
                }
                delete  ptr;
                // has only left child
                return 1;
            }

        //FIX THIS CASE:
            else{ // Has two children, decide new parent
                TreapNode<keytype>* pred_finder = ptr->left;
                bool is_right = false;
                while(pred_finder->right != nullptr){
                    pred_finder = pred_finder->right;
                    is_right = true;
                }
                ptr->key = pred_finder->key;
                ptr->priority = pred_finder->priority;
                if(is_right){
                    pred_finder->parent->right = pred_finder->left;
                    if(pred_finder->left != nullptr){
                        pred_finder->left->parent = pred_finder->parent;
                    }
                }
                else{
                    pred_finder->parent->left = pred_finder->left;
                    if(pred_finder->left != nullptr){
                        pred_finder->left->parent = pred_finder->parent;
                    }
                }
                TreapNode<keytype>* rev_ptr = pred_finder;
                while(true){
                    if(rev_ptr->parent == nullptr){
                        break;
                    }
                    if(rev_ptr->parent->key <= rev_ptr->key){
                        rev_ptr->parent->right_size--;
                    } else{
                        rev_ptr->parent->left_size--;
                    }
                    rev_ptr = rev_ptr->parent;
                }
                checkViolation(ptr);
                delete pred_finder;
                return 1;
            }
            return 0;
        }

        keytype select(int pos){
            keytype dummy;
            if(pos > num_nodes){
                cout<<"invalid input"<<endl;
            }
            TreapNode<keytype>* ptr = root;
            if(ptr == nullptr){
                return dummy;
            }
            int cur_rank = 1+root->left_size;
            while(true){
                if(cur_rank < pos){
                    if(ptr->right == nullptr){
                        return dummy;
                    } else {
                        ptr = ptr->right;
                        cur_rank += (1 + ptr->left_size);
                    }
                } else if(cur_rank > pos){
                    if(ptr->left == nullptr){
                        return dummy;
                    } else {
                        ptr = ptr->left;
                        cur_rank -= (1 + ptr->right_size);
                    }
                } else{
                    return ptr->key;
                }
            }
            return dummy;
        }

        keytype predecessor(keytype k){
            TreapNode<keytype>* ptr = root;
            while(true){
                if(ptr->key == k){
                    break;
                } else if(ptr->key > k){
                    if(ptr->left != nullptr){
                        ptr = ptr->left;
                    } else {
                        return k;
                    }
                } else if(ptr->key < k){
                    if(ptr->right != nullptr){
                        ptr = ptr->right;
                    } else {
                        return k;
                    }
                }
            }
            //K located

            if(ptr->left == nullptr){
                if(ptr->parent == nullptr){
                    return k;
                }
                while(ptr->parent->key > k){
                    ptr = ptr->parent;
                    if(ptr->parent == nullptr){
                        return k;
                    }
                }
                return ptr->parent->key;
            } else {
                ptr = ptr->left;
                while(ptr->right != nullptr){
                    ptr = ptr->right;
                }
                return ptr->key;
            }
        }

        keytype successor(keytype k){
            TreapNode<keytype>* ptr = root;
            while(true){
                if(ptr->key == k){
                    break;
                } else if(ptr->key > k){
                    if(ptr->left != nullptr){
                        ptr = ptr->left;
                    } else {
                        return k;
                    }
                } else if(ptr->key < k){
                    if(ptr->right != nullptr){
                        ptr = ptr->right;
                    } else {
                        return k;
                    }
                }
            }
            //K located

            if(ptr->right == nullptr){ //No successor in subtree
                if(ptr->parent == nullptr){
                    return k;
                }
                while(ptr->parent->key < k){
                    ptr = ptr->parent;
                    if(ptr->parent == nullptr){
                        return k;
                    }
                }
                return ptr->parent->key;
            } else {
                ptr = ptr->right;
                while(ptr->left != nullptr){
                    ptr = ptr->left;
                }
                return ptr->key;
            }
            
        }

        int size(){
            return num_nodes;
        }

        void preorder(){
            preorder_helper(root);
            cout<<endl;
        }

        void preorder_helper(TreapNode<keytype>* root){
            cout<<root->key<<" ";
            // cout<<root->key<<" "<<root->left_size<<" "<<root->right_size<<" "<<rank(root->key)<<" "<<select(rank(root->key))<<" ";
            if(root->left != nullptr){
                preorder_helper(root->left);
            }
            // cout<<"recursed left!"<<endl;
            if(root->right != nullptr){
                preorder_helper(root->right);
            }
        }
        void pri_inorder(){
            pri_inorder_helper(root);
            cout<<endl;
        }
        void inorder(){
            inorder_helper(root);
            cout<<endl;
        }

        void inorder_helper(TreapNode<keytype>* root){
            if(root->left != nullptr){
                inorder_helper(root->left);
            }
            cout<<root->key<<" ";
            if(root->right != nullptr){
                inorder_helper(root->right);
            }
        }

        void pri_inorder_helper(TreapNode<keytype>* root){
            if(root->left != nullptr){
                pri_inorder_helper(root->left);
            }
            cout<<root->priority<<" ";
            if(root->right != nullptr){
                pri_inorder_helper(root->right);
            }
        }

        void postorder(){
            postorder_helper(root);
            cout<<endl;
        }

        void postorder_helper(TreapNode<keytype>* root){
            if(root->left != nullptr){
                postorder_helper(root->left);
            }
            if(root->right != nullptr){
                postorder_helper(root->right);
            }
            cout<<root->key<<" ";
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

// int main(){
//     Treap<char> treap;
//     for(int i = 0; i < 26; i++){
//         treap.insert(char(i+97));
//     }
//     treap.inorder();
//     cout<<treap.check_priority()<<endl<<endl;
    
//     for(int i = 8; i < 17; i++){
//         cout<<"removing: "<<char(i+97)<<endl;
//         treap.remove(char(i+97));
//         treap.inorder();
//         cout<<"checking priority: "<<treap.check_priority()<<endl;
//         cout<<endl;
//     }
// }