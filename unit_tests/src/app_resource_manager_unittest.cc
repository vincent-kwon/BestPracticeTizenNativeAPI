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
#include <app_resource_manager.h>

#include <iostream>
#include <memory>

#include "unit_tests/mock/aul_rsc_mgr.h"

extern int gargc;
extern char** gargv;

class AppResourceManagerTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

static int __fake_aul_resource_manager_init(void) {
  return 0;
}

static int __fake_aul_resource_manager_get(aul_resource_e type, const char* id,
    char** path) {
  *path = strdup(
      "/opt/usr/home/owner/apps_rw/org.tizen.helloworld/res/image.png");
  return 0;
}

static int __fake_aul_resource_manager_release(void) {
  return 0;
}

TEST_F(AppResourceManagerTest, app_resource_manager_init_RETURN_NONE) {
  aul_resource_manager_init_fake.custom_fake = __fake_aul_resource_manager_init;

  int r = app_resource_manager_init();
  EXPECT_EQ(r, APP_ERROR_NONE);
}

TEST_F(AppResourceManagerTest, app_resource_manager_get_RETURN_NONE) {
  aul_resource_manager_get_fake.custom_fake = __fake_aul_resource_manager_get;

  char *path = nullptr;
  int r = app_resource_manager_get(APP_RESOURCE_TYPE_IMAGE, "image", &path);
  EXPECT_EQ(r, APP_ERROR_NONE);
  auto p = std::unique_ptr<char, decltype(std::free)*>(path, std::free);
  EXPECT_EQ(std::string(p.get()),
      "/opt/usr/home/owner/apps_rw/org.tizen.helloworld/res/image.png");
}

TEST_F(AppResourceManagerTest, app_resource_manager_release_RETURN_NONE) {
  aul_resource_manager_release_fake.custom_fake =
    __fake_aul_resource_manager_release;

  int r = app_resource_manager_release();
  EXPECT_EQ(r, APP_ERROR_NONE);
}
