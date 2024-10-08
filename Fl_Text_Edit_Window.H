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

#ifndef Fl_Text_Edit_Window_H
#define Fl_Text_Edit_Window_H
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Return_Button.H>

class Fl_Text_Edit_Window : public Fl_Double_Window {
  void _Fl_Text_Edit_Window();
public:
  Fl_Text_Edit_Window(int X, int Y, int W, int H, const char *L = 0);
  Fl_Text_Edit_Window(int W, int H, const char *L = 0);
  Fl_Text_Edit_Window();
  Fl_Box *title_box;
  Fl_Text_Editor *text_editor;
  Fl_Return_Button *return_button;
private:
  inline void cb_return_button_i(Fl_Return_Button*, void*);
  static void cb_return_button(Fl_Return_Button*, void*);
};
extern "C" { char * fl_text_edit( const char *title, const char *button_text, const char *initial_text, int W = 355, int H = 410 ); }
#endif
