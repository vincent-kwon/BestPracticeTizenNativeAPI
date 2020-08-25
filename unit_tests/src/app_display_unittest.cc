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

#include <iostream>
#include <memory>

#include "include/app_common.h"
#include "unit_tests/mock/system_info.h"
#include "unit_tests/mock/appcore_base.h"

extern int gargc;
extern char** gargv;

class AppDisplayTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

static int __fake_system_info_get_platform_bool_true(const char* key,
                                                     bool* val) {
  *val = true;
  return SYSTEM_INFO_ERROR_NONE;
}

static int __fake_appcore_base_get_display_state_return_on(void) {
  return APPCORE_BASE_DISPLAY_STATE_ON;
}

static int __fake_appcore_base_get_display_state_return_off(void) {
  return APPCORE_BASE_DISPLAY_STATE_OFF;
}

static int __fake_appcore_base_get_display_state_return_unknown(void) {
  return APPCORE_BASE_DISPLAY_STATE_UNKNOWN;
}

TEST_F(AppDisplayTest, app_get_display_state_RETURN_ON) {
  system_info_get_platform_bool_fake.custom_fake =
    __fake_system_info_get_platform_bool_true;
  appcore_base_get_display_state_fake.custom_fake =
    __fake_appcore_base_get_display_state_return_on;

  app_display_state_e display_state;
  int r = app_get_display_state(&display_state);
  EXPECT_EQ(r, APP_ERROR_NONE);
  EXPECT_EQ(display_state, APP_DISPLAY_STATE_ON);
}

TEST_F(AppDisplayTest, app_get_display_state_RETURN_OFF) {
  system_info_get_platform_bool_fake.custom_fake =
    __fake_system_info_get_platform_bool_true;
  appcore_base_get_display_state_fake.custom_fake =
    __fake_appcore_base_get_display_state_return_off;

  app_display_state_e display_state;
  int r = app_get_display_state(&display_state);
  EXPECT_EQ(r, APP_ERROR_NONE);
  EXPECT_EQ(display_state, APP_DISPLAY_STATE_OFF);
}

TEST_F(AppDisplayTest, app_get_display_state_RETURN_INVALID_CONTEXT) {
  system_info_get_platform_bool_fake.custom_fake =
    __fake_system_info_get_platform_bool_true;
  appcore_base_get_display_state_fake.custom_fake =
    __fake_appcore_base_get_display_state_return_unknown;

  app_display_state_e display_state;
  int r = app_get_display_state(&display_state);
  EXPECT_EQ(r, APP_ERROR_INVALID_CONTEXT);
}

TEST_F(AppDisplayTest, app_get_display_state_RETURN_INVALID_PARAMETER) {
  system_info_get_platform_bool_fake.custom_fake =
    __fake_system_info_get_platform_bool_true;
  appcore_base_get_display_state_fake.custom_fake =
    __fake_appcore_base_get_display_state_return_on;

  int r = app_get_display_state(nullptr);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);
}

