#ifndef MYBINARYSEARCHTREE_HPP
#define MYBINARYSEARCHTREE_HPP

#include <algorithm>
#include <fstream>
#include <iostream>

template <typename Comparable>
class myBinarySearchTree {
  public:
    myBinarySearchTree() : root{nullptr} { }
    myBinarySearchTree(const myBinarySearchTree & rhs) : root{nullptr}
    {
      root = clone(rhs.root);
    }
    myBinarySearchTree(myBinarySearchTree && rhs) : root{nullptr}
    {
      root = clone(std::move(rhs.root));
    }
    ~myBinarySearchTree()
    {
      makeEmpty();
    }

    const Comparable & findMin() const
    {
      return findMin(root)->element;
    }
    const Comparable & findMax() const
    {
      return findMax(root)->element;
    }
    bool contains(const Comparable & x) const
    {
      return contains(x, root);
    }
    bool isEmpty() const
    {
      return (root == nullptr);
    }
    void printTreeInorder(std::ostream & out = std::cout) const
    {
      printTreeInorder(root, out);
    }
    void printTreePreorder(std::ostream & out = std::cout) const
    {
      printTreePreorder(root, out);
    }
    void printTreePostorder(std::ostream & out = std::cout) const
    {
      printTreePostorder(root, out);
    }

    void makeEmpty()
    {
      makeEmpty(root);
    }
    void insert(const Comparable & x)
    {
      insert(x, root);
    }
    void insert(Comparable && x)
    {
      insert(std::move(x), root);
    }
    void remove(const Comparable & x)
    {
      remove(x, root);
    }

    myBinarySearchTree & operator=(const myBinarySearchTree & rhs)
    {
      root = clone(rhs.root);
    }
    myBinarySearchTree & operator=(myBinarySearchTree && rhs)
    {
      root = clone(std::move(rhs.root));
    }
  private:
    struct BinaryNode
    {
      Comparable element;
      BinaryNode *left;
      BinaryNode *right;

      BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
        : element{theElement}, left{lt}, right{rt} { }

      BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
        : element{std::move(theElement)}, left{lt}, right{rt} { }
    };

    BinaryNode *root;

    void insert(const Comparable & x, BinaryNode * & t)
    {
      if(t == nullptr)
        t = new BinaryNode(x, nullptr, nullptr);
      else if(x < t->element)
        insert(x, t->left);
      else if(t->element < x)
        insert(x, t->right);
      else
        ; // duplicate --> ignore
    }
    void insert(Comparable && x, BinaryNode * & t)
    {
      if(t == nullptr)
        t = new BinaryNode(std::move(x), nullptr, nullptr);
      else if(x < t->element)
        insert(std::move(x), t->left);
      else if(t->element < x)
        insert(std::move(x), t->right);
      else
        ; // duplicate --> ignore
    }
    void remove(const Comparable & x, BinaryNode * & t)
    {
      if(t == nullptr)
        return; // x not found --> do nothing
      if(x < t->element)
        remove(x, t->left);
      else if(t->element < x)
        remove(x, t->right);
      else if(t->left != nullptr && t->right != nullptr)
      {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
      }
      else
      {
        BinaryNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
      }
    }
    BinaryNode * findMin(BinaryNode *t) const
    {
      if(t == nullptr)
        return nullptr;
      if(t->left == nullptr)
        return t;
      return findMin(t->left);
    }
    BinaryNode * findMax(BinaryNode *t) const
    {
      if(t != nullptr)
        while(t->right != nullptr)
          t = t->right;
      return t;
    }
    bool contains(const Comparable & x, BinaryNode *t) const
    {
      if(t == nullptr)
        return false;
      else if(x < t->element)
        return contains(x, t->left);
      else if(t->element < x)
        return contains(x, t->right);
      else
        return true; // match
    }
    void makeEmpty(BinaryNode * & t)
    {
      if(t != nullptr)
      {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
      }
      t = nullptr;
    }
    void printTreeInorder(BinaryNode *t, std::ostream & out) const
    {
      if(t == nullptr)
        return; // end of branch --> do nothing
      if(t->left != nullptr)
        printTreeInorder(t->left, out);
      out << t->element << '\n';
      if(t->right != nullptr)
        printTreeInorder(t->right, out);
    }
    void printTreePreorder(BinaryNode *t, std::ostream & out) const
    {
      if(t == nullptr)
        return; // end of branch --> do nothing
      out << t->element << '\n';
      if(t->left != nullptr)
        printTreePreorder(t->left, out);
      if(t->right != nullptr)
        printTreePreorder(t->right, out);
    }
    void printTreePostorder(BinaryNode *t, std::ostream & out) const
    {
      if(t == nullptr)
        return; // end of branch --> do nothing
      if(t->left != nullptr)
        printTreePostorder(t->left, out);
      if(t->right != nullptr)
        printTreePostorder(t->right, out);
      out << t->element << '\n';
    }
    BinaryNode * clone(BinaryNode *t) const
    {
      if(t == nullptr)
        return nullptr;
      else
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
    }
};

#endif
