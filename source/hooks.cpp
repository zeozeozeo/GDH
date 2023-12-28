#include "hooks.hpp"
#include "startposSwitcher.hpp"
#include "replayEngine.hpp"

float speed = 1.0f;
PlayLayer* playLayer = nullptr;

void(__thiscall *CCScheduler_update)(void *, float);
void __fastcall CCScheduler_update_H(void* self, int, float dt) {
    dt *= speed;
    CCScheduler_update(self, dt);
}

bool __fastcall hooks::PlayLayer_init_H(PlayLayer *self, int edx, void *GJGameLevel, bool a3, bool a4)
{
    Console::WriteLine("PlayLayer_init_H: " + std::to_string((uint64_t)self));
    playLayer = self;
    startposSwitcher::restartLevelCallback();
    return PlayLayer_init(self, GJGameLevel, a3, a4);
}

void __fastcall hooks::PlayLayer_onExit_H(PlayLayer* self) {
    playLayer = nullptr;
    PlayLayer_onExit(self);
}

void __fastcall hooks::PlayLayer_resetLevel_H(PlayLayer* self) {
    playLayer = self;
    PlayLayer_resetLevel(self);
}

void* __fastcall hooks::PlayLayer_createCheckpoint_H(PlayLayer* self) {
    Console::WriteLine("PlayLayer_createCheckpoint_H");
    replayEngine::addCheckpoint();
    return PlayLayer_createCheckpoint(self);
}

bool __fastcall hooks::PlayLayer_removeCheckpoint_H(PlayLayer* self, int edx, bool a2) {
    Console::WriteLine("PlayLayer_removeCheckpoint_H");
    return PlayLayer_removeCheckpoint(self, 0, a2);
}

void hooks::init() {
    auto cocos = GetModuleHandleA("libcocos2d.dll");
    MH_CreateHook(GetProcAddress(cocos, "?update@CCScheduler@cocos2d@@UAEXM@Z"), CCScheduler_update_H, (void **)&CCScheduler_update);

    Console::Init();
    MH_CreateHook((void*)(base + 0x2D69A0), PlayLayer_init_H, (void **)&PlayLayer_init);
    MH_CreateHook((void*)(base + 0x2E5910), PlayLayer_onExit_H, (void **)&PlayLayer_onExit);
    MH_CreateHook((void*)(base + 0x2e42b0), PlayLayer_resetLevel_H, (void **)&PlayLayer_resetLevel);
    MH_CreateHook((void*)(base + 0x2E1A20), PlayLayer_createCheckpoint_H, (void **)&PlayLayer_createCheckpoint);
    // MH_CreateHook((void*)(base + 0x2cb6d0), PlayLayer_removeCheckpoint_H, (void **)&PlayLayer_removeCheckpoint);
}
