/* 
 * h264bitstream - a library for reading and writing H.264 video
 * Copyright (C) 2005 Auroras Entertainment, LLC
 * 
 * Written by Alex Izvorski <aizvorski@gmail.com>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "stdafx.h"

#include "bs.h"

/****** bitstream operations *******/

void     bs_init(bs_t* b, unsigned char* buf, int size)
{
	b->start = buf;
	b->p = buf;
	b->end = buf + size;
	b->bits_left = 8;
}

unsigned int bs_byte_aligned(bs_t* b) { if (b->bits_left == 8) { return 1; } else { return 0; } }

unsigned int bs_eof(bs_t* b) { if (b->p >= b->end) { return 1; } else { return 0; } }

unsigned int bs_read_u1(bs_t* b)
{
	unsigned int r = 0;
	if (bs_eof(b)) { return 0; }
	
	b->bits_left--;
	r = ((*(b->p)) >> b->bits_left) & 0x01;

	if (b->bits_left == 0) { b->p ++; b->bits_left = 8; }

	return r;
}

unsigned int bs_read_u(bs_t* b, int n)
{
	unsigned int r = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		r |= ( bs_read_u1(b) << ( n - i - 1 ) );
	}
	return r;
}

unsigned int bs_read_f(bs_t* b, int n) { return bs_read_u(b, n); }

unsigned int bs_read_u8(bs_t* b) { return bs_read_u(b, 8); }

unsigned int bs_read_ue(bs_t* b)
{
	int r = 0;
	int i = 0;

    while( bs_read_u1(b) == 0 && i < 32 && !bs_eof(b) )
    {
        i++;
    }
	r = bs_read_u(b, i);
	r += (1 << i) - 1;
	return r;
}

int bs_read_se(bs_t* b) 
{
	int r = bs_read_ue(b);
	if (r & 0x01)
	{
		r = (r+1)/2;
	}
	else
	{
		r = -(r/2);
	}
	return r;
}


void bs_write_u1(bs_t* b, unsigned int v)
{
	if (bs_eof(b)) { return; }
	
	b->bits_left--;
	(*(b->p)) |= ((v & 0x01) << b->bits_left);

	if (b->bits_left == 0) { b->p ++; b->bits_left = 8; }
}

void bs_write_u(bs_t* b, int n, unsigned int v)
{
	int i;
	for (i = 0; i < n; i++)
	{
		bs_write_u1(b, (v >> ( n - i - 1 ))&0x01 );
	}
}

void bs_write_f(bs_t* b, int n, unsigned int v) { bs_write_u(b, n, v); }

void bs_write_u8(bs_t* b, unsigned int v) { bs_write_u(b, 8, v); }

void bs_write_ue(bs_t* b, unsigned int v)
{
    static const int len_table[256] =
    {
        1,
		1,
		2,2,
		3,3,3,3,
		4,4,4,4,4,4,4,4,
		5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
        6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
		6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
        7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
        7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
        8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
        8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
        8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
        8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    };

    int len;

    if (v == 0)
    {
        bs_write_u1(b, 1);
    }
    else
    {
		v++;

		if (v >= 0x01000000)
		{
			len = 24 + len_table[ v >> 24 ];
		}
        else if(v >= 0x00010000)
        {
            len = 16 + len_table[ v >> 16 ];
        }
        else if(v >= 0x00000100)
        {
            len =  8 + len_table[ v >>  8 ];
        }
        else 
        {
            len = len_table[ v ];
        }

        bs_write_u(b, 2*len-1, v);
    }
}

void bs_write_se(bs_t* b, int v)
{
	if (v <= 0)
	{
		bs_write_ue(b, -v*2);
	}
	else
	{
		bs_write_ue(b, v*2 - 1);
	}
}

