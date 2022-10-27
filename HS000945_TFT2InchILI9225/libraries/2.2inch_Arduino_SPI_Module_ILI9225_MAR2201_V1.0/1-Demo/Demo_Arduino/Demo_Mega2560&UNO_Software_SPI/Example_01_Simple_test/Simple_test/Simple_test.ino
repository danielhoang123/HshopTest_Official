//This application does not rely on any libraries and it is for ILI9225

//This program is a demo of clearing screen to display black,white,red,green,blue.

//when using the BREAKOUT BOARD only and using these hardware spi lines to the LCD,
//the SDA pin and SCK pin is defined by the system and can't be modified.
//if you don't need to control the LED pin,you can set it to 3.3V and set the pin definition to -1.
//other pins can be defined by youself,for example
//pin usage as follow:
//                      CS   RS   RST   SDI   CLK   LED  VCC   GND    
//Arduino Mega2560&Uno  A5   A3   A4    A2    A1    A0   5V    GND

//Remember to set the pins to suit your display module!
/********************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE 
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/
#define LED   A0    
#define CS    A5        
#define RS    A3       
#define RESET A4
#define MOSI  A2
#define SCK   A1

void Lcd_Writ_Bus(unsigned char d)
{
   uint8_t val = 0x80;
    while(val)
    {
      if(d&val)
      {
        digitalWrite(MOSI,HIGH);
      }
      else
      {
        digitalWrite(MOSI,LOW);
      }
      digitalWrite(SCK,LOW);
      digitalWrite(SCK,HIGH);
      val >>= 1;
    }
}

void Lcd_Write_Com(unsigned char VH)  
{   
  *(portOutputRegister(digitalPinToPort(RS))) &=  ~digitalPinToBitMask(RS);//LCD_RS=0;
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Data(unsigned int VH)
{
  *(portOutputRegister(digitalPinToPort(RS)))|=  digitalPinToBitMask(RS);//LCD_RS=1;
  Lcd_Writ_Bus(VH>>8);
  Lcd_Writ_Bus(VH);
}

void Lcd_Write_Com_Data(unsigned char com,unsigned int dat)
{
  Lcd_Write_Com(com);
  Lcd_Write_Data(dat);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
  Lcd_Write_Com_Data(0x36,x2);
  Lcd_Write_Com_Data(0x37,x1);
  Lcd_Write_Com_Data(0x38,y2);
  Lcd_Write_Com_Data(0x39,y1);
  Lcd_Write_Com_Data(0x20,x1);
  Lcd_Write_Com_Data(0x21,y1); 
  Lcd_Write_Com(0x22);						 
}

void Lcd_Init(void)
{
  digitalWrite(RESET,HIGH);
  delay(5); 
  digitalWrite(RESET,LOW);
  delay(15);
  digitalWrite(RESET,HIGH);
  delay(15);

  digitalWrite(CS,LOW);  //CS

   Lcd_Write_Com_Data(0x01,0x011c);
 Lcd_Write_Com_Data(0x02,0x0100);
  Lcd_Write_Com_Data(0x03,0x1030);
  Lcd_Write_Com_Data(0x08,0x0808); // set BP and FP
  Lcd_Write_Com_Data(0x0B,0x1100); //frame cycle
  Lcd_Write_Com_Data(0x0C,0x0000); // RGB interface setting R0Ch=0x0110 for RGB 18Bit and R0Ch=0111for RGB16Bit
  Lcd_Write_Com_Data(0x0F,0x1401); // Set frame rate----0801
  Lcd_Write_Com_Data(0x15,0x0000); //set system interface
  Lcd_Write_Com_Data(0x20,0x0000); // Set GRAM Address
  Lcd_Write_Com_Data(0x21,0x0000); // Set GRAM Address
  //*************Power On sequence ****************//
  delay(50);                         // Delay 50ms
  Lcd_Write_Com_Data(0x10,0x0800); // Set SAP,DSTB,STB----0A00
  Lcd_Write_Com_Data(0x11,0x1F3F); // Set APON,PON,AON,VCI1EN,VC----1038
  delay(50);                         // Delay 50ms
  Lcd_Write_Com_Data(0x12,0x0121); // Internal reference voltage= Vci;----1121
  Lcd_Write_Com_Data(0x13,0x006F); // Set GVDD----0066
  Lcd_Write_Com_Data(0x14,0x4349); // Set VCOMH/VCOML voltage----5F60
  //-------------- Set GRAM area -----------------//
  Lcd_Write_Com_Data(0x30,0x0000);
  Lcd_Write_Com_Data(0x31,0x00DB);
  Lcd_Write_Com_Data(0x32,0x0000);
  Lcd_Write_Com_Data(0x33,0x0000);
  Lcd_Write_Com_Data(0x34,0x00DB);
  Lcd_Write_Com_Data(0x35,0x0000);
  Lcd_Write_Com_Data(0x36,0x00AF);
  Lcd_Write_Com_Data(0x37,0x0000);
  Lcd_Write_Com_Data(0x38,0x00DB);
  Lcd_Write_Com_Data(0x39,0x0000);
  // ----------- Adjust the Gamma Curve ----------//
  Lcd_Write_Com_Data(0x50,0x0001);  //0400
  Lcd_Write_Com_Data(0x51,0x200B);  //060B
  Lcd_Write_Com_Data(0x52,0x0000);  //0C0A
  Lcd_Write_Com_Data(0x53,0x0404);  //0105
  Lcd_Write_Com_Data(0x54,0x0C0C);  //0A0C
  Lcd_Write_Com_Data(0x55,0x000C);  //0B06
  Lcd_Write_Com_Data(0x56,0x0101);  //0004
  Lcd_Write_Com_Data(0x57,0x0400);  //0501
  Lcd_Write_Com_Data(0x58,0x1108);  //0E00
  Lcd_Write_Com_Data(0x59,0x050C);  //000E
  delay(50);                                     // Delay 50ms
  Lcd_Write_Com_Data(0x07,0x1017);
  Lcd_Write_Com(0x22);
    digitalWrite(CS,HIGH);
}

void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{	
  unsigned int i,j;
  digitalWrite(CS,LOW);
  Lcd_Write_Com(0x22); //write_memory_start
  //digitalWrite(RS,HIGH);
  l=l+x;
  Address_set(x,y,l,y);
  j=l*2;
  for(i=1;i<=j;i++)
  {
    Lcd_Write_Data(c);
  }
  digitalWrite(CS,HIGH);   
}

void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c)                   
{	
  unsigned int i,j;
  digitalWrite(CS,LOW);
  Lcd_Write_Com(0x22); //write_memory_start
  //digitalWrite(RS,HIGH);
  l=l+y;
  Address_set(x,y,x,l);
  j=l*2;
  for(i=1;i<=j;i++)
  { 
    Lcd_Write_Data(c);
  }
  digitalWrite(CS,HIGH);   
}

void Rect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}

void Rectf(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c)
{
  unsigned int i;
  for(i=0;i<h;i++)
  {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}

int RGB(int r,int g,int b)
{
  return r << 16 | g << 8 | b;
}

void LCD_Clear(unsigned int j)                   
{	
  unsigned int i,m;
  digitalWrite(CS,LOW);
  Address_set(0,0,175,219);
  for(i=0;i<176;i++)
    for(m=0;m<220;m++)
    {
      Lcd_Write_Data(j);
    }
  digitalWrite(CS,HIGH);   
}

void setup()
{
  pinMode(A0,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);

  digitalWrite(A0, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  
  Lcd_Init();
  
}

void loop()
{  
   LCD_Clear(0xf800);
   LCD_Clear(0x07E0);
   LCD_Clear(0x001F);
   LCD_Clear(0x0); 
  for(int i=0;i<300;i++)
  {
    Rect(random(175),random(219),random(176),random(220),random(65535)); // rectangle at x, y, with, hight, color
  }
  
//  LCD_Clear(0xf800);
}
