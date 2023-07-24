<h2 align="center">
    NoVate Project for SA:MP
</h2>

<p align="center">
    <sup>Free Build (Framework & Toolkit) for SA:MP Developers</sup>
</p>

---

## :desktop_computer: DESCRIPTION

Have you wanted to create your own server in SA:MP for a long time, but didn't know where to start? To your attention **NoVate Project**. The build includes a set of basic tools for a good start to the development of the SA:MP server.

---

## :keyboard: TECHNICAL PART

### COMPILATION

Development from [Zeex](https://github.com/pawn-lang/compiler) is used for compilation. A lot of improvements that speed up the compilation process of the mod.

### PLUGINS

- [Pawn.CMD](https://github.com/katursis/Pawn.CMD) - the command processor. Is the fastest according to the developer.
- [Pawn.Regex](https://github.com/katursis/Pawn.Regex) - regular expression support.
- [Streamer](https://github.com/samp-incognito/samp-streamer-plugin) - increases the limits on the server.
- [MySQL](https://github.com/pBlueG/SA-MP-MySQL) - MySQL database.
- [MD5](https://github.com/brbsh/samp-plugin-md5) - data encryption.
- [YSF](https://github.com/IS4Code/YSF) - extracts maximum capabilities by editing memory and connecting.
- [sscanf2](https://github.com/Y-Less/sscanf) - used for various checks.

### INCLUDS

- [mDialog](https://github.com/Open-GTO/mdialog) - simplified system for creating and managing dialogs.

---

## :star: QUICK START

### REQUIRED PROGRAMS
<sup>Links under the sign (*) are optional.</sup>

- [XAMPP](https://www.apachefriends.org/)
- [HeidiSQL](https://www.heidisql.com/download.php)
- [Git](https://git-scm.com/downloads)
- [Visual Studio Code *](https://code.visualstudio.com/Download)
- [SA:MP](https://sa-mp.com/download.php)

### INSTALLATION
<sup>Via Terminal or PowerShell</sup>

```
git clone https://github.com/NoVate911/pawn-novate-project
```

<br/>

```
cd pawn-novate-project
```

<br/>

```
Write "samp-novateproject.sql" and import the database (before that, run XAMPP)
```

<br/>

```
After successfully importing the database, we write "samp-server.exe " and we are waiting for the end of the server launch
```