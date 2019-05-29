#include "apilib.h"

void HariMain(void)
{
    char *buf;
    int win, i;
    api_initmalloc();
    buf = api_malloc(320 * 200);
    win = api_openwin(buf, 320, 200, -1, "lines");
    for (i = 0; i < 8; i++)
    {
        api_linewin(win + 1, 8, 26, 146, i * 18 + 26, i);
        api_linewin(win + 1, 168, 26, i * 18 + 168, 170, i);
    }
    api_refreshwin(win, 6, 26, 313, 193);
    for (;;)
    {
        if (api_getkey(1) == 0x0a)
        {
            break;
        }
    }
    api_closewin(win);
    api_end();
}