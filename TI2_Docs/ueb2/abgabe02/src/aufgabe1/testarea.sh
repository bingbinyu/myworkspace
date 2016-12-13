#!/bin/bash

mkdir mp3s
cp *.mp3 mp3s/
cp the\ programmer/*.mp3 mp3s/
cp unknown mp3s

./mp3-rename.sh mp3s/*

#nice coloring 
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
succ="${GREEN}SUCCESS${NC}"
fail="${RED}FAILED${NC}"

testprint () {

    if [ "$1" = "$2" ] 
    then 
        echo -e "       $succ"
    else 
        echo -e "       ${fail}" >&2
        echo -e "$3 ist nicht der richtige Name" 
    fi
}

## declare an array variable
declare -a correctfnarr=("BGP-Distance Vectors-RIP-07.mp3"
                         "_-Bugs galore-Endless Recursion-01.mp3" 
                         "_-Bugs galore-Race Condition-23.mp3"
                         "_-Bugs galore-Three little bugs-112.mp3"
                         "J. Postel & The Packet Drops-Source Quench-Fragments of IP-01.mp3" 
                         "J. Postel & The Packet Drops-Source Quench-No Route to Host-03.mp3"
                         "J. Postel & The Packet Drops-Source Quench-Traffic Class Assignment-02.mp3"
                         "The Drammer Boys-_-_-36.mp3"
                         "The OpenSSH-Roaming Around-B.E.A.S.T.-05.mp3"
                         "The OpenSSH-Roaming Around-Heartbleed-06.mp3"
                         "The OpenSSH-Roaming Around-Triple 7-04.mp3"
)


for file in mp3s/*; do
    name="$(basename "$file")"
    onematch=false
    for str in "${correctfnarr[@]}"; do
        if [ "$str" = "$name" ] 

            then
                testprint "$name" "$str"
                onematch=true
        fi
    done
    if [ $onematch = false ]
        then 
            testprint "ochne" "nichtgleich" "${name}"
    fi
done

rm -rf mp3s/
