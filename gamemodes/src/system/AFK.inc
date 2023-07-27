/*      [ ПРОВЕРКА НА AFK ]      */
/*      [ CHECKING FOR AFK ]      */
stock AFK_Check(playerid)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    
    // Проверяем на движение | Checking for movement
    if(PAFKInfo[playerid][Position][0] == x && PAFKInfo[playerid][Position][1] == y && PAFKInfo[playerid][Position][2] == z)
        PAFKInfo[playerid][Time]++;
    else
    {
        if(AFK_Exit(playerid))
            SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы вышли с AFK режима.");
    }

    // Сохраняем координаты | Saving the coordinates
    PAFKInfo[playerid][Position][0] = x;
    PAFKInfo[playerid][Position][1] = y;
    PAFKInfo[playerid][Position][2] = z;

    // Проверка на статус Администратора | Checking for Administrator status
    if(!CInfo[playerid][PInfo[playerid][CharacterSelect]][IsAdmin])
    {
        // Устанавливаем режим AFK игроку | Setting the AFK mode to the player
        if(PAFKInfo[playerid][Time] == MAX_AFK_TIME_SET)
        {
            if(AFK_Enter(playerid))
                SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Вы бездействовали %d секунд и встали в AFK режим.", MAX_AFK_TIME_SET);
        }
        else
        {
            new const time = PAFKInfo[playerid][Time] - MAX_AFK_TIME_SET;

            // Предупреждения | Warnings
            switch(time)
            {
                case (MAX_AFK_TIME_WARNING * 3): // Первое предупреждение | First warning
                    SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Вы будете кикнуты за AFK через %d секунд.", (MAX_AFK_TIME_WARNING * 6) - (MAX_AFK_TIME_WARNING * 3));

                case (MAX_AFK_TIME_WARNING * 5): // Первое предупреждение | First warning
                    SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Вы будете кикнуты за AFK через %d секунд.", (MAX_AFK_TIME_WARNING * 6) - (MAX_AFK_TIME_WARNING * 5));

                case (MAX_AFK_TIME_WARNING * 6): // Первое предупреждение | First warning
                    Kick_Player(playerid, _, "Долгое AFK");
            }
        }
    }
    return 1;
}

/*      [ ВХОД В AFK ]      */
/*      [ LOGIN TO AFK ]      */
stock AFK_Enter(playerid)
{
    if(!PAFKInfo[playerid][IsTrue])
    {
        PAFKInfo[playerid][IsTrue] = true;
        return true;
    }
    return false;
}

/*      [ ВЫХОД С AFK ]      */
/*      [ EXIT FROM AFK ]      */
stock AFK_Exit(playerid)
{
    if(PAFKInfo[playerid][IsTrue])
    {
        PAFKInfo[playerid][Time] = 0;
        PAFKInfo[playerid][IsTrue] = false;
        return true;
    }
    return false;
}