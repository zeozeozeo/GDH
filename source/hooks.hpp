#include "include.hpp"

#pragma pack(push, 4)
class PlayLayer {
public:
    int m_level_id;
    int m_nTimeWarp;            // int
    char gap2D4[154];           // char[154]
    char byte36E;               // char
    char gap36F[617];           // char[617]
    PlayLayer* m_pPlayer;       // int (offset)
    char gap5DC[660];           // char[660]
    int offsetDword870;         // int (offset)
    int dword874;               // int
    char gap878[8488];          // char[8488]
    int m_nTaps;                // int
    int m_nAttempts;            // int
    char gap29A8[32];           // char[32]
    int m_nPracticles;          // int
    char gap29CC[96];           // char[96]
    int m_nGradients;           // int
    char gap2A30[192];          // char[192]
    int m_nActive;              // int
    char gap2AF4[564];          // char[564]
    int dword2D28;              // int
    int dword2D2C;              // int
    int dword2D30;              // int
    int dword2D34;              // int
    int m_nMove;                // int
    int m_nScale;               // int
    int m_nRotate;              // int
    int m_nColOp;               // int
    int m_nMove_;               // int
    int m_nScale_;              // int
    int m_nRotate_;             // int
    int m_nFollow;              // int
    char gap2D58[376];          // char[376]
    double m_nTime;             // double
    char gap2ED8[40];           // char[40]
    int offsetPdword2F00;       // int (offset)
};
#pragma pack(pop)

extern float speed;
extern PlayLayer* playLayer;

namespace hooks {
    inline auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

    inline bool(__thiscall* PlayLayer_init)(PlayLayer*, void*, bool, bool);
    inline bool __fastcall PlayLayer_init_H(PlayLayer* self, int edx, void* GJGameLevel, bool a3, bool a4);

    inline void(__thiscall* PlayLayer_onExit)(PlayLayer*);
    inline void __fastcall PlayLayer_onExit_H(PlayLayer* self);

    void init();
}
