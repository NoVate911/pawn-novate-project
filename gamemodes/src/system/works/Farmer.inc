new const Float:Work_Farmer_LV_PositionsInvite[4] = {288.9738, 1141.4445, 8.5859, 86.5413}; // Позиция устройства на работу | The position of the device for work
new const Float:Work_Farmer_LV_PositionsPickup[WORK_FARMER_LV_PICKUP_POINT][3] = { // Позиции взятия сена | Hay taking positions
    {261.0748, 1150.7540, 11.0834},
    {250.6571, 1150.7491, 11.6542},
    {239.0386, 1150.9663, 12.2485},
    {228.5628, 1151.3781, 13.0933}
};
new const Float:Work_Farmer_LV_PositionsPut[WORK_FARMER_LV_PUT_POINT][3] = { // Позиции сдачи сена | Hay delivery positions
    {315.3572, 1148.3951, 8.5859}
};

/*      [ ========== ========== ========== ========== ========== ]      */

stock Work_Farmer_LV_Init()
{
    WFLVInfo[WORK_FARMER_LV_ID][ActorID] = CreateDynamicActor(WORK_FARMER_LV_NPC_INVITE_SKIN_ID, Work_Farmer_LV_PositionsInvite[0], Work_Farmer_LV_PositionsInvite[1], Work_Farmer_LV_PositionsInvite[2], Work_Farmer_LV_PositionsInvite[3], _, _, 0, 0);
    WFLVInfo[WORK_FARMER_LV_ID][Actor3DText] = CreateDynamic3DTextLabel("> Эдуард <\n"C_WHITE"Нажмите "C_YELLOW"\"ALT\" "C_WHITE"для диалога", C_F_YELLOW, Work_Farmer_LV_PositionsInvite[0], Work_Farmer_LV_PositionsInvite[1], Work_Farmer_LV_PositionsInvite[2]+1.5, 10.0, _, _, _, 0, 0);
    return 1;
}

stock Work_Farmer_LV_KeyStateChange(playerid, newkeys)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        switch(newkeys)
        {
            case KEY_WALK: // L. ALT
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, Work_Farmer_LV_PositionsInvite[0], Work_Farmer_LV_PositionsInvite[1], Work_Farmer_LV_PositionsInvite[2]))
                {
                    if(PlayerWFLVInfo[playerid][IsPickup])
                        return SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Для того, чтобы окончить работу нужно сдать текущий ящик.");

                    ApplyDynamicActorAnimation(WFLVInfo[WORK_FARMER_LV_ID][ActorID], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
                    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = true;
                    if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
                        Dialog_Show(playerid, Dialog:Dlg_Work_FarmerLV_Invite);
                    else
                    {
                        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_FARMER_LV_ID)
                            Dialog_Show(playerid, Dialog:Dlg_Work_FarmerLV_Uninvite);
                    }
                }
            }
        }
    }
    return 1;
}

stock Work_Farmer_LV_EnterDynamicCP(playerid, checkpointid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_FARMER_LV_ID)
            {
                if(checkpointid == PlayerWFLVInfo[playerid][Checkpoint])
                {
                    DestroyDynamicCP(PlayerWFLVInfo[playerid][Checkpoint]);
                    if(PlayerWFLVInfo[playerid][IsPickup])
                    {
                        PlayerWFLVInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Farmer_LV_PositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][0], Work_Farmer_LV_PositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][1], Work_Farmer_LV_PositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][2], 2.0, 0, 0, playerid);
                        PlayerWFLVInfo[playerid][IsPickup] = false;
                        PlayerWFLVInfo[playerid][MovedHayCount]++;
                        SetPlayerSpecialAction(playerid, 0);
                        RemovePlayerAttachedObject(playerid, 2);
                        ApplyAnimation(playerid, "CARRY", "PUTDWN05", 4.0, 0, 0, 0, 0, 0, 1);
                    }
                    else
                    {
                        PlayerWFLVInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Farmer_LV_PositionsPut[random(WORK_FARMER_LV_PUT_POINT)][0], Work_Farmer_LV_PositionsPut[random(WORK_FARMER_LV_PUT_POINT)][1], Work_Farmer_LV_PositionsPut[random(WORK_FARMER_LV_PUT_POINT)][2], 2.0, 0, 0, playerid);
                        PlayerWFLVInfo[playerid][IsPickup] = true;
                        SetPlayerSpecialAction(playerid, 25);
                        SetPlayerAttachedObject(playerid, 2, 2969, 5, 0.01, 0.1, 0.2, -90, 0, 90);
                        ApplyAnimation(playerid, "CARRY", "LIFTUP05", 4.0, 0, 0, 0, 0, 0, 1);
                    }
                }
            }
        }
    }
    return 1;
}

/*      [ ========== ========== ========== ========== ========== ]      */

dCreate:Dlg_Work_FarmerLV_Invite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nЭдуард: "C_LIGHTGRAY"Ну дарова! Чего ты так стесняешься подойти то? Я не кусаюсь!\n\
    "C_LIGHTGRAY"Слухай, я по делу, на самом деле. Работёнка видно тебе нужна, а у меня она имеется.\n\
    "C_LIGHTGRAY"Твоя задача перетаскать ящики от точки выдачи до точки погрузки.\n\
    "C_LIGHTGRAY"Работа хоть и тяжёлая, но и я заплачу не гроши, а нормальную сумму.\n\
    "C_LIGHTGRAY"За каждый перенесённый ящик ты получишь %d$. Ну что, по рукам?\n\n\
    "C_WHITE"Сложность: "C_LIGHTGRAY"очень просто"C_WHITE".\n\
    "C_WHITE"Зарплата: "C_LIGHTGRAY"%d$ за сено"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, WORK_FARMER_LV_PRICE_PER_BOX, WORK_FARMER_LV_PRICE_PER_BOX);
    return Dialog_Open(playerid, Dialog:Dlg_Work_FarmerLV_Invite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Эдуард "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:Dlg_Work_FarmerLV_Invite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? (WORK_FARMER_LV_MALE_SKIN_ID) : (WORK_FARMER_LV_FEMALE_SKIN_ID)));
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = true;
        CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] = WORK_FARMER_LV_ID;
        PlayerWFLVInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Farmer_LV_PositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][0], Work_Farmer_LV_PositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][1], Work_Farmer_LV_PositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][2], 3.0, 0, 0, playerid);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы трудоустроились на работу фермера.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Таскайте сено из точки А в точку Б. За каждый сноп сена вы получаете денежное вознаграждение.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"По окончанию работы обратитесь к Эдуарду.");
    }
    return 1;
}

dCreate:Dlg_Work_FarmerLV_Uninvite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nЭдуард: "C_LIGHTGRAY"Хочешь сказать, что уже устал?\n\
    "C_LIGHTGRAY"С такими темпами работы ты никуда не продвинешься.\n\
    "C_LIGHTGRAY"Ну да ладно, не моё дело. Ты хочешь закончить работу?\n\n\
    "C_WHITE"Перенесено сена: "C_LIGHTGRAY"%d штук"C_WHITE".\n\
    "C_WHITE"Заработано: "C_LIGHTGRAY"%d$"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, PlayerWFLVInfo[playerid][MovedHayCount], PlayerWFLVInfo[playerid][MovedHayCount] * WORK_FARMER_LV_PRICE_PER_BOX);
    return Dialog_Open(playerid, Dialog:Dlg_Work_FarmerLV_Uninvite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Эдуард "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:Dlg_Work_FarmerLV_Uninvite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Skin]);
        Money_Give(playerid, PlayerWFLVInfo[playerid][MovedHayCount] * WORK_FARMER_LV_PRICE_PER_BOX);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы закончили работу фермера.");
        SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"За перенос %d сена получено %d$.", PlayerWFLVInfo[playerid][MovedHayCount], PlayerWFLVInfo[playerid][MovedHayCount] * WORK_FARMER_LV_PRICE_PER_BOX);
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = false;
        PlayerWFLVInfo[playerid][MovedHayCount] = 0;
        DestroyDynamicCP(PlayerWFLVInfo[playerid][Checkpoint]);
    }
    return 1;
}