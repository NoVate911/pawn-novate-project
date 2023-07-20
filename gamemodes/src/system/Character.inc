/*      [ СКИНЫ ПЕРСОНАЖЕЙ ]      */
/*      [ CHARACTER SKINS ]      */
new const Skins_Male[9][4] = { // Мужские | Male
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

new const Skins_Female[9][2] = { // Женские | Female
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
stock Player_CharacterShow(playerid)
{
    static const query[] = "SELECT id,login,firstname,lastname,age,sex,race,skin,level,exp,positionX,positionY,positionZ,rotation,interior,vw,health,armour,adminLevel,adminPassword,regIP,lastIP,regDate,lastDate FROM characters WHERE login = '%s' LIMIT %d";
    new mysql[sizeof(query)+(-2+MAX_PLAYER_NAME)+(-2+1)];
    mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, PInfo[playerid][Nick], MAX_CHARACTERS);
    new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
    cache_get_row_count(PInfo[playerid][CharactersCount]);
    if(PInfo[playerid][CharactersCount])
    {
        Data_Get_CharacterInfo(playerid);
        Dialog_Show(playerid, Dialog:Dlg_Char_List);
    }
    else
        Dialog_Show(playerid, Dialog:Dlg_Char_CreateFirstName);
    return cache_delete(cache);
}

/*      [ ========== ========== ========== ========== ========== ]      */

/*      [ ДИАЛОГОВЫЕ ОКНА ]      */
/*      [ DIALOG BOXES ]      */
dCreate:Dlg_Char_List(playerid)
{
    new temp[55+(-2+1)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+3)];
    new string[sizeof(temp)*MAX_CHARACTERS];
    for(new i = 0; i < MAX_CHARACTERS; i++)
    {
        if(CInfo[playerid][i][ID] == 0)
            format(temp, sizeof(temp), ""C_GRAY"[%d] "C_WHITE"Создать персонажа\n", i+1);
        else
            format(temp, sizeof(temp), ""C_GRAY"[%d] "C_WHITE"%s %s "C_GRAY"(%d LVL / %d EXP)\n", i+1, CInfo[playerid][i][FirstName], CInfo[playerid][i][LastName], CInfo[playerid][i][Level], CInfo[playerid][i][Exp]);
        strcat(string, temp, sizeof(string));
    }
    return Dialog_Open(playerid, Dialog:Dlg_Char_List, DIALOG_STYLE_LIST, ""C_WHITE"Выбор персонажа", string, "Выбор", "Выход");
}

dResponse:Dlg_Char_List(playerid)
{
    if(response)
    {
        PInfo[playerid][CharacterSelect] = listitem;
        if(CInfo[playerid][PInfo[playerid][CharacterSelect]][ID] == 0)
            Dialog_Show(playerid, Dialog:Dlg_Char_CreateFirstName);
        else
        {
            Player_SpawnAfterAuthorization(playerid);
            new year, month, day, hour, minute, second, date[15], time[15];
            getdate(year, month, day);
            gettime(hour, minute, second);
            format(date, sizeof(date), "%02d.%02d.%02d", year, month, day);
            format(time, sizeof(time), "%02d:%02d:%02d", hour, minute, second);
            format(CInfo[playerid][PInfo[playerid][CharacterSelect]][LastDate], 22, "%s / %s", date, time);
            GetPlayerIp(playerid, CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], 16);

            static const query[] = "UPDATE characters SET lastIP = '%s', lastDate = '%s' WHERE login = '%s' LIMIT 1";
            new mysql[sizeof(query)+(-2+16)+(-2+22)+(-2+MAX_PLAYER_NAME)];
            mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, CInfo[playerid][PInfo[playerid][CharacterSelect]][LastIP], CInfo[playerid][PInfo[playerid][CharacterSelect]][LastDate], CInfo[playerid][PInfo[playerid][CharacterSelect]][Login]);
            mysql_query(SInfo[MySQL], mysql, false);
        }
    }
    else
        Player_Kick(playerid, _, "Выход");
    return 1;
}

dCreate:Dlg_Char_CreateFirstName(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cВведите имя своего будущего персонажа.\n\
    "C_WHITE"\\cПосле ввода имени, нажмите "C_EMERALD"\"Далее\""C_WHITE".\n\n";
    return Dialog_Open(playerid, Dialog:Dlg_Char_CreateFirstName, DIALOG_STYLE_INPUT, ""C_GRAY"Регистрация "C_BLACK"| "C_WHITE"Создание персонажа", message, "Далее", "");
}

dResponse:Dlg_Char_CreateFirstName(playerid)
{
    if(response)
    {
        if(!strlen(inputtext))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Все поля должны быть заполнены.");
            return Dialog_Show(playerid, Dialog:Dlg_Char_CreateFirstName);
        }

        if(!(MIN_PLAYER_NAME < strlen(inputtext) < MAX_PLAYER_NAME))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Имя слишком короткое или слишком длинное.");
            return Dialog_Show(playerid, Dialog:Dlg_Char_CreateFirstName);
        }

        new Regex:regex_firstname_check = Regex_New("^[a-zA-Z]{1,}$");
        if(Regex_Check(inputtext, regex_firstname_check))
        {
            strmid(CInfo[playerid][0][FirstName], inputtext, 0, strlen(inputtext), MAX_PLAYER_NAME);
            Dialog_Show(playerid, Dialog:Dlg_Char_CreateLastName);
        }
        else
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Имя может содержать только латинские символы.");
            return Dialog_Show(playerid, Dialog:Dlg_Char_CreateFirstName);
        }
        Regex_Delete(regex_firstname_check);
    }
    return 1;
}

dCreate:Dlg_Char_CreateLastName(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cВведите фамилию своего будущего персонажа.\n\
    "C_WHITE"\\cПосле ввода фамилии, нажмите "C_EMERALD"\"Далее\""C_WHITE".\n\n";
    return Dialog_Open(playerid, Dialog:Dlg_Char_CreateLastName, DIALOG_STYLE_INPUT, ""C_GRAY"Регистрация "C_BLACK"| "C_WHITE"Создание персонажа", message, "Далее", "Обратно");
}

dResponse:Dlg_Char_CreateLastName(playerid)
{
    if(response)
    {
        if(!strlen(inputtext))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Все поля должны быть заполнены.");
            return Dialog_Show(playerid, Dialog:Dlg_Char_CreateLastName);
        }

        if(!(MIN_PLAYER_NAME < strlen(inputtext) < MAX_PLAYER_NAME))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Фамилия слишком короткая или слишком длинная.");
            return Dialog_Show(playerid, Dialog:Dlg_Char_CreateLastName);
        }

        if(strlen(inputtext) > ((MAX_PLAYER_NAME - 1) - (strlen(CInfo[playerid][0][FirstName]) - 1)))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Фамилия слишком длинная.");
            return Dialog_Show(playerid, Dialog:Dlg_Char_CreateLastName);
        }

        new Regex:regex_lastname_check = Regex_New("^[a-zA-Z]{1,}$");
        if(Regex_Check(inputtext, regex_lastname_check))
        {
            strmid(CInfo[playerid][0][LastName], inputtext, 0, strlen(inputtext), MAX_PLAYER_NAME);
            Dialog_Show(playerid, Dialog:Dlg_Char_CreateAge);
        }
        else
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Фамилия может содержать только латинские символы.");
            return Dialog_Show(playerid, Dialog:Dlg_Char_CreateLastName);
        }
        Regex_Delete(regex_lastname_check);
    }
    else
        Dialog_Show(playerid, Dialog:Dlg_Char_CreateFirstName);
    return 1;
}

dCreate:Dlg_Char_CreateAge(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cВведите возраст своего будущего персонажа.\n\
    "C_WHITE"\\cПосле ввода возраста, нажмите "C_EMERALD"\"Далее\""C_WHITE".\n\n";
    return Dialog_Open(playerid, Dialog:Dlg_Char_CreateAge, DIALOG_STYLE_INPUT, ""C_GRAY"Регистрация "C_BLACK"| "C_WHITE"Создание персонажа", message, "Далее", "");
}

dResponse:Dlg_Char_CreateAge(playerid)
{
    if(response)
    {
        if(!strval(inputtext))
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Все поля должны быть заполнены.");
            return Dialog_Show(playerid, Dialog:Dlg_Char_CreateAge);
        }

        if(!(MIN_CHARACTER_AGE < strval(inputtext) < MAX_CHARACTER_AGE))
        {
            SCMf(playerid, -1, ""NOTIF_ERROR" "C_WHITE"Возраст персонажа может быть от %d до %d лет.", MIN_CHARACTER_AGE, MAX_CHARACTER_AGE);
            return Dialog_Show(playerid, Dialog:Dlg_Char_CreateAge);
        }

        CInfo[playerid][0][Age] = strval(inputtext);
        Dialog_Show(playerid, Dialog:Dlg_Char_CreateSex);
    }
    return 1;
}

dCreate:Dlg_Char_CreateSex(playerid)
{
    static const message[] = "\
    "C_WHITE"\n\\cВыберите пол будущего персонажа.\n\n";
    return Dialog_Open(playerid, Dialog:Dlg_Char_CreateSex, DIALOG_STYLE_MSGBOX, ""C_GRAY"Регистрация "C_BLACK"| "C_WHITE"Создание персонажа", message, "Мужской", "Женский");
}

dResponse:Dlg_Char_CreateSex(playerid)
{
    if(response)
        CInfo[playerid][0][Sex] = 0;
    else
        CInfo[playerid][0][Sex] = 1;
    return Dialog_Show(playerid, Dialog:Dlg_Char_CreateRace);
}

dCreate:Dlg_Char_CreateRace(playerid)
{
    static const message[] = "\
    "C_WHITE"Европеоидная\n\
    "C_WHITE"Негроидная\n\
    "C_WHITE"Монголоидная";
    return Dialog_Open(playerid, Dialog:Dlg_Char_CreateRace, DIALOG_STYLE_LIST, ""C_GRAY"Регистрация "C_BLACK"| "C_WHITE"Создание персонажа", message, "Создать", "");
}

dResponse:Dlg_Char_CreateRace(playerid)
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
            CInfo[playerid][0][Skin] = Skins_Male[skinID][random(4)];
        else if(CInfo[playerid][0][Sex] == 1)
            CInfo[playerid][0][Skin] = Skins_Female[skinID][random(2)];

        static const query[] = "INSERT INTO characters (login,firstname,lastname,age,sex,race,skin,regIP,lastIP,regDate,lastDate) VALUES ('%s','%s','%s','%d','%d','%d','%d','%s','%s','%s','%s')";
        new mysql[sizeof(query)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+MAX_PLAYER_NAME)+(-2+2)+(-2+1)+(-2+1)+(-2+3)+(-2+16)+(-2+16)+(-2+22)+(-2+22)];
        mysql_format(SInfo[MySQL], mysql, sizeof(mysql), query, PInfo[playerid][Nick], CInfo[playerid][0][FirstName], CInfo[playerid][0][LastName], CInfo[playerid][0][Age], CInfo[playerid][0][Sex], CInfo[playerid][0][Race], CInfo[playerid][0][Skin], CInfo[playerid][0][RegIP], CInfo[playerid][0][LastIP], CInfo[playerid][0][RegDate], CInfo[playerid][0][LastDate]);
        new Cache:cache = mysql_query(SInfo[MySQL], mysql, true);
        if(cache_num_results())
            Player_CharacterShow(playerid);
        else
        {
            SCM(playerid, -1, ""NOTIF_ERROR" "C_WHITE"При создании персонажа произошла ошибка. Обратитесь к Администрации!");
            Player_Kick(playerid, _, "Ошибка");
        }
        cache_delete(cache);
    }
    return 1;
}