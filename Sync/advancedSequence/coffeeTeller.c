/*******************************************************************************
* File:     coffeTeller.c
* Purpose:  simple sequence with semaphores
* Course:   bsy
* Author:   M. Thaler, 2011
* Revision: 5/2012, 7/2013
* Version:  v.fs19
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#include "commonDefs.h"

//******************************************************************************

int main(void) {

    int      i;
    sem_t    *coin, *coffee, *ready;

    // set up a semaphore
    coin   = sem_open(COIN_SEMAPHOR,   0);
    coffee = sem_open(COFFEE_SEMAPHOR, 0);
    ready  = sem_open(READY_SEMAPHOR,  0);

    // start teller machine
    printf("\nCoffee teller machine starting\n\n");

    i = 0;
    while (i < ITERS) {
        printf("teller (%d): waiting for coin\n", i);
        // $ set ready
        sem_post(ready);
        for (int j = 1; j <= NUM_COIN; ++j) {
            // $ wait for coin
            sem_wait(coin);
            printf("       (%d): got coin %d\n", i, j);
        }
        printf("       (%d): dispense coffee\n", i);
        // $ set coffee
        sem_post(coffee);
        i++;
    }
}

//******************************************************************************
