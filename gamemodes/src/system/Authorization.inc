/*      [ ПОЗИЦИИ ПОЯВЛЕНИЯ (ПРИ СПАВНЕ / СПАВН НЕ НАЙДЕН) ]      */
/*      [ SPAWN POSITIONS (AT SPAWN / SPAWN NOT FOUND) ]      */
new const Float:PositionsSpawn[MAX_POSITIONS_SPAWN][4] = { // X, Y, Z, Rotation
    {1680.0198, 1447.8165, 10.7739, 270.7773} // LV
};

/*      [ ========== ========== ========== ========== ========== ]      */

/*      [ ПОЯВЛЕНИЕ ИГРОКА ПОСЛЕ АУТЕНТИФИКАЦИИ ]      */
/*      [ THE APPEARANCE OF THE PLAYER AFTER AUTHENTICATION ]      */
stock PlayerSpawnAfterAuthorization(playerid)
{
    static const licenses_query[] = "SELECT id,characterID,driver FROM licenses WHERE characterID = '%d' LIMIT 1";
    new licenses_mysql[sizeof(licenses_query)+(-2+11)];
    mysql_format(SInfo[MySQL], licenses_mysql, sizeof(licenses_mysql), licenses_query, CInfo[playerid][PInfo[playerid][CharacterSelect]][ID]);
    new Cache:licenses_cache = mysql_query(SInfo[MySQL], licenses_mysql, true);
    if(cache_num_rows())
        DataGetCharacterLicenseInfo(playerid);
    cache_delete(licenses_cache);
    TogglePlayerSpectating(playerid, false);
    ObjectsRemoveForPlayer(playerid);
    ObjectsCreateForPlayer(playerid);
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][0] == 0.0 && CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][1] == 0.0 && CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][2] == 0.0)
        SetSpawnInfo(playerid, 0, CInfo[playerid][PInfo[playerid][CharacterSelect]][Skin], PositionsSpawn[random(MAX_POSITIONS_SPAWN)][0], PositionsSpawn[random(MAX_POSITIONS_SPAWN)][1], PositionsSpawn[random(MAX_POSITIONS_SPAWN)][2], PositionsSpawn[random(MAX_POSITIONS_SPAWN)][3], 0, 0, 0, 0, 0, 0);
    else
        SetSpawnInfo(playerid, 0, CInfo[playerid][PInfo[playerid][CharacterSelect]][Skin], CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][0], CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][1], CInfo[playerid][PInfo[playerid][CharacterSelect]][Position][2], CInfo[playerid][PInfo[playerid][CharacterSelect]][Rotation], 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    SetCameraBehindPlayer(playerid);
    SetPlayerVirtualWorld(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][VirtualWorld]);
    SetPlayerInterior(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Interior]);
    SetPlayerHealth(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Health]);
    SetPlayerArmour(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][Armour]);
    SetPlayerColor(playerid, 0xFFFFFF22);
    TextDrawsCreateForPlayer(playerid);
    TextDrawShowForPlayer(playerid, TDInfo[Time]);
    PInfo[playerid][IsLogged] = true;
    CInfo[playerid][PInfo[playerid][CharacterSelect]][IsSpawning] = true;
    format(CInfo[playerid][PInfo[playerid][CharacterSelect]][FullName], MAX_PLAYER_NAME, "%s_%s", CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName]);
    SetPlayerName(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][FullName]);
    if(CInfo[playerid][PInfo[playerid][CharacterSelect]][Interior] != 0 || CInfo[playerid][PInfo[playerid][CharacterSelect]][VirtualWorld] != 0)
        FreezePlayer(playerid);
    printf("%s Игрок %s(%d) [%s] был заспавнен под персонажем %s %s", DEBUG_INFO, PInfo[playerid][Nick], playerid, PInfo[playerid][LastIP], CInfo[playerid][PInfo[playerid][CharacterSelect]][FirstName], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastName]);
    return 1;
}

/*      [ ========== ========== ========== ========== ========== ]      */

/*      [ ДИАЛОГОВЫЕ ОКНА ]      */
/*      [ DIALOG BOXES ]      */
dCreate:DlgAuthLogPassword(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cС возвращением на сервер "C_EMERALD""SERVER_NAME" "C_WHITE"| "C_EMERALD""SERVER_TYPE""C_WHITE".\n\
    "C_WHITE"\\cДля входа используйте свой пароль.\n\
    "C_WHITE"\\cВведите свой пароль в поле ввода и нажмите \"Играть\"\n\n";
    return Dialog_Open(playerid, Dialog:DlgAuthLogPassword, DIALOG_STYLE_PASSWORD, ""C_GRAY"Аутентификация "C_BLACK"| "C_WHITE"Авторизация", message, "Играть", "Выход");
}

dResponse:DlgAuthLogPassword(playerid)
{
    if(response)
    {
        if(!strlen(inputtext))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Все поля должны быть заполнены.");
            return Dialog_Show(playerid, Dialog:DlgAuthLogPassword);
        }

        if(!(MIN_PASSWORD_LEN < strlen(inputtext) < MAX_PASSWORD_LEN))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Пароль слишком длинный или короткий.");
            return Dialog_Show(playerid, Dialog:DlgAuthLogPassword);
        }

        new Regex:regex_password_check = Regex_New("^[a-zA-Z0-9]{1,}$");
        if(Regex_Check(inputtext, regex_password_check))
        {
            strmid(PInfo[playerid][Password], inputtext, 0, strlen(inputtext), MAX_PASSWORD_LEN);

            static const query[] = "SELECT id,email,donate,regIP,lastIP,regDate,lastDate FROM accounts WHERE nick = '%s' AND password = md5('%s') LIMIT 1";
            new mysql[sizeof(query)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PASSWORD_LEN)];
            mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, PInfo[playerid][Nick], PInfo[playerid][Password]);
            new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
            if(cache_num_rows())
            {
                DataGetPlayerInfo(playerid);
                PlayerCharacterShow(playerid);
                SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы авторизовались на сервере.");
                printf("%s Игрок %s(%d) [%s] авторизовался на сервере.", DEBUG_INFO, PInfo[playerid][Nick], playerid, PInfo[playerid][LastIP]);

                static const query_update[] = "UPDATE accounts SET lastIP = '%s', lastDate = '%s' WHERE nick = '%s' LIMIT 1";
                new mysql_update[sizeof(query_update)+(-2+15)+(-2+12)+(-2+MAX_PLAYER_NAME)];
                mysql_format(SInfo[MySQL], mysql_update, sizeof(mysql_update), query_update, PInfo[playerid][LastIP], PInfo[playerid][LastDate], PInfo[playerid][Nick]);
                mysql_query(SInfo[MySQL], mysql_update, false);
            }
            else
            {
                PInfo[playerid][AuthorizationCountTry]--;
                if(PInfo[playerid][AuthorizationCountTry] < 0)
                    KickPlayer(playerid, _, "Много попыток входа");
                else
                {
                    SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Пароль введён неверно. Осталось %d попыток.", PInfo[playerid][AuthorizationCountTry]);
                    Dialog_Show(playerid, Dialog:DlgAuthLogPassword);
                }
            }
            cache_delete(cache);
        }
        else
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Пароль может состоять из цифр/чисел и латинских символов.");
            Dialog_Show(playerid, Dialog:DlgAuthLogPassword);
        }
        Regex_Delete(regex_password_check);
    }
    else
        KickPlayer(playerid, "Сервер", "Выход");
    return 1;
}

dCreate:DlgAuthRegPassword(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cДобро пожаловать на сервер "C_EMERALD""SERVER_NAME" "C_WHITE"| "C_EMERALD""SERVER_TYPE""C_WHITE".\n\
    "C_WHITE"\\cНа данный логин не зарегистрировано ни одного аккаунта.\n\
    "C_WHITE"\\cДля регистрации, введите пароль в поле ввода и нажмите "C_EMERALD"\"Далее\""C_WHITE".\n\n";
    return Dialog_Open(playerid, Dialog:DlgAuthRegPassword, DIALOG_STYLE_INPUT, ""C_GRAY"Аутентификация "C_BLACK"| "C_WHITE"Регистрация", message, "Далее", "Выход");
}

dResponse:DlgAuthRegPassword(playerid)
{
    if(response)
    {
        if(!strlen(inputtext))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Все поля должны быть заполнены.");
            return Dialog_Show(playerid, Dialog:DlgAuthRegPassword);
        }

        if(!(MIN_PASSWORD_LEN < strlen(inputtext) < MAX_PASSWORD_LEN))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Пароль слишком длинный или короткий.");
            return Dialog_Show(playerid, Dialog:DlgAuthRegPassword);
        }

        new Regex:regex_password_check = Regex_New("^[a-zA-Z0-9]{1,}$");
        if(Regex_Check(inputtext, regex_password_check))
        {
            strmid(PInfo[playerid][Password], inputtext, 0, strlen(inputtext), MAX_PASSWORD_LEN);
            Dialog_Show(playerid, Dialog:DlgAuthRegEmail);
        }
        else
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Пароль может состоять из цифр/чисел и латинских символов.");
            Dialog_Show(playerid, Dialog:DlgAuthRegPassword);
        }
        Regex_Delete(regex_password_check);
    }
    else
        KickPlayer(playerid, "Сервер", "Выход");
    return 1;
}

dCreate:DlgAuthRegEmail(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cТеперь пройдём по безопасности.\n\
    "C_WHITE"\\cВведите свою электронную почту в поле ввода и нажмите "C_EMERALD"\"Далее\""C_WHITE".\n\n";
    return Dialog_Open(playerid, Dialog:DlgAuthRegEmail, DIALOG_STYLE_INPUT, ""C_GRAY"Аутентификация "C_BLACK"| "C_WHITE"Регистрация", message, "Далее", "");
}

dResponse:DlgAuthRegEmail(playerid)
{
    if(response)
    {
        if(!strlen(inputtext))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Все поля должны быть заполнены.");
            return Dialog_Show(playerid, Dialog:DlgAuthRegEmail);
        }

        if(!(MIN_EMAIL_LEN < strlen(inputtext) < MAX_EMAIL_LEN))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Адрес электронной почты слишком длинный или короткий.");
            return Dialog_Show(playerid, Dialog:DlgAuthRegEmail);
        }

        new Regex:regex_email_check = Regex_New("^[a-zA-Z0-9.-_]{1,43}@[a-zA-Z]{1,12}.[a-zA-Z]{1,8}$");
        if(Regex_Check(inputtext, regex_email_check))
        {
            strmid(PInfo[playerid][Email], inputtext, 0, strlen(inputtext), MAX_EMAIL_LEN);
            new year, month, day, hour, minute, second, date[15], time[15];
            getdate(year, month, day);
            gettime(hour, minute, second);
            format(date, sizeof(date), "%02d.%02d.%02d", year, month, day);
            format(time, sizeof(time), "%02d:%02d:%02d", hour, minute, second);
            format(PInfo[playerid][RegDate], 22, "%s / %s", date, time);
            format(PInfo[playerid][LastDate], 22, "%s / %s", date, time);
            GetPlayerIp(playerid, PInfo[playerid][RegIP], 16);
            GetPlayerIp(playerid, PInfo[playerid][LastIP], 16);

            static const query[] = "INSERT INTO accounts (nick,password,email,regIP,lastIP,regDate,lastDate) VALUES ('%s',md5('%s'),'%s','%s','%s','%s','%s')";
            new mysql[sizeof(query)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PASSWORD_LEN)+(-2+MAX_EMAIL_LEN)+(-2+16)+(-2+16)+(-2+22)+(-2+22)];
            mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, PInfo[playerid][Nick], PInfo[playerid][Password], PInfo[playerid][Email], PInfo[playerid][RegIP], PInfo[playerid][LastIP], PInfo[playerid][RegDate], PInfo[playerid][LastDate]);
            new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
            if(cache_num_results())
            {
                PlayerCharacterShow(playerid);
                SCM(playerid, -1, ""NOTIF_SUCCESS" "C_WHITE"Вы зарегистрировались на сервере.");
                printf("%s Игрок %s(%d) [%s] зарегистрировался на сервере.", DEBUG_INFO, PInfo[playerid][Nick], playerid, PInfo[playerid][RegIP]);
            }
            cache_delete(cache);
        }
        else
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Неверный адрес электронной почты.");
            Dialog_Show(playerid, Dialog:DlgAuthRegEmail);
        }
        Regex_Delete(regex_email_check);
    }
    return 1;
}