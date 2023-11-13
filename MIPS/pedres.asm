.data
  # Caminhos dos arquivos
  xtrain: .asciiz "F:/Projects/UnityHub/OAC2-EP1-KNN/MIPS/data/xtrain.txt"
  ytrain: .asciiz "F:/Projects/UnityHub/OAC2-EP1-KNN/MIPS/data/ytrain.txt"
  xtest: .asciiz "F:/Projects/UnityHub/OAC2-EP1-KNN/MIPS/data/xtest.txt"
  
  # Armazenar o conteúdo
  spaceX: .space 17040
  spaceY: .space 10000
  spaceT: .space 17000
  
  #armazenar qtdeLinhas
  XtestLines: .word 0
  YtrainLines: .word 0
  XtrainLines: .word 0
  YtestLines: .word 0
  
  
  # Vetores para efetuar as operações
  vetXTrain: .space 18432 # espaço = 576 linhas x 8 valores por linha x 4 bytes por valor
  .align 2
  vetYTrain: .space 6000 # espaço = 576 linhax x 1 valor por linha x 4 bytes por valor
  .align 2
  vetXTest: .space 6144 #espaço = 192 linhax x 8 valores por linha x 4 bytes por valor
  .align 2
  vetYTest: .space 1000 #espaço = 192 linhax x 1 valor por linha x 4 bytes por valor
  .align 2
  
  # utilitários
  zero: .float 0.0
  dez: .float 10.0
  #para escrever o arquivo em strings
  A: .asciiz "1.0\n"
  B: .asciiz "0.0\n"
  #para ler o arquivo e criar um array de floats
  classeA: .float 1.0
  classeB: .float 0.0
  
.text

.globl main

main:
  # Carregar xtest
  la $a0, xtest
  la $t5, spaceT
  li $t6, 17000
  la $s0, vetXTest
  jal carrega
  sw $t4, XtestLines
  
  # Carregar xtrain
  la $a0, xtrain
  la $t5, spaceX
  li $t6, 17000
  la $s0, vetXTrain
  jal carrega
  sw $t4, XtrainLines
  
  # carregar ytrain
  la $a0, ytrain
  la $t5, spaceY
  li $t6, 10000
  la $s1, vetYTrain
  jal carregay
  sw $t4, YtrainLines

  li $v0, 10  # Encerre o programa
  syscall

carrega:
  li $a1, 0
  li $v0, 13 
  syscall
  
  move $t8, $v0 #salva o endereço do descritor em $t7 para fechar o arquivo posteriormente
  
  move $a0, $t8
  li $v0, 14 
  move $a1, $t5
  add $a2, $a2, $t6
  syscall
  
  move $t0, $a1 #possui a string
  lwc1 $f0, zero
  lwc1 $f1, dez #multiplicador/divisor
  move $a0, $s0 #$a0 deve conter o vetor que está em $t7
  aloca:
    lb $t1, ($t0) #o valor do primeiro caractere da string 1 $t1 = 49
    lwc1 $f2, zero
    lwc1 $f3, zero
    lwc1 $f4, zero
    lwc1 $f5, zero
    lwc1 $f6, zero
  analisa:
    li $t4, 1
    beq $t1, 10, quebraLinha
    beq $t1, 46, decimal
    beq $t1, 44, proximo
    beq $t1, $zero, fim
    beq $t1, 3, fim
    beq $t1, 13, quebraLinha
    sub $t1, $t1, 48
    mtc1 $t1, $f2
    cvt.s.w $f2, $f2 # o valor está em float
  continua:
      addi $t0, $t0, 1
      lb $t1, ($t0)
      beq $t1, 10, proximo
      beq $t1, 44, proximo
      beq $t1, 13, proximo
      beq $t1, 46, decimal
      beq $t1, 0, fim
      beq $t1, 3, fim
      sub $t1, $t1, 48
      mtc1 $t1, $f3
      cvt.s.w $f3, $f3 # o valor está em float
      mul.s $f2, $f2, $f1
      add.s $f2, $f2, $f3
      j continua
  
  
  decimal:
    li $t7, 1 #contador de casas decimais
    addi $t0, $t0, 1
    lb $t1, ($t0)
    beq $t1, 44, proximo
    beq $t1, 10, proximo
    sub $t1, $t1, 48
    mtc1 $t1, $f4
    cvt.s.w $f4, $f4
    div.s $f4, $f4, $f1
    
    loop_decimal:
      addi $t0, $t0, 1
      lb $t1, ($t0)
      beq $t1, 44, proximo
      beq $t1, 10, proximo
      li $t9, 0 #vezes que o loop de divisao deve iteragir
      addi $t7, $t7, 1
      sub $t1, $t1, 48
      mtc1 $t1, $f5
      cvt.s.w $f5, $f5
      loop_divisao:
        beq $t9, $t7, continua_decimal
        div.s $f5, $f5, $f1
        addi $t9, $t9, 1  
        j loop_divisao
      continua_decimal:
      add.s $f4, $f4, $f5
      j loop_decimal
      
  quebraLinha:
  addi $t0, $t0, 1
  j aloca
  
  proximo:
    addi $t4, $t4, 1 # +1 linha
    add.s $f7, $f2, $f4
    li $t1, 4

    div $a0, $t1
    mfhi $t1




    sub $a0, $a0, $t1

  aligned:

    s.s $f7, 0($a0)
    l.s $f13, 0($a0)
    
    addi $a0, $a0, 4
    addi $t0, $t0, 1
    
    j aloca
  
  fim:
    addi $t4, $t4, 1
    add.s $f7, $f2, $f4
  
  # Armazenar o valor convertido em vetXTrain
    s.s $f7, 0($a0)
  # Carregar o valor de vetXTrain para $f13
    li $v0, 16
    move $a0, $t8
    syscall
    jr $ra


    
  # código para ler/escrever os arquivos y
carregay:
  li $a1, 0
  li $v0, 13 
  syscall
  
  move $t8, $v0 #salva o endereço do descritor em $t7 para fechar o arquivo posteriormente
  
  move $a0, $t8
  li $v0, 14 
  move $a1, $t5
  add $a2, $a2, $t6
  syscall
  
  move $t0, $a1 # $t0 possui a string
  lwc1 $f11, classeA #recebe o valor 1.0
  lwc1 $f10, classeB #recebe o valor 0.0
  move $a0, $s1 #$a0 deve conter o vetor que está em $t7
  li $t4, 1
  leitura:
  lb $t1, ($t0)
  beq $t1, 0, fim2
  beq $t1, 3, fim2
  beq $t1, 49, classe1 #possui o valor 1.0
  beq $t1, 48, classe2 #possui o valor 0.0
  addi $t4, $t4, 1
  li $t9, 3
  addi $t0, $t0, 1
  loop_next_line:
    beq $t1, 10, leitura
    beq $t1, 0, fim2
    beq $t1, 3, fim2
    addi $t0, $t0, 1
    lb $t1, ($t0)
    j loop_next_line
  
  classe1:
    li $t1, 4
    div $a0, $t1
    mfhi $t1
    sub $a0, $a0, $t1
    
    s.s $f11, 0($a0)
    l.s $f13, 0($a0)
    addi $a0, $a0, 4
    addi $t0, $t0, 1
    j leitura
    
    
  classe2:
    li $t1, 4
    div $a0, $t1
    mfhi $t1
    sub $a0, $a0, $t1
    
    s.s $f10, 0($a0)
    l.s $f13, 0($a0)
    addi $a0, $a0, 4
    addi $t0, $t0, 1
    j leitura
  
  fim2:
    li $v0, 16
    move $a0, $t8
    syscall
    jr $ra
    
