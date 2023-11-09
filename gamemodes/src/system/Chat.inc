/*      [ ОЧИСТКА ЧАТА ]      */
/*      [ CLEARING THE CHAT ]      */
stock ChatClear(playerid, bool:global = false, count = 50)
{
    for(new i = 0; i < count; i++)
    {
        if(global)
            SCMTA(C_F_WHITE, " ");
        else
            SCM(playerid, C_F_WHITE, " ");
    }
    return 1;
}

/*      [ ОТПРАВКА СООБЩЕНИЙ В ЧАТ АДМИНИСТРАЦИИ ]      */
/*      [ SENDING MESSAGES TO THE ADMINISTRATION CHAT ]      */
stock ChatSendMessageToAdmin(message[], adminLevel = 0, bool:isAdmin = true)
{
    foreach(new i : Player)
    {
        if(PInfo[i][IsLogged])
        {
            if(isAdmin)
            {
                if(CInfo[i][PInfo[i][CharacterSelect]][IsAdmin])
                {
                    if(CInfo[i][PInfo[i][CharacterSelect]][AdminLevel] > adminLevel)
                        SCMf(i, -1, ""NOTIF_ADMIN" %s", message);
                }
            }
            else
            {
                if(!CInfo[i][PInfo[i][CharacterSelect]][IsAdmin])
                {
                    if(CInfo[i][PInfo[i][CharacterSelect]][AdminLevel] > adminLevel)
                        SCMf(i, -1, ""NOTIF_ADMIN" %s", message);
                }
            }
        }
    }
    return 1;
}

/*      [ ОТПРАВКА СООБЩЕНИЙ В ЧАТ ]      */
/*      [ SENDING MESSAGES TO THE CHAT ]      */
stock ChatSendMessage(playerid, Float:max_range, color, string[], Float:max_ratio = 1.6)
{
    new Float:pos_x, Float:pos_y, Float:pos_z, Float:range, Float:range_ratio, Float:range_with_ratio, clr_r, clr_g, clr_b, Float:color_r, Float:color_g, Float:color_b;

    if(!GetPlayerPos(playerid, pos_x, pos_y, pos_z))
        return 0;

    color_r = float(color >> 24 & 0xFF);
    color_g = float(color >> 16 & 0xFF);
    color_b = float(color >> 8 & 0xFF);
    range_with_ratio = max_range * max_ratio;

#if defined foreach
    foreach (new i : Player) {
#else
    for (new i = GetPlayerPoolSize(); i != -1; i--) {
#endif
        if (!IsPlayerStreamedIn(playerid, i)) {
            continue;
        }

        range = GetPlayerDistanceFromPoint(i, pos_x, pos_y, pos_z);
        if (range > max_range) {
            continue;
        }

        range_ratio = (range_with_ratio - range) / range_with_ratio;
        clr_r = floatround(range_ratio * color_r);
        clr_g = floatround(range_ratio * color_g);
        clr_b = floatround(range_ratio * color_b);

        SendClientMessage(i, (color & 0xFF) | (clr_b << 8) | (clr_g << 16) | (clr_r << 24), string);
    }

    SendClientMessage(playerid, color, string);
    return 1;
}