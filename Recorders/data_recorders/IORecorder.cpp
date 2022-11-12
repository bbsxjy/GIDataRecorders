#include "IORecorder.h"

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

static const int MOUSE_VKEYS[] =
{
    VK_LBUTTON,
    VK_RBUTTON,
    VK_MBUTTON
};

static const int VKEYS[] =
{
    0x41,
    0x42,
    0x43,
    0x44,
    0x45,
    0x46,
    0x47,
    0x48,
    0x49,
    0x4A,
    0x4B,
    0x4C,
    0x4D,
    0x4E,
    0x4F,
    0x50,
    0x51,
    0x52,
    0x53,
    0x54,
    0x55,
    0x56,
    0x57,
    0x58,
    0x59,
    0x5A,
    VK_NUMPAD0,
    VK_NUMPAD1,
    VK_NUMPAD2,
    VK_NUMPAD3,
    VK_NUMPAD4,
    VK_NUMPAD5,
    VK_NUMPAD6,
    VK_NUMPAD7,
    VK_NUMPAD8,
    VK_NUMPAD9,
    VK_MULTIPLY,
    VK_ADD,
    VK_SEPARATOR,
    VK_SUBTRACT,
    VK_DECIMAL,
    VK_DIVIDE,
    VK_F1,
    VK_F2,
    VK_F3,
    VK_F4,
    VK_F5,
    VK_F6,
    VK_F7,
    VK_F8,
    VK_F9,
    VK_F10,
    VK_F11,
    VK_F12,
    VK_F13,
    VK_F14,
    VK_F15,
    VK_F16,
    VK_F17,
    VK_F18,
    VK_F19,
    VK_F20,
    VK_F21,
    VK_F22,
    VK_F23,
    VK_F24,
    VK_NUMLOCK,
    VK_SCROLL,
    VK_BACK,
    VK_TAB,
    VK_CLEAR,
    VK_RETURN,
    VK_SHIFT,
    VK_CONTROL,
    VK_MENU,
    VK_PAUSE,
    VK_CAPITAL,
    VK_ESCAPE,
    VK_SPACE,
    VK_PRIOR,
    VK_NEXT,
    VK_END,
    VK_HOME,
    VK_LEFT,
    VK_UP,
    VK_RIGHT,
    VK_DOWN,
    VK_SELECT,
    VK_PRINT,
    VK_SNAPSHOT,
    VK_INSERT,
    VK_DELETE,
    VK_HELP,
    0x31,
    0x32,
    0x33,
    0x34,
    0x35,
    0x36,
    0x37,
    0x38,
    0x39,
    0x30,
    VK_LWIN,
    VK_RWIN,
    VK_LSHIFT,
    VK_RSHIFT,
    VK_LCONTROL,
    VK_RCONTROL,
    VK_OEM_1,
    VK_OEM_PLUS,
    VK_OEM_COMMA,
    VK_OEM_MINUS,
    VK_OEM_PERIOD,
    VK_OEM_2,
    VK_OEM_3,
    VK_OEM_4,
    VK_OEM_5,
    VK_OEM_6,
    VK_OEM_7,
};

static std::unordered_map<int, std::string> VKEY_TO_STRING_MAP =
{
  {VK_LBUTTON, "LClick"},
  {VK_RBUTTON, "RClick"},
  {VK_MBUTTON, "MClick"},
  {0x41, "a"},
  {0x42, "b"},
  {0x43, "c"},
  {0x44, "d"},
  {0x45, "e"},
  {0x46, "f"},
  {0x47, "g"},
  {0x48, "h"},
  {0x49, "i"},
  {0x4A, "j"},
  {0x4B, "k"},
  {0x4C, "l"},
  {0x4D, "m"},
  {0x4E, "n"},
  {0x4F, "o"},
  {0x50, "p"},
  {0x51, "q"},
  {0x52, "r"},
  {0x53, "s"},
  {0x54, "t"},
  {0x55, "u"},
  {0x56, "v"},
  {0x57, "w"},
  {0x58, "x"},
  {0x59, "y"},
  {0x5A, "z"},
  {VK_NUMPAD0, "0"},
  {VK_NUMPAD1, "1"},
  {VK_NUMPAD2, "2"},
  {VK_NUMPAD3, "3"},
  {VK_NUMPAD4, "4"},
  {VK_NUMPAD5, "5"},
  {VK_NUMPAD6, "6"},
  {VK_NUMPAD7, "7"},
  {VK_NUMPAD8, "8"},
  {VK_NUMPAD9, "9"},
  {VK_MULTIPLY, "*"},
  {VK_ADD, "+"},
  {VK_SEPARATOR, "-"},
  {VK_SUBTRACT, "-"},
  {VK_DECIMAL, "."},
  {VK_DIVIDE, "/"},
  {VK_F1, "F1"},
  {VK_F2, "F2"},
  {VK_F3, "F3"},
  {VK_F4, "F4"},
  {VK_F5, "F5"},
  {VK_F6, "F6"},
  {VK_F7, "F7"},
  {VK_F8, "F8"},
  {VK_F9, "F9"},
  {VK_F10, "F10"},
  {VK_F11, "F11"},
  {VK_F12, "F12"},
  {VK_F13, "F13"},
  {VK_F14, "F14"},
  {VK_F15, "F15"},
  {VK_F16, "F16"},
  {VK_F17, "F17"},
  {VK_F18, "F18"},
  {VK_F19, "F19"},
  {VK_F20, "F20"},
  {VK_F21, "F22"},
  {VK_F22, "F23"},
  {VK_F23, "F24"},
  {VK_F24, "F25"},
  {VK_NUMLOCK, "NUM-LOCK"},
  {VK_SCROLL, "SCROLL-LOCK"},
  {VK_BACK, "BACK"},
  {VK_TAB, "TAB"},
  {VK_CLEAR, "CLEAR"},
  {VK_RETURN, "ENTER"},
  {VK_SHIFT, "SHIFT"},
  {VK_CONTROL, "CTRL"},
  {VK_MENU, "ALT"},
  {VK_PAUSE, "PAUSE"},
  {VK_CAPITAL, "CAP-LOCK"},
  {VK_ESCAPE, "ESC"},
  {VK_SPACE, "SPACE"},
  {VK_PRIOR, "PAGEUP"},
  {VK_NEXT, "PAGEDOWN"},
  {VK_END, "END"},
  {VK_HOME, "HOME"},
  {VK_LEFT, "LEFT"},
  {VK_UP, "UP"},
  {VK_RIGHT, "RIGHT"},
  {VK_DOWN, "DOWN"},
  {VK_SELECT, "SELECT"},
  {VK_PRINT, "PRINT"},
  {VK_SNAPSHOT, "PRTSCRN"},
  {VK_INSERT, "INS"},
  {VK_DELETE, "DEL"},
  {VK_HELP, "HELP"},
  {0x31, "1"},
  {0x32, "2"},
  {0x33, "3"},
  {0x34, "4"},
  {0x35, "5"},
  {0x36, "6"},
  {0x37, "7"},
  {0x38, "8"},
  {0x39, "9"},
  {0x30, "0"},
  {VK_LWIN, "WIN"},
  {VK_RWIN, "WIN"},
  {VK_LSHIFT, "SHIFT"},
  {VK_RSHIFT, "SHIFT"},
  {VK_LCONTROL, "CTRL"},
  {VK_RCONTROL, "CTRL"},
  {VK_OEM_1, ";"},
  {VK_OEM_PLUS, "="},
  {VK_OEM_COMMA, ","},
  {VK_OEM_MINUS, "-"},
  {VK_OEM_PERIOD, "."},
  {VK_OEM_2, "/"},
  {VK_OEM_3, "`"},
  {VK_OEM_4, "["},
  {VK_OEM_5, "|"},
  {VK_OEM_6, "]"},
  {VK_OEM_7, "'"},
};

nlohmann::json IORecorder::Record(nlohmann::json record)
{
    auto mouse = record["mouse"];
	auto mouseX = GameFunctions::GetInstance().Input_GetAxis(GameFunctions::GetInstance().string_to_il2cppi("Mouse X"), nullptr);
	auto mouseY = GameFunctions::GetInstance().Input_GetAxis(GameFunctions::GetInstance().string_to_il2cppi("Mouse Y"), nullptr);

    POINT windows_mouse;

    GetPhysicalCursorPos(&windows_mouse);
    mouse["dx"] = mouseX;
    mouse["dy"] = mouseY;

    GetCursorPos(&windows_mouse);
	mouse["x"] = windows_mouse.x;
	mouse["y"] = windows_mouse.y;
	mouse["game_x"] = this->m_psuedo_mouse.x;
	mouse["game_y"] = this->m_psuedo_mouse.y;
	mouse["is_cursor_visible"] = GameFunctions::GetInstance().Cursor_get_visible(nullptr);
	mouse["buttons"] = {};
    for (int vKey : MOUSE_VKEYS)
    {
        if (KEY_DOWN(vKey)) {
            mouse["buttons"].push_back(VKEY_TO_STRING_MAP[vKey]);
        }
    }
	record["mouse"] = mouse;

	auto keyboard = record["keyboard"];
    keyboard["keys"] = {};
	for (int vKey : VKEYS)
	{
        if (KEY_DOWN(vKey)) {
            keyboard["keys"].push_back(VKEY_TO_STRING_MAP[vKey]);
        }
	}
	record["keyboard"] = keyboard;

	return record;
}

void IORecorder::Initialize()
{
    POINT windows_mouse;
    GetCursorPos(&windows_mouse);
    this->m_psuedo_mouse.x = windows_mouse.x;
    this->m_psuedo_mouse.y = windows_mouse.y;
    this->m_psuedo_mouse.is_inited = true;
}
