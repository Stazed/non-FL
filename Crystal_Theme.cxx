
/*******************************************************************************/
/* Copyright (C) 2008-2021 Jonathan Moore Liles                                */
/* Copyright (C) 2021- Stazed                                                  */
/*                                                                             */
/*                                                                             */
/* This program is free software; you can redistribute it and/or modify it     */
/* under the terms of the GNU General Public License as published by the       */
/* Free Software Foundation; either version 2 of the License, or (at your      */
/* option) any later version.                                                  */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but WITHOUT */
/* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       */
/* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for   */
/* more details.                                                               */
/*                                                                             */
/* You should have received a copy of the GNU General Public License along     */
/* with This program; see the file COPYING.  If not,write to the Free Software */
/* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
/*******************************************************************************/


#pragma GCC diagnostic ignored "-Wchar-subscripts"

#include <FL/fl_draw.H>
#include <string.h>

#include "Fl_Theme.H"

/* Crystal boxes, base (obviously) on the FLTK1 'plastic' boxes, but
 * without the rude color blending and with a slightly enhanced
 * appearance. */

extern uchar *fl_gray_ramp();

inline Fl_Color
shade_color ( uchar gc, Fl_Color bc )
{
    return fl_color_average( ( Fl_Color ) gc, bc, 0.25f );
}


static void
frame_rect ( int x, int y, int w, int h, const char *c, Fl_Color bc )
{
    uchar *g = fl_gray_ramp();
    int b = strlen( c ) / 4 + 1;

    for ( x += b, y += b, w -= 2 * b, h -= 2 * b; b > 1; b-- )
    {
        // Draw lines around the perimeter of the button, 4 colors per
        // circuit.
        fl_color( shade_color( g[*c++], bc ) );
        fl_line( x, y + h + b, x + w - 1, y + h + b, x + w + b - 1, y + h );
        fl_color( shade_color( g[*c++], bc ) );
        fl_line( x + w + b - 1, y + h, x + w + b - 1, y, x + w - 1, y - b );
        fl_color( shade_color( g[*c++], bc ) );
        fl_line( x + w - 1, y - b, x, y - b, x - b, y );
        fl_color( shade_color( g[*c++], bc ) );
        fl_line( x - b, y, x - b, y + h, x, y + h + b );
    }
}


static void
frame_round ( int x, int y, int w, int h, const char *c, Fl_Color bc )
{
    uchar *g = fl_gray_ramp();
    int b = strlen( c ) / 4 + 1;

    if ( ! Fl::draw_box_active() )
        bc = fl_inactive( bc );

    if ( w == h )
    {
        for ( ; b > 1; b--, x++, y++, w -= 2, h -= 2 )
        {
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x, y, w, h, 45.0, 135.0 );
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x, y, w, h, 315.0, 405.0 );
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x, y, w, h, 225.0, 315.0 );
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x, y, w, h, 135.0, 225.0 );
        }
    }
    else if ( w > h )
    {
        int d = h / 2;
        for ( ; b > 1; d--, b--, x++, y++, w -= 2, h -= 2 )
        {
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x, y, h, h, 90.0, 135.0 );
            fl_xyline( x + d, y, x + w - d );
            fl_arc( x + w - h, y, h, h, 45.0, 90.0 );
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x + w - h, y, h, h, 315.0, 405.0 );
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x + w - h, y, h, h, 270.0, 315.0 );
            fl_xyline( x + d, y + h - 1, x + w - d );
            fl_arc( x, y, h, h, 225.0, 270.0 );
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x, y, h, h, 135.0, 225.0 );
        }
    }
    else if ( w < h )
    {
        int d = w / 2;
        for ( ; b > 1; d--, b--, x++, y++, w -= 2, h -= 2 )
        {
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x, y, w, w, 45.0, 135.0 );
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x, y, w, w, 0.0, 45.0 );
            fl_yxline( x + w - 1, y + d, y + h - d );
            fl_arc( x, y + h - w, w, w, 315.0, 360.0 );
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x, y + h - w, w, w, 225.0, 315.0 );
            fl_color( shade_color( g[*c++], bc ) );
            fl_arc( x, y + h - w, w, w, 180.0, 225.0 );
            fl_yxline( x, y + d, y + h - d );
            fl_arc( x, y, w, w, 135.0, 180.0 );
        }
    }
}


static void
shade_rect ( int x, int y, int w, int h, const char *c, Fl_Color bc )
{
    uchar *g = fl_gray_ramp();
    int i, j;
    int clen = strlen( c ) - 1;
    int chalf = clen / 2;
    int cstep = 1;

    if ( ! Fl::draw_box_active() )
        bc = fl_inactive( bc );

    if ( h < ( w * 2 ) )
    {
        // Horizontal shading...
        if ( clen >= h )
            cstep = 2;

        for ( i = 0, j = 0; j < chalf; i++, j += cstep )
        {
            // Draw the top line and points...
            fl_color( shade_color( g[c[i]], bc ) );
            fl_xyline( x + 1, y + i, x + w - 2 );

            fl_color( shade_color( g[c[i] - 2], bc ) );
            fl_point( x, y + i + 1 );
            fl_point( x + w - 1, y + i + 1 );

            // Draw the bottom line and points...
            fl_color( shade_color( g[c[clen - i]], bc ) );
            fl_xyline( x + 1, y + h - i, x + w - 2 );

            fl_color( shade_color( g[c[clen - i] - 2], bc ) );
            fl_point( x, y + h - i );
            fl_point( x + w - 1, y + h - i );
        }

        // Draw the interior and sides...
        i = chalf / cstep;

//        fl_color( shade_color( g[c[chalf]], bc ) );
        fl_color( bc );
        fl_rectf( x + 1, y + i, w - 2, h - 2 * i + 1 );

        fl_color( shade_color( g[c[chalf] - 2], bc ) );
        fl_yxline( x, y + i, y + h - i );
        fl_yxline( x + w - 1, y + i, y + h - i );
    }
    else
    {
        // Vertical shading...
        if ( clen >= w )
            cstep = 2;

        for ( i = 0, j = 0; j < chalf; i++, j += cstep )
        {
            // Draw the left line and points...
            fl_color( shade_color( g[c[i]], bc ) );
            fl_yxline( x + i, y + 1, y + h - 1 );

            fl_color( shade_color( g[c[i] - 2], bc ) );
            fl_point( x + i + 1, y );
            fl_point( x + i + 1, y + h );

            // Draw the right line and points...
            fl_color( shade_color( g[c[clen - i]], bc ) );
            fl_yxline( x + w - 1 - i, y + 1, y + h - 1 );

            fl_color( shade_color( g[c[clen - i] - 2], bc ) );
            fl_point( x + w - 2 - i, y );
            fl_point( x + w - 2 - i, y + h );
        }

        // Draw the interior, top, and bottom...
        i = chalf / cstep;

        fl_color( shade_color( g[c[chalf]], bc ) );
        fl_rectf( x + i, y + 1, w - 2 * i, h - 1 );

        fl_color( shade_color( g[c[chalf] - 2], bc ) );
        fl_xyline( x + i, y, x + w - i );
        fl_xyline( x + i, y + h, x + w - i );
    }
}

static void
shade_round ( int x, int y, int w, int h, const char *c, Fl_Color bc )
{
    uchar *g = fl_gray_ramp();
    int i;
    int clen = strlen( c ) - 1;
    int chalf = clen / 2;

    if ( w > h )
    {
        int d = h / 2;
        const int na = 8;
        for ( i = 0; i < chalf; i++, d--, x++, y++, w -= 2, h -= 2 )
        {
            fl_color( shade_color( g[c[i]], bc ) );
            fl_pie( x, y, h, h, 90.0, 135.0 + i * na );
            fl_xyline( x + d, y, x + w - d );
            fl_pie( x + w - h, y, h, h, 45.0 + i * na, 90.0 );
            fl_color( shade_color( g[c[i] - 2], bc ) );
            fl_pie( x + w - h, y, h, h, 315.0 + i * na, 405.0 + i * na );
            fl_color( shade_color( g[c[clen - i]], bc ) );
            fl_pie( x + w - h, y, h, h, 270.0, 315.0 + i * na );
            fl_xyline( x + d, y + h - 1, x + w - d );
            fl_pie( x, y, h, h, 225.0 + i * na, 270.0 );
            fl_color( shade_color( g[c[clen - i] - 2], bc ) );
            fl_pie( x, y, h, h, 135.0 + i * na, 225.0 + i * na );


        }
//        fl_color( shade_color( g[c[chalf]], bc ) );
        fl_color( bc );
        fl_rectf( x + d, y, w - h + 1, h + 1 );
        fl_pie( x, y, h, h, 90.0, 270.0 );
        fl_pie( x + w - h, y, h, h, 270.0, 90.0 );
    }
    else
    {
        int d = w / 2;
        const int na = 8;
        for ( i = 0; i < chalf; i++, d--, x++, y++, w -= 2, h -= 2 )
        {
            fl_color( shade_color( g[c[i]], bc ) );
            fl_pie( x, y, w, w, 45.0 + i * na, 135.0 + i * na );
            fl_color( shade_color( g[c[i] - 2], bc ) );
            fl_pie( x, y, w, w, 0.0, 45.0 + i * na );
            fl_yxline( x + w - 1, y + d, y + h - d );
            fl_pie( x, y + h - w, w, w, 315.0 + i * na, 360.0 );
            fl_color( shade_color( g[c[clen - i]], bc ) );
            fl_pie( x, y + h - w, w, w, 225.0 + i * na, 315.0 + i * na );
            fl_color( shade_color( g[c[clen - i] - 2], bc ) );
            fl_pie( x, y + h - w, w, w, 180.0, 225.0 + i * na );
            fl_yxline( x, y + d, y + h - d );
            fl_pie( x, y, w, w, 135.0 + i * na, 180.0 );
        }
//        fl_color( shade_color( g[c[chalf]], bc ) );
        fl_color( bc );
        fl_rectf( x, y + d, w + 1, h - w + 1 );
        fl_pie( x, y, w, w, 0.0, 180.0 );
        fl_pie( x, y + h - w, w, w, 180.0, 360.0 );
    }
}


static void
up_frame ( int x, int y, int w, int h, Fl_Color c )
{
    frame_rect( x, y, w, h - 1, "MLJIIDLK", c );
}


static void
narrow_thin_box ( int x, int y, int w, int h, Fl_Color c )
{
    if ( h <= 0 || w <= 0 )
        return;
    uchar *g = fl_gray_ramp();
    fl_color( shade_color( g['R'], c ) );
    fl_rectf( x + 1, y + 1, w - 2, h - 2 );
    fl_color( shade_color( g['I'], c ) );
    if ( w > 1 )
    {
        fl_xyline( x + 1, y, x + w - 2 );
        fl_xyline( x + 1, y + h - 1, x + w - 2 );
    }
    if ( h > 1 )
    {
        fl_yxline( x, y + 1, y + h - 2 );
        fl_yxline( x + w - 1, y + 1, y + h - 2 );
    }
}


static void
thin_up_box ( int x, int y, int w, int h, Fl_Color c )
{
    if ( w > 4 && h > 4 )
    {
        shade_rect( x + 1, y + 1, w - 2, h - 3, "QWUSQOQR", c );
        frame_rect( x, y, w, h - 1, "MLJI", c );
    }
    else
        narrow_thin_box( x, y, w, h, c );
}


static void
up_box ( int x, int y, int w, int h, Fl_Color c )
{
    if ( w > 8 && h > 8 )
    {
        shade_rect( x + 1, y + 1, w - 2, h - 3, "QVWVUTSRQPONQVR", c );
//      shade_rect( x + 1, y + 1, w - 2, h - 3, "STUVWVQRWXVUVVQ", c );
//      shade_rect( x + 1, y + 1, w - 2, h - 3, "FISPPQQRSSTTUPJ", c );

        frame_rect( x, y, w, h - 1, "IJLM", c );

    }
    else
        thin_up_box( x, y, w, h, c );
}


static void
up_round ( int x, int y, int w, int h, Fl_Color c )
{
    shade_round( x, y, w, h, "QVWVUTSRQPONQVR", c );
    frame_round( x, y, w, h, "MLJI", c );
}


static void
down_frame ( int x, int y, int w, int h, Fl_Color c )
{
    frame_rect( x, y, w, h - 1, "RRTTLLLL", c );
}


static void
down_box ( int x, int y, int w, int h, Fl_Color c )
{
    if ( w > 6 && h > 6 )
    {
//        shade_rect( x + 2, y + 2, w - 4, h - 5, "STUVWWWVT", c );
        fl_rectf( x + 2, y + 2, w - 4, h - 5 ,
		  FL_BACKGROUND_COLOR == c || FL_BACKGROUND2_COLOR == c
		  ? fl_darker(c)
		  : c );
        down_frame( x, y, w, h, c );
    }
    else
    {
        narrow_thin_box( x, y, w, h, c );
    }
}


static void
down_round ( int x, int y, int w, int h, Fl_Color c )
{
    shade_round( x, y, w, h, "TVWWWVUTS", c );
    frame_round( x, y, w, h, "MLJI", c );
}

static void
border_box ( int x, int y, int w, int h, Fl_Color c )
{
    fl_color(c);
    fl_rectf( x,y,w,h );
    fl_color(fl_darker(c));
    fl_rect(x,y,w,h);
}


static void
init_theme ( void )
{
    printf( "Initializing crystal boxtypes" );

    /* replace the plastic boxes... (is there a better way?) */
    Fl::set_boxtype(  FL_UP_BOX,         up_box,      4,4,8,8 );
    Fl::set_boxtype(  FL_DOWN_BOX,       down_box,    2,2,4,4 );
    Fl::set_boxtype(  FL_UP_FRAME,       up_frame,    2,2,4,4 );
    Fl::set_boxtype(  FL_DOWN_FRAME,     down_frame,  2,2,4,4 );
    Fl::set_boxtype(  FL_THIN_UP_BOX,    thin_up_box, 1,1,2,2 );
    Fl::set_boxtype(  FL_THIN_DOWN_BOX,  down_box,    1,1,2,2 );
    Fl::set_boxtype(  FL_ROUND_UP_BOX,   up_round,    1,1,2,2 );
    Fl::set_boxtype(  FL_ROUND_DOWN_BOX, down_round,  1,1,2,2 );
    Fl::set_boxtype(  FL_BORDER_BOX, border_box,  1,1,2,2 );
}

void
init_crystal_theme ( void )
{
    Fl_Theme *t = new Fl_Theme( "Crystal", "", "", init_theme );

    Fl_Theme::add( t );
}
