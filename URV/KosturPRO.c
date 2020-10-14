/*
    -Project name:
           Regulator (Demonstation by Kvascev & Todorov & Marjanovic)
    -Description:
           This program demonstrates simple control of temperature
           and air levitation using the basic knowledge about PI regulators
    -Test configuration:
     MCU:             P18F4520
     Dev.Board:       EasyPIC4
     SW:              mikroC PRO v5.6.1
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    D/A Converter
     Date:            20.11.2012.
*/
const char _CHIP_SELECT = 1;

char      *text = "  TEMPERATURA" ;
unsigned short int oldPlus, oldMinus, oldMode;
unsigned int  timerTicks;
//Promenljiva za upis u DAC
int write_val;

//Oznaka interrupta
int flag = 0;

int change_mode = 0;
int mode = 1; //0 rucno, 1 automatsko
int change_step = 0; // -1 za minus, 0 za neaktivno, 1 za plus
//Promenljive za LCD
int int_part, floating_point;

//Opsezi upravljanja i visine redom
int minU = 3000, maxU = 4096, minY = 0, maxY = 1023;

//Parametri za PI regulator
float Kp = 0.05, Ti = 10.0, Ts = 0.2, step = 0.5, tf = 0.1, tr = 0.1, tf_dif = 0.1;
float ref = 300.0, e=0.0, Up, Ui, Ui_old, rf = 300.0, yf = 0;
float u_man =0.0, u_auto = 0.0;
//Vrednost visine koja se ocitava sa ADC
int y;


// Lcd pinout settings
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;

// Pin direction
sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;



// Timed Interrupt on 0.02 sec
void interrupt() 
{
     flag = 1;
     timerTicks++;
     TMR1H      =   99;               // 40000 counts until overflow 40000=65535-(99*256+192)
     TMR1L      =   192;              // 40000/2000000=0.02sec on 8MHz, 2000000=8MHz/4
     T1CON      =   0x01;             // TMR1ON: Timer1 On bit 1 = Enables Timer1
     PIR1.TMR1IF=   0;                // Clear interrupt request bit
     PIE1       =   1;                // TMR1IE: TMR1 Overflow Interrupt Enable bit, 1 = Enables
     INTCON     =   0xC0;             // Interrupts enable
}


// DAC increments (0..4095) --> output voltage (0..5V)
void DAC_Output(unsigned int valueDAC) 
{
char temp;
  PORTC &= ~(_CHIP_SELECT);           // ClearBit(PORTC,CHIP_SELECT);
                                      // Prepare for data transfer
  temp = (valueDAC >> 8) & 0x0F;      // Prepare hi-byte for transfer
  temp |= 0x30;                       // It's a 12-bit number, so only
  SPI1_write(temp);                   //   lower nibble of high byte is used
  temp = valueDAC;                    // Prepare lo-byte for transfer
  SPI1_write(temp);

  PORTC |= _CHIP_SELECT;              // SetBit(PORTC,CHIP_SELECT);
}

void ispisDouble(double val, int r)
{
    int_part = val;
    floating_point = val * 10;
    floating_point = floating_point % 10;
    IntToStr(floating_point,text); LCD_Out(r,8,text);
    IntToStr(int_part,text); LCD_Out(r,6,text);
    Lcd_Chr(r, 12, '.');
    Lcd_Chr(r, 14, '%');
}

void PI()
{
    e = ref - y;
    Up = Kp*e;
    Ui = Ui+Kp*(Ts/Ti)*e;
    Ui_old = Ui;
    u_auto = Up+Ui;
    if (u_auto>100)
    {
     u_auto = 100;
     Ui = Ui_old;
    }
    if (u_auto<0)
    {
     u_auto = 0;
     Ui = Ui_old;
    }
}

void main() 
{

// Inicijalizacija portova i periferija
     ADCON1 = 0x0F;                    // Turn off A/D converters on PORTB
     TRISA  = 0xFF;                    // Set PORTA pins as input pins(to work with A/D converter)
     TRISB  = 0xFF;                    // Set PORTB pins as input pins(to work with keybord)
     TRISC &= ~(_CHIP_SELECT);         // SPI ClearBit(TRISC,CHIP_SELECT);
     TRISD  = 0x00;                    // Set PORTD pins as output pins(to work with LCD display)
     SPI1_init();                      // Initialisation of SPI communication

// inicijalizacija interapt rutine
     timerTicks =   0;
     TMR1H      =   99;               // 40000 counts until overflow 40000=65535-(99*256+192)
     TMR1L      =   192;              // 40000/2000000=0.02sec on 8MHz, 2000000=8MHz/4
     T1CON      =   0x01;             // TMR1ON: Timer1 On bit 1 = Enables Timer1
     PIR1.TMR1IF=   0;                // Clear interrupt request bit
     PIE1       =   1;                // TMR1IE: TMR1 Overflow Interrupt Enable bit, 1 = Enables
     INTCON     =   0xC0;             // Interrupts enable



// inicijalizacija i brisanje display-a
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);


//  Odavde ide korisnicki kod
     DAC_Output(0);         //spusti dole
     write_val = 0;
     while(1)
     {
        //Click plus (RB0)
        if (Button(&PORTB, 0, 1, 1)) oldPlus = 1;
        if (oldPlus && Button(&PORTB, 0, 1, 0))
        {
            change_step = 1;
            oldPlus = 0;
        }
        //Click minus (RB1)
        if (Button(&PORTB, 1, 1, 1)) oldMinus = 1;
        if (oldMinus && Button(&PORTB, 1, 1, 0)){
            change_step = -1;
            oldMinus = 0;
        }
        
        //Change mode (RB2)
        if (Button(&PORTB, 2, 1, 1)) oldMode = 1;
        if (oldMode && Button(&PORTB, 2, 1, 0)){
            change_mode = 1; //true
            mode = 1 - mode;
            oldMode = 0;
        }
        
        if(flag == 1)
        {
            y = Adc_Read(3);
            LCD_Out(1,1,"Y:");
            //ispisDouble(1.0*(y_int/1023.0)*100, 1);
            ispisDouble(100.0*(y-minY)/(maxY-minY), 1);

            if(change_step)
            {
                if(mode == 0)
                {
                    u_man = u_man + change_step * step;
                    if (u_man>100.0) u_man = 100.0;
                    if (u_man<0) u_man = 0.0;
                 }
                 else if (mode == 1)
                 {
                    //ref = ref + 1023*0.005;
                    //if (ref > 1023) ref = 1023;
                    ref += 1.0 * change_step * (maxY-minY)*step/100;
                    if(ref > maxY) ref = maxY;
                    if (ref < minY) ref = minY;
                 }
                 change_step = 0;
            }

            if (mode == 0)
            {
               if(change_mode == 1)
               {
                  u_man = u_auto + Kp*e;
                  change_mode = 0;
               }
               write_val = u_man*(maxU-minU)/100.0+minU;
               LCD_Out(2,1,"UPR:");
               ispisDouble(u_man, 2);
            }
            else if (mode == 1)
            {
                if (change_mode == 1)
                {
                    ref = y;
                    Ui = u_man - Kp*e;
                    change_mode = 0;
                }
                PI();
                write_val = u_auto*(maxU-minU)/100.0+minU;
                LCD_Out(2,1,"REF:");
                ispisDouble(100.0*(ref-minY)/(maxY-minY), 2);
            }
            DAC_Output(write_val);
            flag = 0;
        }
     }
}