.data
  # Caminhos dos arquivos
  xtrain: .asciiz "F:/Projects/UnityHub/OAC2-EP1-KNN/MIPS/data/xtrain.txt"
  ytrain: .asciiz "F:/Projects/UnityHub/OAC2-EP1-KNN/MIPS/data/ytest.txt"
  xtest: .asciiz "F:/Projects/UnityHub/OAC2-EP1-KNN/MIPS/data/xtest.txt"
  ytest: .asciiz "xtest.txt"

  
  # Armazenar o conteúdo
  spaceX: .space 17040
  spaceY: .space 1500
  spaceT: .space 17000
  
  # Vetores para efetuar as operações
  vetXTrain: .space 18432 # espaço = 576 linhas x 8 valores por linha x 4 bytes por valor
  .align 2
  vetYTrain: .space 2304 # espaço = 576 linhax x 1 valor por linha x 4 bytes por valor
  .align 2
  vetXTest: .space 6144 #espaço = 192 linhax x 8 valores por linha x 4 bytes por valor
  .align 2
  vetYTest: .space 768 #espaço = 192 linhax x 1 valor por linha x 4 bytes por valor
  .align 2
  
  # utilitários
  separador: .asciiz ", "
  separador2: .asciiz "\n ------------------------------------------------------------------------------------ \n"
  zero: .float 0.0
  dez: .float 10.0
  
.text

.globl main

main:
  # Carregar xtest
  la $a0, xtest
  la $t5, spaceT
  li $t6, 17000
  la $s0, vetXTest
  jal carrega
  
  # Carregar xtrain
  la $a0, xtrain
  la $t5, spaceX
  li $t6, 17000
  la $s0, vetXTrain
  jal carrega
   
  # chamar a função knn e passar os devivos parâmetros
  # Carrega o endereço dos vetores xtrain, ytrain e xtest em $a1, $a2 e $a3, respectivamente
  la $a1, xtrain
  la $a2, ytrain
  la $a3, xtest

  # Chama a função knn
  #jal knn
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
      beq $t1, 13, quebraLinha
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
 
    add.s $f4, $f4, $f6
    j decimal
  
    prox2:
      mul.s $f6, $f6, $f1
      mul.s $f6, $f6, $f1
      add.s $f4, $f6, $f0 #multiplica duas casas e coloca o valor em f4
      lwc1 $f6, zero
      j decimal
    prox1:
      mul.s $f6, $f6, $f1
      add.s $f5, $f6, $f0 #multiplica uma casa e coloca o valor em f5
      add.s $f4, $f5, $f4
      lwc1 $f6, zero
      j decimal
      
quebraLinha:
  addi $t0, $t0, 1
  j aloca
  
proximo:
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
    add.s $f7, $f2, $f4  
  # Armazenar o valor convertido em vetXTrain
    s.s $f7, 0($a0)
  # Carregar o valor de vetXTrain para $f13
    li $v0, 16
    move $a0, $s0
    syscall
    jr $ra