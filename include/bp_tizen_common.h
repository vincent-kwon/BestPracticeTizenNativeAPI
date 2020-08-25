/*
 * Copyright (c) 2020 hobum.kwon@gmail.com All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef __TIZEN_BPS_BP_TIZEN_H__
#define __TIZEN_BPS_BP_TIZEN_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file bp_tizen_common.h
 */

/**
 * @addtogroup CAPI_BPS_BP_TIZEN_MODULE
 * @{
 */


/**
 * @brief Enumeration for some events.
 * @since_tizen @if MOBILE 6.0 @elseif WEARABLE 6.0 @endif
 */
typedef enum {
	BP_TIZEN_EVENT_1 = 0, /**< The bp tizen event 1*/
	BP_TIZEN_EVENT_2 = 1, /**< The bp tizen event 2*/
} bptizen_event_type_e;

/**
 * @brief Gets the one of the application.
 * @since_tizen @if MOBILE 6.0 @elseif WEARABLE 6.0 @endif
 * @return @c 0 on success,
 *         otherwise a negative error value
 * @retval #BPTIZEN_ERROR_NONE Successful
 * @retval #BPTIZEN_ERROR_INVALID_PARAMETER Invalid parameter
 */
int bptizen_get_one();

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_BPS_BP_TIZEN_H__ */

