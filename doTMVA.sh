#!/bin/bash

DOTMVA=0
DOMAKEVAR=0
DOMERGE=1
DOREADXML=1
#
OUTPUTDIR="test"
inputMCs=(
"/data/HeavyFlavourRun2/TMVA_Luke/Dntuple_20170428_pp_BuToD0Pi_20151212_v2_DfinderMC_pp_20170423_BtoD0Pi_Dpt5Dy1Tketa2_pthatweight.root"
"/data/wangj/TutorialsSamples/tmvaBntupleRunII/Bntuple20160816_Bpt7svpv5p5Bpt10svpv3p5_BfinderMC_PbPb_Pythia8_BuToJpsiK_Bpt0_Pthat5_TuneCUEP8M1_20160816_bPt5jpsiPt0tkPt0p8_Bp.root"
)
inputDatas=(
"/data/HeavyFlavourRun2/TMVA_Luke/Dntuple_20170428_HeavyFlavor_DfinderData_pp_20170423_BtoD0Pi_Dpt10Dy1Alpha0p2Svpv2Tketa1p5EvtSkim.root"
"/data/wangj/TutorialsSamples/tmvaBntupleRunII/Bntuple20160816_Bpt7svpv5p5Bpt10svpv3p5_BfinderData_PbPb_20160816_bPt5jpsiPt0tkPt0p8_Bp.root"
)
if [ ! -d $OUTPUTDIR ]; then
    mkdir $OUTPUTDIR
fi

#
# if working on several ptbins, BDT.C need to be changed
PTBIN=(20 100)
RAA=(0.49)
COLSYST=('pp')
isPbPb=(0)

MVA=('CutsGA' 'CutsSA' 'LD' 'MLP' 'BDT' 'BDTB')
#MVA=('CutsGA' 'BDT')

nPT=$((${#PTBIN[@]}-1))
nMVA=${#MVA[@]}
nCOL=${#COLSYST[@]}

#
FOLDERS=("myTMVA/weights" "myTMVA/ROOT" "mva/MVAfiles" "readxml/plots")
for i in ${FOLDERS[@]}
do
    if [ ! -d $i ]; then
        mkdir $i
    fi
done
#

# TMVAClassification.C #
if [ $DOTMVA -eq 1 ]; then
    j=0
    while ((j<$nCOL))
    do
        i=0
        while ((i<$nPT))
        do
	    cd myTMVA/
	    echo "-- Processing pT bin: ${PTBIN[i]} - ${PTBIN[i+1]} GeV/c"
	    echo
		rm TMVAClassification_C.d TMVAClassification_C.so
	    root -l -b -q 'TMVAClassification.C++('${isPbPb[j]}','${PTBIN[i]}','${PTBIN[i+1]}')'
            
	    k=0
	    while ((k<$nMVA))
	    do
	        mv weights/TMVAClassification_${MVA[k]}.weights.xml weights/TMVA_${MVA[k]}_${COLSYST[j]}_${PTBIN[i]}_${PTBIN[i+1]}.weights.xml
	        mv weights/TMVAClassification_${MVA[k]}.class.C weights/TMVA_${MVA[k]}_${COLSYST[j]}_${PTBIN[i]}_${PTBIN[i+1]}.class.C
	        k=$(($k+1))
	    done
	    cd ..
	    i=$(($i+1))    
        done
        j=$(($j+1))
    done    
fi

# Tree Variables #
if [ $DOMAKEVAR -eq 1 ]; then
    j=0
    while ((j<$nCOL))
    do
        i=0
	    while ((i<$nPT))
		do
	    	k=0
			cd mva/
			if [ -e header.h ]; then rm header.h; touch header.h; fi
		    while ((k<$nMVA))
    		do
				if [ "${MVA[k]}" = "LD" ] || [ "${MVA[k]}" = "MLP" ] || [ "${MVA[k]}" = "BDT" ] || [ "${MVA[k]}" = "BDTB" ]; then
					echo "#include \"../myTMVA/weights/TMVA_${MVA[k]}_${COLSYST[j]}_${PTBIN[i]}_${PTBIN[i+1]}.class.C\"" >> header.h
				fi
    			k=$(($k+1))
			done
			cd macros/
			root -l -b -q 'MVA.C++('${isPbPb[j]}','${PTBIN[i]}','${PTBIN[i+1]}',"MVA")' 
			cd ../..
			i=$(($i+1))
    	done
    	j=$(($j+1))
    done
fi

# mergeBDT.C and readxml.cc #
j=0
while ((j<$nCOL))
do
    i=0
    # if working on several ptbins, BDT.C need to be changed
    if [ $nPT -eq 1 ]; then
        while ((i<$nPT))
        do
            outputMC="${OUTPUTDIR}/ntB_${COLSYST[j]}_MC_${PTBIN[i]}_${PTBIN[i+1]}.root"
            outputData="${OUTPUTDIR}/ntB_${COLSYST[j]}_Data_${PTBIN[i]}_${PTBIN[i+1]}.root"
            inputMC=${inputMCs[${isPbPb[j]}]}
            inputData=${inputDatas[${isPbPb[j]}]}
            if [ $DOMERGE -eq 1 ]; then
                echo
                echo "  Processing mergeBDT.sh - ${isPbPb[j]}"
                echo
                if [ -f $outputMC ]; then
                    echo "  Error: Targed merged file exists: $outputMC"
                else
                    hadd $outputMC $inputMC mva/MVAfiles/MVA_${COLSYST[j]}_${PTBIN[i]}_${PTBIN[i+1]}_MC.root
                fi
                if [ -f $outputData ]; then
                    echo "  Error: Targed merged file exists: $outputData"
                else
                    hadd $outputData $inputData mva/MVAfiles/MVA_${COLSYST[j]}_${PTBIN[i]}_${PTBIN[i+1]}_DATA.root
                fi
            fi

            if [ $DOREADXML -eq 1 ]; then
                if [ ! -f $outputMC ]; then
                    echo " Error: Merged MVA trees before readxml.cc : MC"
                    echo
                elif [ ! -f $outputData ]; then
                    echo " Error: Merged MVA trees before readxml.cc : Data"
                    echo
                else
                    cd readxml/
					k=0
					while ((k<$nMVA))
					do
					echo ${MVA[k]}
					if [ "${MVA[k]}" = "LD" ] || [ "${MVA[k]}" = "MLP" ] || [ "${MVA[k]}" = "BDT" ] || [ "${MVA[k]}" = "BDTB" ]; then
#					if [ "${MVA[k]}" = "" ]; then
		                root -b -q "readxml_MVA.cc++("\"$outputMC\"","\"$outputData\"","${isPbPb[j]}","\"${MVA[k]}\"","${PTBIN[i]}","${PTBIN[i+1]}","${RAA[i]}")"
					fi
					if [ "${MVA[k]}" = "Cuts" ] || [ "${MVA[k]}" = "CutsSA" ] || [ "${MVA[k]}" = "CutsGA" ]; then
#					if [ "${MVA[k]}" = "Cuts" ]; then
			       		root -b -q "readxml.cc++("${isPbPb[j]}","\"${MVA[k]}\"","${PTBIN[i]}","${PTBIN[i+1]}","${RAA[i]}")"
					fi
					k=$(($k+1))
					done
	                cd ..
                fi
            fi

            i=$(($i+1))
        done
    else
        echo "  Error: If working on several ptbins, MVA.C need to be changed"
        echo
    fi
    j=$(($j+1))
done

