import ROOT, math, numpy

#inputFile = ROOT.TFile.Open('pfClustersTree.root')
#inputFile = ROOT.TFile.Open('root://eoscms.cern.ch//store/user/shilpi/Egamma_PFCluster/pfClustersTree.root')
#inputFile = ROOT.TFile.Open('pfClusters_noPU_training.root')
#inputFile = ROOT.TFile.Open('pfClusters_noPU_PU_training.root')
inputFile = ROOT.TFile.Open('root://eoscms.cern.ch//eos/cms/store/group/phys_egamma/PFClusteRegressionTrees/pfClusters_noPU_PU_testing.root')
#inputFile = ROOT.TFile.Open('root://eoscms.cern.ch//eos/cms/store/group/phys_egamma/PFClusteRegressionTrees/pfClusters_noPU_testing.root')
inputTree = inputFile.Get('een_analyzer/PfTree')

#outputFile = ROOT.TFile.Open('pfClusters_noPU_PU_testing.root', 'RECREATE')
outputFile = ROOT.TFile.Open('pfClusters_noPU_testing.root', 'RECREATE')
outputFile.mkdir('een_analyzer')
outputFile.cd('een_analyzer')
	

ietamod20 = numpy.zeros(1, dtype=float)
iphimod20 = numpy.zeros(1, dtype=float)
tgtvar    = numpy.zeros(1, dtype=float)
nlgtgtvar = numpy.zeros(1, dtype=float)
nhits     = numpy.zeros(1, dtype=int)

outputTree = inputTree.CloneTree(0)
outputTree.Branch('ietamod20', ietamod20, 'ietamod20/D')
outputTree.Branch('iphimod20', iphimod20, 'iphimod20/D')
outputTree.Branch('nlgtgtvar', nlgtgtvar, 'nlgtgtvar/D')
outputTree.Branch('tgtvar', tgtvar, 'tgtvar/D')
outputTree.Branch('nhits', nhits, 'nhits/I')    

for event in inputTree:
    signeta = -1.
    if event.clusIetaIx > 0: signeta = 1.
    ietamod20[0] = (event.clusIetaIx-26*signeta) % 20
    if abs(event.clusIetaIx) < 26:
        ietamod20[0] = event.clusIetaIx-signeta
    iphimod20[0] = (event.clusIphiIy-1) % 20

    nhits[0] = event.clusSize
    if(event.clusSize >= 3):
        nhits[0] = 3
        
    outputTree.Fill()

outputFile.cd('een_analyzer')
outputFile.Write('PfTree')
outputFile.Close()

inputFile.Close()
