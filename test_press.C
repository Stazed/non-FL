
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

/* Fl::test_shortcut() is broken for use in FL_PUSH handlers etc,
 * because it relies on Fl::event_text(), which isn't cleared as it
 * should be--and there's no official way to clear it. Therefore, we
 * provide a test_press() function instead, which, unlike
 * test_shortcut(), does not treat a missing FL_SHIFT as "don't care". */

#include <FL/Fl.H>

int
test_press ( unsigned long e )
{
    if ( Fl::event_text()[0] )
        ((char *)Fl::event_text())[0] = '\0';

    const int mod_mask = FL_SHIFT | FL_ALT | FL_CTRL;

    if ( ( e & mod_mask ) != ( Fl::event_state() & mod_mask ) )
        return false;
    else
        return Fl::test_shortcut( e );
}
