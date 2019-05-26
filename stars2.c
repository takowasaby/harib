#include "a.h"

int rand(void);

void HariMain(void)
{
    char *buf;
    int win, i, x, y;
    api_initmalloc();
    buf = api_malloc(640 * 400);
    win = api_openwin(buf, 640, 400, -1, "stars2");
    api_boxfillwin(win + 1, 6, 26, 633, 393, 0);
    for (i = 0; i < 1000; i++)
    {
        x = (rand() % 627) + 6;
        y = (rand() % 367) + 26;
        api_point(win + 1, x, y, 3);
    }
    api_refreshwin(win, 6, 26, 633, 393);
    for (;;)
    {
        if (api_getkey(1) == 0x0a)
        {
            break;
        }
    }
    api_end();
}