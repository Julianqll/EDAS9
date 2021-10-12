#ifndef __ITERATOR_H__
#define __ITERATOR_H__
#include <algorithm>
#include <utility>

template <typename Container>
class general_iterator
{
  public:
    typedef  typename Container::Node Node;
    typedef /*typename*/ general_iterator<Container, Node> myself; 
    typedef typename myself::iterator iterator;

    Container *m_pContainer;
    Node      *m_pNode;
  public:
    general_iterator(Container *pContainer, Node *pNode)
                    : m_pContainer(pContainer), m_pNode(pNode) {}
    general_iterator(iterator &other) 
          : m_pContainer(other.m_pContainer), m_pNode(other.m_pNode){}
    general_iterator(iterator &&other) 
          {   m_pContainer = move(other.m_pContainer);
              m_pNode = move(other.m_pNode);
          }
    iterator operator=(iterator &iter) { m_pContainer = move(iter.m_pContainer);
                                         m_pNode = move(iter.m_pNode);}
    bool operator==(iterator iter)   { return m_pNode == iter.m_pNode; }
    bool operator!=(iterator iter)   { return m_pNode != iter.m_pNode; }
    auto &operator*()                { return m_pNode->getDataRef();   }
};

#endif
 