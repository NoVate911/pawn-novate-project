-- --------------------------------------------------------
-- РҐРѕСЃС‚:                         127.0.0.1
-- Р’РµСЂСЃРёСЏ СЃРµСЂРІРµСЂР°:               10.4.27-MariaDB - mariadb.org binary distribution
-- РћРїРµСЂР°С†РёРѕРЅРЅР°СЏ СЃРёСЃС‚РµРјР°:         Win64
-- HeidiSQL Р’РµСЂСЃРёСЏ:              12.5.0.6677
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Р”Р°РјРї СЃС‚СЂСѓРєС‚СѓСЂС‹ Р±Р°Р·С‹ РґР°РЅРЅС‹С… samp-novateproject
CREATE DATABASE IF NOT EXISTS `samp-novateproject` /*!40100 DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci */;
USE `samp-novateproject`;

-- Р”Р°РјРї СЃС‚СЂСѓРєС‚СѓСЂС‹ РґР»СЏ С‚Р°Р±Р»РёС†Р° samp-novateproject.accounts
CREATE TABLE IF NOT EXISTS `accounts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nick` varchar(24) DEFAULT 'NoVate',
  `password` varchar(32) DEFAULT NULL,
  `email` varchar(64) DEFAULT 'admin@yandex.ru',
  `donate` int(11) DEFAULT 0,
  `regIP` varchar(15) DEFAULT '0.0.0.0',
  `lastIP` varchar(15) DEFAULT '0.0.0.0',
  `regDate` varchar(21) DEFAULT '1999.01.01 / 00:00:00',
  `lastDate` varchar(21) DEFAULT '1999.01.01 / 00:00:00',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- Р­РєСЃРїРѕСЂС‚РёСЂСѓРµРјС‹Рµ РґР°РЅРЅС‹Рµ РЅРµ РІС‹РґРµР»РµРЅС‹.

-- Р”Р°РјРї СЃС‚СЂСѓРєС‚СѓСЂС‹ РґР»СЏ С‚Р°Р±Р»РёС†Р° samp-novateproject.characters
CREATE TABLE IF NOT EXISTS `characters` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `login` varchar(24) DEFAULT 'NoVate',
  `firstname` varchar(24) DEFAULT 'Jony',
  `lastname` varchar(24) DEFAULT 'Quatro',
  `age` int(2) DEFAULT 18,
  `sex` int(1) DEFAULT 0,
  `race` int(1) DEFAULT 0,
  `skin` int(3) DEFAULT 0,
  `level` int(3) DEFAULT 1,
  `exp` int(3) DEFAULT 0,
  `expTime` int(4) DEFAULT 3600,
  `positionX` float DEFAULT 0,
  `positionY` float DEFAULT 0,
  `positionZ` float DEFAULT 0,
  `rotation` float DEFAULT 0,
  `interior` int(3) DEFAULT 0,
  `vw` int(10) DEFAULT 0,
  `health` float DEFAULT 100,
  `armour` float DEFAULT 0,
  `adminLevel` int(2) DEFAULT 0,
  `adminPassword` int(4) DEFAULT NULL,
  `regIP` varchar(15) DEFAULT '0.0.0.0',
  `lastIP` varchar(15) DEFAULT '0.0.0.0',
  `regDate` varchar(21) DEFAULT '1999.01.01 / 00:00:00',
  `lastDate` varchar(21) DEFAULT '1999.01.01 / 00:00:00',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

-- Р­РєСЃРїРѕСЂС‚РёСЂСѓРµРјС‹Рµ РґР°РЅРЅС‹Рµ РЅРµ РІС‹РґРµР»РµРЅС‹.

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
