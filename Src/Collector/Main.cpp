#include "CollectorService.hpp"

int main()
{
    CollectorService collector = *(new CollectorService(8080));

    if (!collector.Start())
    {
        return 1;
    }

    return 0;
}
