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




//������ʾ��֧�ֵ���ɫ���������16λɫ�Ļ����붨��256ɫ

#define COLOR_256  //256ɫ 
//#define COLOR_64   //64ɫ 
//#define COLOR_8    //8ɫ 
//----------------------------------------------------------
//����ĺ�  �����㷢��һ���ֽڵĺ��������滻 sendch ���������滻���� SendByte,SendByte���û������ʵ�ʴ��ڻ��߲��ڷ��͵ĺ�����
//����еı�������֧�ִ˶���Ļ����뽫���ڻ��߲��ڷ��͵ĺ������Ƹ�ΪLR_Send_Char			
#define  LR_Send_Char        SendByte 
//----------------------------------------------------------

//�������ͺ궨�壬���滻����ı��뻷����Ӧ������
#define UCHAR  unsigned char	//�޷��ŵ��ֽ�
#define USHORT unsigned short   //�޷���˫�ֽ�

//=========��������һ�㲻���޸ģ������Ҫ�޸ĵĻ���--����---======================//

//����Ϊ�˷�����䶨��ĺ�
//��ɫ����
#ifdef COLOR_256
	#define BLACK    0x00  //��ɫ
	#define BLUE     0x03  //��ɫ
	#define GREEN    0x1c  //��ɫ
	#define CYAN     0x1f  //��ɫ
	#define RED      0xe0  //��ɫ
	#define YELLOW   0xfc  //��ɫ
	#define PINK     0xe3  //��ɫ
	#define WHITE    0xff  //��ɫ
#endif

#ifdef COLOR_64
	#define BLACK    0x00  //��ɫ
	#define BLUE     0x44  //��ɫ
	#define GREEN    0x22  //��ɫ
	#define CYAN     0x66  //��ɫ
	#define RED      0x11  //��ɫ
	#define YELLOW   0x33  //��ɫ
	#define PINK     0x55  //��ɫ
	#define WHITE    0x77  //��ɫ
#endif

#ifdef COLOR_8
	#define BLACK    0x00  //��ɫ
	#define BLUE     0x01  //��ɫ
	#define GREEN    0x02  //��ɫ
	#define CYAN     0x03  //��ɫ
	#define RED      0x04  //��ɫ
	#define YELLOW   0x06  //��ɫ
	#define PINK     0x05  //��ɫ
	#define WHITE    0x07  //��ɫ
#endif



#define SOLID_CIRCLE    0X13 // ʵ��Բ
#define HOLLO_CIRCLE	0X59 // ����Բ
#define STYLE_PIE		0X17 // ��״ͼ
#define STYLE_ARC		0X16 // ���� 
#define RECT_SOLID		0X41 // ʵ�ľ���
#define RECT_HOLLO		0X5A // ���ľ���
#define LINE_SOLID		0X46 // ʵ��
#define LINE_DOT		0X3B // ����

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

#define HOLLO_SHAPE 0xAA // ����ͼ��
#define SOLID_SHAPE 0xAB // ʵ��ͼ��

#define DIAL_ITEM 10   // �Ǳ��̿ؼ�
#define ANG_AUTOVAL 11 // ��̬�Ƕ�ֵ
#define SECTOR_SCOPE 12 // ��Բ���ķ�Χ
#define BAR_ITEM 20 // ��״ͼ�ؼ�
#define BAR_HEIGHT 21 // ��״ͼ�ĸ߶�
#define CTRL_LINE_ITEM 30 // ����ͼ

#define CTRL_LINE_ENABLE 29   //ʹ����ʾ���߿���
#define CARTOON_ITEM 40 // �����ؼ�
#define GRP_CARTOON_STATE 41 // �����ؼ���״̬�����л�ֹͣ��
#define GRP_CARTOON_SHOWINDEX 42 // ���ö����е���һ��ͼƬ

#define LOCBMP_ITEM 50

#define LINE_NO_INTERVAL 31		// �ǵȼ������
#define LINE_SAME_INTERVAL 32	 // �ȼ�����ߣ����л���
#define LINE_SAME_INTERVAL_NO_BUFFER 34		// �ȼ�����ߣ��Ǵ��л���
#define LINE_NO_INTERVAL_NO_BUFFER 33		// �ǵȼ�����ߣ��Ǵ��л���
#define LINE_SAME_INTERVAL_DOT 35	 // �ȼ�������л���,������ֻ��ʾ��
#define LINE_SAME_INTERVAL_NOBUF_DOT 36		// �ȼ�����Ǵ��л���,������ֻ��ʾ��

#define BUTTON_ITEM 1 // ��ť�ؼ�
#define EDITE_ITEM 2  // �ı���ؼ�
#define KEY_ITEM 6  // ��������
#define COOR_INFO 7 // ������Ϣ
#define SET_PROPS 8  // ��������
#define CHECK_SIGNAL 15 // ���38K���ź�
#define GET_CURRTIME 16 // ��ȡ��ǰʱ��

#define DATA_TRAN 3 // ���ݴ���
#define CLICK_EVENT 4 // ����¼�
#define FETCH_DATA 5 // ��ȡ����
#define CMP_EDIT2FLASH 9 // �Ƚ��ı����Flash���ֵ

#define SET_BMP_FACTOR 6 // ���ð�ť�ĻҶ�ֵ����Ҫ���ڽ��ð�ť��
#define BTN_EDIT_CMD 9
#define INIT_GROUP_CMD 10  // ������һ��İ�ťΪ����״̬
	
#define SAVE_CURR_EDIT 30  // 	 ��ǰ�ı���ֵ
	
#define PAGE_ITEM 100  // ҳ������
#define INIT_PAGE_INDEX	101 // ��ʾҳ�������

#define SELF_DEF 0    // �Զ��幦��
#define PAGE_CLOSE 1 // �ر�ҳ��
#define IN_CHAR 2 // �����ַ�
#define DELETE_CHAR 3 // ɾ���ַ�

#define FLASH_TO_EDIT 1   // Flash���ı���
#define EDIT_TO_FLASH 2  // ���ı���Flash
#define EDIT_CMP_FLASH 3 // �Ƚ��ı����Flash������
#define READ_FLASH_VALUE 4 // ��ȡFlash��ֵ

#define SD_LIST_FILE 10   // �г�SD���������ļ�
#define SD_FILE_LEN  36   //SD��ĳ���ļ��ĳ���
#define SD_FILE_NAME_NO  38   //SD��ĳ���ļ�����ź�������
#define SD_COPY_FILE_USB 20 // ��SD���ڵ�һ���ļ�������U����
#define SD_DELETE_FILE 30 // ɾ��SD���ڵ��ļ�
#define SD_SHOW_FILENAME 31 // ��ʾSD����ĳһ���ļ�������
#define SD_SHOW_FILELINE 35 // ��ʾSD����ĳһ���ļ���ĳһ�е�����
#define SD_USB_FILELEN 15 // SD����U��Ŀ¼�ļ�������
#define SD_IMAGE_TYPE 1 // ����SD���Ļ��湤��
#define SD_WRITE_FILE 3 // ��SD��д������
#define SD_WRITE_FILE_WITH_NAME 5 //���ļ���д��SD��
#define SD_FILE_LEN_DATA 42 //SD��ĳ�ļ����Ⱥ�����

#define USB_LIST_FILE 40 // �г�U���������ļ�
#define USB_COPY_FILE_SD 50 // ��U���ڵ�һ���ļ�������U����
#define USB_DELETE_FILE 60 // ɾ��U���ڵ��ļ�
#define USB_SHOW_FILENAME 33 // ��ʾU����ĳһ���ļ�������
#define USB_SHOW_FILELINE 32 // ��ʾU����ĳһ���ļ���ĳһ�е�����
#define USB_FILE_LEN  37   //USBĳ���ļ��ĳ���
#define USB_FILE_NAME_NO  39  //USBĳ���ļ�����ź�������
#define USB_IMAGE_TYPE 0  // ����SD���Ļ��湤��
#define USB_WRITE_FILE 4  // ��SD��д������

#define LINE_SET_PROPS 1  // ������ǿ��GUI�Ļ��ߵ�����
#define DO_LINE_DRAW 2 // ִ�л���


/************* ���ÿؼ�������ֵ **************/
#define keyNumD 254      // ���̱���
#define alignTypeD 253  // ���뷽ʽ(�༭��)
#define yScaleD 252   // ����������Ŵ���(�༭��)
#define xScaleD 251   // ����������Ŵ���(�༭��)
#define bgColorD 250  // ����ɫ(�༭��)
#define fgColorD 249  // ǰ��ɫ(�༭��)
#define page_offsetyD 248 // ���ʱ����ҳ�������ƫ��ֵ
#define page_offsetxD 247 // ���ʱ����ҳ��������ƫ��ֵ
#define inputCharD 246 // �������������ַ�
#define funcTypeD 245 // ��������
#define btnDelaysD 244 // �������ʱ����ť��̬�л���ʾ
#define toPageIndexD 243 // ����ʱת������ҳ��
#define disableOrEnD 242   // ���ð�ť�Ƿ���ʾ��ɫ����ʾ���ܱ����
#define btnstats 240  //���ð�ţ̌����״̬
//����Ϊ��װ�õĺ����������Ե���



#endif