cmd:adminlogin(playerid, params[]) // Войти под Администратором | Log in as an Administrator
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(sscanf(params, "d", params[0]))
            return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "adminlogin [пароль]");

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
            return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Вы уже авторизированы в системе.");

        if(strlen(params[0]) == 4)
        {
            if(params[0] == CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminPassword])
            {
                CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin] = true;
                new message_admin[70+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+2)];
                format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) [%d LVL] авторизовался в системе.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]);
                ChatSendMessageToAdmin(message_admin);
                SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы авторизовались в системе.");
                SCM(playerid, -1, ""NOTIF_INFO" "C_WHITE"Для помощи по командам Администрации - /adminhelp.");
                printf("%s Администратор %s %s(%d) [%s:%s] авторизовался в системе.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
            }
            else
            {
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Пароль неверный! Попробуйте ещё раз.");
                new message_admin[72+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
                format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) попытался авторизоваться в системе.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid);
                ChatSendMessageToAdmin(message_admin);
                printf("%s Администратор %s %s(%d) [%s:%s] попытался авторизоваться в системе.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
            }
        }
        else
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Пароль может состоять из 4-х символов.");
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:adminlogin("alogin")

cmd:adminlogout(playerid) // Выйти из системы | Log out of the system
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin] = false;
            new message_admin[50+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) покинул пост.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid);
            ChatSendMessageToAdmin(message_admin);
            SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы покинули пост Администратора.");
            printf("%s Администратор %s %s(%d) [%s:%s] покинул пост.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
        }
        else
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Вы не авторизированы, как Администратор.");
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:adminlogout("alogout")

cmd:createvehicle(playerid, params[]) // Создать транспорт | Create a transport
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "createvehicle [ID] [ID модели транспорта]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(!(400 <= params[1] <= 611))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный ID транспорта. Диапазон: от 400 до 611.");

            if(IsPlayerInAnyVehicle(params[0]))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_IN_VEHICLE"");

            new Float:x, Float:y, Float:z, Float:rotation;
            GetPlayerPos(params[0], x, y, z);
            GetPlayerFacingAngle(params[0], rotation);
            new vehicle = VehicleCreate(params[1], x, y+2.0, z, rotation, random(255), random(255));
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт был создан (ID: %d).", vehicle);
            new message_admin[63+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+4)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) создал транспорт (ID: %d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, vehicle);
            ChatSendMessageToAdmin(message_admin);
            printf("%s Администратор %s %s(%d) [%s:%s] создал транспорт (ID: %d) для %s %s(%d) [%s:%s].", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], vehicle, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:createvehicle("createveh", "cvehicle", "cveh")

cmd:removevehicle(playerid, params[]) // Удалить транспорт | Delete Transport
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

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
                if(!VehicleFindID(params[0]))
                    return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Транспорт с данным ID не найден.");
                
                vehicle = params[0];
            }

            if(VehicleDestroy(vehicle))
            {
                new message_admin[63+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+4)];
                format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) удалил транспорт (ID: %d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, vehicle);
                ChatSendMessageToAdmin(message_admin);
                SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт был удалён (ID: %d).", vehicle);
                printf("%s Администратор %s %s(%d) [%s:%s] удалил транспорт (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], vehicle);
            }
            else
            {
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"При удалении транспорта произошла ошибка.");
                printf("%s Администратор %s %s(%d) [%s:%s] попытался удалить транспорт.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
            }
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:removevehicle("removeveh", "rvehicle", "rveh")

cmd:fixvehicle(playerid, params[]) // Починить транспорт | Repair the transport
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            new vehicle = 0;
            if(sscanf(params, "d", params[0]))
            {
                if(!IsPlayerInAnyVehicle(playerid))
                    return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Вы не находитесь в транспорте.");
                
                new seat = GetPlayerVehicleSeat(playerid);
                if(seat != 0)
                    return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Для починки транспорта нужно находится на водительском месте.");
                
                vehicle = GetPlayerVehicleID(playerid);
            }
            else
            {
                if(!VehicleFindID(params[0]))
                    return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Транспорт с данным ID не найден.");
                
                vehicle = params[0];
            }

            if(VehicleRepair(vehicle))
            {
                new message_admin[64+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+4)];
                format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) починил транспорт (ID: %d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, vehicle);
                ChatSendMessageToAdmin(message_admin);
                SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт был починен (ID: %d).", vehicle);
                printf("%s Администратор %s %s(%d) [%s:%s] починил транспорт (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], vehicle);
            }
            else
            {
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"При починки транспорта произошла ошибка.");
                printf("%s Администратор %s %s(%d) [%s:%s] попытался починить транспорт.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
            }
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:fixvehicle("fveh")

cmd:vehiclelock(playerid, params[]) // Управление замком транспорта | Transport lock management
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            new vehicle = 0;
            if(sscanf(params, "d", params[0]))
            {
                if(!IsPlayerInAnyVehicle(playerid))
                    return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Вы не находитесь в транспорте.");
                
                new seat = GetPlayerVehicleSeat(playerid);
                if(seat != 0)
                    return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Для управления дверьми транспорта нужно находится на водительском месте.");
                
                vehicle = GetPlayerVehicleID(playerid);
            }
            else
            {
                if(!VehicleFindID(params[0]))
                    return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Транспорт с данным ID не найден.");
                
                vehicle = params[0];
            }

            if(VehicleDoorManagement(vehicle))
            {
                new message_admin[66+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+6)+(-2+4)];
                format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) %s двери транспорта (ID: %d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, (VehicleGetDoorValue(vehicle)) ? ("закрыт") : ("открыт"), vehicle);
                ChatSendMessageToAdmin(message_admin);
                SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт был %s (ID: %d).", (VehicleGetDoorValue(vehicle)) ? ("закрыт") : ("открыт"), vehicle);
                printf("%s Администратор %s %s(%d) [%s:%s] %s транспорт (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], (VehicleGetDoorValue(vehicle)) ? ("закрыт") : ("открыт"), vehicle);
            }
            else
            {
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"При управлением дверьми транспорта произошла ошибка.");
                printf("%s Администратор %s %s(%d) [%s:%s] попытался открыть/закрыть транспорт.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
            }
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:vehiclelock("vehlock","vlock")

cmd:vehiclecolor(playerid, params[]) // Смена цвета транспорта | Changing the color of transport
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "ddd", params[0], params[1], params[2]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "vehiclecolor [ID транспорта] [ID цвета] [ID цвета]");

            if(!(0 <= params[1] <= 255) || !(0 <= params[2] <= 255))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный ID цвета. Диапазон: от 0 до 255.");

            new vehicle = params[0];
            if(VehicleFindID(vehicle))
            {
                if(VehicleSetColor(vehicle, params[1], params[2]))
                {
                    new message_admin[67+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+4)];
                    format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) перекрасил транспорт (ID: %d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, vehicle);
                    ChatSendMessageToAdmin(message_admin);
                    SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт был перекрашен (ID: %d).", vehicle);
                    printf("%s Администратор %s %s(%d) [%s:%s] перекрасил транспорт (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], vehicle);
                }
                else
                {
                    SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"При перекраске транспорта произошла ошибка.");
                    printf("%s Администратор %s %s(%d) [%s:%s] попытался перекрасить транспорт.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
                }
            }
            else
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Транспорт с данным ID не найден.");
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:vehiclecolor("vehcolor", "vcolor")

cmd:vehiclelist(playerid) // Вывести весь созданный транспорт в чат | Output all the created transport to the chat
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            VehiclePrintAllInfo(playerid);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:vehiclelist("vehlist")

cmd:vehiclegoto(playerid, params[]) // Переместиться к транспорту | Move to transport
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "vehiclegoto [ID] [ID транспорта]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(VehicleFindID(params[1]))
            {
                new Float:x, Float:y, Float:z, Float:rotation, vw;
                GetVehiclePos(params[1], x, y, z);
                GetVehicleZAngle(params[1], rotation);
                vw = GetVehicleVirtualWorld(params[1]);
                SetPlayerPos(params[0], x, y, z+1.5);
                SetPlayerFacingAngle(params[0], rotation);
                SetPlayerVirtualWorld(params[0], vw);
                new message_admin[84+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+4)];
                format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) телепортировал %s %s(%d) к транспорту (ID: %d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
                ChatSendMessageToAdmin(message_admin);
                SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы телепортировали %s %s(%d) к транспорту (ID: %d).", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
                SCMf(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Вы были телепортированы к транспорту (ID: %d).", params[1]);
                printf("%s Администратор %s %s(%d) [%s:%s] телепортировал %s %s(%d) [%s:%s] к транспорту (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP], params[1]);
            }
            else
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Транспорт с данным ID не найден.");
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:vehiclegoto("vehgoto")

cmd:vehiclegethere(playerid, params[]) // Переместить транспорт к игроку | Move the transport to the player
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "vehiclegethere [ID] [ID транспорта]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(VehicleFindID(params[1]))
            {
                new Float:x, Float:y, Float:z, Float:rotation, vw;
                GetPlayerPos(params[0], x, y, z);
                GetPlayerFacingAngle(params[0], rotation);
                vw = GetPlayerVirtualWorld(params[0]);
                SetVehiclePos(params[1], x, y, z+1.5);
                SetVehicleZAngle(params[1], rotation);
                SetVehicleVirtualWorld(params[1], vw);
                new message_admin[83+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
                format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) телепортировал транспорт (ID: %d) к %s %s(%d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, params[1], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
                ChatSendMessageToAdmin(message_admin);
                SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы телепортировали транспорт (ID: %d) к %s %s(%d).", params[1], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
                SCMf(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Транспорт (ID: %d) был телепортирован к Вам.", params[1]);
                printf("%s Администратор %s %s(%d) [%s:%s] телепортировал транспорт (ID: %d) к %s %s(%d) [%s:%s].", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], params[1], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
            }
            else
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Транспорт с данным ID не найден.");
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:vehiclegethere("vehgethere")

cmd:clearchat(playerid)
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            ChatClear(playerid, true);
            new message_admin[49+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) очистил чат.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid);
            ChatSendMessageToAdmin(message_admin);
            SCMTA(-1, ""NOTIF_WARNING" "C_WHITE"Чат был очищен Администратором. Приятной игры!");
            printf("%s Администратор %s %s(%d) [%s:%s] очистил глобальный чат.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:hp(playerid, params[]) // Выдать игроку здоровье | Give the player health
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "hp [ID] [Количество]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(!(10 <= params[1] <= 100))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Уровень здоровья не может быть меньше 10 и выше 100 единиц.");

            SetPlayerHealth(params[0], float(params[1]));
            new message_admin[79+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+3)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) установил здоровье %s %s(%d) на %d единиц.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            ChatSendMessageToAdmin(message_admin);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы установили %s %s(%d) здоровье на %d единиц.", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            SCMf(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Администратор установил уровень здоровья на %d единиц.", params[1]);
            printf("%s Администратор %s %s(%d) [%s:%s] установил %d единиц здоровья для %s %s(%d) [%s:%s].", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], params[1], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:armour(playerid, params[]) // Выдать игроку броню | Give the player armour
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "armour [ID] [Количество]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(!(0 <= params[1] <= 100))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Уровень брони не может быть меньше 0 и выше 100 единиц.");

            SetPlayerArmour(params[0], float(params[1]));
            new message_admin[76+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+3)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) установил броню %s %s(%d) на %d единиц.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            ChatSendMessageToAdmin(message_admin);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы установили %s %s(%d) броню на %d единиц.", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            SCMf(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Администратор установил уровень брони на %d единиц.", params[1]);
            printf("%s Администратор %s %s(%d) [%s:%s] установил %d единиц брони для %s %s(%d) [%s:%s].", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], params[1], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:settime(playerid, params[]) // Установить время | Set the time
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "settime [Час] [Минута]");

            if(!(0 <= params[0] <= 23))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверно указаны часы. Диапазон: от 0 до 23.");

            if(!(0 <= params[1] <= 59))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверно указаны минуты. Диапазон: от 0 до 59.");
        
            TimeSet(true, params[0], params[1]);
            TInfo[IsChanged] = true;
            new message_admin[66+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+2)+(-2+2)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) установил время на %02d:%02d.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, params[0], params[1]);
            ChatSendMessageToAdmin(message_admin);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы изменили время суток на %02d:%02d", params[0], params[1]);
            printf("%s Администратор %s %s(%d) [%s:%s] изменил время суток на %02d:%02d", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], params[0], params[1]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:resettime(playerid) // Восстановить время | Restore time
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");
        
            TimeSet();
            TInfo[IsChanged] = false;
            new message_admin[55+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) восстановил время.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid);
            ChatSendMessageToAdmin(message_admin);
            SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы восстановили время суток.");
            printf("%s Администратор %s %s(%d) [%s:%s] восстановил время суток.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:setadmin(playerid, params[]) // Выдать игроку права Администратора | Grant the player Administrator rights
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 6)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "d", params[0]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "setadmin [ID]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] == 0)
            {
                CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] = 1;
                CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminPassword] = 1234;
                new message_admin[74+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
                format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) выдал %s %s(%d) права Администратора.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
                ChatSendMessageToAdmin(message_admin);
                SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы выдали %s %s(%d) права Администратора.", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
                SCM(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Вам были выданы права Администратора.");
                SCM(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Стандартный пароль установлен на "C_GREEN"\"1234\""C_WHITE". Для смены обратитесь к старшему Администратору.");
                printf("%s Администратор %s %s(%d) [%s:%s] выдал %s %s(%d) [%s:%s] права Администратора.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
            }
            else
            {
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У данного игрока уже есть права Администратора.");
                printf("%s Администратор %s %s(%d) [%s:%s] попытался выдать %s %s(%d) [%s:%s] права Администратора.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
            }
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:takeadmin(playerid, params[]) // Забрать права Администратора у игрока | Take away the Administrator rights from the player
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 6)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "d", params[0]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "takeadmin [ID]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] == playerid)
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_ME"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] > 0)
            {
                CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] = 0;
                new message_admin[77+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
                format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) забрал у %s %s(%d) права Администратора.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
                ChatSendMessageToAdmin(message_admin);
                SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы забрали у %s %s(%d) права Администратора.", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
                printf("%s Администратор %s %s(%d) [%s:%s] забрал у %s %s(%d) [%s:%s] права Администратора.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
                KickPlayer(params[0], CInfo[playerid][PInfo[playerid][CharacterSelect]][FullName], "Снятие с Администратора");
            }
            else
            {
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У данного игрока и так нет прав Администратора.");
                printf("%s Администратор %s %s(%d) [%s:%s] попытался забрать у %s %s(%d) [%s:%s] права Администратора.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
            }
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:kick(playerid, params[]) // Кикнуть игрока с сервера | Kick a player from the server
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 2)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "ds[48]", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "kick [ID] (причина)");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] == playerid)
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_ME"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            new message[45+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME*2)];
            format(message, sizeof(message), ""C_RED"Администратор %s %s кикнул %s %s. Причина: %s", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[1]);
            ChatSendGlobalMessage(message);
            printf("%s Администратор %s %s(%d) [%s:%s] кикнул %s %s(%d) [%s:%s]. Причина: %s", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP], params[1]);
            KickPlayer(params[0], CInfo[playerid][PInfo[playerid][CharacterSelect]][FullName], params[1]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:setskin(playerid, params[]) // Выдать постоянный скин игроку | Give a permanent skin to the player
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "setskin [ID] [ID скина]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(!(0 <= params[1] <= 311))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный ID скина. Диапазон: от 0 до 311.");

            if(GetPlayerSkin(params[0]) == params[1])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У этого персонажа и так данный скин.");

            CInfo[params[0]][PInfo[params[0]][CharacterSelect]][Skin] = params[1];
            SetPlayerSkin(params[0], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][Skin]);
            new message_admin[82+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+3)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) установил %s %s(%d) постоянный скин (ID: %d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][Skin]);
            ChatSendMessageToAdmin(message_admin);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы установили %s %s(%d) постоянный скин (ID: %d).", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][Skin]);
            printf("%s Администратор %s %s(%d) [%s:%s] установил %s %s(%d) [%s:%s] постоянный скин (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][Skin]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:settempskin(playerid, params[]) // Выдать временный скин игроку | Give a temporary skin to the player
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "settempskin [ID] [ID скина]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(!(0 <= params[1] <= 311))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный ID скина. Диапазон: от 0 до 311.");

            if(GetPlayerSkin(params[0]) == params[1])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"У этого персонажа и так данный скин.");

            SetPlayerSkin(params[0], params[1]);
            new message_admin[81+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+3)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) установил %s %s(%d) временный скин (ID: %d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            ChatSendMessageToAdmin(message_admin);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы установили %s %s(%d) временный скин (ID: %d).", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            printf("%s Администратор %s %s(%d) [%s:%s] установил %s %s(%d) [%s:%s] временный скин (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP], params[1]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:payday(playerid) // Запустить зарплату (PayDay) | Launch Salary (PayDay)
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 5)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            PayDayLaunch();
            new message_admin[53+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) запустил PayDay.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid);
            ChatSendMessageToAdmin(message_admin);
            printf("%s Администратор %s %s(%d) [%s:%s] запустил PayDay.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:goto(playerid, params[]) // Телепортироваться к игроку | Teleport to the player
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "d", params[0]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "goto [ID]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] == playerid)
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_ME"");

            new Float:x, Float:y, Float:z, Float:a, interior, vw;
            GetPlayerPos(params[0], x, y, z);
            GetPlayerFacingAngle(params[0], a);
            interior = GetPlayerInterior(params[0]);
            vw = GetPlayerVirtualWorld(params[0]);
            SetPlayerPos(playerid, x+1.0, y, z);
            SetPlayerFacingAngle(playerid, a);
            SetPlayerInterior(playerid, interior);
            SetPlayerVirtualWorld(playerid, vw);
            new message_admin[66+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) телепортировался к %s %s(%d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
            ChatSendMessageToAdmin(message_admin);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы телепортировались к %s %s(%d).", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
            printf("%s Администратор %s %s(%d) [%s:%s] телепортировался к %s %s(%d) [%s:%s].", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:gethere(playerid, params[]) // Телепортировать игрока к себе | Teleport the player to yourself
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "d", params[0]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "gethere [ID]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] == playerid)
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_ME"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(IsPlayerInAnyVehicle(params[0]))
            {
                if(GetPlayerVehicleSeat(playerid) == 0)
                    return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_IN_VEHICLE"");
            }

            new Float:x, Float:y, Float:z, Float:a, interior, vw;
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);
            interior = GetPlayerInterior(playerid);
            vw = GetPlayerVirtualWorld(playerid);
            SetPlayerPos(params[0], x+1.0, y, z);
            SetPlayerFacingAngle(params[0], a);
            SetPlayerInterior(params[0], interior);
            SetPlayerVirtualWorld(params[0], vw);
            new message_admin[69+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) телепортировал %s %s(%d) к себе.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
            ChatSendMessageToAdmin(message_admin);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы телепортировали %s %s(%d) к себе.", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
            printf("%s Администратор %s %s(%d) [%s:%s] телепортировал %s %s(%d) [%s:%s] к себе.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:spec(playerid, params[]) // Следить за игроком | Follow the player
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 2)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "d", params[0]))
            {
                if(PAdminSpectateInfo[playerid][IsToggle])
                {
                    PAdminSpectateInfo[playerid][IsToggle] = false;
                    TogglePlayerSpectating(playerid, false);
                    SpawnPlayer(playerid);
                    SetPlayerPos(playerid, PAdminSpectateInfo[playerid][Position][0], PAdminSpectateInfo[playerid][Position][1], PAdminSpectateInfo[playerid][Position][2]+1.0);
                    SetPlayerFacingAngle(playerid, PAdminSpectateInfo[playerid][Rotation]);
                    return SetCameraBehindPlayer(playerid);
                }

                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "spec [ID]");
            }

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] == playerid)
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_ME"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            new interior, vw;
            interior = GetPlayerInterior(params[0]);
            vw = GetPlayerVirtualWorld(params[0]);
            if(!PAdminSpectateInfo[playerid][IsToggle])
            {
                GetPlayerPos(playerid, PAdminSpectateInfo[playerid][Position][0], PAdminSpectateInfo[playerid][Position][1], PAdminSpectateInfo[playerid][Position][2]);
                GetPlayerFacingAngle(playerid, PAdminSpectateInfo[playerid][Rotation]);
            }
            TogglePlayerSpectating(playerid, true);
            SetPlayerInterior(playerid, interior);
            SetPlayerVirtualWorld(playerid, vw);
            if(IsPlayerInAnyVehicle(params[0]))
            {
                new vehicle;
                vehicle = GetPlayerVehicleID(params[0]);
                if(VehicleFindID(vehicle))
                    PlayerSpectateVehicle(playerid, vehicle);
            }
            else
                PlayerSpectatePlayer(playerid, params[0]);
            PAdminSpectateInfo[playerid][IsToggle] = true;
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:spec("sp")

cmd:tpcoord(playerid, params[0]) // Телепорт по координатам | Teleport by coordinates
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 2)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            new Float:x, Float:y, Float:z;
            if(sscanf(params, "fff", x, y, z))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "tpcoord {X} {Y} {Z}");

            SetPlayerPos(playerid, x, y, z);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы телепортировались по координатам (%.2f, %.2f, %.2f).", x, y, z);
            printf("%s Администратор %s %s(%d) [%s:%s] телепортировался по координатам: %.2f, %.2f, %.2f.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], x, y, z);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:tpcoord("tpc")

cmd:setinterior(playerid, params[]) // Установить интерьер | Install the interior
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 2)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "setinterior [ID] [INTERIOR]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(!(0 <= params[1] <= 256))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный интерьер. Диапазон: от 0 до 256.");

            SetPlayerInterior(params[0], params[1]);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы переместили %s %s(%d) в %d интерьер.", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            SCMf(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Администратор переместил Вас в %d интерьер.", params[1]);
            printf("%s Администратор %s %s(%d) [%s:%s] переместил %s %s(%d) [%s:%s] в %d интерьер.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP], params[1]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:setinterior("setint")

cmd:resetinterior(playerid, params[]) // Восстановить интерьер | To restore the interior
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 2)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "d", params[0]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "resetinterior [ID]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            SetPlayerInterior(params[0], 0);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы восстановили %s %s(%d) интерьер.", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
            SCM(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Администратор восстановил Ваш интерьер.");
            printf("%s Администратор %s %s(%d) [%s:%s] восстановил %s %s(%d) [%s:%s] интерьер.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:resetinterior("resetint")

cmd:setvirtualworld(playerid, params[]) // Установить виртуальный мир | Set up a virtual world
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 2)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "setvirtualworld [ID] [VIRTUAL WORLD]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(!(0 <= params[1] <= 2147483647))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный виртуальный мир. Диапазон: от 0 до 2147483647.");

            SetPlayerVirtualWorld(params[0], params[1]);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы переместили %s %s(%d) в %d виртуальный мир.", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            SCMf(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Администратор переместил Вас в %d виртуальный мир.", params[1]);
            printf("%s Администратор %s %s(%d) [%s:%s] переместил %s %s(%d) [%s:%s] в %d виртуальный мир.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP], params[1]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:setvirtualworld("setvw")

cmd:resetvirtualworld(playerid, params[]) // Восстановить виртуальный мир | Restore the virtual world
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 2)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "d", params[0]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "resetvirtualworld [ID]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            SetPlayerVirtualWorld(params[0], 0);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы восстановили %s %s(%d) виртуальный мир.", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
            SCM(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Администратор восстановил Ваш виртуальный мир.");
            printf("%s Администратор %s %s(%d) [%s:%s] восстановил %s %s(%d) [%s:%s] виртуальный мир.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:resetvirtualworld("resetvw")

cmd:spawn(playerid, params[]) // Заспавнить игрока | Wake up the player
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 2)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "d", params[0]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "spawn [ID]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            SetPlayerPos(params[0], PositionsSpawn[random(MAX_POSITIONS_SPAWN)][0], PositionsSpawn[random(MAX_POSITIONS_SPAWN)][1], PositionsSpawn[random(MAX_POSITIONS_SPAWN)][2]);
            SetPlayerFacingAngle(params[0], PositionsSpawn[random(MAX_POSITIONS_SPAWN)][3]);
            SetCameraBehindPlayer(playerid);
            SetPlayerInterior(params[0], 0);
            SetPlayerVirtualWorld(params[0], 0);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы заспавнили %s %s(%d).", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
            SCM(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Вы были заспанены Администратором.");
            printf("%s Администратор %s %s(%d) [%s:%s] заспавнил %s %s(%d) [%s:%s].", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:freeze(playerid, params[]) // Заморозить игрока | Freeze the player
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 3)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "d", params[0]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "freeze [ID]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] == playerid)
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_ME"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            FreezePlayer(playerid, false);
            new message_admin[50+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+11)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) %s %s %s(%d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, (CInfo[params[0]][PInfo[params[0]][CharacterSelect]][IsFrozen] ? ("заморозил") : ("разморозил")), CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
            ChatSendMessageToAdmin(message_admin);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы %s %s %s(%d).", (CInfo[params[0]][PInfo[params[0]][CharacterSelect]][IsFrozen] ? ("заморозили") : ("разморозили")), CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0]);
            SCMf(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Вы были %s Администратором.", (CInfo[params[0]][PInfo[params[0]][CharacterSelect]][IsFrozen] ? ("заморожены") : ("разморожены")));
            printf("%s Администратор %s %s(%d) [%s:%s] %s %s %s(%d) [%s:%s].", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], (CInfo[params[0]][PInfo[params[0]][CharacterSelect]][IsFrozen] ? ("заморозил") : ("разморозил")), CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:adminchat(playerid, params[]) // Отправка сообщения в чат Администрации | Sending a message to the Administration chat
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(sscanf(params, "s[128]", params[0]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "adminchat (текст)");

            new message[128];
            if(strlen(params[0]) > 46)
            {
                new first[37+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+2)+(-2+47)], second[17+(-2+113)];
                strmid(message, params[0], 47, 128, 128);
                strdel(params[0], 47, 128);
                format(first, sizeof(first), ""C_LIGHTGRAY"%s %s(%d) [%d LVL]: %s..", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel], params[0]);
                ChatSendMessageToAdmin(first);
                format(second, sizeof(second), ""C_LIGHTGRAY"..%s", message);
                ChatSendMessageToAdmin(second, _, _, false);
            }
            else
            {
                format(message, sizeof(message), ""C_LIGHTGRAY"%s %s(%d) [%d LVL]: %s", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel], params[0]);
                ChatSendMessageToAdmin(message);
            }
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:adminchat("achat", "ac")

cmd:giveweapon(playerid, params[])
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "dd", params[0], params[1]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "giveweapon [ID] [WEAPON ID]");

            if(!PInfo[params[0]][IsLogged])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_FOUND"");

            if(params[0] != playerid && CInfo[params[0]][PInfo[params[0]][CharacterSelect]][AdminLevel] >= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel])
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_NOT_VALID"");

            if(!(1 <= params[1] <= 46))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный ID оружия. Диапазон: от 1 до 46.");

            if(!(1 <= params[1] <= 15))
                GivePlayerWeapon(params[0], params[1], 777);
            else
                GivePlayerWeapon(params[0], params[1], 1);
            new message_admin[69+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+2)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) выдал %s %s(%d) оружие (ID: %d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            ChatSendMessageToAdmin(message_admin);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы выдали %s %s(%d) оружие (ID: %d).", CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], params[1]);
            SCMf(params[0], -1, ""NOTIF_SUCCESS" "C_WHITE"Администратор выдал Вам оружие (ID: %d).", params[1]);
            printf("%s Администратор %s %s(%d) [%s:%s] выдал %s %s(%d) [%s:%s] оружие (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][FirstName], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastName], params[0], PInfo[params[0]][Nick], CInfo[params[0]][PInfo[params[0]][CharacterSelect]][LastIP], params[1]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:vehiclerespawnall(playerid)
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(VehicleCount > 0)
            {
                if(VehicleRespawn())
                {
                    new message_admin[74+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
                    format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) зареспавнил весь незанятый транспорт.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid);
                    ChatSendMessageToAdmin(message_admin);
                    SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы зареспавнили весь незанятый транспорт.");
                    printf("%s Администратор %s %s(%d) [%s:%s] зареспавнил весь незанятый транспорт.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
                }
                else
                    SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Ни один транспорт не был зареспавнен.");
            }
            else
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"На сервере нет ни одной единицы созданного транспорта.");
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:vehiclerespawnall("vehrespawnall", "vehicleresall", "vehresall")

cmd:adminhelp(playerid, params[])
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(PDialogInfo[playerid][IsActive])
                return 1;

            if(sscanf(params, "d", params[0]))
                Dialog_Show(playerid, Dialog:DlgAdminHelpList);
            else
            {
                if(!(MIN_ADMIN_LEVEL <= params[0] <= CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]))
                    return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный уровень Администратора. Диапазон: от %d до %d.", MIN_ADMIN_LEVEL, CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]);
                PDialogInfo[playerid][AdminHelpLevel] = params[0];
                Dialog_Show(playerid, Dialog:DlgAdminHelp);
            }
            PDialogInfo[playerid][IsActive] = true;
        }
        else
            SCM(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Авторизуйтесь в системе (/adminlogin) для просмотра доступных команд.");
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}
alias:adminhelp("ahelp")

cmd:setweather(playerid, params[])
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");

            if(sscanf(params, "d", params[0]))
                return SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE""COMMAND_INVALID"", "setweather [ID погоды]");

            if(!(0 <= params[0] <= 22))
                return SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверно указаны часы. Диапазон: от 0 до 22.");
        
            WeatherSet(true, params[0]);
            new message_admin[61+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)+(-2+2)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) изменил погоду (ID: %d).", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, params[0]);
            ChatSendMessageToAdmin(message_admin);
            SCMf(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы изменили погоду (ID: %d).", params[0]);
            printf("%s Администратор %s %s(%d) [%s:%s] изменил погоду (ID: %d).", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], params[0]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

cmd:resetweather(playerid)
{
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] > 0)
    {
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][DelaySendCommand] > 0)
            return 1;

        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
        {
            if(CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel] < 4)
                return SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE""PLAYER_MISSING_ADMIN_LEVEL"");
        
            WeatherSet(true, 0);
            new message_admin[56+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+4)];
            format(message_admin, sizeof(message_admin), ""C_LIGHTGRAY"Администратор %s %s(%d) восстановил погоду.", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid);
            ChatSendMessageToAdmin(message_admin);
            SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы восстановили погоду.");
            printf("%s Администратор %s %s(%d) [%s:%s] восстановил погоду.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
        }
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE""COMMAND_NOT_FOUND"");
    return 1;
}

/*      [ ========== ========== ========== ========== ========== ]      */

dCreate:DlgAdminHelpList(playerid)
{
    new level[25+(-2+2)], avaliableLevels[sizeof(level)*MAX_ADMIN_LEVEL];
    for(new i = 0; i < CInfo[playerid][PInfo[playerid][CharacterSelect]][AdminLevel]; i++)
    {
        format(level, sizeof(level), ""C_WHITE"%d уровень\n", i+1);
        strcat(avaliableLevels, level, sizeof(avaliableLevels));
    }
    static const message[] = "\
    "C_LIGHTGRAY"Выберите уровень:\n\
    %s";
    new string[sizeof(message)+(-2+sizeof(avaliableLevels))];
    format(string, sizeof(string), message, avaliableLevels);
    return Dialog_Open(playerid, Dialog:DlgAdminHelpList, DIALOG_STYLE_LIST, ""C_GRAY"Помощь "C_BLACK"| "C_WHITE"Команды Администрации", string, "Выбрать", "Закрыть");
}

dResponse:DlgAdminHelpList(playerid)
{
    if(response)
    {
        if(listitem == 0)
            return Dialog_Show(playerid, Dialog:DlgAdminHelpList);
        PDialogInfo[playerid][AdminHelpLevel] = listitem;
        Dialog_Show(playerid, Dialog:DlgAdminHelp);
    }
    else
        PDialogInfo[playerid][IsActive] = false;
    return 1;
}

dCreate:DlgAdminHelp(playerid)
{
    new header[58+(-2+2)];
    format(header, sizeof(header), ""C_GRAY"Помощь "C_BLACK"| "C_WHITE"Администратор %d уровня", PDialogInfo[playerid][AdminHelpLevel]);
    new avaliableCommands[643];
    switch(PDialogInfo[playerid][AdminHelpLevel])
    {
        case 1:
        {
            format(avaliableCommands, sizeof(avaliableCommands), "\
            /adminlogin - авторизация в системе.\n\
            /adminlogout - деавторизация в системе.\n\
            /adminhelp - просмотр доступных команд.");
        }
        case 2:
        {
            format(avaliableCommands, sizeof(avaliableCommands), "\
            /kick - кикнуть игрока.\n\
            /spec - следить за игроком.\n\
            /tpcoord - телепортироваться по координатам.\n\
            /setinterior - установить интерьер для игрока.\n\
            /resetinterior - восстановить интерьер игроку.\n\
            /setvirtualworld - установить виртуальный мир для игрока.\n\
            /resetvirtualworld - восстановить виртуальный мир игроку.\n\
            /spawn - заспавнить игрока.");
        }
        case 3:
        {
            format(avaliableCommands, sizeof(avaliableCommands), "\
            /createvehicle - создать транспорт для игрока.\n\
            /removevehicle - удалить транспорт.\n\
            /fixvehicle - починить транспорт.\n\
            /vehiclelock - открыть/закрыть транспорт.\n\
            /vehiclecolor - изменить цвет транспорта.\n\
            /vehiclelist - посмотреть весь заспавненный транспорт.\n\
            /vehiclegoto - телепортироваться к транспорту.\n\
            /vehiclegethere - телепортировать транспорт к себе.\n\
            /hp - установить здоровье игроку.\n\
            /armour - установить броню игроку.\n\
            /freeze - заморозить/разморозить игрока.");
        }
        case 4:
        {
            format(avaliableCommands, sizeof(avaliableCommands), "\
            /clearchat - очистить чат сервера.\n\
            /settime - установить время на сервере.\n\
            /resettime - восстановить время на сервере.\n\
            /setskin - установить постоянный скин игроку.\n\
            /settempskin - установить временный скин игроку.\n\
            /goto - телепортироваться к игроку.\n\
            /gethere - телепортировать игрока к себе.\n\
            /giveweapon - выдать оружие игроку.\n\
            /vehiclerespawnall - зареспавнить весь незанятый транспорт.\n\
            /setweather - установить погоду на сервере.\n\
            /resetweather - восстановить погоду на сервере.");
        }
        case 5:
        {
            format(avaliableCommands, sizeof(avaliableCommands), "\
            /payday - запустить внеплановую зарплату.");
        }
        case 6:
        {
            format(avaliableCommands, sizeof(avaliableCommands), "\
            /setadmin - выдать права Администратора игроку.\n\
            /takeadmin - забрать права Администратора у игрока.");
        }
        default: format(avaliableCommands, sizeof(avaliableCommands), "Для данного уровня Администратора не найдено ни одной команды.");
    }
    static const message[] = "\
    "C_WHITE"\n\\cДоступные команды:\n\n\
    "C_LIGHTGRAY"%s\n\n";
    new string[sizeof(message)+(-2+sizeof(avaliableCommands))];
    format(string, sizeof(string), message, avaliableCommands);
    return Dialog_Open(playerid, Dialog:DlgAdminHelp, DIALOG_STYLE_MSGBOX, header, string, "Закрыть", "Назад");
}

dResponse:DlgAdminHelp(playerid)
{
    if(response)
        PDialogInfo[playerid][IsActive] = false;
    else
        Dialog_Show(playerid, Dialog:DlgAdminHelpList);
    return 1;
}