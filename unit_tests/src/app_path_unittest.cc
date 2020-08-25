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

#include <iostream>
#include <memory>

#include "unit_tests/mock/aul.h"

extern int gargc;
extern char** gargv;

static const char DATA_PATH[] =
  "/opt/usr/home/owner/apps_rw/org.tizen.helloworld/data/";
static const char CACHE_PATH[] =
  "/opt/usr/home/owner/apps_rw/org.tizen.helloworld/cache/";
static const char RES_PATH[] =
  "/opt/usr/home/owner/apps_rw/org.tizen.helloworld/res/";
static const char SHARED_DATA_PATH[] =
  "/opt/usr/home/owner/apps_rw/org.tizen.helloworld/shared/data/";
static const char SHARED_RES_PATH[] =
  "/opt/usr/home/owner/apps_rw/org.tizen.helloworld/shared/res/";
static const char SHARED_TRUSTED_PATH[] =
  "/opt/usr/home/owner/apps_rw/org.tizen.helloworld/shared/trusted/";
static const char EXT_DATA_PATH[] =
  "/opt/media/sdcard/apps/owner/apps_rw/org.tizen.helloworld/data/";
static const char EXT_CACHE_PATH[] =
  "/opt/media/sdcard/apps/owner/apps_rw/org.tizen.helloworld/cache/";
static const char EXT_SHARED_DATA_PATH[] =
  "/opt/media/sdcard/apps/owner/apps_rw/org.tizen.helloworld/shared/data/";
static const char TEP_PATH[] =
  "/opt/usr/home/owner/apps_rw/org.tizen.helloworld/tep/mount/";

class AppPathTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

static const char* __fake_aul_get_app_data_path(void) {
  return DATA_PATH;
}

static const char* __fake_aul_get_app_cache_path(void) {
  return CACHE_PATH;
}

static const char* __fake_aul_get_app_resource_path(void) {
  return RES_PATH;
}

static int __fake_aul_get_app_shared_data_path_RETURN_OK(char** path) {
  *path = strdup(SHARED_DATA_PATH);
  return AUL_R_OK;
};

static int __fake_aul_get_app_shared_data_path_RETURN_EREJECTED(
    char** path) {
  return AUL_R_EREJECTED;
};

static int __fake_aul_get_app_shared_data_path_RETURN_ERROR(
    char** path) {
  return AUL_R_ERROR;
};

static const char* __fake_aul_get_app_shared_resource_path(void) {
  return SHARED_RES_PATH;
}

static const char* __fake_aul_get_app_shared_trusted_path(void) {
  return SHARED_TRUSTED_PATH;
}

static const char* __fake_aul_get_app_external_data_path(void) {
  return EXT_DATA_PATH;
}

static const char* __fake_aul_get_app_external_cache_path(void) {
  return EXT_CACHE_PATH;
}

static const char* __fake_aul_get_external_shared_data_path(void) {
  return EXT_SHARED_DATA_PATH;
}

static const char* __fake_aul_get_app_tep_resource_path(void) {
  return TEP_PATH;
}

TEST_F(AppPathTest, app_get_data_path) {
  aul_get_app_data_path_fake.custom_fake = __fake_aul_get_app_data_path;

  auto data_path = std::unique_ptr<char, decltype(std::free)*>(
      app_get_data_path(), std::free);
  EXPECT_EQ(std::string(data_path.get()), DATA_PATH);
}

TEST_F(AppPathTest, app_get_cache_path) {
  aul_get_app_cache_path_fake.custom_fake = __fake_aul_get_app_cache_path;

  auto cache_path = std::unique_ptr<char, decltype(std::free)*>(
      app_get_cache_path(), std::free);
  EXPECT_EQ(std::string(cache_path.get()), CACHE_PATH);
}

TEST_F(AppPathTest, app_get_resource_path) {
  aul_get_app_resource_path_fake.custom_fake = __fake_aul_get_app_resource_path;

  auto res_path = std::unique_ptr<char, decltype(std::free)*>(
      app_get_resource_path(), std::free);
  EXPECT_EQ(std::string(res_path.get()), RES_PATH);
}

TEST_F(AppPathTest, app_get_shared_data_path_RETURN_NONE) {
  aul_get_app_shared_data_path_fake.custom_fake =
    __fake_aul_get_app_shared_data_path_RETURN_OK;

  auto shared_data_path = std::unique_ptr<char, decltype(std::free)*>(
      app_get_shared_data_path(), std::free);
  EXPECT_EQ(get_last_result(), APP_ERROR_NONE);
  EXPECT_EQ(std::string(shared_data_path.get()), SHARED_DATA_PATH);
}

TEST_F(AppPathTest, app_get_shared_data_path_RETURN_PERMISSION_DENINED) {
  aul_get_app_shared_data_path_fake.custom_fake =
    __fake_aul_get_app_shared_data_path_RETURN_EREJECTED;

  auto* shared_data_path = app_get_shared_data_path();
  EXPECT_EQ(get_last_result(), APP_ERROR_PERMISSION_DENIED);
  EXPECT_EQ(shared_data_path, nullptr);
}

TEST_F(AppPathTest, app_get_shared_data_path_RETURN_OUT_OF_MEMORY) {
  aul_get_app_shared_data_path_fake.custom_fake =
    __fake_aul_get_app_shared_data_path_RETURN_ERROR;

  auto* shared_data_path = app_get_shared_data_path();
  EXPECT_EQ(get_last_result(), APP_ERROR_OUT_OF_MEMORY);
  EXPECT_EQ(shared_data_path, nullptr);
}

TEST_F(AppPathTest, app_get_shared_resource_path) {
  aul_get_app_shared_resource_path_fake.custom_fake =
    __fake_aul_get_app_shared_resource_path;

  auto shared_res_path = std::unique_ptr<char, decltype(std::free)*>(
      app_get_shared_resource_path(), std::free);
  EXPECT_EQ(std::string(shared_res_path.get()), SHARED_RES_PATH);
}

TEST_F(AppPathTest, app_get_shared_trusted_path) {
  aul_get_app_shared_trusted_path_fake.custom_fake =
    __fake_aul_get_app_shared_trusted_path;

  auto shared_trusted_path = std::unique_ptr<char, decltype(std::free)*>(
      app_get_shared_trusted_path(), std::free);
  EXPECT_EQ(std::string(shared_trusted_path.get()), SHARED_TRUSTED_PATH);
}

TEST_F(AppPathTest, app_get_external_data_path) {
  aul_get_app_external_data_path_fake.custom_fake =
    __fake_aul_get_app_external_data_path;

  auto ext_data_path = std::unique_ptr<char, decltype(std::free)*>(
      app_get_external_data_path(), std::free);
  EXPECT_EQ(std::string(ext_data_path.get()), EXT_DATA_PATH);
}

TEST_F(AppPathTest, app_get_external_cache_path) {
  aul_get_app_external_cache_path_fake.custom_fake =
    __fake_aul_get_app_external_cache_path;

  auto ext_cache_path = std::unique_ptr<char, decltype(std::free)*>(
      app_get_external_cache_path(), std::free);
  EXPECT_EQ(std::string(ext_cache_path.get()), EXT_CACHE_PATH);
}

TEST_F(AppPathTest, app_get_external_shared_data_path) {
  aul_get_app_external_shared_data_path_fake.custom_fake =
    __fake_aul_get_external_shared_data_path;

  auto ext_shared_data_path = std::unique_ptr<char, decltype(std::free)*>(
      app_get_external_shared_data_path(), std::free);
  EXPECT_EQ(std::string(ext_shared_data_path.get()), EXT_SHARED_DATA_PATH);
}

TEST_F(AppPathTest, app_get_tep_resource_path) {
  aul_get_app_tep_resource_path_fake.custom_fake =
    __fake_aul_get_app_tep_resource_path;

  auto tep_res_path = std::unique_ptr<char, decltype(std::free)*>(
      app_get_tep_resource_path(), std::free);
  EXPECT_EQ(std::string(tep_res_path.get()), TEP_PATH);
}
