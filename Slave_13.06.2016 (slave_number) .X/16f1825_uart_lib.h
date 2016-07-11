void uart_init(){
    /*Pin Select*/
    APFCON0bits.RXDTSEL = 0; //RC5 Rx
    APFCON0bits.TXCKSEL = 0; //RC4 Tx
    
    /*TRANSMIT STATUS AND CONTROL REGISTER*/
    TXSTAbits.TX9       = 0; // 8-bit transmission
    TXSTAbits.TXEN      = 1; // Transmit enable
    TXSTAbits.SYNC      = 0; // Asynchronous mode
    TXSTAbits.SENDB     = 0; // Sync Break transmission completed
    TXSTAbits.BRGH      = 0; // Low speed 
    
    /*RECEIVE STATUS AND CONTROL REGISTER*/
    RCSTAbits.SPEN      = 1; // Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
    RCSTAbits.RX9       = 0; // 8-bit transmission
    RCSTAbits.CREN      = 1; // Enables receiver
    RCSTAbits.FERR      = 0; // No framing error
    RCSTAbits.OERR      = 0; // Not overrun error
    
    /*BAUD RATE CONTROL REGISTER*/
    BAUDCONbits.ABDOVF  = 1; // Auto-baud timer overflowed
    BAUDCONbits.RCIDL   = 0; // Start bit has been received and the receiver is receiving
    BAUDCONbits.SCKP    = 0; // Transmit non-inverted data
    BAUDCONbits.BRG16   = 0; // 8-bit Baud Rate Generator is used
    BAUDCONbits.WUE     = 0; // Receiver is operating normally
    BAUDCONbits.ABDEN   = 0; // Auto-Baud Detect mode is disabled
                          //////////////*Baudrate Formula*/////////////      
        /*SYNC=0,BRG16=0,BRGH=0*/       /*SYNC=0,BRG16=0,BRGH=1*/   /*SYNC=0,BRG16=1,BRGH=0*/ 
          /* FOSC/[64 (n+1)] */           /* FOSC/[64 (n+1)] */        /* FOSC/[64 (n+1)] */    
     /*SPBRG = (10^6/baudrate) - 1;*/             /*SPBRG = ((4x10^6)/baudrate) - 1;*/
    
    PIE1bits.RCIE     = 1; // Enable interrupt
    INTCONbits.GIE    = 1;
    INTCONbits.PEIE   = 1;
    
}

void baudrate(long baudrate){
    
    switch(baudrate){  
        case 9600 :
            SPBRG = 25;
            break;
    }    
   
}

void uart_write(char data){
  while(!TRMT);
  TXREG = data;
}

char uart_read(){
    while(!RCIF);
    return RCREG;
}

