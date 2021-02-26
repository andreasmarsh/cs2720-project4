#include <string>
#include <fstream>
//typedef int ItemType;
template <class ItemType>
struct TreeNode;
#include "QueType.cpp"

template <class ItemType>
class TreeType
{
public:
    TreeType();                     // constructor
    TreeType(const TreeType<ItemType>& originalTree);// copy constructor
    ~TreeType();                    // destructor

    // Function: Initializes tree to empty state.
    // Post: Tree exists and is empty.
    void MakeEmpty();

    // Function: Returns true if the tree is empty; false otherwise.
    // Post: Function value = (tree is empty).
    bool IsEmpty() const;

    // Function: Returns true if there is no room for another item
    // on the free store; false otherwise.
    // Post: Function value = (tree is full).
    bool IsFull() const;

    // Function: // Function: Calls recursive function CountNodes to count the
    // nodes in the tree.
    // Post: Function value = number of elements in the tree
    int GetLength() const;

    // Function: Calls recursive function Retrieve to search the tree for item
    // and retrieves item whose key matches item's key (if present).
    // Pre: Key member of item is initialized.
    // Post: If there is an element someItem whose key matches item's key,
    // then found = true and a copy of someItem is returned, otherwise,
    // found = false and item ias returned. Tree is unchanged.
    ItemType GetItem(ItemType item, bool& found);

    // Function: Calls recursive function Insert to insert item into tree.
    // Pre: Tree is not full. Item is in tree.
    // Post: Binary search property is maintained.
    void PutItem(ItemType item);

    // Function: Calls recursive function Delete to delete item from tree.
    // Pre: Key memeber of item is initialized
    // Post: No element in the tree has a key matching item's key.
    void DeleteItem(ItemType item);

    // Function: Deltes the node pointed to by tree.
    // Post: the user's data in the nide pointed to by the tree is no
    // longer in the tree. If tree is a leaf node, or has only non-NULL child
    // pointer, the node pointed to by tree is deleted; otherwise, the user's
    // data is replaced by its logical predecessor and the predecessor's
    // node is deleted, whew
    void DeleteNode(TreeNode<ItemType>*& tree);

    // Function: Deletes item frim tree
    // Post: item is not in tree.
    void Delete(TreeNode<ItemType>*& tree, ItemType item);

    void Destroy(TreeNode<ItemType>*& tree);

    void operator=(const TreeType<ItemType>& originalTree);

    // Function: alls recursive function inOrderTraverse to print items in the tree
    // Pre: Tree has been initialized
    // Post: Tree is displayed on screen
    void Print() const;

    // Function: prints tree in level order
    // Post: Tree is displayed
    void LevelOrderPrint()const;

    // Function: prints all ansestors of node that contains value, if it exists
    void PrintAncestors(int value);

    // Function: helper function of PrintAncestors
    bool printAnts(TreeNode<ItemType>* a, int value, int &i);

    // Function: helper function to print tree in preorder format
    // Pre: Tree has been initialized
    // Post: Tree is displayed in preorder
    void PreOrderPrintz(TreeNode<ItemType>*& a) const;

    //Function: prints tree in preorder format
    // Pre: Tree has been initialized
    // Post: Tree is displayed in preorder
    void PreOrderPrint() const;

    // Function: helper function to print tree in postorder format
    // Pre: Tree has been initialized
    // Post: Tree is displayed in postorder
    void PostOrderPrintz(TreeNode<ItemType>*& a) const;

    //Function: prints tree in postorder format
    // Pre: Tree has been initialized
    // Post: Tree is displayed in postorder
    void PostOrderPrint() const;

    // Function: sets toFind to point at the TreeNode thar contains value
    void setFind(TreeNode<ItemType>*& toFind, TreeNode<ItemType>* root, int value);

    // Function: returns the succesor value
    ItemType GetSuccessor(int value);

    // Function: returns the height of tree following root
    int GetHeight(TreeNode<ItemType>* root) const;

    // Function: mirrors called on tree and saves new tree to t
    void mirrorImage(TreeType<ItemType>& t);

private:
    TreeNode<ItemType>* root;

    // Function: Finds smallest key node and returns a pointer to that node
    TreeNode<ItemType>* ptrToSuccessor(TreeNode<ItemType>*& tree);

    // Function: helper function for mirrorImage
    // Post: copy is the root of a tree that is a mirror image of ogTree
    void mirror(TreeNode<ItemType>*& copy, const TreeNode<ItemType>* originalTree);
};
