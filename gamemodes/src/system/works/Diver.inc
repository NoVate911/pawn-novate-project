new const Float:Work_Diver_LV_PositionsInvite[4] = {-1377.9067, 2106.2063, 42.2325, 137.0381}; // Позиция устройства на работу | The position of the device for work
new const Float:Work_Diver_LV_PositionsBalloon[WORK_DIVER_LV_TAKE_BALLOON_POINT][3] = { // Позиции взятия баллона | Balloon taking positions
    {-1382.2135, 2114.1858, 42.2000}
};
new const Float:Work_Diver_LV_PositionsMarks[WORK_DIVER_LV_MARK_POINT][3] = { // Позиции меток | Placemark positions
    {-1264.9594, 2130.3674, 31.1240},
    {-1255.9902, 2121.3491, 30.1487},
    {-1235.5114, 2143.7822, 32.4737},
    {-1226.3005, 2121.7324, 26.6363}
};

/*      [ ========== ========== ========== ========== ========== ]      */

stock Work_Diver_LV_Init()
{
    WDLVInfo[WORK_DIVER_LV_ID][ActorID] = CreateDynamicActor(WORK_DIVER_LV_NPC_INVITE_SKIN_ID, Work_Diver_LV_PositionsInvite[0], Work_Diver_LV_PositionsInvite[1], Work_Diver_LV_PositionsInvite[2], Work_Farmer_LV_PositionsInvite[3], _, _, 0, 0);
    WDLVInfo[WORK_DIVER_LV_ID][Actor3DText] = CreateDynamic3DTextLabel("> Долматинец <\n"C_WHITE"Нажмите "C_YELLOW"\"ALT\" "C_WHITE"для диалога", C_F_YELLOW, Work_Diver_LV_PositionsInvite[0], Work_Diver_LV_PositionsInvite[1], Work_Diver_LV_PositionsInvite[2]+1.5, 10.0, _, _, _, 0, 0);
    return 1;
}

stock Work_Diver_LV_KeyStateChange(playerid, newkeys)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        switch(newkeys)
        {
            case KEY_WALK: // L. ALT
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, Work_Diver_LV_PositionsInvite[0], Work_Diver_LV_PositionsInvite[1], Work_Diver_LV_PositionsInvite[2]))
                {
                    ApplyDynamicActorAnimation(WDLVInfo[WORK_DIVER_LV_ID][ActorID], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
                    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = true;
                    if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
                        Dialog_Show(playerid, Dialog:Dlg_Work_DiverLV_Invite);
                    else
                    {
                        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_DIVER_LV_ID)
                            Dialog_Show(playerid, Dialog:Dlg_Work_DiverLV_Uninvite);
                    }
                }

                if(PlayerWDLVInfo[playerid][IsAir])
                {
                    if(IsPlayerInRangeOfPoint(playerid, 2.0, PlayerWDLVInfo[playerid][CheckpointPosition][0], PlayerWDLVInfo[playerid][CheckpointPosition][1], PlayerWDLVInfo[playerid][CheckpointPosition][2]))
                    {
                        DestroyDynamicCP(PlayerWDLVInfo[playerid][Checkpoint]);
                        PlayerWDLVInfo[playerid][TotalTakenMarkCount]++;
                        if(PlayerWDLVInfo[playerid][TakenMarkCount] >= WORK_DIVER_LV_MARK_POINT)
                        {
                            SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Баллон с воздухом на исходе! Вернитесь на берег и возьмите новый.");
                            PlayerWDLVInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Diver_LV_PositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][0], Work_Diver_LV_PositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][1], Work_Diver_LV_PositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][2], 3.0, 0, 0, playerid);
                            PlayerWDLVInfo[playerid][IsAir] = false;
                            PlayerWDLVInfo[playerid][TakenMarkCount] = 0;
                        }
                        else
                        {
                            new const rand = random(WORK_DIVER_LV_MARK_POINT);
                            PlayerWDLVInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Diver_LV_PositionsMarks[rand][0], Work_Diver_LV_PositionsMarks[rand][1], Work_Diver_LV_PositionsMarks[rand][2], 3.0, 0, 0, playerid);
                            for(new pos = 0; pos < 3; pos++)
                                PlayerWDLVInfo[playerid][CheckpointPosition][pos] = Work_Diver_LV_PositionsMarks[rand][pos];
                            PlayerWDLVInfo[playerid][TakenMarkCount]++;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

stock Work_Diver_LV_EnterDynamicCP(playerid, checkpointid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_DIVER_LV_ID)
            {
                if(checkpointid == PlayerWDLVInfo[playerid][Checkpoint])
                {
                    if(!PlayerWDLVInfo[playerid][IsAir])
                    {
                        DestroyDynamicCP(PlayerWDLVInfo[playerid][Checkpoint]);
                        SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы получили кислородный баллон. Отправляйтесь на поиски вещей.");
                        new const rand = random(WORK_DIVER_LV_MARK_POINT);
                        PlayerWDLVInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Diver_LV_PositionsMarks[rand][0], Work_Diver_LV_PositionsMarks[rand][1], Work_Diver_LV_PositionsMarks[rand][2], 3.0, 0, 0, playerid);
                        for(new pos = 0; pos < 3; pos++)
                            PlayerWDLVInfo[playerid][CheckpointPosition][pos] = Work_Diver_LV_PositionsMarks[rand][pos];
                        PlayerWDLVInfo[playerid][IsAir] = true;
                    }
                }
            }
        }
    }
    return 1;
}

/*      [ ========== ========== ========== ========== ========== ]      */

dCreate:Dlg_Work_DiverLV_Invite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nДолматинец: "C_LIGHTGRAY"Ну дарова! Чего ты так стесняешься подойти то? Я не кусаюсь!\n\
    "C_LIGHTGRAY"Слухай, я по делу, на самом деле. Работёнка видно тебе нужна, а у меня она имеется.\n\
    "C_LIGHTGRAY"Твоя задача перетаскать ящики от точки выдачи до точки погрузки.\n\
    "C_LIGHTGRAY"Работа хоть и тяжёлая, но и я заплачу не гроши, а нормальную сумму.\n\
    "C_LIGHTGRAY"За каждую метку ты получишь %d$. Ну что, по рукам?\n\n\
    "C_WHITE"Сложность: "C_LIGHTGRAY"очень просто"C_WHITE".\n\
    "C_WHITE"Зарплата: "C_LIGHTGRAY"%d$ за метку"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, WORK_DIVER_LV_PRICE_PER_MARK, WORK_DIVER_LV_PRICE_PER_MARK);
    return Dialog_Open(playerid, Dialog:Dlg_Work_DiverLV_Invite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Долматинец "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:Dlg_Work_DiverLV_Invite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? (WORK_DIVER_LV_MALE_SKIN_ID) : (WORK_DIVER_LV_FEMALE_SKIN_ID)));
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = true;
        CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] = WORK_DIVER_LV_ID;
        PlayerWDLVInfo[playerid][Checkpoint] = CreateDynamicCP(Work_Diver_LV_PositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][0], Work_Diver_LV_PositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][1], Work_Diver_LV_PositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][2], 3.0, 0, 0, playerid);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы трудоустроились на работу дайвера.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Берите баллон с кислородом и плывите на поиски вещей. За каждую вещь вы получаете денежное вознаграждение.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"По окончанию работы обратитесь к Долматинцу.");
    }
    return 1;
}

dCreate:Dlg_Work_DiverLV_Uninvite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nДолматинец: "C_LIGHTGRAY"Хочешь сказать, что уже устал?\n\
    "C_LIGHTGRAY"С такими темпами работы ты никуда не продвинешься.\n\
    "C_LIGHTGRAY"Ну да ладно, не моё дело. Ты хочешь закончить работу?\n\n\
    "C_WHITE"Найдено вещей: "C_LIGHTGRAY"%d штук"C_WHITE".\n\
    "C_WHITE"Заработано: "C_LIGHTGRAY"%d$"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, PlayerWDLVInfo[playerid][TotalTakenMarkCount], PlayerWDLVInfo[playerid][TotalTakenMarkCount] * WORK_DIVER_LV_PRICE_PER_MARK);
    return Dialog_Open(playerid, Dialog:Dlg_Work_DiverLV_Uninvite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Долматинец "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:Dlg_Work_DiverLV_Uninvite(playerid)
{
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsDialogActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Skin]);
        Money_Give(playerid, PlayerWDLVInfo[playerid][TotalTakenMarkCount] * WORK_DIVER_LV_PRICE_PER_MARK);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы закончили работу дайвера.");
        if(PlayerWDLVInfo[playerid][TotalTakenMarkCount] > 0)
            SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"За находку %d вещей получено %d$.", PlayerWDLVInfo[playerid][TotalTakenMarkCount], PlayerWDLVInfo[playerid][TotalTakenMarkCount] * WORK_DIVER_LV_PRICE_PER_MARK);
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = false;
        PlayerWDLVInfo[playerid][TakenMarkCount] = 0;
        PlayerWDLVInfo[playerid][TotalTakenMarkCount] = 0;
        PlayerWDLVInfo[playerid][IsAir] = false;
        DestroyDynamicCP(PlayerWDLVInfo[playerid][Checkpoint]);
    }
    return 1;
}