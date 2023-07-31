/*      [ БАЗА ДАННЫХ ]      */
/*      [ DATABASE ]      */
#define MYSQL_HOSTNAME              "localhost"
#define MYSQL_USERNAME              "root"
#define MYSQL_PASSWORD              ""
#define MYSQL_DATABASE              "samp-novateproject"

/*      [ АВТОРИЗАЦИЯ/РЕГИСТРАЦИЯ ]      */
/*      [ AUTHORIZATION/REGISTRATION ]      */
#define MAX_AUTHORIZATION_TIME      (120) // Максимальное время авторизации (в секундах) | Maximum authorization time (in seconds)
#define MAX_REGISTRATION_TIME       (180) // Максимальное время регистрации (в секундах) | Maximum registration time (in seconds)
#define AUTHORIZATION_COUNT_TRY     (3) // Максимальное количество попыток входа | Maximum number of login attempts

#define MAX_PASSWORD_LEN            (32) // Максимальная длина пароля | Maximum password length
#define MIN_PASSWORD_LEN            (4) // Минимальная длина пароля | Minimum password length

#define MAX_EMAIL_LEN               (64) // Максимальная длина почты | Maximum mail length
#define MIN_EMAIL_LEN               (1) // Минимальная длина почты | Minimum mail length

#define MAX_POSITIONS_SPAWN         (1) // Максимальное количество позиций для спавна | Maximum number of spawn positions

/*      [ ПЕРСОНАЖ ]      */
/*      [ CHARACTER ]      */
#define MAX_CHARACTERS              (3) // Максимальное количество персонажей | Maximum number of characters

#define MAX_CHARACTER_AGE           (60) // Максимальный возраст персонажа | Maximum age of the character
#define MIN_CHARACTER_AGE           (18) // Минимальный возраст персонажа | Minimum age of the character

/*      [ АДМИНИСТРИРОВАНИЕ ]      */
/*      [ ADMINISTRATION ]      */
#define MAX_ADMIN_LEVEL             (10) // Максимальный уровень Администратора | Maximum Administrator Level
#define MIN_ADMIN_LEVEL             (1) // Минимальный уровень Администратора | Minimum Administrator Level

/*      [ ЧАТ ]      */
/*      [ CHAT ]      */
#define MAX_DISTANCE_CHAT           (10.0) // Максимальная дистанция отправки сообщений | Maximum distance for sending messages

/*      [ УРОВЕНЬ/ОПЫТ ]      */
/*      [ LEVEL/EXP ]      */
#define MAX_LEVEL                   (100) // Максимальное количество уровней | Maximum number of levels

#define MAX_EXP_UPDATE_LEVEL        (2) // Максимальное количество опыта для повышения уровня | Maximum amount of experience to level up
#define MAX_TIME_UPDATE_LEVEL       (3600) // Время обновления уровня/опыта игрока (в секундах) | Player Level/Experience Update Time (in seconds)

/*      [ AFK ]      */
/*      [ AFK ]      */
#define MAX_AFK_TIME_SET            (30) // Время после которого игрок будет входить в AFK (в секундах) | The time after which the player will enter AFK (in seconds)
#define MAX_AFK_TIME_WARNING        (10) // Время после которого будет выводиться предупреждение (в секундах) | The time after which the warning will be displayed (in seconds)

/*      [  ]      */
#define MAX_BAN_ACCOUNTS            (100000) // Максимальное количество банов аккаунтов | Maximum number of account bans
#define MAX_BAN_CHARACTERS          (100000) // Максимальное количество банов персонажей | Maximum number of character bans