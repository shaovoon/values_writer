#include "values_writer.h"

int main()
{
    using namespace writer;

    Console w;
    //Debug w;

    w.WriteLine("My name is {}, My age is {h}", "Harry", 24);
    
    return 0;
}

/*
int main()
{
    using namespace writer;

    FileWriter w("d:\\temp2\\file.txt");
    w.WriteLine("My name is {}, My age is {h}", "Harry", 24);
    
    return 0;
}
*/

/*
#include "syslog_writer.h"

int main()
{
    using namespace writer;

    SyslogWriter w("Logs", LOG_PERROR|LOG_PID, LOG_USER);

    w.Write(LOG_INFO, "My name is {}, My age is {h}", "Henry", 24);

    return 0;
}
*/