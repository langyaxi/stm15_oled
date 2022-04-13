#ifndef ASCII 	//如果其他文件已经做了这个记号，那么不执行#define.
#define ASCII 	//如果其他文件没有这个标记，那么就需要新做一个记号（唯一的）。
				//并且编译#define到#endif之间的代码。
					
extern unsigned char code  F6x8[92][6];//6*8字符
extern unsigned char code  F8X16[];	//8*16 大字符	
extern unsigned char code  Hzk[][16];	//汉字字库
extern unsigned char code  Picture[][128];	//图片库
#endif