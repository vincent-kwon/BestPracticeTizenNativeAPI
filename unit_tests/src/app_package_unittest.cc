/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <gtest/gtest.h>
#include <app_common.h>
#include <app_common_internal.h>

#include <iostream>
#include <memory>

#include "unit_tests/mock/pkgmgr-info.h"
#include "unit_tests/mock/aul.h"

extern int gargc;
extern char** gargv;

class AppPackageTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

static int __fake_aul_app_get_appid_bypid(int pid, char* appid,
    int size) {
  snprintf(appid, size, "%s", "org.tizen.helloworld");
  return AUL_R_OK;
}

static int __fake_pkgmgrinfo_appinfo_get_usr_appinfo(
    const char* appid, uid_t uid, pkgmgrinfo_appinfo_h* handle) {
  return PMINFO_R_OK;
}

static int __fake_pkgmgrinfo_appinfo_get_label(
    pkgmgrinfo_appinfo_h handle, char** label) {
  *label = const_cast<char*>("helloworld");
  return PMINFO_R_OK;
}

static int __fake_pkgmgrinfo_appinfo_get_pkgid(
    pkgmgrinfo_appinfo_h handle, char** pkgid) {
  *pkgid = const_cast<char*>("org.tizen.helloworld");
  return PMINFO_R_OK;
}

static int __fake_pkgmgrinfo_appinfo_destroy_appinfo(
    pkgmgrinfo_appinfo_h handle) {
  return PMINFO_R_OK;
}

static int __fake_pkgmgrinfo_pkginfo_get_pkginfo(const char* pkgid,
    pkgmgrinfo_pkginfo_h* handle) {
  return PMINFO_R_OK;
}

static int __fake_pkgmgrinfo_pkginfo_get_version(
    pkgmgrinfo_pkginfo_h handle, char** version) {
  *version = const_cast<char*>("5.5");
  return PMINFO_R_OK;
}

static int __fake_pkgmgrinfo_pkginfo_destroy_pkginfo(
    pkgmgrinfo_pkginfo_h handle) {
  return PMINFO_R_OK;
}

TEST_F(AppPackageTest, app_get_package_app_name_RETURN_NONE) {
  char* name = nullptr;
  int r = app_get_package_app_name("org.tizen.helloworld", &name);
  auto p = std::unique_ptr<char, decltype(std::free)*>(name, std::free);
  EXPECT_EQ(r, APP_ERROR_NONE);
  EXPECT_EQ(std::string(p.get()), "helloworld");
}

TEST_F(AppPackageTest, app_get_package_app_name_RETURN_INVALID_PARAMETER) {
  char* name = nullptr;
  int r = app_get_package_app_name(nullptr, &name);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);
  EXPECT_EQ(name, nullptr);
}

TEST_F(AppPackageTest, app_get_id_RETURN_NONE) {
  aul_app_get_appid_bypid_fake.custom_fake =
    __fake_aul_app_get_appid_bypid;

  char* id = nullptr;
  int r = app_get_id(&id);
  auto p = std::unique_ptr<char, decltype(std::free)*>(id, std::free);
  EXPECT_EQ(r, APP_ERROR_NONE);
  EXPECT_EQ(std::string(p.get()), "org.tizen.helloworld");
}

TEST_F(AppPackageTest, app_get_id_RETURN_INVALID_PARAMETER) {
  aul_app_get_appid_bypid_fake.custom_fake =
    __fake_aul_app_get_appid_bypid;

  int r = app_get_id(nullptr);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);
}

TEST_F(AppPackageTest, app_get_package) {
  char* package = nullptr;
  int r = app_get_package(&package);
  auto p = std::unique_ptr<char, decltype(std::free)*>(package, std::free);
  EXPECT_EQ(r, APP_ERROR_NONE);
  EXPECT_EQ(std::string(p.get()), "org.tizen.helloworld");
}

TEST_F(AppPackageTest, app_get_name) {
  pkgmgrinfo_appinfo_get_usr_appinfo_fake.custom_fake =
    __fake_pkgmgrinfo_appinfo_get_usr_appinfo;
  pkgmgrinfo_appinfo_get_label_fake.custom_fake =
    __fake_pkgmgrinfo_appinfo_get_label;
  pkgmgrinfo_appinfo_destroy_appinfo_fake.custom_fake =
    __fake_pkgmgrinfo_appinfo_destroy_appinfo;

  char* name = nullptr;
  int r = app_get_name(&name);
  auto p = std::unique_ptr<char, decltype(std::free)*>(name, std::free);
  EXPECT_EQ(r, APP_ERROR_NONE);
  EXPECT_EQ(std::string(p.get()), "helloworld");
}

TEST_F(AppPackageTest, app_get_version) {
  pkgmgrinfo_appinfo_get_usr_appinfo_fake.custom_fake =
    __fake_pkgmgrinfo_appinfo_get_usr_appinfo;
  pkgmgrinfo_appinfo_get_pkgid_fake.custom_fake =
    __fake_pkgmgrinfo_appinfo_get_pkgid;
  pkgmgrinfo_appinfo_destroy_appinfo_fake.custom_fake =
    __fake_pkgmgrinfo_appinfo_destroy_appinfo;
  pkgmgrinfo_pkginfo_get_pkginfo_fake.custom_fake =
    __fake_pkgmgrinfo_pkginfo_get_pkginfo;
  pkgmgrinfo_pkginfo_get_version_fake.custom_fake =
    __fake_pkgmgrinfo_pkginfo_get_version;
  pkgmgrinfo_pkginfo_destroy_pkginfo_fake.custom_fake =
    __fake_pkgmgrinfo_pkginfo_destroy_pkginfo;

  char* version = nullptr;
  int r = app_get_version(&version);
  auto p = std::unique_ptr<char, decltype(std::free)*>(version, std::free);
  EXPECT_EQ(r, APP_ERROR_NONE);
  EXPECT_EQ(std::string(p.get()), "5.5");
}
