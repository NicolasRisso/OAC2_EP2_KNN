.data
# Caminhos dos arquivos
xtrain: .asciiz "F:/Projects/UnityHub/OAC2-EP1-KNN/MIPS/data/xtrain.txt"
ytrain: .asciiz "F:/Projects/UnityHub/OAC2-EP1-KNN/MIPS/data/ytrain.txt"
xtest: .asciiz "F:/Projects/UnityHub/OAC2-EP1-KNN/MIPS/data/xtest.txt"

#Vetores para efetuar as operações
vetXTrain: .space 18432 # espaço = 576 linhas x 8 valores por linha x 4 bytes por valor
  .align 2
vetYTrain: .space 6000 # espaço = 576 linhax x 1 valor por linha x 4 bytes por valor
  .align 2
vetXTest: .space 6144 #espaço = 192 linhax x 8 valores por linha x 4 bytes por valor
  .align 2
ytest: #AKA SAIDA
    .space 768 #4 Bytes(Float) x Tamanho do Array
    
#Armazenar o conteúdo
spaceX: .space 17040
spaceY: .space 10000
spaceT: .space 17000

#Armazenar qtdeLinhas
XtestLines: .word 0
YtrainLines: .word 0
XtrainLines: .word 0
YtestLines: .word 0

ytestFileName: .asciiz "F:/Projects/UnityHub/OAC2-EP1-KNN/MIPS/ytest.txt"

closer_dist: .float 10000000
closer_class: .float -1

newline: .asciiz " | "   # Definição da string de nova linha
newline2: .asciiz "\n"
newlinecomplete: .asciiz "=============================\n"

file_error_msg: .asciiz "Erro ao abrir o arquivo"

zero_float: .float 0
infinity: .float 10000000

string1: .asciiz "1.0"
string0: .asciiz "0.0"

float1: .float 1.0

# utilitários
zero: .float 0.0
dez: .float 10.0
#para escrever o arquivo em strings
A: .asciiz "1.0\n"
B: .asciiz "0.0\n"
#para ler o arquivo e criar um array de floats
classeA: .float 1.0
classeB: .float 0.0

#UTILIZADO PARA DEBUGGAR
closerlist: #Apagar dps, mas é útil para debugar
    .space 1536 # 4 Bytes(Float) x Tamanho do Array (1° float: distância, 2° float: classe)
closerlistSize: .word 192

.text

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
    
    

    la $a1, vetXTrain
    la $a2, vetYTrain
    la $a3, vetXTest
    jal chamaknn
    
    la $t0, ytest #salvar a caralha do xtest no registrador
    li $t1, 0 #0 -> inicio do array
    lw $a1, YtestLines #24 Floats
    jal print
    
    jal saida
    
    li $v0, 10
    syscall
#---------------------LEITURA--------------------------------------

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
 
#---------------------PRINT--------------------------------------

#PrintLista(Lista[$t0], indexDoPrimeiroPrint[$t1], TamanhoDaLista[$a1]) 

print:
    li $t2, 4 #4 bytes
    mul $t3, $t1, $t2 #mover para o bit atual
    add $t3, $t0, $t3
    l.s $f12, 0($t3)

    li $v0, 2
    syscall

    #QUEBRA DE LINHA
    li $v0, 4         # Código do sistema para imprimir string
    la $a0, newline   # Endereço da string de quebra de linha
    syscall

    addi $t1, $t1, 1
    blt $t1, $a1, print

    move $t2, $ra	# Armazena o retorno da função principal em $t2 (ele eh reiniciado no começo do print, entao nao tem problema)
    jal printlinha
    move $ra, $t2	#Devolve o retorno da main para $ra
    jr $ra
    
printlinha:
    li $v0, 4         # Código do sistema para imprimir string
    la $a0, newlinecomplete   # Endereço da string de quebra de linha
    syscall
    jr $ra

#---------------------KNN--------------------------------------

#$t0, $t2, $t6: contador do yloop, xloop e (xtrain e xtest) respectivamente
#$t1, $t3: tem o tamanho do yloop, xloop,
#$a1, $a3, $a2, $t7: xtrain, xtest, ytrain e ytest (respectivamente)
#$3: lista de Distancias e Classes (closerlist)
#$s1, $s2: Utilizados para armazenar temporariamente o retorno de outras funções
#$f0, $f1, $f2, $f3: utilizados para armazenar temporariamente nos calculos de float
   
chamaknn:
    # Inicializa o contador do primeiro loop
    li $t0, 0  # $t0 é o contador do primeiro loop
    la $t7, ytest #endereço do vetor que salva o resultado da classificação
    la $s0, closerlist
    
    l.s $f5, closer_dist #Menor distancia

first_loop:
    # Verifica se o contador do primeiro loop atingiu 192 (pontos que serão testados)
    li $t1,192## (((se quiser testar menos linhas para conferir mude aqui))
    beq $t0, $t1, first_loop_end  # Se igual a 192, saia do primeiro loop
    la $a3, vetXTest #mv inicio do vetor para t5 Xtest 
    mul $t9, $t0, 32 #multiplica o contador do loop externo(referente tamanho de xTest) por 32 para atualizar a linha a ser comparada
    add $a3,$a3,$t9 # ponteiro para a linha de teste analisada
    mul $t9, $t0, 4
    la $t7, ytest
    add $t7, $t7, $t9
    la $s0, closerlist
    add $s0, $s0, $t9
    la $a1, vetXTrain #mv inicio do vetor para a1 Xtrain
    # Inicializa o contador do segundo loop
    li $t2, 0  # $t2 é o contador do segundo loop

second_loop:
    # Verifica se o contador do segundo loop atingiu 576
    li $t6, 0
    l.s $f0, zero_float
    li $t3, 576
    beq $t2, $t3, second_loop_end  # Se igual a 576, saia do segundo loop
	
    # Coloque o código a ser executado durante cada iteração do segundo loop aqui
    move $s2, $ra
    jal knn
    move $ra, $s2
    #j calcula
    # Incrementa o contador do segundo loop
    addi $t2, $t2, 1

    # Volta para o início do segundo loop
    j second_loop

second_loop_end:
    # Incrementa o contador do primeiro loop
    addi $t0, $t0, 1
    sw $v0, 0($s0) #Salva a classe (int)
    l.s $f5, infinity
    # Volta para o início do primeiro loop
    j first_loop

first_loop_end:
    # Aqui, o primeiro loop termina após 192 iterações e o segundo loop é executado para cada iteração do primeiro loop   	
    jr $ra

#Calcula a menor distancia e da o retorno como a classe em int em $v0
knn:
    l.s $f2, 0($a1) # salva 'inicio' de xtrain 
    l.s $f3, 0($a3) #salva 'inicio' de xtest
    
    sub.s $f1, $f2, $f3
    mul.s $f1, $f1, $f1 #Elevando ao 2
    add.s $f0, $f0, $f1 #Armazena em $f0 o total
    
    addi $a1, $a1, 4
    addi $a3, $a3, 4
    addi $t6, $t6, 4
    
    bne $t6, 32, knn #32 = 8 x 4
   
    sqrt.s $f0, $f0
    addi $a3, $a3, -32 # volta a posição 0 da linha analisada de Xtest
    c.lt.s $f0, $f5
    bc1t alocarmenor
    jr $ra

alocarmenor:

    mov.s $f5, $f0
    mul $s6,$t2,4 # pega a posição referente aos 576 linhas do ytrain
    add $a2, $a2, $s6 #adiciona ao inicio do vetor de ytrain
    l.s $f6, 0($a2) #carrega o valor da classe em f6
    sub $a2, $a2, $s6 #subtrain a posição referência para voltar para o inicio do vetor de ytrain
    s.s $f6, 0($t7) #salva / atualiza a classe no vetor Yteste
    l.s $f2, 0($a2)
    
    cvt.w.s $f0, $f0  # Convert $f0 to a 32-bit integer
    mfc1 $v0, $f0

    jr $ra

#---------------------SAIDA--------------------------------------

saida:
    # Abrir o arquivo para escrita
    li $v0, 13  # Código do sistema para abrir arquivo (13 para escrever)
    la $a0, ytestFileName  # Carrega o endereço da string do nome do arquivo
    li $a1, 1            
    syscall
    
    move $s6, $v0
    
    la $t0 ytest
    lw $t1 YtestLines
    
    l.s $f14, float1
    
    j write_loop

write_loop:
    # Carrega um valor do array
    lwc1 $f12, 0($t0)

    c.eq.s $f12, $f14 # if f12 == 1.0
    bc1t write1

    # Escreve a string no arquivo
    li $v0, 15  # Código do sistema para escrever string
    move $a0, $s6 
    la $a1, string0
    li $a2, 3
    syscall
        
    # Atualiza o endereço do array
    addi $t0, $t0, 4

    # Decrementa o contador
    sub $t1, $t1, 1
    bnez $t1, call_loop  # Se o contador não for zero, continue o loop

    # Fechar o arquivo
    li $v0, 16  # Código do sistema para fechar o arquivo
    move $a0, $s6
    syscall

    jr $ra
    
write1:
    # Escreve a string no arquivo
    li $v0, 15  # Código do sistema para escrever string
    move $a0, $s6 
    la $a1, string1
    li $a2, 4
    syscall

    addi $t0, $t0, 4
    sub $t1, $t1, 1
    bnez $t1, call_loop  # Se o contador não for zero, continue o loop

    # Fechar o arquivo
    li $v0, 16  # Código do sistema para fechar o arquivo
    move $a0, $s6
    syscall

    jr $ra

call_loop:
    li $v0, 15  # Código do sistema para escrever string
    move $a0, $s6 
    la $a1, newline2
    li $a2, 1
    syscall
    
    j write_loop
