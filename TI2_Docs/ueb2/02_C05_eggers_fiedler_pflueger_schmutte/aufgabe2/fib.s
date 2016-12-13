fib__Fm:
	pushq	%rbp            ; %rpb auf Stack sichern
	movq	%rsp, %rbp      ; alten Stackpointer nach %rbp
	pushq	%rbx            ; %rbx auf Stack sichern
	subq	$40, %rsp       ; neuen Stackframe anlegen
	movq	%rdi, -40(%rbp) ; Argument n auf Stack sichern
	movq	$1, -24(%rbp)   ; unsigned long r = 1
	cmpq	$1, -40(%rbp)   ; 
	jbe	.L2             ; n <= 1 --> L2
	movq	-40(%rbp), %rax ; n in %rax kopieren
	subq	$2, %rax        ; 2 subtrahieren
	movq	%rax, %rdi      ; und als Argument fuer fib nutzen
	call	fib__Fm         ; fib aufrufen
	movq	%rax, %rbx      ; Ergebnis von fib(n-2) in %rbx sichern
	movq	-40(%rbp), %rax ; n in %rax kopieren
	subq	$1, %rax        ; 1 subtrahieren
	movq	%rax, %rdi      ; und als Argument fuer fib nutzen
	call	fib__Fm         ; fib aufrufen
	addq	%rbx, %rax      ; Ergebnis mit Ergebnis von fib(n-2) addieren
	movq	%rax, -24(%rbp) ; und in Ergebnisvariable r speichern
.L2:
	movq	-24(%rbp), %rax ; Ergebnis vom Stack holen
	addq	$40, %rsp       ; Stackframe abraeumen
	popq	%rbx            ; %rbx wieder herstellen
	popq	%rbp            ; %rbp wieder herstellen
	ret                     ; zum Aufrufer zurueck
