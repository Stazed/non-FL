
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

#pragma once

#include <FL/Fl_Group.H>

#define MODULE_RESIZE_ADJUST 1

#ifdef MODULE_RESIZE_ADJUST
extern const char *GAIN_LABEL;
extern const char *METER_LABEL;
#endif

class Fl_Scalepack : public Fl_Group
{

    int _spacing;
#ifdef MODULE_RESIZE_ADJUST
    bool _adjust_gain;
    bool _adjust_meter;
#endif

public:

    enum { VERTICAL, HORIZONTAL };

    Fl_Scalepack ( int X, int Y, int W, int H, const char *L = 0 );
    virtual ~Fl_Scalepack ( ) { }

    int spacing ( void ) const { return _spacing; }
    void spacing ( int v ) { _spacing = v; redraw(); }

    virtual void resize ( int, int, int, int );

    virtual void draw ( void );

};
