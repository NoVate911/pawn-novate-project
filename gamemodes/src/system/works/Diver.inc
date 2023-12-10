new const Float:WorkDiverLVPositionsInvite[4] = {-1377.9067, 2106.2063, 42.2325, 137.0381}; // Позиция устройства на работу | The position of the device for work
new const Float:WorkDiverLVPositionsBalloon[WORK_DIVER_LV_TAKE_BALLOON_POINT][3] = { // Позиции взятия баллона | Balloon taking positions
    {-1382.2135, 2114.1858, 42.2000}
};
new const Float:WorkDiverLVPositionsMarks[WORK_DIVER_LV_MARK_POINT][3] = { // Позиции меток | Placemark positions
    {-1264.9594, 2130.3674, 40.0},
    {-1255.9902, 2121.3491, 40.0},
    {-1235.5114, 2143.7822, 40.0},
    {-1226.3005, 2121.7324, 40.0}
};

/*      [ ========== ========== ========== ========== ========== ]      */

stock WorkDiverLVInit()
{
    WInfo[WORK_DIVER_LV_ID][ActorID] = CreateDynamicActor(WORK_DIVER_LV_NPC_INVITE_SKIN_ID, WorkDiverLVPositionsInvite[0], WorkDiverLVPositionsInvite[1], WorkDiverLVPositionsInvite[2], WorkDiverLVPositionsInvite[3], _, _, 0, 0);
    WInfo[WORK_DIVER_LV_ID][Actor3DText] = CreateDynamic3DTextLabel("> Долматинец <\n"C_WHITE"Нажмите "C_YELLOW"\"ALT\" "C_WHITE"для диалога", C_F_YELLOW, WorkDiverLVPositionsInvite[0], WorkDiverLVPositionsInvite[1], WorkDiverLVPositionsInvite[2]+1.5, 10.0, _, _, _, 0, 0);
    return 1;
}

stock WorkDiverLVKeyStateChange(playerid, newkeys)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        switch(newkeys)
        {
            case KEY_WALK: // L. ALT
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.0, WorkDiverLVPositionsInvite[0], WorkDiverLVPositionsInvite[1], WorkDiverLVPositionsInvite[2]))
                {
                    ApplyDynamicActorAnimation(WInfo[WORK_DIVER_LV_ID][ActorID], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);
                    PDialogInfo[playerid][IsActive] = true;
                    CInfo[playerid][PInfo[playerid][CharacterSelect]][DelayOpeningDialog] = MAX_DELAY_OPENING_DIALOG;
                    if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
                        Dialog_Show(playerid, Dialog:DlgWorkDiverLVInvite);
                    else
                    {
                        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_DIVER_LV_ID)
                            Dialog_Show(playerid, Dialog:DlgWorkDiverLVUninvite);
                    }
                }

                if(PWInfo[playerid][DiverIsAir])
                {
                    if(IsPlayerInRangeOfPoint(playerid, 2.0, PWInfo[playerid][DiverCheckpointPosition][0], PWInfo[playerid][DiverCheckpointPosition][1], PWInfo[playerid][DiverCheckpointPosition][2]))
                    {
                        DestroyDynamicCP(PWInfo[playerid][Checkpoint]);
                        PWInfo[playerid][DiverTotalTakenMarkCount]++;
                        new string[2+(-2+2)];
                        format(string, sizeof(string), "%d", PWInfo[playerid][DiverTotalTakenMarkCount]);
                        NotificationShow(playerid, string, _, false);
                        if(PWInfo[playerid][DiverTakenMarkCount] >= WORK_DIVER_LV_MARK_POINT)
                        {
                            SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Баллон с воздухом на исходе! Вернитесь на пристань и возьмите новый.");
                            PWInfo[playerid][Checkpoint] = CreateDynamicCP(WorkDiverLVPositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][0], WorkDiverLVPositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][1], WorkDiverLVPositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][2], 3.0, 0, 0, playerid);
                            PWInfo[playerid][DiverIsAir] = false;
                            PWInfo[playerid][DiverTakenMarkCount] = 0;
                        }
                        else
                        {
                            new const rand = random(WORK_DIVER_LV_MARK_POINT);
                            PWInfo[playerid][Checkpoint] = CreateDynamicCP(WorkDiverLVPositionsMarks[rand][0], WorkDiverLVPositionsMarks[rand][1], 40.0, 3.0, 0, 0, playerid);
                            for(new pos = 0; pos < 3; pos++)
                                PWInfo[playerid][DiverCheckpointPosition][pos] = WorkDiverLVPositionsMarks[rand][pos];
                            PWInfo[playerid][DiverTakenMarkCount]++;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

stock WorkDiverLVEnterDynamicCP(playerid, checkpointid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Working])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] == WORK_DIVER_LV_ID)
            {
                if(checkpointid == PWInfo[playerid][Checkpoint])
                {
                    if(!PWInfo[playerid][DiverIsAir])
                    {
                        DestroyDynamicCP(PWInfo[playerid][Checkpoint]);
                        SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы получили кислородный баллон. Отправляйтесь на сбор мусора.");
                        new const rand = random(WORK_DIVER_LV_MARK_POINT);
                        PWInfo[playerid][Checkpoint] = CreateDynamicCP(WorkDiverLVPositionsMarks[rand][0], WorkDiverLVPositionsMarks[rand][1], 40.0, 3.0, 0, 0, playerid);
                        for(new pos = 0; pos < 3; pos++)
                            PWInfo[playerid][DiverCheckpointPosition][pos] = WorkDiverLVPositionsMarks[rand][pos];
                        PWInfo[playerid][DiverIsAir] = true;
                    }
                    else
                        NotificationShow(playerid, "L.ALT", C_F_YELLOW, false);
                }
            }
        }
    }
    return 1;
}

/*      [ ========== ========== ========== ========== ========== ]      */

dCreate:DlgWorkDiverLVInvite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nДолматинец: "C_LIGHTGRAY"Привет! Сразу к делу. Меня зовут Долма, но в местных кругах я Долматинец.\n\
    "C_LIGHTGRAY"Это хороший пляж на котором люди отдыхают, плавают и веселяться.\n\
    "C_LIGHTGRAY"Некоторые из отдыхающих мусорят, теряют вещи и пакостят. Пакости - дело полиции, а вот мусор - моё..\n\
    "C_LIGHTGRAY"За каждый предмет, который соберёшь ты получаешь %d$. Поможешь?\n\n\
    "C_WHITE"Сложность: "C_LIGHTGRAY"очень просто"C_WHITE".\n\
    "C_WHITE"Зарплата: "C_LIGHTGRAY"%d$ за найденный мусор"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, WORK_DIVER_LV_PRICE_PER_MARK, WORK_DIVER_LV_PRICE_PER_MARK);
    return Dialog_Open(playerid, Dialog:DlgWorkDiverLVInvite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Долматинец "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:DlgWorkDiverLVInvite(playerid)
{
    PDialogInfo[playerid][IsActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, (CInfo[playerid][PInfo[playerid][CharacterSelect]][Sex] == 0 ? (WORK_DIVER_LV_MALE_SKIN_ID) : (WORK_DIVER_LV_FEMALE_SKIN_ID)));
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = true;
        CInfo[playerid][PInfo[playerid][CharacterSelect]][WorkingType] = WORK_DIVER_LV_ID;
        PWInfo[playerid][Checkpoint] = CreateDynamicCP(WorkDiverLVPositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][0], WorkDiverLVPositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][1], WorkDiverLVPositionsBalloon[random(WORK_DIVER_LV_TAKE_BALLOON_POINT)][2], 3.0, 0, 0, playerid);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы трудоустроились на работу дайвера.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Берите баллон с кислородом и плывите на поиски мусора. За каждый найденный мусор Вы получаете денежное вознаграждение.");
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"По окончанию работы обратитесь к Долматинцу.");
    }
    return 1;
}

dCreate:DlgWorkDiverLVUninvite(playerid)
{
    static const message[] = "\
    "C_WHITE"\nДолматинец: "C_LIGHTGRAY"Это отлично! Ты большой молодец!\n\
    "C_LIGHTGRAY"Я смогу это сдать и получить хорошие деньги, хе-хе-хе..\n\
    "C_LIGHTGRAY"Ты хочешь закончить сбор мусора?\n\n\
    "C_WHITE"Найдено мусора: "C_LIGHTGRAY"%d штук"C_WHITE".\n\
    "C_WHITE"Заработано: "C_LIGHTGRAY"%d$"C_WHITE".\n\n";
    new string[sizeof(message)+(-2+8)+(-2+8)];
    format(string, sizeof(string), message, PWInfo[playerid][DiverTotalTakenMarkCount], PWInfo[playerid][DiverTotalTakenMarkCount] * WORK_DIVER_LV_PRICE_PER_MARK);
    return Dialog_Open(playerid, Dialog:DlgWorkDiverLVUninvite, DIALOG_STYLE_MSGBOX, ""C_GRAY"Долматинец "C_BLACK"| "C_WHITE"Трудоустройство", string, "Да", "Нет");
}

dResponse:DlgWorkDiverLVUninvite(playerid)
{
    PDialogInfo[playerid][IsActive] = false;
    if(response)
    {
        SetPlayerSkin(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Skin]);
        MoneyGive(playerid, PWInfo[playerid][DiverTotalTakenMarkCount] * WORK_DIVER_LV_PRICE_PER_MARK);
        SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Вы закончили работу дайвера.");
        if(PWInfo[playerid][DiverTotalTakenMarkCount] > 0)
        {
            SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"За найденные %d мусора Вы получили %d$.", PWInfo[playerid][DiverTotalTakenMarkCount], PWInfo[playerid][DiverTotalTakenMarkCount] * WORK_DIVER_LV_PRICE_PER_MARK);
            new string[4+(-2+8)];
            format(string, sizeof(string), "+%d$", PWInfo[playerid][DiverTotalTakenMarkCount] * WORK_DIVER_LV_PRICE_PER_MARK);
            NotificationShow(playerid, string, C_F_GREEN);
        }
        CInfo[playerid][PInfo[playerid][CharacterSelect]][Working] = false;
        PWInfo[playerid][DiverTakenMarkCount] = 0;
        PWInfo[playerid][DiverTotalTakenMarkCount] = 0;
        for(new pos = 0; pos < 3; pos++)
            PWInfo[playerid][DiverCheckpointPosition] = 0.0;
        PWInfo[playerid][DiverIsAir] = false;
        DestroyDynamicCP(PWInfo[playerid][Checkpoint]);
    }
    return 1;
}