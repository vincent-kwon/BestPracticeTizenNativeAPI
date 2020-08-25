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
#include <glib.h>
#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "unit_tests/mock/app_common.h"
#include <app_common.h>

extern int gargc;
extern char** gargv;

class AppEventTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(AppEventTest, app_event_get_low_memory_status) {
  app_event_low_memory_status_e status;
  struct app_event_info event_info;
  app_event_info_h info = static_cast<app_event_info_h>(&event_info);

  int r = app_event_get_low_memory_status(nullptr, nullptr);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);

  event_info.type = APP_EVENT_LOW_BATTERY;
  r = app_event_get_low_memory_status(info, &status);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);
}

TEST_F(AppEventTest, app_event_get_low_battery_status) {
  app_event_low_battery_status_e status;
  struct app_event_info event_info;
  app_event_info_h info = static_cast<app_event_info_h>(&event_info);

  int r = app_event_get_low_battery_status(nullptr, nullptr);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);

  info->type = APP_EVENT_LOW_MEMORY;
  r = app_event_get_low_battery_status(info, &status);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);
}

TEST_F(AppEventTest, app_event_get_language) {
  char *lang = nullptr;
  struct app_event_info event_info;
  app_event_info_h info = static_cast<app_event_info_h>(&event_info);

  int r = app_event_get_language(nullptr, nullptr);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);

  info->type = APP_EVENT_DEVICE_ORIENTATION_CHANGED;
  r = app_event_get_language(info, &lang);
  EXPECT_EQ(r, APP_ERROR_INVALID_CONTEXT);
}

TEST_F(AppEventTest, app_event_get_region_format) {
  char *region = nullptr;
  struct app_event_info event_info;
  app_event_info_h info = static_cast<app_event_info_h>(&event_info);

  int r = app_event_get_region_format(nullptr, nullptr);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);

  info->type = APP_EVENT_DEVICE_ORIENTATION_CHANGED;
  r = app_event_get_region_format(info, &region);
  EXPECT_EQ(r, APP_ERROR_INVALID_CONTEXT);
}

TEST_F(AppEventTest, app_event_get_device_orientation) {
  app_device_orientation_e orientation;
  struct app_event_info event_info;
  app_event_info_h info = static_cast<app_event_info_h>(&event_info);

  int r = app_event_get_device_orientation(nullptr, nullptr);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);

  info->type = APP_EVENT_LANGUAGE_CHANGED;
  r = app_event_get_device_orientation(info, &orientation);
  EXPECT_EQ(r, APP_ERROR_INVALID_CONTEXT);
}

TEST_F(AppEventTest, app_event_get_suspended_state) {
  app_suspended_state_e state;
  struct app_event_info event_info;
  app_event_info_h info = static_cast<app_event_info_h>(&event_info);

  int r = app_event_get_suspended_state(nullptr, nullptr);
  EXPECT_EQ(r, APP_ERROR_INVALID_PARAMETER);

  info->type = APP_EVENT_LANGUAGE_CHANGED;
  r = app_event_get_suspended_state(info, &state);
  EXPECT_EQ(r, APP_ERROR_INVALID_CONTEXT);
}
