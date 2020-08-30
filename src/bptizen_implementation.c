/*
 * Copyright (c) 2020 hobum.kwon Ltd All Rights Reserved
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

#include <bp_tizen_common.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dlog.h>
#include <dbus/dbus.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "CAPI_BPS_BP_TIZEN"

const char* bp_client_bus_name = "org.tizen.bp.client.bus";
const char* bp_client_interface_name = "org.tizen.bp.client.interface";
const char* bp_client_object_name =    "/org/tizen/bp/client/object";
const char* bp_client_method_name_1 = "bp.client.methodinterface1.method.name";

const char* bp_manager_bus_name =       "org.tizen.bp.manager.tizen";
const char* bp_manager_object_path =    "/org/tizen/bps/bp/tizen/manager/object";
const char* bp_manager_interface_name = "org.tizen.bps.bp.manager.interface";
const char* bp_manager_method_name_1 = "bp.manager.methodinterface1.method.name";
const char* param = "This must not be null";
DBusPendingCall* pending;

static int bptizen_handle_dbus_signal() 
{
	DBusMessage* msg;
	DBusMessageIter args;
	DBusConnection* conn;
	DBusError err;

	int ret = 0;
	dbus_uint32_t serial = 0;
	static int count = 0;

	dlog_print(DLOG_INFO, LOG_TAG, "bptizen_handle_dbus_signal\n");
    
	// Initialize the error
	dbus_error_init(&err);

	// Connect to the bus and check for errors
	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);

	// Check for dbus error
	if (dbus_error_is_set(&err)) 
	{
		dlog_print(DLOG_INFO, LOG_TAG, "Connection Error (%s)\n", err.message);
		dbus_error_free(&err);
	}

	if (NULL == conn) 
	{
		dlog_print(DLOG_INFO, LOG_TAG, "Connection Null\n");
		exit(1);
	}

	// Request our name on the bus and check for errors
	ret = dbus_bus_request_name(conn, bp_client_bus_name, DBUS_NAME_FLAG_REPLACE_EXISTING , &err);

	// For request name, check error
	if (dbus_error_is_set(&err)) 
	{
		dlog_print(DLOG_INFO, LOG_TAG, "Name Error (%s)\n", err.message);
		dbus_error_free(&err);
	}

	// Check for primary for the requested name
	if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) 
	{
		dlog_print(DLOG_INFO, LOG_TAG, "Not Primary Owner (%d)\n", ret);
		exit(1);
	}

    // Try a method call
	dlog_print(DLOG_INFO, LOG_TAG, "Start remote method call %s\n", bp_manager_bus_name);
	msg = dbus_message_new_method_call(bp_manager_bus_name, // target for the method call
	   	 	 	 	 	 	 	bp_manager_object_path, // object to call on
	                            bp_manager_interface_name, // interface to call on
    	                        bp_manager_method_name_1); // method name
    dlog_print(DLOG_INFO, LOG_TAG, "End remote method call %s\n", bp_manager_bus_name);
	// append arguments
	dbus_message_iter_init_append(msg, &args);

	if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &param)) {
		dlog_print(DLOG_INFO, LOG_TAG, "Out Of Memory!\n");
		exit(1);
	}

	// send message and get a handle for a reply
	if (!dbus_connection_send_with_reply (conn, msg, &pending, -1)) { // -1 is default timeout
		dlog_print(DLOG_INFO, LOG_TAG, "[Client] Out Of Memory!\n");
		exit(1);
	}

	if (NULL == pending) {
		dlog_print(DLOG_INFO, LOG_TAG, "[Client] Pending Call Null\n");
		exit(1);
	}
	dbus_connection_flush(conn);

	if (NULL == msg) {
	    dlog_print(DLOG_INFO, LOG_TAG, "[Client] Message Null\n");
		exit(1);
	}

	// append arguments
#if REPLY	
	dbus_message_iter_init_append(msg, &args);

	if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &param)) 
	{
		dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Out Of Memory!\n");
		exit(1);
	}

	// send message and get a handle for a reply
	if (!dbus_connection_send_with_reply (conn, msg, &pending, -1)) 
	{ // -1 is default timeout
		dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Out Of Memory!\n");
		exit(1);
	}

	if (NULL == pending) {
		dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Pending Call Null\n");
		exit(1);
	}
	dbus_connection_flush(conn);
    // free message
	dbus_message_unref(msg);
    dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client]  End of remote method call\n");
#endif			

#if 0
	// Wait for new message
	while (true) {
	    //send new signal here
  	    //create a signal & check for errors
		if (count%2) {
			dlog_print(DLOG_INFO, LOG_TAG, "[SystemServer] start send signal now\n");
			msg = dbus_message_new_signal(bp_client_object_name,
										  bp_client_interface_name,
										  bp_client_signal_name_1);

			if (NULL == msg) {
				dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Message Null\n");
				exit(1);
			}

			//append arguments onto signal
			dbus_message_iter_init_append(msg, &args);

			if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_UINT32, &count)) {
				dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Out Of Memory!\n");
				exit(1);
			}

			if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &application_path)) {
				dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Out Of Memory!\n");
				exit(1);
			}

			//send the message and flush the connection
			if (!dbus_connection_send(conn, msg, &serial)) {
				dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Out Of Memory!\n");
				exit(1);
			}

			//Flush
			dbus_connection_flush(conn);

			//Free the message and close the connection
			dbus_message_unref(msg);
		    dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client]  End of Signal Sending call\n");
		}
		else {
#if 1
			//@20111210-vincent: DBus will not work if below value is empty;
			 const char* param = "This must not be null";
			 DBusPendingCall* pending;
			 int level;
			 bool stat;
		     dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client]  start remote method call\n");
			 msg = dbus_message_new_method_call(bp_client_bus_name, // target for the method call
					 	 	 	 	 	 	 	bp_client_object_name, // object to call on
			                                    bp_client_interface_name, // interface to call on
			                                    bp_client_method_name_1); // method name
		    if (NULL == msg) {
			  dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Message Null\n");
			  exit(1);
			}

		    // append arguments
		    dbus_message_iter_init_append(msg, &args);

			if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &param)) {
			  dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Out Of Memory!\n");
			  exit(1);
			}

			// send message and get a handle for a reply
			if (!dbus_connection_send_with_reply (conn, msg, &pending, -1)) { // -1 is default timeout
			  dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Out Of Memory!\n");
			  exit(1);
			}

			if (NULL == pending) {
			  dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client] Pending Call Null\n");
			  exit(1);
			}
			dbus_connection_flush(conn);

  		    // free message
			dbus_message_unref(msg);
		    dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client]  End of remote method call\n");

#endif

#if 1
			// block until we recieve a reply
			dbus_pending_call_block(pending);

			// get the reply message
			msg = dbus_pending_call_steal_reply(pending);
			if (NULL == msg) {
			  dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client]  Error!!! Reply Null\n");
			  exit(1);
			}
			// free the pending message handle
			dbus_pending_call_unref(pending);

			// read the parameters
			if (!dbus_message_iter_init(msg, &args)) {
			  dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client]  Error!!! Message has no arguments!\n");
			  exit(1);
			}
			else if (DBUS_TYPE_UINT32 != dbus_message_iter_get_arg_type(&args)) {
			  dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client]  Error!!! Argument is not int!\n");
			  exit(1);
			}
			else {
			  dbus_message_iter_get_basic(&args, &level);
			  dlog_print(DLOG_INFO, LOG_TAG, "[System Server Client]  Got Reply:%d\n", level);
			}
			// free reply and close connection
			dbus_message_unref(msg);
#endif
		}

		if (count++ == 10)
			break;

		sleep(1);
	}
#endif
	dbus_connection_close(conn);
}

int bptizen_get_one()
{
	dlog_print(DLOG_INFO, LOG_TAG, "bptizen_get_one is called.......");

	bptizen_handle_dbus_signal();
	return 0;
}
