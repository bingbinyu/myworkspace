main:
	pushq	%rbp            ; %rbp auf Stack sichern
	movq	%rsp, %rbp      ; Stackpointer nach %rbp kopieren
	subq	$32, %rsp       ; neuen Stackframe anlegen
	movl	%edi, -20(%rbp) ; argc auf Stack sichern
	movq	%rsi, -32(%rbp) ; argv auf Stack sichern
	cmpl	$1, -20(%rbp)
	jle	.L2             ; argc <= 0? --> .L2
	movq	-32(%rbp), %rax ; argv nach %rax
	addq	$8, %rax        ; 8 aufaddieren (LP64!)
	movq	(%rax), %rax    ; argv[1] nach %rax
	movl	$10, %edx       ; 10 als drittes Argument von strtol
	movl	$0, %esi        ; NULL als zweites Argument von strtol
	movq	%rax, %rdi      ; erstes Argument von strtol setzen
	call	strtol          ; und strtol aufrufen
	movq	%rax, -16(%rbp) ; Ergebnis von strtol (n) auf Stack sichern
	movq	$0, -8(%rbp)    ; lokale Variable i mit 0 initialisieren
.L4:
	movq	-8(%rbp), %rax  ; i nach %rax
	cmpq	-16(%rbp), %rax ; mit n vergleichen
	ja	.L3             ; i > n? --> .L3
	movq	-8(%rbp), %rax  ; i nach %rax kopieren
	movq	%rax, %rdi      ; und als Argument fuer fib setzen
	call	fib__Fm         ; fib aufrufen
	movq	%rax, %rdi      ; Ergebnis von fib als Argument fuer show
	call	show__Fm        ; und show aufrufen
	addq	$1, -8(%rbp)    ; i um 1 erhöhen
	jmp	.L4             ; nach .L4 springen
.L3:
	movq	endl__F7ostream(%rip), %rax ; Adresse von endl nach %rax
	movq	%rax, %rsi      ; und als Argument fuer cout setzen
	leaq	cout(%rip), %rdi ; Adresse von cout als Argument fuer __ls__
	call	__ls__7ostreamm ; Operator << aufrufen
.L2:
	movl	$0, %eax        ; Rueckgabewert 0 setzen
	ret                     ; und zum Aufrufer zurueckkehren
