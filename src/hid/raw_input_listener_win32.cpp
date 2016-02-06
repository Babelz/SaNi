#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/hid/raw_input_listener.hpp"

namespace sani {
	namespace hid {

		sani::hid::Key RawInputListener::rawKeyToKeyCode(const WPARAM& param) {
			switch (param) {
				// Digits
			case 0x30: return Key::D0;
			case 0x31: return Key::D1;
			case 0x32: return Key::D2;
			case 0x33: return Key::D3;
			case 0x34: return Key::D4;
			case 0x35: return Key::D5;
			case 0x36: return Key::D6;
			case 0x37: return Key::D7;
			case 0x38: return Key::D8;
			case 0x39: return Key::D9;

				// Letters
			case 0x41: return Key::A;
			case 0x42: return Key::B;
			case 0x43: return Key::C;
			case 0x44: return Key::D;
			case 0x45: return Key::E;
			case 0x46: return Key::F;
			case 0x47: return Key::G;
			case 0x48: return Key::H;
			case 0x49: return Key::I;
			
			case 0x4A: return Key::J;
			case 0x4B: return Key::K;
			case 0x4C: return Key::L;
			case 0x4D: return Key::M;
			case 0x4E: return Key::N;
			case 0x4F: return Key::O;
			
			case 0x50: return Key::P;
			case 0x51: return Key::Q;
			case 0x52: return Key::R;
			case 0x53: return Key::S;
			case 0x54: return Key::T;
			case 0x55: return Key::U;
			case 0x56: return Key::V;
			case 0x57: return Key::W;
			case 0x58: return Key::X;
			case 0x59: return Key::Y;

			case 0x5A: return Key::Z;
				// TODO add more keys
			default: return Key::Void;
			}
		}

		void RawInputListener::init() {
			// register mouse
			RAWINPUTDEVICE device;
			device.usUsagePage = 0x01;
			device.usUsage = 0x02;
			device.hwndTarget = NULL;
			device.dwFlags = 0;

			RegisterRawInputDevices(&device, 1, sizeof(device));
			DWORD error = GetLastError();

		}

		void RawInputListener::update() {
			MSG msg;
			// retrieve messages for any window
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				switch (msg.message) {
				case WM_KEYDOWN:
					// key down
					break;
				case WM_KEYUP:
					// key up
					break;
				}
			}
		}

	}
}


#endif