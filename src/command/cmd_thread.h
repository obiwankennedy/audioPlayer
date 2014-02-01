#ifndef CMD_THREAD_H
#define CMD_THREAD_H
//
#include <QThread>
#include "pl_command.h"
//
class cmd_thread : public QThread
{
Q_OBJECT
	PL_COMMAND* mycommand;
	bool undo;
public:
	cmd_thread(PL_COMMAND* mycommand,bool undo);
	
protected:
	void run();
	
	
};
#endif
