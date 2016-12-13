# Musterlösung Übungsblatt 4, Aufgabe 1

![](pic/ti2sh-flowchart-main.pdf){ height=.95\textheight }\ 

# Musterlösung Übungsblatt 4, Aufgabe 1

![](pic/ti2sh-flowchart-child.pdf){ height=.95\textheight }\ 

# Musterlösung Übungsblatt 4, Aufgabe 1

![](pic/ti2sh-flowchart-signalhandler.pdf){ height=.95\textheight }\ 

# Musterlösung Übungsblatt 4, Aufgabe 2a)

![](pic/buddy_aufg2a.pdf){ height=.8\textheight }\ 

# Musterlösung Übungsblatt 4, Aufgabe 2b)

![](pic/buddy_aufg2b.pdf){ height=.8\textheight }\ 

# Musterlösung Übungsblatt 4, Aufgabe 3

![](pic/aufg3.pdf){ height=.95\textheight }\ 

# Übungsblatt 6 (Abgabe: 12.12.2016) { .shrink }

## Aufgabe 1 (4 Punkte)

`/home/ti2/ueb/06/mycp` *eingabe* *ausgabe*


* Viel Umkopiererei (Buffer-Cache $\rightarrow$ Puffer $\rightarrow$ Buffer-Cache)
* Pagegröße ermitteln: `sysconf(_SC_PAGESIZE)`
* `mmap()` verwenden (nach getaner Arbeit `munmap()` nicht vergessen)
* ungerade Anzahl von Bytes?
* Dateien der Länge 0? Nullbytes in Dateien?
* das Übliche:
    * Fehlerbehandlung
    * geöffnete Dateien wieder schließen\\
    * genutzten Speicher freigeben, `munmap()`

Performance testen

* `time` 
* ggf. Cache leeren: `sudo sh -c 'printf 1 >/proc/sys/vm/drop_caches'`

# Aufgabe 1 (4 Punkte)

\scriptsize{}

~~~~
$ time dd if=/dev/urandom of=foo2 bs=1 count=819200
819200+0 records in
819200+0 records out
819200 bytes (819 kB) copied, 28.4263 s, 28.8 kB/s

real	0m28.429s
user	0m0.185s
sys	0m28.160s
~~~~

~~~~
$ time dd if=/dev/urandom of=foo bs=4096 count=200
200+0 records in
200+0 records out
819200 bytes (819 kB) copied, 0.0711573 s, 11.5 MB/s

real	0m0.075s
user	0m0.001s
sys	0m0.073s
~~~~

# Aufgabe 2 (3 Punkte)

## Plattengeometrie

![](pic/Hard_disk_platters_and_head.jpg){ height=3cm }\ 

\scriptsize{}

Matthew Field, [http://www.photography.mattfield.com](http://www.photography.mattfield.com)  
[https://commons.wikimedia.org/wiki/File:Hard_disk_platters_and_head.jpg](https://commons.wikimedia.org/wiki/File:Hard_disk_platters_and_head.jpg)  
 22.05.2008, letzter Zugriff am 5.12.2016  
Lizenz: [GFDL v1.2](https://commons.wikimedia.org/wiki/Commons:GNU_Free_Documentation_License,_version_1.2), [CC BY-SA 3.0](http://creativecommons.org/licenses/by-sa/3.0/)

# Aufgabe 2 (3 Punkte)

## Festplatten

Nick Parlante: [„How A Hard Drive Works“](https://www.youtube.com/watch?v=rREkzeoJz1s). 5/2012  
CC Attribution-Share-Alike 3.0  
letzter Zugriff am 5.12.2016  
Lizenz: [CC BY-SA 3.0](http://creativecommons.org/licenses/by-sa/3.0/)

# Aufgabe 2 (3 Punkte)

* physische Geometrie (keine Optimierung im Controller)
* Wie ist die Anordnung der Daten im besten Fall und im schlechtesten Fall?
* Rechnet genau (Runden nur im letzten Schritt, KiB vs. kB)
* 7200 Umdrehungen pro **Minute**

# Aufgabe 3 (3 Punkte)

## Warteschlangen

* Datenrate 10000 **Byte**/s
* Wie lange dauert das Senden eines Zeichens?
* pauschal 5 ms zum Auffüllen
    * Ein Byte oder hundert? $\rightarrow$ egal
    * Was vorher im Puffer war, kann gleichzeitig gesendet werden, neue Daten erst nach Ablauf der Auffüllzeit
* Wie lange muss pausiert werden, während die Warteschlange wieder aufgefüllt wird?
* Welche Datenrate ergibt sich? (B/s angeben)
* Optimale minimale LWM? (nur ganze Bytes!)

<!--  LocalWords:  
 -->

<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
