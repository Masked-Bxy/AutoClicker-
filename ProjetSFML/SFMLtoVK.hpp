#include "common.h"

#include <string>
#include <sstream>

const static int SfmlKeyToVirtualKey(sf::Keyboard::Key key)
{
	switch (key)
	{
		// Lettres
	case sf::Keyboard::Key::A: return 'A';
	case sf::Keyboard::Key::B: return 'B';
	case sf::Keyboard::Key::C: return 'C';
	case sf::Keyboard::Key::D: return 'D';
	case sf::Keyboard::Key::E: return 'E';
	case sf::Keyboard::Key::F: return 'F';
	case sf::Keyboard::Key::G: return 'G';
	case sf::Keyboard::Key::H: return 'H';
	case sf::Keyboard::Key::I: return 'I';
	case sf::Keyboard::Key::J: return 'J';
	case sf::Keyboard::Key::K: return 'K';
	case sf::Keyboard::Key::L: return 'L';
	case sf::Keyboard::Key::M: return 'M';
	case sf::Keyboard::Key::N: return 'N';
	case sf::Keyboard::Key::O: return 'O';
	case sf::Keyboard::Key::P: return 'P';
	case sf::Keyboard::Key::Q: return 'Q';
	case sf::Keyboard::Key::R: return 'R';
	case sf::Keyboard::Key::S: return 'S';
	case sf::Keyboard::Key::T: return 'T';
	case sf::Keyboard::Key::U: return 'U';
	case sf::Keyboard::Key::V: return 'V';
	case sf::Keyboard::Key::W: return 'W';
	case sf::Keyboard::Key::X: return 'X';
	case sf::Keyboard::Key::Y: return 'Y';
	case sf::Keyboard::Key::Z: return 'Z';

		// Chiffres (ligne supérieure)
	case sf::Keyboard::Key::Num0: return '0';
	case sf::Keyboard::Key::Num1: return '1';
	case sf::Keyboard::Key::Num2: return '2';
	case sf::Keyboard::Key::Num3: return '3';
	case sf::Keyboard::Key::Num4: return '4';
	case sf::Keyboard::Key::Num5: return '5';
	case sf::Keyboard::Key::Num6: return '6';
	case sf::Keyboard::Key::Num7: return '7';
	case sf::Keyboard::Key::Num8: return '8';
	case sf::Keyboard::Key::Num9: return '9';

		// Pavé numérique
	case sf::Keyboard::Key::Numpad0: return VK_NUMPAD0;
	case sf::Keyboard::Key::Numpad1: return VK_NUMPAD1;
	case sf::Keyboard::Key::Numpad2: return VK_NUMPAD2;
	case sf::Keyboard::Key::Numpad3: return VK_NUMPAD3;
	case sf::Keyboard::Key::Numpad4: return VK_NUMPAD4;
	case sf::Keyboard::Key::Numpad5: return VK_NUMPAD5;
	case sf::Keyboard::Key::Numpad6: return VK_NUMPAD6;
	case sf::Keyboard::Key::Numpad7: return VK_NUMPAD7;
	case sf::Keyboard::Key::Numpad8: return VK_NUMPAD8;
	case sf::Keyboard::Key::Numpad9: return VK_NUMPAD9;

		// Touches communes
	case sf::Keyboard::Key::Escape: return VK_ESCAPE;
	case sf::Keyboard::Key::LControl: return VK_LCONTROL;
	case sf::Keyboard::Key::RControl: return VK_RCONTROL;
	case sf::Keyboard::Key::LShift: return VK_LSHIFT;
	case sf::Keyboard::Key::RShift: return VK_RSHIFT;
	case sf::Keyboard::Key::LAlt: return VK_LMENU;
	case sf::Keyboard::Key::RAlt: return VK_RMENU;
	case sf::Keyboard::Key::LSystem: return VK_LWIN;
	case sf::Keyboard::Key::RSystem: return VK_RWIN;
	case sf::Keyboard::Key::Menu: return VK_APPS;
	case sf::Keyboard::Key::Space: return VK_SPACE;
	case sf::Keyboard::Key::Enter: return VK_RETURN;
	case sf::Keyboard::Key::Backspace: return VK_BACK;
	case sf::Keyboard::Key::Tab: return VK_TAB;
	case sf::Keyboard::Key::Delete: return VK_DELETE;
	case sf::Keyboard::Key::Insert: return VK_INSERT;
	case sf::Keyboard::Key::Home: return VK_HOME;
	case sf::Keyboard::Key::End: return VK_FINAL;
	case sf::Keyboard::Key::PageUp: return VK_PRIOR;
	case sf::Keyboard::Key::PageDown: return VK_NEXT;

		// Flèches
	case sf::Keyboard::Key::Up: return VK_UP;
	case sf::Keyboard::Key::Down: return VK_DOWN;
	case sf::Keyboard::Key::Left: return VK_LEFT;
	case sf::Keyboard::Key::Right: return VK_RIGHT;

		// Fonctions
	case sf::Keyboard::Key::F1: return VK_F1;
	case sf::Keyboard::Key::F2: return VK_F2;
	case sf::Keyboard::Key::F3: return VK_F3;
	case sf::Keyboard::Key::F4: return VK_F4;
	case sf::Keyboard::Key::F5: return VK_F5;
	case sf::Keyboard::Key::F6: return VK_F6;
	case sf::Keyboard::Key::F7: return VK_F7;
	case sf::Keyboard::Key::F8: return VK_F8;
	case sf::Keyboard::Key::F9: return VK_F9;
	case sf::Keyboard::Key::F10: return VK_F10;
	case sf::Keyboard::Key::F11: return VK_F11;
	case sf::Keyboard::Key::F12: return VK_F12;
	case sf::Keyboard::Key::F13: return VK_F13;
	case sf::Keyboard::Key::F14: return VK_F14;
	case sf::Keyboard::Key::F15: return VK_F15;

		// Ponctuation / touches dépendantes du layout (approx.)
	case sf::Keyboard::Key::Semicolon: return VK_OEM_1;   // ;
	case sf::Keyboard::Key::Comma: return VK_OEM_COMMA;   // ,
	case sf::Keyboard::Key::Period: return VK_OEM_PERIOD; // .
	case sf::Keyboard::Key::Slash: return VK_OEM_2;       // /
	case sf::Keyboard::Key::LBracket: return VK_OEM_4;   // [
	case sf::Keyboard::Key::RBracket: return VK_OEM_6;   // ]
	case sf::Keyboard::Key::Backslash: return VK_OEM_5;   // \ //
	//case sf::Keyboard::Key::D: return VK_OEM_MINUS;    // -
	case sf::Keyboard::Key::Equal: return VK_OEM_PLUS;    // =

	default:
		return 0; // inconnu / non mappé
	}
}

const static int SfmlJoystickButtonToVirtualKey(unsigned int buttonIndex)
{
	switch (buttonIndex)
	{
	case 0: return VK_GAMEPAD_A;
	case 1: return VK_GAMEPAD_B;
	case 2: return VK_GAMEPAD_X;
	case 3: return VK_GAMEPAD_Y;
	case 4: return VK_GAMEPAD_LEFT_SHOULDER;
	case 5: return VK_GAMEPAD_RIGHT_SHOULDER;
	case 6: return VK_GAMEPAD_VIEW;
	case 7: return VK_GAMEPAD_MENU;
	case 8: return VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON;
	case 9: return VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON;
	case 10: return VK_GAMEPAD_DPAD_UP;
	case 11: return VK_GAMEPAD_DPAD_DOWN;
	case 12: return VK_GAMEPAD_DPAD_LEFT;
	case 13: return VK_GAMEPAD_DPAD_RIGHT;
	default:
		return 0; // non mappé
	}
}
const static int SfmlMouseButtonToVirtualKey(unsigned int buttonIndex)
{
	switch (buttonIndex)
	{
	case 0: return VK_LBUTTON;
	case 1: return VK_RBUTTON;
	case 2: return VK_MBUTTON;
	case 3: return VK_XBUTTON1;
	case 4: return VK_XBUTTON2;
	default:
		return 0; // non mappé
	}
}

const static std::string VirtualKeyToString(WORD vk)
{
	// Lettres / chiffres ASCII
	if (vk >= 'A' && vk <= 'Z') return std::string(1, static_cast<char>(vk));
	if (vk >= '0' && vk <= '9') return std::string(1, static_cast<char>(vk));

	switch (vk)
	{
		// touches communes
	case VK_SPACE: return "Space";
	case VK_RETURN: return "Enter";
	case VK_ESCAPE: return "Escape";
	case VK_BACK: return "Backspace";
	case VK_TAB: return "Tab";
	case VK_CAPITAL: return "CapsLock";

		// modificateurs
	case VK_SHIFT: return "Shift";
	case VK_LSHIFT: return "LShift";
	case VK_RSHIFT: return "RShift";
	case VK_CONTROL: return "Control";
	case VK_LCONTROL: return "LControl";
	case VK_RCONTROL: return "RControl";
	case VK_MENU: return "Alt";
	case VK_LMENU: return "LAlt";
	case VK_RMENU: return "RAlt";
	case VK_LWIN: return "LWin";
	case VK_RWIN: return "RWin";
	case VK_APPS: return "ContextMenu";

		// navigation
	case VK_PRIOR: return "PageUp";
	case VK_NEXT: return "PageDown";
	case VK_FINAL: return "Final";
	case VK_HOME: return "Home";
	case VK_LEFT: return "Left";
	case VK_RIGHT: return "Right";
	case VK_UP: return "Up";
	case VK_DOWN: return "Down";
	case VK_INSERT: return "Insert";
	case VK_DELETE: return "Delete";

		// fonction
	case VK_F1: return "F1";
	case VK_F2: return "F2";
	case VK_F3: return "F3";
	case VK_F4: return "F4";
	case VK_F5: return "F5";
	case VK_F6: return "F6";
	case VK_F7: return "F7";
	case VK_F8: return "F8";
	case VK_F9: return "F9";
	case VK_F10: return "F10";
	case VK_F11: return "F11";
	case VK_F12: return "F12";
	case VK_F13: return "F13";
	case VK_F14: return "F14";
	case VK_F15: return "F15";

		// pavé numérique
	case VK_NUMPAD0: return "Numpad0";
	case VK_NUMPAD1: return "Numpad1";
	case VK_NUMPAD2: return "Numpad2";
	case VK_NUMPAD3: return "Numpad3";
	case VK_NUMPAD4: return "Numpad4";
	case VK_NUMPAD5: return "Numpad5";
	case VK_NUMPAD6: return "Numpad6";
	case VK_NUMPAD7: return "Numpad7";
	case VK_NUMPAD8: return "Numpad8";
	case VK_NUMPAD9: return "Numpad9";
	case VK_MULTIPLY: return "NumpadMultiply";
	case VK_ADD: return "NumpadAdd";
	case VK_SEPARATOR: return "NumpadSeparator";
	case VK_SUBTRACT: return "NumpadSubtract";
	case VK_DECIMAL: return "NumpadDecimal";
	case VK_DIVIDE: return "NumpadDivide";

		// touches dépendantes du layout (OEM) - nom générique
	case VK_OEM_1: return "OEM_1";
	case VK_OEM_PLUS: return "OEM_Plus";
	case VK_OEM_COMMA: return "OEM_Comma";
	case VK_OEM_MINUS: return "OEM_Minus";
	case VK_OEM_PERIOD: return "OEM_Period";
	case VK_OEM_2: return "OEM_2";
	case VK_OEM_3: return "OEM_3";
	case VK_OEM_4: return "OEM_4";
	case VK_OEM_5: return "OEM_5";
	case VK_OEM_6: return "OEM_6";
	case VK_OEM_7: return "OEM_7";
	case VK_OEM_8: return "OEM_8";

		// joystick / gamepad (si utilisés)
	case VK_GAMEPAD_A: return "Gamepad_A";
	case VK_GAMEPAD_B: return "Gamepad_B";
	case VK_GAMEPAD_X: return "Gamepad_X";
	case VK_GAMEPAD_Y: return "Gamepad_Y";
	case VK_GAMEPAD_LEFT_SHOULDER: return "Gamepad_LB";
	case VK_GAMEPAD_RIGHT_SHOULDER: return "Gamepad_RB";
	case VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON: return "Gamepad_LThumbButton";
	case VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON: return "Gamepad_RThumbButton";
	case VK_GAMEPAD_VIEW: return "Gamepad_View";
	case VK_GAMEPAD_MENU: return "Gamepad_Menu";
	case VK_GAMEPAD_DPAD_UP: return "Gamepad_DPad_Up";
	case VK_GAMEPAD_DPAD_DOWN: return "Gamepad_DPad_Down";
	case VK_GAMEPAD_DPAD_LEFT: return "Gamepad_DPad_Left";
	case VK_GAMEPAD_DPAD_RIGHT: return "Gamepad_DPad_Right";
	case VK_LBUTTON: return "LeftMouse";
	case VK_RBUTTON: return "RightMouse";
	case VK_MBUTTON: return "MiddleMouse";
		

	default:
		// fallback : afficher en hexadécimal
	{
		std::ostringstream ss;
		ss << "Unknow";
		return ss.str();
	}
	}
}