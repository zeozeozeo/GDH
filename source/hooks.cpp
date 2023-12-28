#include "hooks.hpp"

float speed = 1.0f;
PlayLayer* playLayer = nullptr;

void(__thiscall *CCScheduler_update)(void *, float);
void __fastcall CCScheduler_update_H(void* self, int, float dt) {
    dt *= speed;
    CCScheduler_update(self, dt);
}

bool __fastcall hooks::PlayLayer_init_H(PlayLayer *self, int edx, void *GJGameLevel, bool a3, bool a4)
{
    const auto res = PlayLayer_init(self, GJGameLevel, a3, a4);
    if (res) {
        playLayer = self;
    }
    return res;
}

void __fastcall hooks::PlayLayer_onExit_H(PlayLayer* self) {
    playLayer = nullptr;
    PlayLayer_onExit(self);
}

void __fastcall hooks::PlayLayer_resetLevel_H(PlayLayer* self) {
    playLayer = self;
    PlayLayer_resetLevel(self);
}

void hooks::init() {
    auto cocos = GetModuleHandleA("libcocos2d.dll");
    MH_CreateHook(GetProcAddress(cocos, "?update@CCScheduler@cocos2d@@UAEXM@Z"), CCScheduler_update_H, (void **)&CCScheduler_update);

    Console::Init();
    MH_CreateHook((void*)(base + 0x2D69A0), PlayLayer_init_H, (void **)&PlayLayer_init);
    MH_CreateHook((void*)(base + 0x2E5910), PlayLayer_onExit_H, (void **)&PlayLayer_onExit);
    MH_CreateHook((void*)(base + 0x2e42b0), PlayLayer_resetLevel_H, (void **)&PlayLayer_resetLevel);
}
