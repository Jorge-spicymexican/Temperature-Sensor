/*
Rerun.c
Jorge Jesus Jurado-Garcia
Purpose_intefsce an analog sensor and button turn toggle data reporting

Hardware required:
 *Launchpad with LM34

Modified 01/09/2020 by Jorge Jurado to use MSP432 Register operations
Modified 01/10/2020 by Jorge Jurado to run in Code composer studio
 */

/*  BEGINNER LAB - Write a program that lights up 8 LEDs, one at a time, in order, for 1 second each.
    You must do this efficiently in your code: do not use 8 separate if/else statements or a long case statement.
 */

#include "msp432.h"
#include "ee1910delay.h"
#include "stdio.h"
#include "ee1910analog.h"

#define LB 0X02
#define RB 0X10
/////////////////////////////////////////////////////////////

void main(void){
    int PM = 0;
    analogSetup();
    int RT = analogRead();

    P1-> DIR &= ~(LB|RB);
    P1-> REN |= (LB|RB);
    P1-> OUT |= (LB|RB);

    while(1){
        int CT = analogRead();

        int z = 0.0806*CT;

        while( (P1->IN & RB)==0){
                PM = 1-PM;
                printf("Print mode On\n");

                analogWrite(0,0);

                analogWrite(1,0);

                analogWrite(2,0);
            }
        if( (P1->IN & LB)==0){

            RT=CT;

        }
        if(PM>0){
            printf("The temperature is %d\n", (z));
        } else {

            if((CT-RT)<-50){

                analogWrite(0,0);

                analogWrite(1,0);

                analogWrite(2,100);

                delay(500);
            }

            if( (CT-RT)>-50 && (CT-RT)<0){

                analogWrite(0,0);

                analogWrite(1,(100+2*(CT-RT)));

                analogWrite(2,(-2*(CT-RT)));

                delay(500);
            }

            if( (CT-RT)>0 && (CT-RT)<50){

                analogWrite(0,(2*(CT-RT)));

                analogWrite(1,(100-2*(CT-RT)));

                analogWrite(2,0);

                delay(500);
            }}

        if( (CT-RT)> 50){

            analogWrite(0,100);

            analogWrite(1,0);

            analogWrite(2,0);

            delay(500);
        }


    }
}


