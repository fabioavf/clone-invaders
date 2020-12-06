# Clone Invaders: um Space Invaders feito para PICgenios com PIC18F4520

Como requisitado, esse é um relatório demonstrando os passos que tomei para fazer o Clone Invaders, num modelo Instructables.

## Passo 1: Conhecimento necessário

Para fazer esse jogo, você precisa ter conhecimento de todo o funcionamento básico da linguagem C e precisa conhecer o
funcionamento da PICgenios e do PIC18F4520. Estudar os _datasheets_, especificamente o do HD44780, também é necessário.

## Passo 2: Planejamento do jogo

Nesse passo, você deve fazer um _sketch_ de como será o funcionamento de seu jogo. Como serão as _sprites_? Como funcionará a
_gameplay_? No que o _hardware_ te limita ao fazer esse jogo?

Nesse passo e em mais alguns, tive muita ajuda seguindo esse [guia](https://www.instructables.com/LCD-Invaders-a-Space-Invaders-Like-Game-on-16x2-LC/),
que detalha a criação de um clone de Space Invaders num display LCD 16x2. As diferenças, no meu caso, foram que usei o HD44780 16x4
e a plataforma do desenvolvimento também foi totalmente diferente. 

De todo modo, foi antes de começar a fazer o código que pensei mais ou menos como seria meu jogo e já fiz os modelos das _sprites_ do jogo (infelizmente limitadas
a 8 pela plataforma).

## Passo 3: Adaptação da biblioteca `lcd.h`

No meu caso, tive uma biblioteca `lcd.h` bastante básica com apenas as funções necessárias para seu funcionamento. Desenvolver
o jogo com funções tão _barebones_ seria desnecessariamente difícil, então criei algumas funções. 

![lcd.h](https://i.imgur.com/fF29f0W.png)

Criei as funções `lcdNumber`, `lcdStr`, `lcdStrDelay` e `lcdPosition`. `lcdNumber` imprime números inteiros de valor até 9999. `lcdStr` imprime uma _string_ ao invés de
_char_ por _char_. `lcdStrDelay` faz o mesmo, só que com um pequeno _delay_ entre cada letra. Essa função foi usada apenas na tela de título do jogo.
`lcdPosition` posiciona o cursor na posição pedida.

O _datasheet_ do HD44780 foi especialmente útil para isso, pois tive de adaptar o conhecimento teórico das aulas, que era limitado a um display 16x2, para
poder programar num display 16x4.

![Funções de lcd.c](https://i.imgur.com/wQJQQaf.png)

## Passo 4: Processamento do _input_

Essa parte me deu bastante dor de cabeça por um tempo, porque estava processando o _input_ de uma forma ineficiente e, toda vez que apertava uma tecla,
a nave se mexia em várias unidades de uma vez. Vou simplificar as coisas e mostrar apenas o que funcionou.

![Input do Usuário](https://i.imgur.com/fIfpqh5.png)

Desse modo, o movimento da nave é dado uma unidade por vez. A função da variável `keyCount` é tornar o movimento repetível ao segurar a tecla de movimento
por um intervalo definido de tempo.

## Passo 5: Lógica do jogo

É aqui que se define toda a lógica de colisões, morte de aliens (ou jogador) e os tiros dos aliens. Me inspirei bastante no _instructables_ mencionado
anteriormente, mas também implementei minhas próprias funções e alterei bastante o código para se adequar às minhas necessidades. 

![Lógica pt. 1](https://i.imgur.com/koWuGac.png)
![Lógica pt. 2](https://i.imgur.com/4CFEpBf.png)

## Passo 6: Atualização da tela

Uma das partes mais importantes de um jogo é o seu visual. É como ele vai ser interpretado e jogado. Nessa parte, também me inspirei muito no _instructables_ mencionado lá
em cima, principalmente na ideia do _buffer_. Uma das minhas primeiras versões da atualização da tela era em tempo de execução, ou seja, cada objeto era
atualizado à medida que era processado. O display ficava todo irregular e confuso devido a isso. Com o _buffer_, todas as informações são guardadas numa
matriz e, feito todo o processamento, elas são impressas na tela. Assim, a atualização dos objetos passou a ser sempre consistente. Foi aqui que também entrou a atualização
do display de 7 segmentos com o _score_.

![Atualização da Tela pt. 1](https://i.imgur.com/JVKqTY4.png)
![Atualização da Tela pt. 2](https://i.imgur.com/au8WRF8.png)

## Passo 7: Inicialização do nível e retoques finais

Por fim, é necessário definir todas as variáveis iniciais necessárias para o funcionamento do jogo, além da definição de velocidade com o nível e a inicialização
dos aliens. Isso foi responsabilidade da função `setupLevel`.

![setupLevel](https://i.imgur.com/9k5aVWx.png)

Depois disso, apenas alguns retoques finais são necessários. No meu caso, fiz a tela de título, a tela de vitória e a tela de derrota. Todas essas fazem parte apenas da interface do jogo e não têm função de jogabilidade. Essa parte, especificamente, é dependente somente de sua criatividade.

## Conclusões finais

Claro que o meu desenvolvimento desse jogo não foi separado em passos e linear dessa forma. O jogo teve várias versões, que foram sendo incrementadas à medida que eu incorporava mais recursos. Precisei estudar o funcionamento do _display_ e, também, toda a lógica de um jogo. A função desse guia é te ajudar a chegar nesse caminho mais rapidamente sem cometer os erros que eu tive que cometer.

Foi bastante desafiador aprender todo esse conteúdo num período tão curto de tempo, mas também foi extremamente gratificante ver, de pouco em pouco, meu projeto tomando forma.

Agradeço fortemente a oportunidade aos professores Rodrigo e Otávio, da Unifei.

Espero que esse guia seja de alguma ajuda para alguém!
