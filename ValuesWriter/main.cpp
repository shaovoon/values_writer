#include "values_writer.h"

int main()
{
    using namespace writer;

    Console w;
    //Debug w;

    // test new trim specifier : {t}
    w.WriteLine("My name is {t} and my age is {}", " Harry\t", 24);
    
    return 0;
}

/*
int main()
{
    using namespace writer;

    FileWriter w("d:\\temp2\\file.txt");
    w.WriteLine("My name is {} and my age is {}", "Harry", 24);
    
    return 0;
}
*/

/*
#include "syslog_writer.h"

int main()
{
    using namespace writer;

    SyslogWriter w("Logs", LOG_PERROR|LOG_PID, LOG_USER);

    w.Write(LOG_INFO, "My name is {} and my age is {}", "Harry", 24);

    return 0;
}
*/