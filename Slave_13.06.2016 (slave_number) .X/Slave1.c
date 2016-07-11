#include "Slave_config.h" ;
#include "16f1825_uart_lib.h";
#include "16f1825_adc_lib.h";

const int slave_number = 12;

int receive_data = 0;
int data = 100;
int voltage_adc_value = 0 , temp_adc_value = 0 ;

#define LED2 LATC0 
#define LED1 LATC1 
#define Balance LATC2

void interrupt uart(void){
    if (RCIF){   
    PIR1bits.RCIF = 0;
    
    receive_data = uart_read();
    
    if(receive_data == 100 + slave_number){
        LED1 = 1; 
        Balance = 0;
        LED2 = 0;
                
        uart_write(100 + slave_number);
        uart_write(voltage_adc_value>>8);
        uart_write(voltage_adc_value>>4&0xF);
        uart_write(voltage_adc_value & 0xF);
        uart_write(100+ slave_number);
        
        uart_write(200 + slave_number);
        uart_write(temp_adc_value>>8);
        uart_write(temp_adc_value>>4&0xF);
        uart_write(temp_adc_value & 0xF);
        uart_write(200 + slave_number);
        
        LED1 = 0;    
    }
    
    if(receive_data==200 + slave_number){
        LED1 = 1; 
        Balance = 1;
        LED2 = 1;
                
        uart_write(100+ slave_number);
        uart_write(voltage_adc_value>>8);
        uart_write(voltage_adc_value>>4&0xF);
        uart_write(voltage_adc_value & 0xF);
        uart_write(100+slave_number);
        
        uart_write(200+ slave_number);
        uart_write(temp_adc_value>>8);
        uart_write(temp_adc_value>>4&0xF);
        uart_write(temp_adc_value & 0xF);
        uart_write(200+ slave_number);
        
        LED1 = 0;    
    } 
    }
}

int main(){
    
    OSCCON = 0b01111010;  //intosc 16MHz 
     
    uart_init();
    baudrate(9600);
    adc_init();
    __delay_us(10);
    
    TRISA  = 0b00010100;  //A4(an3), A2(an2) input 
    ANSELA = 0b00010100;  //A4(an3), A2(an2) analog
    PORTC  = 0x00;
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    
    
    while(1){
        
        //LED2 = 1;
        
        adc_pin_select(2);
        __delay_us(10);
        voltage_adc_value = adc_read();
         __delay_us(10);
        adc_pin_select(3);
        __delay_us(10);
        temp_adc_value = adc_read();
        __delay_us(10);
     
        
    }
}
