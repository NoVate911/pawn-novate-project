<h1 align="center">
  <img src="https://i.imgur.com/Tz5wQL5.png" title="NoVate Project" alt="NoVate Project">
</h1>

<p align="center">
  <a href="https://t.me/novatesource" target="__blank">
    <img src="https://i.imgur.com/qbW4p8Y.png" width="30" height="30" title="Telegram" alt="Telegram">
  </a>
  <a href="https://t.me/novatesource" target="__blank">
    <img src="https://i.imgur.com/TFvPWEX.png" width="30" height="30" title="Discord" alt="Discord">
  </a>
</p>

<br/>

<h2 align="center">
  ВЫБЕРИТЕ ЯЗЫК
</h2>

<h3 align="center">
  <b>Русский</b> | <a href="README/eng.md">English</a>
</h3>

<br/>

---

<br/>

<h2 align="center">
    NoVate Project для SA:MP
</h2>

<p align="center">
    <sup>Бесплатная сборка (Framework & Toolkit) для SA:MP разработчиков</sup>
</p>

---

## :desktop_computer: ОПИСАНИЕ

Давно хотели создать свой собственный сервер в SA:MP, но не знали с чего начать? Вашему вниманию **NoVate Project**. Сборка включает в себя набор основных инструментов для хорошего старта разработки сервера SA:MP.

---

## :keyboard: ТЕХНИЧЕСКАЯ ЧАСТЬ

### КОМПИЛЯЦИЯ

Для компиляции используется разработка от [Zeex](https://github.com/pawn-lang/compiler). Множество улучшений, которые ускоряют процесс компиляции мода.

### ПЛАГИНЫ

- [Pawn.CMD](https://github.com/katursis/Pawn.CMD) - командный процессор. Является самым быстрым по словам разработчика.
- [Pawn.Regex](https://github.com/katursis/Pawn.Regex) - поддержка регулярных выражений.
- [Streamer](https://github.com/samp-incognito/samp-streamer-plugin) - увеличивает лимиты на сервере.
- [MySQL](https://github.com/pBlueG/SA-MP-MySQL) - база данных MySQL.
- [MD5](https://github.com/brbsh/samp-plugin-md5) - шифрование данных.
- [YSF](https://github.com/IS4Code/YSF) - извлекает максимум возможностей с помощью редактирования памяти и подключения.
- [sscanf2](https://github.com/Y-Less/sscanf) - используется для различных проверок.

### ИНКЛУДЫ

- [mDialog](https://github.com/Open-GTO/mdialog) - упрощённая система для создания и управления диалогами.

---

## :star: БЫСТРЫЙ СТАРТ

### НЕОБХОДИМЫЕ ПРОГРАММЫ
<sup>Ссылки под знаком (*) не являются обязательными.</sup>

- [XAMPP](https://www.apachefriends.org/)
- [HeidiSQL](https://www.heidisql.com/download.php)
- [Git](https://git-scm.com/downloads)
- [Visual Studio Code *](https://code.visualstudio.com/Download)
- [SA:MP](https://sa-mp.com/download.php)

### УСТАНОВКА
<sup>Через Terminal или PowerShell</sup>

```
git clone https://github.com/NoVate911/pawn-novate-project
```

<br/>

```
cd pawn-novate-project
```

<br/>

```
Пишем "samp-novateproject.sql" и импортируем базу данных (перед этим запустите XAMPP)
```

<br/>

```
После успешного импортирования базы данных, пишем "samp-server.exe" и ждём окончания запуска сервера
```