
.data
  # Caminhos dos arquivos
  xtrain: .asciiz "F:\Projects\UnityHub\OAC2-EP1-KNN\MIPS\data\xtrain.txt"
  ytrain: .asciiz "F:\Projects\UnityHub\OAC2-EP1-KNN\MIPS\data\ytest.txt"
  xtest: .asciiz "F:\Projects\UnityHub\OAC2-EP1-KNN\MIPS\data\xtest.txt"
  ytest: .asciiz "xtest.txt"

  
  # Armazenar o conteúdo
  spaceX: .space 17040
  .word 0x10040000
  spaceY: .space 1500
  .word 0x10050000
  spaceT: .space 17000
  .word 0x10060000
  
  # Vetores para efetuar as operações
  vetXTrain: .space 18432 # espaço = 576 linhas x 8 valores por linha x 4 bytes por valor
  .align 2
  .word 0x10018b4c
  vetYTrain: .space 2304 # espaço = 576 linhax x 1 valor por linha x 4 bytes por valor
  .align 2
  .word 0x10010000
  vetXTest: .space 6144 #espaço = 192 linhax x 8 valores por linha x 4 bytes por valor
  .align 2
  .word 0x10020000
  vetYTest: .space 768 #espaço = 192 linhax x 1 valor por linha x 4 bytes por valor
  .align 2
  .word 0x10030000
  
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
  
  # Imprimir os valores de vetXTest
  li $t1, 100      # Inicialize o contador para 100 valores
  la $t2, vetXTest  # $t2 aponta para o início de vetXTest
  la $a0, separador # Carregue a string de separação
  
  print_xtest:
    li $v0, 2         # Use a syscall 2 para imprimir números em ponto flutuante
    lwc1 $f12, ($t2)  # Carregue o valor do vetor em $f12
    syscall

    li $v0, 4          # Use a syscall 4 para imprimir uma string (separador)
    la $a0, separador
    syscall

    addi $t1, $t1, -1  # Decrementa o contador
    beqz $t1, continue_xtest

    addi $t2, $t2, 4    # Avance para o próximo valor no vetor
    j print_xtest
    
  #separar os dois arrays
  continue_xtest:
  la $a0, separador2
  li $v0, 4
  syscall

  # Imprimir os valores de vetXTrain
  li $t1, 100       # Reinicialize o contador para 100 valores
  la $t2, vetXTrain  # $t2 aponta para o início de vetXTrain

  la $a0, separador
  
  print_xtrain:
    li $v0, 2         # Use a syscall 2 para imprimir números em ponto flutuante
    lwc1 $f12, -1($t2)  # Carregue o valor do vetor em $f12
    syscall

    li $v0, 4          # Use a syscall 4 para imprimir uma string (separador2)
    la $a0, separador
    syscall

    addi $t1, $t1, -1  # Decrementa o contador
    beqz $t1, continue_xtrain

    addi $t2, $t2, 4    # Avance para o próximo valor no vetor
    j print_xtrain

  continue_xtrain:
  
  # chamar a função knn e passar os devivos parâmetros
  # Carrega o endereço dos vetores xtrain, ytrain e xtest em $a1, $a2 e $a3, respectivamente
  la $a1, xtrain
  la $a2, ytrain
  la $a3, xtest

  # Chama a função knn
  jal knn
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
    
    
    
    
    
    
    #ideia:
    #para cada ponto de teste realizar o cálculo com os 576 pontos do train.
    #no momento que ele calcula o valor conferimos se ele é o menor valor entre os que
    # ja foram analisados e armazenamos em t5, além disso armazenamos o valor do iterador para identificar  a linha a a que se refere.
    # tendo o valor da linha referida é possivel buscar em ytrian valor a qual o ponto se refere( 0 ou 1)
    # escrever no arquivo de saída ytest 
    
    
    
knn:
    # Inicializa o contador do primeiro loop
    li $t0, 0  # $t0 é o contador do primeiro loop

first_loop:
    # Verifica se o contador do primeiro loop atingiu 192 (pontos que serão testados)
    li $t1, 192
    beq $t0, $t1, first_loop_end  # Se igual a 192, saia do primeiro loop

    # Inicializa o contador do segundo loop
    li $t2, 0  # $t2 é o contador do segundo loop

second_loop:
    # Verifica se o contador do segundo loop atingiu 576
    li $t3, 576
    beq $t2, $t3, second_loop_end  # Se igual a 576, saia do segundo loop

    # Coloque o código a ser executado durante cada iteração do segundo loop aqui
    #j calcula
    # Incrementa o contador do segundo loop
    addi $t2, $t2, 1

    # Volta para o início do segundo loop
    j second_loop

second_loop_end:
    # Incrementa o contador do primeiro loop
    addi $t0, $t0, 1

    # Volta para o início do primeiro loop
    j first_loop

first_loop_end:
    # Aqui, o primeiro loop termina após 192 iterações e o segundo loop é executado para cada iteração do primeiro loop

    # Coloque o código adicional aqui, se necessário

    # Termina o programa
    	
    jr $ra

calcula:
	#calcula a distancia entre os pontos
	