//
// Copyright (C) 2017 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef UPDATE_ENGINE_AOSP_METRICS_REPORTER_ANDROID_H_
#define UPDATE_ENGINE_AOSP_METRICS_REPORTER_ANDROID_H_

#include <string>

#include "update_engine/common/error_code.h"
#include "update_engine/common/metrics_constants.h"
#include "update_engine/common/metrics_reporter_interface.h"
#include "update_engine/payload_consumer/install_plan.h"

namespace chromeos_update_engine {

class MetricsReporterAndroid : public MetricsReporterInterface {
 public:
  explicit MetricsReporterAndroid(
      DynamicPartitionControlInterface* dynamic_partition_control,
      const InstallPlan* install_plan)
      : dynamic_partition_control_(dynamic_partition_control),
        install_plan_(install_plan) {}

  ~MetricsReporterAndroid() override = default;

  void ReportRollbackMetrics(metrics::RollbackResult result) override {}

  void ReportEnterpriseRollbackMetrics(
      bool success, const std::string& rollback_version) override {}

  void ReportDailyMetrics(base::TimeDelta os_age) override {}

  void ReportUpdateCheckMetrics(
      metrics::CheckResult result,
      metrics::CheckReaction reaction,
      metrics::DownloadErrorCode download_error_code) override {}

  void ReportUpdateAttemptMetrics(int attempt_number,
                                  PayloadType payload_type,
                                  base::TimeDelta duration,
                                  base::TimeDelta duration_uptime,
                                  int64_t payload_size,
                                  metrics::AttemptResult attempt_result,
                                  ErrorCode internal_error_code) override;

  void ReportUpdateAttemptDownloadMetrics(
      int64_t payload_bytes_downloaded,
      int64_t payload_download_speed_bps,
      DownloadSource download_source,
      metrics::DownloadErrorCode payload_download_error_code,
      metrics::ConnectionType connection_type) override;

  void ReportAbnormallyTerminatedUpdateAttemptMetrics() override;

  void ReportSuccessfulUpdateMetrics(
      int attempt_count,
      int updates_abandoned_count,
      PayloadType payload_type,
      int64_t payload_size,
      int64_t num_bytes_downloaded[kNumDownloadSources],
      int download_overhead_percentage,
      base::TimeDelta total_duration,
      base::TimeDelta total_duration_uptime,
      int reboot_count,
      int url_switch_count) override;

  void ReportCertificateCheckMetrics(ServerToCheck server_to_check,
                                     CertificateCheckResult result) override {}

  void ReportFailedUpdateCount(int target_attempt) override {}

  void ReportTimeToReboot(int time_to_reboot_minutes) override {}

  void ReportInstallDateProvisioningSource(int source, int max) override {}

  void ReportInternalErrorCode(ErrorCode error_code) override {}

  void ReportKeyVersionMetrics(int kernel_min_version,
                               int kernel_max_rollforward_version,
                               bool kernel_max_rollforward_success) override {}

  void ReportEnterpriseUpdateSeenToDownloadDays(
      bool has_time_restriction_policy, int time_to_update_days) override {}

 private:
  DynamicPartitionControlInterface* dynamic_partition_control_{};
  const InstallPlan* install_plan_{};

  DISALLOW_COPY_AND_ASSIGN(MetricsReporterAndroid);
};

}  // namespace chromeos_update_engine

#endif  // UPDATE_ENGINE_AOSP_METRICS_REPORTER_ANDROID_H_
