new const Float:Work_Loader_Positions_Invite[4] = {2442.2417, 1954.8455, 10.7978, 269.7844}; // Позиция устройства на работу | The position of the device for work
new const Float:Work_Loader_Positions_Pickup[WORK_LOADER_PICKUP_POINT][3] = { // Позиции взятия груза | Cargo pickup positions
    {2414.1614, 1949.2720, 6.0156},
    {2421.8457, 1953.3391, 6.0156}
};
new const Float:Work_Loader_Positions_Put[WORK_LOADER_PUT_POINT][3] = { // Позиции сдачи груза | Delivery positions
    {2478.2112, 1951.4685, 10.3570},
    {2473.5769, 1939.1465, 9.9569}
};

/*      [ ========== ========== ========== ========== ========== ]      */

stock Work_Loader_Init()
{
    WLInfo[WORK_LOADER_ID][ActorID] = CreateDynamicActor(WORK_LOADER_NPC_INVITE_SKIN_ID, Work_Loader_Positions_Invite[0], Work_Loader_Positions_Invite[1], Work_Loader_Positions_Invite[2], Work_Loader_Positions_Invite[3], _, _, 0, 0);
    WLInfo[WORK_LOADER_ID][Actor3DText] = CreateDynamic3DTextLabel("> Прораб <\n"C_WHITE"Нажмите "C_YELLOW"\"ALT\" "C_WHITE"для диалога", C_F_YELLOW, Work_Loader_Positions_Invite[0], Work_Loader_Positions_Invite[1], Work_Loader_Positions_Invite[2]+1.5, 10.0, _, _, _, 0, 0);
    return 1;
}

stock Work_Loader_KeyStateChange(playerid, newkeys)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        switch(newkeys)
        {
            case KEY_WALK: // L. ALT
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, Work_Loader_Positions_Invite[0], Work_Loader_Positions_Invite[1], Work_Loader_Positions_Invite[2]))
                {
                    ApplyDynamicActorAnimation(WLInfo[WORK_LOADER_ID][ActorID], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
                    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = true;
                    if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
                        Dialog_Show(playerid, Dialog:Dlg_Work_Loader_Invite);
                    else
                    {
                        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_LOADER_ID)
                            Dialog_Show(playerid, Dialog:Dlg_Work_Loader_Uninvite);
                    }
                }
            }
        }
    }
    return 1;
}

public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_LOADER_ID)
            {
                if(checkpointid == PlayerWLInfo[playerid][Checkpoint])
                {
                    DestroyDynamicCP(PlayerWLInfo[playerid][Checkpoint]);
                    if(PlayerWLInfo[playerid][IsBoxPickup])
                    {
                        PlayerWLInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Loader_Positions_Pickup[random(WORK_LOADER_PICKUP_POINT)][0], Work_Loader_Positions_Pickup[random(WORK_LOADER_PICKUP_POINT)][1], Work_Loader_Positions_Pickup[random(WORK_LOADER_PICKUP_POINT)][2], 2.0, 0, 0, playerid);
                        PlayerWLInfo[playerid][IsBoxPickup] = false;
                        PlayerWLInfo[playerid][MovedBoxCount]++;
                        SetPlayerSpecialAction(playerid, 0);
                        RemovePlayerAttachedObject(playerid, 2);
                    }
                    else
                    {
                        PlayerWLInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Loader_Positions_Put[random(WORK_LOADER_PUT_POINT)][0], Work_Loader_Positions_Put[random(WORK_LOADER_PUT_POINT)][1], Work_Loader_Positions_Put[random(WORK_LOADER_PUT_POINT)][2], 2.0, 0, 0, playerid);
                        PlayerWLInfo[playerid][IsBoxPickup] = true;
                        SetPlayerSpecialAction(playerid, 25);
                        SetPlayerAttachedObject(playerid, 2, 1279, 5, 0.01, 0.1, 0.2, 100, 10, 85);
                    }
                }
            }
        }
    }
    return 1;
}

/*      [ ========== ========== ========== ========== ========== ]      */

dCreate:Dlg_Work_Loader_Invite(playerid)
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
    format(string, sizeof(string), message, WORK_LOADER_PRICE_PER_BOX, WORK_LOADER_PRICE_PER_BOX);
    return Dialog_Open(playerid, Dialog:Dlg_Work_Loader_Invite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Прораб "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:Dlg_Work_Loader_Invite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? (WORK_LOADER_MALE_SKIN_ID) : (WORK_LOADER_FEMALE_SKIN_ID)));
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = true;
        CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] = WORK_LOADER_ID;
        PlayerWLInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Loader_Positions_Pickup[random(WORK_LOADER_PICKUP_POINT)][0], Work_Loader_Positions_Pickup[random(WORK_LOADER_PICKUP_POINT)][1], Work_Loader_Positions_Pickup[random(WORK_LOADER_PICKUP_POINT)][2], 3.0, 0, 0, playerid);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы трудоустроились на работу грузчика.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Таскайте мешки из точки А в точку Б. За каждый мешок вы получаете денежное вознаграждение.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"По окончанию работы обратитесь к прорабу.");
    }
    return 1;
}

dCreate:Dlg_Work_Loader_Uninvite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nПрораб: "C_LIGHTGRAY"Хочешь сказать, что уже устал?\n\
    "C_LIGHTGRAY"С такими темпами работы ты никуда не продвинешься.\n\
    "C_LIGHTGRAY"Ну да ладно, не моё дело. Ты хочешь закончить работу?\n\n\
    "C_WHITE"Перенесено ящиков: "C_LIGHTGRAY"%d штук"C_WHITE".\n\
    "C_WHITE"Заработано: "C_LIGHTGRAY"%d$"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, PlayerWLInfo[playerid][MovedBoxCount], PlayerWLInfo[playerid][MovedBoxCount] * WORK_LOADER_PRICE_PER_BOX);
    return Dialog_Open(playerid, Dialog:Dlg_Work_Loader_Uninvite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Прораб "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:Dlg_Work_Loader_Uninvite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Skin]);
        Money_Give(playerid, PlayerWLInfo[playerid][MovedBoxCount] * WORK_LOADER_PRICE_PER_BOX);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы закончили работу грузчика.");
        SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"За перенос %d ящиков получено %d$.", PlayerWLInfo[playerid][MovedBoxCount], PlayerWLInfo[playerid][MovedBoxCount] * WORK_LOADER_PRICE_PER_BOX);
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = false;
        PlayerWLInfo[playerid][MovedBoxCount] = 0;
    }
    return 1;
}