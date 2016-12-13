show__Fm:
	pushq	%rbp            ; %rbp auf Stack sichern
	movq	%rsp, %rbp      ; aktuellen Stackpointer nach %rbp
	subq	$16, %rsp       ; neuen Stackframe reservieren
	movq	%rdi, -8(%rbp)  ; Argument n auf Stack sichern
	movq	-8(%rbp), %rax  ; n nach %rax uebertragen
	movq	%rax, %rsi      ; und nach %rsi
	leaq	cout(%rip), %rdi ; Adresse von cout als Argument fuer __ls__
	call	__ls__7ostreamm ; Operator << aufrufen
	movl	$32, %esi       ; ' ' nach %esi
	movq	%rax, %rdi      ; und Ergebnis von Operator << als Argument fuer ls
	call	__ls__7ostreamc ; Operator << aufrufen
	ret
