# Aufgabe 1 (3 Punkte)

Das folgende Stück Pseudo-Code zeigt ein typisches
Erzeuger/Verbraucher-Szenario:

\lstinputlisting[]{vorgabe/einseitig.pseudo}

a) Wo könnten in diesem Programm Probleme durch nebenläufige
   Ausführung auftreten?
b) Schützt die entsprechenden Stellen (ausschließlich) mit
   den Pseudo-Code-Funktionen `lock()` und `unlock()`.

Hinweise: Kritische Abschnitte müssen so klein wie möglich gehalten
werden, um die nebenläufige Ausführung nicht unnötig einzuschränken.
Die Funktion `sell()` dient hier nur zur Illustration und ist intern
ohne ungeschützte kritische Abschnitte implementiert, über die
Implementierung von `storage` ist nur bekannt, dass intern verkettete
Listen verwendet werden.

# Aufgabe 2 (3 Punkte)

Die folgende Funktion `lock` (mit zugehörigem `unlock`) in
Assembler-Pseudocode[^1] soll den gegenseitigen Ausschluss zwischen
genau zwei Threads sichern. Es gibt zwei globale Variablen `A` und
`B`, die initial auf den Wert 1 gesetzt sind.

[^1]: Es wird nur ein Allzweckregister zur Zeit verwendet, daher ist
dieses implizites Argument für `LOAD`, `STORE`, `NOT` und
`BNEZ`/`BEQZ`.  Die Instruktionen `BNEZ` und `BEQZ` verzweigen zu der
angegebenen Sprungmarke, wenn der Registerinhalt gleich null
bzw. ungleich null ist.

~~~~
    # Thread A                      # Thread B
    lock:                           lock:                   
            LOAD    A                       LOAD    B       
            NOT                             NOT             
            STORE   A                       STORE   B       
            BNEZ    lock                    BNEZ    lock    
            LOAD    B                       LOAD    A       
            BEQZ    lock                    BEQZ    lock    
            RET                             RET             
                                                            
    unlock:                         unlock:                 
            LOAD    1                       LOAD    1       
            STORE   A                       STORE   B       
            RET                             RET      
~~~~

Untersucht, ob die Funktion `lock` den gegenseitigen Ausschluss auf
einem quasiparallel arbeitenden System mit einer CPU und nur einem
CPU-Kern gewährleistet. Warum? Welche Schwächen hat sie?

Begründet Eure Aussagen auf der Basis der Pseudo-Assemblerbefehle,
wobei ihr alle Instruktionen als atomare Operationen ansehen
dürft. Ihr braucht nur Verzahnungen zu betrachten, die für das
Ergebnis relevant sind. Bildet sinnvoll zusammenhängende
Befehlsblöcke.

<!--  LocalWords:  
 -->

<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
