/*      [ СКИНЫ ПЕРСОНАЖЕЙ ]      */
/*      [ CHARACTER SKINS ]      */
new const SkinsMale[9][4] = { // Мужские | Male
    {18,21,22,28},
    {18,21,22,28},
    {18,21,22,28},
    {18,21,22,28},
    {18,21,22,28},
    {18,21,22,28},
    {18,21,22,28},
    {18,21,22,28},
    {18,21,22,28}
};

new const SkinsFemale[9][2] = { // Женские | Female
    {13,69},
    {13,69},
    {13,69},
    {13,69},
    {13,69},
    {13,69},
    {13,69},
    {13,69},
    {13,69}
};

/*      [ ========== ========== ========== ========== ========== ]      */

/*      [ ОТОБРАЖАЕТ ВЫБОР ПЕРСОНАЖА ]      */
/*      [ DISPLAYS THE CHARACTER SELECTION ]      */
stock PlayerCharacterShow(playerid)
{
    static const characters_query[] = "SELECT id,accountID,firstName,lastName,age,sex,race,skin,level,exp,expTime,positionX,positionY,positionZ,rotation,interior,vw,health,armour,adminLevel,adminPassword,money,regIP,lastIP,regDate,lastDate FROM characters WHERE accountID = '%d' LIMIT %d";
    new characters_mysql[sizeof(characters_query)+(-2+11)+(-2+1)];
    mysql_format(SInfo[MySQL], characters_mysql, sizeof(characters_mysql), characters_query, PInfo[playerid][ID], MAX_CHARACTERS);
    new Cache:characters_cache = mysql_query(SInfo[MySQL], characters_mysql, true);
    cache_get_row_count(PInfo[playerid][CharactersCount]);
    if(PInfo[playerid][CharactersCount])
    {
        DataGetCharacterInfo(playerid);
        Dialog_Show(playerid, Dialog:DlgCharList);
    }
    else
        Dialog_Show(playerid, Dialog:DlgCharCreateFirstName);
    return cache_delete(characters_cache);
}

/*      [ ========== ========== ========== ========== ========== ]      */

/*      [ ДИАЛОГОВЫЕ ОКНА ]      */
/*      [ DIALOG BOXES ]      */
dCreate:DlgCharList(playerid)
{
    new temp[58+(-2+1)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+3)+(-2+3)+(-2+3)];
    new string[sizeof(temp)*MAX_CHARACTERS];
    for(new i = 0; i < MAX_CHARACTERS; i++)
    {
        if(CInfo[playerid][i][ID] == 0)
            format(temp, sizeof(temp), ""C_GRAY"[%d] "C_WHITE"Создать персонажа\n", i+1);
        else
            format(temp, sizeof(temp), ""C_GRAY"[%d] "C_WHITE"%s %s "C_GRAY"[%d LVL | %d/%d EXP]\n", i+1, CInfo[playerid][i][FirstName], CInfo[playerid][i][LastName], CInfo[playerid][i][Level], CInfo[playerid][i][Exp], LevelNeedExp(playerid, i));
        strcat(string, temp, sizeof(string));
    }
    return Dialog_Open(playerid, Dialog:DlgCharList, DIALOG_STYLE_LIST, ""C_WHITE"Выбор персонажа", string, "Выбор", "Выход");
}

dResponse:DlgCharList(playerid)
{
    if(response)
    {
        PInfo[playerid][CharacterSelect] = listitem;
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][ID] == 0)
            Dialog_Show(playerid, Dialog:DlgCharCreateFirstName);
        else
        {
            PlayerSpawnAfterAuthorization(playerid);
            new year, month, day, hour, minute, second, date[15], time[15];
            getdate(year, month, day);
            gettime(hour, minute, second);
            format(date, sizeof(date), "%02d.%02d.%02d", year, month, day);
            format(time, sizeof(time), "%02d:%02d:%02d", hour, minute, second);
            format(CInfo[playerid][PInfo[playerid][CharacterSelect]][LastDate], 22, "%s / %s", date, time);
            GetPlayerIp(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], 16);

            static const characters_query[] = "UPDATE characters SET lastIP = '%s', lastDate = '%s' WHERE id = '%d' LIMIT 1";
            new characters_mysql[sizeof(characters_query)+(-2+16)+(-2+22)+(-2+11)];
            mysql_format(SInfo[MySQL], characters_mysql, sizeof(characters_mysql), characters_query, CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastDate], CInfo[playerid][PInfo[playerid][CharacterSelect]][ID]);
            mysql_query(SInfo[MySQL], characters_mysql, false);

            static const licenses_select_query[] = "SELECT id FROM licenses WHERE characterID = '%d' LIMIT 1";
            new licenses_select_mysql[sizeof(licenses_select_query)+(-2+11)];
            mysql_format(SInfo[MySQL], licenses_select_mysql, sizeof(licenses_select_mysql), licenses_select_query, CInfo[playerid][PInfo[playerid][CharacterSelect]][ID]);
            new Cache:licenses_select_cache = mysql_query(SInfo[MySQL], licenses_select_mysql, true);
            if(!cache_num_rows())
            {
                static const licenses_insert_query[] = "INSERT INTO licenses (characterID) VALUE ('%d')";
                new licenses_insert_mysql[sizeof(licenses_insert_query)+(-2+11)];
                mysql_format(SInfo[MySQL], licenses_insert_mysql, sizeof(licenses_insert_mysql), licenses_insert_query, CInfo[playerid][PInfo[playerid][CharacterSelect]][ID]);
                mysql_query(SInfo[MySQL], licenses_insert_mysql, false);
            }
            cache_delete(licenses_select_cache);
        }
    }
    else
        KickPlayer(playerid, _, "Выход");
    return 1;
}

dCreate:DlgCharCreateFirstName(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cВведите имя своего будущего персонажа.\n\
    "C_WHITE"\\cПосле ввода имени, нажмите "C_EMERALD"\"Далее\""C_WHITE".\n\n";
    return Dialog_Open(playerid, Dialog:DlgCharCreateFirstName, DIALOG_STYLE_INPUT, ""C_GRAY"Регистрация "C_BLACK"| "C_WHITE"Создание персонажа", message, "Далее", "");
}

dResponse:DlgCharCreateFirstName(playerid)
{
    if(response)
    {
        if(!strlen(inputtext))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Все поля должны быть заполнены.");
            return Dialog_Show(playerid, Dialog:DlgCharCreateFirstName);
        }

        if(!(MIN_PLAYER_NAME <= strlen(inputtext) <= 20))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Имя слишком короткое или слишком длинное.");
            return Dialog_Show(playerid, Dialog:DlgCharCreateFirstName);
        }

        new Regex:regex_firstname_check = Regex_New("^[a-zA-Z]{1,}$");
        if(Regex_Check(inputtext, regex_firstname_check))
        {
            strmid(CInfo[playerid][0][FirstName], inputtext, 0, strlen(inputtext), MAX_PLAYER_NAME);
            Dialog_Show(playerid, Dialog:DlgCharCreateLastName);
        }
        else
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Имя может содержать только латинские символы.");
            return Dialog_Show(playerid, Dialog:DlgCharCreateFirstName);
        }
        Regex_Delete(regex_firstname_check);
    }
    return 1;
}

dCreate:DlgCharCreateLastName(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cВведите фамилию своего будущего персонажа.\n\
    "C_WHITE"\\cПосле ввода фамилии, нажмите "C_EMERALD"\"Далее\""C_WHITE".\n\n";
    return Dialog_Open(playerid, Dialog:DlgCharCreateLastName, DIALOG_STYLE_INPUT, ""C_GRAY"Регистрация "C_BLACK"| "C_WHITE"Создание персонажа", message, "Далее", "Обратно");
}

dResponse:DlgCharCreateLastName(playerid)
{
    if(response)
    {
        if(!strlen(inputtext))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Все поля должны быть заполнены.");
            return Dialog_Show(playerid, Dialog:DlgCharCreateLastName);
        }

        if(!(MIN_PLAYER_NAME <= strlen(inputtext) <= MAX_PLAYER_NAME))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Фамилия слишком короткая или слишком длинная.");
            return Dialog_Show(playerid, Dialog:DlgCharCreateLastName);
        }

        if(strlen(inputtext) > (20 - strlen(CInfo[playerid][0][FirstName])))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Фамилия слишком длинная.");
            return Dialog_Show(playerid, Dialog:DlgCharCreateLastName);
        }

        new Regex:regex_lastname_check = Regex_New("^[a-zA-Z]{1,}$");
        if(Regex_Check(inputtext, regex_lastname_check))
        {
            strmid(CInfo[playerid][0][LastName], inputtext, 0, strlen(inputtext), MAX_PLAYER_NAME);

            static const query[] = "SELECT firstname,lastname FROM characters WHERE firstname = '%s' AND lastname = '%s' LIMIT 1";
            new mysql[sizeof(query)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)];
            mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, CInfo[playerid][0][FirstName], CInfo[playerid][0][LastName]);
            new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
            if(cache_num_rows())
            {
                SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Данные имя и фамилия уже заняты! Попробуйте другие и повторите попытку.");
                return Dialog_Show(playerid, Dialog:DlgCharCreateFirstName);
            }
            else
                Dialog_Show(playerid, Dialog:DlgCharCreateAge);
            cache_delete(cache);
        }
        else
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Фамилия может содержать только латинские символы.");
            return Dialog_Show(playerid, Dialog:DlgCharCreateLastName);
        }
        Regex_Delete(regex_lastname_check);
    }
    else
        Dialog_Show(playerid, Dialog:DlgCharCreateFirstName);
    return 1;
}

dCreate:DlgCharCreateAge(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cВведите возраст своего будущего персонажа.\n\
    "C_WHITE"\\cПосле ввода возраста, нажмите "C_EMERALD"\"Далее\""C_WHITE".\n\n";
    return Dialog_Open(playerid, Dialog:DlgCharCreateAge, DIALOG_STYLE_INPUT, ""C_GRAY"Регистрация "C_BLACK"| "C_WHITE"Создание персонажа", message, "Далее", "");
}

dResponse:DlgCharCreateAge(playerid)
{
    if(response)
    {
        if(!strval(inputtext))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Все поля должны быть заполнены.");
            return Dialog_Show(playerid, Dialog:DlgCharCreateAge);
        }

        if(!(MIN_CHARACTER_AGE < strval(inputtext) < MAX_CHARACTER_AGE))
        {
            SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Возраст персонажа может быть от %d до %d лет.", MIN_CHARACTER_AGE, MAX_CHARACTER_AGE);
            return Dialog_Show(playerid, Dialog:DlgCharCreateAge);
        }

        CInfo[playerid][0][Age] = strval(inputtext);
        Dialog_Show(playerid, Dialog:DlgCharCreateSex);
    }
    return 1;
}

dCreate:DlgCharCreateSex(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cВыберите пол будущего персонажа.\n\n";
    return Dialog_Open(playerid, Dialog:DlgCharCreateSex, DIALOG_STYLE_MSGBOX, ""C_GRAY"Регистрация "C_BLACK"| "C_WHITE"Создание персонажа", message, "Мужской", "Женский");
}

dResponse:DlgCharCreateSex(playerid)
{
    if(response)
        CInfo[playerid][0][Sex] = 0;
    else
        CInfo[playerid][0][Sex] = 1;
    return Dialog_Show(playerid, Dialog:DlgCharCreateRace);
}

dCreate:DlgCharCreateRace(playerid)
{
    static const message[] = "\
    "C_WHITE"Европеоидная\n\
    "C_WHITE"Негроидная\n\
    "C_WHITE"Монголоидная";
    return Dialog_Open(playerid, Dialog:DlgCharCreateRace, DIALOG_STYLE_LIST, ""C_GRAY"Регистрация "C_BLACK"| "C_WHITE"Создание персонажа", message, "Создать", "");
}

dResponse:DlgCharCreateRace(playerid)
{
    if(response)
    {
        CInfo[playerid][0][Race] = listitem;
        new year, month, day, hour, minute, second, date[15], time[15];
        getdate(year, month, day);
        gettime(hour, minute, second);
        format(date, sizeof(date), "%02d.%02d.%02d", year, month, day);
        format(time, sizeof(time), "%02d:%02d:%02d", hour, minute, second);
        format(CInfo[playerid][0][RegDate], 22, "%s / %s", date, time);
        format(CInfo[playerid][0][LastDate], 22, "%s / %s", date, time);
        GetPlayerIp(playerid, CInfo[playerid][0][RegIP], 16);
        GetPlayerIp(playerid, CInfo[playerid][0][LastIP], 16);

        // Выбор рандомного скина исходя из возраста и расы персонажа
        // Choosing a random skin based on the age and race of the character
        new skinID = 0;
        switch(CInfo[playerid][0][Age])
        {
            case 30..45: skinID++;
            case 46..60: skinID+=2;
        }

        switch(CInfo[playerid][0][Race])
        {
            case 1: skinID+=3;
            case 2: skinID+=6;
        }

        if(CInfo[playerid][0][Sex] == 0)
            CInfo[playerid][0][Skin] = SkinsMale[skinID][random(4)];
        else if(CInfo[playerid][0][Sex] == 1)
            CInfo[playerid][0][Skin] = SkinsFemale[skinID][random(2)];

        static const character_query[] = "INSERT INTO characters (accountID,firstName,lastName,age,sex,race,skin,regIP,lastIP,regDate,lastDate) VALUES ('%d','%s','%s','%d','%d','%d','%d','%s','%s','%s','%s')";
        new character_mysql[sizeof(character_query)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+2)+(-2+1)+(-2+1)+(-2+3)+(-2+16)+(-2+16)+(-2+22)+(-2+22)];
        mysql_format(SInfo[MySQL], character_mysql, sizeof(character_mysql), character_query, PInfo[playerid][ID], CInfo[playerid][0][FirstName], CInfo[playerid][0][LastName], CInfo[playerid][0][Age], CInfo[playerid][0][Sex], CInfo[playerid][0][Race], CInfo[playerid][0][Skin], CInfo[playerid][0][RegIP], CInfo[playerid][0][LastIP], CInfo[playerid][0][RegDate], CInfo[playerid][0][LastDate]);
        new Cache:character_cache = mysql_query(SInfo[MySQL], character_mysql, true);
        if(cache_num_results())
            PlayerCharacterShow(playerid);
        else
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"При создании персонажа произошла ошибка. Обратитесь к Администрации!");
            KickPlayer(playerid, _, "Ошибка");
        }
        cache_delete(character_cache);
    }
    return 1;
}