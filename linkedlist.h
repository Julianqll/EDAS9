#ifndef __LINKEDLIST_H__  
#define __LINKEDLIST_H__ 
#include <utility>
#include <algorithm>
#include <cassert>//Leonardo
//#include "iterator.h"
#include "types.h"
using namespace std;

template <typename Node>
void CreateBridge(Node *&rParent, Node *pNew, Node *Node::*pMember)
{
    pNew->*pMember = rParent; // Puente #1
    rParent = pNew; 
}

template <typename T>
class NodeLE
{
  typedef NodeLE<T> Node;
  public: //Joaquin Cambie de protected a public porque indicaba que m_pnext era un miembro protegido
    T       m_data;
    Node   *m_pNext;//
  public:
    // TODO: Completar
    NodeLE(T data, Node *pNext = nullptr) 
        : m_data(data), m_pNext(pNext)
    {};
    T         getData()                {   return m_data;    }
    T        &getDataRef()             {   return m_data;    }
    void      setpNext(NodeLE *pNext)  {   m_pNext = pNext;  }
    Node     *getpNext()               {   return m_pNext;   }
    Node    *&getpNextRef()            {   return m_pNext;   }
};

template <typename Container>
class LLIterator //: public general_iterator<Container>
{public:   
    typedef typename Container::Node Node;
    //typedef general_iterator<Container> Parent;
    typedef class LLIterator<Container> myself;

// Tarea #2 pasar el siguiente codigo a
// Inicio
    Container *m_pContainer;
    Node      *m_pNode;
  public:
    LLIterator(Container *pContainer, Node *pNode)
        : m_pContainer(pContainer), m_pNode(pNode) {}
    LLIterator(myself &other) 
          : m_pContainer(other.m_pContainer), m_pNode(other.m_pNode){}
    LLIterator(myself &&other) 
          {   m_pContainer = move(other.m_pContainer);
              m_pNode = move(other.m_pNode);
          }
    myself operator=(myself &iter)
          {   m_pContainer = move(iter.m_pContainer);
              m_pNode = move(iter.m_pNode);
          }
    bool operator==(myself iter)   { return m_pNode == iter.m_pNode; }
    bool operator!=(myself iter)   { return m_pNode != iter.m_pNode; }
    auto &operator*()              { return m_pNode->getDataRef();   }
  // Fin

public:
    LLIterator operator++() { m_pNode = m_pNode->getpNext();  
                            return *this;
                          }
};

// Tarea #1 hacer que la lista enlazada trabaje bien
template <typename T>
class LinkedList
{
  public:
    typedef NodeLE<T>           Node;
    typedef LinkedList<T>       myself;
    typedef LLIterator<myself>  iterator;
    
  protected:
    Node    *m_pHead = nullptr, 
            *m_pTail = nullptr;
    size_t   m_size  = 0;
  public:
    LinkedList() {}
    void    push_front(T elem); 
    void    push_back(T elem); 

    void    insert(T elem);

    T       PopHead();
    size_t  size()  const       { return m_size;       }
    bool    empty() const       { return size() == 0;  }

    ostream & print(ostream &os);
    T &operator[](size_t pos);

  private:
    Node **findPrev(T &elem) {   return findPrev(m_pHead, elem);   }
    Node **findPrev(Node *&rpPrev, T &elem);
    virtual Node *CreateNode(T &data, Node *pNext=nullptr){ return new Node(data, pNext); }
  public:
    iterator begin() { iterator iter(this, m_pHead);    return iter;    }
    iterator end()   { iterator iter(this, nullptr);    return iter;    }
};

template <typename T>
void LinkedList<T>::push_front(T elem)
{
  Node *pNew = CreateNode(elem);
  pNew->setpNext(m_pHead);
  m_pHead = pNew;
  m_size++;
}

// Leonardo, Ricardo, Miguel Ucañay,Jesus,carlos daniel,joaquin
template <typename T>
void LinkedList<T>::push_back(T elem)
{
    Node *pNew = CreateNode(elem, nullptr);
    if(m_pTail)
      m_pTail->setpNext(pNew);
    m_pTail = pNew;
    if(!m_pHead)
      m_pHead = pNew;
    m_size++;
}

template <typename T>
void LinkedList<T>::insert(T elem)
{   
    Node **pParent = findPrev(m_pHead, elem);
    Node *pNew = CreateNode(elem);
    CreateBridge(*pParent, pNew, &Node::m_pNext);
    if( !pNew->getpNext() )
      m_pTail = pNew;
}

template <typename T>
typename LinkedList<T>::Node ** //Joaquin Farfan ::
LinkedList<T>::findPrev(Node *&rpPrev, T &elem)
{   
  if(!rpPrev || elem < rpPrev->getData() )
     return &rpPrev; // Retorna la direccion del puntero que me apunta
  return findPrev(rpPrev->getpNextRef(), elem);
}

// Leonardo
template <typename T>
T LinkedList<T>::PopHead()
{
    if(m_pHead)
    {
        Node *pNode = m_pHead;
        T data = pNode->getData();
        m_pHead = m_pHead->getpNext();
        delete pNode;
        m_size--;
        if(!m_size) m_pTail = nullptr;
        return data;
    }
    throw "hola excepcion"; // Create custom exception pending
}

template <typename T>
T &LinkedList<T>::operator[](size_t pos)
{
  assert(pos <= size());
  Node *pTmp = m_pHead;
  for(auto i= 0 ; i < pos ; i++)
    pTmp = pTmp->getpNext();
  return pTmp->getDataRef();
}

template <typename T>
ostream &LinkedList<T>::print(ostream &os)
{
  Node *pNode = m_pHead;
  while(pNode)
  {
    os << pNode->getData() << ", ";
    pNode = pNode->getpNext();
  }
  return os;
}

#endif