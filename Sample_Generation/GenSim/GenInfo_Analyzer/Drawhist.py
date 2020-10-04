import uproot 
import pandas as pd


## --Tree reader
dat = uproot.open("test_gen_tree.root")['GenInfo']
tree = dat['ZTree']
print(tree.show())


## --Branch to arrays

# Z mass with  st=22
Zmass = tree.array('ZMass')


Zmass = Zmass.flatten()



## -- Draw hist
import matplotlib.pyplot as plt

plt.rcParams["figure.figsize"] = (6,6)
plt.rcParams['lines.linewidth'] = 4

#plt.hist(Zmass,bins=100,histtype='step')
plt.hist(Zmass,bins=100,histtype='step')
plt.xlim(0,200)
plt.title("Z mass",fontsize=20)
plt.xlabel("$Mass_{Z}$")
plt.ylabel("Number of Events")
plt.yscale('log')
plt.grid()
#plt.show()
plt.savefig("Image_N01_Zmass.png")




