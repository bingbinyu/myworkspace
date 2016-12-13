#! /usr/bin/env bash

for datei in "$@";do
    
    # Hier wird die Tracknummer bestimmt
    if [ $( cat ./$datei | tail -c2 | cut -b1 | od -d | cut -b10-14  ) -eq 2560 ]
    then
	number= ""
    else
		if [ $(expr $( cat ./$datei | tail -c2 | cut -b1 | od -d | cut -b10-14  ) - 2560) -lt 10 ]
		then
	   		number=-0$(expr $( cat ./$datei | tail -c2 | cut -b1 | od -d | cut -b10-14  ) - 2560)
		else
	    	number=-$(expr $( cat ./$datei | tail -c2 | cut -b1 | od -d | cut -b10-14  ) - 2560)
		fi
    fi

    # Hier wird der der Titel bestimmt
    if [ -z "$(cat ./$datei | tail -c125 | cut -c1-30 | tr -d [:blank:])" ]
    then
	titel="_"
    else
	titel=$(cat ./$datei | tail -c125 | cut -c1-30 | tr -d [:blank:])
    fi

    #Hier wird der Kuenstler bestimmt
    if [ -z "$(cat ./$datei | tail -c95  | cut -c1-30 | tr -d [:blank:])" ]
    then
	kuenstler="_"
    else
	kuenstler=$(cat ./$datei | tail -c95  | cut -c1-30 | tr -d [:blank:])
    fi

    #Hier wird das Album bestimmt
    if [ -z $(cat ./$datei | tail -c65  | cut -c1-30 | tr -d [:blank:]) ]
    then
	album="_"
    else
	album=$(cat ./$datei | tail -c65  | cut -c1-30 | tr -d [:blank:])
    fi

    #Nun wird die Datei der Form entsprechend umbenannt
    mv "$datei" "$( echo "$kuenstler"-"$album"-"$titel""$number".mp3 )"
done
