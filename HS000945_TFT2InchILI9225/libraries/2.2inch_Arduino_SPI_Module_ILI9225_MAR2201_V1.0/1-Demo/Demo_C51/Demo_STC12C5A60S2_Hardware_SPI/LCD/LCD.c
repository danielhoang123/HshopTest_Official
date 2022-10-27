//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STC12C5A60S2,晶振12M  单片机工作电压3.3V
//QDtech-TFT液晶驱动 for C51
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/8/22
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
//********************************************************************************
//=========================================电源接线================================================//
//5V接DC 5V电源
//GND接地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为SPI
//液晶屏模块            单片机
//  SDI          接       P15        //SPI写信号
//=======================================液晶屏控制线接线==========================================//
//液晶屏模块            单片机
//  CS           接       P13       //片选控制信号
//  RST          接       P33       //复位信号
//  RS           接       P12       //数据/命令选择控制信号
//  CLK          接       P17       //SPI时钟信号
//  LED          接       P32       //背光控制信号，如果使用STC89C52RC单片机或者不需要控制，接3.3V
//=========================================触摸屏接线=========================================//
//STC89C52RC单片机ROM太小，无法运行带触摸功能的程序，所以触摸屏不需要接线
//不使用触摸或者模块本身不带触摸，则可不连接
//触摸屏使用的数据总线类型为SPI
//触摸屏模块            单片机
//  T_CLK        接       P36       //触摸屏SPI时钟信号
//  T_CS         接       P37       //触摸屏片选控制信号
//  T_DIN        接       P34       //触摸屏SPI写信号
//  T_DO         接       P35       //触摸屏SPI读信号
//  T_IRQ        接       P40       //触摸屏响应检查信号，如单片机无P4组，请自行更改其他可用IO并修改代码定义
//**************************************************************************************************/		
#include "sys.h"
#include "lcd.h"

//LCD的画笔颜色和背景色	   
u16 POINT_COLOR=0x0000;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 
//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

void  delay_ms_new(unsigned char ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 14000;
		  while(--i)	;   //14T per loop
     }while(--ms);
}

void	SPI_init(void)	
{
	SPCTL = (SSIG << 7)+(SPEN << 6)+(DORD << 5)+(MSTR << 4)+(CPOL << 3)+(CPHA << 2)+SPEED_4;
}

/*****************************************************************************
 * @name       :void SPI_WriteByte(u8 byte)
 * @date       :2018-08-09 
 * @function   :Write a byte of data using C51's Hardware SPI
 * @parameters :d:Data to be written
 * @retvalue   :None
******************************************************************************/
void SPI_WriteByte(u8 byte)
{			
			SPDAT = byte;		//发送一个字节
			while((SPSTAT & SPIF)==0)	;	//等待发送完成
			SPSTAT = SPIF+WCOL;			//清0 SPIF和WCOL标志
}

/*****************************************************************************
 * @name       :void LCD_WR_REG(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u8 Reg)	 
{	
	LCD_CS=0;
	LCD_RS=0;
	SPI_WriteByte(Reg);
	LCD_CS=1;
} 

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_DATA(u8 Data)
{
	LCD_CS=0;
	LCD_RS=1;
	SPI_WriteByte(Data);
	LCD_CS=1;
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA_16Bit(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/	 
void LCD_WR_DATA_16Bit(u16 Data)
{
	LCD_CS=0;
	LCD_RS=1;
	SPI_WriteByte(Data>>8);
	SPI_WriteByte(Data);
	LCD_CS=1;
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
  LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA_16Bit(LCD_RegValue);
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_WriteRAM_Prepare(void)
{
 	LCD_WR_REG(lcddev.wramcmd);	  
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/	
void LCD_Clear(u16 Color)
{
	u16 i,j;
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	
    for(i=0;i<lcddev.width;i++)
	 {
	  for (j=0;j<lcddev.height;j++)
	   	{
        	 LCD_WR_DATA_16Bit(Color);
	    }

	  }
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/	
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetWindows(x,y,x,y);//设置光标位置 
	LCD_WR_DATA_16Bit(POINT_COLOR); 	    
} 	 

/*****************************************************************************
 * @name       :void LCD_Reset(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_Reset(void)
{
	LCD_RESET=1;
	delay_ms_new(50);	
	LCD_RESET=0;
	delay_ms_new(50);
	LCD_RESET=1;
	delay_ms_new(50);
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 	 
void LCD_Init(void)
{
	SPI_init(); //初始化硬件SPI
	LCD_Reset(); //初始化之前复位
//************* ILI9225初始化**********//	
	LCD_WriteReg(0x01,0x011c);
	LCD_WriteReg(0x02,0x0100);
	LCD_WriteReg(0x03,0x1038);
	LCD_WriteReg(0x08,0x0808); // set BP and FP
	LCD_WriteReg(0x0B,0x1100); //frame cycle
	LCD_WriteReg(0x0C,0x0000); // RGB interface setting R0Ch=0x0110 for RGB 18Bit and R0Ch=0111for RGB16Bit
	LCD_WriteReg(0x0F,0x1401); // Set frame rate----0801
	LCD_WriteReg(0x15,0x0000); //set system interface
	LCD_WriteReg(0x20,0x0000); // Set GRAM Address
	LCD_WriteReg(0x21,0x0000); // Set GRAM Address
	//*************Power On sequence ****************//
	delay_ms(50);                         // Delay 50ms
	LCD_WriteReg(0x10,0x0800); // Set SAP,DSTB,STB----0A00
	LCD_WriteReg(0x11,0x1F3F); // Set APON,PON,AON,VCI1EN,VC----1038
	delay_ms(50);                         // Delay 50ms
	LCD_WriteReg(0x12,0x0121); // Internal reference voltage= Vci;----1121
	LCD_WriteReg(0x13,0x006F); // Set GVDD----0066
	LCD_WriteReg(0x14,0x4349); // Set VCOMH/VCOML voltage----5F60
	//-------------- Set GRAM area -----------------//
	LCD_WriteReg(0x30,0x0000);
	LCD_WriteReg(0x31,0x00DB);
	LCD_WriteReg(0x32,0x0000);
	LCD_WriteReg(0x33,0x0000);
	LCD_WriteReg(0x34,0x00DB);
	LCD_WriteReg(0x35,0x0000);
	LCD_WriteReg(0x36,0x00AF);
	LCD_WriteReg(0x37,0x0000);
	LCD_WriteReg(0x38,0x00DB);
	LCD_WriteReg(0x39,0x0000);
	// ----------- Adjust the Gamma Curve ----------//
	LCD_WriteReg(0x50,0x0001);  //0400
	LCD_WriteReg(0x51,0x200B);  //060B
	LCD_WriteReg(0x52,0x0000);  //0C0A
	LCD_WriteReg(0x53,0x0404);  //0105
	LCD_WriteReg(0x54,0x0C0C);  //0A0C
	LCD_WriteReg(0x55,0x000C);  //0B06
	LCD_WriteReg(0x56,0x0101);  //0004
	LCD_WriteReg(0x57,0x0400);  //0501
	LCD_WriteReg(0x58,0x1108);  //0E00
	LCD_WriteReg(0x59,0x050C);  //000E
	delay_ms(50);                                     // Delay 50ms
	LCD_WriteReg(0x07,0x1017);
	LCD_WR_REG(0x22);

	//设置LCD属性参数
	LCD_direction(USE_HORIZONTAL);//设置LCD显示方向 
	LCD_BL=1;//点亮背光	 
}
 
/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	u16 x,y,tmp;
	switch(lcddev.dir)
	{
		case 0:
			x = xStar;
			y = yStar;
			break;
		case 1:
			tmp = yStar;
			yStar = xStar;
			xStar = LCD_W-1-yEnd;
			yEnd = xEnd;
			xEnd = LCD_W-1-tmp;
			x = xEnd;
			y = yStar;
			break;
		case 2:
			tmp = xStar;
			xStar = LCD_W-1-xEnd;
			xEnd = LCD_W-1-tmp;
			tmp = yStar;
			yStar = LCD_H-1-yEnd;
			yEnd = LCD_H-1-tmp;
			x = xEnd;
			y = yEnd;
			break;
		case 3:
			tmp = xStar;
			xStar = yStar;
			yStar = LCD_H-1-xEnd;
			xEnd = yEnd;
			yEnd = LCD_H-1-tmp;
			x = xStar;
			y = yEnd;
			break;
		default:
			break;
	}
	LCD_WriteReg(0x36, xEnd);
	LCD_WriteReg(0x37, xStar);
	LCD_WriteReg(0x38, yEnd);
	LCD_WriteReg(0x39, yStar);
	LCD_WriteReg(lcddev.setxcmd, x);
	LCD_WriteReg(lcddev.setycmd, y);
	LCD_WriteRAM_Prepare();	//开始写入GRAM			
}   

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);	
} 

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/ 
void LCD_direction(u8 direction)
{ 
			lcddev.dir = direction&3;
			lcddev.setxcmd=0x20;
			lcddev.setycmd=0x21;
			lcddev.wramcmd=0x22;
	switch(lcddev.dir){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;		
			LCD_WriteReg(0x03,0x1030);
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x03,0x1028);
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			LCD_WriteReg(0x03,0x1000);
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x03,0x1018);
		break;	
		default:break;
	}		
}	 





