/*      [ УРОВНИ ДЛЯ АДМИНИСТРАЦИИ ]      */
/*      [ LEVELS FOR ADMINISTRATION ]      */
new const Admin_Level[MAX_ADMIN_LEVEL][] = {
    "Мл. Хелпер",
    "Хелпер",
    "Ст. Хелпер",
    "Мл. Администратор",
    "Администратор",
    "Ст. Администратор",
    "Следящий",
    "Куратор",
    "Заместитель",
    "Создатель"
};

/*      [ ========== ========== ========== ========== ========== ]      */

/*      [ КОМАНДЫ ]      */
/*      [ COMMANDS ]      */
cmd:alogin(playerid, params[]) // Войти под Администратором | Log in as an Administrator
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(sscanf(params, "d", params[0]))
            return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "alogin [пароль]");

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
            return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Вы уже авторизированы, как %s", Admin_Level[CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]-1]);

        if(strlen(params[0]) == 4)
        {
            if(params[0] == CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminPassword])
            {
                CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin] = true;
                SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы авторизовались, как %s.", Admin_Level[CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]-1]);
                printf("%s %s %s(%d) [%s] [%s] авторизовался под: %s.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], Admin_Level[CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]-1]);
            }
            else
            {
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Пароль неверный! Попробуйте ещё раз.");
                printf("%s %s %s(%d) [%s] [%s] попытался авторизоваться под: %s.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], Admin_Level[CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]-1]);
            }
        }
        else
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Пароль может состоять из 4-х символов.");
    }
    return 1;
}

cmd:alogout(playerid)
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin] = false;
            SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы покинули пост Администратора.");
            printf("%s %s %s(%d) [%s] [%s] вышел с роли: %s.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], Admin_Level[CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]-1]);
        }
        else
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Вы не авторизированы, как Администратор.");
    }
    return 1;
}

cmd:createvehicle(playerid, params[]) // Создать транспорт | Create a transport
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
            return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У Вас недостаточно прав для выполнения данной команды.");

        if(sscanf(params, "d", params[0]))
            return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "createvehicle [ID транспорта]");

        if(!(400 < params[0] < 611))
            return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный ID транспорта. Диапазон: от 400 до 611.");

        new Float:x, Float:y, Float:z, Float:rotation;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, rotation);
        new vehicle = CreateVehicle(params[0], x, y, z, rotation, random(255), random(255), 0);
        PutPlayerInVehicle(playerid, vehicle, 0);
        SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт был создан (ID: %d).", vehicle);
        printf("%s %s %s(%d) [%s] [%s] создал транспорт (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], vehicle);
    }
    return 1;
}
alias:createvehicle("createveh", "cvehicle", "cveh")

cmd:removevehicle(playerid, params[]) // Удалить транспорт | Delete Transport
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
            return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У Вас недостаточно прав для выполнения данной команды.");

        new seat = GetPlayerVehicleSeat(playerid);
        if(seat != 0)
            return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Для удаления транспорта нужно находится на водительском месте.");

        new vehicle = GetPlayerVehicleID(playerid);
        DestroyVehicle(vehicle);
        SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт был удалён (ID: %d).", vehicle);
        printf("%s %s %s(%d) [%s] [%s] удалил транспорт (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], vehicle);
    }
    return 1;
}
alias:removevehicle("removeveh", "rvehicle", "rveh")