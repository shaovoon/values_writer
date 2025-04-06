#include "print.h"

using namespace printer;


int main()
{
	print("My name is {} and my age is {}\n", "Harry", 24);
    dprint("My name is {} and my age is {}\n", "Harry", 24);
    
    return 0;
}


/*
int main()
{
	std::string filePath = "d:\\temp2\\file.txt";
	FILE* fp = fopen(filePath.c_str(), "wt");

    fprint(fp, "My name is {} and my age is {}\n", "Harry", 24);

	fclose(fp);
	fp = nullptr;

    return 0;
}
*/

/*
#include <syslog.h>

int main()
{
    openlog("Logs", LOG_PERROR|LOG_PID, LOG_USER);

    sysprint(LOG_INFO, "My name is {} and my age is {}", "Harry", 24);

    closelog();

    return 0;
}
*/