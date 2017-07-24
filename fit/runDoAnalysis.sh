#!/bin/bash

BINMIN="20"
BINMAX="100"

mkdir plotFits/$BINMIN-$BINMAX

#METHOD="cutsGA"
#source doAnalysis.sh
#METHOD="cutsSA"
#source doAnalysis.sh
#METHOD="LD"
#source doAnalysis.sh
METHOD="MLP"
source doAnalysis.sh
#METHOD="BDT"
#source doAnalysis.sh
#METHOD="BDTB"
#source doAnalysis.sh

cp -r plotFits/$BINMIN-$BINMAX ~
