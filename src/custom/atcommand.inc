// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//ACMD_FUNC(newcommand)
//{
//	clif_displaymessage(fd, "It works!");
//	clif_specialeffect(&sd->bl, EF_HEARTCASTING, AREA);
//	return 0;
//}

ACMD_FUNC(afk){
	nullpo_retr(-1,sd);
	if(map_getmapflag(sd->m, MF_PVP) || map_getmapflag(sd->m, MF_GVG) || map_getmapflag(sd->m, MF_GVG_CASTLE) || map_getmapflag(sd->m, MF_BATTLEGROUND) ) {
		clif_displaymessage(fd, msg_txt(sd, 1541));
		return -1;
	}

	if( pc_isdead(sd) ) {
		clif_displaymessage(fd, msg_txt(sd, 1542));
		return -1;
	}

	/*
	pc_setsit(sd);
	skill_sit(sd,1);
	clif_sitting(&sd->bl);
	clif_changelook(&sd->bl,LOOK_HEAD_TOP,471);
	clif_specialeffect(&sd->bl, 234,AREA);   
	*/

	strcpy(sd->away_message, msg_txt(sd, 1543));
	clif_displaymessage(fd, msg_txt(sd, 1544));

	sd->state.afk = 1;
	sd->state.block_action |= PCBLOCK_IMMUNE;
	sd->state.autotrade = 1;

	if (battle_config.at_logout_event)
		npc_script_event(*sd, NPCE_LOGOUT); 

	channel_pcquit(sd,0xF); //leave all chan
	clif_authfail_fd(sd->fd, 15);
	chrif_save(sd, CSAVE_NORMAL|CSAVE_INVENTORY);

	return 0;
}
