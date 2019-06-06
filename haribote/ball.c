#include "bootpack.h"

void init_ball8(char *ball, char bc)
{
	static char cursor[16][16] = {
		"......////......",
		"....//OOOO//....",
		".../OOOOOOOO/...",
		"../OOOOOOOOOO/..",
		"./OOOOOOOOOOOO/.",
		"./OOOOOOOOOOOO/.",
		"/OOOOOOOOOOOOOO/",
		"/OOOOOOOOOOOOOO/",
		"/OOOOOOOOOOOOOO/",
		"/OOOOOOOOOOOOOO/",
		"./OOOOOOOOOOOO/.",
		"./OOOOOOOOOOOO/.",
		"../OOOOOOOOOO/..",
		".../OOOOOOOO/...",
		"....//OOOO//....",
		"......////......"
	};
	int x, y;

	for (y = 0; y < 16; y++) 
	{
		for (x = 0; x < 16; x++)
		{
			if (cursor[y][x] == 'O')
			{
				ball[y * 16 + x] = COL8_FFFFFF;
			}
			if (cursor[y][x] == '/')
			{
				ball[y * 16 + x] = COL8_000000;
			}
			if (cursor[y][x] == '.')
			{
				ball[y * 16 + x] = bc;
			}
		}
	}
	return;
}

unsigned char get_map_val(unsigned char *map, int scrnx, int x, int y)
{
    return map[y * scrnx + x];
}

int update_ball(struct BALL *ball, int scrnx, int scrny, int v, struct SHTCTL *shtctl)
{
    int ret = 0;

    ball->x += ball->dirx * 3;
    ball->y += ball->diry * 3;

    if (ball->x < 0)
    {
        ball->x = 0;
        ball->dirx = -ball->dirx;
    }
    if (ball->y < 0)
    {
        ball->y = 0;
        ball->diry = -ball->diry;
    }
    if (ball->x > scrnx - ball->w)
    {
        ball->x = scrnx - ball->w;
        ball->dirx = -ball->dirx;
    }
    if (ball->y > scrny - ball->h)
    {
        ball->y = scrny - ball->h;
        ball->diry = -ball->diry;
        for (;;)
        {
            taskctl = 0;
        }
    }

    int center_point_x = ball->x + ball->w / 2;
    int center_point_y = ball->y + ball->h / 2;

    int up_point = get_map_val(shtctl->map, scrnx, center_point_x, ball->y);
    int down_point = get_map_val(shtctl->map, scrnx, center_point_x, ball->y + ball->h);
    int left_point = get_map_val(shtctl->map, scrnx, ball->x, center_point_y);
    int right_point = get_map_val(shtctl->map, scrnx, ball->x + ball->w, center_point_y);

    if (up_point != ball->sht - ball->sht->ctl->sheets0 && up_point != 0 && !(down_point != ball->sht - ball->sht->ctl->sheets0 && down_point != 0))
    {
        if ((shtctl->sheets0[up_point].flags & 0x80) != 0)
        {
            sheet_updown(&shtctl->sheets0[up_point], -1);
            ret = 1;
        }
        ball->diry = 1;
    }
    if (down_point != ball->sht - ball->sht->ctl->sheets0 && down_point != 0 && !(up_point != ball->sht - ball->sht->ctl->sheets0 && up_point != 0))
    {
        if ((shtctl->sheets0[down_point].flags & 0x80) != 0)
        {
            sheet_updown(&shtctl->sheets0[down_point], -1);
            ret = 1;
        }
        ball->diry = -1;
    }
    if (left_point != ball->sht - ball->sht->ctl->sheets0 && left_point != 0 && !(right_point != ball->sht - ball->sht->ctl->sheets0 && right_point != 0))
    {
        if ((shtctl->sheets0[left_point].flags & 0x80) != 0)
        {
            sheet_updown(&shtctl->sheets0[left_point], -1);
            ret = 1;
        }
        ball->dirx = 1;
    }
    if (right_point != ball->sht - ball->sht->ctl->sheets0 && right_point != 0 && !(left_point != ball->sht - ball->sht->ctl->sheets0 && left_point != 0))
    {
        if ((shtctl->sheets0[right_point].flags & 0x80) != 0)
        {
            sheet_updown(&shtctl->sheets0[right_point], -1);
            ret = 1;
        }
        ball->dirx = -1;
    }

    sheet_slide(ball->sht, ball->x, ball->y);
    timer_settime(ball->timer, 3);

    return ret;
}
