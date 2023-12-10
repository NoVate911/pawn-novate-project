new const Float:DrivingSchoolPositionsBeginning[MAX_DRIVING_SCHOOL][4] = { // Позиции начала сдачи экзамена | Exam start positions
    {1173.1636, 1349.3612, 10.9219, 181.2486}
};

new const DrivingSchoolLicensesParams[MAX_DRIVING_SCHOOL_LICENSES][2] = { // Категории лицензий для сдачи | License categories for delivery
    // {цена, ид транспорта для сдачи} | {price, transport ID for delivery}
    {500, 445},
    {10000, 403}
};

new const DrivingSchoolLicensesName[MAX_DRIVING_SCHOOL_LICENSES][] = { // Название категорий лицензий для сдачи | The name of the license categories for delivery
    "Легковой транспорт",
    "Грузовой транспорт"
};

new const Float:DrivingSchoolPositionsSpawnVehs[MAX_DRIVING_SCHOOL_LICENSES][4] = { // Позиции появления транспорта при начале экзамена | The position of the appearance of transport at the beginning of the exam
    {1171.2139, 1340.1089, 10.6875, 91.0170},
    {1171.2139, 1340.1089, 10.6875, 91.0170}
};

/*      [ ========== ========== ========== ========== ========== ]      */

stock DrivingSchoolInit()
{
    for(new i = 0; i < MAX_DRIVING_SCHOOL; i++)
    {
        DSchoolInfo[i][BeginningPickup] = CreateDynamicPickup(1239, 1, DrivingSchoolPositionsBeginning[i][0], DrivingSchoolPositionsBeginning[i][1], DrivingSchoolPositionsBeginning[i][2], 0, 0);
        DSchoolInfo[i][Beginning3DText] = CreateDynamic3DTextLabel("> СДАЧА ЭКЗАМЕНА <\n"C_WHITE"Нажмите \"ALT\" для начала сдачи.", C_F_YELLOW, DrivingSchoolPositionsBeginning[i][0], DrivingSchoolPositionsBeginning[i][1], DrivingSchoolPositionsBeginning[i][2]+1.0, 10.0, _, _, _, 0, 0);
    }
    return 1;
}

stock DrivingSchoolKeyStateChange(playerid, newkeys)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        switch(newkeys)
        {
            case KEY_WALK: // L. ALT
            {
                for(new id = 0; id < MAX_DRIVING_SCHOOL; id++)
                {
                    if(IsPlayerInRangeOfPoint(playerid, 2.0, DrivingSchoolPositionsBeginning[id][0], DrivingSchoolPositionsBeginning[id][1], DrivingSchoolPositionsBeginning[id][2]))
                    {
                        PDialogInfo[playerid][IsActive] = true;
                        CInfo[playerid][PInfo[playerid][CharacterSelect]][DelayOpeningDialog] = MAX_DELAY_OPENING_DIALOG;
                        CLicenseInfo[playerid][SchoolID] = id;
                        Dialog_Show(playerid, Dialog:DlgDrivingSchoolLicenses);
                        break;
                    }
                }
            }
        }
    }
    return 1;
}

stock DrivingSchoolStateChange(playerid, newstate, oldstate)
{
    if(oldstate == PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_DRIVER)
    {
        if(CLicenseInfo[playerid][IsStarted])
        {
            CLicenseInfo[playerid][IsStarted] = false;
            SetPlayerVirtualWorld(playerid, 0);
            VehicleDestroy(CLicenseInfo[playerid][VehicleID]);
            SetPlayerPos(playerid, DrivingSchoolPositionsBeginning[CLicenseInfo[playerid][SchoolID]][0], DrivingSchoolPositionsBeginning[CLicenseInfo[playerid][SchoolID]][1], DrivingSchoolPositionsBeginning[CLicenseInfo[playerid][SchoolID]][2]);
            SetPlayerFacingAngle(playerid, DrivingSchoolPositionsBeginning[CLicenseInfo[playerid][SchoolID]][3]);
            SetCameraBehindPlayer(playerid);
            SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Вы принудительно закончили сдачу экзамена из-за того, что покинули транспорт.");
        }
    }
    else if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle])
            CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle] = false;
    }
    return 1;
}

stock DrivingSchoolEnterDynamicCP(playerid, checkpointid)
{
    new const Float:driverPositionsCheckpoint[11][3] = {
        {1157.7979, 1319.6343, 10.6952},
        {1157.6028, 1271.1787, 10.6952},
        {1133.8137, 1240.4879, 10.6952},
        {1115.0806, 1260.3724, 10.6952},
        {1134.2081, 1281.2137, 10.6952},
        {1135.2109, 1310.3784, 10.6952},
        {1108.6718, 1335.1180, 10.6953},
        {1136.2954, 1351.3788, 10.6953},
        {1148.8702, 1325.4036, 10.6952},
        {1163.5385, 1303.2172, 10.6952},
        {1171.5242, 1337.0902, 10.6874}
    };

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        if(CLicenseInfo[playerid][IsStarted])
        {
            if(checkpointid == CLicenseInfo[playerid][Checkpoint])
            {
                CLicenseInfo[playerid][CurrentCheckpoint]++;
                if(IsValidDynamicCP(CLicenseInfo[playerid][Checkpoint]))
                    DestroyDynamicCP(CLicenseInfo[playerid][Checkpoint]);
                switch(CLicenseInfo[playerid][SelectedCategory])
                {
                    case 0:
                    {
                        if(CLicenseInfo[playerid][CurrentCheckpoint] < sizeof(driverPositionsCheckpoint))
                        {
                            CLicenseInfo[playerid][Checkpoint] = CreateDynamicCP(driverPositionsCheckpoint[CLicenseInfo[playerid][CurrentCheckpoint]][0], driverPositionsCheckpoint[CLicenseInfo[playerid][CurrentCheckpoint]][1], driverPositionsCheckpoint[CLicenseInfo[playerid][CurrentCheckpoint]][2], 5.0, GetPlayerVirtualWorld(playerid), 0, playerid);
                            return 1;
                        }
                        CLicenseInfo[playerid][IsDriver] = true;
                    }
                }
                CLicenseInfo[playerid][IsStarted] = false;
                CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle] = false;
                SetPlayerVirtualWorld(playerid, 0);
                VehicleDestroy(CLicenseInfo[playerid][VehicleID]);
                SetPlayerPos(playerid, DrivingSchoolPositionsBeginning[CLicenseInfo[playerid][SchoolID]][0], DrivingSchoolPositionsBeginning[CLicenseInfo[playerid][SchoolID]][1], DrivingSchoolPositionsBeginning[CLicenseInfo[playerid][SchoolID]][2]);
                SetPlayerFacingAngle(playerid, DrivingSchoolPositionsBeginning[CLicenseInfo[playerid][SchoolID]][3]);
                SetCameraBehindPlayer(playerid);
                SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Поздравляем! Вы получили права на категорию %s.", DrivingSchoolLicensesName[CLicenseInfo[playerid][SelectedCategory]]);
            }
        }
    }
    return 1;
}

/*      [ ========== ========== ========== ========== ========== ]      */

dCreate:DlgDrivingSchoolLicenses(playerid)
{
    static const message[] = "\
    "C_GRAY"Категория\t"C_GRAY"Цена\n\
    %s";
    new category[9+(-2+MAX_PLAYER_NAME)+(-2+8)];
    new categories_string[sizeof(category)*MAX_DRIVING_SCHOOL_LICENSES];
    for(new i = 0; i < MAX_DRIVING_SCHOOL_LICENSES; i++)
    {
        format(category, sizeof(category), "%s\t%d$\n", DrivingSchoolLicensesName[i], DrivingSchoolLicensesParams[i][0]);
        strcat(categories_string, category, sizeof(categories_string));
    }
    new string[sizeof(message)+(-2+sizeof(categories_string))];
    format(string, sizeof(string), message, categories_string);
    return Dialog_Open(playerid, Dialog:DlgDrivingSchoolLicenses, DIALOG_STYLE_TABLIST_HEADERS, ""C_GRAY"Автошкола "C_BLACK"| "C_WHITE"Выбор категории", string, "Выбрать", "Выйти");
}

dResponse:DlgDrivingSchoolLicenses(playerid)
{
    if(response)
    {
        CLicenseInfo[playerid][SelectedCategory] = listitem;
        Dialog_Show(playerid, Dialog:DlgDrivingSchoolBeginning);
    }
    else
        PDialogInfo[playerid][IsActive] = false;
    return 1;
}

dCreate:DlgDrivingSchoolBeginning(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cКатегория для сдачи: %s\n\
    "C_WHITE"\\cЦена сдачи: %d$\n\n\
    "C_WHITE"\\cВы согласны сдать экзамен?\n\n";
    new string[sizeof(message)+(-2+MAX_PLAYER_NAME)+(-2+8)];
    format(string, sizeof(string), message, DrivingSchoolLicensesName[CLicenseInfo[playerid][SelectedCategory]], DrivingSchoolLicensesParams[CLicenseInfo[playerid][SelectedCategory]][0]);
    return Dialog_Open(playerid, Dialog:DlgDrivingSchoolBeginning, DIALOG_STYLE_MSGBOX, ""C_GRAY"Автошкола "C_BLACK"| "C_WHITE"Начало", string, "Да", "Нет");
}

dResponse:DlgDrivingSchoolBeginning(playerid)
{
    PDialogInfo[playerid][IsActive] = false;
    if(response)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Money] < DrivingSchoolLicensesParams[CLicenseInfo[playerid][SelectedCategory]][0])
            return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У Вас недостаточно средств для сдачи экзамена.");

        switch(CLicenseInfo[playerid][SelectedCategory])
        {
            case 0:
            {
                if(CLicenseInfo[playerid][IsDriver])
                    return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У Вас уже имеется лицензия на управления легковым транспортом.");

                SetPlayerVirtualWorld(playerid, playerid+1000);
                CLicenseInfo[playerid][VehicleID] = VehicleCreate(DrivingSchoolLicensesParams[CLicenseInfo[playerid][SelectedCategory]][1], DrivingSchoolPositionsSpawnVehs[CLicenseInfo[playerid][SelectedCategory]][0], DrivingSchoolPositionsSpawnVehs[CLicenseInfo[playerid][SelectedCategory]][1], DrivingSchoolPositionsSpawnVehs[CLicenseInfo[playerid][SelectedCategory]][2], DrivingSchoolPositionsSpawnVehs[CLicenseInfo[playerid][SelectedCategory]][3], random(255), random(255));
                if(CLicenseInfo[playerid][VehicleID] == 0)
                {
                    SetPlayerVirtualWorld(playerid, 0);
                    SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"При попытке начать экзамен произошла ошибка.");
                    return 1;
                }
                CLicenseInfo[playerid][IsStarted] = true;
                CLicenseInfo[playerid][CurrentCheckpoint] = 0;
                CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle] = true;
                SetVehicleVirtualWorld(CLicenseInfo[playerid][VehicleID], GetPlayerVirtualWorld(playerid));
                PutPlayerInVehicle(playerid, CLicenseInfo[playerid][VehicleID], 0);
                MoneyTake(playerid, DrivingSchoolLicensesParams[CLicenseInfo[playerid][SelectedCategory]][0]);
                CLicenseInfo[playerid][Checkpoint] = CreateDynamicCP(1157.7979, 1319.6343, 10.6952, 5.0, GetPlayerVirtualWorld(playerid), 0, playerid);
            }
        }
    }
    return 1;
}