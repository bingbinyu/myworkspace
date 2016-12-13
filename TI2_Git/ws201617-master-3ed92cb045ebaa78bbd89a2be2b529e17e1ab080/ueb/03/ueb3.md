# Aufgabe 1 (4 Punkte)

Eine Benutzerin gibt in ihrer Shell das Kommando „`ls -lR / >ausgabe`“
ein. Während der Prozess läuft, drückt sie die Tastenkombination
**Strg-Z**, um den Prozess anzuhalten. Sie setzt ihn anschließend mit
dem Shell-Kommando `bg` im Hintergrund fort. Nach einiger Zeit ist das
Kommando fertig, und das Ergebnis wurde vollständig in die Datei mit
dem Namen „ausgabe“ geschrieben.

Beschreibt kurz, an welchen Stellen Traps, Interrupts oder Signale
ausgelöst werden (sollten mehrere gleichartige Ereignisse unmittelbar
aufeinander folgen, könnt ihr diese zusammenfassend
beschreiben). Welche Zustandsänderungen werden dadurch für die hier
beteiligten Prozesse bewirkt?

# Aufgabe 2 (2 Punkte)

Schreibt ein einfaches C++-Programm mit dem Namen `sigserver`, das
mittels `sigaction` einen Handler für das Signal `SIGUSR1`
installiert. In eurem Signalhandler soll die Nummer des empfangenen
Signals ausgegeben werden sowie die Prozess-ID und die User-ID des
sendenden Prozesses. Nach dem Setzen des Signalhandlers soll euer
Programm in einer Endlosschleife mittels `pause` auf eingehende
Signale warten.

Hinweis: Benutzt in eurer Lösung die Variante `sa_sigaction` zum
Setzen eures Handlers, d. h. `sa_flags` muss auf `SA_SIGINFO` gesetzt
werden (siehe `man sigaction`).

# Aufgabe 3 (4 Punkte)

Ein hypothetischer Scheduler verwendet den folgenden Algorithmus (an
den vorgestellten allgemeinen UNIX-Scheduler angelehnt):

* Scheduling findet alle 200 ms statt (d. h. die
  ermittelten Prioritäten bleiben für diese Zeitspanne gültig).
* Gibt ein Prozess seine Zeitscheibe vorzeitig ab, so kommt
  sofort der Prozess mit der nächstbesten Priorität (ermittelt zu
  Beginn der betreffenden Zeitscheibe) an die Reihe.
* Jeder Prozess hat ein CPU-Konto, das folgendermaßen
  verwaltet wird: Bei jedem Lauf des Schedulers wird die in der soeben
  vergangenen Zeitscheibe für diesen Prozess verbrauchte CPU-Zeit in
  Prozent (der Zeitscheibe mit der Länge 200 ms) auf das Konto
  aufgeschlagen.  Anschließend wird der aktuelle Kontostand halbiert 
  (ein ggf. auftretender Nachkommaanteil für den Kontostand und die
  prozentuale Nutzung wird jeweils abgeschnitten).
* Die Priorität eines Prozesses errechnet sich als Summe aus
  der (voreingestellten) Basispriorität (*nice*-Wert zwischen 0
  und 100) und dem aktuellen CPU-Kontostand (nach dem Halbieren).  Je
  kleiner der ermittelte Wert ist, desto höher ist die Priorität.

Fragen hierzu:

a) Zu welchen unangenehmen Effekten würde dieser
  Scheduling-Algorithmus führen, wenn der CPU-Kontostand der Prozesse
  nicht nach jeder Zeitscheibe halbiert würde?
b) A und B sind immer lauffähige Prozesse.  A hat die
  Basispriorität 56, B dagegen die Basispriorität 10.  Wann laufen
  diese Prozesse?  Berechnet eine Tabelle für die ersten zwölf Zeitscheiben
  der Laufzeit. Lässt das Ergebnis eine Regelmäßigkeit erkennen? Wenn
  ja: welche?
c) A und B sind immer lauffähige Prozesse. A hat die Basispriorität 0.
   Ab welcher Basispriorität würde B die CPU niemals erhalten?
d) A hat die Basispriorität 0, B die Basispriorität 15.  A ist
   immer lauffähig.  B ist ein Backupprogramm, das im Hintergrund den
   gesamten Inhalt eines Dateisystems auf Band sichern soll. Die dazu
   genutzte Systemfunktion `write` blockiert nach jedem Aufruf solange,
   bis eine bestimmte Datenmenge erfolgreich geschrieben worden ist.
   Vereinfacht soll angenommen werden, dass B nach jedem Aufwachen
   55 ms arbeitet und dann den nächsten `write`-Aufruf absetzt. Dieser
   blockiert B jeweils für 250 ms. Wie sieht das Scheduling für
   die ersten zwölf Zeitscheiben aus?


<!--  LocalWords:  
 -->

<!-- Local Variables: -->
<!-- coding: utf-8 -->
<!-- ispell-local-dictionary: "german-new8" -->
<!-- End: -->
