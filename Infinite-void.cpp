#include <windows.h>
#ifndef UNICODE
#define UNICODE
#endif

LRESULT CALLBACK InfinityProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
const wchar_t* InfinityArray[51] = {
    L"Unexpected error occured",
    L"Are you sure? 😇",
    L"Just wanted 2nd assurance 🤔",
    L"Oh really? 🙄",
    L"Do you even know what you're doing? 😏",
    L"You really think I'll obey... you???? 😈",
    L"Good luck exiting, peasant 👑💀",
    L"This again? 🙃",
    L"Still trying? 😬",
    L"Persistent little one, aren’t you? 🐀",
    L"I live here now 🏠",
    L"You press No like it’s a hobby 🎮",
    L"Getting bored yet? 😴",
    L"Even Windows is judging you 💻😒",
    L"You know I can do this all day 🕒",
    L"This isn’t progress, it’s a loop 🔄",
    L"How’s that mouse hand? 🖱️🖐️",
    L"You’re basically arguing with a box 📦",
    L"Meanwhile your CPU cries 🖥️😭",
    L"I’ll stop when you stop. Spoiler: you won’t. 🔥",
    L"Careful, the void stares back 👁️",
    L"This button won’t save you 🚪",
    L"Closing time? Not for you 🕛",
    L"You’re still here? 😵",
    L"You could’ve finished a sandwich by now 🥪",
    L"Humans… so predictable 🤡",
    L"You thought clicking Yes would help? 😹",
    L"Error: User too stubborn ⚠️",
    L"Achievement unlocked: Infinite Annoyance 🏆",
    L"Press harder, maybe it’ll work 💪",
    L"You’re like a hamster in Windows 🐹💫",
    L"Control-Alt-Del looking good right now 🔐",
    L"Every click makes me stronger ⚡",
    L"This is why aliens don’t visit 🌌",
    L"Congratulations, you’ve angered software 🤬",
    L"At this point, just pull the plug 🔌",
    L"You have 0 power here 🪦",
    L"Still smarter than Clippy 🤷",
    L"Persistence ≠ intelligence 🧠❌",
    L"Try rage-quitting harder 😡",
    L"You’re basically beta testing my evil side 😼",
    L"This message is sponsored by chaos 🌀",
    L"Guess who’s winning? (Hint: not you) 🏁",
    L"Maybe you enjoy suffering? 🤨",
    L"Some people read books. You do this. 📚❌",
    L"You could’ve learned C++ by now 👨‍💻",
    L"The end is near… just kidding 💀",
    L"Quitter’s button? Doesn’t exist 🚫",
    L"Keep going, clown 🤡🎪",
    L"You’ll die before I close ☠️",
    L"Behold, your eternity 🔮"
};

struct State {
    int index;
    WNDCLASS* pPClass = NULL;
    WNDCLASS* pCClass = NULL;
    HWND* pHwndParent = NULL;
};


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{   
    WNDCLASS wc = { };
    wc.lpszClassName = L"Main";
    wc.hInstance = hInstance;
    wc.lpfnWndProc = InfinityProc;

    RegisterClass(&wc);

    State state = {};
    state.index = 0;
    state.pPClass = &wc;

    HWND Hmain = CreateWindowW(
        L"Main",
        L"Parent",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        400,
        200,
        NULL,
        NULL,
        hInstance,
        &state
    );

    state.pHwndParent = &Hmain;
    SetWindowLongPtr(Hmain, GWLP_USERDATA, (LONG_PTR)&state);

    ShowWindow(Hmain, nCmdShow);

    MSG msg = {};
    
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

inline State* GetState(HWND hwnd) {
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    State* state = reinterpret_cast<State*>(ptr);
    return state;
}

void SpawnChild(State* state) {
    WNDCLASS ParentClass = *(state->pPClass);
    if (state->pCClass == NULL) {
        WNDCLASS wc = {};
        wc.lpfnWndProc = InfinityProc;
        wc.lpszClassName = L"Child";
        wc.hInstance = ParentClass.hInstance;

        RegisterClass(&wc);
        state->pCClass = &wc;
    }

    WNDCLASS ChildClass = *(state->pCClass);

    HWND handle = CreateWindow(
            L"Child",
            L"Error occured",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            400,
            200,
            *state->pHwndParent, // always anchor to original main window
            NULL,
            state->pPClass->hInstance,
            state
        );

    SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)state);
    ShowWindow(handle, SW_SHOWNORMAL);
    state->index++;
}




LRESULT CALLBACK InfinityProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    State* state = GetState(hwnd);

    switch (uMsg) {

    case WM_CLOSE:
    {
        SpawnChild(state);
        return 0;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        DrawTextW(hdc, InfinityArray[state->index % 50], -1, &ps.rcPaint, DT_CENTER | DT_VCENTER);

        EndPaint(hwnd, &ps);
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}