#!/bin/bash


#./applyRegression.exe -t pfClusters_PU_testing.root -o pfClusters_PU_application.root -c ../python/configs_PU/Config_May8_pfcluster -p ../PU_allEta/Config_May8_pfcluster

#./applyRegression.exe -t pfClusters_PU_testing.root -o pfClusters_PU_application.root -c ../python/morenhits_8cores/Config_May8_pfcluster -p Config_2019July26_pfcluster

#./applyRegression.exe -t pfClusters_PU_testing.root -o pfClusters_PU_application.root -c ../python/version_from_previous105X_nhits/Config_May8_pfcluster -p Config_2019July26_pfcluster

#./applyRegression.exe -t pfClusters_PU_testing.root -o pfClusters_PU_application.root -c ../python/interactiveRun/Config_May8_pfcluster -p Config_2019July26_pfcluster


#./applyRegression.exe -t pfClusters_PU_testing.root -o pfClusters_PU_application.root -c ../python/interactiveRun/Config_May8_pfcluster -p ../interactiveRun/Config_May8_pfcluster

#./applyRegression.exe -t pfClusters_PU_testing.root -o pfClusters_PU_application.root -c ../python/Config_May8_pfcluster -p ../morenhits_8cores/Config_May8_pfcluster

###for checks
./applyRegression.exe -t /eos/cms/store/group/phys_egamma/PFClusterCalibration/debug_2018UL/tree_test.root -o tree_test_application.root -c ../python/interactiveRun/Config_May8_pfcluster -p ../interactiveRun/Config_May8_pfcluster