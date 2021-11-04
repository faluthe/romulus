#pragma once

#include <stdint.h>

#include "CUserCmd.h"
#include "Vector.h"

struct model_t
{
    void* fnHandle;
    char name[260];
};

struct ModelRenderInfo_t
{
    char pad0[32];
    const model_t* pModel;
    char pad1[16];
    int entityIndex;
};

struct mstudiobbox_t
{
    int         bone;
    int         group;
    Vector      bbmin;
    Vector      bbmax;
    int         szhitboxnameindex;
    int32_t     m_iPad01[3];
    float       m_flRadius;
    int32_t     m_iPad02[4];

    const char* GetName()
    {
        if (!szhitboxnameindex) return nullptr;
        return (const char*)((uint8_t*)this + szhitboxnameindex);
    }
};

struct mstudiohitboxset_t
{
    int    sznameindex;
    int    numhitboxes;
    int    hitboxindex;

    const char* GetName()
    {
        if (!sznameindex) return nullptr;
        return (const char*)((uint8_t*)this + sznameindex);
    }

    mstudiobbox_t* GetHitbox(int i)
    {
        if (i > numhitboxes) return nullptr;
        return (mstudiobbox_t*)((uint8_t*)this + hitboxindex) + i;
    }
};

class studiohdr_t
{
public:
    __int32 id;                     //0x0000 
    __int32 version;                //0x0004 
    long    checksum;               //0x0008 
    char    szName[64];             //0x000C 
    __int32 length;                 //0x004C 
    Vector  vecEyePos;              //0x0050 
    Vector  vecIllumPos;            //0x005C 
    Vector  vecHullMin;             //0x0068 
    Vector  vecHullMax;             //0x0074 
    Vector  vecBBMin;               //0x0080 
    Vector  vecBBMax;               //0x008C 
    __int32 flags;                  //0x0098 
    __int32 numbones;               //0x009C 
    __int32 boneindex;              //0x00A0 
    __int32 numbonecontrollers;     //0x00A4 
    __int32 bonecontrollerindex;    //0x00A8 
    __int32 numhitboxsets;          //0x00AC 
    __int32 hitboxsetindex;         //0x00B0 
    __int32 numlocalanim;           //0x00B4 
    __int32 localanimindex;         //0x00B8 
    __int32 numlocalseq;            //0x00BC 
    __int32 localseqindex;          //0x00C0 
    __int32 activitylistversion;    //0x00C4 
    __int32 eventsindexed;          //0x00C8 
    __int32 numtextures;            //0x00CC 
    __int32 textureindex;           //0x00D0

    mstudiohitboxset_t* GetHitboxSet(int i)
    {
        if (i > numhitboxsets) return nullptr;
        return (mstudiohitboxset_t*)((uint8_t*)this + hitboxsetindex) + i;
    }
};//Size=0x00D4

struct player_info_t {
    int64_t __pad0;
    union {
        int64_t xuid;
        struct xuid {
            int xuidlow;
            int xuidhigh;
        };
    };
    char name[128];
    int userid;
    char guid[33];
    unsigned int friendsid;
    char friendsname[128];
    bool fakeplayer;
    bool ishltv;
    unsigned int customfiles[4];
    unsigned char filesdownloaded;
};

struct CGlobalVarsBase
{
    float     realtime;                     // 0x0000
    int       framecount;                   // 0x0004
    float     absoluteframetime;            // 0x0008
    float     absoluteframestarttimestddev; // 0x000C
    float     curtime;                      // 0x0010
    float     frametime;                    // 0x0014
    int       maxClients;                   // 0x0018
    int       tickcount;                    // 0x001C
    float     interval_per_tick;            // 0x0020
    float     interpolation_amount;         // 0x0024
    int       simTicksThisFrame;            // 0x0028
    int       network_protocol;             // 0x002C
    void* pSaveData;                    // 0x0030
    bool      m_bClient;                    // 0x0031
    bool      m_bRemoteClient;              // 0x0032

    float serverTime(CUserCmd* cmd = nullptr);
};

class player_move_data {
public:
    bool    first_run_of_instructions : 1;
    bool    game_code_moved_player : 1;
    int     player_handle;
    int     impulse_command;
    Vector	view_angles;
    Vector	abs_view_angles;
    int     buttons;
    int     old_buttons;
    float   fw_move;
    float   sd_move;
    float   up_move;
    float   max_speed;
    float   client_max_speed;
    Vector	velocity;
    Vector	angles;
    Vector	old_angles;
    float   step_height;
    Vector	wish_velocity;
    Vector	jump_velocity;
    Vector	constraint_center;
    float   constraint_radius;
    float   constraint_width;
    float   constraint_speed_factor;
    float   u0[5];
    Vector	abs_origin;
};