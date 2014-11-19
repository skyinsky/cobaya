/*
Navicat MySQL Data Transfer

Source Server         : mysql
Source Server Version : 50538
Source Host           : localhost:3306
Source Database       : cobaya

Target Server Type    : MYSQL
Target Server Version : 50538
File Encoding         : 65001

Date: 2014-11-20 00:43:21
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
  `科室编号` varchar(20) NOT NULL,
  `科室名称` varchar(20) NOT NULL,
  `院区` varchar(20) NOT NULL,
  `异常时间` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 异常
-- ----------------------------
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-19 23:59:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:00:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:01:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:02:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:03:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:04:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:05:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:06:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:07:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:08:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:09:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:10:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:11:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:12:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:13:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:14:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:15:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:16:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:17:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:18:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:19:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:20:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:21:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:22:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:23:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:24:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:25:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:26:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:27:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:28:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:29:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:30:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:31:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:32:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:33:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:34:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:35:25');
INSERT INTO `异常` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院', '2014-11-20 00:36:25');

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
  `科室编号` varchar(20) NOT NULL,
  `科室名称` varchar(20) NOT NULL,
  `院区` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 日志
-- ----------------------------

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
-- Table structure for 监控科室
-- ----------------------------
DROP TABLE IF EXISTS `监控科室`;
CREATE TABLE `监控科室` (
  `科室编号` varchar(20) NOT NULL,
  `科室名称` varchar(20) NOT NULL,
  `院区` varchar(20) NOT NULL,
  `执行项目` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 监控科室
-- ----------------------------
INSERT INTO `监控科室` VALUES ('0000021', '放射科', '人民医院', '_FS');
INSERT INTO `监控科室` VALUES ('0000097', '核磁室', '人民医院', '_HC');
INSERT INTO `监控科室` VALUES ('0000096', 'CT室', '人民医院', '_CT');
INSERT INTO `监控科室` VALUES ('0000130', '二院CT室', '妇产医院', '_CT');
INSERT INTO `监控科室` VALUES ('0000038', '二院放射科', '妇产医院', '_FS');
INSERT INTO `监控科室` VALUES ('0000039', '心脑超声', '心脑医院', '_CS');
INSERT INTO `监控科室` VALUES ('0000037', '心脑放射', '心脑医院', '_CT_FS');

-- ----------------------------
-- Table structure for 监控科室全
-- ----------------------------
DROP TABLE IF EXISTS `监控科室全`;
CREATE TABLE `监控科室全` (
  `科室编号` varchar(20) DEFAULT NULL,
  `科室名称` varchar(20) DEFAULT NULL,
  `院区` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 监控科室全
-- ----------------------------
INSERT INTO `监控科室全` VALUES ('0000021', '放射科', '人民医院');
INSERT INTO `监控科室全` VALUES ('0000097', '核磁室', '人民医院');
INSERT INTO `监控科室全` VALUES ('0000096', 'CT室', '人民医院');
INSERT INTO `监控科室全` VALUES ('0000130', '二院CT室', '妇产医院');
INSERT INTO `监控科室全` VALUES ('0000038', '二院放射科', '妇产医院');
INSERT INTO `监控科室全` VALUES ('0000098', 'CT室', '心脑医院');
INSERT INTO `监控科室全` VALUES ('0000039', '心脑超声', '心脑医院');
INSERT INTO `监控科室全` VALUES ('0000035', '心脑检验', '心脑医院');
INSERT INTO `监控科室全` VALUES ('0000037', '心脑放射', '心脑医院');
INSERT INTO `监控科室全` VALUES ('0000034', '体检中心', '心脑医院');

-- ----------------------------
-- Table structure for 科室
-- ----------------------------
DROP TABLE IF EXISTS `科室`;
CREATE TABLE `科室` (
  `编号` varchar(20) CHARACTER SET gbk NOT NULL,
  `名称` varchar(20) NOT NULL,
  `院区` varchar(20) NOT NULL,
  PRIMARY KEY (`编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 科室
-- ----------------------------
INSERT INTO `科室` VALUES ('0000000', '全院', '全院');
INSERT INTO `科室` VALUES ('0000001', '手术室', '人民医院');
INSERT INTO `科室` VALUES ('0000002', '总院外二科', '人民医院');
INSERT INTO `科室` VALUES ('0000003', '总院外一科', '人民医院');
INSERT INTO `科室` VALUES ('0000004', '总院骨科', '人民医院');
INSERT INTO `科室` VALUES ('0000005', '普内科', '人民医院');
INSERT INTO `科室` VALUES ('0000006', '总院脑外科', '人民医院');
INSERT INTO `科室` VALUES ('0000007', '口腔科', '人民医院');
INSERT INTO `科室` VALUES ('0000008', '中医骨伤科', '人民医院');
INSERT INTO `科室` VALUES ('0000009', '耳鼻喉科', '人民医院');
INSERT INTO `科室` VALUES ('0000010', '眼  科', '人民医院');
INSERT INTO `科室` VALUES ('0000011', '肛肠科', '人民医院');
INSERT INTO `科室` VALUES ('0000012', '脑血管科', '心脑医院');
INSERT INTO `科室` VALUES ('0000013', '心内科', '心脑医院');
INSERT INTO `科室` VALUES ('0000014', '妇产妇科', '妇产医院');
INSERT INTO `科室` VALUES ('0000015', '产  科', '妇产医院');
INSERT INTO `科室` VALUES ('0000016', '二院手术室(一)', '妇产医院');
INSERT INTO `科室` VALUES ('0000017', '急诊科', '人民医院');
INSERT INTO `科室` VALUES ('0000018', '总院儿科', '人民医院');
INSERT INTO `科室` VALUES ('0000019', '超声科', '人民医院');
INSERT INTO `科室` VALUES ('0000020', '检验科', '人民医院');
INSERT INTO `科室` VALUES ('0000021', '放射科', '人民医院');
INSERT INTO `科室` VALUES ('0000022', '心电图室', '人民医院');
INSERT INTO `科室` VALUES ('0000023', '皮肤科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000024', '内窥镜室', '人民医院');
INSERT INTO `科室` VALUES ('0000025', '病理科', '人民医院');
INSERT INTO `科室` VALUES ('0000026', '中医科', '人民医院');
INSERT INTO `科室` VALUES ('0000027', '供应室', '人民医院');
INSERT INTO `科室` VALUES ('0000028', '二院供应室', '妇产医院');
INSERT INTO `科室` VALUES ('0000029', '医院药剂科', '人民医院');
INSERT INTO `科室` VALUES ('0000030', '药  库', '人民医院');
INSERT INTO `科室` VALUES ('0000031', '制剂室', '人民医院');
INSERT INTO `科室` VALUES ('0000032', '心脑药房', '心脑医院');
INSERT INTO `科室` VALUES ('0000033', '二院药房(一)', '妇产医院');
INSERT INTO `科室` VALUES ('0000034', '体检中心', '心脑医院');
INSERT INTO `科室` VALUES ('0000035', '心脑检验', '心脑医院');
INSERT INTO `科室` VALUES ('0000036', '二院检验科(一)', '妇产医院');
INSERT INTO `科室` VALUES ('0000037', '心脑放射', '心脑医院');
INSERT INTO `科室` VALUES ('0000038', '二院放射科', '妇产医院');
INSERT INTO `科室` VALUES ('0000039', '心脑超声', '心脑医院');
INSERT INTO `科室` VALUES ('0000040', '二院超声科', '妇产医院');
INSERT INTO `科室` VALUES ('0000041', '感染科', '人民医院');
INSERT INTO `科室` VALUES ('0000042', '老年公寓', '心脑医院');
INSERT INTO `科室` VALUES ('0000043', '幼儿园', '心脑医院');
INSERT INTO `科室` VALUES ('0000044', '门诊收费', '人民医院');
INSERT INTO `科室` VALUES ('0000045', '住院收费', '人民医院');
INSERT INTO `科室` VALUES ('0000046', '心脑收费', '心脑医院');
INSERT INTO `科室` VALUES ('0000047', '二院收费处(一)', '妇产医院');
INSERT INTO `科室` VALUES ('0000048', '医务处', '人民医院');
INSERT INTO `科室` VALUES ('0000049', '总护理部', '人民医院');
INSERT INTO `科室` VALUES ('0000050', '院感科', '人民医院');
INSERT INTO `科室` VALUES ('0000051', '办公室', '人民医院');
INSERT INTO `科室` VALUES ('0000052', '人事科', '人民医院');
INSERT INTO `科室` VALUES ('0000053', '财务科', '人民医院');
INSERT INTO `科室` VALUES ('0000054', '信息科', '人民医院');
INSERT INTO `科室` VALUES ('0000055', '器械科', '人民医院');
INSERT INTO `科室` VALUES ('0000056', '门诊部', '人民医院');
INSERT INTO `科室` VALUES ('0000057', '总务科', '人民医院');
INSERT INTO `科室` VALUES ('0000058', '司机班', '人民医院');
INSERT INTO `科室` VALUES ('0000059', '一分院', '人民医院');
INSERT INTO `科室` VALUES ('0000060', '四分院', '人民医院');
INSERT INTO `科室` VALUES ('0000061', '五分院', '人民医院');
INSERT INTO `科室` VALUES ('0000062', '普内科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000063', '普内2', '人民医院');
INSERT INTO `科室` VALUES ('0000064', '糖尿病门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000065', '总院外一科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000066', '泌尿科', '人民医院');
INSERT INTO `科室` VALUES ('0000067', '未使用的外一科', '人民医院');
INSERT INTO `科室` VALUES ('0000068', '总院外二科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000069', '总院脑外科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000070', '中医骨伤科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000071', '总院骨科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000072', '总院妇科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000073', '总院产科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000074', '总院儿科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000075', '肛肠科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000076', '眼科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000077', '耳鼻喉科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000078', '产科门诊', '妇产医院');
INSERT INTO `科室` VALUES ('0000079', '妇科门诊', '妇产医院');
INSERT INTO `科室` VALUES ('0000080', '心内科门诊', '心脑医院');
INSERT INTO `科室` VALUES ('0000081', '脑血管科门诊', '心脑医院');
INSERT INTO `科室` VALUES ('0000082', '心理咨询门诊', '心脑医院');
INSERT INTO `科室` VALUES ('0000083', '脑血管科康复', '心脑医院');
INSERT INTO `科室` VALUES ('0000084', '急诊科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000085', '口腔科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000086', '中医科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000087', '门诊药房', '人民医院');
INSERT INTO `科室` VALUES ('0000088', '住院药房', '人民医院');
INSERT INTO `科室` VALUES ('0000089', '二院体检中心', '妇产医院');
INSERT INTO `科室` VALUES ('0000090', '口腔科药房', '人民医院');
INSERT INTO `科室` VALUES ('0000091', '中医科药房', '人民医院');
INSERT INTO `科室` VALUES ('0000092', '药库药房', '人民医院');
INSERT INTO `科室` VALUES ('0000093', '心脑康复', '心脑医院');
INSERT INTO `科室` VALUES ('0000094', '心脑氧舱', '心脑医院');
INSERT INTO `科室` VALUES ('0000095', '政府医务室', '人民医院');
INSERT INTO `科室` VALUES ('0000096', 'CT室', '人民医院');
INSERT INTO `科室` VALUES ('0000097', '核磁室', '人民医院');
INSERT INTO `科室` VALUES ('0000098', 'CT室', '人民医院');
INSERT INTO `科室` VALUES ('0000099', '虚拟药库', '人民医院');
INSERT INTO `科室` VALUES ('0000100', '虚拟科室（心脑）', '心脑医院');
INSERT INTO `科室` VALUES ('0000101', '虚拟科室（妇产）', '妇产医院');
INSERT INTO `科室` VALUES ('0000102', '虚拟科室（人民）', '人民医院');
INSERT INTO `科室` VALUES ('0000103', '中心供氧', '人民医院');
INSERT INTO `科室` VALUES ('0000104', '心脑中心供氧', '心脑医院');
INSERT INTO `科室` VALUES ('0000105', '二院中心供氧', '妇产医院');
INSERT INTO `科室` VALUES ('0000106', '心内科二病区', '心脑医院');
INSERT INTO `科室` VALUES ('0000107', '普内科三病区', '人民医院');
INSERT INTO `科室` VALUES ('0000108', '产科二病区', '妇产医院');
INSERT INTO `科室` VALUES ('0000109', '儿科门诊', '儿科');
INSERT INTO `科室` VALUES ('0000110', '二院急诊科门诊', '妇产医院');
INSERT INTO `科室` VALUES ('0000111', '儿科', '儿科');
INSERT INTO `科室` VALUES ('0000112', '二院急诊科', '妇产医院');
INSERT INTO `科室` VALUES ('0000113', '二院收费处(二)', '儿科');
INSERT INTO `科室` VALUES ('0000114 ', '二院药房(二)', '儿科');
INSERT INTO `科室` VALUES ('0000115 ', '二院检验科(二)', '儿科');
INSERT INTO `科室` VALUES ('0000116', '二院心电图室', '妇产医院');
INSERT INTO `科室` VALUES ('0000117', '二院骨密度室', '妇产医院');
INSERT INTO `科室` VALUES ('0000118', '二院手术室(二)', '二院外科');
INSERT INTO `科室` VALUES ('0000119', '二院药房(三)', '二院外科');
INSERT INTO `科室` VALUES ('0000120', '二院收费处(三)', '二院外科');
INSERT INTO `科室` VALUES ('0000121', '外二科', '二院外科');
INSERT INTO `科室` VALUES ('0000122', '妇科', '二院外科');
INSERT INTO `科室` VALUES ('0000123', '骨科', '二院外科');
INSERT INTO `科室` VALUES ('0000124', '外一科', '二院外科');
INSERT INTO `科室` VALUES ('0000125', '脑外科', '二院外科');
INSERT INTO `科室` VALUES ('0000126', '外二科门诊', '妇产医院');
INSERT INTO `科室` VALUES ('0000127', '外一科门诊', '妇产医院');
INSERT INTO `科室` VALUES ('0000128', '骨科门诊', '妇产医院');
INSERT INTO `科室` VALUES ('0000129', '脑外科门诊', '妇产医院');
INSERT INTO `科室` VALUES ('0000130', '二院CT室', '妇产医院');
INSERT INTO `科室` VALUES ('0000131', '普内科二病区', '人民医院');
INSERT INTO `科室` VALUES ('0000132', '儿童耳鼻喉科门诊', '儿科');
INSERT INTO `科室` VALUES ('0000133', '二院药库', '妇产医院');
INSERT INTO `科室` VALUES ('0000134', '儿科(新生儿监护室)', '儿科');
INSERT INTO `科室` VALUES ('0000135', '新院区总务科', '人民医院');
INSERT INTO `科室` VALUES ('0000136', '心脑院区总务科', '心脑医院');
INSERT INTO `科室` VALUES ('0000137', '总院心内科', '人民医院');
INSERT INTO `科室` VALUES ('0000138', '总院心内科门诊', '人民医院');
INSERT INTO `科室` VALUES ('0000139', '信息化管理中心', 'NULL');
INSERT INTO `科室` VALUES ('0000140', '专家公寓', '二院');
INSERT INTO `科室` VALUES ('0000141', '食堂', '二院');

-- ----------------------------
-- Table structure for 设备
-- ----------------------------
DROP TABLE IF EXISTS `设备`;
CREATE TABLE `设备` (
  `器械编码` varchar(10) NOT NULL,
  `器械名称` varchar(20) NOT NULL,
  `管理终端` varchar(20) NOT NULL,
  `科室编号` varchar(20) NOT NULL,
  `科室名称` varchar(20) NOT NULL,
  `院区` varchar(20) NOT NULL,
  PRIMARY KEY (`器械编码`,`管理终端`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

-- ----------------------------
-- Records of 设备
-- ----------------------------
INSERT INTO `设备` VALUES ('CT_001', 'CT机', '192.168.122.3', '0000096', 'CT室', '人民医院');

-- ----------------------------
-- Table structure for 项目
-- ----------------------------
DROP TABLE IF EXISTS `项目`;
CREATE TABLE `项目` (
  `院区` varchar(20) NOT NULL,
  `项目编号` varchar(20) NOT NULL,
  `项目名称` varchar(20) NOT NULL,
  `项目编码` varchar(4) NOT NULL,
  `执行科室编号` varchar(20) NOT NULL,
  PRIMARY KEY (`项目编号`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 项目
-- ----------------------------
INSERT INTO `项目` VALUES ('01', '100', '小腿MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '101', '上臂MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '102', '前臂MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '103', '上腹部MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '104', '盆腔MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '105', '头颅MRA', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '106', 'CT增强扫描', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '10601', 'CT增强扫描', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '10602', 'CT增强扫描', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '107', '鼻窦横断+冠位CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '10701', '鼻窦横断+冠位CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '10702', '鼻窦横断+冠位CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '108', '颈部MRA', 'HC', '0000097');
INSERT INTO `项目` VALUES ('02', '1101', '妇科彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '111', '腰骶正侧片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '11101', '腰骶正侧片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '11102', '腰骶正侧片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '112', '骶椎正侧片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '11201', '骶椎正侧片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '11202', '骶椎正侧片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '113', '骶尾正侧片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '11301', '骶尾正侧片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '11302', '骶尾正侧片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '114', '头颅正侧片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '11401', '头颅正侧片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '11402', '头颅正侧片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '116', '胸部正侧位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '11601', '胸部正侧位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '11602', '胸部正侧位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '118', '跟骨侧轴位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '11801', '跟骨侧轴位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '11802', '跟骨侧轴位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '119', '踝关节片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '11901', '踝关节片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '11902', '踝关节片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '120', '膝关节片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '12001', '膝关节片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '12002', '膝关节片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('02', '1201', '产科彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '121', '足正斜片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '12101', '足正斜片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '12102', '足正斜片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '122', '胫腓骨片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '12201', '胫腓骨片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '12202', '胫腓骨片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '123', '髋关节片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '12301', '髋关节片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '12302', '髋关节片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '125', '骶髂关节片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '12501', '骶髂关节片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '12502', '骶髂关节片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '126', '胸骨正侧位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '12601', '胸骨正侧位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '12602', '胸骨正侧位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '127', '手正斜位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '12701', '手正斜位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '12702', '手正斜位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '128', '腕关节正侧位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '12801', '腕关节正侧位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '12802', '腕关节正侧位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '129', '股骨中上段片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '12901', '股骨中上段片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '12902', '股骨中上段片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '130', '副鼻窦瓦氏位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '13001', '副鼻窦瓦氏位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '13002', '副鼻窦瓦氏位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('02', '1301', '右下腹彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '132', '双乳突许氏位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '13201', '双乳突许氏位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '13202', '双乳突许氏位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '137', '腺样体片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '13701', '腺样体片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '13702', '腺样体片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '140', '前臂正侧位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '14001', '前臂正侧位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '14002', '前臂正侧位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('02', '1401', '泌尿系彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '141', '肱骨正侧位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '14101', '肱骨正侧位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '14102', '肱骨正侧位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '142', '肩关节正位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '14201', '肩关节正位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '14202', '肩关节正位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '143', '腹部正位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '14301', '腹部正位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '14302', '腹部正位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '144', '胸部（儿童）片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '14401', '胸部（儿童）片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '14402', '胸部（儿童）片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '146', '骨盆正位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '14601', '骨盆正位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '14602', '骨盆正位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '147', '股骨中下段片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '14701', '股骨中下段片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '14702', '股骨中下段片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '148', '食道造影', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '14801', '食道造影', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '14802', '食道造影', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '149', '上消化道造影', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '14901', '上消化道造影', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '14902', '上消化道造影', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '150', '钡灌肠', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '15001', '钡灌肠', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '15002', '钡灌肠', 'FS', '0000038');
INSERT INTO `项目` VALUES ('02', '1501', '肝胆胰脾双肾彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '151', 'T管造影', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '15101', 'T管造影', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '15102', 'T管造影', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '152', '静脉泌尿系造影', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '15201', '静脉泌尿系造影', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '15202', '静脉泌尿系造影', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '153', '胸透', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '15301', '胸透', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '15302', '胸透', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '154', '腹透', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '15401', '腹透', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '15402', '腹透', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '155', '动脉系统检查', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '15501', '动脉系统检查', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '15502', '动脉系统检查', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '156', '子宫输卵管造影', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '15601', '子宫输卵管造影', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '15602', '子宫输卵管造影', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '158', '普通床旁摄片(CR)', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '15801', '普通床旁摄片(CR)', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '15802', '普通床旁摄片(CR)', 'FS', '0000038');
INSERT INTO `项目` VALUES ('02', '1601', '胸部彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '1701', '彩超(碎石后复查)', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '1801', '门脉高压症', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '1901', '颈部血管超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '2001', '甲状腺超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '201', '临床操作的彩色多普勒超声引导', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '2101', '乳腺超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '2201', '双眼超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '2301', '阴囊睾丸血管超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '2401', '体表包块彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '2501', '心脏彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '2601', '阴茎彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '2801', '下腔静脉彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '2901', '腹主动脉彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '301', '体外碎石（第一次）', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '318', '体部CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '31801', '体部CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('01', '320', '磁共振平扫', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '321', '磁共振血管成象(MRA)', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '322', '喉CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '32201', '喉CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '32202', '喉CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('02', '32701', '临床操作的腔内B超引导', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '32901', '左侧上肢血管超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '341', '胸腰段正侧位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '34101', '胸腰段正侧位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '34102', '胸腰段正侧位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '343', '肘关节正侧位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '34301', '肘关节正侧位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '34302', '肘关节正侧位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '344', '头颅MRV', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '345', '颈部MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '360', '颈椎正侧位+双斜片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '3601', '左侧下肢血管超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '362', '颈椎正侧位+双斜片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '364', '颈椎正侧位+双斜片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '367', '全消造影', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '368', '全消造影', 'FS', '0000037');
INSERT INTO `项目` VALUES ('02', '369', '泌尿系+肾动脉彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('03', '370', '全消造影', 'FS', '0000038');
INSERT INTO `项目` VALUES ('02', '373', '半价彩超', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '379', '双侧锁骨下动脉彩色超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '382', '小儿腹部彩超', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '401', '体外碎石（第二次）', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '406', '右侧上肢血管超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '408', '右侧下肢血管超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '410', '双侧上肢血管超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '412', '双侧下肢血管超声', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '424', '磁共振平扫(同时增强扫描)', 'HC', '0000097');
INSERT INTO `项目` VALUES ('02', '426', '无菌耦合剂、医用胶片', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '433', '阴道彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '439', '直肠彩色超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '44', '肩胛骨正切位片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '4401', '肩胛骨正切位片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '4402', '肩胛骨正切位片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('02', '443', '腔内彩色多普勒超声检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '446', '肌骨超声彩色多普勒检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '449', '动脉弹性血管跟踪检查', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '45', '眼眶CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '4501', '眼眶CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '4502', '眼眶CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('02', '451', '院际主任医师会诊', 'CS', '0000039');
INSERT INTO `项目` VALUES ('02', '454', '经颅及周身血管多普勒', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '46', '胸椎正侧片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '4601', '胸椎正侧片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '4602', '胸椎正侧片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('02', '469', '产科彩色超声检查(双胎)', 'CS', '0000039');
INSERT INTO `项目` VALUES ('01', '472', '磁共振增强扫描', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '48', '腰椎正侧片', 'FS', '0000021');
INSERT INTO `项目` VALUES ('02', '4801', '腰椎正侧片', 'FS', '0000037');
INSERT INTO `项目` VALUES ('03', '4802', '腰椎正侧片', 'FS', '0000038');
INSERT INTO `项目` VALUES ('01', '49', '颅脑CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '4901', '颅脑CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '4902', '颅脑CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '50', '鼻骨CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '5001', '鼻骨CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '5002', '鼻骨CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '51', '颧弓CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '5101', '颧弓CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '5102', '颧弓CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '52', '鼻窦CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '5201', '鼻窦CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '5202', '鼻窦CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '53', '上颌骨CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '5301', '上颌骨CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '5302', '上颌骨CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '54', '下颌骨CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '5401', '下颌骨CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '5402', '下颌骨CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '55', '颞下颌关节CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '5501', '颞下颌关节CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '5502', '颞下颌关节CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '56', '颞骨CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '5601', '颞骨CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '5602', '颞骨CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '57', '中耳乳突CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '5701', '中耳乳突CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '5702', '中耳乳突CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '58', '咽部CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '5801', '咽部CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '5802', '咽部CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '59', '腮腺CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '5901', '腮腺CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '5902', '腮腺CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '60', '颌下腺CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '6001', '颌下腺CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '6002', '颌下腺CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '61', '甲状腺CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '6101', '甲状腺CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '6102', '甲状腺CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '62', '颈部CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '6201', '颈部CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '6202', '颈部CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '63', '颈椎CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '6301', '颈椎CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '6302', '颈椎CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '64', '胸部CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '6401', '胸部CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '6402', '胸部CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '65', '胸骨CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '6501', '胸骨CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '6502', '胸骨CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '66', '上段胸椎CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '6601', '上段胸椎CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '6602', '上段胸椎CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '67', '下段胸椎CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '6701', '下段胸椎CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '6702', '下段胸椎CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '68', '胸腰段CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '6801', '胸腰段CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '6802', '胸腰段CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '69', '肩关节CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '6901', '肩关节CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '6902', '肩关节CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '70', '肘关节CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '7001', '肘关节CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '7002', '肘关节CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '71', '腕关节CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '7101', '腕关节CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '7102', '腕关节CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '72', '上腹部CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '7201', '上腹部CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '7202', '上腹部CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '73', '盆腔CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '7301', '盆腔CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '7302', '盆腔CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '74', '肾上腺CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '7401', '肾上腺CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '7402', '肾上腺CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '75', '下腹部CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '7501', '下腹部CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '7502', '下腹部CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '76', '腰椎间盘CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '7601', '腰椎间盘CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '7602', '腰椎间盘CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '77', '腰椎椎体CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '7701', '腰椎椎体CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '7702', '腰椎椎体CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '78', '骶尾椎CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '7801', '骶尾椎CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '7802', '骶尾椎CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '79', '髋关节CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '7901', '髋关节CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '7902', '髋关节CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '80', '骶髂关节CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '8001', '骶髂关节CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '8002', '骶髂关节CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '81', '足CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '8101', '足CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '8102', '足CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '82', '膝关节CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '8201', '膝关节CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '8202', '膝关节CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '83', '踝关节CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '8301', '踝关节CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '8302', '踝关节CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '84', '跟距关节CT', 'CT', '0000096');
INSERT INTO `项目` VALUES ('02', '8401', '跟距关节CT', 'CT', '0000037');
INSERT INTO `项目` VALUES ('03', '8402', '跟距关节CT', 'CT', '0000130');
INSERT INTO `项目` VALUES ('01', '85', '头颅MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '86', '眼眶MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '87', '垂体MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '88', '颈椎MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '89', '胸椎MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '90', '腰椎MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '91', '骶尾椎MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '92', '肩关节MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '93', '肘关节MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '94', '腕关节MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '95', '髋关节MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '96', '骶髂关节MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '97', '膝关节MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '98', '踝关节MRI', 'HC', '0000097');
INSERT INTO `项目` VALUES ('01', '99', '大腿MRI', 'HC', '0000097');

-- ----------------------------
-- Table structure for 项目全
-- ----------------------------
DROP TABLE IF EXISTS `项目全`;
CREATE TABLE `项目全` (
  `院区01人民02心脑03二院` varchar(20) NOT NULL,
  `项目编号` varchar(20) NOT NULL,
  `项目名称` varchar(20) NOT NULL,
  `执行科室编号` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of 项目全
-- ----------------------------
INSERT INTO `项目全` VALUES ('01', '2', '临床操作的彩色多普勒超声引导', '0000019');
INSERT INTO `项目全` VALUES ('01', '44', '肩胛骨正切位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '45', '眼眶CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '51', '颧弓CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '52', '鼻窦CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '53', '上颌骨CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '54', '下颌骨CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '55', '颞下颌关节CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '3', '体外碎石（第一次）', '0000019');
INSERT INTO `项目全` VALUES ('01', '4', '体外碎石（第二次）', '0000019');
INSERT INTO `项目全` VALUES ('01', '17', '彩超(碎石后复查)', '0000019');
INSERT INTO `项目全` VALUES ('01', '18', '门脉高压症', '0000019');
INSERT INTO `项目全` VALUES ('01', '20', '甲状腺超声', '0000019');
INSERT INTO `项目全` VALUES ('01', '21', '乳腺超声', '0000019');
INSERT INTO `项目全` VALUES ('01', '22', '双眼超声', '0000019');
INSERT INTO `项目全` VALUES ('01', '23', '阴囊睾丸血管超声', '0000019');
INSERT INTO `项目全` VALUES ('01', '24', '体表包块彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '25', '心脏彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '26', '阴茎彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '28', '下腔静脉彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '29', '腹主动脉彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '56', '颞骨CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '100', '小腿MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '101', '上臂MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '102', '前臂MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '103', '上腹部MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '104', '盆腔MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '111', '腰骶正侧片', '0000021');
INSERT INTO `项目全` VALUES ('01', '112', '骶椎正侧片', '0000021');
INSERT INTO `项目全` VALUES ('01', '122', '胫腓骨片', '0000021');
INSERT INTO `项目全` VALUES ('01', '125', '骶髂关节片', '0000021');
INSERT INTO `项目全` VALUES ('01', '126', '胸骨正侧位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '127', '手正斜位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '128', '腕关节正侧位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '129', '股骨中上段片', '0000021');
INSERT INTO `项目全` VALUES ('01', '130', '副鼻窦瓦氏位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '132', '双乳突许氏位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '141', '肱骨正侧位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '142', '肩关节正位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '143', '腹部正位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '144', '胸部（儿童）片', '0000021');
INSERT INTO `项目全` VALUES ('01', '344', '头颅MRV', '0000097');
INSERT INTO `项目全` VALUES ('01', '146', '骨盆正位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '147', '股骨中下段片', '0000021');
INSERT INTO `项目全` VALUES ('01', '148', '食道造影', '0000021');
INSERT INTO `项目全` VALUES ('01', '149', '上消化道造影', '0000021');
INSERT INTO `项目全` VALUES ('01', '152', '静脉泌尿系造影', '0000021');
INSERT INTO `项目全` VALUES ('01', '153', '胸透', '0000021');
INSERT INTO `项目全` VALUES ('01', '154', '腹透', '0000021');
INSERT INTO `项目全` VALUES ('01', '158', '普通床旁摄片(CR)', '0000021');
INSERT INTO `项目全` VALUES ('01', '320', '磁共振平扫', '0000097');
INSERT INTO `项目全` VALUES ('01', '321', '磁共振血管成象(MRA)', '0000097');
INSERT INTO `项目全` VALUES ('01', '105', '头颅MRA', '0000097');
INSERT INTO `项目全` VALUES ('01', '106', 'CT增强扫描', '0000096');
INSERT INTO `项目全` VALUES ('01', '107', '鼻窦横断+冠位CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '108', '颈部MRA', '0000097');
INSERT INTO `项目全` VALUES ('01', '116', '胸部正侧位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '150', '钡灌肠', '0000021');
INSERT INTO `项目全` VALUES ('01', '151', 'T管造影', '0000021');
INSERT INTO `项目全` VALUES ('01', '384', '门诊常规心电图', '0000022');
INSERT INTO `项目全` VALUES ('03', '396', '超声骨密度检测', '0000117');
INSERT INTO `项目全` VALUES ('01', '360', '颈椎正侧位+双斜片', '0000021');
INSERT INTO `项目全` VALUES ('03', '456', '耳纤维内窥镜检查(组)', '0000132');
INSERT INTO `项目全` VALUES ('01', '19', '颈部血管超声', '0000019');
INSERT INTO `项目全` VALUES ('01', '85', '头颅MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '86', '眼眶MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '87', '垂体MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '88', '颈椎MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '89', '胸椎MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '90', '腰椎MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '91', '骶尾椎MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '92', '肩关节MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '93', '肘关节MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '94', '腕关节MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '95', '髋关节MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '96', '骶髂关节MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '97', '膝关节MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '98', '踝关节MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '99', '大腿MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '119', '踝关节片', '0000021');
INSERT INTO `项目全` VALUES ('01', '120', '膝关节片', '0000021');
INSERT INTO `项目全` VALUES ('01', '123', '髋关节片', '0000021');
INSERT INTO `项目全` VALUES ('01', '318', '体部CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '322', '喉CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '327', '临床操作的腔内B超引导', '0000019');
INSERT INTO `项目全` VALUES ('01', '468', '产科彩色超声检查(双胎)', '0000019');
INSERT INTO `项目全` VALUES ('01', '329', '左侧上肢血管超声', '0000019');
INSERT INTO `项目全` VALUES ('01', '345', '颈部MRI', '0000097');
INSERT INTO `项目全` VALUES ('01', '425', '无菌耦合剂、医用胶片', '0000019');
INSERT INTO `项目全` VALUES ('01', '30', '无痛苦胃镜', '0000024');
INSERT INTO `项目全` VALUES ('02', '362', '颈椎正侧位+双斜片', '0000037');
INSERT INTO `项目全` VALUES ('03', '364', '颈椎正侧位+双斜片', '0000038');
INSERT INTO `项目全` VALUES ('02', '368', '全消造影', '0000037');
INSERT INTO `项目全` VALUES ('02', '369', '泌尿系+肾动脉彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('01', '472', '磁共振增强扫描', '0000097');
INSERT INTO `项目全` VALUES ('01', '341', '胸腰段正侧位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '343', '肘关节正侧位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '113', '骶尾正侧片', '0000021');
INSERT INTO `项目全` VALUES ('01', '11', '妇科彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '12', '产科彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '13', '右下腹彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '14', '泌尿系彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '15', '肝胆胰脾双肾彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '16', '胸部彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '140', '前臂正侧位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '1', '纤维胃十二指肠镜检查（电子镜）', '0000024');
INSERT INTO `项目全` VALUES ('01', '50', '鼻骨CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '74', '肾上腺CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '75', '下腹部CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '76', '腰椎间盘CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '77', '腰椎椎体CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '78', '骶尾椎CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '114', '头颅正侧片', '0000021');
INSERT INTO `项目全` VALUES ('01', '31', '纤维结肠镜检查（电子镜）', '0000024');
INSERT INTO `项目全` VALUES ('01', '35', '四维彩超拍片', '0000019');
INSERT INTO `项目全` VALUES ('01', '36', '左侧下肢血管超声', '0000019');
INSERT INTO `项目全` VALUES ('01', '46', '胸椎正侧片', '0000021');
INSERT INTO `项目全` VALUES ('01', '48', '腰椎正侧片', '0000021');
INSERT INTO `项目全` VALUES ('01', '49', '颅脑CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '57', '中耳乳突CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '58', '咽部CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '59', '腮腺CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '60', '颌下腺CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '61', '甲状腺CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '62', '颈部CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '63', '颈椎CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '64', '胸部CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '65', '胸骨CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '66', '上段胸椎CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '67', '下段胸椎CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '68', '胸腰段CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '69', '肩关节CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '70', '肘关节CT', '0000096');
INSERT INTO `项目全` VALUES ('03', '370', '全消造影', '0000038');
INSERT INTO `项目全` VALUES ('03', '371', '泌尿系+肾动脉彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('01', '372', '半价彩超', '0000019');
INSERT INTO `项目全` VALUES ('02', '373', '半价彩超', '0000039');
INSERT INTO `项目全` VALUES ('03', '374', '半价彩超', '0000040');
INSERT INTO `项目全` VALUES ('01', '71', '腕关节CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '72', '上腹部CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '73', '盆腔CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '79', '髋关节CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '80', '骶髂关节CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '81', '足CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '82', '膝关节CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '83', '踝关节CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '84', '跟距关节CT', '0000096');
INSERT INTO `项目全` VALUES ('01', '118', '跟骨侧轴位片', '0000021');
INSERT INTO `项目全` VALUES ('01', '121', '足正斜片', '0000021');
INSERT INTO `项目全` VALUES ('01', '137', '腺样体片', '0000021');
INSERT INTO `项目全` VALUES ('01', '155', '动脉系统检查', '0000021');
INSERT INTO `项目全` VALUES ('01', '156', '子宫输卵管造影', '0000021');
INSERT INTO `项目全` VALUES ('02', '4401', '肩胛骨正切位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '4501', '眼眶CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '5101', '颧弓CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '5201', '鼻窦CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '5301', '上颌骨CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '5401', '下颌骨CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '5501', '颞下颌关节CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '5601', '颞骨CT', '0000037');
INSERT INTO `项目全` VALUES ('01', '431', '阴道彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('02', '11101', '腰骶正侧片', '0000037');
INSERT INTO `项目全` VALUES ('02', '11201', '骶椎正侧片', '0000037');
INSERT INTO `项目全` VALUES ('02', '12201', '胫腓骨片', '0000037');
INSERT INTO `项目全` VALUES ('02', '12501', '骶髂关节片', '0000037');
INSERT INTO `项目全` VALUES ('02', '12601', '胸骨正侧位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '12701', '手正斜位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '12801', '腕关节正侧位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '12901', '股骨中上段片', '0000037');
INSERT INTO `项目全` VALUES ('02', '13001', '副鼻窦瓦氏位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '13201', '双乳突许氏位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '14101', '肱骨正侧位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '14201', '肩关节正位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '14301', '腹部正位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '14401', '胸部（儿童）片', '0000037');
INSERT INTO `项目全` VALUES ('02', '14601', '骨盆正位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '14701', '股骨中下段片', '0000037');
INSERT INTO `项目全` VALUES ('02', '14801', '食道造影', '0000037');
INSERT INTO `项目全` VALUES ('02', '14901', '上消化道造影', '0000037');
INSERT INTO `项目全` VALUES ('02', '15201', '静脉泌尿系造影', '0000037');
INSERT INTO `项目全` VALUES ('02', '15301', '胸透', '0000037');
INSERT INTO `项目全` VALUES ('02', '15401', '腹透', '0000037');
INSERT INTO `项目全` VALUES ('02', '15801', '普通床旁摄片(CR)', '0000037');
INSERT INTO `项目全` VALUES ('02', '10601', 'CT增强扫描', '0000037');
INSERT INTO `项目全` VALUES ('02', '10701', '鼻窦横断+冠位CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '11601', '胸部正侧位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '15001', '钡灌肠', '0000037');
INSERT INTO `项目全` VALUES ('02', '15101', 'T管造影', '0000037');
INSERT INTO `项目全` VALUES ('01', '381', '小儿腹部彩超', '0000019');
INSERT INTO `项目全` VALUES ('02', '11901', '踝关节片', '0000037');
INSERT INTO `项目全` VALUES ('02', '12001', '膝关节片', '0000037');
INSERT INTO `项目全` VALUES ('02', '12301', '髋关节片', '0000037');
INSERT INTO `项目全` VALUES ('02', '31801', '体部CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '32201', '喉CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '1901', '颈部血管超声', '0000039');
INSERT INTO `项目全` VALUES ('02', '32701', '临床操作的腔内B超引导', '0000039');
INSERT INTO `项目全` VALUES ('02', '32901', '左侧上肢血管超声', '0000039');
INSERT INTO `项目全` VALUES ('02', '1101', '妇科彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('02', '1201', '产科彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('02', '1301', '右下腹彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('02', '1401', '泌尿系彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('02', '1501', '肝胆胰脾双肾彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('02', '1601', '胸部彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('02', '3601', '左侧下肢血管超声', '0000039');
INSERT INTO `项目全` VALUES ('03', '4402', '肩胛骨正切位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '4502', '眼眶CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '5102', '颧弓CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '5202', '鼻窦CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '5302', '上颌骨CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '5402', '下颌骨CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '5502', '颞下颌关节CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '5602', '颞骨CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '11102', '腰骶正侧片', '0000038');
INSERT INTO `项目全` VALUES ('03', '11202', '骶椎正侧片', '0000038');
INSERT INTO `项目全` VALUES ('03', '12202', '胫腓骨片', '0000038');
INSERT INTO `项目全` VALUES ('03', '12502', '骶髂关节片', '0000038');
INSERT INTO `项目全` VALUES ('03', '12602', '胸骨正侧位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '12702', '手正斜位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '12802', '腕关节正侧位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '12902', '股骨中上段片', '0000038');
INSERT INTO `项目全` VALUES ('03', '13002', '副鼻窦瓦氏位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '13202', '双乳突许氏位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '14102', '肱骨正侧位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '14202', '肩关节正位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '14302', '腹部正位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '14402', '胸部（儿童）片', '0000038');
INSERT INTO `项目全` VALUES ('03', '14602', '骨盆正位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '14702', '股骨中下段片', '0000038');
INSERT INTO `项目全` VALUES ('03', '14802', '食道造影', '0000038');
INSERT INTO `项目全` VALUES ('03', '14902', '上消化道造影', '0000038');
INSERT INTO `项目全` VALUES ('03', '15202', '静脉泌尿系造影', '0000038');
INSERT INTO `项目全` VALUES ('03', '15302', '胸透', '0000038');
INSERT INTO `项目全` VALUES ('03', '15402', '腹透', '0000038');
INSERT INTO `项目全` VALUES ('03', '15802', '普通床旁摄片(CR)', '0000038');
INSERT INTO `项目全` VALUES ('03', '10602', 'CT增强扫描', '0000130');
INSERT INTO `项目全` VALUES ('03', '10702', '鼻窦横断+冠位CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '11602', '胸部正侧位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '15002', '钡灌肠', '0000038');
INSERT INTO `项目全` VALUES ('03', '15102', 'T管造影', '0000038');
INSERT INTO `项目全` VALUES ('03', '11902', '踝关节片', '0000038');
INSERT INTO `项目全` VALUES ('03', '12002', '膝关节片', '0000038');
INSERT INTO `项目全` VALUES ('03', '12302', '髋关节片', '0000038');
INSERT INTO `项目全` VALUES ('03', '32202', '喉CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '34102', '胸腰段正侧位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '34302', '肘关节正侧位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '11302', '骶尾正侧片', '0000038');
INSERT INTO `项目全` VALUES ('03', '14002', '前臂正侧位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '5002', '鼻骨CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '7402', '肾上腺CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '7502', '下腹部CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '7602', '腰椎间盘CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '7702', '腰椎椎体CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '7802', '骶尾椎CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '11402', '头颅正侧片', '0000038');
INSERT INTO `项目全` VALUES ('03', '4602', '胸椎正侧片', '0000038');
INSERT INTO `项目全` VALUES ('03', '4802', '腰椎正侧片', '0000038');
INSERT INTO `项目全` VALUES ('03', '4902', '颅脑CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '5702', '中耳乳突CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '5802', '咽部CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '5902', '腮腺CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '6002', '颌下腺CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '6102', '甲状腺CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '6202', '颈部CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '6302', '颈椎CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '6402', '胸部CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '6502', '胸骨CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '6602', '上段胸椎CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '6702', '下段胸椎CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '6802', '胸腰段CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '6902', '肩关节CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '7002', '肘关节CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '7102', '腕关节CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '7202', '上腹部CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '7302', '盆腔CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '7902', '髋关节CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '8002', '骶髂关节CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '8102', '足CT', '0000130');
INSERT INTO `项目全` VALUES ('02', '34101', '胸腰段正侧位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '34301', '肘关节正侧位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '11301', '骶尾正侧片', '0000037');
INSERT INTO `项目全` VALUES ('02', '14001', '前臂正侧位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '5001', '鼻骨CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '7401', '肾上腺CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '7501', '下腹部CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '7601', '腰椎间盘CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '7701', '腰椎椎体CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '7801', '骶尾椎CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '11401', '头颅正侧片', '0000037');
INSERT INTO `项目全` VALUES ('02', '4601', '胸椎正侧片', '0000037');
INSERT INTO `项目全` VALUES ('02', '4801', '腰椎正侧片', '0000037');
INSERT INTO `项目全` VALUES ('02', '4901', '颅脑CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '5701', '中耳乳突CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '5801', '咽部CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '5901', '腮腺CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '6001', '颌下腺CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '6101', '甲状腺CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '6201', '颈部CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '6301', '颈椎CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '6401', '胸部CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '6501', '胸骨CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '6601', '上段胸椎CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '6701', '下段胸椎CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '6801', '胸腰段CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '6901', '肩关节CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '7001', '肘关节CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '7101', '腕关节CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '7201', '上腹部CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '7301', '盆腔CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '7901', '髋关节CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '8001', '骶髂关节CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '8101', '足CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '8201', '膝关节CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '8301', '踝关节CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '8401', '跟距关节CT', '0000037');
INSERT INTO `项目全` VALUES ('02', '11801', '跟骨侧轴位片', '0000037');
INSERT INTO `项目全` VALUES ('02', '12101', '足正斜片', '0000037');
INSERT INTO `项目全` VALUES ('02', '13701', '腺样体片', '0000037');
INSERT INTO `项目全` VALUES ('02', '15501', '动脉系统检查', '0000037');
INSERT INTO `项目全` VALUES ('02', '15601', '子宫输卵管造影', '0000037');
INSERT INTO `项目全` VALUES ('02', '201', '临床操作的彩色多普勒超声引导', '0000039');
INSERT INTO `项目全` VALUES ('02', '301', '体外碎石（第一次）', '0000039');
INSERT INTO `项目全` VALUES ('02', '401', '体外碎石（第二次）', '0000039');
INSERT INTO `项目全` VALUES ('02', '1701', '彩超(碎石后复查)', '0000039');
INSERT INTO `项目全` VALUES ('02', '1801', '门脉高压症', '0000039');
INSERT INTO `项目全` VALUES ('02', '2001', '甲状腺超声', '0000039');
INSERT INTO `项目全` VALUES ('02', '2101', '乳腺超声', '0000039');
INSERT INTO `项目全` VALUES ('02', '2201', '双眼超声', '0000039');
INSERT INTO `项目全` VALUES ('02', '2301', '阴囊睾丸血管超声', '0000039');
INSERT INTO `项目全` VALUES ('02', '2401', '体表包块彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('02', '2501', '心脏彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('02', '2601', '阴茎彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('01', '464', '内镜下食道染色', '0000024');
INSERT INTO `项目全` VALUES ('02', '2801', '下腔静脉彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('02', '2901', '腹主动脉彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('03', '8202', '膝关节CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '8302', '踝关节CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '8402', '跟距关节CT', '0000130');
INSERT INTO `项目全` VALUES ('03', '11802', '跟骨侧轴位片', '0000038');
INSERT INTO `项目全` VALUES ('03', '12102', '足正斜片', '0000038');
INSERT INTO `项目全` VALUES ('03', '13702', '腺样体片', '0000038');
INSERT INTO `项目全` VALUES ('03', '15502', '动脉系统检查', '0000038');
INSERT INTO `项目全` VALUES ('03', '15602', '子宫输卵管造影', '0000038');
INSERT INTO `项目全` VALUES ('03', '202', '临床操作的彩色多普勒超声引导', '0000040');
INSERT INTO `项目全` VALUES ('03', '302', '体外碎石（第一次）', '0000040');
INSERT INTO `项目全` VALUES ('03', '402', '体外碎石（第二次）', '0000040');
INSERT INTO `项目全` VALUES ('01', '465', '内镜下药物注射', '0000024');
INSERT INTO `项目全` VALUES ('03', '1702', '彩超(碎石后复查)', '0000040');
INSERT INTO `项目全` VALUES ('03', '1802', '门脉高压症', '0000040');
INSERT INTO `项目全` VALUES ('03', '2002', '甲状腺超声', '0000040');
INSERT INTO `项目全` VALUES ('03', '2102', '乳腺超声', '0000040');
INSERT INTO `项目全` VALUES ('03', '2202', '双眼超声', '0000040');
INSERT INTO `项目全` VALUES ('03', '2302', '阴囊睾丸血管超声', '0000040');
INSERT INTO `项目全` VALUES ('03', '2402', '体表包块彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('03', '2502', '心脏彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('03', '2602', '阴茎彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('01', '466', '内镜下活检采样', '0000024');
INSERT INTO `项目全` VALUES ('03', '2802', '下腔静脉彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('03', '2902', '腹主动脉彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('03', '1902', '颈部血管超声', '0000040');
INSERT INTO `项目全` VALUES ('03', '32702', '临床操作的腔内B超引导', '0000040');
INSERT INTO `项目全` VALUES ('03', '32902', '左侧上肢血管超声', '0000040');
INSERT INTO `项目全` VALUES ('03', '1102', '妇科彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('03', '1202', '产科彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('03', '1302', '右下腹彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('03', '1402', '泌尿系彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('03', '1502', '肝胆胰脾双肾彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('03', '1602', '胸部彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('03', '3502', '四维彩超拍片', '0000040');
INSERT INTO `项目全` VALUES ('03', '3602', '左侧下肢血管超声', '0000040');
INSERT INTO `项目全` VALUES ('01', '385', '住院心电图', '0000022');
INSERT INTO `项目全` VALUES ('03', '377', '高危人乳头瘤病毒HPV-DNA检测', '0000025');
INSERT INTO `项目全` VALUES ('01', '378', '双侧锁骨下动脉彩色超声', '0000019');
INSERT INTO `项目全` VALUES ('02', '379', '双侧锁骨下动脉彩色超声', '0000039');
INSERT INTO `项目全` VALUES ('03', '380', '双侧锁骨下动脉彩色超声', '0000040');
INSERT INTO `项目全` VALUES ('02', '382', '小儿腹部彩超', '0000039');
INSERT INTO `项目全` VALUES ('03', '383', '小儿腹部彩超', '0000040');
INSERT INTO `项目全` VALUES ('01', '387', '心电综合检查', '0000022');
INSERT INTO `项目全` VALUES ('01', '390', '动态心电图(十二导)', '0000022');
INSERT INTO `项目全` VALUES ('01', '402', '右侧下肢血管超声', '0000019');
INSERT INTO `项目全` VALUES ('01', '404', '双侧下肢血管超声', '0000019');
INSERT INTO `项目全` VALUES ('02', '406', '右侧上肢血管超声', '0000039');
INSERT INTO `项目全` VALUES ('02', '408', '右侧下肢血管超声', '0000039');
INSERT INTO `项目全` VALUES ('02', '410', '双侧上肢血管超声', '0000039');
INSERT INTO `项目全` VALUES ('02', '412', '双侧下肢血管超声', '0000039');
INSERT INTO `项目全` VALUES ('03', '414', '右侧下肢血管超声', '0000040');
INSERT INTO `项目全` VALUES ('03', '416', '双侧下肢血管超声', '0000040');
INSERT INTO `项目全` VALUES ('03', '418', '右侧上肢血管超声', '0000040');
INSERT INTO `项目全` VALUES ('03', '420', '双侧上肢血管超声', '0000040');
INSERT INTO `项目全` VALUES ('01', '422', '急诊心电图', '0000022');
INSERT INTO `项目全` VALUES ('03', '423', '急诊心电图', '0000116');
INSERT INTO `项目全` VALUES ('02', '426', '无菌耦合剂、医用胶片', '0000039');
INSERT INTO `项目全` VALUES ('03', '427', '无菌耦合剂、医用胶片', '0000040');
INSERT INTO `项目全` VALUES ('03', '457', '纤维鼻咽镜检查(组)', '0000132');
INSERT INTO `项目全` VALUES ('02', '469', '产科彩色超声检查(双胎)', '0000039');
INSERT INTO `项目全` VALUES ('02', '433', '阴道彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('03', '435', '阴道彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('01', '437', '直肠彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('02', '439', '直肠彩色超声检查', '0000039');
INSERT INTO `项目全` VALUES ('03', '441', '直肠彩色超声检查', '0000040');
INSERT INTO `项目全` VALUES ('01', '445', '肌骨超声彩色多普勒检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '451', '院际主任医师会诊', '0000019');
INSERT INTO `项目全` VALUES ('02', '451', '院际主任医师会诊', '0000039');
INSERT INTO `项目全` VALUES ('03', '452', '院际主任医师会诊', '0000040');
INSERT INTO `项目全` VALUES ('01', '453', '经颅及周身血管多普勒', '0000019');
INSERT INTO `项目全` VALUES ('02', '454', '经颅及周身血管多普勒', '0000039');
INSERT INTO `项目全` VALUES ('03', '455', '经颅及周身血管多普勒', '0000040');
INSERT INTO `项目全` VALUES ('03', '458', '纤维喉镜检查(电子镜)(组)', '0000132');
INSERT INTO `项目全` VALUES ('03', '471', '产科彩色超声检查(双胎)', '0000040');
INSERT INTO `项目全` VALUES ('01', '463', '内镜下异物取出术', '0000024');
INSERT INTO `项目全` VALUES ('03', '473', '胎儿生物物理相评分', '0000040');
INSERT INTO `项目全` VALUES ('01', '398', '右侧上肢血管超声', '0000019');
INSERT INTO `项目全` VALUES ('03', '447', '肌骨超声彩色多普勒检查', '0000040');
INSERT INTO `项目全` VALUES ('01', '459', '体外碎石(第三次)', '0000019');
INSERT INTO `项目全` VALUES ('01', '467', '内镜下良性肿物切除术', '0000024');
INSERT INTO `项目全` VALUES ('03', '469', '体外碎石（第三次）', '0000040');
INSERT INTO `项目全` VALUES ('01', '366', '泌尿系+肾动脉彩色超声检查', '0000019');
INSERT INTO `项目全` VALUES ('01', '367', '全消造影', '0000021');
INSERT INTO `项目全` VALUES ('03', '391', '门诊常规心电图', '0000116');
INSERT INTO `项目全` VALUES ('03', '393', '住院心电图', '0000116');
INSERT INTO `项目全` VALUES ('02', '449', '动脉弹性血管跟踪检查', '0000039');
INSERT INTO `项目全` VALUES ('03', '450', '动脉弹性血管跟踪检查', '0000040');
INSERT INTO `项目全` VALUES ('01', '401', '双侧上肢血管超声', '0000019');
INSERT INTO `项目全` VALUES ('01', '424', '磁共振平扫(同时增强扫描)', '0000097');
INSERT INTO `项目全` VALUES ('03', '428', '心电综合检查', '0000116');
INSERT INTO `项目全` VALUES ('03', '430', '动态心电图(十二导)', '0000116');
INSERT INTO `项目全` VALUES ('01', '442', '腔内彩色多普勒超声检查', '0000019');
INSERT INTO `项目全` VALUES ('02', '443', '腔内彩色多普勒超声检查', '0000039');
INSERT INTO `项目全` VALUES ('03', '444', '腔内彩色多普勒超声检查', '0000040');
INSERT INTO `项目全` VALUES ('02', '446', '肌骨超声彩色多普勒检查', '0000039');
INSERT INTO `项目全` VALUES ('01', '448', '动脉弹性血管跟踪检查', '0000019');
INSERT INTO `项目全` VALUES ('03', '470', '液基薄层细胞制片术', '0000025');
