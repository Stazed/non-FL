
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

#include <FL/Fl_Pack.H>

class Fl_Sometimes_Pack : public Fl_Pack
{
    bool _pack;

public:

    Fl_Sometimes_Pack ( int X, int Y, int W, int H, const char *L=0 ) : Fl_Pack(X,Y,W,H,L)
        {
            _pack = true;
        }

    virtual ~Fl_Sometimes_Pack ( ) 
        {
        }

    void pack ( bool b )
        {
            if ( b != _pack )
                redraw();

            _pack = b;
        }

    bool pack ( void ) const
        {
            return _pack;
        }

    virtual void draw ( void )
        {
            /* draw_box(); */

            if ( _pack )
            {
                Fl_Pack::draw();
            }
            else
            {
                if ( children() )
                {
                    for ( int i = 0; i < children(); i++ )
                    {
                        Fl_Widget *o = child( i );

                        o->resize( x(),y(),w(), o->h() );
                    }
                    resize( x(), y(), w(), child(0)->h() );
                }

                Fl_Group::draw();
            }
        }
};
