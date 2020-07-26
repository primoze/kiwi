#ifndef KW_KW_INTERNAL_H
#define KW_KW_INTERNAL_H

#include <kiwi/core/input-event.h>
#include "kiwi/core/widget.h"
#include "kiwi/core/old-renderdriver.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GUIHandler)(void);

typedef enum KW_GUIEventHandlerType {
  KW_GUI_ONFONTCHANGED,
  KW_GUI_ONTEXTCOLORCHANGED,
  KW_GUI_ONTILESETCHANGED,
  KW_GUIEVENTHANDLER_TOTAL
} KW_GUIEventHandlerType;

struct KW_GUI {
  KW_Texture * tilesettexture;
  KW_Surface * tilesetsurface;
  KW_OldRenderDriver * renderer;
  KW_Widget * rootwidget; /* the parent to all parent-less widgets :) */
  KW_Font * font;
  KW_Font * defaultfont;
  KW_Color textcolor;
  
  KW_Widget * currentmouseover; /* the current widget that has mouse over */
  KW_Widget * currentfocus; /* which widget was the last focused/clicked */
  KW_Widget * currentdrag; /* the widget where the drag started */
  SDL_bool cursordown; /* indicates whether the cursor is clicked or not */
  SDL_bool cursorwasdown;
  
  SDL_bool handleevents;
  KW_InputEvent inputEventQueue[1024];
  int evqueuesize;
  SDL_mutex * evqueuelock;
  
  struct {
    struct KW_GUICallback {
      GUIHandler handler;
      void * priv;
    } * handlers;
    unsigned int      count;
  } eventhandlers[KW_GUIEVENTHANDLER_TOTAL];
};

void AddGUIHandler(KW_GUI * gui, KW_GUIEventHandlerType handlertype, GUIHandler handler, void * priv);
void RemoveGUIHandler(KW_GUI * gui, KW_GUIEventHandlerType handlertype, GUIHandler handler, void * priv);
void MouseMoved(KW_GUI * gui, int mousex, int mousey, int xrel, int yrel);
void MousePressed(KW_GUI * gui, int mousex, int mousey, int button);
void MouseReleased(KW_GUI * gui, int mousex, int mousey, int button);
void TextInputReady(KW_GUI * gui, uint8_t const * text);
void KeyUp(KW_GUI * gui, KW_InputKey key);
void KeyDown(KW_GUI * gui, KW_InputKey key);

#ifdef __cplusplus
}
#endif

#endif
