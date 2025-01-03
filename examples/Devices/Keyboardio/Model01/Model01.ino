// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-LED-Palette-Theme.h"
#include "Kaleidoscope-Colormap.h"
#include "Kaleidoscope-HostPowerManagement.h"
// Extra
#include <Kaleidoscope-LED-ActiveModColor.h>
#include <Kaleidoscope-LED-ActiveLayerColor.h>
#include <Kaleidoscope-TapDance.h>
#include <Kaleidoscope-OneShot.h>
#include <Kaleidoscope-HostOS.h> // Unicode depends on it
#include <Kaleidoscope-Unicode.h>
#include <Kaleidoscope-CycleTimeReport.h>

// Tap Dance
enum {
  LPB,               // Left paren, bracket, braces
  RPB,               // Right paren, bracket, braces
  UNICODE_A,
  UNICODE_E,
  UNICODE_O,
  UNICODE_CAPITAL_A,
  UNICODE_CAPITAL_E,
  UNICODE_CAPITAL_O,
  NEXT_PREVIOUS_TRACK,
};

// Layers
enum {
  _PRIMARY,
  _NAV,
  _AUX,
  _EMPTY,

  LAYER_MAX = _EMPTY
};

// Macros
enum {
  UNICODE_A_GRAVE,
  UNICODE_A_ACUTE,
  UNICODE_E_GRAVE,
  UNICODE_E_ACUTE,
  UNICODE_I_ACUTE,
  UNICODE_O_GRAVE,
  UNICODE_O_ACUTE,
  UNICODE_U_ACUTE,
  UNICODE_CAPITAL_A_GRAVE,
  UNICODE_CAPITAL_A_ACUTE,
  UNICODE_CAPITAL_E_GRAVE,
  UNICODE_CAPITAL_E_ACUTE,
  UNICODE_CAPITAL_I_ACUTE,
  UNICODE_CAPITAL_O_GRAVE,
  UNICODE_CAPITAL_O_ACUTE,
  UNICODE_CAPITAL_U_ACUTE,
  UNICODE_N_TILDE,
  UNICODE_C_CEDILLA,
  F11,
};

#define Key_AT    LSHIFT(Key_2)
#define Key_STAR  LSHIFT(Key_8)
#define Key_DOLLR LSHIFT(Key_4)
#define Key_CARET LSHIFT(Key_6)
#define Key_PRCNT LSHIFT(Key_5)
#define Key_EXCLM LSHIFT(Key_1)
#define Key_HASH  LSHIFT(Key_3)
#define Key_AND   LSHIFT(Key_7)
#define Key_LCB   LSHIFT(Key_LeftBracket)
#define Key_RCB   LSHIFT(Key_RightBracket)
#define Key_Plus  LSHIFT(Key_Equals)

#define Key_PlayPause Consumer_PlaySlashPause
#define Key_LArrow Key_LeftArrow
#define Key_RArrow Key_RightArrow
#define Key_DnArrow Key_DownArrow
#define Key_PageDn Key_PageDown

#define Key_Underscore LSHIFT(Key_Minus)

KEYMAPS(
  [_PRIMARY] = KEYMAP_STACKED
  (
    M(F11)       ,Key_1 ,Key_2   ,Key_3     ,Key_4     ,Key_5  ,Key_Backslash
   ,Key_Backtick ,Key_Q ,Key_W   ,Key_E     ,Key_R     ,Key_T  ,TD(LPB)
   ,Key_Tab      ,Key_A ,Key_S   ,Key_D     ,Key_F     ,Key_G
   ,XXX          ,Key_Z ,Key_X   ,Key_C     ,Key_V     ,Key_B  ,Key_Semicolon

   ,OSM(LeftControl) ,Key_Backspace ,OSM(LeftShift) ,Key_Escape
   ,OSL(_NAV)

   ,Key_Equals     ,Key_6     ,Key_7     ,Key_8      ,Key_9      ,Key_0     ,Key_PlayPause
   ,TD(RPB)        ,Key_Y     ,Key_U     ,Key_I      ,Key_O      ,Key_P     ,TD(NEXT_PREVIOUS_TRACK)
                   ,Key_H     ,Key_J     ,Key_K      ,Key_L      ,Key_Quote ,M(UNICODE_N_TILDE)
   ,Key_Minus      ,Key_N     ,Key_M     ,Key_Comma  ,Key_Period ,Key_Slash ,Key_PrintScreen

   ,OSM(LeftGui) ,Key_Enter ,Key_Spacebar , OSM(LeftAlt)
   ,OSL(_AUX)
  ),

  [_NAV] = KEYMAP_STACKED
  (
    ___ ,XXX ,XXX ,XXX ,XXX ,XXX ,Key_Mute
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,Key_VolumeUp
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX
   ,XXX ,XXX ,XXX ,XXX ,XXX ,XXX ,Key_VolumeDown

   ,___ ,___ ,___ ,OSM(LeftGui)
   ,OSL(_EMPTY)

   ,LGUI(Key_Z) ,XXX        ,XXX        ,XXX         ,XXX        ,XXX        ,XXX
   ,Key_Home    ,XXX        ,XXX        ,XXX         ,XXX        ,XXX        ,XXX
                ,Key_PageUp ,Key_LArrow ,Key_DnArrow ,Key_UpArrow,Key_RArrow ,XXX
   ,Key_End     ,Key_PageDn ,XXX        ,XXX         ,XXX        ,XXX        ,XXX

   ,___ ,___ ,___ ,___
   ,OSL(_EMPTY)
  ),

  [_AUX] = KEYMAP_STACKED
  (
    ___   ,Key_F1                ,Key_F2                ,Key_F3                     ,Key_F4                ,Key_F5                     ,Key_F11
   ,XXX   ,TD(UNICODE_CAPITAL_A) ,TD(UNICODE_CAPITAL_E) ,M(UNICODE_CAPITAL_I_ACUTE) ,TD(UNICODE_CAPITAL_O) ,M(UNICODE_CAPITAL_U_ACUTE) ,XXX
   ,XXX   ,TD(UNICODE_A)         ,TD(UNICODE_E)         ,M(UNICODE_I_ACUTE)         ,TD(UNICODE_O)         ,M(UNICODE_U_ACUTE)
   ,XXX   ,XXX                   ,XXX                   ,M(UNICODE_C_CEDILLA)       ,XXX                   ,XXX                        ,XXX

   ,___ ,Key_Backspace ,Key_Delete ,___
   ,OSL(_EMPTY)

   ,Key_F12        ,Key_F6     ,Key_F7 ,Key_F8 ,Key_F9 ,Key_F10   ,XXX
   ,Key_Underscore ,XXX        ,Key_1  ,Key_2  ,Key_3  ,XXX       ,Key_Equals
                   ,Key_0      ,Key_4  ,Key_5  ,Key_6  ,Key_Minus ,Key_Plus
   ,Key_Comma      ,Key_Period ,Key_7  ,Key_8  ,Key_9  ,XXX       ,XXX

   ,___ ,___ ,___ ,___
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

static void unicode(uint32_t character, uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Unicode.type(character);
  }
}

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {

    case UNICODE_A_GRAVE:
      unicode(0x00E0, event.state);
      break;
    case UNICODE_A_ACUTE:
      unicode(0x00E1, event.state);
      break;
    case UNICODE_CAPITAL_A_GRAVE:
      unicode(0x00C0, event.state);
      break;
    case UNICODE_CAPITAL_A_ACUTE:
      unicode(0x00C1, event.state);
      break;

    case UNICODE_E_GRAVE:
      unicode(0x00E8, event.state);
      break;
    case UNICODE_E_ACUTE:
      unicode(0x00E9, event.state);
      break;
    case UNICODE_CAPITAL_E_GRAVE:
      unicode(0x00C8, event.state);
      break;
    case UNICODE_CAPITAL_E_ACUTE:
      unicode(0x00C9, event.state);
      break;

    case UNICODE_O_GRAVE:
      unicode(0x00F2, event.state);
      break;
    case UNICODE_O_ACUTE:
      unicode(0x00F3, event.state);
      break;
    case UNICODE_CAPITAL_O_GRAVE:
      unicode(0x00D2, event.state);
      break;
    case UNICODE_CAPITAL_O_ACUTE:
      unicode(0x00D3, event.state);
      break;

    case UNICODE_I_ACUTE:
      unicode(0x00ED, event.state);
      break;
    case UNICODE_CAPITAL_I_ACUTE:
      unicode(0x00CD, event.state);
      break;

    case UNICODE_U_ACUTE:
      unicode(0x00FA, event.state);
      break;
    case UNICODE_CAPITAL_U_ACUTE:
      unicode(0x00DA, event.state);
      break;

    case UNICODE_N_TILDE:
      unicode(0x00F1, event.state);
      break;

    case UNICODE_C_CEDILLA:
      unicode(0x00E7, event.state);
      break;

    case F11:
      if (!keyToggledOn(event.state)) {
        return MACRO_NONE;
      } else {
        return MACRO(T(F11));
      }
      break;

  }
  return MACRO_NONE;
}

void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count,
                    kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {

    case LPB:
      switch (tap_dance_action) {
        case kaleidoscope::plugin::TapDance::ActionType::Hold:
          return tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_LeftBracket));
        default:
          return tapDanceActionKeys(tap_count, tap_dance_action,
                                    LSHIFT(Key_9), Key_LeftBracket);
      }

    case RPB:
      switch (tap_dance_action) {
        case kaleidoscope::plugin::TapDance::ActionType::Hold:
          return tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_RightBracket));
        default:
          return tapDanceActionKeys(tap_count, tap_dance_action,
                                    LSHIFT(Key_0), Key_RightBracket);
      }

    case UNICODE_A:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                M(UNICODE_A_GRAVE),
                                M(UNICODE_A_ACUTE));

    case UNICODE_CAPITAL_A:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                M(UNICODE_CAPITAL_A_GRAVE),
                                M(UNICODE_CAPITAL_A_ACUTE));

    case UNICODE_E:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                M(UNICODE_E_GRAVE),
                                M(UNICODE_E_ACUTE));

    case UNICODE_CAPITAL_E:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                M(UNICODE_CAPITAL_E_GRAVE),
                                M(UNICODE_CAPITAL_E_ACUTE));

    case UNICODE_O:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                M(UNICODE_O_GRAVE),
                                M(UNICODE_O_ACUTE));

    case UNICODE_CAPITAL_O:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                M(UNICODE_CAPITAL_O_GRAVE),
                                M(UNICODE_CAPITAL_O_ACUTE));

    case NEXT_PREVIOUS_TRACK:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                Consumer_ScanNextTrack,
                                Consumer_ScanPreviousTrack);
  }
}

void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
    case kaleidoscope::plugin::HostPowerManagement::Suspend:
      LEDControl.set_all_leds_to({0, 0, 0});
      LEDControl.syncLeds();
      LEDControl.disable();
      break;
    case kaleidoscope::plugin::HostPowerManagement::Resume:
      LEDControl.enable();
      LEDControl.refreshAll();
      break;
    case kaleidoscope::plugin::HostPowerManagement::Sleep:
      break;
  }
}

KALEIDOSCOPE_INIT_PLUGINS(
  EEPROMSettings,
  EEPROMKeymap,
  Focus,
  FocusSettingsCommand,
  FocusEEPROMCommand,
  Macros,
  LEDControl,
  LEDOff,
  LEDPaletteTheme,
  ColormapEffect,
  HostPowerManagement,
  CycleTimeReport,
  HostOS,
  Unicode,
  TapDance,
  OneShot,
  ActiveModColorEffect // Last always
);

// Colormap:
//   $ ./colormap/apply ega
//
// Modify ./colormap/colormap.txt and define your own palette
//
// 0  0  0  0
// 0  0  0  0
// 0  0  0  0
// 0  0  0  0
// 0  0  0  0
// 0  0  0  0
// 0  0  9  1
// 0  4  0  3
//
// The colormap.txt does a zig-zag

void setup() {
  // $ ls /dev/serial/by-id/
  // $ cat /dev/ttyACM0 | rg time
  Kaleidoscope.serialPort().begin(9600); // CycleTimeReport
  Kaleidoscope.setup();

  // Tap dance
  TapDance.setTimeout(200);

  // OneShot
  OneShot.setTimeout(750);
  OneShot.disableStickabilityForModifiers();
  OneShot.disableStickabilityForLayers();

  // ActiveModcolor
  ActiveModColorEffect.setOneShotColor(CRGB(255, 255, 0));
  ActiveModColorEffect.setStickyColor(CRGB(255, 0, 0));
  ActiveModColorEffect.setHighlightColor(CRGB(255, 255, 255));

  ColormapEffect.max_layers(LAYER_MAX);
  ColormapEffect.activate();
}

void loop() {
  Kaleidoscope.loop();

  if (Layer.isActive(_EMPTY)) {
    LEDControl.set_all_leds_to(CRGB(0x0, 0x0, 0x0));
  }
}
