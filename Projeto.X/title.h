#ifndef TITLE_H
#define TITLE_H

void titleScreen() {
    lcdPosition(0, 0);
    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|              |");

    lcdPosition(2, 0);
    lcdStr("|              |");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|             C|");

    lcdPosition(2, 0);
    lcdStr("|             I|");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|            CL|");

    lcdPosition(2, 0);
    lcdStr("|            IN|");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|           CLO|");

    lcdPosition(2, 0);
    lcdStr("|           INV|");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|          CLON|");

    lcdPosition(2, 0);
    lcdStr("|          INVA|");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|         CLONE|");

    lcdPosition(2, 0);
    lcdStr("|         INVAD|");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|        CLONE |");

    lcdPosition(2, 0);
    lcdStr("|        INVADE|");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|       CLONE  |");

    lcdPosition(2, 0);
    lcdStr("|       INVADER|");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|      CLONE   |");

    lcdPosition(2, 0);
    lcdStr("|      INVADERS|");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|     CLONE    |");

    lcdPosition(2, 0);
    lcdStr("|     INVADERS |");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|    CLONE     |");

    lcdPosition(2, 0);
    lcdStr("|    INVADERS  |");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|   CLONE      |");

    lcdPosition(2, 0);
    lcdStr("|   INVADERS   |");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    for(int i = 0; i < TITLE_WAIT; i++);
    for(int i = 0; i < TITLE_WAIT; i++);
    for(int i = 0; i < TITLE_WAIT; i++);
    for(int i = 0; i < TITLE_WAIT; i++);
    for(int i = 0; i < TITLE_WAIT; i++);

    lcdPosition(0, 0);

    lcdStr("|--------------|");

    lcdPosition(1, 0);
    lcdStr("|              |");

    lcdPosition(2, 0);
    lcdStr("|              |");

    lcdPosition(3, 0);
    lcdStr("|--------------|");

    lcdPosition(1, 2);
    lcdStrDelay("PRESS 5");

    lcdPosition(2, 2);
    lcdStrDelay("TO START...");

    unsigned int key;

    while(! bitTst(key, 6)) {
        kpDebounce();
        
        key = kpRead();
    }
}

#endif