#pragma once
#include "IRuntimeModule.h"

namespace Phantom {
    class InputManager : implements IRuntimeModule
    {
        public:
            virtual int Init();
            virtual void Shutdown();
            virtual void Tick();

            // keyboard handling
            void UpArrowKeyDown();
            void UpArrowKeyUp();
            void DownArrowKeyDown();
            void DownArrowKeyUp();
            void LeftArrowKeyDown();
            void LeftArrowKeyUp();
            void RightArrowKeyDown();
            void RightArrowKeyUp();

            void AsciiKeyDown(char keycode);
            void AsciiKeyUp(char keycode);

            // mouse handling
            void LeftMouseButtonDown();
            void LeftMouseButtonUp();
            void LeftMouseDrag(int deltaX, int deltaY);

			bool GetUpKeyPressed() { return m_bUpKeyPressed; }
			bool GetDownKeyPressed() { return m_bDownKeyPressed; }
			bool GetLeftKKeyPressed() { return m_bLeftKeyPressed; }
			bool GetRightKeyPressed() { return m_bRightKeyPressed; }
        protected:
            bool m_bUpKeyPressed    = false;
            bool m_bDownKeyPressed  = false;
            bool m_bLeftKeyPressed  = false;
            bool m_bRightKeyPressed = false;
    };

    extern InputManager* g_pInputManager;
}

