//XPT2046是​电阻触摸屏控制，专为驱动4线电阻触摸屏设计，通过检测屏幕按压点的电压变化，计算触点坐标（X/Y轴）。
​//内置12位模数转换器（ADC），提供高精度的坐标测量（分辨率可达4096级）。

#include <REGX52.H>
#include <INTRINS.H>

//引脚定义
sbit XPY2046_DIN=P3^4;
sbit XPY2046_CS=P3^5;
sbit XPY2046_DCLK=P3^6;
sbit XPY2046_DOUT=P3^7;

/**
  * @brief  ZPT2046读取AD值
  * @param  Command 命令字，范围：头文件内定义的宏，结尾的数字表示转换的位数
  * @retval AD转换后的数字量，范围：8位为0~255，12位为0~4095
  */
unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i;
	unsigned int Data=0;
	XPY2046_DCLK=0;
	XPY2046_CS=0;
	for(i=0;i<8;i++)
	{
		XPY2046_DIN=Command&(0x80>>i);
		XPY2046_DCLK=1;
		XPY2046_DCLK=0;
	}
	for(i=0;i<16;i++)
	{
		XPY2046_DCLK=1;
		XPY2046_DCLK=0;
		if(XPY2046_DOUT){Data|=(0x8000>>i);}
	}
	XPY2046_CS=1;
	return Data>>8;
}
