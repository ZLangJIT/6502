#include <inttypes.h>
#include <stdio.h>
#include <stdarg.h>
#include <cassert>
#include <cstring>
#include <string>

#include <iostream>

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <string>

#include <stddef.h>
#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <filesystem>

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include "ftxui/screen/color.hpp"
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>

extern "C" {
// #include "handlemap.h"
// #include "simplelock.h"

// struct global_map {
//   struct handlemap * map;
//   struct rwlock lock;
//   global_map() {
//     map = handlemap_init();
//     rwlock_init(&lock);
//   }
//   ~global_map() {
//     handlemap_exit(map);
//   }
// };

// global_map map;

struct ComponentHolder {
  std::shared_ptr<ftxui::ComponentBase> component;
  ComponentHolder(std::shared_ptr<ftxui::ComponentBase> c) : component(c) {}
};

void delete_component(void * component) {
  delete reinterpret_cast<ComponentHolder*>(component);
}

void delete_components(void ** components, int size) {
  for (int i = 0; i < size; i++)
    delete reinterpret_cast<ComponentHolder*>(components[i]);
}

void * set_decorator(void * component, ftxui::Decorator decorator) {
  reinterpret_cast<ComponentHolder*>(component)->component |= decorator;
  return component;
}

void * set_flex(void * component) {
  return set_decorator(component, ftxui::flex);
}

void * set_hflex(void * component) {
  return set_decorator(component, ftxui::yflex);
}

void * set_vflex(void * component) {
  return set_decorator(component, ftxui::xflex);
}

void * set_border(void * component) {
  return set_decorator(component, ftxui::border);
}

void * set_frame(void * component) {
  return set_decorator(component, ftxui::frame);
}

void * create_wrap(void * component) {
  return new ComponentHolder(ftxui::Renderer([=]{return ftxui::flexbox({reinterpret_cast<ComponentHolder*>(component)->component->Render()});}));
}

void * create_separator() {
  return new ComponentHolder(ftxui::Renderer([=]{return ftxui::separator();}));
}

void * create_filler() {
  return new ComponentHolder(ftxui::Renderer([=]{return ftxui::filler();}));
}

void * create_text(const char * text) {
  return new ComponentHolder(ftxui::Renderer([=]{return ftxui::text(text);}));
}

void * create_text_integer(int * value) {
  return new ComponentHolder(ftxui::Renderer([=]{return ftxui::text(std::to_string(*value));}));
}

void * create_text_hex1(uint8_t * value, char * buffer) {
  return new ComponentHolder(ftxui::Renderer([=]{
    int x = *value;
    int place = 1;
    buffer[place] = '\0';
    while (place > 0) {
      buffer[--place] = "0123456789ABCDEF"[x & 15];
      x >>= 4;
    }
    return ftxui::text(buffer);
  }));
}

void * create_text_hex2(uint8_t * value, char * buffer) {
  return new ComponentHolder(ftxui::Renderer([=]{
    int x = *value;
    int place = 2;
    buffer[place] = '\0';
    while (place > 0) {
      buffer[--place] = "0123456789ABCDEF"[x & 15];
      x >>= 4;
    }
    return ftxui::text(buffer);
  }));
}

void * create_text_hex3(uint16_t * value, char * buffer) {
  return new ComponentHolder(ftxui::Renderer([=]{
    int x = *value;
    int place = 3;
    buffer[place] = '\0';
    while (place > 0) {
      buffer[--place] = "0123456789ABCDEF"[x & 15];
      x >>= 4;
    }
    return ftxui::text(buffer);
  }));
}

void * create_text_hex4(uint16_t * value, char * buffer) {
  return new ComponentHolder(ftxui::Renderer([=]{
    int x = *value;
    int place = 4;
    buffer[place] = '\0';
    while (place > 0) {
      buffer[--place] = "0123456789ABCDEF"[x & 15];
      x >>= 4;
    }
    return ftxui::text(buffer);
  }));
}

void * create_text_hex5(uint32_t * value, char * buffer) {
  return new ComponentHolder(ftxui::Renderer([=]{
    int x = *value;
    int place = 5;
    buffer[place] = '\0';
    while (place > 0) {
      buffer[--place] = "0123456789ABCDEF"[x & 15];
      x >>= 4;
    }
    return ftxui::text(buffer);
  }));
}

void * create_text_hex6(uint32_t * value, char * buffer) {
  return new ComponentHolder(ftxui::Renderer([=]{
    int x = *value;
    int place = 6;
    buffer[place] = '\0';
    while (place > 0) {
      buffer[--place] = "0123456789ABCDEF"[x & 15];
      x >>= 4;
    }
    return ftxui::text(buffer);
  }));
}

void * create_text_hex7(uint64_t * value, char * buffer) {
  return new ComponentHolder(ftxui::Renderer([=]{
    int x = *value;
    int place = 5;
    buffer[place] = '\0';
    while (place > 0) {
      buffer[--place] = "0123456789ABCDEF"[x & 15];
      x >>= 4;
    }
    return ftxui::text(buffer);
  }));
}

void * create_text_hex8(uint64_t * value, char * buffer) {
  return new ComponentHolder(ftxui::Renderer([=]{
    int x = *value;
    int place = 8;
    buffer[place] = '\0';
    while (place > 0) {
      buffer[--place] = "0123456789ABCDEF"[x & 15];
      x >>= 4;
    }
    return ftxui::text(buffer);
  }));
}

void * create_list(void ** list, int size, bool is_vertical) {
  return new ComponentHolder(
    is_vertical ? 
      ftxui::Renderer([=] {
        std::vector<ftxui::Element> element_list;
        for (int i = 0; i < size; i++) {
          element_list.push_back(reinterpret_cast<ComponentHolder*>(list[i])->component->Render());
        }
        return ftxui::vbox(element_list);
      })
    :
      ftxui::Renderer([=] {
        std::vector<ftxui::Element> element_list;
        for (int i = 0; i < size; i++) {
          element_list.push_back(reinterpret_cast<ComponentHolder*>(list[i])->component->Render());
        }
        return ftxui::hbox(element_list);
      })
  );
}

void * create_screen() {
  return ftxui::ScreenInteractive::AllocFullscreen();
}

// Renderer returns a std::shared_ptr<ftxui::ComponentBase>

void screen_loop(void * screen, void * component) {
  reinterpret_cast<ftxui::ScreenInteractive*>(screen)->Loop(reinterpret_cast<ComponentHolder*>(component)->component);
}

void delete_screen(void * screen) {
  delete reinterpret_cast<ftxui::ScreenInteractive*>(screen);
}
}
