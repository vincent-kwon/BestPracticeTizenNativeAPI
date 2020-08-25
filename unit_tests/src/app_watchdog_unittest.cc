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

#include "unit_tests/mock/appcore_watchdog.h"

extern int gargc;
extern char** gargv;

class AppWatchdogTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

static int __fake_appcore_watchdog_enable_return_zero(void) {
  return 0;
}

static int __fake_appcore_watchdog_enable_return_error(void) {
  return -1;
}

static int __fake_appcore_watchdog_disable_return_zero(void) {
  return 0;
}

static int __fake_appcore_watchdog_disable_return_error(void) {
  return -1;
}

static int __fake_appcore_watchdog_kick_return_zero(void) {
  return 0;
}

static int __fake_appcore_watchdog_kick_return_error(void) {
  return -1;
}

TEST_F(AppWatchdogTest, app_watchdog_timer_enable_RETURN_NONE) {
  appcore_watchdog_enable_fake.custom_fake =
    __fake_appcore_watchdog_enable_return_zero;

  int r = app_watchdog_timer_enable();
  EXPECT_EQ(r, APP_ERROR_NONE);
}

TEST_F(AppWatchdogTest, app_watchdog_timer_enable_RETURN_INVALID_CONTEXT) {
  appcore_watchdog_enable_fake.custom_fake =
    __fake_appcore_watchdog_enable_return_error;

  int r = app_watchdog_timer_enable();
  EXPECT_EQ(r, APP_ERROR_INVALID_CONTEXT);
}

TEST_F(AppWatchdogTest, app_watchdog_timer_disable_RETURN_NONE) {
  appcore_watchdog_disable_fake.custom_fake =
    __fake_appcore_watchdog_disable_return_zero;

  int r = app_watchdog_timer_disable();
  EXPECT_EQ(r, APP_ERROR_NONE);
}

TEST_F(AppWatchdogTest, app_watchdog_timer_disable_RETURN_INVALID_CONTEXT) {
  appcore_watchdog_disable_fake.custom_fake =
    __fake_appcore_watchdog_disable_return_error;

  int r = app_watchdog_timer_disable();
  EXPECT_EQ(r, APP_ERROR_INVALID_CONTEXT);
}

TEST_F(AppWatchdogTest, app_watchdog_timer_kick_RETURN_NONE) {
  appcore_watchdog_kick_fake.custom_fake =
    __fake_appcore_watchdog_kick_return_zero;

  int r = app_watchdog_timer_kick();
  EXPECT_EQ(r, APP_ERROR_NONE);
}

TEST_F(AppWatchdogTest, app_watchdog_timer_kick_RETURN_INVALID_CONTEXT) {
  appcore_watchdog_kick_fake.custom_fake =
    __fake_appcore_watchdog_kick_return_error;

  int r = app_watchdog_timer_kick();
  EXPECT_EQ(r, APP_ERROR_INVALID_CONTEXT);
}
