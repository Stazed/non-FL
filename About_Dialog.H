//
// Copyright (C) 2008-2021 Jonathan Moore Liles
// Copyright (C) 2021- Stazed
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

// generated by Fast Light User Interface Designer (fluid) version 1.0309

#ifndef About_Dialog_H
#define About_Dialog_H
#include <FL/Fl.H>
void open_url( const char *url );
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Button.H>

class About_Dialog {
public:
  About_Dialog( const char *logo_filename );
  void run();
private:
  Fl_Double_Window* make_window( const char *logo_filename );
  Fl_Double_Window *window;
  inline void cb_window_i(Fl_Double_Window*, void*);
  static void cb_window(Fl_Double_Window*, void*);
public:
  Fl_Box *credits;
  Fl_Box *copyright;
  Fl_Box *logo_box;
private:
  inline void cb_Rock_i(Fl_Return_Button*, void*);
  static void cb_Rock(Fl_Return_Button*, void*);
public:
  Fl_Button *website_url;
private:
  inline void cb_website_url_i(Fl_Button*, void*);
  static void cb_website_url(Fl_Button*, void*);
public:
  Fl_Box *title;
};
#endif
