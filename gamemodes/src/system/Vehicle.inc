/*      [ ИНИЦИАЛИЗАЦИЯ ТРАНСПОРТА ]      */
/*      [ INITIALIZING TRANSPORT ]      */
stock VehicleInit()
{
    VehicleCount = 0;
    return 1;
}

/*      [ СОЗДАНИЕ ТРАНСПОРТА ]      */
/*      [ CREATING A TRANSPORT ]      */
stock VehicleCreate(vehicleid, Float:x, Float:y, Float:z, Float:rotation, color1, color2, Float:fuel = 80.0, bool:isAdmin = false)
{
    new vehicle = CreateVehicle(vehicleid, x, y, z, rotation, color1, color2, 0);
    if(vehicle != 0)
    {
        new engine = 0, lights = 0, alarm = 0, doors = 0, bonnet = 0, boot = 0, objective = 0;
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] == 0)
            {
                VehicleCount++;
                VInfo[v][ID] = vehicle;
                VInfo[v][Model] = vehicleid;
                GetVehiclePos(vehicle, VInfo[v][SpawnPosition][0], VInfo[v][SpawnPosition][1], VInfo[v][SpawnPosition][2]);
                GetVehicleZAngle(vehicle, VInfo[v][SpawnRotation]);
                GetVehiclePos(vehicle, VInfo[v][CurrentPosition][0], VInfo[v][CurrentPosition][1], VInfo[v][CurrentPosition][2]);
                GetVehicleZAngle(vehicle, VInfo[v][CurrentRotation]);
                VInfo[v][Color1] = color1;
                VInfo[v][Color2] = color2;
                VInfo[v][Fuel] = fuel;
                VInfo[v][Health] = 1000.0;
                VInfo[v][Speed] = 0.0;
                VInfo[v][Mileage] = 0.0;
                if(isAdmin)
                    VInfo[v][Description] = CreateDynamic3DTextLabel("ADMIN CAR", C_F_RED, x, y, z+0.5, 10.0, _, vehicle, _, GetVehicleVirtualWorld(vehicle));
                VInfo[v][VirtualWorld] = GetVehicleVirtualWorld(vehicle);
                VInfo[v][IsUsed] = false;
                if(VehicleIsControlled(VInfo[v][Model]))
                    VInfo[v][IsEngine] = false;
                else
                    VInfo[v][IsEngine] = true;
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

/*      [ УДАЛЕНИЕ ТРАНСПОРТА ]      */
/*      [ DELETING A TRANSPORT ]      */
stock VehicleDestroy(vehicleid)
{
    for(new v = 0; v < MAX_VEHICLES; v++)
    {
        if(VInfo[v][ID] == vehicleid)
        {
            VehicleCount--;
            VInfo[v][ID] = 0;
            VInfo[v][Model] = 0;
            VInfo[v][SpawnPosition][0] = 0.0;
            VInfo[v][SpawnPosition][1] = 0.0;
            VInfo[v][SpawnPosition][2] = 0.0;
            VInfo[v][SpawnRotation] = 0.0;
            VInfo[v][CurrentPosition][0] = 0.0;
            VInfo[v][CurrentPosition][1] = 0.0;
            VInfo[v][CurrentPosition][2] = 0.0;
            VInfo[v][CurrentRotation] = 0.0;
            VInfo[v][Color1] = 0;
            VInfo[v][Color2] = 0;
            VInfo[v][Fuel] = 0.0;
            VInfo[v][Health] = 0.0;
            VInfo[v][Speed] = 0.0;
            VInfo[v][Mileage] = 0.0;
            if(IsValidDynamic3DTextLabel(VInfo[v][Description]))
                DestroyDynamic3DTextLabel(VInfo[v][Description]);
            VInfo[v][VirtualWorld] = 0;
            VInfo[v][IsUsed] = false;
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
        new id = VehicleGetArrayID(vehicleid);
        RepairVehicle(vehicleid);
        GetVehicleHealth(vehicleid, VInfo[id][Health]);
        return true;
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
        new id = VehicleGetArrayID(vehicleid);
        if(!VehicleIsControlled(VInfo[id][Model]))
            return false;
        VInfo[id][IsDoorsClosed] = !VInfo[id][IsDoorsClosed];
        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
        SetVehicleParamsEx(vehicleid, VInfo[id][IsEngine], VInfo[id][IsLights], alarm, VInfo[id][IsDoorsClosed], bonnet, boot, objective);
        for(new p = 0; p < MAX_PLAYERS; p++)
        {
            if(IsPlayerInAnyVehicle(p))
            {
                if(GetPlayerVehicleID(p) == vehicleid && GetPlayerVehicleSeat(p) == 0)
                {
                    TextDrawsUpdateForPlayer(p, PTDInfo[p][Speedometer][1], _, (VInfo[id][IsDoorsClosed] ? (C_F_RED) : (C_F_GREEN)));
                    break;
                }
            }
        }
        return true;
    }
    return false;
}

/*      [ ПОЛУЧИТЬ ЗНАЧЕНИЕ ДВЕРЕЙ У ТРАНСПОРТА ]      */
/*      [ GET THE VALUE OF TRANSPORT DOORS ]      */
stock VehicleGetDoorValue(vehicleid)
{
    new id = VehicleGetArrayID(vehicleid);
    return VInfo[id][IsDoorsClosed];
}

/*      [ ПОЛУЧИТЬ ЗНАЧЕНИЕ ДВИГАТЕЛЯ У ТРАНСПОРТА ]      */
/*      [ GET THE ENGINE VALUE OF A TRANSPORT ]      */
stock VehicleGetEngineValue(vehicleid)
{
    new id = VehicleGetArrayID(vehicleid);
    return VInfo[id][IsEngine];
}

/*      [ ПОЛУЧИТЬ ЗНАЧЕНИЕ ФАР У ТРАНСПОРТА ]      */
/*      [ GET THE VALUE OF THE TRANSPORT LIGHTS ]      */
stock VehicleGetLightsValue(vehicleid)
{
    new id = VehicleGetArrayID(vehicleid);
    return VInfo[id][IsLights];
}

/*      [ ПОЛУЧИТЬ СКОРОСТЬ ТРАНСПОРТА ]      */
/*      [ GET THE SPEED OF TRANSPORT ]      */
stock VehicleGetSpeedValue(vehicleid)
{
    new id = VehicleGetArrayID(vehicleid);
    return VInfo[id][Speed];
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
        new id = VehicleGetArrayID(vehicleid);
        VInfo[id][Color1] = color1;
        VInfo[id][Color2] = color2;
        ChangeVehicleColor(vehicleid, color1, color2);
        return true;
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

/*      [ ЗАРЕСПАВНИТЬ ТРАНСПОРТ ]      */
/*      [ TO RESTORE TRANSPORT ]      */
stock VehicleRespawn(bool:isUsed = false)
{
    new count = 0, needCount = VehicleCount;
    new engine = 0, lights = 0, alarm = 0, doors = 0, bonnet = 0, boot = 0, objective = 0;
    if(!isUsed)
        needCount = 0;
    for(new v = 0; v < MAX_VEHICLES; v++)
    {
        if(isUsed)
        {
            SetVehiclePos(VInfo[v][ID], VInfo[v][SpawnPosition][0], VInfo[v][SpawnPosition][1], VInfo[v][SpawnPosition][2]);
            SetVehicleZAngle(VInfo[v][ID], VInfo[v][SpawnRotation]);
            VInfo[v][IsUsed] = false;
            VInfo[v][IsEngine] = false;
            VInfo[v][IsLights] = false;
            VInfo[v][IsDoorsClosed] = true;
        }
        else
        {
            if(!VInfo[v][IsUsed])
            {
                SetVehiclePos(VInfo[v][ID], VInfo[v][SpawnPosition][0], VInfo[v][SpawnPosition][1], VInfo[v][SpawnPosition][2]);
                SetVehicleZAngle(VInfo[v][ID], VInfo[v][SpawnRotation]);
                VInfo[v][IsUsed] = false;
                VInfo[v][IsEngine] = false;
                VInfo[v][IsLights] = false;
                VInfo[v][IsDoorsClosed] = true;
                needCount++;
            }
        }
        GetVehicleParamsEx(VInfo[v][ID], engine, lights, alarm, doors, bonnet, boot, objective);
        SetVehicleParamsEx(VInfo[v][ID], VInfo[v][IsEngine], VInfo[v][IsLights], alarm, VInfo[v][IsDoorsClosed], bonnet, boot, objective);
        count++;
    }
    if(count == needCount)
        return true;
    else
        return false;
}

/*      [ ПРОВЕРЯЕМ ТРАНСПОРТ НА ВОЗМОЖНОСТЬ УПРАВЛЕНИЯ (двигатель, фары и другое) ]      */
/*      [ WE CHECK THE TRANSPORT FOR THE POSSIBILITY OF CONTROL (engine, headlights, etc.) ]      */
stock VehicleIsControlled(modelid)
{
    if(modelid == 509 || modelid == 481 || modelid == 510)
        return false;
    return true;
}

/*      [ ВЫВЕСТИ ВЕСЬ ТРАНСПОРТ ]      */
/*      [ WITHDRAW ALL TRANSPORT ]      */
stock VehiclePrintAllInfo(playerid)
{
    if(VehicleCount > 0)
    {
        printf("%s %s %s(%d) [%s:%s] запросил информацию о транспорте на сервере.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, PInfo[playerid][Nick], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
        ChatClear(playerid, _, 1);
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] != 0)
                SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"[%d] Model: "C_GRAY"%d "C_WHITE"| X: "C_GRAY"%f"C_WHITE", Y: "C_GRAY"%f"C_WHITE", Z: "C_GRAY"%f", VInfo[v][ID], VInfo[v][Model], VInfo[v][SpawnPosition][0], VInfo[v][SpawnPosition][1], VInfo[v][SpawnPosition][2]);
        }
        SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"На сервере %d единиц созданного транспорта.", VehicleCount);
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"На сервере нет ни одной единицы созданного транспорта.");
    return 0;
}

/*      [ ПОКАЗАТЬ СПИДОМЕТР ТРАНСПОРТА ДЛЯ ИГРОКА ]      */
/*      [ SHOW THE SPEEDOMETER OF THE TRANSPORT FOR THE PLAYER ]      */
stock VehicleShowSpeedometerForPlayer(playerid, arrayid)
{
    for(new speedometer = 0; speedometer < 6; speedometer++)
        PlayerTextDrawShow(playerid, PTDInfo[playerid][Speedometer][speedometer]);
    TextDrawsUpdateForPlayer(playerid, PTDInfo[playerid][Speedometer][1], _, (VInfo[arrayid][IsDoorsClosed] ? (C_F_RED) : (C_F_GREEN)));
    TextDrawsUpdateForPlayer(playerid, PTDInfo[playerid][Speedometer][2], _, (VInfo[arrayid][IsEngine] ? (C_F_GREEN) : (C_F_RED)));
    TextDrawsUpdateForPlayer(playerid, PTDInfo[playerid][Speedometer][3], _, (VInfo[arrayid][IsLights] ? (C_F_GREEN) : (C_F_RED)));
    return 1;
}

/*      [ СКРЫТЬ СПИДОМЕТР ТРАНСПОРТА ДЛЯ ИГРОКА ]      */
/*      [ HIDE THE TRANSPORT SPEEDOMETER FOR THE PLAYER ]      */
stock VehicleHideSpeedometerForPlayer(playerid)
{
    for(new speedometer = 0; speedometer < 6; speedometer++)
        PlayerTextDrawHide(playerid, PTDInfo[playerid][Speedometer][speedometer]);
    return 1;
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
                new id = VehicleGetArrayID(vehicleid);
                if(VehicleIsControlled(VInfo[id][Model]))
                {
                    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
                    switch(newkeys)
                    {
                        case KEY_ACTION: // L. CTRL
                        {
                            VInfo[id][IsEngine] = !VInfo[id][IsEngine];
                            SetVehicleParamsEx(vehicleid, VInfo[id][IsEngine], VInfo[id][IsLights], alarm, VInfo[id][IsDoorsClosed], bonnet, boot, objective);
                            TextDrawsUpdateForPlayer(playerid, PTDInfo[playerid][Speedometer][2], _, (VInfo[id][IsEngine] ? (C_F_GREEN) : (C_F_RED)));
                        }
                        
                        case KEY_FIRE: // L. ALT
                        {
                            VInfo[id][IsLights] = !VInfo[id][IsLights];
                            SetVehicleParamsEx(vehicleid, VInfo[id][IsEngine], VInfo[id][IsLights], alarm, VInfo[id][IsDoorsClosed], bonnet, boot, objective);
                            TextDrawsUpdateForPlayer(playerid, PTDInfo[playerid][Speedometer][3], _, (VInfo[id][IsLights] ? (C_F_GREEN) : (C_F_RED)));
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
        new id = VehicleGetArrayID(GetPlayerVehicleID(playerid));
        CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle] = true;
        VInfo[id][IsUsed] = true;
        if(VehicleIsControlled(VInfo[id][Model]))
            VehicleShowSpeedometerForPlayer(playerid, id);
    }
    else if(oldstate == PLAYER_STATE_DRIVER)
    {
        CInfo[playerid][PInfo[playerid][CharacterSelect]][IsVehicle] = false;
        VehicleHideSpeedometerForPlayer(playerid);
    }
    return 1;
}