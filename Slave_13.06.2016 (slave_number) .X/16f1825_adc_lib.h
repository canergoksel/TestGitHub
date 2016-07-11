void adc_init(){
    
    FVRCON = 0b11000010;  // Vref+ = 2.048V
    
    ADCON1bits.ADFM     = 1;     // Right justified
    ADCON1bits.ADCS     = 0b110; // FOSC/64 conversion clock
    ADCON1bits.ADNREF   = 0;     // Vref- is connected to Vss
    ADCON1bits.ADPREF   = 0b11;  // Vref+ is connected to FVR
    __delay_us(10);
    ADCON0bits.ADON     = 1;     // ADC is enable
    ADCON0bits.GO_nDONE = 0;     // Conversion is not in progress
                     
}

void adc_pin_select(int pin_number){
    
    switch(pin_number){
        case 0 :
            ADCON0 = 0b00000001;
            break ;
        
        case 1 :
            ADCON0 = 0b00000101;
            break ;
            
        case 2 :
            ADCON0 = 0b00001001;
            break ;
            
        case 3 :
            ADCON0 = 0b00001101;
            break ;
            
        case 4 :
            ADCON0 = 0b00010001;
            break ;
            
        case 5 :
            ADCON0 = 0b00010101;
            break ;
            
        case 6 :
            ADCON0 = 0b00011001;
            break ;
           
        case 7 :
            ADCON0 = 0b00011101;
            break ;
            
        
    }
    
   
                  
}

int adc_read(){
    int adc_value;
    
    ADCON0bits.GO_nDONE = 1;
    __delay_us(10);
    adc_value = (ADRESH<<8) +ADRESL; 
    
    return adc_value;
           
}