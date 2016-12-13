# Übungsblatt 2 (Abgabe: 14.11.2016)

## Aufgabe 1 (4 Punkte)

testscript.sh:
```sh
#! /usr/bin/env bash

# Argumente:
echo "$*"

if test "x$1" = "xHallo"; then
    echo "Welt!"
else
    echo "Falsch!" >&2
    exit 1
fi
```

# Aufgabe 1 (Fortsetzung)

* `chmod +x testscript.sh`

* ID3-Tag ist in den letzten 128 Bytes ($\rightarrow$ `man tail`)
* Felder enthalten Null-Bytes :-(
    * zum Glück nur am Ende: `cut -bx-y|tr -d "\000"`
* Parameter expansion ($\rightarrow$ `man bash`)
    * Dateinamen (und sonstige Argumente) können Zeichen mit Sonderbedeutung enthalten (z. B. Leerzeichen)
    * `echo "$1"` $\rightarrow$ Shell löst eine Quoting-Ebene auf
    * „Quoting Hell“
    * `printf -v VAR "...."` = „sprintf“ 

# Aufgabe 1 (Fortsetzung)

* Tracknummer
    * binär im Header
    * Umwandeln z. B. mit `od`
* Kommandos ausführen mit backtick (`` ` ``)  
  (alternative Syntax `$(...)`) 
    * `` VAR=`echo -n "bla"|tail -c1` ``

* Weitere Hilfe
    * [http://www.tldp.org/LDP/abs/html/](http://www.tldp.org/LDP/abs/html/)
    * `man bash`
       für `printf`, `for`, Variablen \dots
    * `man test`
    * `man od`
    * `man dirname`

# Aufgabe 2 (5 Punkte)

* Wdh.: Objektdateien enthalten Maschinencode der Übersetzungseinheit
    * Instruktionen im Textsegment
    * Daten im Datensegment
* Symboltabelle enthält exportierte Adressen und Abbildung auf Zeichenketten in Stringtabelle
* Text/Data Relocation Table verknüpft Text- und Datensegment mit Symboltabelle

* Vereinfachungen:
    * Assemblercode statt Maschinencode
    * alle Instruktionen sind 4 B lang
    * a.out-Header kann entfallen
    * Name-Mangling-Format aus der Vorlesung

# Objektdatei für twoton.s

<!-- [x86masm]Assembler erkennt keine Pseudoinstruktionen -->
\lstinputlisting[language={}]{twoton.s}

# Objektdatei für twoton.s

1. Interne Sprünge unmittelbar auflösen (hier vereinfacht mit relativen Sprüngen)
2. Globale Symbole
3. Woanders definiert oder unbekannt

# Interne Sprünge

\includegraphics{twoton.01}

# Interne Sprünge

\includegraphics{twoton.02}

# Interne Sprünge

\includegraphics{twoton.03}

# Globale Symbole

\includegraphics[height=.8\textheight]{symtbl_01}

# Globale Symbole

\includegraphics[height=.8\textheight]{symtbl_02}

# Globale Symbole

\includegraphics[height=.8\textheight]{symtbl_02}

# Woanders definiert oder unbekannt

\includegraphics[height=.8\textheight]{symtbl2_01}

# Woanders definiert oder unbekannt

\includegraphics[height=.8\textheight]{symtbl2_02}

# Zusammenbau durch den Linker

\includegraphics[height=.8\textheight]{linked}

# Aufgabe 3 (1 Punkt)

`gdb geheim`

* Was verrät uns `disassemble main`?
* Wo könnte ein `breakpoint` nützlich sein?  
  `b *0x123456` setzt einen Breakpoint an Adresse 123456
* ggf. aktiven Stackframe auswählen (`backtrace` und `frame`)
* Lokale Variablen anzeigen (`info locals`)

[http://darkdust.net/files/GDB Cheat Sheet.pdf](http://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)

# Beispiel: hello_world

\scriptsize{}

```
$ g++ -o hello_world -g -O0 hello_world.cc
$ rm hello_world.cc
$ gdb hello_world
...
(gdb) disassemnle main
Dump of assembler code for function main():
...
   0x0000000000400a81 <+49>:	callq  0x400a1c <show(std::string const&)>
(gdb) disassemble  show
Dump of assembler code for function show(std::string const&):
...
   0x0000000000400a49 <+45>:	callq  0x400850 <printf@plt>
(gdb) break *0x0000000000400a49
Breakpoint 1 at 0x400a49: file hello_world.cc, line 7.
```

# Beispiel: hello_world

\scriptsize{}
```
...
(gdb) run
Starting program: /tmp/hello_world 

Breakpoint 1, 0x0000000000400a49 in show (s=...) at hello_world.cc:7
7	hello_world.cc: No such file or directory.
(gdb) disassemble
Dump of assembler code for function show(std::string const&):
...
   0x0000000000400a44 <+40>:	mov    $0x0,%eax
=> 0x0000000000400a49 <+45>:	callq  0x400850 <printf@plt>
   0x0000000000400a4e <+50>:	leaveq 
   0x0000000000400a4f <+51>:	retq   
End of assembler dump.
```

# Beispiel: hello_world

\scriptsize{}
```
(gdb) x/s $rsi
0x602028:	 "Hallo"
(gdb) info locals
zeichenkette = 0x602028 "Hallo"
(gdb) p zeichenkette
$3 = 0x602028 "Hallo"
(gdb) x 0x602028 
0x602028:	 "Hallo"
(gdb) set {char}0x602028 = 'W'
(gdb) set {char}0x602029 = 'e'
(gdb) set {char}0x60202b = 't'
(gdb) set {char}0x60202c = 0
(gdb) p zeichenkette
$4 = 0x602028 "Welt"
(gdb) continue
Welt
[Inferior 1 (process 30929) exited normally]
```

<!--  LocalWords:  
 -->

<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
