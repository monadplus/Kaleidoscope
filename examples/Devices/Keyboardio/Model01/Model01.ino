#include <Kaleidoscope.h>

#include <Kaleidoscope-Macros.h>
#include <Kaleidoscope-LEDControl.h>
#include <Kaleidoscope-NumPad.h>
#include <Kaleidoscope-TapDance.h>
#include <Kaleidoscope-OneShot.h>
#include <Kaleidoscope-LED-ActiveModColor.h>

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

KALEIDOSCOPE_INIT_PLUGINS(
  LEDControl,
  LEDOff,
  NumPad,
  Macros,
  TapDance,
  OneShot,
  ActiveModColorEffect // Last always
);

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

// Tap Dance
enum {
  TD_PAR_L,
  TD_PAR_R
};

// Layers
enum {
  _PRIMARY,
  _NAV, // Blue
  _AUX, // Red
  _EMPTY,

  LAYER_MAX = _EMPTY
};

// Macros
enum {
  M_F11,
};

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// Macro

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (macro_id == M_F11) {
    if (!keyToggledOn(event.state)) {
      return MACRO_NONE;
    } else {
      return MACRO(T(F11));
    }
  }
  return MACRO_NONE;
}

///////////////////////////////////////////////////////////////////////////////////
// Tap Dance

void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count,
                    kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {

    // Left par, Left bracket, Left curly bracket
    case TD_PAR_L:
      switch (tap_dance_action) {
        case kaleidoscope::plugin::TapDance::ActionType::Hold:
          return tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_LeftBracket));
        default:
          return tapDanceActionKeys(tap_count, tap_dance_action,
                                    Key_KeypadLeftParen, Key_LeftBracket);
      }

    // Right par, Right bracket, Right curly bracket
    case TD_PAR_R:
      switch (tap_dance_action) {
        case kaleidoscope::plugin::TapDance::ActionType::Hold:
          return tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_RightBracket));
        default:
          return tapDanceActionKeys(tap_count, tap_dance_action,
                                    Key_KeypadLeftParen, Key_LeftBracket);
      }
  }
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

KEYMAPS(
  [_PRIMARY] = KEYMAP_STACKED
  (
    XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___

   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
        ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___
  ),

  [_NAV] = KEYMAP_STACKED
  (
    XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___

   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
        ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___
  ),

  [_AUX] =  KEYMAP_STACKED
  (
    XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___

   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
        ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___
  ),


  [_EMPTY] = KEYMAP_STACKED
  (
    XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___

   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
        ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX

   ,XXX ,XXX ,XXX ,XXX
   ,___
   )
);

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

void setup() {
  Kaleidoscope.setup();

  // Tap dance
  TapDance.time_out = 300;

  // ActiveModcolor
  ActiveModColorEffect.setOneShotColor(CRGB(255, 255, 0));
  ActiveModColorEffect.setStickyColor(CRGB(255, 0, 0));
  ActiveModColorEffect.setHighlightColor(CRGB(255, 255, 255));
}

void loop() {
  Kaleidoscope.loop();
}
