#include QMK_KEYBOARD_H

// ==========================================
// 1. CUSTOM KEYCODES & VARIABLES
// ==========================================
enum custom_keycodes {
    SHFT_LCK = SAFE_RANGE
};

bool is_shift_locked = false;

// ==========================================
// 2. CUSTOM KEY LOGIC (Shift Lock)
// ==========================================
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SHFT_LCK:
            if (record->event.pressed) {
                is_shift_locked = !is_shift_locked; 
                
                if (is_shift_locked) {
                    register_code(KC_LSFT);   
                } else {
                    unregister_code(KC_LSFT); 
                }
            }
            return false; 
            
        default:
            return true; 
    }
}

// ==========================================
// 3. LAYOUTS
// ==========================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        SHFT_LCK, KC_ESC,    TG(1),       // Top Row (Base) - Shift Lock | Escape | Toggle
        RGB_TOG,  RGB_MOD,   RGB_HUI,     // Middle Row (Base): LED Controls
        KC_Z,     KC_X,      KC_C         // Bottom Row (Base): Standard Keys
    ),
    [1] = LAYOUT_ortho_3x3(
        KC_F1,        KC_Q,         TG(1),       // Top Row: F1 | Q | Toggle
        LALT(KC_F2),  LALT(KC_F3),  LALT(KC_F4), // Middle Row: Alt+F2 | Alt+F3 | Alt+F4
        KC_LCTL,      LCTL(KC_F1),  LALT(KC_F1)  // Bottom Row: Ctrl | Ctrl+F1 | Alt+F1
    )
};

// ==========================================
// 4. ROTARY ENCODER
// ==========================================
#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    // Layer 0 (Base): Left = Open File Explorer | Right = Open Task Manager
    [0] = { ENCODER_CCW_CW(LGUI(KC_E), LCTL(LSFT(KC_ESC))) },
    
    // Layer 1 (EVE): Left = Previous Browser Tab | Right = Next Browser Tab
    [1] = { ENCODER_CCW_CW(LCTL(LSFT(KC_TAB)), LCTL(KC_TAB)) } 
};
#endif

// ==========================================
// 5. OLED SCREEN
// ==========================================
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0; 
}

bool oled_task_user(void) {
    oled_write_P(PSTR("My Hackpad\n"), false);
    oled_write_P(PSTR("----------\n"), false);
    
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base \n"), false);
            if (is_shift_locked) {
                oled_write_P(PSTR("[SHIFT LCK ON] \n"), false);
            } else {
                oled_write_P(PSTR("               \n"), false);
            }
            break;
        case 1:
            oled_write_P(PSTR("EVE Online\n"), false); 
            break;
        default:
            oled_write_P(PSTR("Unknown\n"), false);
            break;
    }
    return false;
}
#endif

// ==========================================
// 6. PER-KEY RGB LIGHTING
// ==========================================
#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        
        case 0: 
            rgb_matrix_set_color_all(0, 0, 50); 
            
            rgb_matrix_set_color(5, 255, 100, 0); 
            rgb_matrix_set_color(4, 255, 0, 255); 
            rgb_matrix_set_color(3, 0, 255, 255); 
            
            rgb_matrix_set_color(7, 255, 255, 255); 
            
            if (is_shift_locked) {
                rgb_matrix_set_color(8, 255, 0, 0); 
            }
            break;

        case 1: 
            rgb_matrix_set_color_all(0, 0, 0); 
            
            rgb_matrix_set_color(8, 255, 0, 0);
            rgb_matrix_set_color(7, 0, 255, 255);
            
            rgb_matrix_set_color(5, 255, 100, 0);   
            rgb_matrix_set_color(4, 255, 100, 0);   
            rgb_matrix_set_color(3, 255, 100, 0);   
            
            rgb_matrix_set_color(2, 150, 0, 255);   
            rgb_matrix_set_color(1, 150, 0, 255);   
            rgb_matrix_set_color(0, 150, 0, 255);   
            break;
    }
    return false;
}
#endif