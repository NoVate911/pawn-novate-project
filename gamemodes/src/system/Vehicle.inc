/*      [ ИНИЦИАЛИЗАЦИЯ ТРАНСПОРТА ]      */
/*      [ INITIALIZING TRANSPORT ]      */
stock VehicleInit()
{
    Vehicle_Count = 0;
    return 1;
}

/*      [ СОЗДАНИЕ ТРАНСПОРТА ]      */
/*      [ CREATING A TRANSPORT ]      */
stock VehicleCreate(vehicleid, Float:x, Float:y, Float:z, Float:rotation, color1, color2, Float:fuel = 80.0, bool:isAdmin = false)
{
    new vehicle = CreateVehicle(vehicleid, x, y, z, rotation, color1, color2, 0);
    new vw = 0, engine = 0, lights = 0, alarm = 0, doors = 0, bonnet = 0, boot = 0, objective = 0;
    if(vehicle != 0)
    {
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] == 0)
            {
                Vehicle_Count++;
                VInfo[v][ID] = vehicle;
                VInfo[v][Model] = vehicleid;
                VInfo[v][SpawnPosition][0] = x;
                VInfo[v][SpawnPosition][1] = y;
                VInfo[v][SpawnPosition][2] = z;
                VInfo[v][SpawnRotation] = rotation;
                VInfo[v][Color1] = color1;
                VInfo[v][Color2] = color2;
                VInfo[v][Fuel] = fuel;
                VInfo[v][Health] = 1000.0;
                VInfo[v][Speed] = 0.0;
                VInfo[v][Mileage] = 0.0;
                vw = GetVehicleVirtualWorld(vehicle);
                if(isAdmin)
                    VInfo[v][Description] = CreateDynamic3DTextLabel("ADMIN CAR", C_F_RED, x, y, z+0.5, 10.0, _, vehicle, _, vw);
                VehicleCreateSpeedometer(v);
                VInfo[v][IsEngine] = false;
                VInfo[v][IsLights] = false;
                VInfo[v][IsDoorsClosed] = false;
                SetVehicleHealth(vehicle, VInfo[v][Health]);
                GetVehicleParamsEx(vehicle, engine, lights, alarm, doors, bonnet, boot, objective);
                SetVehicleParamsEx(vehicle, VInfo[v][IsEngine], VInfo[v][IsLights], alarm, VInfo[v][IsDoorsClosed], bonnet, boot, objective);
                return vehicle;
            }
        }
    }
    return 0;
}

/*      [ СОЗДАНИЕ СПИДОМЕТРА ДЛЯ ТРАНСПОРТА ]      */
/*      [ CREATING A SPEEDOMETER FOR TRANSPORT ]      */
stock VehicleCreateSpeedometer(id)
{
    VInfo[id][Speedometer][0] = TextDrawCreate(406.000000, 424.611083, "usebox");
    TextDrawLetterSize(VInfo[id][Speedometer][0], 0.000000, -10.456583);
    TextDrawTextSize(VInfo[id][Speedometer][0], 613.666625, 0.000000);
    TextDrawAlignment(VInfo[id][Speedometer][0], 1);
    TextDrawColor(VInfo[id][Speedometer][0], 0);
    TextDrawUseBox(VInfo[id][Speedometer][0], true);
    TextDrawBoxColor(VInfo[id][Speedometer][0], 136);
    TextDrawSetShadow(VInfo[id][Speedometer][0], 0);
    TextDrawSetOutline(VInfo[id][Speedometer][0], -22);
    TextDrawBackgroundColor(VInfo[id][Speedometer][0], -1);
    TextDrawFont(VInfo[id][Speedometer][0], 0);
    VInfo[id][Speedometer][1] = TextDrawCreate(445.333801, 338.903625, "DOORS");
    TextDrawLetterSize(VInfo[id][Speedometer][1], 0.400999, 1.400889);
    TextDrawAlignment(VInfo[id][Speedometer][1], 2);
    TextDrawColor(VInfo[id][Speedometer][1], C_F_GREEN);
    TextDrawSetShadow(VInfo[id][Speedometer][1], 0);
    TextDrawSetOutline(VInfo[id][Speedometer][1], 1);
    TextDrawBackgroundColor(VInfo[id][Speedometer][1], 51);
    TextDrawFont(VInfo[id][Speedometer][1], 3);
    TextDrawSetProportional(VInfo[id][Speedometer][1], 1);
    VInfo[id][Speedometer][2] = TextDrawCreate(507.333465, 339.318389, "ENGINE");
    TextDrawLetterSize(VInfo[id][Speedometer][2], 0.400000, 1.400889);
    TextDrawAlignment(VInfo[id][Speedometer][2], 2);
    TextDrawColor(VInfo[id][Speedometer][2], C_F_RED);
    TextDrawSetShadow(VInfo[id][Speedometer][2], 0);
    TextDrawSetOutline(VInfo[id][Speedometer][2], 1);
    TextDrawBackgroundColor(VInfo[id][Speedometer][2], 51);
    TextDrawFont(VInfo[id][Speedometer][2], 3);
    TextDrawSetProportional(VInfo[id][Speedometer][2], 1);
    VInfo[id][Speedometer][3] = TextDrawCreate(572.333251, 339.318420, "LIGHT");
    TextDrawLetterSize(VInfo[id][Speedometer][3], 0.400999, 1.400889);
    TextDrawAlignment(VInfo[id][Speedometer][3], 2);
    TextDrawColor(VInfo[id][Speedometer][3], C_F_RED);
    TextDrawSetShadow(VInfo[id][Speedometer][3], 0);
    TextDrawSetOutline(VInfo[id][Speedometer][3], 1);
    TextDrawBackgroundColor(VInfo[id][Speedometer][3], 51);
    TextDrawFont(VInfo[id][Speedometer][3], 3);
    TextDrawSetProportional(VInfo[id][Speedometer][3], 1);
    VInfo[id][Speedometer][4] = TextDrawCreate(507.666595, 369.185180, "999 KM/H");
    TextDrawLetterSize(VInfo[id][Speedometer][4], 0.600332, 1.600000);
    TextDrawAlignment(VInfo[id][Speedometer][4], 2);
    TextDrawColor(VInfo[id][Speedometer][4], -1);
    TextDrawSetShadow(VInfo[id][Speedometer][4], 0);
    TextDrawSetOutline(VInfo[id][Speedometer][4], 0);
    TextDrawBackgroundColor(VInfo[id][Speedometer][4], 51);
    TextDrawFont(VInfo[id][Speedometer][4], 3);
    TextDrawSetProportional(VInfo[id][Speedometer][4], 1);
    new string[7+(-2+8)];
    format(string, sizeof(string), "%.0f KM", VInfo[id][Mileage]);
    VInfo[id][Speedometer][5] = TextDrawCreate(414.666259, 401.955780, string);
    TextDrawLetterSize(VInfo[id][Speedometer][5], 0.400999, 1.400887);
    TextDrawAlignment(VInfo[id][Speedometer][5], 1);
    TextDrawColor(VInfo[id][Speedometer][5], -86);
    TextDrawSetShadow(VInfo[id][Speedometer][5], 0);
    TextDrawSetOutline(VInfo[id][Speedometer][5], 1);
    TextDrawBackgroundColor(VInfo[id][Speedometer][5], 51);
    TextDrawFont(VInfo[id][Speedometer][5], 3);
    TextDrawSetProportional(VInfo[id][Speedometer][5], 1);
    return 1;
}

/*      [ УДАЛЕНИЕ ТРАНСПОРТА ]      */
/*      [ DELETING A TRANSPORT ]      */
stock VehicleDestroy(vehicleid)
{
    for(new v = 0; v < MAX_VEHICLES; v++)
    {
        if(VInfo[v][ID] == vehicleid)
        {
            Vehicle_Count--;
            VInfo[v][ID] = 0;
            VInfo[v][Model] = 0;
            VInfo[v][SpawnPosition][0] = 0.0;
            VInfo[v][SpawnPosition][1] = 0.0;
            VInfo[v][SpawnPosition][2] = 0.0;
            VInfo[v][SpawnRotation] = 0.0;
            VInfo[v][Color1] = 0;
            VInfo[v][Color2] = 0;
            VInfo[v][Fuel] = 0.0;
            VInfo[v][Health] = 0.0;
            VInfo[v][Speed] = 0.0;
            VInfo[v][Mileage] = 0.0;
            if(IsValidDynamic3DTextLabel(VInfo[v][Description]))
                DestroyDynamic3DTextLabel(VInfo[v][Description]);
            for(new speedometer = 0; speedometer < 6; speedometer++)
                TextDrawDestroy(VInfo[v][Speedometer][speedometer]);
            VInfo[v][IsEngine] = false;
            VInfo[v][IsLights] = false;
            VInfo[v][IsDoorsClosed] = false;
            DestroyVehicle(vehicleid);
            return true;
        }
    }
    return false;
}

/*      [ ПОЧИНКА ТРАНСПОРТА ]      */
/*      [ REPAIR OF TRANSPORT ]      */
stock VehicleRepair(vehicleid)
{
    if(VehicleFindID(vehicleid))
    {
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] == vehicleid)
            {
                RepairVehicle(vehicleid);
                GetVehicleHealth(vehicleid, VInfo[v][Health]);
                return true;
            }
        }
    }
    return false;
}

/*      [ УПРАВЛЕНИЕ ДВЕРЬМИ ТРАНСПОРТА ]      */
/*      [ TRANSPORT DOOR MANAGEMENT ]      */
stock VehicleDoorManagement(vehicleid)
{
    if(VehicleFindID(vehicleid))
    {
        new engine = 0, lights = 0, alarm = 0, doors = 0, bonnet = 0, boot = 0, objective = 0;
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] == vehicleid)
            {
                VInfo[v][IsDoorsClosed] = !VInfo[v][IsDoorsClosed];
                GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
                SetVehicleParamsEx(vehicleid, engine, lights, alarm, VInfo[v][IsDoorsClosed], bonnet, boot, objective);
                TextDrawColor(VInfo[v][Speedometer][1], (VInfo[v][IsDoorsClosed] ? (C_F_RED) : (C_F_GREEN)));
                for(new p = 0; p < MAX_PLAYERS; p++)
                {
                    if(IsPlayerInAnyVehicle(p))
                    {
                        if(GetPlayerVehicleID(p) == vehicleid && GetPlayerVehicleSeat(p) == 0)
                        {
                            TextDrawsUpdateForServer(p, VInfo[v][Speedometer][1], _, (VInfo[v][IsDoorsClosed] ? (C_F_RED) : (C_F_GREEN)));
                            break;
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}

/*      [ ПОЛУЧИТЬ ЗНАЧЕНИЕ ДВЕРЕЙ У ТРАНСПОРТА ]      */
/*      [ GET THE VALUE OF TRANSPORT DOORS ]      */
stock VehicleGetDoorValue(vehicleid)
{
    if(VehicleFindID(vehicleid))
    {
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] == vehicleid)
            {
                return VInfo[v][IsDoorsClosed];
            }
        }
    }
    return false;
}

/*      [ ПОЛУЧИТЬ ЗНАЧЕНИЕ ДВИГАТЕЛЯ У ТРАНСПОРТА ]      */
/*      [ GET THE ENGINE VALUE OF A TRANSPORT ]      */
stock VehicleGetEngineValue(vehicleid)
{
    if(VehicleFindID(vehicleid))
    {
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] == vehicleid)
            {
                return VInfo[v][IsEngine];
            }
        }
    }
    return false;
}

/*      [ ПОЛУЧИТЬ ЗНАЧЕНИЕ ФАР У ТРАНСПОРТА ]      */
/*      [ GET THE VALUE OF THE TRANSPORT LIGHTS ]      */
stock VehicleGetLightsValue(vehicleid)
{
    if(VehicleFindID(vehicleid))
    {
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] == vehicleid)
            {
                return VInfo[v][IsLights];
            }
        }
    }
    return false;
}

/*      [ ПОЛУЧИТЬ СКОРОСТЬ ТРАНСПОРТА ]      */
/*      [ GET THE SPEED OF TRANSPORT ]      */
stock VehicleGetSpeedValue(vehicleid)
{
    if(VehicleFindID(vehicleid))
    {
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] == vehicleid)
            {
                return VInfo[v][Speed];
            }
        }
    }
    return 1;
}

/*      [ ВЫСЧИТАТЬ СКОРОСТЬ И ПРОБЕГ ТРАНСПОРТА ]      */
/*      [ CALCULATE THE SPEED AND MILEAGE OF THE TRANSPORT ]      */
stock VehicleCalculateSpeedValue(id)
{
    if(VInfo[id][ID] != 0)
    {
        new Float:velocity[3];
        GetVehicleVelocity(VInfo[id][ID], velocity[0], velocity[1], velocity[2]);
        VInfo[id][Speed] = floatsqroot(floatpower(floatabs(velocity[0]), 2.0) + floatpower(velocity[1], 2.0) + floatpower(velocity[2], 2.0)) * 100.3;
        new Float:mileage = (VInfo[id][Speed] / 8.6) / 300;
        if(VInfo[id][Speed] > 0.0)
        {
            if(mileage > 0.0)
                VInfo[id][Mileage] += mileage;
        }
        return true;
    }
    return false;
}

/*      [ СМЕНА ЦВЕТА ТРАНСПОРТА ]      */
/*      [ CHANGING THE COLOR OF TRANSPORT ]      */
stock VehicleSetColor(vehicleid, color1, color2)
{
    if(VehicleFindID(vehicleid))
    {
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] == vehicleid)
            {
                VInfo[v][Color1] = color1;
                VInfo[v][Color2] = color2;
                ChangeVehicleColor(vehicleid, color1, color2);
                return true;
            }
        }
    }
    return false;
}

/*      [ ПОИСК ТРАНСПОРТА ПО НОМЕРУ ]      */
/*      [ SEARCH FOR TRANSPORT BY NUMBER ]      */
stock VehicleFindID(vehicleid)
{
    for(new v = 0; v < MAX_VEHICLES; v++)
    {
        if(VInfo[v][ID] == vehicleid)
            return true;
    }
    return false;
}

/*      [ ПОЛУЧЕНИЕ НОМЕРА МАССИВА В КОТОРОМ ХРАНИТСЯ ТРАНСПОРТ ]      */
/*      [ GETTING THE NUMBER OF THE ARRAY WHERE THE TRANSPORT IS STORED ]      */
stock VehicleGetArrayID(vehicleid)
{
    for(new v = 0; v < MAX_VEHICLES; v++)
    {
        if(VInfo[v][ID] == vehicleid)
            return v;
    }
    return 0;
}

/*      [ ВЫВЕСТИ ВЕСЬ ТРАНСПОРТ ]      */
/*      [ WITHDRAW ALL TRANSPORT ]      */
stock VehiclePrintAllInfo(playerid)
{
    if(Vehicle_Count > 0)
    {
        printf("%s %s %s(%d) [%s:%s] запросил информацию о транспорте на сервере.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
        ChatClear(playerid, _, 1);
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] != 0)
                SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"[%d] Model: "C_GRAY"%d "C_WHITE"| X: "C_GRAY"%f"C_WHITE", Y: "C_GRAY"%f"C_WHITE", Z: "C_GRAY"%f", VInfo[v][ID], VInfo[v][Model], VInfo[v][SpawnPosition][0], VInfo[v][SpawnPosition][1], VInfo[v][SpawnPosition][2]);
        }
        SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"На сервере %d единиц созданного транспорта.", Vehicle_Count);
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"На сервере нет ни одной единицы созданного транспорта.");
    return 0;
}

/*      [ ПОКАЗАТЬ СПИДОМЕТР ТРАНСПОРТА ДЛЯ ИГРОКА ]      */
/*      [ SHOW THE SPEEDOMETER OF THE TRANSPORT FOR THE PLAYER ]      */
stock VehicleShowSpeedometerForPlayer(playerid, vehicleid)
{
    if(GetPlayerVehicleSeat(playerid) == 0)
    {
        new id = VehicleGetArrayID(vehicleid);
        for(new speedometer = 0; speedometer < 6; speedometer++)
            TextDrawShowForPlayer(playerid, VInfo[id][Speedometer][speedometer]);
        return true;
    }
    return false;
}

/*      [ СКРЫТЬ СПИДОМЕТР ТРАНСПОРТА ДЛЯ ИГРОКА ]      */
/*      [ HIDE THE TRANSPORT SPEEDOMETER FOR THE PLAYER ]      */
stock VehicleHideSpeedometerForPlayer(playerid, vehicleid)
{
    if(GetPlayerVehicleSeat(playerid) == 0)
    {
        new id = VehicleGetArrayID(vehicleid);
        for(new speedometer = 0; speedometer < 6; speedometer++)
            TextDrawHideForPlayer(playerid, VInfo[id][Speedometer][speedometer]);
        return true;
    }
    return false;
}

stock VehicleKeyStateChange(playerid, newkeys)
{
    if(IsPlayerInAnyVehicle(playerid))
    {
        new const vehicleid = GetPlayerVehicleID(playerid);
        new engine = 0, lights = 0, alarm = 0, doors = 0, bonnet = 0, boot = 0, objective = 0;
        if(GetPlayerVehicleSeat(playerid) == 0) // Водитель | Driver
        {
            if(VehicleFindID(vehicleid))
            {
                GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
                switch(newkeys)
                {
                    case KEY_ACTION: // L. CTRL
                    {
                        for(new v = 0; v < MAX_VEHICLES; v++)
                        {
                            if(VInfo[v][ID] == vehicleid)
                            {
                                VInfo[v][IsEngine] = !VInfo[v][IsEngine];
                                SetVehicleParamsEx(vehicleid, VInfo[v][IsEngine], VInfo[v][IsLights], alarm, VInfo[v][IsDoorsClosed], bonnet, boot, objective);
                                TextDrawsUpdateForServer(playerid, VInfo[v][Speedometer][2], _, (VInfo[v][IsEngine] ? (C_F_GREEN) : (C_F_RED)));
                            }
                        }
                    }
                    
                    case KEY_FIRE: // L. ALT
                    {
                        for(new v = 0; v < MAX_VEHICLES; v++)
                        {
                            if(VInfo[v][ID] == vehicleid)
                            {
                                VInfo[v][IsLights] = !VInfo[v][IsLights];
                                SetVehicleParamsEx(vehicleid, VInfo[v][IsEngine], VInfo[v][IsLights], alarm, VInfo[v][IsDoorsClosed], bonnet, boot, objective);
                                TextDrawsUpdateForServer(playerid, VInfo[v][Speedometer][3], _, (VInfo[v][IsLights] ? (C_F_GREEN) : (C_F_RED)));
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}

stock VehicleStateChange(playerid, newstate, oldstate)
{
    if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
    {
        CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle] = true;
        VehicleShowSpeedometerForPlayer(playerid, GetPlayerVehicleID(playerid));
    }
    return 1;
}