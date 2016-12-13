# Musterlösung Übungsblatt 5, Aufgabe 1

a) Code-Segment (ermitteln z. B. mit `disassemble`)

~~~~
      0x0040054c-0x0040057c
      0x0040057d-0x004005e5
~~~~

b) Stacksegment (nachvollziehen der Aufrufe mit indirekter Adressierung)

~~~~
     -0x18(%rbp) = 0x7fffffffdf60 - 0x18 
                 = 0x7fffffffdf48
     -0x8(%rbp)  = 0x7fffffffdf60 - 0x08 
                 = 0x7fffffffdf58
~~~~

   genutzt werden also die Adressbereiche

~~~~
     0x7fffffffdf48-0x7fffffffdf4b
     0x7fffffffdf58-0x7fffffffdf5b
~~~~

# Musterlösung Übungsblatt 5, Aufgabe 1

c) Zeichenkette `"factorial(%lu) = %lu\n"` im Datensegment
   $\rightarrow$ `mov $0x40069c, %edi`  
   (21 Bytes plus terminierendes Nullbyte.)

~~~~
     0x40069c-0x4006b1
~~~~

d) $PA = PF0 + PF \cdot PS + PO$, wobei  
   $PF0 = 0x1000000, PS = 0x1000$

# Musterlösung Übungsblatt 5, Aufgabe 1

* 0x00400**54c**—0x00400**5e5** $\rightarrow$ 0x53d354c—0x53d35e5  
  Page: 1024  
  Page-Frame: 17363 (0x43d3)
  
* 0x7fffffffd**f48**—0x7fffffffd**f4b** $\rightarrow$ 0x1004f48—0x1004f4b  
  0x7fffffffd**f58**—0x7fffffffd**f5b** $\rightarrow$ 0x1004f58—0x1004f5b  
  Page: 34359738365  
  Page-Frame (frei wählbar): 4 (0x4)

* 0x400**69c**-0x400**6b1** $\rightarrow$ 0x53d369c—0x53d36b1  
  Page: 1024  
  Page-Frame: 17363 (0x43d3)

# Musterlösung Übungsblatt 5, Aufgabe 2

  $\left\lceil\frac{33696325\mathrm{B}}{512\mathrm{B}}\right\rceil = 65814$  Datenblöcke  
  zzgl. Verwaltungsinformationen

\begin{columns}[c]
  \begin{column}[c]{.25\textwidth}
  \begin{figure}
     \includegraphics[height=.7\textheight]{pic/ext3-bloecke_markiert.pdf} 
  \end{figure}
  \end{column}
  
  \begin{column}[c]{.75\textwidth}
  {\scriptsize
  \begin{tabular}{rll}
  1 & Inode & zehn Datenblöcke\\
  1 & einfach indirekt & 128 Datenblöcke\\
  1 + 128 & zweifach indirekt & $128^2$ Datenblöcke\\
  1 + 4 + 386 & dreifach indirekt & $3 \cdot 128^2 + 128 + 12$\\

  \hline
  522 & \multicolumn{2}{l}{Inodes/Indirektblöcke}
  \end{tabular}\\
  \vspace{2em}

  \textbf{$\rightarrow 522 + 65814$ = 66336 Blöcke auf der Platte}
  }
  \end{column}
\end{columns}

# Musterlösung Übungsblatt 5, Aufgabe 3

## open("...nikolaus.avi"):

nacheinander Lesen der Inodes und Datenblöcke für Verzeichnisse, bis
Inode 12783 von `nikolaus.avi` ermittelt ist

## open("...meta"):

nacheinander Lesen der Inodes und Datenblöcke für Verzeichnisse, bis
Inode 112 von `meta` ermittelt ist

## lseek():

Verschieben des Positionszeigers

# Musterlösung Übungsblatt 5, Aufgabe 3 {.shrink}

## read():
Zugriff auf Inode 12783 von `nikolaus.avi` zum Ermitteln des Datenblocks $\left\lfloor\frac{12572911}{512}\right\rfloor = 24556$

- Block 24556 befindet sich in der Dreifach-indirekt-Struktur
- Laden des Dreifach-indirekt-Blocks von der Festplatte
- Laden des ref. zweifach-indirekt-Blocks $\left\lfloor\frac{8034}{128^2}\right\rfloor = 0$
- Laden des ref. einfach-indirekt-Blocks $\left\lfloor\frac{8034}{128^2}\right\rfloor = 62$
- 512 Bytes aus Datenblock lesen, auf den Eintrag 98 zeigt
- 512 Bytes aus Datenblock lesen, auf den Eintrag 99 zeigt  
  ...
- 512 Bytes aus Datenblock lesen, auf den Eintrag 105 zeigt

# Musterlösung Übungsblatt 5, Aufgabe 3

## write():

- Zugriff auf Inode 112 von `meta`
- Anlegen des ersten Datenblocks.
- Schreiben von 512 B in ersten Datenblock.
- Anlegen des zweiten Datenblocks.
- Schreiben von 512 B in zweiten Datenblock.  
  ...
- Anlegen des achten Datenblocks.
- Schreiben von 512 B in achten Datenblock.


# Übungsblatt 7 (Abgabe: 19.12.2016)

Diesmal: **6 Punkte** insgesamt.

## Aufgabe 1 (3 Punkte)

* Pseudo-Code.
* Container nutzt wohl verkettete Listen.
* Erzeuger stellt neues Produkt in das Lager ein, erhöht globalen Zähler.
* Verbraucher nehmen Produkt aus dem Lager heraus, wenn verfügbar,
  verringern Zähler.
* Verbraucher tun irgendetwas mit „ihrem“ Produkt.

# Aufgabe 2 (3 Punkte)

* Pseudo-Assemblercode
* alle Instruktionen sind atomar
* Ausführung ist single-threaded, *busy waiting*
* Algorithmus soll gegenseitigen Ausschluss von zwei Threads gewährleisten
  * nein: ein Gegenbeispiel genügt
  * ja: gute Argumentation notwendig
* wenn ja: welche Schwäche(n) hat der Algorithmus dennoch?


<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
