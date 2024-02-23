
	addi 	$a0, $zero, 7	# n
	add 	$a1, $a0, $zero	# counter1
	add	$a2, $a0, $zero	# counter2
	add	$a3, $a0, $zero
		
# ************* F A C T O R I A L ************************
	beq	$a0, $zero, ifZero # 0!=1
	add	$v0, $a0, $zero	# value out first arg
factV0:
	addi	$a1, $a1, -1 #minska med 1 5-->4 sålänge det inte är 1
	beq	$a1, 1, Stop
	add	$a2, $a1, $zero #a2=4
	add	$a3, $v0, $zero	# Sparar summan 5
summa: #innreloop
	add	$v0, $v0, $a3 #addera 5+5 när på 2 plats, blir dubbel
	addi	$a2, $a2, -1 #a2---> 3 från 4
	beq	$a2, 1, factV0
	beq	$zero, $zero, summa #unconditional
ifZero:
	addi	$v0, $zero, 1
Stop:
	beq	$0, $0, Stop
	nop
