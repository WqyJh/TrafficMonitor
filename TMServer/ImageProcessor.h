#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <string>
#include <mutex>
#include <queue>
#include <thread>
#include "PlateRecognizer.h"
#include "PlateDao.h"

class ImageProcessor
{
public:
	ImageProcessor();
	~ImageProcessor();

	/*
	* Summary: 开始处理程序
	*/
	void start();

	/*
	* Summary: 停止处理程序
	*/
	void stop();

	/*
	* Summary: 添加一个文件到处理队列
	*/
	void put(std::string file);

private:

	int _timeval;

	std::mutex _queue_mutex;

	bool _running;

	std::mutex _running_mutex;

	std::queue<std::string> _msgqueue;

	std::thread *_thread;

	PlateRecognizer _recognizer;

	PlateDao _dao;

	std::string _db_name;

	void set_running(bool running);
};

#endif // !IMAGE_PROCESSOR_H



