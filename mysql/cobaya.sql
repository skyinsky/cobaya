/*
Navicat MySQL Data Transfer

Source Server         : mysql
Source Server Version : 50538
Source Host           : localhost:3306
Source Database       : cobaya

Target Server Type    : MYSQL
Target Server Version : 50538
File Encoding         : 65001

Date: 2014-10-27 00:44:03
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for 日志
-- ----------------------------
DROP TABLE IF EXISTS `日志`;
CREATE TABLE `日志` (
  `编号` bigint(8) NOT NULL,
  `时间` datetime NOT NULL,
  `操作员` varchar(10) NOT NULL,
  `登录终端` varchar(20) NOT NULL,
  `器械编码` varchar(10) NOT NULL,
  `器械名称` varchar(20) NOT NULL,
  `器械科室` varchar(10) NOT NULL,
  `病人唯一号` varchar(20) NOT NULL,
  `病人姓名` varchar(10) NOT NULL,
  `登记项目` varchar(255) NOT NULL,
  PRIMARY KEY (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 日志
-- ----------------------------
INSERT INTO `日志` VALUES ('1', '2014-09-01 11:15:42', '小张', '192.168.122.2', '1', 'B超机', 'B超室', '', '', '');

-- ----------------------------
-- Table structure for 用户
-- ----------------------------
DROP TABLE IF EXISTS `用户`;
CREATE TABLE `用户` (
  `姓名` varchar(10) NOT NULL,
  `密码` varchar(10) NOT NULL,
  `所属科室` varchar(10) NOT NULL,
  `注册时间` datetime NOT NULL,
  `注册终端` varchar(20) NOT NULL,
  PRIMARY KEY (`姓名`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 用户
-- ----------------------------
INSERT INTO `用户` VALUES ('小王', '111111', 'CT室', '2014-09-03 11:38:10', '192.168.122.3');
INSERT INTO `用户` VALUES ('小张', '111111', 'CT室', '2014-09-04 10:55:23', '192.168.122.3');
INSERT INTO `用户` VALUES ('小赵', '111111', 'B超室', '2014-09-02 11:38:59', '192.168.122.2');

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
  PRIMARY KEY (`器械编码`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 设备
-- ----------------------------
INSERT INTO `设备` VALUES ('BC_001', 'B超机', '192.168.122.2', 'B超室');
INSERT INTO `设备` VALUES ('BC_002', 'B超机', '192.168.122.4', 'CT室');
INSERT INTO `设备` VALUES ('CT_001', 'CT机', '192.168.122.3', 'CT室');
INSERT INTO `设备` VALUES ('DR_001', 'DR机', '192.168.122.5', '放射科');
