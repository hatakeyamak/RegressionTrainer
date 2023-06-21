In order to use this code do:

```bash
cmsrel CMSSW_10_5_0
cd CMSSW_10_5_0/src
cmsenv
git clone git@github.com:cms-egamma/HiggsAnalysis.git
scram b -j 4
git clone https://github.com/hatakeyamak/RegressionTrainer.git -b Run3_V0
cd RegressionTrainer
make -j 4
```
