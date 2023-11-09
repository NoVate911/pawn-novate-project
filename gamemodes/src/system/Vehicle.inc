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
stock VehicleDestroy(vehicleid)
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

/*      [ ВЫВЕСТИ ВЕСЬ ТРАНСПОРТ ]      */
/*      [ WITHDRAW ALL TRANSPORT ]      */
stock VehiclePrintAllInfo(playerid)
{
    if(Vehicle_Count > 0)
    {
        printf("%s %s %s(%d) [%s:%s] запросил информацию о транспорте на сервере.", DEBUG_INFO, CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName], playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Login], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP]);
        ChatClear(playerid, _, 1);
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
                    case KEY_ACTION: // L. ALT
                    {
                        for(new v = 0; v < MAX_VEHICLES; v++)
                        {
                            if(VInfo[v][ID] == vehicleid)
                            {
                                VInfo[v][IsEngine] = !VInfo[v][IsEngine];
                                SetVehicleParamsEx(vehicleid, VInfo[v][IsEngine], VInfo[v][IsLights], alarm, VInfo[v][IsDoorsClosed], bonnet, boot, objective);
                            }
                        }
                    }
                    
                    case KEY_FIRE: // L. CTRL
                    {
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