/*
Navicat MySQL Data Transfer

Source Server         : mysql
Source Server Version : 50538
Source Host           : localhost:3306
Source Database       : cobaya

Target Server Type    : MYSQL
Target Server Version : 50538
File Encoding         : 65001

Date: 2014-10-29 22:04:28
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for 异常
-- ----------------------------
DROP TABLE IF EXISTS `异常`;
CREATE TABLE `异常` (
  `器械编码` varchar(10) NOT NULL,
  `器械名称` varchar(20) NOT NULL,
  `管理终端` varchar(20) NOT NULL,
  `所属科室` varchar(10) NOT NULL,
  `异常时间` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 异常
-- ----------------------------
INSERT INTO `异常` VALUES ('DR_001', 'DR机', '192.168.122.5', '放射科', '2014-10-29 22:00:19');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', 'CT室', '2014-10-29 22:00:19');
INSERT INTO `异常` VALUES ('BC_002', 'B超机', '192.168.122.4', 'CT室', '2014-10-29 22:00:19');
INSERT INTO `异常` VALUES ('BC_001', 'B超机', '192.168.122.2', 'B超室', '2014-10-29 22:00:19');
INSERT INTO `异常` VALUES ('DR_001', 'DR机', '192.168.122.5', '放射科', '2014-10-29 22:01:19');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', 'CT室', '2014-10-29 22:01:19');
INSERT INTO `异常` VALUES ('BC_002', 'B超机', '192.168.122.4', 'CT室', '2014-10-29 22:01:19');
INSERT INTO `异常` VALUES ('BC_001', 'B超机', '192.168.122.2', 'B超室', '2014-10-29 22:01:19');
INSERT INTO `异常` VALUES ('DR_001', 'DR机', '192.168.122.5', '放射科', '2014-10-29 22:02:19');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', 'CT室', '2014-10-29 22:02:19');
INSERT INTO `异常` VALUES ('BC_002', 'B超机', '192.168.122.4', 'CT室', '2014-10-29 22:02:19');
INSERT INTO `异常` VALUES ('BC_001', 'B超机', '192.168.122.2', 'B超室', '2014-10-29 22:02:19');

-- ----------------------------
-- Table structure for 日志
-- ----------------------------
DROP TABLE IF EXISTS `日志`;
CREATE TABLE `日志` (
  `操作员` varchar(10) NOT NULL,
  `登录终端` varchar(20) NOT NULL,
  `时间` datetime NOT NULL,
  `器械编码` varchar(10) NOT NULL,
  `器械名称` varchar(20) NOT NULL,
  `器械科室` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 日志
-- ----------------------------
INSERT INTO `日志` VALUES ('小张', '192.168.122.2', '2014-09-01 11:15:42', '1', 'B超机', 'B超室');

-- ----------------------------
-- Table structure for 用户
-- ----------------------------
DROP TABLE IF EXISTS `用户`;
CREATE TABLE `用户` (
  `姓名` varchar(10) NOT NULL,
  `密码` varchar(10) NOT NULL,
  `登录终端` varchar(20) NOT NULL,
  `登录时间` datetime NOT NULL,
  PRIMARY KEY (`姓名`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 用户
-- ----------------------------
INSERT INTO `用户` VALUES ('小王', '123456', '10.10.10.10', '2014-09-03 11:38:10');
INSERT INTO `用户` VALUES ('小张', '111111', '192.168.122.3', '2014-09-04 10:55:23');
INSERT INTO `用户` VALUES ('小赵', '111111', '192.168.122.2', '2014-09-02 11:38:59');

-- ----------------------------
-- Table structure for 科室
-- ----------------------------
DROP TABLE IF EXISTS `科室`;
CREATE TABLE `科室` (
  `科室` varchar(10) NOT NULL,
  PRIMARY KEY (`科室`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 科室
-- ----------------------------
INSERT INTO `科室` VALUES ('B超室');
INSERT INTO `科室` VALUES ('CT室');
INSERT INTO `科室` VALUES ('放射科');
INSERT INTO `科室` VALUES ('检验科');
INSERT INTO `科室` VALUES ('体检中心');

-- ----------------------------
-- Table structure for 设备
-- ----------------------------
DROP TABLE IF EXISTS `设备`;
CREATE TABLE `设备` (
  `器械编码` varchar(10) NOT NULL,
  `器械名称` varchar(20) NOT NULL,
  `管理终端` varchar(20) NOT NULL,
  `所属科室` varchar(10) NOT NULL,
  PRIMARY KEY (`器械编码`,`管理终端`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 设备
-- ----------------------------
INSERT INTO `设备` VALUES ('BC_001', 'B超机', '192.168.122.2', 'B超室');
INSERT INTO `设备` VALUES ('BC_002', 'B超机', '192.168.122.4', 'CT室');
INSERT INTO `设备` VALUES ('CT_001', 'CT机', '192.168.122.3', 'CT室');
INSERT INTO `设备` VALUES ('DR_001', 'DR机', '192.168.122.5', '放射科');
