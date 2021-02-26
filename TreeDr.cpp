// Test driver

#include <string>
#include <cctype>
#include <cstring>
#include "TreeType.cpp"
#include<iostream>
using namespace std;

template <class ItemType>
TreeType<ItemType>& makeTree(ItemType arr[], int size);
int main()
{
  string command;        // operation to be executed
  int item;
  TreeType<int> tree;
  bool found;
  ifstream inFile;

  cout << "This project is done by Andreas Marsh\n"
       << "If you have any questions or concerns\n"
       << "please email me at andreas.marsh@uga.edu\n"
       << "I also have a non-generic version as my prevoius\n"
       << "submission if you would like to see that.\n"
       << "Thank you for all that you do!\n" << endl;

  inFile.open("input.txt");
  inFile >> command;

  while (command != "Quit")
  {

	  //1
	  if (command == "PutItem")
	  {
		  //cout << "Enter Item to be inserted in the tree  ";
		  inFile >> item;
		  tree.PutItem(item);
		  cout << item;
		  cout << " is inserted" << endl;
	  }
	  //2
	  else if (command == "DeleteItem")
	  {
		  inFile >> item;
		  tree.DeleteItem(item);
	  }
	  //3
	  else if (command == "GetItem")
	  {
		  inFile >> item;
		  item = tree.GetItem(item, found);
		  if (found)
			  cout << item << " found in tree." << endl;
		  else cout << item << " is not in tree." << endl;
	  }
	  //4
	  else if (command == "GetLength")
	  {
		  cout << "Calling GetLength\n";
		  cout << "Number of nodes is " << tree.GetLength() << endl;
	  }
	  //5
	  else if (command == "IsEmpty")
		  if (tree.IsEmpty())
			  cout << "Tree is empty." << endl;
		  else cout << "Tree is not empty." << endl;
	  //6
	  else if (command == "IsFull")
		  if (tree.IsFull())
			  cout << "Tree is full." << endl;
		  else cout << "Tree is not full." << endl;
	  //7
	  else if (command == "Print")
	  {
		  cout << "Printing the tree...InOrder Traversal\n";
		  tree.Print();
		  cout << endl;
	  }
	  //8
	  else if (command == "PreOrderPrint")
	  {
		  cout << "PreOrder Print:\n";
		  tree.PreOrderPrint();
	  }
	  //9
	  else if (command == "PostOrderPrint")
	  {
		  cout << "PostOrder Print:\n";
		  tree.PostOrderPrint();
	  }
	  //10
	  else if (command == "LevelOrderPrint")
	  {
		  cout << "LevelOrder Print:\n";
		  tree.LevelOrderPrint();
	  }
	  //11
	  else if (command == "MakeEmpty")
	  {
		  tree.MakeEmpty();
		  std::cout << "Tree has been made empty." << endl;
	  }

	  //12
	  else if (command == "GetSuccessor")
	  {
		  inFile >> item;
		  cout << "Logical successor of "<<item<< " is:\n";
		  tree.GetSuccessor(item);
	  }
	  //13
	  else if (command == "PrintAncestorsOf")
	  {
		  inFile >> item;
		  cout << "testing Ancestors of " << item << endl;
		  tree.PrintAncestors(item);
	  }
	  //14
	  else if (command == "MirrorImage")
	  {
		  cout << "Testing Mirror Image\n";
		  tree.MakeEmpty();
		  tree.PutItem(10);
		  tree.PutItem(13);
		  tree.PutItem(5);
		  tree.PutItem(4);
		  tree.PutItem(7);
		  tree.PutItem(12);
		  tree.PutItem(20);
		  cout << "\nOriginal Tree before mirroring:\n";
		  tree.LevelOrderPrint();
		  TreeType<int> mirrorOftree;
		  tree.mirrorImage(mirrorOftree);
		  cout<< "Original Tree After Mirroring:\n";
		  tree.LevelOrderPrint();
		  cout<< "Mirror Image:\n";
		  mirrorOftree.LevelOrderPrint();
	  }

	  //15
	  else if (command == "MakeTree")
	  {

          int array[100];
          int length;
          inFile >> length;
          for (int i = 0; i < length; i++) {
			  inFile >> array[i];
          }
          // After implementing makeTree
          // Remove the follwoing comment to call the function
          TreeType<int> balancedTree;
          balancedTree = makeTree(array, length);
          tree = balancedTree;
	  }
	  else
          cout << "Undefined Command!" << command<<endl;
	  inFile >> command;
  }
  cout << "Testing completed."  << endl;


  return 0;
}
// Function: takes in a TreeType reference to add to,
// a QueType to manipulate, and the size of the QueType.
// The function then recursivly calls itself and turns the
// QueType into a balancedTree held in balancedTree
// Pre: size is amount of elements held in QueType a
// Post: balancedTree holds a balanced tree of elements
template <class ItemType>
void makeBalance(TreeType<ItemType>& balancedTree, QueType<ItemType> a, int size){
    // create a temp queue called DUMPER ;)
    QueType<ItemType> dumper;

    // creater a counter for the size of DUMPER
    int counter = 0;

    // check if size is one, if so insert last element and return
    // as no need to split QueType a
    if (size == 1) {
        ItemType item;
        a.Dequeue(item);
        balancedTree.PutItem(item);
        return;
    }
    // if size is to, just move those 2 elements right into the
    // tree, no problamo
    if (size == 2) {
        ItemType item, item2;
        a.Dequeue(item);
        a.Dequeue(item2);
        balancedTree.PutItem(item);
        balancedTree.PutItem(item2);
        return;
    } else {
        // the real money
        // we're going to remove the first "half" of elements
        // from a and throw them into DUMPER
        // "half" cause it's kinda half but not really, it depends
        for (int i = 0; i < ((size+1) / 2) - 1; i++) {
            ItemType item;
            a.Dequeue(item);
            dumper.Enqueue(item);
            counter++;
        }
    }

    // well now the first element in a is the middle value of a
    // this is the first thing we want to enqueue to make the
    // the tree balanced, so let's do that
    ItemType item;
    a.Dequeue(item);
    balancedTree.PutItem(item);

    // the recursive calls, yummy
    // well we want to now do this process again with
    // the first half of a, aka DUMPER
    // and what's left of a, still called a
    // also that counter we made before comes in handy for
    // calculating size of DUMPER and a after all that movement
    makeBalance(balancedTree, dumper, counter);
    makeBalance(balancedTree, a, (size-(counter + 1)));
}

// Function: takes in a sorted array and its size and creates a
// balanced tree using its values
// Pre: arr is initialized and size is number of elements in arr
// Post: balancedTree is returned
template <class ItemType>
TreeType<ItemType>& makeTree(ItemType arr[], int size)
{
	TreeType<ItemType>& balancedTree = * new TreeType<ItemType>;

    // turn arr int a que for FIFO benefits
    QueType<ItemType> a;

    for (int i = 0; i < size; i++) {
        a.Enqueue(arr[i]);
        // balancedTree.PutItem(arr[i]);
    }

    // where the magic really happens
    makeBalance(balancedTree, a, size);

	return balancedTree;
}
