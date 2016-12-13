bin="/usr/bin"
binX="/bin"
PATH2=$PATH
paths=$(echo $PATH2 | tr ":" "\n")
containsbin=0
containsbin2=0

for p in $paths
do	
if [ "$p" = "$bin" ]
then
containsbin=1
fi
done

if [ "$containsbin" -eq 1 ] 
then 
PATH=$PATH:/usr/bin
export PATH
fi

for q in $paths
do	
if [ "$q" = "$binX" ]
then
containsbin2=1
fi
done

if [ "$containsbin2" -eq 1 ] 
then 
PATH=$PATH:/bin
export PATH
fi

failCounter=0
testCounter=0

echo "Test gestartet" > TestResults.txt
echo "---------------------------------" >> TestResults.txt

((testCounter++))
echo "echo Test1 &" > Befehle
echo "sleep 1 " >> Befehle
echo "echo Test2" >> Befehle

./ti2sh < Befehle > loc

l1=$(sed -n '3p' loc | tr -d '\n')
l2=$(sed -n '5p' loc | tr -d '\n')
 
echo "$l1 is in line 3. $l1 should be in line 3" >> TestResults.txt
echo "$l2 is in line 5. $l2 should be in line 5" >> TestResults.txt

if [ "$l1" != "Test1" -o "$l2" != "Test2" ] 
then 
((failCounter++))
echo "Testfall Fehgeschlagen" >> TestResults.txt
fi
echo "---------------------------------" >>TestResults.txt

((testCounter++))
echo "echo Test1" > Befehle
echo "sleep 1 " >> Befehle
echo "echo Test2" >> Befehle

./ti2sh < Befehle > loc

l1=$(sed -n '2p' loc | tr -d '\n')
l2=$(sed -n '5p' loc | tr -d '\n')
 
echo "$l1 is in line 2. $l1 should be in line 2" >> TestResults.txt
echo "$l2 is in line 5. $l2 should be in line 5" >> TestResults.txt

if [ "$l1" != "Test1" -o "$l2" != "Test2" ] 
then 
((failCounter++))
echo "Testfall Fehgeschlagen" >> TestResults.txt
fi
echo "---------------------------------" >> TestResults.txt

((testCounter++))
echo "ech Test1" > Befehle

./ti2sh < Befehle > loc

l1=$(sed -n '2p' loc | tr -d '\n')
echo "$l1" >> loc2
l2=$(tail -n -1 loc2 | cut -d$ -f2)
rm loc2
 
echo "line 2 is$l2. line 2 should be$l2" >> TestResults.txt

if [ "$l2" != " (bye)" ] 
then 
((failCounter++))
echo "Testfall Fehgeschlagen" >> TestResults.txt
fi
echo "---------------------------------" >> TestResults.txt


echo "Test beendet" >> TestResults.txt
echo "$testCounter Testfälle. $failCounter Testfälle fehgeschlagen" >> TestResults.txt 

rm loc 
rm Befehle