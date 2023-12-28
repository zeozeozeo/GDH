#include "startposSwitcher.hpp"
#include "smartStartpos.hpp"
#include "hooks.hpp"

namespace startposSwitcher
{
    void(__thiscall *resetLevel)(void *) = nullptr;
    void(__thiscall *setStartPosObject)(void *, void *) = nullptr;
    void(__thiscall *startposObjectInit)(void *) = nullptr;

    std::vector<float *> startposObjects;
    int startposIndex = -1;
    float tmp[] = {0, 0};
    bool enabled = false;
    bool alternateKeys = false;

    void __fastcall startposObjectInitHook(void *self, void *_)
    {
        startposObjects.push_back((float *)self);
        startposIndex = startposObjects.size() - 1;
        startposObjectInit(self);
    }

    void restartLevelCallback()
    {
        startposObjects = {};
        startposIndex = 0;
        smartStartpos::resetObjects();
    }

    void init()
    {
        uintptr_t base = (uintptr_t)GetModuleHandleA(0);

        MH_CreateHook((LPVOID)(base + 0x3A0D10), startposObjectInitHook, (LPVOID *)&startposObjectInit);
        resetLevel = (decltype(resetLevel))(base + 0x2E42B0);
        setStartPosObject = (decltype(setStartPosObject))(base + 0x195FC0);
    }

    void handleKeyPress(int keyCode)
    {
        if (!enabled)
            return;
        if (!alternateKeys && (keyCode == VK_LEFT || keyCode == VK_RIGHT))
        {
            switchStartPos(keyCode == VK_RIGHT);
        }
        else if (alternateKeys && (keyCode == 'A' || keyCode == 'D'))
        {
            switchStartPos(keyCode == 'D');
        }
    }

    void switchStartPos(bool direction)
    {
        if (playLayer == nullptr || !enabled)
        {
            return;
        }

        if (direction)
        {
            startposIndex = startposIndex + 1;
            if (static_cast<unsigned int>(startposIndex) >= startposObjects.size())
            {
                startposIndex = -1;
            }
        }
        else
        {
            startposIndex = startposIndex - 1;
            if (startposIndex < -1)
            {
                startposIndex = startposObjects.size() - 1;
            }
        }

        ((uint32_t *)playLayer)[0xB7D] = 0; // PlayLayer::startPosCheckpoint i believe?

        if (startposIndex >= 0)
        {
            setStartPosObject(playLayer, startposObjects[startposIndex]);
        }
        else
        {
            setStartPosObject(playLayer, nullptr);
        }

        resetLevel(playLayer);
    }

    void setAlternateKeys(bool alternate)
    {
        alternateKeys = alternate;
    }

    void setEnabled(bool enable)
    {
        enabled = enable;
    }
}
