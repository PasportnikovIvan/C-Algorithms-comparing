#include "ParalleITrapezoidalIntegralSolver.hpp"

double ParallelTrapezoidalIntegralSolver::trapezoidalIntegration(const std::function<double(double)> &f, double a,
                                                                 double b, int n) {
    int num_threads = std::thread::hardware_concurrency();
    double h = (b - a) / n;
    double integral = 0.0;
    std::mutex integral_mutex;

    std::vector<std::thread> threads;
    threads.reserve(num_threads);
for (int t = 0; t < num_threads; ++t) {
        threads.emplace_back([&, t]() {
            double thread_integral = 0.0;
            for (int i = t; i < n; i += num_threads) {
                double x0 = a + i * h;
                double x1 = a + (i + 1) * h;
                thread_integral += (f(x0) + f(x1)) / 2;
            }

            std::lock_guard<std::mutex> lock(integral_mutex);
            integral += thread_integral;
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return integral * h;
}