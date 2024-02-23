
	addi 	$a0, $zero, 3	# n
	add 	$a1, $a0, $0
# ************* F A C T O R I A L ************************
	beq	$a0, $zero, ifZero # 0!=1
	add	$v0, $a0, $zero	
factorial:
	addi	$a1, $a1, -1 
	beq	$a1, 1, Stop
	mul	$v0, $a1, $v0 #factorial n*(n-1)*(n-2)....
	beq	$0, $0, factorial
ifZero:
	addi	$v0, $zero, 1
Stop:
	beq	$0, $0, Stop
