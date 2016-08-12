/*
 * COPYRIGHT 2016 SEAGATE LLC
 *
 * THIS DRAWING/DOCUMENT, ITS SPECIFICATIONS, AND THE DATA CONTAINED
 * HEREIN, ARE THE EXCLUSIVE PROPERTY OF SEAGATE TECHNOLOGY
 * LIMITED, ISSUED IN STRICT CONFIDENCE AND SHALL NOT, WITHOUT
 * THE PRIOR WRITTEN PERMISSION OF SEAGATE TECHNOLOGY LIMITED,
 * BE REPRODUCED, COPIED, OR DISCLOSED TO A THIRD PARTY, OR
 * USED FOR ANY PURPOSE WHATSOEVER, OR STORED IN A RETRIEVAL SYSTEM
 * EXCEPT AS ALLOWED BY THE TERMS OF SEAGATE LICENSES AND AGREEMENTS.
 *
 * YOU SHOULD HAVE RECEIVED A COPY OF SEAGATE'S LICENSE ALONG WITH
 * THIS RELEASE. IF NOT PLEASE CONTACT A SEAGATE REPRESENTATIVE
 * http://www.seagate.com/contact
 *
 * Original author:  Kaustubh Deorukhkar <kaustubh.deorukhkar@seagate.com>
 * Original creation date: 16-Jun-2016
 */

#include "s3_cli_options.h"
#include "s3_option.h"

DEFINE_string(s3host, "0.0.0.0", "S3 server bind address");
DEFINE_int32(s3port, 8081, "S3 server bind port");

DEFINE_string(s3loglevel, "INFO", "options: DEBUG | INFO | WARN | ERROR | FATAL");

DEFINE_bool(perfenable, false, "Enable performance log");
DEFINE_string(perflogfile, "/var/log/seagate/s3/perf.log", "Performance log path");

DEFINE_string(clovislocal, "localhost@tcp:12345:33:100", "Clovis local address");
DEFINE_string(clovisha, "CLOVIS_DEFAULT_HA_ADDR", "Clovis ha address");
DEFINE_string(clovisconfd, "localhost@tcp:12345:33:100", "Clovis confd address");
DEFINE_int32(clovislayoutid, 9, "For options please see the readme");
DEFINE_string(clovisprofile, "<0x7000000000000001:0>", "Clovis profile");

DEFINE_string(authhost, "127.0.0.1", "Auth server host");
DEFINE_int32(authport, 8095, "Auth server port");
DEFINE_bool(disable_auth, false, "Disable authentication");

DEFINE_bool(fake_authenticate, false, "Fake out authenticate");
DEFINE_bool(fake_authorization, false, "Fake out authorization");

DEFINE_bool(fake_clovis_createobj, false, "Fake out clovis create object");
DEFINE_bool(fake_clovis_writeobj, false, "Fake out clovis write object data");
DEFINE_bool(fake_clovis_deleteobj, false, "Fake out clovis delete object");
DEFINE_bool(fake_clovis_createidx, false, "Fake out clovis create index");
DEFINE_bool(fake_clovis_deleteidx, false, "Fake out clovis delete index");
DEFINE_bool(fake_clovis_getkv, false, "Fake out clovis get key-val");
DEFINE_bool(fake_clovis_putkv, false, "Fake out clovis put key-val");
DEFINE_bool(fake_clovis_deletekv, false, "Fake out clovis delete key-val");
DEFINE_bool(fault_injection, false, "Enable fault Injection flag for testing");

int parse_and_load_config_options(int argc, char ** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  // Create the initial options object with default values.
  S3Option *option_instance = S3Option::get_instance();

  // load the configurations from config file.
  bool force_override_from_config = true;
  if (!option_instance->load_all_sections(force_override_from_config)) {
    return -1;
  }

  // Override with options set on command line
  gflags::CommandLineFlagInfo flag_info;

  gflags::GetCommandLineFlagInfo("s3host", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_BIND_ADDR, flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("s3port", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_BIND_PORT, flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("authhost", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_AUTH_IP_ADDR, flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("authport", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_AUTH_PORT, flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("perflogfile", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_PERF_LOG_FILE, flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("log_dir", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_LOG_DIR,
                                        flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("s3loglevel", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_LOG_MODE, flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("max_log_size", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_LOG_FILE_MAX_SIZE,
                                        flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("clovislocal", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_CLOVIS_LOCAL_ADDR, flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("clovisha", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_CLOVIS_HA_ADDR, flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("clovisconfd", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_OPTION_CLOVIS_CONFD_ADDR, flag_info.current_value.c_str());
  }

  gflags::GetCommandLineFlagInfo("clovislayoutid", &flag_info);
  if (!flag_info.is_default) {
    option_instance->set_cmdline_option(S3_CLOVIS_LAYOUT_ID, flag_info.current_value.c_str());
  }

  return 0;
}
