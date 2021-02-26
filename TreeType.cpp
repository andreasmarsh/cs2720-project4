#include<iostream>
using namespace std;
#include "TreeType.h"
template <class ItemType>
struct TreeNode
{
    ItemType info;
    TreeNode<ItemType>* left;
    TreeNode<ItemType>* right;
};

// Function: constructor
// Post: TreeType object is initialized
template <class ItemType>
TreeType<ItemType>::TreeType()
{
	root = NULL;
}

// Function: copy constructor, which is unused and thus empty
// Post: Copys originalTree to new TreeType object
template <class ItemType>
TreeType<ItemType>::TreeType(const TreeType& originalTree)
{
}

// Destroy header
template <class ItemType>
void Destroy(TreeNode<ItemType>*& tree);

// Function: destructor which dynamicall deallocates TreeType objects
template <class ItemType>
TreeType<ItemType>::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
	Destroy(root);
}

template <class ItemType>
bool TreeType<ItemType>::IsFull() const
// Function: Returns true if there is no room for another item
// on the free store; false otherwise.
// Post: Function value = (tree is full).
{
    TreeNode<ItemType>* location;
    try
    {
        location = new TreeNode<ItemType>;
        delete location;
        return false;
    }
    catch(std::bad_alloc&)
    {
        return true;
    }
}

template <class ItemType>
bool TreeType<ItemType>::IsEmpty() const
// Function: Returns true if the tree is empty; false otherwise.
// Post: Function value = (tree is empty).
{
    return root == NULL;
}

// CountNodes header
template <class ItemType>
int CountNodes(TreeNode<ItemType>* tree);

template <class ItemType>
int TreeType<ItemType>::GetLength() const
// Function: Calls recursive function CountNodes to count the
// nodes in the tree.
// Post: Function value = number of elements in the tree.
{
    return CountNodes(root);
}

template <class ItemType>
int CountNodes(TreeNode<ItemType>* tree)
// Function: return number of nodes in tree recursivly
// Post: returns the number of nodes in the tree.
{
    if (tree == NULL)
        return 0;
    else
        return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

// Retrieve header
template <class ItemType>
void Retrieve(TreeNode<ItemType>* tree,
              ItemType& item, bool& found);

template <class ItemType>
ItemType TreeType<ItemType>::GetItem(ItemType item, bool& found)
// Function: Calls recursive function Retrieve to search the tree for item
// and retrieves item whose key matches item's key (if present).
// Pre: Key member of item is initialized.
// Post: If there is an element someItem whose key matches item's key,
// then found = true and a copy of someItem is returned, otherwise,
// found = false and item ias returned. Tree is unchanged.
{
    Retrieve(root, item, found);
    return item;
}

// helper function for GetItem
template <class ItemType>
void Retrieve(TreeNode<ItemType>* tree,
              ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem;
//       otherwise found is false and item is unchanged.
{
    if (tree == NULL)
        found = false;                     // item is not found.
    else if (item < tree->info)
        Retrieve(tree->left, item, found); // Search left subtree.
    else if (item > tree->info)
        Retrieve(tree->right, item, found);// Search right subtree.
    else
    {
        item = tree->info;                 // item is found.
        found = true;
    }
}

template <class ItemType>
void Insert(TreeNode<ItemType>*& tree, ItemType item);
// Function: Inserts item into tree.
// Pre: Tree is not full and item is in tree.
// Post: Binary search property is maintained.

template <class ItemType>
void TreeType<ItemType>::PutItem(ItemType item)
// Function: Calls recursive function Insert to insert item into tree.
// Pre: Tree is not full. Item is in tree.
// Post: Binary search property is maintained.
{
    Insert(root, item);
}

// helper Function for PutItem
template <class ItemType>
void Insert(TreeNode<ItemType>*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
    if (tree == NULL){// Insertion place found.
        tree = new TreeNode<ItemType>;
        tree->right = NULL;
        tree->left = NULL;
        tree->info = item;
    }
    else if (item < tree->info)
        Insert(tree->left, item);    // Insert in left subtree.
    else
        Insert(tree->right, item);   // Insert in right subtree.
}

template <class ItemType>
void TreeType<ItemType>::DeleteItem(ItemType item)
// Function: Calls recursive function Delete to delete item from tree.
// Pre: Key memeber of item is initialized
// Post: No element in the tree has a key matching item's key.
{
	bool found = false;
	GetItem(item, found);
	if (found)
		Delete(root, item);
	else
		cout << item << " is not in tree\n";
}

template <class ItemType>
void TreeType<ItemType>::Delete(TreeNode<ItemType>*& tree, ItemType item)
// Function: Deletes item from tree.
// Post:  item is not in tree.
{
    if (item < tree->info)
        Delete(tree->left, item);   // Look in left subtree.
    else if (item > tree->info)
        Delete(tree->right, item);  // Look in right subtree.
    else
        DeleteNode(tree);           // Node found; call DeleteNode.
}

// GetPred header
template <class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data);

// Function: Finds smallest key node in right subtree
// and returns a pointer to that node
template <class ItemType>
TreeNode<ItemType>* TreeType<ItemType>::ptrToSuccessor(TreeNode<ItemType>*& tree)
{
    TreeNode<ItemType>* suc = tree;
    if (suc -> right == NULL) {
        return NULL;
    }

    if (suc -> right != NULL) {
        suc = suc -> right;
        while (suc -> left != NULL) {
            suc = suc -> left;
        }
    }
    return suc;
}

template <class ItemType>
void TreeType<ItemType>::DeleteNode(TreeNode<ItemType>*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no
//       longer in the tree.  If tree is a leaf node or has only
//       non-NULL child pointer the node pointed to by tree is
//       deleted; otherwise, the user's data is replaced by its
//       logical predecessor and the predecessor's node is deleted.
{
    ItemType data;
    TreeNode<ItemType>* tempPtr;

    tempPtr = tree;
    if (tree->left == NULL)
    {
        tree = tree->right;
        delete tempPtr;
    }
    else if (tree->right == NULL)
    {
        tree = tree->left;
        delete tempPtr;
    }
    else
    {
        tempPtr = ptrToSuccessor(tree);
        data = tempPtr->info;
        // GetPredecessor(tree->left, data);
        tree->info = data;
        Delete(tree->right, data);  // Delete predecessor node.
    }
}

// Helper function for DeleteNode
template <class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Function: Sets data to the info member of the right-most node in tree.
{
    while (tree->right != NULL)
        tree = tree->right;
    data = tree->info;
}

// Helper function for Print
template <class ItemType>
void inOrderTraverse(TreeNode<ItemType>* tree)
// Prints info member of items in tree in sorted order on screen.
{
    if (tree != NULL)
    {
        inOrderTraverse(tree->left);   // Print left subtree.
        cout << tree->info<<"  ";
        inOrderTraverse(tree->right);  // Print right subtree.
    }
}

template <class ItemType>
void TreeType<ItemType>::Print() const
// Function: alls recursive function inOrderTraverse to print items in the tree.
// Pre: Tree has been initialized
// Post: Tree is displayed on screen
{
	inOrderTraverse(root);
}

// Function: helper function to print tree in preorder format
// Pre: Tree has been initialized
// Post: Tree is displayed in preorder
template <class ItemType>
void TreeType<ItemType>::PreOrderPrintz(TreeNode<ItemType>*& a)const
{
    if (a == NULL) return;
    cout << a->info << " ";
    PreOrderPrintz(a->left);
    PreOrderPrintz(a->right);
}

// Function: prints tree in preorder format
// Pre: Tree has been initialized
// Post: Tree is displayed in preorder
template <class ItemType>
void TreeType<ItemType>::PreOrderPrint()const
{
    if (this == NULL) return;
    TreeNode<ItemType>* roots = this->root;
    PreOrderPrintz(roots);
    cout << "\n";
}

// Function: helper function to print tree in postorder format
// Pre: Tree has been initialized
// Post: Tree is displayed in postorder
template <class ItemType>
void TreeType<ItemType>::PostOrderPrintz(TreeNode<ItemType>*& a) const
{
    if (a == NULL) return;
    PostOrderPrintz(a->left);
    PostOrderPrintz(a->right);
    cout << a->info << " ";
}

// Function: prints tree in postorder format
// Pre: Tree has been initialized
// Post: Tree is displayed in postorder
template <class ItemType>
void TreeType<ItemType>::PostOrderPrint()const
{
    if (this == NULL) return;
    TreeNode<ItemType>* roots = this->root;
    PostOrderPrintz(roots);
    cout << "\n";
}

// helper function for Mirror Image
template <class ItemType>
void TreeType<ItemType>::mirror(TreeNode<ItemType>*& copy,
                                const TreeNode<ItemType>* originalTree)
// Post: copy is the root of a tree that is a mirror Image of originalTree.
{
    if (originalTree == NULL) return;
    else {
        copy = new TreeNode<ItemType>;
        copy->right = NULL;
        copy->left = NULL;
        copy->info = originalTree->info;
    }
    if (originalTree->left != NULL) mirror(copy->right, originalTree->left);
    if (originalTree->right != NULL) mirror(copy->left, originalTree->right);
    return;
}

// Function: mirrors called on tree and saves new tree to t
template <class ItemType>
void TreeType<ItemType>::mirrorImage(TreeType<ItemType>& t)
{
	// calls the helper function mirror
    mirror(t.root, this->root);
}

// Function: dynamically deletes all trees
// Post: tree is empty; nodes have been deallocated.
template <class ItemType>
void TreeType<ItemType>::Destroy(TreeNode<ItemType>*& tree)
{
    if (tree != NULL)
    {
        Destroy(tree->left);
        Destroy(tree->right);
        delete tree;
    }
}

template <class ItemType>
void TreeType<ItemType>::MakeEmpty()
// Function: Initializes tree to empty state.
// Post: Tree exists and is empty.
{
    Destroy(root);
    root = NULL;
}

template <class ItemType>
void CopyTree(TreeNode<ItemType>*& copy,
              const TreeNode<ItemType>* originalTree)
// Post: copy is the root of a tree that is a duplicate
// of originalTree.
{
	if (originalTree == NULL)
		copy = NULL;
	else
	{
		copy = new TreeNode<ItemType>;
		copy->info = originalTree->info;
        copy->left = NULL;
        copy->right = NULL;
    }

	if (originalTree->left != NULL)	CopyTree(copy->left, originalTree->left);
	if (originalTree->right != NULL) CopyTree(copy->right, originalTree->right);
}

template <class ItemType>
void TreeType<ItemType>::operator=
(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree
// into root.
{
    {
        if (&originalTree == this)
            return;             // Ignore assigning self to self
        Destroy(root);      // Deallocate existing tree nodes
        CopyTree(root, originalTree.root);
    }

}

// Function: returns the height of tree following root
template <class ItemType>
int TreeType<ItemType>::GetHeight(TreeNode<ItemType>* root) const
{
    if (root == NULL) return 0;
    else
    {
        int lDep = GetHeight(root->left);
        int rDep = GetHeight(root->right);

        if (lDep > rDep) return (lDep + 1);
        else return (rDep + 1);
    }
}

template <class ItemType>
void printLevel(TreeNode<ItemType>* root, int level, int& num);

// Function: prints tree in level order
// Post: tree is displayed
template <class ItemType>
void TreeType<ItemType>::LevelOrderPrint()const
{
    int h = GetHeight(this->root);
    int num = CountNodes(this->root);
    for (int i = 1; i <= h; i++)
    {
        printLevel (this->root, i, num);
        cout << "\n";
    }
}

// Functions: helper function of LevelOrderPrint
template <class ItemType>
void printLevel(TreeNode<ItemType>* root, int level, int& num)
{
    if (root == NULL && num <= 0) return;
    if (root == NULL && num > 0) {
        cout << "- "; // puts in - where nulls are until all values are printed
        return;
    }
    if (level == 1) {
        if (root->info != -99999) {
            cout << root->info << " ";
            num--;
        } else  {
            cout << "NULL ";
        }
    } else if (level > 1) {
        printLevel(root->left, level - 1, num);
        printLevel(root->right, level - 1, num);
    }
}

// Function: sets toFind to point at the TreeNode that contains value
template <class ItemType>
void TreeType<ItemType>::setFind(TreeNode<ItemType>*& toFind,
                                 TreeNode<ItemType>* root, int value){
    if (root == NULL) return;
    if (root->info == value) {
        toFind = root;
        return;
    }
    setFind(toFind, root->right, value);
    setFind(toFind, root->left, value);
    return;
}

// returns the succesor value
template <class ItemType>
ItemType  TreeType<ItemType>::GetSuccessor(int value) {
    ItemType successor = -99999;
    bool found = false;
    ItemType search = GetItem(value, found);
    if (found) {
        TreeNode<ItemType>* toFind = NULL; // toFind is the node that has info = value
        setFind(toFind, this->root, value);
        TreeNode<ItemType>* succer = ptrToSuccessor(toFind);
        if (succer != NULL) successor = succer->info;
    } else {
        cout << "Item is not in the Tree" << endl;
        return NULL;
    }
    if (successor == -99999) {
        cout << "NULL" << endl;
        return NULL;
    }
    cout << successor << endl;
    return successor;
}

// Function: prints the ancestoers of a given node whose info members
// contains value. Do not print value
// Pre: Tree is initialized
// Post: The ancestors of the node whose info members is value have been
// printed
template <class ItemType>
void TreeType<ItemType>::PrintAncestors(int value) {
    if (this->root == NULL) return;

    bool found = false;
    GetItem(value, found);
    if (found == false) {
        cout << value << " is not in the tree" << endl;
        return;
    } else {
        // call some function that works
        int i = 0;
        this->printAnts(this->root, value, i);
        cout << "\n";
        return;
    }
    return;
}

// Function: helper function of PrintAncestors
template <class ItemType>
bool TreeType<ItemType>::printAnts(TreeNode<ItemType>* a, int value, int &i) {
    i++; // used to distiguish if value is root or not
    if (a == NULL) return false;
    if (a->info == value) {
        if (i == 1) cout << value << " is the root value, No ancestor";
        return true;
    }
    if (printAnts(a->left, value, i) ||
        printAnts(a->right, value, i)) {
        cout << a->info << " ";
        return true;
    }
    return false;
}
