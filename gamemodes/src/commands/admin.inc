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
                printf("%s %s %s(%d) [%s:%s] авторизовался под: %s.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], Admin_Level[CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]-1]);
            }
            else
            {
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Пароль неверный! Попробуйте ещё раз.");
                printf("%s %s %s(%d) [%s:%s] попытался авторизоваться под: %s.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], Admin_Level[CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]-1]);
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
            printf("%s %s %s(%d) [%s:%s] вышел с роли: %s.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], Admin_Level[CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]-1]);
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

        if(sscanf(params, "dd", params[0], params[1]))
            return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "createvehicle [ID] [ID модели транспорта]");

        if(!PInfo[params[0]][IsLogged])
            return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

        if(!(400 < params[1] < 611))
            return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный ID транспорта. Диапазон: от 400 до 611.");

        if(IsPlayerInAnyVehicle(params[0]))
            return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_ISVEHICLE"");

        new Float:x, Float:y, Float:z, Float:rotation;
        GetPlayerPos(params[0], x, y, z);
        GetPlayerFacingAngle(params[0], rotation);
        new vehicle = Vehicle_Create(params[1], x+1.5, y, z, rotation, random(255), random(255));
        SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт был создан (ID: %d).", vehicle);
        printf("%s %s %s(%d) [%s:%s] создал транспорт (ID: %d) для %s %s(%d) [%s:%s].", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], vehicle, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][Login], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
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

        new vehicle = 0;
        if(sscanf(params, "d", params[0]))
        {
            if(!IsPlayerInAnyVehicle(playerid))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Вы не находитесь в транспорте.");
            
            new seat = GetPlayerVehicleSeat(playerid);
            if(seat != 0)
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Для удаления транспорта нужно находится на водительском месте.");
            
            vehicle = GetPlayerVehicleID(playerid);
        }
        else
        {
            if(!Vehicle_FindID(params[0]))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Транспорт с данным ID не найден.");
            
            vehicle = params[0];
        }

        if(Vehicle_Destroy(vehicle))
        {
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт был удалён (ID: %d).", vehicle);
            printf("%s %s %s(%d) [%s:%s] удалил транспорт (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], vehicle);
        }
        else
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"При удалении транспорта произошла ошибка.");
            printf("%s %s %s(%d) [%s:%s] попытался удалить транспорт.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
        }
    }
    return 1;
}
alias:removevehicle("removeveh", "rvehicle", "rveh")

cmd:vehiclelist(playerid) // Вывести весь созданный транспорт в чат | Output all the created transport to the chat
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
            return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У Вас недостаточно прав для выполнения данной команды.");

        Vehicle_PrintAllInfo(playerid);
    }
    return 1;
}
alias:vehiclelist("vehlist")

cmd:vehiclegoto(playerid, params[]) // Переместиться к транспорту | Move to transport
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
            return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У Вас недостаточно прав для выполнения данной команды.");

        if(sscanf(params, "dd", params[0], params[1]))
            return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "vehiclegoto [ID] [ID транспорта]");

        if(!PInfo[params[0]][IsLogged])
            return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

        if(Vehicle_FindID(params[1]))
        {
            new Float:x, Float:y, Float:z, Float:rotation, vw;
            GetVehiclePos(params[1], x, y, z);
            GetVehicleZAngle(params[1], rotation);
            vw = GetVehicleVirtualWorld(params[1]);
            SetPlayerPos(params[0], x, y, z+1.5);
            SetPlayerFacingAngle(params[0], rotation);
            SetPlayerVirtualWorld(params[0], vw);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы телепортировали %s %s(%d) к транспорту (ID: %d).", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            SCMf(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Вы были телепортированы к транспорту (ID: %d).", params[1]);
            printf("%s %s %s(%d) [%s:%s] телепортировал %s %s(%d) [%s:%s] к транспорту (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][Login], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP], params[1]);
        }
        else
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Транспорт с данным ID не найден.");
    }
    return 1;
}
alias:vehiclegoto("vehgoto")

cmd:vehiclegethere(playerid, params[]) // Переместить транспорт к игроку | Move the transport to the player
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
            return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У Вас недостаточно прав для выполнения данной команды.");

        if(sscanf(params, "dd", params[0], params[1]))
            return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "vehiclegethere [ID] [ID транспорта]");

        if(!PInfo[params[0]][IsLogged])
            return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

        if(Vehicle_FindID(params[1]))
        {
            new Float:x, Float:y, Float:z, Float:rotation, vw;
            GetPlayerPos(params[0], x, y, z);
            GetPlayerFacingAngle(params[0], rotation);
            vw = GetPlayerVirtualWorld(params[0]);
            SetVehiclePos(params[1], x, y, z+1.5);
            SetVehicleZAngle(params[1], rotation);
            SetVehicleVirtualWorld(params[1], vw);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы телепортировали транспорт (ID: %d) к %s %s(%d).", params[1], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
            SCMf(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт (ID: %d) был телепортирован к Вам.", params[1]);
            printf("%s %s %s(%d) [%s:%s] телепортировал транспорт (ID: %d) к %s %s(%d) [%s:%s].", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], params[1], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][Login], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
        }
        else
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Транспорт с данным ID не найден.");
    }
    return 1;
}
alias:vehiclegethere("vehgethere")