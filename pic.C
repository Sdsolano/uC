/* 
 * File:   Licitacion_2c.c 
 * Author: Kbarrios3
 * 
 * 
 */
// PIC16F877A Configuration Bit Settings 

// 'C' source line config statements 

// CONFIG 
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator) 
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled) 
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled) 
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled) 
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming) 
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off) 
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control) 
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off) 
#define _XTAL_FREQ 4000000
// #pragma config statements should precede project file includes. 
// Use project enums instead of #define for ON and OFF. 

#include <xc.h> 
#include <stdio.h> 
#include<math.h>
int velocidad = 2;
////////////////////////////////////////////// 
void pasos_izquierda(void){
        PORTAbits.RA0=0;
        PORTAbits.RA1=0;
        PORTAbits.RA2=1;
        PORTAbits.RA3=1;
        __delay_ms(velocidad);
        
        PORTAbits.RA0=0;
        PORTAbits.RA1=1;
        PORTAbits.RA2=1;
        PORTAbits.RA3=0;
        __delay_ms(velocidad);
        
        PORTAbits.RA0=1;
        PORTAbits.RA1=1;
        PORTAbits.RA2=0;
        PORTAbits.RA3=0;
        __delay_ms(velocidad);
        
        PORTAbits.RA0=1;
        PORTAbits.RA1=0;
        PORTAbits.RA2=0;
        PORTAbits.RA3=1;
        __delay_ms(velocidad);
        
        

    }
    
    void pasos_derecha(void){
        PORTAbits.RA0=1;
        PORTAbits.RA1=1;
        PORTAbits.RA2=0;
        PORTAbits.RA3=0;
        __delay_ms(velocidad);
        
        PORTAbits.RA0=0                                                                         ;
        PORTAbits.RA1=1;
        PORTAbits.RA2=1;
        PORTAbits.RA3=0;
        __delay_ms(velocidad);
        
        PORTAbits.RA0=0;
        PORTAbits.RA1=0;
        PORTAbits.RA2=1;
        PORTAbits.RA3=1;
        __delay_ms(velocidad);
        
        PORTAbits.RA0=1;
        PORTAbits.RA1=0;
        PORTAbits.RA2=0;
        PORTAbits.RA3=1;
        __delay_ms(velocidad);
    }
    void pasos_off(void){
        PORTAbits.RA0=0;
        PORTAbits.RA1=0;
        PORTAbits.RA2=0;
        PORTAbits.RA3=0;
    }
    
    
    int piso=1;
    void subir_un_piso(void){
        for (int i=1;i<=650;i++){
            pasos_izquierda(); 
        }    
    }
    
    void bajar_un_piso(void){
        for (int i=1;i<=650;i++){
           pasos_derecha(); 
        }           
    }
    
    void set_speed(uint16_t speed){
        CCPR1L=(speed>>2);
        CCP1CON = (CCP1CON & 0xCF) | ((speed & 0x03)<<4);
    }
    
    
    void abrir_puerta(void){
        PORTBbits.RB0=1;
        PORTBbits.RB1=0;
    }

    void cerrar_puerta(void){
        PORTBbits.RB0=0;
        PORTBbits.RB1=1;
    }    
    
    void parar_puerta(void){
        PORTBbits.RB0=0;
        PORTBbits.RB1=0; 
    }
    
    
    void PWM_init(void){
        PR2=249;
        CCP1CON=0x0C;
        T2CON=0x06;
    }
    
    void en_piso(void){
        abrir_puerta();
        set_speed(350);
        __delay_ms(300);
        parar_puerta();
        __delay_ms(2000);
        cerrar_puerta();
        set_speed(350);
        __delay_ms(300);
        parar_puerta();
    }
    
    
void main(void) {
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    TRISA = 0x00; //todos son inputs 
    TRISB = 0x00; // Todo salidas 
    TRISC = 0x00; // Todo salidas 
    TRISD = 0xFF; // Todo entradas pulsadores 
    TRISE = 0x00; // Todo salidas 

    ADCON0 = 0x00; //Activar el ADC 
    ADCON1 = 0x06; 
    
    piso=1;

    
    PWM_init();
    
    while (1) {
        
        parar_puerta();
        pasos_off();
        if (piso==1){
            if(PORTDbits.RD0==1){
                subir_un_piso();
                en_piso();
                piso=2;
            }
            if(PORTDbits.RD1==1){
                subir_un_piso();
                subir_un_piso();
                en_piso();
                piso=3;
            }
            if(PORTDbits.RD2==1){
                subir_un_piso();
                en_piso();
                bajar_un_piso();
                piso=1;
            }
            if(PORTDbits.RD3==1){
                subir_un_piso();
                en_piso();
                subir_un_piso();
                piso=3;
            }
            
            if(PORTDbits.RD4==1){
                subir_un_piso();
                subir_un_piso();
                en_piso();
                bajar_un_piso();
                piso=2;
            }
            if(PORTDbits.RD5==1){
                subir_un_piso();
                subir_un_piso();
                en_piso();
                bajar_un_piso();
                bajar_un_piso();
                piso=1;
            } 
            
            
            
            
            
            
        }
        
        if (piso==2){
            if(PORTDbits.RD0==1){
                 bajar_un_piso();
                en_piso();
                subir_un_piso();
                piso=2;
                en_piso();
            }
            if(PORTDbits.RD1==1){
                bajar_un_piso();
                en_piso();
                subir_un_piso();
                subir_un_piso();
                piso=3;
                en_piso();
            } 

            if(PORTDbits.RD2==1){
                bajar_un_piso();
                piso=1;
                en_piso();
            }
            if(PORTDbits.RD3==1){
                subir_un_piso();
                piso=3;
                en_piso();
            }
            
            if(PORTDbits.RD4==1){
                subir_un_piso();
                en_piso();
                bajar_un_piso();
                piso=2;
                en_piso();
            }
            if(PORTDbits.RD5==1){
                subir_un_piso();
                en_piso();
                bajar_un_piso();
                bajar_un_piso();
                piso=1;
                en_piso();
            } 
            
            
            
            
            
            
            
            
        }
        
        if (piso==3){
            if(PORTDbits.RD0==1){
                bajar_un_piso();
                bajar_un_piso();
                en_piso();
                subir_un_piso();
                piso=2;
                en_piso();
            }
            if(PORTDbits.RD1==1){
                bajar_un_piso();
                bajar_un_piso();
                en_piso();
                subir_un_piso();
                subir_un_piso();
                piso=3;
                en_piso();
            }
            
            if(PORTDbits.RD2==1){
                bajar_un_piso();
                en_piso();
                bajar_un_piso();
                piso=1;
                en_piso();
            }
            
            if(PORTDbits.RD3==1){
                bajar_un_piso();
                en_piso();
                subir_un_piso();
                piso=3;
                en_piso();
            } 
            if(PORTDbits.RD4==1){
                bajar_un_piso();
                piso=2;
                en_piso();
            }
            if(PORTDbits.RD5==1){
                bajar_un_piso();
                bajar_un_piso();
                piso=1;
                en_piso();  
            } 
        }
        
        

        
    };
}
