#include <iostream>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

#include "oformat.h"
#include "pArray.h"
#include "store_tree.h"
using std::string;
using std::cout;
using std::endl;

bool store_tree(const string rootName,
                const string treeName,
                const pArray * pA_set,
                const int n_pA) { //pA_set means a group of pArray
  if (n_pA < 2) {
    PRINT_Dividing_line('*');
    cout<<"store_tree ERROR: illegal parametter "<<endl;
    cout<<"  bool store_tree(const string rootName, const string treeName,\\"<<endl;
    cout<<"    const pArray * pA_set, const int n_pA)"<<endl;
    cout<<"  n_pA should be bigger than 2"<<endl;
    PRINT_Dividing_line('*');
    return false;
  }
  if (pA_set[0].GetName() != "Energy") {
    PRINT_Dividing_line('*');
    cout<<"store_tree ERROR: Illegal Parametter "<<endl;
    cout<<"  bool store_tree(const string rootName, const string treeName,\\"<<endl;
    cout<<"    const pArray * pA_set, const int n_pA)"<<endl;
    cout<<"  pA_set[0] should be pArray with name \"Energy\"!!!"<<endl;
    PRINT_Dividing_line('*');
    return false;
  }

  // deal with the Energy tree
  int EnergyLength = pA_set[0].GetLength();

  TFile f(rootName.c_str(), "UPDATE");
  TTree * ene;
  f.GetObject("Energy", ene);
  if(ene) {// tree "Energy" was in the rootfile
    int nEntry = ene->GetEntries();
    if (nEntry != EnergyLength) {
      PRINT_Dividing_line('*');
      cout<<"store_tree ERROR: Energy Length inconsistent"<<endl;
      cout<<"  Energy tree saving in file \""<<rootName<<"\""<<endl;
      cout<<"  has different length with the Energy you want to save"<<endl;
      PRINT_Dividing_line('*');
      f.Close();
      return false;
    }
    double temp;
    ene->SetBranchAddress("Ekin", &temp);
    for (int i=0; i<nEntry; i++) {
      ene->GetEntry(i);
      if (temp != pA_set[0].a[i]) {
        PRINT_Dividing_line('*');
        cout<<"temp = "<<temp<<"\t"<<"data = "<<pA_set[0].a[i]<<endl;
        cout<<"store_tree ERROR: Energy Data inconsistent"<<endl;
        cout<<"  Energy tree saving in file \""<<rootName<<"\""<<endl;
        cout<<"  inconsistent with the Energy you want to save"<<endl;
        PRINT_Dividing_line('*');
        f.Close();
        return false;
      }
    }

  } else { // no tree "Energy" was in the rootfile
    ene = new TTree("Energy", pA_set[0].GetUnit().c_str());
    double temp;
    ene->Branch("Ekin", &temp, "Ekin/D");
    for (int i=0; i<EnergyLength; i++) {
      temp = pA_set[0].a[i];
      ene->Fill();
    }
    ene->Write();
    ene->Delete();
  } 

  // deal with tree Flux
  TTree * flux;
  flux = new TTree(treeName.c_str(), pA_set[1].GetUnit().c_str());
  double temp[n_pA];
  for (int i=1; i<n_pA; i++) {
    string brname = pA_set[i].GetName();
    string leafset = brname + "/D";
    flux->Branch(brname.c_str(), &temp[i], leafset.c_str());
  }
  for (int i=0; i<EnergyLength; i++) {
    for (int j=1; j<n_pA; j++) {
      temp[j] = pA_set[j].a[i];
    }
    flux->Fill();
  }
  flux->Write();
  flux->Delete();

  // finish
  f.Close();
  cout<<"store_tree SUCCESS"<<endl;
  return true;
}
