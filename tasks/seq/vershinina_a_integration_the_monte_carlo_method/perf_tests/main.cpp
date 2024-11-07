#include <gtest/gtest.h>

#include <vector>

#include "core/perf/include/perf.hpp"
#include "seq/vershinina_a_integration_the_monte_carlo_method/include/ops_seq.hpp"

TEST(vershinina_a_integration_the_monte_carlo_method, test_pipeline_run) {
  std::vector<float> in;
  std::vector<float> reference_res(1, 0);
  const float count_size_vector = 4;
  in = vershinina_a_integration_the_monte_carlo_method::getRandomVector(count_size_vector);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(reference_res.data()));
  taskDataSeq->outputs_count.emplace_back(reference_res.size());

  auto testTaskSequential =
      std::make_shared<vershinina_a_integration_the_monte_carlo_method::TestTaskSequential>(taskDataSeq);

  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSequential);
  perfAnalyzer->pipeline_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
  ASSERT_EQ(count_size_vector, reference_res[0]);
}

TEST(vershinina_a_integration_the_monte_carlo_method, test_task_run) {
  std::vector<float> in;
  std::vector<float> reference_res(1, 0);
  const float count_size_vector = 4;
  in = vershinina_a_integration_the_monte_carlo_method::getRandomVector(count_size_vector);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(reference_res.data()));
  taskDataSeq->outputs_count.emplace_back(reference_res.size());

  auto testTaskSequential =
      std::make_shared<vershinina_a_integration_the_monte_carlo_method::TestTaskSequential>(taskDataSeq);

  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSequential);
  perfAnalyzer->task_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
  ASSERT_EQ(count_size_vector, reference_res[0]);
}
