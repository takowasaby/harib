#include "a.h"

int rand(void);

void HariMain(void)
{
    char *buf;
    int win, i, x, y;
    api_initmalloc();
    buf = api_malloc(320 * 200);
    win = api_openwin(buf, 320, 200, -1, "stars2");
    api_boxfillwin(win + 1, 6, 26, 313, 193, 0);
    for (i = 0; i < 100; i++)
    {
        x = (rand() % 307) + 6;
        y = (rand() % 167) + 26;
        api_point(win + 1, x, y, 3);
    }
    api_refreshwin(win, 6, 26, 313, 193);
    api_end();
}