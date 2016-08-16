#ifndef  __LR_LCD_API_H__
#define  __LR_LCD_API_H__


#define ESC 0X1B
#define LR_LCD_SDK_VER 4.1


typedef unsigned char  UCHAR;         /* smallest memory entity */
typedef unsigned short USHORT;        /* 16bit value */
//typedef unsigned long  FMSTR_U32;        /* 32bit value */

//typedef signed char    FMSTR_S8;         /* signed 8bit value */
//typedef signed short   FMSTR_S16;        /* signed 16bit value */
//typedef signed long    FMSTR_S32;        /* signed 32bit value */




//定义显示器支持的颜色数，如果是16位色的话，请定义256色

#define COLOR_256  //256色 
//#define COLOR_64   //64色 
//#define COLOR_8    //8色 
//----------------------------------------------------------
//下面的宏  请用你发送一个字节的函数名来替换 sendch 我们这里替换成了 SendByte,SendByte是用户定义的实际串口或者并口发送的函数名
//如果有的编译器不支持此定义的话，请将串口或者并口发送的函数名称改为LR_Send_Char			
#define  LR_Send_Char        SendByte 
//----------------------------------------------------------

//数据类型宏定义，请替换成你的编译环境相应的类型
#define UCHAR  unsigned char	//无符号单字节
#define USHORT unsigned short   //无符号双字节

//=========以下内容一般不用修改，如果你要修改的话请--慎重---======================//

//以下为了方便记忆定义的宏
//颜色定义
#ifdef COLOR_256
	#define BLACK    0x00  //黑色
	#define BLUE     0x03  //蓝色
	#define GREEN    0x1c  //绿色
	#define CYAN     0x1f  //青色
	#define RED      0xe0  //红色
	#define YELLOW   0xfc  //黄色
	#define PINK     0xe3  //紫色
	#define WHITE    0xff  //白色
#endif

#ifdef COLOR_64
	#define BLACK    0x00  //黑色
	#define BLUE     0x44  //蓝色
	#define GREEN    0x22  //绿色
	#define CYAN     0x66  //青色
	#define RED      0x11  //红色
	#define YELLOW   0x33  //黄色
	#define PINK     0x55  //紫色
	#define WHITE    0x77  //白色
#endif

#ifdef COLOR_8
	#define BLACK    0x00  //黑色
	#define BLUE     0x01  //蓝色
	#define GREEN    0x02  //绿色
	#define CYAN     0x03  //青色
	#define RED      0x04  //红色
	#define YELLOW   0x06  //黄色
	#define PINK     0x05  //紫色
	#define WHITE    0x07  //白色
#endif



#define SOLID_CIRCLE    0X13 // 实心圆
#define HOLLO_CIRCLE	0X59 // 空心圆
#define STYLE_PIE		0X17 // 饼状图
#define STYLE_ARC		0X16 // 扇形 
#define RECT_SOLID		0X41 // 实心矩形
#define RECT_HOLLO		0X5A // 空心矩形
#define LINE_SOLID		0X46 // 实线
#define LINE_DOT		0X3B // 虚线

#define HZK16   0X00
#define HZK24   0X01
#define HZK32   0X02 



#define BUF_START_FIRST 0X01
#define BUF_START_CURR	0X03
#define BUF_END_ONECE	0X02
#define BUF_END_LOOP	0X04
#define BUF_STOP_LOOP	0X00
#define MOVE_UP			0X00
#define MOVE_DOWN		0X01
#define MOVE_RIGHT		0X02
#define MOVE_LEFT		0X03
#define TOUCH_SINGLE_SEND   0X00
#define TOUCH_DOUBLE_SEND   0X01
#define TOUCH_CONTINUE_SEND 0X02

#define HOLLO_SHAPE 0xAA // 空心图形
#define SOLID_SHAPE 0xAB // 实心图形

#define DIAL_ITEM 10   // 仪表盘控件
#define ANG_AUTOVAL 11 // 动态角度值
#define SECTOR_SCOPE 12 // 外圆弧的范围
#define BAR_ITEM 20 // 柱状图控件
#define BAR_HEIGHT 21 // 柱状图的高度
#define CTRL_LINE_ITEM 30 // 曲线图

#define CTRL_LINE_ENABLE 29   //使能显示曲线控制
#define CARTOON_ITEM 40 // 动画控件
#define GRP_CARTOON_STATE 41 // 动画控件的状态（运行或停止）
#define GRP_CARTOON_SHOWINDEX 42 // 设置动画中的哪一副图片

#define LOCBMP_ITEM 50

#define LINE_NO_INTERVAL 31		// 非等间隔曲线
#define LINE_SAME_INTERVAL 32	 // 等间隔曲线，带有缓存
#define LINE_SAME_INTERVAL_NO_BUFFER 34		// 等间隔曲线，非带有缓存
#define LINE_NO_INTERVAL_NO_BUFFER 33		// 非等间隔曲线，非带有缓存
#define LINE_SAME_INTERVAL_DOT 35	 // 等间隔，带有缓存,不划线只显示点
#define LINE_SAME_INTERVAL_NOBUF_DOT 36		// 等间隔，非带有缓存,不划线只显示点

#define BUTTON_ITEM 1 // 按钮控件
#define EDITE_ITEM 2  // 文本框控件
#define KEY_ITEM 6  // 按键类型
#define COOR_INFO 7 // 坐标信息
#define SET_PROPS 8  // 设置属性
#define CHECK_SIGNAL 15 // 检测38K的信号
#define GET_CURRTIME 16 // 获取当前时间

#define DATA_TRAN 3 // 数据传输
#define CLICK_EVENT 4 // 点击事件
#define FETCH_DATA 5 // 获取数据
#define CMP_EDIT2FLASH 9 // 比较文本框和Flash里的值

#define SET_BMP_FACTOR 6 // 设置按钮的灰度值（主要用于禁用按钮）
#define BTN_EDIT_CMD 9
#define INIT_GROUP_CMD 10  // 设置哪一组的按钮为操作状态
	
#define SAVE_CURR_EDIT 30  // 	 当前文本的值
	
#define PAGE_ITEM 100  // 页面类型
#define INIT_PAGE_INDEX	101 // 显示页面的索引

#define SELF_DEF 0    // 自定义功能
#define PAGE_CLOSE 1 // 关闭页面
#define IN_CHAR 2 // 输入字符
#define DELETE_CHAR 3 // 删除字符

#define FLASH_TO_EDIT 1   // Flash到文本框
#define EDIT_TO_FLASH 2  // 从文本框到Flash
#define EDIT_CMP_FLASH 3 // 比较文本框和Flash的数据
#define READ_FLASH_VALUE 4 // 读取Flash的值

#define SD_LIST_FILE 10   // 列出SD卡内所有文件
#define SD_FILE_LEN  36   //SD卡某个文件的长度
#define SD_FILE_NAME_NO  38   //SD卡某个文件的序号和总行数
#define SD_COPY_FILE_USB 20 // 把SD卡内的一个文件拷贝到U盘中
#define SD_DELETE_FILE 30 // 删除SD卡内的文件
#define SD_SHOW_FILENAME 31 // 显示SD卡内某一个文件的名字
#define SD_SHOW_FILELINE 35 // 显示SD卡内某一个文件的某一行的数据
#define SD_USB_FILELEN 15 // SD卡和U盘目录文件的数量
#define SD_IMAGE_TYPE 1 // 下载SD卡的画面工程
#define SD_WRITE_FILE 3 // 向SD卡写入文字
#define SD_WRITE_FILE_WITH_NAME 5 //带文件名写入SD卡
#define SD_FILE_LEN_DATA 42 //SD卡某文件长度和数据

#define USB_LIST_FILE 40 // 列出U盘内所有文件
#define USB_COPY_FILE_SD 50 // 把U盘内的一个文件拷贝到U盘中
#define USB_DELETE_FILE 60 // 删除U盘内的文件
#define USB_SHOW_FILENAME 33 // 显示U盘内某一个文件的名字
#define USB_SHOW_FILELINE 32 // 显示U盘内某一个文件的某一行的数据
#define USB_FILE_LEN  37   //USB某个文件的长度
#define USB_FILE_NAME_NO  39  //USB某个文件的序号和总行数
#define USB_IMAGE_TYPE 0  // 下载SD卡的画面工程
#define USB_WRITE_FILE 4  // 向SD卡写入文字

#define LINE_SET_PROPS 1  // 设置增强性GUI的划线的属性
#define DO_LINE_DRAW 2 // 执行划线


/************* 设置控件的属性值 **************/
#define keyNumD 254      // 键盘编码
#define alignTypeD 253  // 对齐方式(编辑框)
#define yScaleD 252   // 横坐标字体放大倍数(编辑框)
#define xScaleD 251   // 纵坐标字体放大倍数(编辑框)
#define bgColorD 250  // 背景色(编辑框)
#define fgColorD 249  // 前景色(编辑框)
#define page_offsetyD 248 // 点击时弹出页面横坐标偏移值
#define page_offsetxD 247 // 点击时弹出页面纵坐标偏移值
#define inputCharD 246 // 点击键盘输入的字符
#define funcTypeD 245 // 函数类型
#define btnDelaysD 244 // 点击键盘时，按钮动态切换演示
#define toPageIndexD 243 // 单击时转发到的页面
#define disableOrEnD 242   // 设置按钮是否显示灰色，显示后不能被点击
#define btnstats 240  //设置按钮抬起按下状态
//以下为封装好的函数，您可以调用



#endif