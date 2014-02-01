#include "cmd_thread.h"
//
cmd_thread::cmd_thread(PL_COMMAND* _mycommand,bool _undo) 
	: QThread(),mycommand(_mycommand),undo(_undo)
{
	
	
}
//
void cmd_thread::run()
{
	
	if(undo)
		mycommand->undo();
	else
		mycommand->doCommand();
}
