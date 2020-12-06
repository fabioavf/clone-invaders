// --------------------------------------------------------------------------
//   Clone Invaders!
// --------------------------------------------------------------------------
//   Autor: Fabio Amorelli Vieira Filho
// 
//   Jogo feito como projeto para a disciplina Programação Embarca (ECOP04 e
//   ECOP14) na Unifei, com orientação dos professores Rodrigo Maximiano An-
//   tunes de Almeida e Otávio de Souza Martins Gomes.
//
// --------------------------------------------------------------------------

#define CLR 0x01
#define ON  0x0F

// frequencia do cristal

#define _XTAL_FREQ 8

#define TITLE_WAIT 18000

// tamanho virtual da tela

#define HEIGHT 8
#define WIDTH 16

#define NUM_ALIENS 16

// caracteres personalizados

#define        NAVE 0
#define   NAVE_TIRO 1
#define  TIRO_BAIXO 2
#define   TIRO_ALTO 3
#define      ALIEN1 4
#define      ALIEN2 5
#define ALIEN1_TIRO 6
#define ALIEN2_TIRO 7

#include <xc.h>
#include "bits.h"
#include "config.h"
#include "io.h"
#include "keypad.h"
#include "lcd.h"
#include "ssd.h"
#include "timer.h"
#include "title.h"
#include "objects.h"

struct Object player, aliens[16];
unsigned int keyCount = 0, contadorLoop = 0, speed = 30;
unsigned int key, aliensLeft, level = 1, score = 0;
unsigned char i = 0, j = 0, k = 0;
unsigned char screenBuffer[HEIGHT / 2][WIDTH];

void playerInput();
void updateScreen();
void gameLogic();
void setupLevel(unsigned int lvl);
void gameOver();
void youWin();

void main(void) {
    char customChars[64] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0E, 0x1B, // 0 - nave
        0x00, 0x04, 0x04, 0x00, 0x00, 0x04, 0x0E, 0x1B, // 1 - nave com tiro
        0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, // 2 - tiro baixo
        0x00, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, // 3 - tiro alto
        0x0A, 0x15, 0x0E, 0x11, 0x00, 0x00, 0x00, 0x00, // 4 - alien 1
        0x0A, 0x15, 0x0E, 0x0A, 0x00, 0x00, 0x00, 0x00, // 5 - alien 2
        0x0A, 0x15, 0x0E, 0x11, 0x00, 0x04, 0x04, 0x00, // 6 - alien 1 com tiro
        0x0A, 0x15, 0x0E, 0x0A, 0x00, 0x04, 0x04, 0x00, // 7 - alien 2 com tiro
    };

    lcdInit();
    ssdInit();
    kpInit();
    timerInit();

    lcdCommand(ON);
    lcdCommand(0x0C);

    lcdCommand(0x40); // Inicializa caracteres personalizados
    for (i = 0; i < 64; i++) {
        lcdChar(customChars[i]);
    }

    titleScreen();

    lcdCommand(0x01); // clear screen e coloca o cursor na posição (0, 0)

    setupLevel(level);

    for (;;) {
        playerInput();
        updateScreen();
        gameLogic();
    }
}

void playerInput() {
    kpDebounce();

    if (kpRead() != key || keyCount > 8) {
        key = kpRead();
        keyCount = 0;

        if (bitTst(key, 3)) { // move a esquerda
            if (player.x > 0) {
                player.x--;
            }
        }

        if (bitTst(key, 7)) { // move a direita
            if (player.x < WIDTH - 1) {
                player.x++;
            }
        }

        if (bitTst(key, 2)) { // atira
            player.projectileAlive = 1;
            player.projX = player.x;
            player.projY = player.y - 1;
        }


    } else keyCount++;
}

void updateScreen() {
    for (i = 0; i < HEIGHT / 2; i++) { // preenche o buffer com espaços
        for (j = 0; j < WIDTH; j++) {
            screenBuffer[i][j] = ' ';
        }
    }

    for (i = 0; i < NUM_ALIENS; i++) { // preenche o buffer com aliens em seus estados de animação
        if (aliens[i].isAlive) {
            screenBuffer[aliens[i].y / 2][aliens[i].x]
                    = aliens[i].state ? ALIEN1 : ALIEN2;
        }
    }

    for (i = 0; i < NUM_ALIENS; i++) { // preenche o buffer com os tiros dos aliens
        if (aliens[i].projectileAlive) {
            if ((aliens[i].x == aliens[i].projX) && (aliens[i].projY == 1) && (aliens[i].isAlive) && i < 8) {
                screenBuffer[aliens[i].projY / 2][aliens[i].projX]
                        = aliens[i].state ? ALIEN1_TIRO : ALIEN2_TIRO;
            } else if ((aliens[i].x == aliens[i].projX) && (aliens[i].projY == 3) && (aliens[i].isAlive)) {
                screenBuffer[aliens[i].projY / 2][aliens[i].projX]
                        = aliens[i].state ? ALIEN1_TIRO : ALIEN2_TIRO;
            } else if ((player.x == aliens[i].projX) && (aliens[i].projY == player.y - 1)) {
                screenBuffer[aliens[i].projY / 2][aliens[i].projX] = NAVE_TIRO;
            } else {
                screenBuffer[aliens[i].projY / 2][aliens[i].projX]
                        = (aliens[i].projY % 2) ? TIRO_BAIXO : TIRO_ALTO;
            }
        }
    }

    if (player.isAlive) { // preenche o buffer com a nave
        screenBuffer[player.y / 2][player.x] = NAVE;
    }

    if (player.projectileAlive) { // preenche o buffer com os tiros da nave
        if (player.projY == (player.y - 1)) {
            screenBuffer[player.projY / 2][player.projX] = NAVE_TIRO;
        } else {
            screenBuffer[player.projY / 2][player.projX]
                    = (player.projY % 2) ? TIRO_BAIXO : TIRO_ALTO;
        }
    }

    for (i = 0; i < HEIGHT / 2; i++) { // printa todo o buffer
        lcdPosition(i, 0);

        for (j = 0; j < WIDTH; j++) {
            lcdChar(screenBuffer[i][j]);
        }
    }
    
    // atualiza display de 7 segmentos com o score

    ssdDigit((score / 1) % 10, 3);
    ssdDigit((score / 10) % 10, 2);
    ssdDigit((score / 100) % 10, 1);
    ssdDigit((score / 1000) % 10, 0);

    ssdUpdate();
}

void gameLogic() {
    if (player.projectileAlive) { // atualiza tiro da nave e verifica colisões com aliens
        if (player.projY == 0) {
            player.projectileAlive = 0;
        } else {
            player.projY -= 1;
        }

        for (i = 0; i < NUM_ALIENS; i++) {
            if (player.projX == aliens[i].x && player.projY == aliens[i].y && aliens[i].isAlive) {
                aliens[i].isAlive = 0;
                score += 10 * level;
            }
        }
    }

    for (i = 0; i < NUM_ALIENS; i++) { // verifica colisões dos tiros dos aliens com a nave
        if (aliens[i].projectileAlive) {
            if (aliens[i].projY = 7) {
                aliens[i].projectileAlive = 0;
            } else {
                aliens[i].projY -= 1;
            }

            if (aliens[i].projX == player.x && aliens[i].projY == player.y) {
                player.isAlive = 0;
                gameOver();
            }
        }
    }

    aliensLeft = 0;

    for (i = 0; i < NUM_ALIENS; i++) { // verifica numero de aliens vivos
        if (aliens[i].isAlive) {
            aliensLeft++;
        }
    }

    if (contadorLoop == 0) {
        contadorLoop = speed;

        for (i = 0; i < NUM_ALIENS; i++) { // movimentação dos aliens
            if (aliens[i].isAlive) {
                if (i < 8) {
                    if (aliens[i].state) {
                        aliens[i].x -= 1;
                        aliens[i].state = 0;
                    } else {
                        aliens[i].x += 1;
                        aliens[i].state = 1;
                    }
                } else {
                    if (aliens[i].state) {
                        aliens[i].x += 1;
                        aliens[i].state = 0;
                    } else {
                        aliens[i].x -= 1;
                        aliens[i].state = 1;
                    }
                }

                if (rand() % 100 < 8 && !aliens[i].projectileAlive) { // tiro dos aliens
                    aliens[i].projX = aliens[i].x;
                    aliens[i].projY = aliens[i].y + 1;
                    aliens[i].projectileAlive = 1;
                }
            }
        }
    } else contadorLoop--;

    if (!aliensLeft && level < 10) { // condição para subir de nivel
        setupLevel(level + 1);
    } else if (!aliensLeft && level == 10) { // vitoria
        youWin();
    }
}

void setupLevel(unsigned int lvl) { // rotina de setup de todos as variaveis necessarias para o inicio de cada nivel
    level = lvl;

    player.x = WIDTH / 2;
    player.y = 7;
    player.isAlive = 1;

    player.projX = WIDTH / 2;
    player.projY = 6;
    player.projectileAlive = 0;

    for (i = 0; i < NUM_ALIENS; i++) {
        if (i < 8) {
            aliens[i].x = 1 + 2 * i;
            aliens[i].y = 0;
            aliens[i].projX = 1 + 2 * i;
            aliens[i].projY = 1;
            aliens[i].isAlive = 1;
            aliens[i].state = 1;
            aliens[i].projectileAlive = 0;
        } else {
            aliens[i].x = 2 * (i - 8);
            aliens[i].y = 2;
            aliens[i].projX = 2 * (i - 8);
            aliens[i].projY = 3;
            aliens[i].isAlive = 1;
            aliens[i].state = 1;
            aliens[i].projectileAlive = 0;
        }
    }

    speed = 30 - lvl * 2;

    aliensLeft = NUM_ALIENS;
}

void gameOver() {
    lcdCommand(0x01);

    lcdStr("|--------------|");
    lcdPosition(1, 0);
    lcdStr("| Voce perdeu! |");
    lcdPosition(2, 0);
    lcdStr("| Score = ");
    lcdNumber(score);
    lcdStr(" |");
    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for (;;);
}

void youWin() {
    lcdCommand(0x01);

    lcdStr("|--------------|");
    lcdPosition(1, 0);
    lcdStr("| Voce venceu! |");
    lcdPosition(2, 0);
    lcdStr("| Score = ");
    lcdNumber(score);
    lcdStr(" |");
    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for (;;);
}