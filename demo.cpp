
#include <iostream>
#include "demo.h"
#include "linkedlist.h"
#include "types.h"
#include "recorrer.h"

using namespace std;

const int nElem = 20;
TX vect[nElem] = {5, 30,40, 7,80, 90, 37,25, 54,47, 
                  3, 6, 12, 8, 25, 27, 19, 83, 9, 17};



void demoLinkedListSorted()
{
  LinkedList<TX> mylist;
  for(auto x=0; x<nElem; x++)
  {   
    cout << "insertando " << vect[x] << endl; 
    mylist.insert(vect[x]);
  }
  cout << "Lista en orden: ";
  recorrer(mylist, fx);  cout << endl;
  cout << "Lista invertida: ";
  // recorrer_inverso(mylist, fx);  cout << endl;
}