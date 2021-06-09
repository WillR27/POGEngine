#pragma once

#define POG_KEY_UNKNOWN				-1

#define POG_KEY_SPACE				32
#define POG_KEY_APOSTROPHE			39  /* ' */
#define POG_KEY_COMMA				44  /* , */
#define POG_KEY_MINUS				45  /* - */
#define POG_KEY_PERIOD				46  /* . */
#define POG_KEY_SLASH				47  /* / */
#define POG_KEY_0					48
#define POG_KEY_1					49
#define POG_KEY_2					50
#define POG_KEY_3					51
#define POG_KEY_4					52
#define POG_KEY_5					53
#define POG_KEY_6					54
#define POG_KEY_7					55
#define POG_KEY_8					56
#define POG_KEY_9					57
#define POG_KEY_SEMICOLON			59  /* ; */
#define POG_KEY_EQUAL				61  /* = */
#define POG_KEY_A					65
#define POG_KEY_B					66
#define POG_KEY_C					67
#define POG_KEY_D					68
#define POG_KEY_E					69
#define POG_KEY_F					70
#define POG_KEY_G					71
#define POG_KEY_H					72
#define POG_KEY_I					73
#define POG_KEY_J					74
#define POG_KEY_K					75
#define POG_KEY_L					76
#define POG_KEY_M					77
#define POG_KEY_N					78
#define POG_KEY_O					79
#define POG_KEY_P					80
#define POG_KEY_Q					81
#define POG_KEY_R					82
#define POG_KEY_S					83
#define POG_KEY_T					84
#define POG_KEY_U					85
#define POG_KEY_V					86
#define POG_KEY_W					87
#define POG_KEY_X					88
#define POG_KEY_Y					89
#define POG_KEY_Z					90
#define POG_KEY_LEFT_BRACKET		91  /* [ */
#define POG_KEY_BACKSLASH			92  /* \ */
#define POG_KEY_RIGHT_BRACKET		93  /* ] */
#define POG_KEY_GRAVE_ACCENT		96  /* ` */
#define POG_KEY_WORLD_1				161 /* non-US #1 */
#define POG_KEY_WORLD_2				162 /* non-US #2 */

#define POG_KEY_ESCAPE				256
#define POG_KEY_ENTER				257
#define POG_KEY_TAB					258
#define POG_KEY_BACKSPACE			259
#define POG_KEY_INSERT				260
#define POG_KEY_DELETE				261
#define POG_KEY_RIGHT				262
#define POG_KEY_LEFT				263
#define POG_KEY_DOWN				264
#define POG_KEY_UP					265
#define POG_KEY_PAGE_UP				266
#define POG_KEY_PAGE_DOWN			267
#define POG_KEY_HOME				268
#define POG_KEY_END					269
#define POG_KEY_CAPS_LOCK			280
#define POG_KEY_SCROLL_LOCK			281
#define POG_KEY_NUM_LOCK			282
#define POG_KEY_PRINT_SCREEN		283
#define POG_KEY_PAUSE				284
#define POG_KEY_F1					290
#define POG_KEY_F2					291
#define POG_KEY_F3					292
#define POG_KEY_F4					293
#define POG_KEY_F5					294
#define POG_KEY_F6					295
#define POG_KEY_F7					296
#define POG_KEY_F8					297
#define POG_KEY_F9					298
#define POG_KEY_F10					299
#define POG_KEY_F11					300
#define POG_KEY_F12					301
#define POG_KEY_F13					302
#define POG_KEY_F14					303
#define POG_KEY_F15					304
#define POG_KEY_F16					305
#define POG_KEY_F17					306
#define POG_KEY_F18					307
#define POG_KEY_F19					308
#define POG_KEY_F20					309
#define POG_KEY_F21					310
#define POG_KEY_F22					311
#define POG_KEY_F23					312
#define POG_KEY_F24					313
#define POG_KEY_F25					314
#define POG_KEY_KP_0				320
#define POG_KEY_KP_1				321
#define POG_KEY_KP_2				322
#define POG_KEY_KP_3				323
#define POG_KEY_KP_4				324
#define POG_KEY_KP_5				325
#define POG_KEY_KP_6				326
#define POG_KEY_KP_7				327
#define POG_KEY_KP_8				328
#define POG_KEY_KP_9				329
#define POG_KEY_KP_DECIMAL			330
#define POG_KEY_KP_DIVIDE			331
#define POG_KEY_KP_MULTIPLY			332
#define POG_KEY_KP_SUBTRACT			333
#define POG_KEY_KP_ADD				334
#define POG_KEY_KP_ENTER			335
#define POG_KEY_KP_EQUAL			336
#define POG_KEY_LEFT_SHIFT			340
#define POG_KEY_LEFT_CONTROL		341
#define POG_KEY_LEFT_ALT			342
#define POG_KEY_LEFT_SUPER			343
#define POG_KEY_RIGHT_SHIFT			344
#define POG_KEY_RIGHT_CONTROL		345
#define POG_KEY_RIGHT_ALT			346
#define POG_KEY_RIGHT_SUPER			347
#define POG_KEY_MENU				348

#define POG_MAX_KEY_VALUE			350

#define POG_INPUT_NONE			   -1
#define POG_INPUT_RELEASE			0
#define POG_INPUT_PRESS        		1
#define POG_INPUT_REPEAT  			2

#define POG_MOUSE_BUTTON_1			0
#define POG_MOUSE_BUTTON_2			1
#define POG_MOUSE_BUTTON_3			2
#define POG_MOUSE_BUTTON_4			3
#define POG_MOUSE_BUTTON_5			4
#define POG_MOUSE_BUTTON_6			5
#define POG_MOUSE_BUTTON_7			6
#define POG_MOUSE_BUTTON_8			7
#define POG_MOUSE_BUTTON_LAST		POG_MOUSE_BUTTON_8
#define POG_MOUSE_BUTTON_LEFT		POG_MOUSE_BUTTON_1
#define POG_MOUSE_BUTTON_RIGHT		POG_MOUSE_BUTTON_2
#define POG_MOUSE_BUTTON_MIDDLE		POG_MOUSE_BUTTON_3

#define POG_MAX_MOUSE_VALUE			10

#define POG_MOD_ANY				   -0x0001
#define POG_MOD_NONE				0x0000
#define POG_MOD_SHIFT				0x0001
#define POG_MOD_CONTROL				0x0002
#define POG_MOD_ALT					0x0004
#define POG_MOD_SUPER				0x0008
#define POG_MOD_CAPS_LOCK			0x0010
#define POG_MOD_NUM_LOCK			0x0020