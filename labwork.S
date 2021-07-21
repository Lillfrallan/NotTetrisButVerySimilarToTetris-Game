  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

.global		hexasc
.global	 	delay
.global	 	time2string
.global		enable_interrupt
.data

.text
hexasc:
	andi 	$t0,$a0,0xf	# copy the value of a0 to t0
	
	ble	$t0,9,numbers	# branch to numbers if <= 9
	nop			# delay slot filler (just in case)
	ble	$t0,15,letters	# branch to letters if <= 15
	nop			# delay slot filler (just in case)
	
	numbers:
	addi	$v0,$t0,0x30	
	jr	$ra
	nop
		
	letters:
	addi	$v0,$t0,0x37
	jr	$ra
	nop
	
old_delay:
	jr	$ra
	nop

delay:
	move	$t0,$a0		# ms
	li	$t2,4450	# limit for i
	
	while:
	beq	$t0,$0,end_while
	nop
	addi	$t0,$t0,-1
	li	$t1,0		# i = 0

	loop:
	beq	$t1,$t2,end_loop
	nop
	addi	$t1,$t1,1
	j	loop
	nop
	
	end_loop:
	j	while
	nop
	
end_while:
	jr	$ra
	nop

time2string:
	PUSH	$s1
	PUSH	$s0
	PUSH	$ra
	move	$s0,$a0
	move	$s1,$a1

# oneties minutes
	andi	$t1,$s1,0xf000
	srl	$a0,$t1,12
	jal	hexasc
	nop
	sb	$v0,0($s0)
# single minutes
	andi	$t1,$s1,0x0f00
	srl	$a0,$t1,8
	jal	hexasc
	nop
	sb	$v0,1($s0)
# colon sign
	li	$t1,0x3a
	sb	$t1,2($s0)
# oneties seconds
	andi	$t1,$s1,0x00f0
	srl	$a0,$t1,4
	jal	hexasc
	nop
	sb	$v0,3($s0)
# single seconds
	andi	$a0,$s1,0x000f
	jal	hexasc
	nop
	sb	$v0,4($s0)
# null
	li	$t1,0x00
	sb	$t1,5($s0)

	POP	$ra
	POP	$s0
	POP 	$s1
	
	jr	$ra
	nop

enable_interrupt:
	ei
	jr	$ra
	nop
