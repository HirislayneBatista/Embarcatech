## Desafio 1 - Teclado Matricial:
Controle de LED RGB por meio de um teclado matricial.

  ✓ Pressionando as teclas 1, 4, 7 e “*” acenda o Led Vermelho;
  
  ✓ Pressionando as teclas 2, 5, 8 e 0 acenda o Led Verde;
  
  ✓ Pressionando as teclas 3, 6, 9 e “#” acenda o Led Azul;
  
  ✓ Pressionando as teclas A, B, C e D e nenhum Led deve acender;

## Desafio 2 - Cofre Digital:
Controle de um cofre digital por meio de uma senha de 4 dígitos. 

✓ Requisitos Funcionais:
- Leitura e Validação da Senha: Capturar a senha de 4 dígitos utilizando um teclado matricial e compará-la com a senha predefinida do cofre.

- Controle de Acesso e Bloqueio: Se a senha for correta, acionar o LED verde indicando que o cofre está aberto; Se a senha for incorreta, piscar o LED vermelho para indicar erro. Após três tentativas incorretas consecutivas,
entrar em um modo de bloqueio temporário, desativando o sistema por alguns segundos.

✓ Funções auxiliares: 
- Função de Leitura do Teclado: Captura a tecla pressionada e retorna o número correspondente.

- Função de Exibição no Display: Mostra os dígitos no display correspondente, utilizando multiplexação para alternar entre os displays.

- Função de Validação de Senha: Compara a senha digitada com a senha correta.

- Função de Bloqueio Temporário: Impede novas entradas por um determinado tempo após três tentativas incorretas.
