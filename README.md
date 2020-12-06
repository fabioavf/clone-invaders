# Clone Invaders!

![Imagem do Jogo](https://i.imgur.com/KUk7O5e.png)

Clone Invaders é um jogo desenvolvido como avaliação para a disciplina de Programação Embarcada
na Universidade Federal de Itajubá com orientação dos professores [Rodrigo Almeida](https://github.com/rmaalmeida) e [Otavio Gomes](https://github.com/osmgomes). O jogo é um clone do clássico "Space Invaders" e foi desenvolvido
para o software [PICSimLab](https://github.com/lcgamboa/picsimlab), que simula a placa PICgenios, com o microprocessador PIC18F4520.

Caso você queira saber o passo a passo do desenvolvimento desse jogo, dê uma olhada no [relatório](https://github.com/fabioavf/clone-invaders/blob/main/RELATORIO.md) de desenvolvimento que escrevi.

### Como jogar

Você controla a nave usando as teclas 1 e 2 do teclado matricial do PICgenios e a tecla 4 é usada para atirar. Teclas equivalentes no teclado
de seu computador também funcionam.

Toda vez que você mata todos os aliens na tela, o nível do jogo aumenta e, portanto, a dificuldade também. Os aliens passam a se mover mais rápido
e a atirar com mais frequência também. Quando você alcança o nível 10 e mata todos os aliens, você vence o jogo e vê uma tela com o seu score final.

### Compilação do Código

Para compilar o código, você precisa clonar esse repositório e importar a pasta `Projeto.X` no [MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)
com o compilador XC8. No MPLAB, você deve clicar em `Production > Clean and Build Project`.

### Como executar o jogo

Para executar o jogo, depois de compilado, basta baixar o [PICSimLab](https://github.com/lcgamboa/picsimlab), abrir o software
e clicar em `File > Load Hex` e selecionar o arquivo `Projeto.X\dist\default\production\Projeto.X.production.hex`.
