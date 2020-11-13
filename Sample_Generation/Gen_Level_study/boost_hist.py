####################### Requirements ###
# python > 3.8
# pip install uproot4
# pip install boost-histogram
# pip install mplhep
######################################

import uproot4
import matplotlib.pyplot as plt
import mplhep
import boost_histogram as bh
import numpy as np


## Copying Negative-binned histogram is not applied yet



hist = uproot4.open('scheme1.root')
classname_dict = hist.classnames()
classname_dict.pop('GenInfo')

print("Histograms...")
hist_dict={}
for key,_ in classname_dict.items():
	hist_outname = key.split('/')[1]
	print(key,hist_outname)
	
	## fill hist
	hist_dict[hist_outname] = hist[key].to_boost()
	

'''
h1_typeLL 
h1_typeLN 
h1_typeP 
h1_phoPt 
h1_phoPt_HAD 
h1_phoPt_FSR 
h1_nDauZ 
h1_nDauW 
h1_mZDau 
h1_mZDauLL
h1_mWDau 
h1_mWDauLL
'''


histname='h1_phoPt'
Entries = hist_dict[histname].sum(flow=True)
Lumi=150000


## --Normalize histogram
print("Number of events: ",Entries)
weight = Lumi / Entries # In this case, the hist already weighted by xsec 
#weight = 1


## --Rebining  or Slicing
rebin=10
print(hist_dict[histname][::bh.rebin(rebin)])
hist_obj = hist_dict[histname][::bh.rebin(rebin)]
bin_width = hist_obj.axes[0].widths[0]

## --Draw hist
mplhep.histplot(hist_obj*weight,label='%s %d' % ("Entries: ",Entries))
plt.title(histname)

# Log scale
plt.yscale('log')

# Label name
xlabel_name = histname.split('_')[1] + '[GeV]'
ylabel_name = "Number of events / %3.1f GeV" %(bin_width)
plt.xlabel(xlabel_name)
plt.ylabel(ylabel_name)

# Axes ranges
limit=600
plt.xlim(0,limit)
minort_ticks = np.arange(0,limit,20)

# Additional options
plt.minorticks_on()
plt.grid(linestyle='-')
plt.legend()


## --Save or show hist
plt.show()
#outname = histname + '.png'
#lt.savefig(outname)
