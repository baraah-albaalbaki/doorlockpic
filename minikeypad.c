#include <p18F4550.h>
#pragma code main = 0x800
#define _XTAL_FREQ 20000000UL

#include <delays.h>
#include <timers.h>

#define servo PORTEbits.RE1

#define RS PORTCbits.RC0
#define EN PORTCbits.RC1

#define R1 PORTBbits.RB0
#define R2 PORTBbits.RB1
#define R3 PORTBbits.RB2
#define R4 PORTBbits.RB3

#define C1 PORTBbits.RB4
#define C2 PORTBbits.RB5
#define C3 PORTBbits.RB6
#define C4 PORTBbits.RB7

void init_port(void);
void init_lcd(void);
void send_command(unsigned char cmd);
void send_letter(unsigned char letter);
void send_word(char *str);
void delay(void);

char Check_Col1(int m);
char Check_Col2(int m);
char Check_Col3(int m);
char Check_Col4(int m);

void servoRotate0(void);
void servoRotate90(void);
void servoRotate180(void);

int i = 0;
int j = 0;
int k = 0;
int y = 0;
int t = 0;
char user [4];
//const char p[] = "WELCOME";

void main() {
    init_port();
    init_lcd();

    while (1) {
        send_letter('E');
        send_letter('N');
        send_letter('T');
        send_letter('E');
        send_letter('R');
        send_letter(' ');
        send_letter('P');
        send_letter('I');
        send_letter('N');
        send_command(0xc0); //move to the second line

        INTCON2 = 0b01111111; //pull up resistors
        C1 = C2 = C3 = C4 = 1;


        for (i = 0; i < 4; i++) {

            R1 = R2 = R3 = R4 = 0; //return them to zero when pressing one key
            while (C1 == 1 && C2 == 1 && C3 == 1 && C4 == 1);

            if (C1 == 0) {
                user[i] = Check_Col1(i);
                send_letter(user[i]);
            }
            if (C2 == 0) {
                user[i] = Check_Col2(i);
                send_letter(user[i]);
            }
            if (C3 == 0) {
                user[i] = Check_Col3(i);
                send_letter(user[i]);
            }
            if (C4 == 0) {
                user[i] = Check_Col4(i);
                send_letter(user[i]);
            }
        }
        if (user[0] == '7' && user[1] == '5' && user[2] == '3' && user[3] == '0') {
            send_command(0x01);
            send_letter('W');
            send_letter('E');
            send_letter('L');
            send_letter('C');
            send_letter('O');
            send_letter('M');
            send_letter('E');

            servoRotate180();
            send_command(0x01);
            servoRotate90();
            //Delay10KTCYx(200);

        }
        send_command(0x01);
    }

}//end main

void init_port(void) {
    ADCON1 = 0x0f;
    TRISB = 0xf0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
}

void init_lcd(void) {
    send_command(0x01); /* clear display screen */
    send_command(0x38); /* uses 2 line and initialize 5*7 matrix of LCD */
    send_command(0x0e); //display on and cursor blinking
}

void send_command(unsigned char cmd) {
    RS = 0; /* Command Register is selected */
    PORTD = cmd;
    EN = 1; /* High-to-Low pulse on Enable pin to latch data */
    delay();
    EN = 0;
    delay();
}

void send_letter(unsigned char letter) {
    RS = 1;
    PORTD = letter;
    EN = 1;
    delay();
    EN = 0;
    delay();
}

void send_word(char *str) {//pointer
    while (*str != '\0') {
        send_letter(*str);
        str++;
    }
}

void delay() {
    for (k = 0; k < 150; k++)
        for (y = 0; y < 100; y++)
            Nop();
}

char Check_Col1(int v) {
    R1 = R2 = R3 = R4 = 1;


    R1 = 0;
    if (C1 == 0) {
        while (C1 == 0);
        return ('7');

    }

    R1 = 1;

    R2 = 0;
    if (C1 == 0) {
        while (C1 == 0);
        return ('4');
    }
    R2 = 1;


    R3 = 0;
    if (C1 == 0) {
        while (C1 == 0);
        return ('1');
    }
    R3 = 1;

    R4 = 0;
    if (C1 == 0) {
        while (C1 == 0);
        return ('=');
    }
    //R4 = 1;
}

char Check_Col2(int m) {
    R1 = R2 = R3 = R4 = 1;

    R1 = 0;
    if (C2 == 0) {
        while (C2 == 0);
        return ('8');
    }
    R1 = 1;



    R2 = 0;
    if (C2 == 0) {
        while (C2 == 0);
        return ('5');
    }
    R2 = 1;


    R3 = 0;
    if (C2 == 0) {
        while (C2 == 0);
        return ('2');
    }
    R3 = 1;

    R4 = 0;
    if (C2 == 0) {
        while (C2 == 0);
        return ('0');
    }
    //R4 = 1;
}

char Check_Col3(int m) {
    R1 = R2 = R3 = R4 = 1;

    R1 = 0;
    if (C3 == 0) {
        while (C3 == 0);
        return ('9');

    }
    R1 = 1;



    R2 = 0;
    if (C3 == 0) {
        while (C3 == 0);
        return ('6');

    }
    R2 = 1;


    R3 = 0;
    if (C3 == 0) {
        while (C3 == 0);
        return ('3');
    }
    R3 = 1;

    R4 = 0;
    if (C3 == 0) {
        while (C3 == 0);
        return ('A');
    }
    //R4 = 1;
}

char Check_Col4(int m) {
    R1 = R2 = R3 = R4 = 1;

    R1 = 0;
    if (C4 == 0) {
        while (C4 == 0);
        return ('B');

    }
    R1 = 1;

    R2 = 0;
    if (C4 == 0) {
        while (C4 == 0);
        return ('C');
    }
    R2 = 1;

    R3 = 0;
    if (C4 == 0) {
        while (C4 == 0);
        return ('D');
    }
    R3 = 1;

    R4 = 0;
    if (C4 == 0) {
        while (C4 == 0);
        return ('E');
    }
    //R4 = 1;
}

void servoRotate0() //0 Degree
{
    for (j = 0; j < 50; j++) {
        servo = 1;
        Delay1KTCYx(2); //4
        Delay100TCYx(5);
        servo = 0;
        Delay1KTCYx(97); //96
        Delay100TCYx(5);
    }
}

void servoRotate90() //90 Degree
{
    for (j = 0; j < 50; j++) {
        servo = 1;
        Delay1KTCYx(7); //Delay 1.5mS
        Delay100TCYx(5);
        servo = 0;
        Delay1KTCYx(92); //Delay 18.5mS  
        Delay100TCYx(5);
        //while (1);

    }
}

void servoRotate180() //180 Degree
{

    for (j = 0; j < 50; j++) {
        servo = 1;
        Delay1KTCYx(10); //
        servo = 0;
        Delay1KTCYx(90); //
    }
}
//Delay10KTCYx(200);                   // 1 second delay
//Delay1KTCYx(500); //100ms delay
