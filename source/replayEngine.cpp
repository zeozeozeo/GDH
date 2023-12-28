#include "replayEngine.hpp"
#include "hooks.hpp"

namespace replayEngine {
    bool enabled = false;

    uint32_t getFrame() {
        if (playLayer == nullptr)
            return 0;
        const auto time = *(double*)(((char*)playLayer) + 0x328); // might also be 0x2ed0
        const float fps = 60.0f; // TODO
        return (uint32_t)(time * fps);
    }

    void addCheckpoint() {
        Console::WriteLine("adding checkpoint, frame " + std::to_string(getFrame()));
    }

    void setEnabled(bool enable) {
        enabled = enable;
    }
}
