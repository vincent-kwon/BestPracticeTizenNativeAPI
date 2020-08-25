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
#include <app_common_internal.h>

#include <iostream>
#include <memory>

extern int gargc;
extern char** gargv;

class AppFinalizerTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}

  static void AppFinalizerCB(void* data) {
    AppFinalizerTest* p = static_cast<AppFinalizerTest*>(data);
    p->app_finalizer_cb_touched_ = true;
  }

  bool app_finalizer_cb_touched_ = false;;
};

TEST_F(AppFinalizerTest, app_finalizer_add) {
  int r = app_finalizer_add(AppFinalizerCB, this);
  EXPECT_EQ(r, APP_ERROR_NONE);

  app_finalizer_remove(AppFinalizerCB);
}

TEST_F(AppFinalizerTest, app_finalizer_remove) {
  /* pre */
  int r = app_finalizer_add(AppFinalizerCB, this);
  EXPECT_EQ(r, APP_ERROR_NONE);

  r = app_finalizer_remove(AppFinalizerCB);
  EXPECT_EQ(r, APP_ERROR_NONE);
}

TEST_F(AppFinalizerTest, app_finalizer_execute) {
  /* pre */
  int r = app_finalizer_add(AppFinalizerCB, this);
  EXPECT_EQ(r, APP_ERROR_NONE);

  app_finalizer_execute();
  EXPECT_EQ(app_finalizer_cb_touched_, true);
}
