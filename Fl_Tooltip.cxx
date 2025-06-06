//
// "$Id: Fl_Tooltip.cxx 8788 2011-06-08 14:35:22Z matt $"
//
// Tooltip source file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2011 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#if defined(FLTK_SUPPORT)

#include "Fl_Tooltip.H"
#include <FL/fl_draw.H>
#include <FL/Fl_Menu_Window.H>

#include <stdio.h>
#include <string.h>	// strdup()
#include <cstdlib>	// free()

float		Fl_Tooltip::delay_ = 1.0f;
float		Fl_Tooltip::hoverdelay_ = 0.2f;
Fl_Color	Fl_Tooltip::color_ = fl_color_cube(FL_NUM_RED - 1,
		                                   FL_NUM_GREEN - 1,
						   FL_NUM_BLUE - 2);
Fl_Color	Fl_Tooltip::textcolor_ = FL_BLACK;
Fl_Font         Fl_Tooltip::font_ = FL_HELVETICA;
Fl_Fontsize     Fl_Tooltip::size_ = -1;

#define MAX_WIDTH 400

static const char* tip;
/**
    This widget creates a tooltip box window, with no caption.
*/
class Fl_TooltipBox : public Fl_Menu_Window {
public:
  /** Creates the box window */
  Fl_TooltipBox() : Fl_Menu_Window(0, 0) {
    set_override();
    set_tooltip_window();
    end();
  }
  void draw();
  void layout();
  /** Shows the tooltip windows only if a tooltip text is available. */
  void show() {
    if (!tip) return;
    
    Fl_Menu_Window::show();
  }
};

Fl_Widget* Fl_Tooltip::widget_ = 0;
static Fl_TooltipBox *window = 0;
static int Y,H;

#ifdef __APPLE__
// returns the unique tooltip window
Fl_Window *Fl_Tooltip::current_window(void)
{
  return (Fl_Window*)window;
}
#endif


static void show_tooltip_func ( const char *s )
{
      if (!window) window = new Fl_TooltipBox;
      // this cast bypasses the normal Fl_Window label() code:
      ((Fl_Widget*)window)->label(s);
      window->layout();
      window->redraw();
  //    printf("tooltip_timeout: Showing window %p with tooltip \"%s\"...\n",
  //           window, tip ? tip : "(null)");
      window->show();
}

static void hide_tooltip_func ( void )
{
    if (window) window->hide();
}

static void ensure_callbacks ( void )
{
    if ( ! fl_hide_tooltip )
        fl_hide_tooltip = hide_tooltip_func;
    if ( ! fl_show_tooltip )
        fl_show_tooltip = show_tooltip_func;
}

void Fl_TooltipBox::layout() {
  fl_font(Fl_Tooltip::font(), Fl_Tooltip::size());
  int ww, hh;
  ww = MAX_WIDTH;
  fl_measure(tip, ww, hh, FL_ALIGN_LEFT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
  ww += 6; hh += 6;

  // find position on the screen of the widget:
  int ox = Fl::event_x_root();
  int oy = Y + H+2;
  for (Fl_Widget* p = Fl_Tooltip::current(); p; p = p->window()) {
    oy += p->y();
  }
  int scr_x, scr_y, scr_w, scr_h;
  Fl::screen_xywh(scr_x, scr_y, scr_w, scr_h);
  if (ox+ww > scr_x+scr_w) ox = scr_x+scr_w - ww;
  if (ox < scr_x) ox = scr_x;
  if (H > 30) {
    oy = Fl::event_y_root()+13;
    if (oy+hh > scr_y+scr_h) oy -= 23+hh;
  } else {
    if (oy+hh > scr_y+scr_h) oy -= (4+hh+H);
  }
  if (oy < scr_y) oy = scr_y;

  resize(ox, oy, ww, hh);
}

void Fl_TooltipBox::draw() {
  draw_box(FL_BORDER_BOX, 0, 0, w(), h(), Fl_Tooltip::color());
  fl_color(Fl_Tooltip::textcolor());
  fl_font(Fl_Tooltip::font(), Fl_Tooltip::size());
  fl_draw(tip, 3, 3, w()-6, h()-6, Fl_Align(FL_ALIGN_LEFT|FL_ALIGN_WRAP));
}

static char recent_tooltip;

static void recent_timeout(void*) {
#ifdef DEBUG
  puts("recent_timeout();");
#endif // DEBUG

  recent_tooltip = 0;
}

static char recursion;

void (*fl_show_tooltip)( const char *s ) = 0;
void (*fl_hide_tooltip)( void ) = 0;

static void tooltip_timeout(void*) {
    
    ensure_callbacks();

#ifdef DEBUG
  puts("tooltip_timeout();");
#endif // DEBUG

  if (recursion) return;
  recursion = 1;
  if (!tip || !*tip) {
      fl_hide_tooltip();
  } else {
    int condition = 1;
#if !(defined(__APPLE__) || defined(WIN32))
    condition = (Fl::grab() == NULL);
#endif
    if ( condition ) 
        fl_show_tooltip( tip );
  }

  Fl::remove_timeout(recent_timeout);
  recent_tooltip = 1;
  recursion = 0;
}

/**
   This method is called when the mouse pointer enters a widget.
   <P>If this widget or one of its parents has a tooltip, enter it. This
   will do nothing if this is the current widget (even if the mouse moved
   out so an exit() was done and then moved back in). If no tooltip can
   be found do Fl_Tooltip::exit_(). If you don't want this behavior (for instance
   if you want the tooltip to reappear when the mouse moves back in)
   call the fancier enter_area() below.
*/
void Fl_Tooltip::enter_(Fl_Widget* w) {
#ifdef DEBUG
  printf("Fl_Tooltip::enter_(w=%p)\n", w);
  printf("    window=%p\n", window);
#endif // DEBUG

  // find the enclosing group with a tooltip:
  Fl_Widget* tw = w;
  for (;;) {
    if (!tw) {exit_(0); return;}
    if (tw == widget_) return;
    if (tw->tooltip()) break;
    tw = tw->parent();
  }
  enter_area(w, 0, 0, w->w(), w->h(), tw->tooltip());
}
/** 
     Sets the current widget target. 
     Acts as though enter(widget) was done but does not pop up a
     tooltip.  This is useful to prevent a tooltip from reappearing when
     a modal overlapping window is deleted. FLTK does this automatically
     when you click the mouse button.
*/
void Fl_Tooltip::current(Fl_Widget* w) {
#ifdef DEBUG
  printf("Fl_Tooltip::current(w=%p)\n", w);
#endif // DEBUG

  exit_(0);
  // find the enclosing group with a tooltip:
  Fl_Widget* tw = w;
  for (;;) {
    if (!tw) return;
    if (tw->tooltip()) break;
    tw = tw->parent();
  }
  // act just like Fl_Tooltip::enter_() except we can remember a zero:
  widget_ = w;
}

// Hide any visible tooltip.
/**  This method is called when the mouse pointer leaves a  widget. */
void Fl_Tooltip::exit_(Fl_Widget *w) {
#ifdef DEBUG
  printf("Fl_Tooltip::exit_(w=%p)\n", w);
  printf("    widget=%p, window=%p\n", widget_, window);
#endif // DEBUG

  ensure_callbacks();

  if (!widget_ || (w && w == window)) return;
  widget_ = 0;
  Fl::remove_timeout(tooltip_timeout);
  Fl::remove_timeout(recent_timeout);
  fl_hide_tooltip();
  if (recent_tooltip) {
    if (Fl::event_state() & FL_BUTTONS) recent_tooltip = 0;
    else Fl::add_timeout(Fl_Tooltip::hoverdelay(), recent_timeout);
  }
}

// Get ready to display a tooltip. The widget and the xywh box inside
// it define an area the tooltip is for, this along with the current
// mouse position places the tooltip (the mouse is assumed to point
// inside or near the box).
/**
  You may be able to use this to provide tooltips for internal pieces
  of your widget. Call this after setting Fl::belowmouse() to
  your widget (because that calls the above enter() method). Then figure
  out what thing the mouse is pointing at, and call this with the widget
  (this pointer is used to remove the tooltip if the widget is deleted
  or hidden, and to locate the tooltip), the rectangle surrounding the
  area, relative to the top-left corner of the widget (used to calculate
  where to put the tooltip), and the text of the tooltip (which must be
  a pointer to static data as it is not copied).
*/
void Fl_Tooltip::enter_area(Fl_Widget* wid, int x,int y,int w,int h, const char* t)
{
  (void)x;
  (void)w;
  
  ensure_callbacks();

#ifdef DEBUG
  printf("Fl_Tooltip::enter_area(wid=%p, x=%d, y=%d, w=%d, h=%d, t=\"%s\")\n",
         wid, x, y, w, h, t ? t : "(null)");
  printf("    recursion=%d, window=%p\n", recursion, window);
#endif // DEBUG

  if (recursion) return;
  if (!t || !*t || !enabled()) {
    exit_(0);
    return;
  }
  // do nothing if it is the same:
  if (wid==widget_ /*&& x==X && y==Y && w==W && h==H*/ && t==tip) return;
  Fl::remove_timeout(tooltip_timeout);
  Fl::remove_timeout(recent_timeout);
  // remember it:
  widget_ = wid; Y = y; H = h; tip = t;
  // popup the tooltip immediately if it was recently up:
  if (recent_tooltip) {
      fl_hide_tooltip();
    Fl::add_timeout(Fl_Tooltip::hoverdelay(), tooltip_timeout);
  } else if (Fl_Tooltip::delay() < .1) {
#ifdef WIN32
    // possible fix for the Windows titlebar, it seems to want the
    // window to be destroyed, moving it messes up the parenting:
      fl_hide_tooltip();
#endif // WIN32
    tooltip_timeout(0);
  } else {
      fl_hide_tooltip();
    Fl::add_timeout(Fl_Tooltip::delay(), tooltip_timeout);
  }

#ifdef DEBUG
  printf("    tip=\"%s\", window->shown()=%d\n", tip ? tip : "(null)",
         window ? window->shown() : 0);
#endif // DEBUG
}

void Fl_Tooltip::set_enter_exit_once_() {
  static char beenhere = 0;
  if (!beenhere) {
    beenhere          = 1;
    Fl_Tooltip::enter = Fl_Tooltip::enter_;
    Fl_Tooltip::exit  = Fl_Tooltip::exit_;
  }
}

/**
  Sets the current tooltip text. 

  Sets a string of text to display in a popup tooltip window when the user 
  hovers the mouse over the widget. The string is <I>not</I> copied, so 
  make sure any formatted string is stored in a static, global, 
  or allocated buffer. If you want a copy made and managed for you,
  use the copy_tooltip() method, which will manage the tooltip string
  automatically.

  If no tooltip is set, the tooltip of the parent is inherited. Setting a 
  tooltip for a group and setting no tooltip for a child will show the 
  group's tooltip instead. To avoid this behavior, you can set the child's 
  tooltip to an empty string ("").
  \param[in] text New tooltip text (no copy is made)
  \see copy_tooltip(const char*), tooltip()
*/
void Fl_Widget::tooltip(const char *text) {
  Fl_Tooltip::set_enter_exit_once_();
  if (flags() & COPIED_TOOLTIP) {
    // reassigning a copied tooltip remains the same copied tooltip
    if (tooltip_ == text) return;
    free((void*)(tooltip_));            // free maintained copy
    clear_flag(COPIED_TOOLTIP);         // disable copy flag (WE don't make copies)
  }
  tooltip_ = text;
}

/**
  Sets the current tooltip text. 
  Unlike tooltip(), this method allocates a copy of the tooltip 
  string instead of using the original string pointer.

  The internal copy will automatically be freed whenever you assign
  a new tooltip or when the widget is destroyed.

  If no tooltip is set, the tooltip of the parent is inherited. Setting a 
  tooltip for a group and setting no tooltip for a child will show the 
  group's tooltip instead. To avoid this behavior, you can set the child's 
  tooltip to an empty string ("").
  \param[in] text New tooltip text (an internal copy is made and managed)
  \see tooltip(const char*), tooltip()
*/
void Fl_Widget::copy_tooltip(const char *text) {
  Fl_Tooltip::set_enter_exit_once_();
  if (flags() & COPIED_TOOLTIP) free((void *)(tooltip_));
  if (text) {
    set_flag(COPIED_TOOLTIP);
    tooltip_ = strdup(text);
  } else {
    clear_flag(COPIED_TOOLTIP);
    tooltip_ = (char *)0;
  }
}

#endif // FLTK_SUPPORT
//
// End of "$Id: Fl_Tooltip.cxx 8788 2011-06-08 14:35:22Z matt $".
//
