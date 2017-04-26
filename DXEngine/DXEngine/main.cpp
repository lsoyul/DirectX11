#include "FrameWork.h"

int main()
{
	FrameWork* framework = new FrameWork();

	if (framework->Initialize())
	{
		framework->Run();
	}

	delete framework;

	return 0;
}