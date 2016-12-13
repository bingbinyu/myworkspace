#!/usr/bin/env bash

echo "Die Dateien: $* werden umbenannt."

#Geht Eingabe fuer Eingabe durch
while [ "$1" != '' ]
do
    DATA=$(basename $1) #Nur Dateiname ohne Pfad, sieht schoener aus
    echo "$DATA wird umbenannt..."

    # ID3v1-Tag ?
    TAG=$(tail -c 128 $1)
    if [[ ${TAG:0:3} == TAG ]]; then

        # Titel bestimmen
        TITEL=$(tail -c 128 $1|cut -b4-33|tr -d "\000")
        TITEL=${TITEL//[ -]/_}  # ' ' und - durch _ ersetzen
        if [[ ${TITEL} == "" ]]; then
            TITEL+="_"
        fi

        # Interpret bestimmen
        INTERPRET=$(tail -c 128 $1|cut -b34-63|tr -d "\000")
        INTERPRET=${INTERPRET//[ -]/_}
        if [[ ${INTERPRET} == "" ]]; then
            INTERPRET+="_"
        fi

        # Album bestimmen
        ALBUM=$(tail -c 128 $1|cut -b64-93|tr -d "\000")
        ALBUM=${ALBUM//[ -]/_}
        if [[ ${ALBUM} == "" ]]; then
            ALBUM+="_"
        fi

        # Titel bauen
        NAME=${INTERPRET}-${ALBUM}-${TITEL}

        #Titel anhaengen falls vefuegbar(If bedingung ist uns unklar)
        #IFTRACK=$(tail -c 128 $1| cut -b126)
        #if [[ ${IFTRACK} == "\000"  ]]; then
        if [[ true ]]; then
            TRACK=$(tail -c 128 $1|cut -b127|tr -d "\000"|od|cut -b13-14)
            NAME+=-${TRACK}
        fi

        NAME+=".mp3"

        mv -f $1 ${NAME} #umbenennen

        echo "$DATA wurde umbenannt in $NAME"
    else
        echo "$1 besitzt keinen ID3v1-Tag..."
        echo "$1 konnte nicht umbenannt werden..."
    fi

    shift # $x nach links shiften
done
echo "Fertig :)"

