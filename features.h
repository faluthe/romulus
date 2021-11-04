#pragma once

struct CUserCmd;
struct ModelRenderInfo_t;

void autopistol(CUserCmd* cmd);
void bunnyhop(CUserCmd* cmd);
void chams(void* _this, void* _edx, void* context, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, void* pCustomBoneToWorld);
void external_xhair();
void infopanel();
void render_esp();