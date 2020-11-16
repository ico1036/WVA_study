import uproot 
import pandas as pd
import numpy as np

#infile = "gen_tree_Z_boson.root"
#infile = "gen_tree_W_boson.root"
infile = "gen_tree_Gamma_hard.root"
#infile = "gen_tree_Gamma_all.root"


#treename = "ZTree"
#treename = "WpTree"
#treename = "WmTree"
treename = "PhoTree"

#hist_name = "ZMass"
#hist_name = "WpMT"
#hist_name = "WmMT"
hist_name = "PhoPT"


out_image_name = "Image_" + hist_name + ".png"

#### -----------------------------------------




## --Tree reader
dat = uproot.open(infile)['GenInfo']
tree = dat[treename]
print(tree.show())


## --Branch to arrays
hist_arr = tree.array(hist_name)
hist_arr = hist_arr.flatten()


xsec = 1.188e-02
Lumi = 150000
Gen_Event = 1047.
weights = np.ones(hist_arr.shape) * xsec * Lumi / Gen_Event 


## -- Draw hist
import matplotlib.pyplot as plt

plt.rcParams["figure.figsize"] = (6,6)
plt.rcParams['lines.linewidth'] = 4

#plt.hist(Zmass,bins=100,histtype='step')
plt.hist(hist_arr,bins=100,histtype='step',weights=weights)
plt.xlim(0,100)
plt.title(hist_name,fontsize=20)
plt.xlabel(hist_name)
plt.ylabel("Number of Events")
plt.yscale('log')
plt.grid()
plt.show()


#plt.savefig(out_image_name)




