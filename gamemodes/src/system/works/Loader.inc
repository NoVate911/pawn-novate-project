new const Float:WorkLoaderLVPositionsInvite[4] = {2442.2417, 1954.8455, 10.7978, 269.7844}; // Позиция устройства на работу | The position of the device for work
new const Float:WorkLoaderLVPositionsPickup[WORK_LOADER_LV_PICKUP_POINT][3] = { // Позиции взятия груза | Cargo pickup positions
    {2414.1614, 1949.2720, 6.0156},
    {2421.8457, 1953.3391, 6.0156}
};
new const Float:WorkLoaderLVPositionsPut[WORK_LOADER_LV_PUT_POINT][3] = { // Позиции сдачи груза | Delivery positions
    {2478.2112, 1951.4685, 10.3570},
    {2473.5769, 1939.1465, 9.9569}
};

/*      [ ========== ========== ========== ========== ========== ]      */

stock WorkLoaderLVInit()
{
    WInfo[WORK_LOADER_LV_ID][ActorID] = CreateDynamicActor(WORK_LOADER_LV_NPC_INVITE_SKIN_ID, WorkLoaderLVPositionsInvite[0], WorkLoaderLVPositionsInvite[1], WorkLoaderLVPositionsInvite[2], WorkLoaderLVPositionsInvite[3], _, _, 0, 0);
    WInfo[WORK_LOADER_LV_ID][Actor3DText] = CreateDynamic3DTextLabel("> Прораб <\n"C_WHITE"Нажмите "C_YELLOW"\"ALT\" "C_WHITE"для диалога", C_F_YELLOW, WorkLoaderLVPositionsInvite[0], WorkLoaderLVPositionsInvite[1], WorkLoaderLVPositionsInvite[2]+1.5, 10.0, _, _, _, 0, 0);
    return 1;
}

stock WorkLoaderLVKeyStateChange(playerid, newkeys)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        switch(newkeys)
        {
            case KEY_WALK: // L. ALT
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, WorkLoaderLVPositionsInvite[0], WorkLoaderLVPositionsInvite[1], WorkLoaderLVPositionsInvite[2]))
                {
                    if(PWInfo[playerid][LoaderIsPickup])
                        return SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Для того, чтобы окончить работу нужно сдать ящик.");

                    ApplyDynamicActorAnimation(WInfo[WORK_LOADER_LV_ID][ActorID], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
                    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = true;
                    CInfo[playerid][PInfo[playerid][CharacterSelect]][DelayOpeningDialog] = MAX_DELAY_OPENING_DIALOG;
                    if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
                        Dialog_Show(playerid, Dialog:DlgWorkLoaderLVInvite);
                    else
                    {
                        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_LOADER_LV_ID)
                            Dialog_Show(playerid, Dialog:DlgWorkLoaderLVUninvite);
                    }
                }
            }
        }
    }
    return 1;
}

stock WorkLoaderLVEnterDynamicCP(playerid, checkpointid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_LOADER_LV_ID)
            {
                if(checkpointid == PWInfo[playerid][Checkpoint])
                {
                    DestroyDynamicCP(PWInfo[playerid][Checkpoint]);
                    if(PWInfo[playerid][LoaderIsPickup])
                    {
                        PWInfo[playerid][Checkpoint] = CreateDynamicCP(WorkLoaderLVPositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][0], WorkLoaderLVPositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][1], WorkLoaderLVPositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][2], 2.0, 0, 0, playerid);
                        PWInfo[playerid][LoaderIsPickup] = false;
                        PWInfo[playerid][LoaderMovedBoxCount]++;
                        SetPlayerSpecialAction(playerid, 0);
                        RemovePlayerAttachedObject(playerid, 2);
                        ApplyAnimation(playerid, "CARRY", "PUTDWN05", 4.0, 0, 0, 0, 0, 0, 1);
                        NotificationShow(playerid, "+1");
                    }
                    else
                    {
                        PWInfo[playerid][Checkpoint] = CreateDynamicCP(WorkLoaderLVPositionsPut[random(WORK_LOADER_LV_PUT_POINT)][0], WorkLoaderLVPositionsPut[random(WORK_LOADER_LV_PUT_POINT)][1], WorkLoaderLVPositionsPut[random(WORK_LOADER_LV_PUT_POINT)][2], 2.0, 0, 0, playerid);
                        PWInfo[playerid][LoaderIsPickup] = true;
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

dCreate:DlgWorkLoaderLVInvite(playerid)
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
    return Dialog_Open(playerid, Dialog:DlgWorkLoaderLVInvite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Прораб "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:DlgWorkLoaderLVInvite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? (WORK_LOADER_LV_MALE_SKIN_ID) : (WORK_LOADER_LV_FEMALE_SKIN_ID)));
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = true;
        CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] = WORK_LOADER_LV_ID;
        PWInfo[playerid][Checkpoint] = CreateDynamicCP(WorkLoaderLVPositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][0], WorkLoaderLVPositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][1], WorkLoaderLVPositionsPickup[random(WORK_LOADER_LV_PICKUP_POINT)][2], 3.0, 0, 0, playerid);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы трудоустроились на работу грузчика.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Таскайте мешки из точки А в точку Б. За каждый мешок вы получаете денежное вознаграждение.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"По окончанию работы обратитесь к прорабу.");
    }
    return 1;
}

dCreate:DlgWorkLoaderLVUninvite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nПрораб: "C_LIGHTGRAY"Хочешь сказать, что уже устал?\n\
    "C_LIGHTGRAY"С такими темпами работы ты никуда не продвинешься.\n\
    "C_LIGHTGRAY"Ну да ладно, не моё дело. Ты хочешь закончить работу?\n\n\
    "C_WHITE"Перенесено ящиков: "C_LIGHTGRAY"%d штук"C_WHITE".\n\
    "C_WHITE"Заработано: "C_LIGHTGRAY"%d$"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, PWInfo[playerid][LoaderMovedBoxCount], PWInfo[playerid][LoaderMovedBoxCount] * WORK_LOADER_LV_PRICE_PER_BOX);
    return Dialog_Open(playerid, Dialog:DlgWorkLoaderLVUninvite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Прораб "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:DlgWorkLoaderLVUninvite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Skin]);
        MoneyGive(playerid, PWInfo[playerid][LoaderMovedBoxCount] * WORK_LOADER_LV_PRICE_PER_BOX);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы закончили работу грузчика.");
        if(PWInfo[playerid][LoaderMovedBoxCount] > 0)
        {
            SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"За перенос %d ящиков получено %d$.", PWInfo[playerid][LoaderMovedBoxCount], PWInfo[playerid][LoaderMovedBoxCount] * WORK_LOADER_LV_PRICE_PER_BOX);
            new string[4+(-2+8)];
            format(string, sizeof(string), "+%d$", PWInfo[playerid][LoaderMovedBoxCount] * WORK_LOADER_LV_PRICE_PER_BOX);
            NotificationShow(playerid, string, C_F_GREEN);
        }
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = false;
        PWInfo[playerid][LoaderMovedBoxCount] = 0;
        PWInfo[playerid][LoaderIsPickup] = false;
        DestroyDynamicCP(PWInfo[playerid][Checkpoint]);
    }
    return 1;
}