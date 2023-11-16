#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <queue>

template <class T>
class Node
{
public:
    /**
     * Represents a general node that stores data of type T.
     */
    Node()
    {
        data = new T;
    }
    Node(T d)
    {
        data = new T;
        (*data) = d;
    }
    /**
     * Allows assigning a value of type T to a Node object. 
     * This function returns a reference to the current object
     */
    Node &operator=(T d)
    {
        (*data) = d;
        return *this;
    }
    /**
     *  Node and Node * output directly to the standard output stream
     */
    friend std::ostream &operator<<(std::ostream &out, Node n)
    {
        out << *(n.data);
        return out;
    }
    friend std::ostream &operator<<(std::ostream &out, Node *n)
    {
        out << *(n->data);
        return out;
    }
    // Set the data stored in this node.
    void setData(T d)
    {
        *data = d;
    }
    // Return the data stored in this node.
    T &getData() const
    {
        return *data;
    }

protected:
    T *data;
};

template <class T>
class ListNode : public Node<T> // ListNode class inherits from Node class
{
public:
    /**
     * init a ListNode prev and next to NULL
    */
    ListNode() : Node<T>()
    {
        prev = NULL;
        next = NULL;
    }
    /**
     * Accepts a value of type T as a parameter, creates a new node
     * and prev and next are set to NULL
     */
    ListNode(T d) : Node<T>(d)
    {
        prev = NULL;
        next = NULL;
    }
    /**
     * Two ListNode pointers are used as parameters
     * representing the previous and next nodes respectively.
     */
    ListNode(ListNode *p, ListNode *n) : Node<T>()
    {
        prev = p;
        next = n;
    }
    /**
     * Accepts a T type data and two node pointers 
     * creates a new node, and sets the previous and next nodes
     */
    ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
    {
        prev = p;
        next = n;
    }
    /**
     * Used to obtain the pointers of the next and previous nodes of the current node respectively
     */
    ListNode *getNext() const
    {
        return next;
    }
    ListNode *getPrev() const
    {
        return prev;
    }
    /**
     * Used to set the pointers of the next and previous nodes of the current node respectively
     */
    void setNext(ListNode *n)
    {
        next = n;
    }
    void setPrev(ListNode *p)
    {
        prev = p;
    }
    /**
     * Assignment operator overloading
     * allowing a value of type T to be assigned to the current node
     */
    ListNode &operator=(T d)
    {
        this->setData(d);
        return *this;
    }
    /**
     * Use to obtain the data stored in the node
     */
    T &getData() const
    {
        return Node<T>::getData();
    }

private:
    ListNode *prev, *next;
};

template <class T>
class LinkList
{
public:
    // Initialize the head and tail pointers to NULL
    LinkList()
    {
        head = NULL;
        tail = NULL;
    }
    // Add a new element to the head of the linked list
    void addFromHead(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        /**
         * If the linked list is not empty, 
         * insert the new node into the head and update the front pointer 
         * of the original head node and the back pointer of the new head node.
         */
        if (head != NULL)
        {
            head->setPrev(node);
        }
        node->setNext(head);
        head = node;
        if (tail == NULL)
            tail = node;
    }
    // Add a new element to the end of the linked list
    void addFromTail(T d)
    {
        ListNode<T> *node = new ListNode<T>(d);
        /**
         * If the linked list is not empty, 
         * insert the new node to the tail and update the back pointer 
         * of the original tail node and the front pointer of the new tail node.
         */
        if (tail != NULL)
        {
            tail->setNext(node);
        }
        node->setPrev(tail);
        tail = node;
        if (head == NULL)
            head = node;
    }
    // Adds a new element after the specified node in the linked list
    void addAfter(ListNode<T> *at, T d)
    {
        /**
         * If the specified node exists and is not the end of the linked list, 
         * update the front and rear pointers of the adjacent nodes.
         */
        if (!exist(at))
            return;
        ListNode<T> *node = new ListNode<T>(d);
        if (at->getNext() != NULL)
            at->getNext()->setPrev(node);
        node->setNext(at->getNext());
        at->setNext(node);
        node->setPrev(at);
        if (node->getNext() == NULL)
            tail = node;
    }
    /**
     * Remove an element from the head of the linked list and return the removed node
     */
    ListNode<T> *removeFromHead()
    {
        ListNode<T> *n = head;
        // If the linked list is not empty, update the front pointer of the second node
        if (head != NULL)
        {
            head = head->getNext();
            if (head != NULL)
                head->setPrev(NULL);
            else
                tail = NULL;
            n->setNext(NULL);
        }
        return n;
    }
    /**
     * Remove an element from the end of the linked list and return the removed node
     */
    ListNode<T> *removeFromTail()
    {
        ListNode<T> *n = tail;
        // If the linked list is not empty, update the back pointer of the second last node
        if (tail != NULL)
        {
            tail = tail->getPrev();
            if (tail != NULL)
                tail->setNext(NULL);
            else
                head = NULL;
            n->setPrev(NULL);
        }
        return n;
    }
    /**
     * Remove the specified node from the linked list and return the removed node
     */
    ListNode<T> *remove(ListNode<T> *n)
    {
        // If the specified node does not exist, return NULL
        if (!exist(n))
            return NULL;
        if (n == head)
            return removeFromHead();
        if (n == tail)
            return removeFromTail();
        n->getPrev()->setNext(n->getNext());
        n->getNext()->setPrev(n->getPrev());
        n->setNext(NULL);
        n->setPrev(NULL);
        return n;
    }
    /**
     * Remove the element at the specified index from the linked list and return the removed node
     */
    ListNode<T> *exist(T d)
    {
        ListNode<T> *j = head;
        while (j != NULL)
        {
            if (j->getData() == d)
                return j;
            j = j->getNext();
        }
        return NULL;
    }
    /**
     * Determine whether the specified node is in the linked list
     */
    bool exist(ListNode<T> *n)
    {
        ListNode<T> *j = head;
        while (j != NULL)
        {
            if (j == n)
                return true;
            j = j->getNext();
        }
        return false;
    }
    /**
     * Access elements in a linked list by index
     */
    ListNode<T> &operator[](int i)
    {
        ListNode<T> *j = head;
        int k;
        for (k = 0; k < i && j != NULL; k++)
            j = j->getNext();
        if (j == NULL)
            throw std::invalid_argument("index does not exist.");
        return *j;
    }
    void print() const
    {
        ListNode<T> *j;
        j = head;
        while (j != NULL)
        {
            std::cout << (*j) << " ";
            j = j->getNext();
        }
        std::cout << std::endl;
    }
    /**
     * Returns the total number of elements in the linked list
     */
    int count() const
    {
        int count = 0;
        ListNode<T> *current = head;
        while (current != NULL)
        {
            count++;
            current = current->getNext();
        }
        return count;
    }

protected:
    
    ListNode<T> *head, *tail;
};

/*
    Please finish the TreeNode class, TreeNode class respresent a node in a general tree.
    A general tree is different from binary tree, every node in binary tree have at most two child node, but a node in general tree may have more than two child node.
*/
template <class T>
class TreeNode : public Node<T>
{
public:
    /**
     * The child pointer is initialized to point to a newly created LinkList<TreeNode<T> *> class
     * linked list is used to store the child nodes of the tree node.
     */
    TreeNode() : Node<T>(), child(new LinkList<TreeNode<T> *>()) {}
    TreeNode(T d) : Node<T>(d), child(new LinkList<TreeNode<T> *>()) {}

    /**
     * Adds a child node to the current node. This method adds a pointer of type TreeNode<T> to the end of the child list
     */
    void addChild(TreeNode<T> *n)
    {
        child->addFromTail(n);
    }
    /**
     * Create a new TreeNode<T> node and add it as a child node to the current node
     */
    void addChild(T d)
    {
        TreeNode<T> *newNode = new TreeNode<T>(d);
        addChild(newNode);
    }
    /**
     * Returns the number of child nodes of the current node.
     */
    int childCount() const
    {
        return child->count();
    }
    /**
     * Used to access the child nodes of the current node by index. 
     * If the index is out of range, throw std::out_of_range exception
     */
    TreeNode<T> *operator[](int n)
    {
        if (n < 0 || n >= child->count())
        {
            throw std::out_of_range("Child index out of range");
        }
        return (*child)[n].getData();
    }

private:
    LinkList<TreeNode<T> *> *child;
};

/*
    Please finish the Tree class. Tree class respresent a general tree, that means node on this tree may have more than two child node.

*/
template <class T>
class Tree
{
public:
    // Tree is initialized to NULL
    Tree()
    {
        root = NULL;
    }
    /*
        return the nth node on this tree with level order.
    */
    TreeNode<T> *operator[](int n)
    {
        if (!root || n < 0)
            throw std::out_of_range("Index out of range");
        std::queue<TreeNode<T> *> q;
        q.push(root);
        int index = 0;
        while (!q.empty())
        {
            TreeNode<T> *current = q.front();
            q.pop();
            if (index == n)
                return current;
            index++;
            for (int i = 0; i < current->childCount(); i++)
            {
                q.push((*current)[i]);
            }
        }
        throw std::out_of_range("Index out of range");
    }
    /**
     * Returns the total number of nodes in the tree. 
     * This method is calculated by recursively calling the countNodes(TreeNode<T> *node) method
     */
    int count()
    {
        return countNodes(root);
    }
    /*
        print all the node on this tree with level order.
    */
    void levelOrder()
    {
        if (!root) return;
        std::queue<TreeNode<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode<T> *current = q.front();
            q.pop();
            std::cout << current->getData() << " ";
            for (int i = 0; i < current->childCount(); i++)
            {
                q.push((*current)[i]);
            }
        }
        std::cout << std::endl;
    }
    /*
        print all the node on this tree with preorder.
    */
    void preorder()
    {
        preorderTraversal(root);
        std::cout << std::endl;
    }
    /*
        print all the node on this tree with postorder.
    */
    void postorder()
    {
        postorderTraversal(root);
        std::cout << std::endl;
    }
    /**
     * Set the root node of the tree. If the root node already exists
     * delete the old root node first and then create a new root node
     */
    void setRoot(T d)
    {
        if (root != NULL)
        {
            delete root;
        }
        root = new TreeNode<T>(d);
    }

private:
    TreeNode<T> *root;
    // The root node of a tree or subtree that counts the number of nodes
    int countNodes(TreeNode<T> *node)
    {
        // Check if the node passed in is empty. If empty, returns 0
        if (!node)
            return 0;
        int count = 1; // Count this node
        /**
         * For each child node of the current node, call the countNodes method recursively and add the returned number to count
         */
        for (int i = 0; i < node->childCount(); i++)
        {
            count += countNodes((*node)[i]);
        }
        return count;
    }

    void preorderTraversal(TreeNode<T> *node)
    {
        // Check if the node passed in is empty. If empty, returns
        if (!node)
            return;
        // Output the data stored in the current node
        std::cout << node->getData() << " ";
        /**
         * For each child node of the current node, call the preorderTraversal method recursively
        */
        for (int i = 0; i < node->childCount(); i++)
        {
            preorderTraversal((*node)[i]);
        }
    }

    void postorderTraversal(TreeNode<T> *node)
    {
        // Check if the node passed in is empty. If empty, returns
        if (!node)
            return;
        /**
         * For each child node of the current node, call the postorderTraversal method recursively
        */
        for (int i = 0; i < node->childCount(); i++)
        {
            postorderTraversal((*node)[i]);
        }
        // Output the data stored in the current node
        std::cout << node->getData() << " ";
    }
};

int main()
{
    Tree<int> *tree = new Tree<int>();
    srand(0);
    int j, k, i;
    for (j = 0; j < 20; j++)
    {
        if (tree->count() == 0)
            tree->setRoot(rand() % 100);
        else
        {
            k = rand() % tree->count();
            (*tree)[k]->addChild(rand() % 100);
        }
    }
    tree->levelOrder();
    tree->preorder();
    tree->postorder();
}
