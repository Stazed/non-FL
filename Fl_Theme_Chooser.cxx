// generated by Fast Light User Interface Designer (fluid) version 1.0309

#include "Fl_Theme_Chooser.H"
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Double_Window.H>
#include "Clean_Theme.H"
#include "Crystal_Theme.H"
#include "Gleam_Theme.H"


Fl_Color_Button::Fl_Color_Button( int X, int Y, int W, int H, const char *L ) : Fl_Button( X, Y, W, H, L ) {
}

int Fl_Color_Button::handle( int m ) {
  switch ( m )
  {
  	case FL_PUSH:
  	{
  		uchar r, g, b;
  
  		Fl::get_color( color(), r, g, b );
  
  		fl_color_chooser( label(), r, g, b );
  
  		color( fl_rgb_color( r, g, b ) );
  		
  		do_callback();
  			
  		return 1;
  	}
  }
  
  return Fl_Button::handle( m );
}

void Fl_Theme_Chooser::cb_theme_choice_i(Fl_Choice* o, void*) {
  Fl_Theme::set( o->mvalue()->label() );

redraw();
}
void Fl_Theme_Chooser::cb_theme_choice(Fl_Choice* o, void* v) {
  ((Fl_Theme_Chooser*)(o->parent()))->cb_theme_choice_i(o,v);
}

void Fl_Theme_Chooser::cb_color_scheme_choice_i(Fl_Choice* o, void*) {
  Fl_Color_Scheme::set( o->mvalue()->label() );

redraw();
}
void Fl_Theme_Chooser::cb_color_scheme_choice(Fl_Choice* o, void* v) {
  ((Fl_Theme_Chooser*)(o->parent()))->cb_color_scheme_choice_i(o,v);
}

void Fl_Theme_Chooser::cb_OK_i(Fl_Return_Button*, void*) {
  Fl_Theme::save(); Fl_Color_Scheme::save(); hide();
}
void Fl_Theme_Chooser::cb_OK(Fl_Return_Button* o, void* v) {
  ((Fl_Theme_Chooser*)(o->parent()))->cb_OK_i(o,v);
}

void Fl_Theme_Chooser::cb_background_color_button_i(Fl_Color_Button* o, void*) {
  uchar r,g,b;

Fl::get_color( o->color(), r,g,b );

Fl::background( r,g,b );

o->window()->redraw();
}
void Fl_Theme_Chooser::cb_background_color_button(Fl_Color_Button* o, void* v) {
  ((Fl_Theme_Chooser*)(o->parent()))->cb_background_color_button_i(o,v);
}

void Fl_Theme_Chooser::cb_background2_color_button_i(Fl_Color_Button* o, void*) {
  uchar r,g,b;

Fl::get_color( o->color(), r,g,b );

Fl::background2( r,g,b );

o->window()->redraw();
}
void Fl_Theme_Chooser::cb_background2_color_button(Fl_Color_Button* o, void* v) {
  ((Fl_Theme_Chooser*)(o->parent()))->cb_background2_color_button_i(o,v);
}

void Fl_Theme_Chooser::cb_foreground_color_button_i(Fl_Color_Button* o, void*) {
  uchar r,g,b;

Fl::get_color( o->color(), r,g,b );

Fl::foreground( r,g,b );

o->window()->redraw();
}
void Fl_Theme_Chooser::cb_foreground_color_button(Fl_Color_Button* o, void* v) {
  ((Fl_Theme_Chooser*)(o->parent()))->cb_foreground_color_button_i(o,v);
}
Fl_Theme_Chooser::Fl_Theme_Chooser(int X, int Y, int W, int H, const char *L)
  : Fl_Double_Window(X, Y, W, H, L) {
  _Fl_Theme_Chooser();
}

Fl_Theme_Chooser::Fl_Theme_Chooser(int W, int H, const char *L)
  : Fl_Double_Window(0, 0, W, H, L) {
  clear_flag(16);
  _Fl_Theme_Chooser();
}

Fl_Theme_Chooser::Fl_Theme_Chooser()
  : Fl_Double_Window(0, 0, 435, 380, "Theme") {
  clear_flag(16);
  _Fl_Theme_Chooser();
}

void Fl_Theme_Chooser::_Fl_Theme_Chooser() {
this->box(FL_FLAT_BOX);
this->color(FL_BACKGROUND_COLOR);
this->selection_color(FL_BACKGROUND_COLOR);
this->labeltype(FL_NO_LABEL);
this->labelfont(0);
this->labelsize(14);
this->labelcolor(FL_FOREGROUND_COLOR);
this->align(Fl_Align(FL_ALIGN_TOP));
this->when(FL_WHEN_RELEASE);
{ theme_choice = new Fl_Choice(120, 20, 300, 25, "Theme:");
  theme_choice->down_box(FL_BORDER_BOX);
  theme_choice->callback((Fl_Callback*)cb_theme_choice);
} // Fl_Choice* theme_choice
{ color_scheme_choice = new Fl_Choice(120, 48, 300, 25, "Color Scheme:");
  color_scheme_choice->down_box(FL_BORDER_BOX);
  color_scheme_choice->callback((Fl_Callback*)cb_color_scheme_choice);
} // Fl_Choice* color_scheme_choice
{ Fl_Return_Button* o = new Fl_Return_Button(355, 345, 75, 25, "OK");
  o->callback((Fl_Callback*)cb_OK);
} // Fl_Return_Button* o
{ Fl_Group* o = new Fl_Group(5, 215, 425, 120, "Example");
  o->box(FL_ENGRAVED_FRAME);
  { Fl_Scrollbar* o = new Fl_Scrollbar(155, 240, 265, 25, "Scroll Bar");
    o->type(1);
    o->align(Fl_Align(FL_ALIGN_TOP));
  } // Fl_Scrollbar* o
  { Fl_Check_Button* o = new Fl_Check_Button(15, 230, 120, 15, "Check Button");
    o->down_box(FL_DOWN_BOX);
  } // Fl_Check_Button* o
  { new Fl_Dial(155, 275, 35, 35, "Dial");
  } // Fl_Dial* o
  { Fl_Progress* o = new Fl_Progress(240, 300, 185, 30, "Progress");
    o->value( 0.50 );
  } // Fl_Progress* o
  { new Fl_Light_Button(15, 285, 120, 35, "Light Button");
  } // Fl_Light_Button* o
  o->end();
} // Fl_Group* o
{ Fl_Color_Button* o = background_color_button = new Fl_Color_Button(120, 76, 300, 25, "Background 1:");
  background_color_button->box(FL_BORDER_BOX);
  background_color_button->color(FL_BACKGROUND_COLOR);
  background_color_button->selection_color(FL_BACKGROUND_COLOR);
  background_color_button->labeltype(FL_NORMAL_LABEL);
  background_color_button->labelfont(0);
  background_color_button->labelsize(14);
  background_color_button->labelcolor(FL_FOREGROUND_COLOR);
  background_color_button->callback((Fl_Callback*)cb_background_color_button);
  background_color_button->align(Fl_Align(FL_ALIGN_LEFT));
  background_color_button->when(FL_WHEN_RELEASE_ALWAYS);
  o->color( FL_BACKGROUND_COLOR );
} // Fl_Color_Button* background_color_button
{ Fl_Color_Button* o = background2_color_button = new Fl_Color_Button(120, 104, 300, 25, "Background 2:");
  background2_color_button->box(FL_BORDER_BOX);
  background2_color_button->color(FL_BACKGROUND_COLOR);
  background2_color_button->selection_color(FL_BACKGROUND_COLOR);
  background2_color_button->labeltype(FL_NORMAL_LABEL);
  background2_color_button->labelfont(0);
  background2_color_button->labelsize(14);
  background2_color_button->labelcolor(FL_FOREGROUND_COLOR);
  background2_color_button->callback((Fl_Callback*)cb_background2_color_button);
  background2_color_button->align(Fl_Align(FL_ALIGN_LEFT));
  background2_color_button->when(FL_WHEN_RELEASE);
  o->color( FL_BACKGROUND2_COLOR );
} // Fl_Color_Button* background2_color_button
{ Fl_Color_Button* o = foreground_color_button = new Fl_Color_Button(120, 132, 300, 25, "Foreground:");
  foreground_color_button->box(FL_BORDER_BOX);
  foreground_color_button->color(FL_BACKGROUND_COLOR);
  foreground_color_button->selection_color(FL_BACKGROUND_COLOR);
  foreground_color_button->labeltype(FL_NORMAL_LABEL);
  foreground_color_button->labelfont(0);
  foreground_color_button->labelsize(14);
  foreground_color_button->labelcolor(FL_FOREGROUND_COLOR);
  foreground_color_button->callback((Fl_Callback*)cb_foreground_color_button);
  foreground_color_button->align(Fl_Align(FL_ALIGN_LEFT));
  foreground_color_button->when(FL_WHEN_RELEASE);
  o->color( FL_FOREGROUND_COLOR );
} // Fl_Color_Button* foreground_color_button
{ selection_color_button = new Fl_Color_Button(120, 160, 300, 25, "Selection:");
  selection_color_button->box(FL_BORDER_BOX);
  selection_color_button->color(FL_BACKGROUND_COLOR);
  selection_color_button->selection_color(FL_BACKGROUND_COLOR);
  selection_color_button->labeltype(FL_NORMAL_LABEL);
  selection_color_button->labelfont(0);
  selection_color_button->labelsize(14);
  selection_color_button->labelcolor(FL_FOREGROUND_COLOR);
  selection_color_button->align(Fl_Align(FL_ALIGN_LEFT));
  selection_color_button->when(FL_WHEN_RELEASE);
  selection_color_button->hide();
} // Fl_Color_Button* selection_color_button
{

Fl_Theme::load_default();
Fl_Theme **ta = Fl_Theme::get();

for ( Fl_Theme **t = ta; *t; t++ )
    theme_choice->add( (*t)->name() );

free( ta );

const Fl_Menu_Item *item = theme_choice->find_item( Fl_Theme::current()->name() );

theme_choice->value( item );
}

{
Fl_Color_Scheme **ta = Fl_Color_Scheme::get();

for ( Fl_Color_Scheme **t = ta; *t; t++ )
    color_scheme_choice->add( (*t)->name() );

free( ta );
}
end();
}

void fl_theme_chooser() {
  Fl_Window *w = new Fl_Theme_Chooser();
  
  w->end();
  w->show();
  
  while( w->shown() )
    Fl::wait();
}

void fl_apply_theme()
{
    Fl_Theme::load_default();
}