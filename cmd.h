#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <base.h>
#include <iostream>
#include <string>

class cmd : public base {
	protected:
	vector<Base*> commands;
	
	public:
	bool execute();
};
#endif
