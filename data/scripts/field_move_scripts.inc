@ Interact with cuttable tree
EventScript_CutTree::
	lockall
	checkitem ITEM_AXE, 1
	goto_if_eq VAR_RESULT, 0, EventScript_CheckTreeCantCut
	msgbox Text_WantToCut, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_CancelCut
	msgbox Text_PlayerUsedAxe, MSGBOX_DEFAULT
EventScript_CutTreeDown:: @ fallthrough
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate
	applymovement VAR_LAST_TALKED, Movement_CutTreeDown
	waitmovement 0
	removeobject VAR_LAST_TALKED
	releaseall
	end

@ Use cut from party menu
EventScript_UseCut::
	lockall
	goto EventScript_CutTreeDown
	end

Movement_CutTreeDown:
	cut_tree
	step_end

EventScript_CheckTreeCantCut::
	msgbox Text_CantCut, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelCut::
	closemessage
	releaseall
	end

Text_WantToCut:
	.string "This tree looks like it can be\n"
	.string "cut down!\p"
	.string "Would you like to use the Axe?$"

Text_MonUsedFieldMove:
	.string "{STR_VAR_1} used {STR_VAR_2}!$"

Text_PlayerUsedAxe:
	.string "{PLAYER} used the Axe!$"

Text_CantCut:
	.string "This tree looks like it can be\n"
	.string "cut down!$"

@ Use rock smash from party menu
EventScript_UseRockSmash::
	lockall
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto EventScript_SmashRock
	end

@ Interact with smashable rock
EventScript_RockSmash::
	lockall
	checkitem ITEM_PICKAXE, 1
	goto_if_eq VAR_RESULT, 0, EventScript_CantSmashRock
	msgbox Text_WantToSmash, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_CancelSmash
	msgbox Text_PlayerUsedPickaxe, MSGBOX_DEFAULT
EventScript_SmashRock:: @ fallthrough
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	applymovement VAR_LAST_TALKED, Movement_SmashRock
	waitmovement 0
	removeobject VAR_LAST_TALKED
	specialvar VAR_RESULT, TryUpdateRusturfTunnelState
	goto_if_eq VAR_RESULT, TRUE, EventScript_EndSmash
	special RockSmashWildEncounter
	goto_if_eq VAR_RESULT, FALSE, EventScript_EndSmash
	waitstate
	releaseall
	end

EventScript_FollowerFieldMove:
	getdirectiontoface VAR_0x8005, OBJ_EVENT_ID_FOLLOWER, OBJ_EVENT_ID_PLAYER
	specialvar VAR_0x8006, GetPlayerFacingDirection
	goto_if_eq VAR_0x8005, DIR_NONE, EventScript_FollowerFieldMoveEnd
	@ Swap follower and player
	call EventScript_FollowerSwap
	@ Face follower in direction and jump
	switch VAR_0x8006
	case DIR_NORTH, EventScript_FollowerJumpNorth
	case DIR_EAST, EventScript_FollowerJumpEast
	case DIR_SOUTH, EventScript_FollowerJumpSouth
	case DIR_WEST, EventScript_FollowerJumpWest
EventScript_FollowerFieldMoveEnd:
	return

EventScript_FollowerSwap:
	switch VAR_0x8005
	case DIR_NORTH, EventScript_FollowerMoveNorth
	case DIR_EAST, EventScript_FollowerMoveEast
	case DIR_SOUTH, EventScript_FollowerMoveSouth
	case DIR_WEST, EventScript_FollowerMoveWest
	return

EventScript_FollowerMoveNorth:
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	return

EventScript_FollowerMoveEast:
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkLeft
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	return

EventScript_FollowerMoveSouth:
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	return

EventScript_FollowerMoveWest:
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	return

EventScript_FollowerJumpNorth:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpUp
	waitmovement 0
	return

EventScript_FollowerJumpEast:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpRight
	waitmovement 0
	return

EventScript_FollowerJumpSouth:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpDown
	waitmovement 0
	return

EventScript_FollowerJumpWest:
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpLeft
	waitmovement 0
	return

EventScript_EndSmash::
	releaseall
	end

Movement_WalkUp:
	walk_up
	step_end

Movement_JumpUp:
	jump_in_place_up
	step_end

Movement_WalkRight:
	walk_right
	step_end

Movement_JumpRight:
	jump_in_place_right
	step_end

Movement_WalkDown:
	walk_down
	step_end

Movement_JumpDown:
	jump_in_place_down
	step_end

Movement_WalkLeft:
	walk_left
	step_end

Movement_JumpLeft:
	jump_in_place_left
	step_end

Movement_SmashRock:
	rock_smash_break
	step_end

EventScript_CantSmashRock::
	msgbox Text_CantSmash, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelSmash::
	closemessage
	releaseall
	end

Text_WantToSmash:
	.string "This rock appears to be breakable.\n"
	.string "Would you like to use the Pickaxe?$"

Text_CantSmash:
	.string "It's a rugged rock, but a tool\n"
	.string "might be able to smash it.$"

Text_PlayerUsedPickaxe:
	.string "{PLAYER} used the Pickaxe!$"	

EventScript_StrengthBoulder::
	lockall
	goto_if_set FLAG_SYS_USE_STRENGTH, EventScript_CheckActivatedBoulder
	checkitem ITEM_POWER_GLOVE, 1
	goto_if_eq VAR_RESULT, 0, EventScript_CantStrength
	msgbox Text_WantToStrength, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_CancelStrength
	msgbox Text_PlayerUsedGlove, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrength
	end

EventScript_UseStrength::
	lockall
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_ActivateStrength
	end

EventScript_ActivateStrength::
	setflag FLAG_SYS_USE_STRENGTH
	releaseall
	end

EventScript_CantStrength::
	msgbox Text_CantStrength, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CheckActivatedBoulder::
	msgbox Text_StrengthActivated, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelStrength::
	closemessage
	releaseall
	end

Text_WantToStrength:
	.string "It's a big boulder, but the Power\n"
	.string "Glove may be able to help you push it.\p"
	.string "Would you like to wear the Power Glove?$"

Text_CantStrength:
	.string "It's a big boulder, but its too heavy\n"
	.string "to push it aside.$"

Text_StrengthActivated:
	.string "Its now possible to move boulders\n"
	.string "around.$"
	
Text_PlayerUsedGlove:
	.string "{PLAYER} used the Power Glove!$"

EventScript_UseWaterfall::
	lockall
	checkitem ITEM_SURFBOARD, 1
	goto_if_eq VAR_RESULT, 0, EventScript_CantWaterfall
	setfieldeffectargument 0, VAR_RESULT
	msgbox Text_WantToWaterfall, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_EndWaterfall
	hidefollowernpc
	msgbox Text_PlayerUsedWaterfall, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_WATERFALL
	callnative FollowerNPC_WarpSetEnd
	goto EventScript_EndWaterfall

EventScript_CannotUseWaterfall::
	lockall

EventScript_CantWaterfall::
	lockall
	msgbox Text_CantWaterfall, MSGBOX_DEFAULT

EventScript_EndWaterfall::
	releaseall
	end

Text_CantWaterfall:
	.string "A wall of water is crashing down with\n"
	.string "a mighty roar.$"

Text_WantToWaterfall:
	.string "It's a large waterfall.\n"
	.string "Would you like to scale it?$"

Text_PlayerUsedWaterfall:
	.string "{PLAYER} started scaling the waterfall!$"
	
EventScript_DiveSpot::
	lockall
	checkitem ITEM_SCUBA_GEAR, 1
	goto_if_eq VAR_RESULT, 0, EventScript_CantDive
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_WantToDive, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_EndDive
	msgbox Text_PlayerUsedDive, MSGBOX_DEFAULT
	hidefollowernpc
	setfieldeffectargument 0, VAR_0x8004
	setfieldeffectargument 1, 1
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive
	end

EventScript_UseDive::
	lockall
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive
	end

EventScript_CantDive::
	msgbox Text_CantDive, MSGBOX_DEFAULT
	releaseall
	end

EventScript_EndDive::
	releaseall
	end

EventScript_UseDiveUnderwater::
	lockall
	checkitem ITEM_SCUBA_GEAR, 1
	goto_if_eq VAR_RESULT, 0, EventScript_CantSurface
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 1, 1
	msgbox Text_WantToSurface, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_NoSurface
	msgbox Text_Surfaced, MSGBOX_DEFAULT
	hidefollowernpc
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndSurface
	end

EventScript_CantSurface::
	lockall
	msgbox Text_CantSurface, MSGBOX_DEFAULT
	goto EventScript_EndSurface
	end

EventScript_EndSurface::
	callnative SetFollowerNPCSurfSpriteAfterDive
EventScript_NoSurface::
	releaseall
	end

EventScript_DigCommon:
	isfollowerfieldmoveuser VAR_0x8004
	setfieldeffectargument 3, VAR_0x8004 @ skip pose if true
	dofieldeffect FLDEFF_USE_DIG
	waitstate
EventScript_DigSealedChamber:: @ fallthrough
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	call_if_eq VAR_0x8004, TRUE, EventScript_FollowerFieldMove
	callnative DoBrailleDigEffect
	releaseall
	end

@ Use Dig from party menu
EventScript_UseDig::
	lockall
	goto EventScript_DigCommon


EventScript_CutGrassCommon:
	isfollowerfieldmoveuser VAR_0x8004
	setfieldeffectargument 3, VAR_0x8004 @ skip pose if true
	dofieldeffect FLDEFF_USE_CUT_ON_GRASS
	waitstate

@ Use Cut grass from party menu
EventScript_UseCutGrass::
	lockall
	goto EventScript_CutGrassCommon

Text_CantDive:
	.string "The sea is deep here. Some gear\n"
	.string "may be able to go underwater.$"

Text_WantToDive:
	.string "The sea is deep here.\n"
	.string "Would you like to put on the Scuba Gear?$"

Text_PlayerUsedDive:
	.string "{PLAYER} put on the Scuba Gear!$"
	
Text_Surfaced:
	.string "{PLAYER} returned to the surface!$"

Text_CantSurface:
	.string "Light is filtering down from above.$"

Text_WantToSurface:
	.string "Light is filtering down from above.\n"
	.string "Would you like to swim up?$"

EventScript_FailSweetScent::
	msgbox Text_FailSweetScent, MSGBOX_SIGN
	end

Text_FailSweetScent:
	.string "Looks like there's nothing here…$"

EventScript_UseDefog::
	lockall
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_DEFOG
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	isfollowerfieldmoveuser VAR_0x8004
	setfieldeffectargument 3, VAR_0x8004 @ skip pose if so
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	call_if_eq VAR_0x8004, TRUE, EventScript_FollowerFieldMove
	waitmovement 0
	setfieldeffectargument 0, VAR_RESULT
	dofieldeffect FLDEFF_DEFOG
	waitstate
	releaseall
	end

EventScript_UseRockClimb::
	lockall
	checkfieldmove FIELD_MOVE_ROCK_CLIMB
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantRockClimb
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	msgbox Text_WantToRockClimb, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_EndRockClimb
	msgbox Text_MonUsedRockClimb, MSGBOX_DEFAULT
	closemessage
	dofieldeffect FLDEFF_USE_ROCK_CLIMB
	waitstate
	goto EventScript_EndRockClimb
	end

EventScript_CantRockClimb::
	msgbox Text_CantRockClimb, MSGBOX_DEFAULT

EventScript_EndRockClimb::
	releaseall
	end

Text_WantToRockClimb:
	.string "The cliff is steep.\n"
	.string "Would you like to use Rock Climb?$"

Text_MonUsedRockClimb:
	.string "{STR_VAR_1} used Rock Climb!$"

Text_CantRockClimb:
	.string "The cliff is steep.\n"
	.string "A Pokémon may be able to climb it.$"

@ Use headbutt from party menu
EventScript_UseHeadbutt::
	lockall
	goto EventScript_HeadbuttCommon

@ Interact with headbuttable tree
EventScript_Headbutt::
	lockall
	checkfieldmove FIELD_MOVE_HEADBUTT, TRUE
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantHeadbutt
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_HEADBUTT
	msgbox Text_WantToHeadbutt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_CancelHeadbutt
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
EventScript_HeadbuttCommon:
	@ check if follower should use the field move
	isfollowerfieldmoveuser VAR_0x8004
	setfieldeffectargument 3, VAR_0x8004 @ skip pose if so
	dofieldeffect FLDEFF_USE_HEADBUTT
	waitstate
EventScript_HeadbuttTree:: @ fallthrough
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	call_if_eq VAR_0x8004, TRUE, EventScript_FollowerFieldMove
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	special HeadbuttWildEncounter
	compare VAR_RESULT, FALSE
	goto_if_eq EventScript_EndHeadbutt
	waitstate
	releaseall
	end

EventScript_CantHeadbutt::
	msgbox Text_CantHeadbutt, MSGBOX_DEFAULT
	releaseall
	end

EventScript_CancelHeadbutt::
	closemessage
	releaseall
	end

	EventScript_EndHeadbutt::
	releaseall
	end

	Text_WantToHeadbutt:
	.string "It's a moderately sized tree.\p"
	.string "Would you like {STR_VAR_1}\n"
	.string "to use {STR_VAR_2}?$"

Text_CantHeadbutt:
	.string "There's a large, formidable tree\n"
	.string "that looks like it can be headbutted!$"
