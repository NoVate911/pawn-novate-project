new const Float:Work_Loader_LV_PositionsInvite[4] = {2442.2417, 1954.8455, 10.7978, 269.7844}; // Позиция устройства на работу | The position of the device for work
new const Float:Work_Loader_LV_PositionsPickup[WORK_LOADER_LV_PICKUP_POINT][3] = { // Позиции взятия груза | Cargo pickup positions
    {2414.1614, 1949.2720, 6.0156},
    {2421.8457, 1953.3391, 6.0156}
};
new const Float:Work_Loader_LV_PositionsPut[WORK_LOADER_LV_PUT_POINT][3] = { // Позиции сдачи груза | Delivery positions
    {2478.2112, 1951.4685, 10.3570},
    {2473.5769, 1939.1465, 9.9569}
};

/*      [ ========== ========== ========== ========== ========== ]      */

stock Work_Loader_LV_Init()
{
    WLLVInfo[WORK_LOADER_LV_ID][ActorID] = CreateDynamicActor(WORK_LOADER_LV_NPC_INVITE_SKIN_ID, Work_Loader_LV_PositionsInvite[0], Work_Loader_LV_PositionsInvite[1], Work_Loader_LV_PositionsInvite[2], Work_Loader_LV_PositionsInvite[3], _, _, 0, 0);
    WLLVInfo[WORK_LOADER_LV_ID][Actor3DText] = CreateDynamic3DTextLabel("> Прораб <\n"C_WHITE"Нажмите "C_YELLOW"\"ALT\" "C_WHITE"для диалога", C_F_YELLOW, Work_Loader_LV_PositionsInvite[0], Work_Loader_LV_PositionsInvite[1], Work_Loader_LV_PositionsInvite[2]+1.5, 10.0, _, _, _, 0, 0);
    return 1;
}

stock Work_Loader_LV_KeyStateChange(playerid, newkeys)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        switch(newkeys)
        {
            case KEY_WALK: // L. ALT
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, Work_Loader_LV_PositionsInvite[0], Work_Loader_LV_PositionsInvite[1], Work_Loader_LV_PositionsInvite[2]))
                {
                    if(PlayerWLLVInfo[playerid][IsPickup])
                        return SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Для того, чтобы окончить работу нужно сдать текущий ящик.");

                    ApplyDynamicActorAnimation(WLLVInfo[WORK_LOADER_LV_ID][ActorID], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
                    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = true;
                    if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
                        Dialog_Show(playerid, Dialog:Dlg_Work_LoaderLV_Invite);
                    else
                    {
                        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_LOADER_LV_ID)
                            Dialog_Show(playerid, Dialog:Dlg_Work_LoaderLV_Uninvite);
                    }
                }
            }
        }
    }
    return 1;
}

stock Work_Loader_LV_EnterDynamicCP(playerid, checkpointid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_LOADER_LV_ID)
            {
                if(checkpointid == PlayerWLLVInfo[playerid][Checkpoint])
                {
                    DestroyDynamicCP(PlayerWLLVInfo[playerid][Checkpoint]);
                    if(PlayerWLLVInfo[playerid][IsPickup])
                    {
                        PlayerWLLVInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Loader_LV_PositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][0], Work_Loader_LV_PositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][1], Work_Loader_LV_PositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][2], 2.0, 0, 0, playerid);
                        PlayerWLLVInfo[playerid][IsPickup] = false;
                        PlayerWLLVInfo[playerid][MovedBoxCount]++;
                        SetPlayerSpecialAction(playerid, 0);
                        RemovePlayerAttachedObject(playerid, 2);
                        ApplyAnimation(playerid, "CARRY", "PUTDWN05", 4.0, 0, 0, 0, 0, 0, 1);
                    }
                    else
                    {
                        PlayerWLLVInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Loader_LV_PositionsPut[random(WORK_LOADER_LV_PUT_POINT)][0], Work_Loader_LV_PositionsPut[random(WORK_LOADER_LV_PUT_POINT)][1], Work_Loader_LV_PositionsPut[random(WORK_LOADER_LV_PUT_POINT)][2], 2.0, 0, 0, playerid);
                        PlayerWLLVInfo[playerid][IsPickup] = true;
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

dCreate:Dlg_Work_LoaderLV_Invite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nПрораб: "C_LIGHTGRAY"Ну дарова! Чего ты так стесняешься подойти то? Я не кусаюсь!\n\
    "C_LIGHTGRAY"Слухай, я по делу, на самом деле. Работёнка видно тебе нужна, а у меня она имеется.\n\
    "C_LIGHTGRAY"Твоя задача перетаскать ящики от точки выдачи до точки погрузки.\n\
    "C_LIGHTGRAY"Работа хоть и тяжёлая, но и я заплачу не гроши, а нормальную сумму.\n\
    "C_LIGHTGRAY"За каждый перенесённый ящик ты получишь %d$. Ну что, по рукам?\n\n\
    "C_WHITE"Сложность: "C_LIGHTGRAY"очень просто"C_WHITE".\n\
    "C_WHITE"Зарплата: "C_LIGHTGRAY"%d$ за ящик"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, WORK_LOADER_LV_PRICE_PER_BOX, WORK_LOADER_LV_PRICE_PER_BOX);
    return Dialog_Open(playerid, Dialog:Dlg_Work_LoaderLV_Invite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Прораб "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:Dlg_Work_LoaderLV_Invite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? (WORK_LOADER_LV_MALE_SKIN_ID) : (WORK_LOADER_LV_FEMALE_SKIN_ID)));
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = true;
        CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] = WORK_LOADER_LV_ID;
        PlayerWLLVInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Loader_LV_PositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][0], Work_Loader_LV_PositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][1], Work_Loader_LV_PositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][2], 3.0, 0, 0, playerid);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы трудоустроились на работу грузчика.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Таскайте мешки из точки А в точку Б. За каждый мешок вы получаете денежное вознаграждение.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"По окончанию работы обратитесь к прорабу.");
    }
    return 1;
}

dCreate:Dlg_Work_LoaderLV_Uninvite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nПрораб: "C_LIGHTGRAY"Хочешь сказать, что уже устал?\n\
    "C_LIGHTGRAY"С такими темпами работы ты никуда не продвинешься.\n\
    "C_LIGHTGRAY"Ну да ладно, не моё дело. Ты хочешь закончить работу?\n\n\
    "C_WHITE"Перенесено ящиков: "C_LIGHTGRAY"%d штук"C_WHITE".\n\
    "C_WHITE"Заработано: "C_LIGHTGRAY"%d$"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, PlayerWLLVInfo[playerid][MovedBoxCount], PlayerWLLVInfo[playerid][MovedBoxCount] * WORK_LOADER_LV_PRICE_PER_BOX);
    return Dialog_Open(playerid, Dialog:Dlg_Work_LoaderLV_Uninvite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Прораб "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:Dlg_Work_LoaderLV_Uninvite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Skin]);
        Money_Give(playerid, PlayerWLLVInfo[playerid][MovedBoxCount] * WORK_LOADER_LV_PRICE_PER_BOX);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы закончили работу грузчика.");
        if(PlayerWLLVInfo[playerid][MovedBoxCount] > 0)
            SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"За перенос %d ящиков получено %d$.", PlayerWLLVInfo[playerid][MovedBoxCount], PlayerWLLVInfo[playerid][MovedBoxCount] * WORK_LOADER_LV_PRICE_PER_BOX);
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = false;
        PlayerWLLVInfo[playerid][MovedBoxCount] = 0;
        DestroyDynamicCP(PlayerWLLVInfo[playerid][Checkpoint]);
    }
    return 1;
}