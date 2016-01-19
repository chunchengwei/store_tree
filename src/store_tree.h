/*********************************************************************/ 
// use this method to store pArray[] to file in form of tree
// NB: pArray[0] must be pArray with name Energy
//       and it Unit is Mev/nuclear, and will be Ekin in galprop
//     pArray[i] will be Flux with any name
//       and it Unit is [cm^-2 s^-1 sr^-1 MeV^-1]
//     in root file:
//                  Energy(tree): Ekin(Branch)
//                  Flux(tree):   DM_electron(Branch) //pArray[1]'s name
//                                Primay_electron(Branch) //pArray[2]'s name
//                                ... //pArray[i]'s name
/*********************************************************************/ 
#ifndef _STORE_TREE_H
#define _STORE_TREE_H
#include <string>
#include "pArray.h"

bool store_tree(const std::string ,const std::string, const pArray *, const int);
//use: store_tree(FileName, TreeName, pArray[]);
//FileName can be path + name, eg: tree/tree.root

#endif
