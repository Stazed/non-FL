
/*******************************************************************************/
/* Copyright (C) 2008-2021 Jonathan Moore Liles                                */
/* Copyright (C) 2024- Stazed                                                  */
/*                                                                             */
/* Copyright (C) 2001-2005 by Colin Jones                                      */
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

#include <FL/Fl.H>
#ifdef FLTK_VERSION_1_4
#include <FL/platform.H>
#else
#include <FL/x.H>
#endif
#include <FL/fl_draw.H>

#include "Fl_Theme.H"
#include <math.h>

static const int DX = 2;

static void cairo_color(Fl_Color c)
{
    c = fl_color_average( FL_BLACK, c, 0.10f );

    if (Fl::draw_box_active())
        fl_color(c);
    else
        fl_color(fl_inactive(c));
}

static Fl_Color border_color ( Fl_Color c )
{
    return fl_color_average( FL_FOREGROUND_COLOR, c, 0.25f );
}

static Fl_Color interior_color ( Fl_Color c )
{
    return fl_color_average( FL_FOREGROUND_COLOR, c, 0.05f );
}

static void rect_path ( float x, float y, float w, float h, Fl_Color bc, double radius )
{
    x+= 0.5f;
    y+= 0.5f;
    w-=1;
    h-=1;

    fl_color( bc );

    fl_begin_line();
    fl_arc(x, y, radius, radius, 90.0, 180.0);  // top left
    fl_arc(x, y + h - radius, radius, radius, 180.0, 270.0);    // bottom left
    fl_arc(x + w - radius - 1, y + h - radius, radius, radius, 270.0, 360.0); // top right
    fl_arc(x + w - radius - 1, y, radius, radius, 0.0, 90.0);   // bottom right
    fl_end_line();

    fl_xyline(x + 3, y, x + w - 4);     // top
    fl_yxline(x, y + 2, y + h - 4);     // left
    fl_yxline(x + w - 2, y + 2, y + h - 4); // right
    fl_xyline(x + 3, y + h - 1, x + w - 4); // bottom
}

static void rect_pathf ( float x, float y, float w, float h, Fl_Color bc, double /*radius*/)
{
    x+= 0.5f;
    y+= 0.5f;
    w-=2;
    h-=1;

    fl_color( bc );
    
    fl_begin_polygon();
    fl_vertex(x, y);
    fl_vertex(x + w, y);
    fl_vertex(x + w, y + h);
    fl_vertex(x, y + h);
    fl_end_polygon();
}

static void draw_rect(int x, int y, int w, int h, Fl_Color bc, double radius = 6 )
{
    cairo_color( bc );
    rect_path( x, y, w, h, bc, radius );
}

static void draw_rectf(int x, int y, int w, int h, Fl_Color bc , double radius = 8  )
{
    cairo_color( bc );
#ifdef FLTK_VERSION_1_4
#ifdef FLTK_USE_WAYLAND
    rect_pathf( x - 1, y - 1, w, h, bc, radius );
#else
    rect_pathf( x, y, w, h, bc, radius );
#endif
#else   // FLTK version 1.3.x
    rect_pathf( x, y, w, h, bc, radius );
#endif
}

static void up_box(int x, int y, int w, int h, Fl_Color bc)
{
    draw_rectf( x + 2, y + 2, w - 2, h - 4, interior_color( bc ) );
    draw_rect( x+1, y+1, w, h-2, border_color( bc ) );
}

static void up_frame(int x, int y, int w, int h, Fl_Color bc)
{
    draw_rect( x+1,y+1,w-2,h-2, border_color(bc) );
}

static void down_frame(int x, int y, int w, int h, Fl_Color bc)
{
    draw_rect( x+1,y+1,w-2,h-2, bc );
}

static void down_box(int x, int y, int w, int h, Fl_Color bc)
{
    draw_rectf( x + 2, y + 2, w - 2 , h - 4,
		FL_BACKGROUND_COLOR == bc || FL_BACKGROUND2_COLOR == bc
		? fl_darker(interior_color(bc))
		: interior_color( bc ) );

    draw_rect( x + 1, y + 1 , w, h - 2, bc  ); 
}

static void border_box(int x, int y, int w, int h, Fl_Color bc)
{
    fl_rectf( x, y, w, h, bc );
    fl_rect(x, y, w, h, border_color( bc ));
}

static void
init_theme ( void )
{
    Fl::set_boxtype(  FL_UP_BOX,         up_box,             DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_DOWN_BOX,       down_box,           DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_THIN_UP_BOX,    up_box,             DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_THIN_DOWN_BOX,  down_box,           DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_UP_FRAME,       up_frame,           DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_DOWN_FRAME,     down_frame,         DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_ROUND_UP_BOX,   up_box,             DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_ROUND_DOWN_BOX, down_box,           DX,DX,DX*2,DX*2  );
    Fl::set_boxtype(  FL_BORDER_BOX,     border_box,         1,1,2,2  );
}

void
init_vector_theme ( void )
{
    Fl_Theme *t = new Fl_Theme( "Vector", "Vector theme based on NTK vector", "Stazed", init_theme );

    Fl_Theme::add( t );
}

