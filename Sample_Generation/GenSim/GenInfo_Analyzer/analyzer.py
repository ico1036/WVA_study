import uproot 
import pandas as pd


data = uproot.open('test_gen_tree.root')
tree = data['GenInfo']['outTree']

#print(tree.show())

Zele1pt, Zele1eta, Zele1phi = tree.arrays(['ze1_pt','ze1_eta','ze1_phi'],outputtype=tuple)
Zele2pt, Zele2eta, Zele2phi = tree.arrays(['ze2_pt','ze2_eta','ze2_phi'],outputtype=tuple)

import uproot_methods


Zele1vec = uproot_methods.TLorentzVectorArray.from_ptetaphi(Zele1pt, Zele1eta, Zele1phi)
Zele2vec = uproot_methods.TLorentzVectorArray.from_ptetaphi(Zele2pt, Zele2eta, Zele2phi)
print(Zele1vec)
