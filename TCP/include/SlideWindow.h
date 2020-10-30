#ifndef SLIDEWINDOW_H
#define SLIDEWINDOW_H

#include <vector>
#include "DataStructure.h"
#include "Global.h"

// 使用vector创建一个可以保存缓存包的窗口类
// 该类继承于类型为Packet的vector类
// 具有vector类的添加删除等等属性
class SlideWindow : std::vector<Packet>
{
private:
	/* slide window size */
	const int size;

public:
	SlideWindow(int size);
	~SlideWindow();

public:
	/**
	* overload vector operator []
	* 
	* @param seq get the seq'th element in vector
	* 
	* @returns Package element
	*/
	Packet &operator[](int seq);

	/**
	* 
	* @param base  the first value which is going to be printed
	*/
	void ShowWindow(const int base);
};

#endif
