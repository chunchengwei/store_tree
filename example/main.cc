#include <iostream>
#include "pArray.h"
#include "store_tree.h"
using namespace std;

int main() {
  pArray a[4] {
    {3,"Energy"},
    {3,"Electron"},
    {3,"Positron"},
    {3,"DM"}
  };
  double temp0[3] = {1,2,3};
  double temp1[3] = {0,0,1};
  double temp2[3] = {0,0,1};
  double temp3[3] = {0,0,1};
  
  a[0] = temp0;
  a[1] = temp1;
  a[2] = temp2;
  a[3] = temp3;
  
  int result = store_tree("test.root", "Flux11", a, 4);
  cout<<result<<endl;

  return 0;
}
