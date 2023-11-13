.data
  # Caminhos dos arquivos
  xtrain: .asciiz "data/xtrain.txt"
  ytrain: .asciiz "data/ytrain.txt"
  xtest: .asciiz ""  # Caminho do arquivo de teste
  ytest: .asciiz "xtest.txt"

  # Vetores para efetuar as operações
  vetXTrain: .space 18432
  vetYTrain: .space 2304
  vetXTest: .space 6144
  vetYTest: .space 768

  # Utilitários
  zero: .float 0.0
  dez: .float 10.0

.text

# Função para converter caractere numérico em ponto flutuante
# $a0: Caractere a ser convertido
# $f1: Multiplicador/divisor
converte_caractere:
  sub $a0, $a0, 48       # Converte caractere numérico para inteiro (ASCII)
  mtc1 $a0, $f2          # Copia o valor inteiro para $f2
  cvt.s.w $f2, $f2       # Converte inteiro em ponto flutuante
  div.s $f2, $f2, $f1    # Divide pelo multiplicador/divisor
  jr $ra

# Função para carregar dados de arquivo para vetor
# $a0: Caminho do arquivo
# $a1: Tamanho do espaço alocado
# $a2: Endereço do vetor
carrega_dados:
  li $v0, 13               # Abrir arquivo
  syscall
  move $s0, $v0

  move $a0, $s0
  li $v0, 14               # Ler arquivo
  li $a2, 0                # Inicializa o índice do vetor
ler_dados:
  lw $t0, 0($a0)           # Carrega um caractere
  beqz $t0, fim_leitura    # Se chegou ao fim, termina a leitura

  # Processa o caractere
  sub $t0, $t0, 48          # Verifica se é um dígito
  beqz $t0, proximo

  # Converte caractere para ponto flutuante
  jal converte_caractere
  add.s $f7, $f2, $f0       # Soma o valor convertido a $f7
  j proximo

proximo:
  # Armazena o valor no vetor
  s.s $f7, 0($a2)
  addiu $a2, $a2, 4

  j ler_dados

fim_leitura:
  # Feche o arquivo
  li $v0, 16
  move $a0, $s0
  syscall

  jr $ra

# Função principal
main:
  # Carregando dados de xtrain para vetXTrain
  la $a0, xtrain
  li $a1, 17040
  la $a2, vetXTrain
  li.s $f1, 10.0            # Defina o multiplicador/divisor para conversão
  jal carrega_dados

  # Carregando dados de ytrain para vetYTrain
  la $a0, ytrain
  li $a1, 1500
  la $a2, vetYTrain
  li.s $f1, 1.0             # Defina o multiplicador/divisor para conversão
  jal carrega_dados

  # Carregando dados de xtest para vetXTest
  la $a0, xtest
  li $a1, 17000
  la $a2, vetXTest
  li.s $f1, 10.0            # Defina o multiplicador/divisor para conversão
  jal carrega_dados

  # Carregando dados de ytest para vetYTest
  la $a0, ytest
  li $a1, 768
  la $a2, vetYTest
  li.s $f1, 1.0             # Defina o multiplicador/divisor para conversão
  jal carrega_dados

  # Resto do código aqui...

  # Saída do programa
  li $v0, 10
  syscall