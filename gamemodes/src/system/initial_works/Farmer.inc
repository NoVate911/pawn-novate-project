new const Float:WorkFarmerLVPositionsInvite[4] = {288.9738, 1141.4445, 8.5859, 86.5413}; // Позиция устройства на работу | The position of the device for work
new const Float:WorkFarmerLVPositionsPickup[WORK_FARMER_LV_PICKUP_POINT][3] = { // Позиции взятия сена | Hay taking positions
    {261.0748, 1150.7540, 11.0834},
    {250.6571, 1150.7491, 11.6542},
    {239.0386, 1150.9663, 12.2485},
    {228.5628, 1151.3781, 13.0933}
};
new const Float:WorkFarmerLVPositionsPut[WORK_FARMER_LV_PUT_POINT][3] = { // Позиции сдачи сена | Hay delivery positions
    {315.3572, 1148.3951, 8.5859}
};

/*      [ ========== ========== ========== ========== ========== ]      */

stock WorkFarmerLVInit()
{
    WInfo[WORK_FARMER_LV_ID][ActorID] = CreateDynamicActor(WORK_FARMER_LV_NPC_INVITE_SKIN_ID, WorkFarmerLVPositionsInvite[0], WorkFarmerLVPositionsInvite[1], WorkFarmerLVPositionsInvite[2], WorkFarmerLVPositionsInvite[3], _, _, 0, 0);
    WInfo[WORK_FARMER_LV_ID][Actor3DText] = CreateDynamic3DTextLabel("> Эдуард <\n"C_WHITE"Нажмите "C_YELLOW"\"ALT\" "C_WHITE"для диалога", C_F_YELLOW, WorkFarmerLVPositionsInvite[0], WorkFarmerLVPositionsInvite[1], WorkFarmerLVPositionsInvite[2]+1.5, 10.0, _, _, _, 0, 0);
    return 1;
}

stock WorkFarmerLVKeyStateChange(playerid, newkeys)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        switch(newkeys)
        {
            case KEY_WALK: // L. ALT
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, WorkFarmerLVPositionsInvite[0], WorkFarmerLVPositionsInvite[1], WorkFarmerLVPositionsInvite[2]))
                {
                    if(PWInfo[playerid][FarmerIsPickup])
                        return SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Для того, чтобы окончить работу нужно отнести сноп сена в амбар.");

                    ApplyDynamicActorAnimation(WInfo[WORK_FARMER_LV_ID][ActorID], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
                    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = true;
                    if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
                        Dialog_Show(playerid, Dialog:DlgWorkFarmerLVInvite);
                    else
                    {
                        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_FARMER_LV_ID)
                            Dialog_Show(playerid, Dialog:DlgWorkFarmerLVUninvite);
                    }
                }
            }
        }
    }
    return 1;
}

stock WorkFarmerLVEnterDynamicCP(playerid, checkpointid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_FARMER_LV_ID)
            {
                if(checkpointid == PWInfo[playerid][Checkpoint])
                {
                    DestroyDynamicCP(PWInfo[playerid][Checkpoint]);
                    if(PWInfo[playerid][FarmerIsPickup])
                    {
                        PWInfo[playerid][Checkpoint] = CreateDynamicCP(WorkFarmerLVPositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][0], WorkFarmerLVPositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][1], WorkFarmerLVPositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][2], 2.0, 0, 0, playerid);
                        PWInfo[playerid][FarmerIsPickup] = false;
                        PWInfo[playerid][FarmerMovedHayCount]++;
                        SetPlayerSpecialAction(playerid, 0);
                        RemovePlayerAttachedObject(playerid, 2);
                        ApplyAnimation(playerid, "CARRY", "PUTDWN05", 4.0, 0, 0, 0, 0, 0, 1);
                        NotificationShow(playerid, "+1");
                    }
                    else
                    {
                        PWInfo[playerid][Checkpoint] = CreateDynamicCP(WorkFarmerLVPositionsPut[random(WORK_FARMER_LV_PUT_POINT)][0], WorkFarmerLVPositionsPut[random(WORK_FARMER_LV_PUT_POINT)][1], WorkFarmerLVPositionsPut[random(WORK_FARMER_LV_PUT_POINT)][2], 2.0, 0, 0, playerid);
                        PWInfo[playerid][FarmerIsPickup] = true;
                        SetPlayerSpecialAction(playerid, 25);
                        SetPlayerAttachedObject(playerid, 2, 1453, 5, 0.01, 0.1, 0.2, 0, 10, 85);
                        ApplyAnimation(playerid, "CARRY", "LIFTUP05", 4.0, 0, 0, 0, 0, 0, 1);
                    }
                }
            }
        }
    }
    return 1;
}

/*      [ ========== ========== ========== ========== ========== ]      */

dCreate:DlgWorkFarmerLVInvite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nЭдуард: "C_LIGHTGRAY"Привет, друг! Меня звать Эдуард. Тут я местный фермер.\n\
    "C_LIGHTGRAY"Я вижу, что ты ищешь работу, не так ли?\n\
    "C_LIGHTGRAY"Я могу предложить тебе собирать готовые снопы сена и таскать в амбар за этим домом.\n\
    "C_LIGHTGRAY"За один перенесённый сноп сена ты получаешь %d$, пойдет?\n\n\
    "C_WHITE"Сложность: "C_LIGHTGRAY"очень просто"C_WHITE".\n\
    "C_WHITE"Зарплата: "C_LIGHTGRAY"%d$ за сено"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, WORK_FARMER_LV_PRICE_PER_HAY, WORK_FARMER_LV_PRICE_PER_HAY);
    return Dialog_Open(playerid, Dialog:DlgWorkFarmerLVInvite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Эдуард "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:DlgWorkFarmerLVInvite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? (WORK_FARMER_LV_MALE_SKIN_ID) : (WORK_FARMER_LV_FEMALE_SKIN_ID)));
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = true;
        CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] = WORK_FARMER_LV_ID;
        PWInfo[playerid][Checkpoint] = CreateDynamicCP(WorkFarmerLVPositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][0], WorkFarmerLVPositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][1], WorkFarmerLVPositionsPickup[random(WORK_FARMER_LV_PICKUP_POINT)][2], 3.0, 0, 0, playerid);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы трудоустроились на работу фермера.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Таскайте снопы сена в амбар. За каждый сноп сена вы получаете денежное вознаграждение.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"По окончанию работы обратитесь к Эдуарду.");
    }
    return 1;
}

dCreate:DlgWorkFarmerLVUninvite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nЭдуард: "C_LIGHTGRAY"На этом всё? Запыхался?\n\
    "C_LIGHTGRAY"Смотрю на тебя и вижу, как ты устал, совсем хиленький.\n\
    "C_LIGHTGRAY"Сходи в 24/7, он тут поблизости и купи воды. Заканчиваешь работу?\n\n\
    "C_WHITE"Перенесено снопов сена: "C_LIGHTGRAY"%d штук"C_WHITE".\n\
    "C_WHITE"Заработано: "C_LIGHTGRAY"%d$"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, PWInfo[playerid][FarmerMovedHayCount], PWInfo[playerid][FarmerMovedHayCount] * WORK_FARMER_LV_PRICE_PER_HAY);
    return Dialog_Open(playerid, Dialog:DlgWorkFarmerLVUninvite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Эдуард "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:DlgWorkFarmerLVUninvite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Skin]);
        MoneyGive(playerid, PWInfo[playerid][FarmerMovedHayCount] * WORK_FARMER_LV_PRICE_PER_HAY);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы закончили работу фермера.");
        if(PWInfo[playerid][FarmerMovedHayCount] > 0)
        {
            SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"За перенос %d снопов сена Вы получили %d$.", PWInfo[playerid][FarmerMovedHayCount], PWInfo[playerid][FarmerMovedHayCount] * WORK_FARMER_LV_PRICE_PER_HAY);
            new string[4+(-2+8)];
            format(string, sizeof(string), "+%d$", PWInfo[playerid][FarmerMovedHayCount] * WORK_FARMER_LV_PRICE_PER_HAY);
            NotificationShow(playerid, string, C_F_GREEN);
        }
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = false;
        PWInfo[playerid][FarmerMovedHayCount] = 0;
        PWInfo[playerid][FarmerIsPickup] = false;
        DestroyDynamicCP(PWInfo[playerid][Checkpoint]);
    }
    return 1;
}