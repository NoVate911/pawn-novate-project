/*      [ ИНИЦИАЛИЗАЦИЯ ТРАНСПОРТА ]      */
/*      [ INITIALIZING TRANSPORT ]      */
stock Vehicle_Init()
{
    Vehicle_Count = 0;
    return 1;
}

/*      [ СОЗДАНИЕ ТРАНСПОРТА ]      */
/*      [ CREATING A TRANSPORT ]      */
stock Vehicle_Create(vehicleid, Float:x, Float:y, Float:z, Float:rotation, color1, color2, Float:fuel = 80.0, bool:isAdmin = false)
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
                VInfo[v][Position][0] = x;
                VInfo[v][Position][1] = y;
                VInfo[v][Position][2] = z;
                VInfo[v][Rotation] = rotation;
                VInfo[v][Color1] = color1;
                VInfo[v][Color2] = color2;
                VInfo[v][Fuel] = fuel;
                VInfo[v][Health] = 1000.0;
                vw = GetVehicleVirtualWorld(vehicle);
                if(isAdmin)
                    VInfo[v][Description] = CreateDynamic3DTextLabel("ADMIN CAR", C_F_RED, x, y, z+0.5, 10.0, _, vehicle, _, vw);
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

/*      [ УДАЛЕНИЕ ТРАНСПОРТА ]      */
/*      [ DELETING A TRANSPORT ]      */
stock Vehicle_Destroy(vehicleid)
{
    for(new v = 0; v < MAX_VEHICLES; v++)
    {
        if(VInfo[v][ID] == vehicleid)
        {
            Vehicle_Count--;
            VInfo[v][ID] = 0;
            VInfo[v][Model] = 0;
            VInfo[v][Position][0] = 0.0;
            VInfo[v][Position][1] = 0.0;
            VInfo[v][Position][2] = 0.0;
            VInfo[v][Rotation] = 0.0;
            VInfo[v][Color1] = 0;
            VInfo[v][Color2] = 0;
            VInfo[v][Fuel] = 0.0;
            VInfo[v][Health] = 0.0;
            if(IsValidDynamic3DTextLabel(VInfo[v][Description]))
                DestroyDynamic3DTextLabel(VInfo[v][Description]);
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
stock Vehicle_Repair(vehicleid)
{
    if(Vehicle_FindID(vehicleid))
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
stock Vehicle_DoorManagement(vehicleid)
{
    if(Vehicle_FindID(vehicleid))
    {
        new engine = 0, lights = 0, alarm = 0, doors = 0, bonnet = 0, boot = 0, objective = 0;
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] == vehicleid)
            {
                VInfo[v][IsDoorsClosed] = !VInfo[v][IsDoorsClosed];
                GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
                SetVehicleParamsEx(vehicleid, engine, lights, alarm, VInfo[v][IsDoorsClosed], bonnet, boot, objective);
                return true;
            }
        }
    }
    return false;
}

/*      [ ПОЛУЧИТЬ ЗНАЧЕНИЕ ДВЕРЕЙ У ТРАНСПОРТА ]      */
/*      [ GET THE VALUE OF TRANSPORT DOORS ]      */
stock Vehicle_GetDoorValue(vehicleid)
{
    if(Vehicle_FindID(vehicleid))
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

/*      [ СМЕНА ЦВЕТА ТРАНСПОРТА ]      */
/*      [ CHANGING THE COLOR OF TRANSPORT ]      */
stock Vehicle_SetColor(vehicleid, color1, color2)
{
    if(Vehicle_FindID(vehicleid))
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
stock Vehicle_FindID(vehicleid)
{
    for(new v = 0; v < MAX_VEHICLES; v++)
    {
        if(VInfo[v][ID] == vehicleid)
            return true;
    }
    return false;
}

/*      [ ВЫВЕСТИ ВЕСЬ ТРАНСПОРТ ]      */
/*      [ WITHDRAW ALL TRANSPORT ]      */
stock Vehicle_PrintAllInfo(playerid)
{
    if(Vehicle_Count > 0)
    {
        printf("%s %s %s(%d) [%s:%s] запросил информацию о транспорте на сервере.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
        Chat_Clear(playerid, _, 1);
        for(new v = 0; v < MAX_VEHICLES; v++)
        {
            if(VInfo[v][ID] != 0)
                SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"[%d] Model: "C_GRAY"%d "C_WHITE"| X: "C_GRAY"%f"C_WHITE", Y: "C_GRAY"%f"C_WHITE", Z: "C_GRAY"%f", VInfo[v][ID], VInfo[v][Model], VInfo[v][Position][0], VInfo[v][Position][1], VInfo[v][Position][2]);
        }
        SCMf(playerid, -1, ""NOTIF_INFO" "C_WHITE"На сервере %d единиц созданного транспорта.", Vehicle_Count);
    }
    else
        SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"На сервере нет ни одной единицы созданного транспорта.");
    return 0;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(IsPlayerNPC(playerid))
        return 1;

    if(PInfo[playerid][IsLogged])
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            new const vehicleid = GetPlayerVehicleID(playerid);
            new engine = 0, lights = 0, alarm = 0, doors = 0, bonnet = 0, boot = 0, objective = 0;
            if(GetPlayerVehicleSeat(playerid) == 0) // Водитель | Driver
            {
                if(newkeys == KEY_ACTION) // L.CTRL
                {
                    if(Vehicle_FindID(vehicleid))
                    {
                        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
                        for(new v = 0; v < MAX_VEHICLES; v++)
                        {
                            if(VInfo[v][ID] == vehicleid)
                            {
                                VInfo[v][IsEngine] = !VInfo[v][IsEngine];
                                SetVehicleParamsEx(vehicleid, VInfo[v][IsEngine], VInfo[v][IsLights], alarm, VInfo[v][IsDoorsClosed], bonnet, boot, objective);
                            }
                        }
                    }
                }
                else if(newkeys == KEY_FIRE) // L.ALT
                {
                    if(Vehicle_FindID(vehicleid))
                    {
                        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
                        for(new v = 0; v < MAX_VEHICLES; v++)
                        {
                            if(VInfo[v][ID] == vehicleid)
                            {
                                VInfo[v][IsLights] = !VInfo[v][IsLights];
                                SetVehicleParamsEx(vehicleid, VInfo[v][IsEngine], VInfo[v][IsLights], alarm, VInfo[v][IsDoorsClosed], bonnet, boot, objective);
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}