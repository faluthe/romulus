#pragma once

#include "Entity.h"
#include "helper.h"
#include "Vector.h"

//class PlayerMoveHelper {
//public:
//	bool	first_run_of_iunctions : 1;
//	bool	game_code_moved_player : 1;
//	int	player_handle;
//	int	impulse_command;
//	Vector	view_angles;
//	Vector	abs_view_angles;
//	int	buttons;
//	int	old_buttons;
//	float	forward_move;
//	float	side_move;
//	float	up_move;
//	float	max_speed;
//	float	client_max_speed;
//	Vector	velocity;
//	Vector	angles;
//	Vector	old_angles;
//	float	out_step_height;
//	Vector	wish_velocity;
//	Vector	jump_velocity;
//	Vector	constraint_center;
//	float	constraint_radius;
//	float	constraint_width;
//	float	constraint_speed_factor;
//	float	u0[5];
//	Vector	abs_origin;
//	virtual	void u1() = 0;
//	virtual void set_host(Entity* host) = 0;
//};

class PlayerMoveHelper
{
public:
	void SetHost(Entity* host)
	{
		return call_virtual_method<void(__thiscall*)(void*, Entity*)>(this, 1)(this, host);
	}
};