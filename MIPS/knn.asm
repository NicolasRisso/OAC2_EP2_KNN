.data
  # Caminhos dos arquivos
  xtrain: .asciiz "data/xtrain.txt"
  ytrain: .asciiz "data/ytrain.txt"
  xtest: .asciiz
  ytest: .asciiz "xtest.txt"
  
  # Armazenar o conteúdo
  spaceX: .space 17000
  spaceY: .space 1500
  spaceT: .space 17000
  
  # Vetores para efetuar as operações
  vetXTrain: .space 18432 # espaço = 576 linhas x 8 valores por linha x 4 bytes por valor
  .align 4
  vetYTrain: .space 2304 # espaço = 576 linhax x 1 valor por linha x 4 bytes por valor
  vetXTest: .space 6144 #espaço = 192 linhax x 8 valores por linha x 4 bytes por valor
  vetYTest: .space 768 #espaço = 192 linhax x 1 valor por linha x 4 bytes por valor
  
  # utilitários
  separador: .asciiz ", "
  zero: .float 0.0
  dez: .float 10.0
  
.text

carrega:
  la $a0, xtrain
  li $a1,0
  li $v0, 13 #abrir arquivo
  syscall
  
  move $s0, $v0
  
  move $a0, $s0
  li $v0, 14 
  la $a1, spaceX
  li $a2, 17000
  syscall
  
  move $t0, $a1 #possui a string
  lwc1 $f0, zero
  lwc1 $f1, dez #multiplicador/divisor
  la $a0, vetXTrain
aloca:
  lb $t1, ($t0) #o valor do primeiro caractere da string 1 $t1 = 49
  lwc1 $f2, zero
  lwc1 $f3, zero
  lwc1 $f4, zero
  lwc1 $f5, zero
analisa:
  beq $t1, 10, proximo
  beq $t1, 46, decimal
  beq $t1, 44, proximo
  beq $t1, 0, fim
  sub $t1, $t1, 48
  mtc1 $t1, $f2
  cvt.s.w $f2, $f2 # o valor está em float
  continua:
    addi $t0, $t0, 1
    lb $t1, ($t0)
    beq $t1, 10, proximo
    beq $t1, 44, proximo
    beq $t1, 46, decimal
    sub $t1, $t1, 48
    mtc1 $t1, $f3
    cvt.s.w $f3, $f3 # o valor está em float
    mul.s $f2, $f2, $f1
    add.s $f2, $f2, $f3
    j continua
  
  
decimal:
  addi $t0, $t0, 1
  lb $t1, ($t0)
  beq $t1, 44, proximo
  beq $t1, 10, proximo
  sub $t1, $t1, 48
  mtc1 $t1, $f6
  cvt.s.w $f6, $f6
  div.s $f6, $f6, $f1
  div.s $f6, $f6, $f1
  div.s $f6, $f6, $f1
  
  c.eq.s $f4, $f0
  bc1t prox2
  c.eq.s $f5, $f0
  bc1t prox1
  add.s $f4, $f4, $f5
  add.s $f4, $f4, $f6
  j decimal
  
  prox2:
    mul.s $f6, $f6, $f1
    mul.s $f6, $f6, $f1
    add.s $f4, $f6, $f0 #multiplica duas casas e coloca o valor em f4
    j decimal
  prox1:
    mul.s $f6, $f6, $f1
    add.s $f5, $f6, $f0 #multiplica uma casa e coloca o valor em f5
    j decimal

proximo:
  addi $t0, $t0, 1
  add.s $f7, $f2, $f4
  jal insere
  j aloca

insere:
  # Verifique se $a0 está alinhado em um múltiplo de 4
  andi $t1, $a0, 0x3  # Verifique os 2 bits menos significativos
  beqz $t1, aligned  # Se $a0 estiver alinhado, vá para aligned

  # Calcule o deslocamento necessário para o alinhamento
  sub $t2, $t1, 0x4
  add $a0, $a0, $t2

aligned:
  s.s $f7, 0($a0)
  addi $a0, $a0, 4
  jr $ra
fim:
  l.s $f13, 5($a0)