#include "CollectorService.hpp"

int main()
{
    CollectorService collector = *(new CollectorService(8080));

    sleep(1);

    if (!collector.Start())
    {
        return 1;
    }

    return 0;
}
