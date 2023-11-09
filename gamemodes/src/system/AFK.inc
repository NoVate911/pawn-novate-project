/*      [ ПРОВЕРКА НА AFK ]      */
/*      [ CHECKING FOR AFK ]      */
stock AFKCheck(playerid)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    
    // Проверяем на движение | Checking for movement
    if(PAFKInfo[playerid][Position][0] == x && PAFKInfo[playerid][Position][1] == y && PAFKInfo[playerid][Position][2] == z)
        PAFKInfo[playerid][Time]++;
    else
    {
        if(AFKExit(playerid))
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
            if(AFKEnter(playerid))
                SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Вы бездействовали %d минуту и встали в AFK режим.", MAX_AFK_TIME_SET / 60);
        }
        else
        {
            // Предупреждения | Warnings
            switch(PAFKInfo[playerid][Time] - MAX_AFK_TIME_SET)
            {
                case MAX_AFK_TIME_WARNING: // Первое предупреждение | First warning
                    SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Вы будете кикнуты за AFK через %d минуты.", ((MAX_AFK_TIME_WARNING * 5) - MAX_AFK_TIME_WARNING) / 60);

                case MAX_AFK_TIME_WARNING * 3: // Второе предупреждение | Second warning
                    SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Вы будете кикнуты за AFK через %d минуты.", ((MAX_AFK_TIME_WARNING * 5) - (MAX_AFK_TIME_WARNING * 3)) / 60);

                case MAX_AFK_TIME_WARNING * 4: // Третье предупреждение | Third warning
                    SCMf(playerid, -1, ""NOTIF_WARNING" "C_WHITE"Вы будете кикнуты за AFK через %d минуту.", ((MAX_AFK_TIME_WARNING * 5) - (MAX_AFK_TIME_WARNING * 4)) / 60);

                case MAX_AFK_TIME_WARNING * 5: // Четвёртое предупреждение |  warning
                    KickPlayer(playerid, _, "Долгое AFK");
            }
        }
    }
    return 1;
}

/*      [ ВХОД В AFK ]      */
/*      [ LOGIN TO AFK ]      */
stock AFKEnter(playerid)
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
stock AFKExit(playerid)
{
    if(PAFKInfo[playerid][IsTrue])
    {
        PAFKInfo[playerid][Time] = 0;
        PAFKInfo[playerid][IsTrue] = false;
        return true;
    }
    return false;
}