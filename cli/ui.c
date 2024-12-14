#include <stdbool.h>
#include <stdlib.h>

void * set_flex(void * component);
void * set_hflex(void * component);
void * set_vflex(void * component);
void * set_border(void * component);
void * set_frame(void * component);
void * create_wrap(void * component);
void * create_screen();
void * create_separator();
void * create_filler();
void * create_text(const char *);
void * create_text_integer(int * value);
void * create_list(void **, int, bool);
void screen_loop(void *, void *);
void delete_component(void *);
void delete_components(void **, int);
void delete_screen(void *);

int show_ui() {
  void * screen = create_screen();
  
  void * main_view;

  // create a RAM view header
  void * ram_header_l[3] = { create_filler(), create_text("RAM"), create_filler() };
  void * ram_header = create_list(ram_header_l, 3, false);
  
  // create RAM view editor window
  int lines = 10;
  int data_len = 8;

  void ** ram_window_address_list_l = malloc(lines*sizeof(void*));
  for (int line = 0; line < lines; line++)
    ram_window_address_list_l[line] = create_text("000000");
  void * ram_window_address_list = create_list(ram_window_address_list_l, lines, true);

  void * ram_window_address_l[3] = {
    create_text("ADDRESS"),
    create_separator(),
    set_flex(ram_window_address_list)
  };
  void * ram_window_address = create_list(ram_window_address_l, 3, true);

  void ** ram_window_address_values_list_l_h = malloc(data_len*2*sizeof(void*));
  for (int lineh = 0; lineh < data_len*2; lineh++) {
    ram_window_address_values_list_l_h[lineh++] = create_text("00");
    ram_window_address_values_list_l_h[lineh] = create_text(" ");
  }
  void * ram_window_address_values_list_h = create_list(ram_window_address_values_list_l_h, data_len*2, false);

  void ** ram_window_address_values_list_l = malloc(lines*sizeof(void*));
  for (int line = 0; line < lines; line++) {
    void ** ram_window_address_values_list_lh = malloc(data_len*2*sizeof(void*));
    for (int lineh = 0; lineh < data_len*2; lineh++) {
      ram_window_address_values_list_lh[lineh] = create_text("00");
      ram_window_address_values_list_lh[++lineh] = create_text(" ");
    }
    ram_window_address_values_list_l[line] = create_list(ram_window_address_values_list_lh, data_len*2, false);
  }
  void * ram_window_address_values_list = create_list(ram_window_address_values_list_l, lines, true);

  void * ram_window_address_values_l[3] = {
    ram_window_address_values_list_h,
    create_separator(),
    set_flex(ram_window_address_values_list)
  };
  void * ram_window_address_values = create_list(ram_window_address_values_l, 3, true);

  void * ram_window_l[3] = {
    ram_window_address,
    create_separator(),
    set_flex(ram_window_address_values)
  };
  void * ram_window = create_list(ram_window_l, 3, false);

  // create RAM view
  void * ram_view_l[3] = { ram_header, create_separator(), ram_window };
  void * ram_view = create_wrap(set_border(create_list(ram_view_l, 3, true)));

  void * main_view_l[1] = { ram_view };
  main_view = create_list(main_view_l, 1, true);

  screen_loop(screen, main_view);

  delete_screen(screen);

  exit(0);
  return 0;
}
