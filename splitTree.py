import ROOT, math, numpy

#inputFile = ROOT.TFile.Open('pfClustersTree.root')
inputFile = ROOT.TFile.Open('pfClusters_tree_noPU_training.root')

inputTree = inputFile.Get('een_analyzer/PfTree')

categories = ['ZS1_EB', 'ZS1_EE', 
              'FULL_EB_PT1', 'FULL_EB_PT2', 'FULL_EB_PT3',
              'FULL_EE_PT1', 'FULL_EE_PT2', 'FULL_EE_PT3']
#ptranges = [0., 4.5, 18., 1000.]
ptranges = [0., 2.5, 6, 1000.]

ietamod20 = numpy.zeros(1, dtype=float)
iphimod20 = numpy.zeros(1, dtype=float)
tgtvar    = numpy.zeros(1, dtype=float)
nlgtgtvar = numpy.zeros(1, dtype=float)
nhits_mod     = numpy.zeros(1, dtype=int)


outputs = []
for cat in categories:
    outputs.append([])
    outputs[-1].append(ROOT.TFile.Open('pfClustersTree_%s.root'% cat, 'RECREATE'))

    outputs[-1][0].mkdir('een_analyzer')
    outputs[-1][0].cd('een_analyzer')
    outputs[-1].append(inputTree.CloneTree(0))

nevt=0
for event in inputTree:
    nevt=nevt+1
    if event.genEnergy < 0.25: continue
    if event.nClus > 2: continue

    #if event.clusEta > 2.5: continue
    #if event.clusEta < -2.5: continue

#    if event.clusEta > 2.: continue
#    if event.clusEta < -2.: continue

    signeta = -1.
    if event.clusIetaIx > 0: signeta = 1.
#    ietamod20[0] = (event.clusIetaIx-26*signeta) % 20
    ietamod20[0] = math.fmod((event.clusIetaIx-26*signeta),20)
    if abs(event.clusIetaIx) < 26:
        ietamod20[0] = event.clusIetaIx-signeta
#    iphimod20[0] = (event.clusIphiIy-1) % 20
    iphimod20[0] = math.fmod((event.clusIphiIy-1),20)

#    print ""
#    print "signeta  ", signeta
#    print "mod 20 : ", (event.clusIetaIx-26*signeta)%20
#    print "ieta : ietamod20 : ", event.clusIetaIx, " ",ietamod20[0]
    if event.clusLayer == -1:
        nlgtgtvar[0] = (event.genEnergy/event.clusrawE)
        tgtvar[0] = math.log(event.genEnergy/event.clusrawE)

#        nhits_mod[0] = event.clusSize
#        if(event.clusSize >= 3):
#            nhits_mod[0] = 3

        ###TRY 19th may, 2019
#        if(event.clusSize >= 5):
#            nhits_mod[0] = 5
        
        if event.clusFlag == 1:
        #if event.clusSize == 1:
            outputs[0][1].Fill()
        elif event.clusFlag == 3:
        #elif event.clusSize > 2:
            if event.clusrawE/math.cosh(event.clusEta) < ptranges[1]:
                outputs[2][1].Fill()
            elif event.clusrawE/math.cosh(event.clusEta) < ptranges[2]:
                outputs[3][1].Fill()
            else:
                #print(nevt,nevt%3)
                if nevt%3 == 0: # reduce EB full pt3 statistics by a factor of 3
                    outputs[4][1].Fill()
    elif event.clusLayer == -2:
        nlgtgtvar[0] = (event.genEnergy/(event.clusrawE+event.clusPS1+event.clusPS2))
        tgtvar[0] = math.log(event.genEnergy/(event.clusrawE+event.clusPS1+event.clusPS2))


#        nhits_mod[0] = event.clusSize

#        if(event.clusSize >= 5):
#            nhits_mod[0] = 5

        #if event.clusFlag == 1:
        if event.clusFlag == 1:
        #if event.clusSize == 1:
            outputs[1][1].Fill()
        elif event.clusFlag == 3:
        #elif event.clusSize > 2:
            if event.clusrawE/math.cosh(event.clusEta) < ptranges[1]:
                outputs[5][1].Fill()
            elif event.clusrawE/math.cosh(event.clusEta) < ptranges[2]:
                outputs[6][1].Fill()
            else:
                outputs[7][1].Fill()

for out in outputs:
    out[0].cd('een_analyzer')
    out[1].Write('PfTree')
    out[0].Close()

inputFile.Close()
