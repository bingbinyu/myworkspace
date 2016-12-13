#!/bin/bash
#ausführbar machen: chmod +x /pfad/zu/mp3-rename.sh

#TODO greift irgendwie noch nicht (richtig) auf den tag zu
#TODO wenn tag datei nicht beschrieben kommen hässliche Err.



#benennt datei des übergebenen Pfades korrekt um
myrename (){
     pathfile=$1

     kuenstler=$(cat "$1" | tail -c 128 | cut -b 33-62)
     if [ "$kuenstler" = "" ]
     then 
         kuenstler='_'
     fi

     album=$(cat "$1" | tail -c 128 | cut -b 63-92)
     if [ "$album" = "" ]
     then 
         album='_'
     fi

     titel=$(cat "$1" | tail -c 128 | cut -b 4-33)
     if [ "$titel" = "" ]
     then 
         titel='_'
     fi

     NN=$(echo $((16#$(tail -c 128 $1 | dd skip=126 count=1 ibs=1 status=none | hexdump -e'1/1 "%02x"' -e'"\n"'))))
     if [ $NN -lt 10 ]
     then NN="-0"$NN
     else
         NN="-"$NN
     fi
     newname=("$kuenstler""-""$album""-""$titel""$NN"".mp3")
     dir=$(dirname $pathfile)"/"
     pathtofilename=$dir$newname
     mv $1 "$pathtofilename" 
     echo -e "rename $pathfile to $pathtofilename"
}

for var in "$@"
do
    myrename $var
done

